---
title: "Computing Binomial Coefficients (mod $p^q$)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` 정수론, 이항계수, Wilson's theorem, Legendre's theorem, Kummer's theorem, Andrew Granville's paper

이번 포스팅은 [BOJ 14854. 이항 계수 6](https://www.acmicpc.net/problem/14854)를 풀기 위해 필요한 정리를 이해하기 위한 내용을 담았다.

또한, 그 과정에서 새롭게 알게 된 정수론 지식들에 대해서도 다루었다.

## 1. Wilson's Theorem

> **자연수 $n$($n > 1$)이 소수인 것의 필요충분조건은 $(n-1)! \equiv -1 \pmod{n}$이다.

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

(\gets) 
