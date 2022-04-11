---
title: "중국인의 나머지 정리(Chinese Remainder Theorem, CRT)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` 정수론, 합동식, 

## 1. Chinese Remainder Theorem

### 1-1. Theorem

$1$보다 크고 서로 서로소(coprime)인 $k$개의 정수 $n_1, n_2, \dots, n_k$와 $N = n_1 n_2 \dots n_k$을 생각하자. 

중국인의 나머지 정리는 아래 연립 합동식(congruence)의 해가 존재한다는 것이다.

\begin{aligned}
x \equiv a_1 \pmod{n_1} \\\\  
x \equiv a_2 \pmod{n_2} \\\\  
\dots 
x \equiv a_k \pmod{n_k}
\end{aligned}

이때 모든 $i$에 대해 $a_i$는 $0 \leq a_i < n_i$를 만족하는 정수이다.

특히, $0 \leq x < N$을 만족하는 해 $x$는 유일하다.

---

### 1-2. Proof

**[Uniqueness]**

$x, y$($x > y$)를 주어진 연립 합동식의 해라고 하자.

모든 $i$에 대해 $x \equiv y \pmod{n_i}$이므로, $x - y$는 $n_i$의 배수이다.

즉, 어떤 양의 정수 $m$에 대해 $x - y = mN$이다.

따라서 $0$ 이상, $n$ 미만인 해는 유일하다.

**[Existence]**



---

