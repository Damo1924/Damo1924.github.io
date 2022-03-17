---
title: "Sparse Table"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` Range Minimum Queries, RMQ

## 1. Sparse Table

Sparse table은 range queries, 특히 **range minimum queries를 처리하는데 있어 강점을 가진 자료구조**이다.

- Range Queries: $O(\log n)$
- Range Minimum Queries: $O(1)$

단, 주어진 수열에 대한 전처리를 통해 얻은 정보를 이용하기 때문에 **수열이 변하는 경우에는 사용할 수 없다.**

---

### 1-1. Intuition

모든 음이 아닌 정수는 $2$의 거듭제곱으로 표현이 가능하다는 사실을 이용하면, 주어진 구간을 $2$의 거듭제곱 길이의 구간들로 나눌 수 있다는 것을 알 수 있다.

예를 들어 구간 $\[4, 14\]$은 길이가 $11 = 2^3 + 2^1 + 2^0$이므로 $\[4, 11\]$, $\[12, 13\]$, $\[14, 14\]$로 나눌 수 있다.

따라서 수열의 각 원소에 대해 **해당 원소로 시작하는 길이가 $2^i$($0 \leq i \leq \lfloor \log n \rfloor$)$인 부분 수열**의 쿼리 결과값을 미리 구해둔다면, 임의의 구간에 대해 $O(\log n)$로 쿼리를 처리할 수 있다.

---

### 1-2. Preprocessing

다음의 배열을 정의하자.

> `st[i][j]` : 구간 $\[i, i + 2^j - 1\]$의 쿼리 결과값

구간 $\[i, i + 2^j - 1\]$는 $\[i, i + 2^{j-1} - 1\] \cup \[i + 2^{j-1}, i + 2^j - 1\]$이므로 다음과 같이 $st$ 배열을 채울 수 있다.

```cpp
for (int i = 0; i < N; i++) st[i][0] = a[i];
for (int j = 1; j <= M; j++)
    for (int i = 0; i + (1 << j) <= N; i++)
        st[i][j] = f(st[i][j-1], st[i + (1 << (j - 1))][j - 1]);
```

이때 $a$는 길이가 $N$인 주어진 수열이고, 함수 $f(x, y)$는 쿼리의 종류에 따라 결정되는 함수이다.

$M$은 $2^M \leq N$을 만족하는 가장 큰 정수로, $M = \lfloor \log n \rfloor$이다.

$N \times M$ 크기의 배열을 채우는 과정이므로 전처리는 $O(N \log N)$의 시간복잡도를 갖는다.

---

### 1-3. Query

이제 쿼리를 처리하는 함수를 구현해보자.

구간 $\[l, r\]$에 대한 쿼리를 처리하는 방법은 다음과 같다.

- $2^j \leq r - l + 1$을 만족하는 정수 중 가장 큰 $j$를 구한다.
- 전체 결과값 $res$를 $f(res, st\[l\]\[j\]$)로 갱신한다.
- $l$을 $l + 2^j$로 갱신하고 맨 처음으로 돌아간다.

위 과정을 $l \leq r$일 동안 반복해주면 된다.

```cpp
int query(int l, int r)
{
    int res = 0;
    for (int j = M; j >= 0; j--)
    {
        if ((1 << j) <= r - l + 1)
        {
            res = f(res, st[l][j]);
            l += (1 << j);
        }
    }
}
```

<br/>

## 2. Range Minimum Queries (RMQ)

RMQ는 말 그대로 주어진 구간의 최솟값을 구하는 쿼리를 의미한다.

그렇다면 왜 많은 쿼리들 중 최솟값을 구하는 쿼리만 $O(1)$에 처리할 수 있을까?

그 이유는 최솟값의 경우, **같은 수를 여러 번 처리해도 결과에 영향이 없기 때문**이다.

> 이와 같은 성질을 [idempotence](https://en.m.wikipedia.org/wiki/Idempotence)라고 부른다.

구간 $\[l, r\]$의 최솟값은 다음과 같이 구할 수 있다.

\begin{aligned}
min(st\[l\]\[j\], st\[r - (1 << j) + 1\]\[j\])
\end{aligned}

이때 $j = \lfloor \log (r - l + 1) \rfloor$이다.

$j$값만 빠르게 구할 수 있다면 $O(1)$로 쿼리를 처리할 수 있는 것이다.

$j$값은 $O(1)$에 구하기 위해 $1$부터 $N$까지의 정수 $i$에 대해 $lfloor \log i \rfloor$을 미리 구해둘 것이다.

```cpp
int log[N + 1];
log[1] = 0;
for (int i = 1; i <= N; i++)
    log[i] = log[i / 2] + 1;
```

전처리 과정에 위 코드를 추가하고 나면, 구간 $\[l, r\]$의 최솟값을 다음과 같이 구할 수 있다.

```cpp
int j = log[r - l + 1];
cout << mn = query(st[l][j], st[r - (1 << j) + 1][j]);
```

<br/>

## References

[1] [Algorithms for Competitive Programming, 'Sparse Table'](https://cp-algorithms.com/data_structures/sparse-table.html)
