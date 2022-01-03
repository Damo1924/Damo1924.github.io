---
title: "Knapsack Problem"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` DP, Backtracking, Branch and Bound

## 0. Knapsack Problem

$n$개의 물건이 있을 때, $i$번째 물건의 무게를 $w_i$, 가치를 $v_i$라고 하자.

배낭에 넣을 수 있는 최대 무게가 $W$인 배낭이 있다.

이 배낭에 넣은 물건들의 가치의 합이 최대가 되도록 물건을 담고 싶다.

배낭에 담은 $i$번째 물건의 개수를 $x_i$라고 하면, $x_1, x_2, \dots, x_n$는 다음을 만족한다.

\begin{aligned}
\sum_{i = 1}^n w_ix_i \leq W
\end{aligned}




0-1 knapsack problem은 각 물건의 개수를 가장 일반적인 형태의 문제이다.

$n$개의 물건이 있을 때, $i$번째 물건의 무게를 $w_i$, 가치를 $v_i$라고 하자.

배낭에 넣을 수 있는 최대 무게가 $W$인 배낭이 있다.

이 배낭에 넣을 수 있는 물건들의 가치가 최대가 되는 

## 1. Bruteforce

