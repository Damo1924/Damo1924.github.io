---
title: "덱(Deque)을 이용해서 구간의 최대/최소값 구하기"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:    
  - Algorithm
use_math: true
comments: true

---

`Tags` 다이나믹 프로그래밍, DP, 11003

## 1. Problem Setting

길이가 $n$인 수열 $a_1, a_2, \dots, a_n$ 와 $1 \leq d \leq n$ 인 정수 $d$에 대하여,

\begin{aligned}
m_i = \min_{i - d + 1 \leq j \leq i} a_j
\end{aligned}

라고 정의하자.

$i \leq 0$ 인 $a_i$ 는 무시할 때, $m_1, m_2, \dots, m_n$ 의 값을 모두 구해야한다.

</br>

## 2. Usable Methods: Segment tree, Priority queue

**구간의 최소/최대값**을 구하는 위 문제를 $O(n \log n)$에 처리할 수 있는 방법은 크게 두 가지이다.

1. **세그먼트 트리(segment tree)**
2. **우선순위 큐(priority queue)**

각 방법에 대하여 간단히 설명하면,

1. 각 노드가 해당하는 구간의 최소/최대값을 저장하는 세그먼트 트리를 구현한다.
2. 수열을 선형탐색하면서 우선순위 큐에 최소/최대값일 가능성이 있는 후보들을 저장해둔다.

정도로 정리할 수 있다.

물론 세그먼트 트리 방식은 임의의 구간 쿼리도 $O(\log n)$에 처리할 수 있다는 점에서 뛰어나지만, 그만큼 메모리를 차지하고 트리를 구현하는데도 시간이 소요된다.

반만 우선순위 큐 방식은 제한적인 구간에 대한 쿼리만 처리할 수 있다는 단점이 있지만, 굉장히 깔끔하고 짧은 코드로 해결이 가능하다.

```cpp
priority_queue<pair<int, int>> pq;
for (int i = 1; i <= n; i++) {
    while (pq.top().second <= i - d) pq.pop();
    pq.push({ a[i], i });
    m[i] = pq.top().first;
}
```

위 코드는 수열 $a$에서 길이가 $d$인 구간들의 최댓값을 구하는 코드이다.

그런데 사실 이 문제는 $O(n)$으로 해결할 수 있다.

<br/>

## 3. $O(n)$ solution using Deque

덱(deque)은 양쪽 끝에서 삽입과 삭제가 가능한 시퀀스 자료구조이다.

앞서 우선순위 큐 방식과 비슷하게 덱에 **최소값일 가능성이 있는 후보들을 저장**해두는데, 그 방법은 다음과 같다.

1. 덱의 앞부분에서 $j \leq i - d$ 인 $a_j$들을 모두 삭제
2. 덱의 뒷부분에서 $a_j > a_i$ 인 $a_j$들을 모두 삭제 (최대값이면 $a_j < a_i$)

한 후에 덱의 뒷부분에 $a_i$를 삽입해준다.

그렇다면 $a_{i-d+1}$부터 $a_i$까지의 값들 중 최소값인 $m_i$는 **덱의 가장 앞에 있는 원소**이다.

1번 작업은 **덱 안에 범위에 해당하는 수열의 원소들만을 남기기 위함**이고,

2번 작업은 **$a_i$ 앞에 있는 원소들 중 $a_i$보다 큰 원소는 앞으로 절대 최소값이 될 수 없으므로 제거**하는데, 그 결과 **덱 안의 원소들은 오름차순으로 정렬**된다.

따라서 덱의 맨 앞에 있는 원소가 현재 범위의 최솟값이 되는 것이다.

수열 $a_i$가 주어졌을 때, $m_i$를 구하는 코드는 다음과 같다.

```cpp
deque<pair<int, int>> dq;
for (int i = 1; i <= n; i++) {
    while (!dq.empty() && dq.front().second <= i - d) dq.pop_front();
    while (!dq.empty() && dq.back().first > a[i]) dq.pop_back();
    dq.push_back({ a[i], i });
    m[i] = dq.front().first;
}
```

<br/>

## 4. Optimization of Dynamic Programming using Deque

이 방법이 단순히 앞선 문제를 풀기 위한 테크닉이었으면 따로 정리하지 않았을 것이다.

이를 잘 이용하면 **동적계획법 문제**들을 빠르게 해결할 수 있게 된다.

수열 $a_i$와 적절히 정의된 $dp_i$에 대하여 점화식이 다음과 같은 경우를 생각해보자.

\begin{aligned}
dp_i = a_i + \min_{s_i \leq j \leq e_i} b_j
\end{aligned}

이때 $b$는 $dp$ 와 $a$ 로 표현되는 값이고, 어떤 정수 $1 \leq d \leq n$에 대하여 $e_i - s_i = d$ 로 고정된다.

- 브루트포스로 구하면 $O(dn)$,
- 세그먼트 트리나 우선순위 큐로 구하면 $O(n \log n)$,
- 덱으로 구하면 $O(n)$

이므로 덱을 이용하는 것이 가장 바람직하다.

<br/>

## 5. Related Problems

덱을 이용해서 풀 수 있는 동적 계획법 문제들이다.

> 더 많은 문제를 풀고 싶다면 [덱을 이용한 다이나믹 프로그래밍](https://www.acmicpc.net/problemset?sort=ac_desc&algo=108) 파트를 참고.

---

### [BOJ] 11003. 최솟값 찾기

[BOJ 11003. 최솟값 찾기 문제 링크](https://www.acmicpc.net/problem/11003)

$n$의 범위가 $1 \leq n \leq 5 \cdot 10^6$ 인 1절에서 정의된 문제이다.

---

### [BOJ] 15678. 연세워터파크

[BOJ 15678. 연세워터파크 문제 링크](https://www.acmicpc.net/problem/15678)

$N$개의 징검다리들이 있고, 각 징검다리를 밟으면 점수를 준다. (단, 점수가 음수일 수 있다.)

한 번 밟은 징검다리는 다시 밟을 수 없고, 징검다리에는 번호가 붙여져 있어서 번호의 차이가 $d$ 이하인 징검다리로만 점프할 수 있다.

이때 얻을 수 있는 최대 점수를 구하는 문제이다.

> 징검다리를 밟는 순서는 상관이 없다는 사실을 이용해서 $dp_i$를 다음과 같이 정의하자.
> 
> - $dp_i$ : $i$보다 작거나 같은 번호의 징검다리들을 지나 $i$번 징검다리를 밟고 끝냈을 때 얻을 수 있는 점수의 최댓값
> 
> $i$번 징검다리를 밟았을 때 얻는 점수를 $k_i$라고 할 때, 점화식은 다음과 같이 구해진다.
> 
> \begin{aligned}
> dp_i = k_i + \max \left( \max_{i-d \leq j \leq i - 1} dp_j , 0 \right)
> 
> 점수가 음수일 수 있으므로, $i$번 징검다리만 밟고 끝내는 경우도 고려해야한다.

---

### [BOJ] 5977. Mowing the Lawn

[BOJ 5977. Mowing the Lawn 문제 링크](https://www.acmicpc.net/problem/5977)





