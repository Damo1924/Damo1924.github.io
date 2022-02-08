---
title: "Segment Tree"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` 

## 1. Segment Tree

길이가 $n$인 배열 $A$에 대해 다음 작업을 $m$번 수행해야하는 문제가 있다.

> 두 자연수 $l$, $r$($l \leq r$)이 주어졌을 때, $A\[l\] + A\[l+1\] + \dots + A\[r\]$을 계산하여 출력하기

단순히 매번 하나하나 더한다면 각 작업마다 $O(n)$, 총 $O(nm)$의 시간복잡도를 갖는다.

이 문제를 가장 효율적으로 해결하는 방법은 다음과 같다.

$S\]i\] = A\[1\] + \dots + A\[i\]$인 배열 $S$를 미리 구해두면, 각 작업을 $O(1)$에 수행할 수 있다.

배열 $S$를 구하는데 $O(n)$, $m$번의 작업을 수행하는데 $O(m)$이므로 총 $O(n + m)$의 시간복잡도로 해결할 수 있다.

그렇다면 이번에는 새로운 작업 하나를 추가해보자.

> 자연수 $i$, 정수 $v$가 주어졌을 때, $A\[i\] = v$

