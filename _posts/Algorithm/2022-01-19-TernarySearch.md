---
title: "삼분 탐색(Ternary Search)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` Parametric Search, Unimodal functions

## 1. Ternary Search

삼분 탐색은 **볼록 함수에서 극값이나 최대/최솟값을 찾을 때** 사용하는 방법이다.

이분 탐색이 항상 단조 증가/감소하는 함수에만 사용할 수 있었던 것에 비해, 삼분 탐색은 더 많은 함수에 대해 적용할 수 있다는 장점이 있다.

방법 자체는 이분 탐색과 크게 다르지 않다.

아래로 볼록한 함수 $f(x)$의 최솟값을 찾는 경우를 생각해보자.($x$는 정수값만을 가진다.)

주어진 $x$값의 구간을 $\[s, e)$라고 하면, 해당 구간을 삼등분하는 두 값 $p, q$는 다음과 같다.

\begin{aligned}
p = \lfloor \frac{2s + e}{3} \rfloor, q = \lfloor \frac{s + 2e}{3} \rfloor
\end{aligned}

전체 구간은 $\[s, p)$, $\[p, q)$, $\[q, e)$로 나누어진다.

여기서 $f(p)$와 $f(q)$ 값에 따라 두 가지 경우로 나눌 수 있다.

1. $f(p) > f(q)$: 구간 $\[s, p)$에서 최솟값을 가질 수 없으므로 탐색 범위를 $\[p, e)$로 줄인다.
2. 
