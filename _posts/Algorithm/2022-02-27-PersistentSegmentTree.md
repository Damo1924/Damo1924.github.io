---
title: "Persistent Segment Tree"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` 

## 1. When do we use a Persistent Segment Tree?

Persistent segment tree는 **여러 개의 세그먼트 트리를 효율적으로 관리하는 자료구조**이다.

어떤 상황에서 persistent segment tree를 사용할 수 있는지 간단한 예시를 통해 알아보자.

---

다음과 같은 문제는 세그먼트 트리를 이용해서 쉽게 풀 수 있다.

> 길이가 $N$인 선분 위에 $M$개의 점이 있다.
> 
> 이때 특정 구간에 포함되어 있는 점의 개수를 구하는 쿼리를 $Q$개 처리해야한다.

만약 $N$이 작다면 **구간 합 구하기** 문제처럼 DP로 $O(N + Q)$로 해결할 수도 있다.

이번에는 위 문제를 2차원 좌표평면으로 확장시켜보자.

> 좌표평면 상의 크기가 $N \times N$인 영역에 $M$개의 점이 있다.
> 
> 이때 특정 영역에 포함되어 있는 점의 개수를 구하는 쿼리를 $Q$개 처리해야한다.

이 문제도 마찬가지로 $N$이 작다면 **2차원 영역의 합 구하기** 문제처럼 DP로 $O(N^2 + NQ)$로 해결할 수 있다.

하지만 $N$이 $10^6$ 정도로 커지면 DP로 시간 내에 해결할 수 없게 된다.

이때 가장 먼저 떠오르는 방법은 바로 세그먼트 트리를 $x$좌표마다 구현하는 것이다.

이러면 각 쿼리를 $O(\log N)$에 처리할 수 있게 되지만, 문제는 공간복잡도가 $O(2N^2)$이 되어 메모리초과가 발생할 확률이 매우 높다.

> 세그먼트 트리를 구현하는데 필요한 배열의 크기는,
> 
> 트리의 높이 $h = \lceil \log N \rceil$에 대해 $2^{h + 1} \leq 2N$이다.
> 
> 따라서 각 $x$좌표마다 세그먼트 트리를 구현하는데 필요한 배열의 크기는 $O(2N^2)$이다.

바로 이런 상황에서 persistent segment tree를 사용할 수 있다.

<br/>

## 2. What is a Persistent Segment Tree?











