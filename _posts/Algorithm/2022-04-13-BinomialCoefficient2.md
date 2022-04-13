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

간단한 이항계수 문제들의 경우에는 소수(ex. $10^9 + 7$)로 나눈 나머지를 구하거나,

조금 더 복잡한 문제라면 제곱 인수가 없는 정수(square-free integer)로 나눈 나머지를 구하게 된다.

소수로 나눈 나머지를 구할 때는 [이 포스트](https://damo1924.github.io/algorithm/BinomialCoefficient/)에서 다루고 있는 방법들로 해결할 수 있고,

제곱 인수가 없는 정수로 나눈 나머지를 구할 때에는 해당 수를 소인수분해하여 얻은 소수들 각각으로 나눈 나머지를 구한 뒤, 중국인의 나머지 정리(Chinese Remainder Theorem)을 사용하여 답을 얻을 수 있다.

하지만 $142857 = 3^3 \times 11 \times 13 \times 37$이므로 square-free가 아니기 때문에 기존에 사용하던 방법으로는 해결할 수 없다.

따라서 이 문제를 풀기 위해서는 **이항계수를 소수의 제곱꼴로 나눈 나머지**를 빠르게 구할 수 있어야한다.



<br/>

## 1. Background Knowledges from Number Theory

필요한 내용을 찾아보면서 함께 공부한 정수론 배경지식들에 대해 정리하였다.

---

### Wilson's Theorem

> [Thm] **자연수 $n$($n > 1$)이 소수인 것의 필요충분조건은 $(n-1)! \equiv -1 \pmod{n}$이다.**

**Proof.**

$(\to)$ 소수 $p$에 대해 $(p-1)! \equiv -1 \pmod{p}$가 성립한다는 사실을 보이자.

$p = 2$이면 $(2 - 1)! \equiv -1 \pmod{2}$이므로 성립한다.

$p = 3$이면 $(3 - 1)! \equiv -1 \pmod{3}$이므로 성립한다.

이제 $p > 3$인 경우에 대해 합동식이 성립함을 보이면 된다.

정수 $a$($1 \leq a \leq p - 1$)에 대해 $a$는 유일한 모듈러 곱셈의 역원(modular multiplicative inverse) $a^{-1}$을 갖는다.

이때 $a \equiv a^{-1} \pmod{p}$는 $a^2 \equiv 1 \pmod{p}$이므로, 자기 자신이 역원인 정수 $a$는 $a \equiv \pm 1 \pmod{p}$뿐이다.

따라서 $(p-1)!$의 인자 중 $1$과 $p-1$을 제외한 나머지 인자들은 $a_ib_i \equiv 1 \pmod{p}$를 만족하는 쌍 $(a_i, b_i)$($a_i \neq b_i$)로 묶을 수 있다.

\begin{aligned}
(p-1)! = \[ 1 \cdot (p - 1) \] \cdot \prod_{i=1}^{(p-3)/2} a_i \cdot b_i \equiv (-1) \cdot \prod 1 \equiv -1 \pmod{p}
\end{aligned}

(\gets) $(n - 1)! \equiv -1 \pmod{n}$을 만족하는 정수 $n$은 소수임을 보이자.

$n$이 소수가 아니라고 가정하면, $n$은 $1 < d < n$인 어떤 정수 $d$에 대해 $d \mid n$이다.

또한, $1 < d < n$이므로 $d \mid (n-1)!$이다.

한편, 주어진 식으로부터 $(n-1)!+1 \equiv 0 \pmod{n}$이므로 $n \mid (n-1)! + 1$이다.

$d \mid n$이므로 $d \mid (n-1)! + 1$이다.

따라서 $d$는 $d \mid 1$을 만족해야하는데, 이는 $d$가 $1$보다 큰 정수라는 것에 모순이다.

따라서 주어진 식을 만족하는 $n$은 소수이다.

---

### 1-2. Legendre's Theorem

> [Def] **소수 $p$와 $0$이 아닌 정수 $n$에 대하여, $\nu_p(n)$을 $n$의 $p$진 값매김($p$-adic valuation)이라 하고, $p^{\nu} \mid n$을 만족하는 양의 정수 $\nu$ 중 가장 큰 값으로 정의한다. 또한, $\nu_p(0) = \infty$로 정의한다.
> 
> \begin{aligned}
> \nu_p(n) = 
> \begin{cases}
> \max\\{\nu \in \mathbb{N} : p^{\nu} \mid n \\} & \mbox{if } n \neq 0 \\\\  
> \infty & \mbox{if } n = 0
> \end{aligned}
> 
> 즉, $\nu_p(n)$는 $n$을 소인수분해 했을 때 $p$의 지수와 같다.



<br/>

## References

[1] [WIKIPEDIA, 'Wilson's theorem'](https://en.m.wikipedia.org/wiki/Wilson%27s_theorem)  
[2] 
