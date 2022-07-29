---
title: "Sqrt Decomposition & Mo's Algorithm"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:    
  - Algorithm
use_math: true
comments: true

---

`Tags` 구간 쿼리

## 1. Sqrt Decomposition

**평방 분할(sqrt decomposition)**은 구간 쿼리를 $O(\sqrt{n})$에 처리할 수 있는 방법이다.

예를 들어 부분 수열의 합을 구하는 쿼리나, 최대/최소값을 구하는 쿼리 같은 것들을 빠르게 구할 수 있다.

> 물론 각 쿼리를 $O(\log n)$에 처리할 수 있는 **세그먼트 트리(segment tree)**보단 못하다.

좀 더 직관적인 이해를 위해 구간 합 쿼리를 평방 분할을 이용해서 처리해보자.

- 길이가 $n$인 수열 $a_0, a_1, a_2, \dots, a_{n-1}$ 에 대하여 임의의 두 정수 $l, r$($l < r$)가 주어졌을 때 구간 합 $a_l + a_{l+1} + \dots + a_r$ 의 값을 $O(\sqrt{n})$에 구하여라.

평방 분할은 **전체 구간을 $\sqrt{n}$개의 같은 크기의 블록으로 나누어서 관리**한다.

$\sqrt{n}$가 정수가 아닐 수 있으므로 올림을 해주어서 각 블록의 크기 $s$를 정해주자.

\begin{aligned}
s = \lceil \sqrt{n} \rceil
\end{aligned}

이때 마지막 블록의 크기가 $s$보다 작을 수 있지만, 일단은 무시하자.

각 블록에 속한 원소들의 합을 $b_0, b_1, b_2, \dots, b_{s-1}$ 라고 하면,

\begin{aligned}
b_0 &= a_0 + a_1 + \dots + a_{s-1}, \\\\  
b_1 &= a_s + a_{s+1} + \dots + a_{2s-1}, \\\\  
& \vdots \\\\  
b_{s-1} &= a_{(s-1)s} + \dots + a_{n-1}.
\end{aligned}

이므로, 정수 $k$($0 \leq k < s$)에 대하여

\begin{aligned}
b_k = \sum_{i = ks}^{\min(n-1, (k+1)s - 1)} a_i
\end{aligned}

와 같이 쓸 수 있다. 모든 $b_k$들을 구하는데는 $O(n)$이 걸린다.

이제 구간 쿼리 $l, r$을 처리해보자.

구간 $\[l, r\]$은 크게 세 가지 부분으로 구분할 수 있다.

1. 블록의 일부만 구간에 속하는 원소들 (구간 왼쪽): $a_l, \dots, a_{xs - 1}$
2. 블록 전체가 구간에 속하는 원소들
3. 블록의 일부만 구간에 속하는 원소들 (구간 오른쪽): $a_{ys}, \dots, a_r$

이미 2번에 속하는 원소들의 합은 구해두었기 때문에 해당하는 $b_k$를 더해주기만 하면 된다.

2번에 해당하는 블록은 최대 $s$개이기 때문에 $O(s)$가 걸린다.

1번과 3번에 속하는 원소들은 최대 $2(s-1)$개이기 때문에 직접 더해주어도 $O(s)$이다.

따라서 임의의 구간에 대하여 구간 합을 구하는 쿼리를 $O(s) = O(\sqrt{n})$ 으로 처리할 수 있음을 알 수 있다.

만약 **데이터를 업데이트하는 쿼리**가 주어진다면 어떻게 할까?

블록의 구간의 합은 단순히 그 차이만큼 더해주면 되므로 $O(1)$에 처리할 수 있고,

블록의 최대/최소값은 해당 블록을 전부 탐색하면 되므로 $O(s)$에 처리할 수 있다.

쿼리의 개수를 $q$라고 하면 전체 시간복잡도는 $O(n + q \sqrt{n})$ 으로, 세그먼트 트리만큼은 아니지만 충분히 빠르다.

```cpp

```

<br/>

## References

[1] [Algorithms for Competitive Programming, 'Sqrt Decomposition'](https://cp-algorithms.com/data_structures/sqrt_decomposition.html)  
[2] 
