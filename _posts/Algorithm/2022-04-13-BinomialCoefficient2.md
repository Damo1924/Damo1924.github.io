---
title: "Computing Binomial Coefficients (mod prime power)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` 정수론, 이항계수, Wilson's theorem, Legendre's theorem, Kummer's theorem, Andrew Granville's paper

## 0. Introduction

이번 포스팅은 [BOJ 14854. 이항 계수 6](https://www.acmicpc.net/problem/14854)를 풀기 위해 필요한 정리를 이해하기 위한 내용을 담았다.

위 문제는 이항계수를 $142857$이라는 특이한 숫자로 나눈 나머지를 구하는 문제이다.

간단한 이항계수 문제들의 경우에는 **소수**(ex. $10^9 + 7$)로 나눈 나머지를 구하거나,

조금 더 복잡한 문제라면 **제곱 인수가 없는 정수(square-free integer)**로 나눈 나머지를 구하게 된다.

소수로 나눈 나머지를 구할 때는 [이 포스트](https://damo1924.github.io/algorithm/BinomialCoefficient/)에서 다루고 있는 방법들로 해결할 수 있고,

제곱 인수가 없는 정수로 나눈 나머지를 구할 때에는 해당 수를 소인수분해하여 얻은 소수들 각각으로 나눈 나머지를 구한 뒤, 중국인의 나머지 정리(Chinese Remainder Theorem)을 사용하여 답을 얻을 수 있다.

하지만 $142857 = 3^3 \times 11 \times 13 \times 37$이므로 square-free가 아니기 때문에 기존에 사용하던 방법으로는 해결할 수 없다.

따라서 이 문제를 풀기 위해서는 **이항계수를 소수의 제곱꼴로 나눈 나머지**를 빠르게 구할 수 있어야한다.



<br/>

## 1. Background Knowledges from Number Theory

필요한 내용을 찾아보면서 함께 공부한 정수론 배경지식들에 대해 정리하였다.

---

### 1-1. Wilson's Theorem

> [Thm] Wilson's Theorem
> 
> $1$보다 큰 자연수 $n$이 소수인 것의 필요충분조건은 $(n-1)! \equiv -1 \pmod{n}$이다.

**Proof.**

$(\to)$ 소수 $p$에 대해 $(p-1)! \equiv -1 \pmod{p}$가 성립한다는 사실을 보이자.

$p = 2$이면 $(2 - 1)! \equiv -1 \pmod{2}$이므로 성립한다.

$p = 3$이면 $(3 - 1)! \equiv -1 \pmod{3}$이므로 성립한다.

이제 $p > 3$인 경우에 대해 합동식이 성립함을 보이면 된다.

정수 $a$($1 \leq a \leq p - 1$)에 대해 $a$는 유일한 모듈러 곱셈의 역원(modular multiplicative inverse) $a^{-1}$을 갖는다.

이때 자기 자신을 역원으로 갖는 정수 $a$는

\begin{aligned}
a \equiv a^{-1} \pmod{p}
\end{aligned}

을 만족하고, 이는

\begin{aligned}
a^2 \equiv 1 \pmod{p}
\end{aligned}

이므로, 자기 자신이 역원인 정수 $a$는 $a \equiv \pm 1 \pmod{p}$뿐임을 알 수 있다.

따라서 $(p-1)!$의 인자 중 $1$과 $(p-1)$을 제외한 나머지 인자들은

\begin{aligned}
a_ib_i \equiv 1 \pmod{p}
\end{aligned}

을 만족하는 쌍 $(a_i, b_i)$($a_i \neq b_i$)로 묶을 수 있다.

\begin{aligned}
\therefore (p-1)! = \[ 1 \cdot (p - 1) \] \cdot \prod_{i=1}^{(p-3)/2} a_ib_i \equiv (-1) \cdot \prod_{i=1}^{(p-3)/2} 1 \equiv -1 \pmod{p}
\end{aligned}

$(\gets)$ $(n - 1)! \equiv -1 \pmod{n}$을 만족하는 정수 $n$은 소수임을 보이자.

$n$이 소수가 아니라고 가정하면, $n$은 $1 < d < n$인 어떤 정수 $d$에 대해 $d \mid n$이다.

또한, $1 < d < n$이므로 $d \mid (n-1)!$이다.

한편, 주어진 식으로부터 $(n-1)!+1 \equiv 0 \pmod{n}$이므로 $n \mid (n-1)! + 1$이다.

$d \mid n$이므로 $d \mid (n-1)! + 1$이다.

따라서 $d$는 $d \mid 1$을 만족해야하는데, 이는 $d$가 $1$보다 큰 정수라는 것에 모순이다.

따라서 주어진 식을 만족하는 $n$은 소수이다.

---

### 1-2. Legendre's Theorem

> [Def] 소수 $p$와 $0$이 아닌 정수 $n$에 대하여, $\nu_p(n)$을 **$n$의 $p$진 값매김($p$-adic valuation)**이라 하고,
> 
> $p^{\nu} \mid n$을 만족하는 양의 정수 $\nu$ 중 가장 큰 값으로 정의한다.
> 
> 또한, $\nu_p(0) = \infty$로 정의한다.
> 
> \begin{aligned}
> \nu_p(n) = 
> \begin{cases}
> \max\\{\nu \in \mathbb{N} : p^{\nu} \mid n \\} & \mbox{if } n \neq 0 \\\\  
> \infty & \mbox{if } n = 0
> \end{cases}
> \end{aligned}
> 
> 즉, $\nu_p(n)$는 **$n$을 소인수분해 했을 때 $p$의 지수**와 같다.

> [Thm] Legendre's Formula
> 
> 소수 $p$와 양의 정수 $n$에 대하여 $\nu_p(n!)$은 다음과 같이 구할 수 있다.
> 
> \begin{aligned}
> \nu_p(n!) = \sum_{i=1}^{\infty} \left\lfloor \frac{n}{p^i} \right\rfloor
> \end{aligned}

**Proof.**

$\nu_p(n!)$는 모든 $i$($i > 0$)에 대하여 $1$부터 $n$까지의 정수 중 $p^i$의 개수를 합한 것과 같다.

이때 $1$부터 $n$까지의 정수 중 $p^i$의 개수는 $\left\lfloor \frac{n}{p^i} \right\rfloor$이므로 위 정리가 성립한다.

> [Def] 양의 정수 $n$에 대한 $p$진 전개($p$-adic expansion)는 다음과 같이 나타낼 수 있다.
> 
> \begin{aligned}
> n = a_0 + a_1p + a_2p^2 + \dots + a_kp^k
> \end{aligned}
> 
> 이때 모든 $i$($0 \leq i \leq k$)에 대하여 $a_i$는 $0 \leq a_i \leq p - 1$인 정수이며,
> 
> 이들의 합을 $s_p(n) = a_0 + a_1 + \dots, a_k$로 정의하자.
> 
> 즉, $s_p(n)$은 $n$을 $p$진법으로 나타냈을 때의 각 자릿수의 합과 같다.

> [Thm] Legendre's Theorem
> 
> 소수 $p$와 양의 정수 $n$에 대하여 $\nu_p(n!)$은 다음과 같이 구할 수 있다.
> 
> \begin{aligned}
> \nu_p(n!) = \frac{n - s_p(n)}{p-1}
> \end{aligned}

**Proof.**

$n$의 $p$진 전개를 $n = a_0 + a_1p + a_2p^2 + \dots + a_kp^k$라고 하자.

각 $1 \leq i\leq k$에 대하여

\begin{aligned}
\left\lfloor \frac{n}{p^i} \right\rfloor = a_i + a_{i+1}p + \dots + a_kp^{k-i} = \sum_{j=i}^k a_jp^{j-i}
\end{aligned}

가 성립하고, 르장드르 공식에 의해 다음을 얻는다.

\begin{aligned}
\nu_p(n!) &= \sum_{i=1}^k \left\lfloor \frac{n}{p^i} \right\rfloor = \sum_{i=1}^k \sum_{j=1}^k a_jp^{j-i} = \sum_{j=1}^k \sum_{i=1}^k a_jp^{j-i} \\\\  
&= \sum_{j=1}^k a_j \cdot \frac{p^j - 1}{p-1} = \sum_{j=0}^k a_j \cdot \frac{p^j - 1}{p-1} = \frac{1}{p-1} \left( \sum_{j=0}^k a_jp^j - \sum_{j=0}^ka_j \right) \\\\  
&= \frac{1}{p-1} \left( n - s_p(n) \right)
\end{aligned}

### 1-3. Kummer's Theorem



<br/>

## References

[1] [WIKIPEDIA, 'Wilson's theorem'](https://en.m.wikipedia.org/wiki/Wilson%27s_theorem)  
[2] 
