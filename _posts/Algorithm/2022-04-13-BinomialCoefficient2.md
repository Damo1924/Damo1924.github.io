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

### 1-1. Wilson's Theorem

> **Wilson's Theorem**
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

을 만족하고, 이를 정리하면

\begin{aligned}
(a + 1)(a - 1) \equiv 0 \pmod{p}
\end{aligned}

이므로, $p$가 소수이므로 자기 자신이 역원인 정수 $a$는 $a \equiv \pm 1 \pmod{p}$뿐임을 알 수 있다.

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

> **Definition.** 소수 $p$와 $0$이 아닌 정수 $n$에 대하여, $\nu_p(n)$을 **$n$의 $p$진 값매김($p$-adic valuation)**이라 하고,
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

> **Legendre's Formula**
> 
> 소수 $p$와 양의 정수 $n$에 대하여 $\nu_p(n!)$은 다음과 같이 구할 수 있다.
> 
> \begin{aligned}
> \nu_p(n!) = \sum_{i=1}^{\infty} \left\lfloor \frac{n}{p^i} \right\rfloor
> \end{aligned}

**Proof.**

$\nu_p(n!)$는 모든 $i$($i > 0$)에 대하여 $1$부터 $n$까지의 정수 중 $p^i$의 개수를 합한 것과 같다.

이때 $1$부터 $n$까지의 정수 중 $p^i$의 개수는 $\left\lfloor \frac{n}{p^i} \right\rfloor$이므로 위 정리가 성립한다.

> **Definition.** 양의 정수 $n$에 대한 $p$진 전개($p$-adic expansion)는 다음과 같이 나타낼 수 있다.
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

> **Legendre's Theorem**
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

---

### 1-3. Kummer's Theorem

> **Properties of $p$-adic valuation**
> 
> 소수 $p$와 두 양의 정수 $m, n$에 대하여 다음이 성립한다.
> 
> (a) $\nu_p(nm) = \nu_p(n) + \nu_p(m)$  
> (b) $\nu_p(n^m) = m \cdot \nu_p(n)$  
> (c) $\nu_p \left( \frac{n}{m} \right) = \nu_p(n) - \nu_p(m)$ ($m \neq 0$)

> **Kummer's Theorem**
> 
> 소수 $p$와 두 양의 정수 $m, n$에 대하여 다음 식이 성립한다.
> 
> \begin{aligned}
> \nu_p \left( {m + n \choose n} \right) = \frac{s_p(m) + s_p(n) - s_p(m + n)}{p - 1}
> \end{aligned}
> 
> 이때 위 식의 우변은 $p$진법에서 $m$과 $n$을 더할 때의 **자리 올림의 횟수**와 같다.

**Proof.**

$\nu_p(n)$의 성질과 르장드르 정리에 의해 다음이 성립한다.

\begin{aligned}
\nu_p \left( {m + n \choose n} \right) &= \nu_p \left( \frac{(m+n)!}{m!n!} \right) = \nu_p((m+n)!) - \nu_p(m!) - \nu_p(n!) \\\\  
&= \frac{(m+n) - s_p(m + n)}{p - 1} -  \frac{m - s_p(m)}{p - 1} -  \frac{n - s_p(n)}{p - 1} \\\\  
&= \frac{s_p(m) + s_p(n) - s_p(m + n)}{p - 1}
\end{aligned}

<br/>

## 2. Computing Binomial Coefficients modulo Prime Powers

이제 앞에서 공부한 내용을 토대로 []의 내용을 정리해보자.

> **Definition.** 양의 정수 $n$과 소수 $p$에 대하여, $(n!)\_p$를 다음과 같이 정의한다.
> 
> \begin{aligned}
> (n!)\_p = \prod_{1\leq k \leq n, p \nmid k}^n k
> \end{aligned}
> 
> 즉, $(n!)\_p$는 $n$ 이하의 자연수 중 $p$의 배수가 아닌 것들의 곱이다.

> **Lemma 1. Generalization of Wilson's Theorem to prime powers**
> 
> 소수 $p$와 자연수 $q$에 대하여 다음이 성립한다.
> 
> \begin{aligned}
> (p^q!)\_p \equiv \pm 1 \pmod{p^q}
> \end{aligned}
> 
> 이때 $\pm 1$은 Theorem 1에서 정의된 것과 동일하다.

**Proof.** Wilson's Theorem과 비슷한 방법으로 증명이 가능하다.

$1 \leq a \leq p^q$, $p \nmid a$를 만족하는 정수 $a$ 중 모듈러 곱셈의 역원이 자기 자신과 같은 것은 다음을 만족한다.

\begin{aligned}
(a + 1)(a - 1) \equiv 0 \pmod{p^q}
\end{aligned}

$p, q$에 따라 경우를 나누어서 위 합동식의 해를 구하면,

(a) $p^q = 2$ : $a = 1$  
(b) $p^q = 4$ : $a = 1, 3$  
(c) $p = 2, q \geq 3$ : $a = 1, 2^q - 1, 2^{q-1} \pm 1$  
(d) $p \neq 2$ : $a = 1, p^q- 1$

이다.($p \neq 2$인 경우, $a \equiv \pm 1 \pmod{p^q}$ 이외의 해가 존재하지 않는다.)

위 해들을 제외한 $(p^q!)\_p$의 다른 인자들은 각각의 모듈러 곱셈의 역원과 짝지을 수 있다.

각 경우에 대해 $(p^q!)\_p$를 $p^q$로 나눈 나머지를 구해보면 다음과 같다.

(a) $(2!)\_2 = 1 \equiv -1 \pmod{2}$
(b) $(4!)\_4 = 1 \cdot 3 = 3 \equiv -1 \pmod{4}$  
(c) $(2^q!)\_2 \equiv 1 \cdot (2^q - 1) \cdot (2^{q-1} - 1) \cdot (2^{q-1} + 1) \cdot 1 \equiv 1 \pmod{2^q}$  
(d) $(p^q!)\_p \equiv 1 \cdot (p^q - 1) \cdot 1 \equiv -1 \pmod{p^q}$

따라서 다음을 얻을 수 있다.

\begin{aligned}
(p^q!)\_p =
\begin{cases}
1 & \mbox{if } p = 2 \mbox{ and } q \geq 3 \\\\  
-1 & \mbox{otherwise}
\end{cases}
\end{aligned}

> **Corollary 1.** 

<br/>

## References

[1] [WIKIPEDIA, 'Wilson's theorem'](https://en.m.wikipedia.org/wiki/Wilson%27s_theorem)  
[2] [jjycjn's Math Storehouse, '르장드르의 정리와 쿠머의 정리'](https://jjycjnmath.tistory.com/532)  
[3] 
