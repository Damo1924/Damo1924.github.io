---
title: "Segment Tree & Lazy Propagation"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` 2042 구간 합 구하기, 10999 구간 합 구하기 2, 10868 최솟값

## 1. Introduction to Segment Tree

길이가 $n$인 배열 $A$에 대해 다음 작업을 $m$번 수행해야하는 문제가 있다.

> 두 자연수 $l$, $r$($l \leq r$)이 주어졌을 때, $A\[l\] + A\[l+1\] + \dots + A\[r\]$을 계산하여 출력하기

단순히 매번 하나하나 더한다면 각 작업마다 $O(n)$, 총 $O(nm)$의 시간복잡도를 갖는다.

이 문제를 가장 효율적으로 해결하는 방법은 다음과 같다.

$S\]i\] = A\[0\] + \dots + A\[i\]$인 배열 $S$를 미리 구해두면, 각 작업을 $O(1)$에 수행할 수 있다.

배열 $S$를 구하는데 $O(n)$, $m$번의 작업을 수행하는데 $O(m)$이므로 총 $O(n + m)$의 시간복잡도로 해결할 수 있다.

그렇다면 이번에는 새로운 작업 하나를 추가해보자.

> 자연수 $i$, 정수 $v$가 주어졌을 때, $A\[i\] = v$

두 가지 작업을 합쳐서 $m$번 수행하는 문제를 배열 $S$를 구하는 방법으로 풀면, 배열 $A$의 값이 바뀔 때마다 $S$의 값들을 변경해주어야 한다.

$A\[i\]$를 $v$로 바꾸는 작업의 시간복잡도가 $O(n)$이 되어 배열 $S$를 이용한 방법마저 총 $O(nm)$의 시간복잡도를 가지게 된다.

이러한 문제를 좀 더 빠르게 해결할 수 있는 방법이 바로 **세그먼트 트리(segment tree)**이다.

<br/>

## 2. Segment Tree Implementation

세그먼트 트리를 이용하면 주어진 구간의 합을 구하는 작업을 $O(\log n)$, 수를 바꾸는 작업도 $O(\log n)$에 수행할 수 있다.

세그먼트 트리의 노드들은 다음과 같이 정의된다.

> 세그먼트 트리의 노드들은 **왼쪽 자식 노드와 오른쪽 자식 노드에 저장된 값의 합**을 저장

어떤 노드에 $A\[l\] + \dots + A\[r\]$이 저장되어 있다면, 왼쪽 자식 노드에는 $A\[l\] + \dots + A\[m\]$, 오른쪽 자식 노드에는 $A\[m + 1\] + \dots + A\[r\]$을 저장하게 된다.

이때 $m = \left\lfloor \frac{l + r}{2} \right\rfloor$이다.

세그먼트 트리도 일반적인 트리처럼 배열에 저장한다고 할 때, 다음과 같다.

- 루트 노드의 인덱스는 1
- 어떤 노드의 인덱스가 $x$일 때, 왼쪽 자식 노드의 인덱스는 $2x$, 오른쪽 자식 노드의 인덱스는 $2x + 1$

아래 그림은 세그먼트 트리의 각 노드의 인덱스와 저장하고 있는 범위를 나타낸 것이다.

<center><img src="https://user-images.githubusercontent.com/88201512/153126398-195894ad-e55c-445d-8241-6254f29da5a1.jpg" width="60%" height="60%"></center>

이제 세그먼트 트리를 C++로 구현해보자.

---

### 2-1. Build Segment Tree

세그먼트 트리를 생성하는 코드는 다음과 같다.

```cpp
int buildSegtree(vector<int>& A, vector<int>& tree, int n, int s, int e)
{
    if (s == e) return tree[n] = a[s];
    
    int m = (s + e) / 2;
    return tree[n] = buildSegtree(a, tree, 2 * n, s, m) + buildSegtree(a, tree, 2 * n + 1, m + 1, e);
}
```

- `A`: 부분합을 구해야하는 벡터
- `tree`: 세그먼트 트리를 저장할 벡터
- `n`: 현재 탐색중인 노드의 인덱스
- `s, e`: `tree[n]`에 해당하는 구간

---

### 2-2. Get Sum

앞선 코드로 구현한 트리에서 $O(\log n)$에 부분합을 구하는 함수를 구현해보자.

현재 탐색 중인 노드를 $n$, 해당하는 구간을 $s$부터 $e$, 그리고 부분합을 구하고자 하는 구간을 $l$부터 $r$이라고 하면 다음과 같이 세 가지 케이스로 나눌 수 있다.

1. $\[l, r\]$와 $\[s, e\]$가 겹치지 않는 경우
2. $\[l, r\]$가 $\[s, e\]$를 완전히 포함하는 경우
3. $\[l, r\]$와 $\[s, e\]$가 겹쳐져 있는 경우(2번 경우 제외)

첫 번째 경우는 두 구간이 전혀 겹치지 않으므로 0을 반환한다.

두 번째 경우는 현재 탐색 중인 노드에 해당하는 구간이 구하고자 하는 구간에 포함되므로 `tree[n]`을 반환한다.

마지막 경우는 왼쪽 자식 노드와 오른쪽 자식 노드에 대해 탐색을 이어간다.

```cpp
int _sum(vector<int>& tree, int n, int s, int e, int l, int r)
{
    if (e < l || r < s) return 0;
    if (l <= s && e <= r) return tree[n];
    
    int m = (s + e) / 2;
    return _sum(tree, 2 * n, s, m, l, r) + _sum(tree, 2 * n + 1, m + 1, e, l ,r);
}
```

---

### 2-3. Update Value

마지막으로 배열 $A$의 값을 업데이트하는 작업을 $O(\log n)$에 수행하는 함수를 구현해보자.

어떤 $i$에 대해 $A\[i\]$의 값을 바꾸면 $i$가 포함된 구간들의 값을 모두 바꾸어주어야 한다.

```cpp
void _update(vector<int>& tree, int n, int s, int e, int i, int diff)
{
    if (i < s || e < i) return;
    
    tree[n] += diff;
    if (s != e)
    {
        int m = (s + e) / 2;
        _update(tree, 2 * n, s, m, diff);
        _update(tree, 2 * n + 1, m + 1, e, diff);
    }
}
```

> 주의: 배열 $A$의 값을 바꾸어주어야 한다!

<br/>

## 3. Lazy Propagation

만약 어떤 하나의 수를 업데이트하는 것이 아니라 **어떤 구간에 속하는 수들을 모두 업데이트**해야한다면 어떻게 될까?

앞서 구현한 방법으로는 하나의 수를 업데이트하는데 $O(\log n)$이기 때문에 구간 업데이트를 한 번 수행하는데 $O(n \log n)$이 걸린다.

**Lazy propagation**은 구간에 속하는 수들을 하나씩 업데이트하는 것이 아닌, **구간의 대표 노드를 업데이트**해서 $O(\log n)$에 수행하는 방법이다.



<br/>

## 4. Related Problems

세그먼트 트리를 이용해서 문제를 풀어보자.

### [백준] 2042. 구간 합 구하기

[백준 2042. 구간 합 구하기 문제 링크](https://www.acmicpc.net/problem/2042)

수의 개수 $N(1 \leq N \leq 10^6)$, 수의 변경이 일어나는 횟수 $M(1 \leq M \leq 10^4)$, 구간의 합을 구하는 횟수 $K(1 \leq K \leq 10^4)$가 주어진다.

명령은 세 정수 $a, b, c$로 주어진다.

$a = 1$이면 $b$번째 수를 $c$로 바꾸라는 의미이고, $a = 2$이면 $b$번째 수부터 $c$번째 수까지의 합을 출력하면 된다.

**[SOLUTION]**

앞에서 구현한 세그먼트 트리 코드를 그대로 이용하면 된다.

```cpp
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;

ll buildSegtree(vector<ll>& A, vector<ll>& tree, int n, int s, int e)
{
    if (s == e) return tree[n] = A[s];
    
    int m = (s + e) / 2;
    return tree[n] = buildSegtree(A, tree, 2 * n, s, m) + buildSegtree(A, tree, 2 * n + 1, m + 1, e);
}

ll _sum(vector<ll>& tree, int n, int s, int e, int l, int r)
{
    if (e < l || r < s) return 0;
    if (l <= s && e <= r) return tree[n];
    
    int m = (s + e) / 2;
    return _sum(tree, 2 * n, s, m, l, r) + _sum(tree, 2 * n + 1, m + 1, e, l ,r);
}

void _update(vector<ll>& tree, int n, int s, int e, int i, ll diff)
{
    if (i < s || e < i) return;
    
    tree[n] += diff;
    if (s != e)
    {
        int m = (s + e) / 2;
        _update(tree, 2 * n, s, m, i, diff);
        _update(tree, 2 * n + 1, m + 1, e, i, diff);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, M, K; cin >> N >> M >> K;
    
    int h = (int) ceil(log2(N)); // 트리의 높이
    vector<ll> A(N + 1), tree(1 << (h + 1));
    for(int i = 1; i <= N; i++) cin >> A[i];
    buildSegtree(A, tree, 1, 1, N);
    
    for(int i = 0; i < M + K; i++)
    {
        ll a, b, c; cin >> a >> b >> c;
        if (a == 1)
        {
            _update(tree, 1, 1, N, b, c - A[b]);
            A[b] = c;
        }
        else cout << _sum(tree, 1, 1, N, b, c) << "\n";
    }
}
```

---

### [백준] 10868. 최솟값

[백준 10868. 최솟값 문제 링크](https://www.acmicpc.net/problem/10868)

수의 개수 $N(1 \leq N \leq 10^5)$과 연산의 개수 $M(1 \leq M \leq 10^5)$가 주어진다.

각 연산은 두 정수 $a, b$로 이루어져 있고, $a$번째 정수부터 $b$번째 정수까지의 정수들 중 최솟값을 출력하면 된다.

**[SOLUTION]**

부분합 대신 최솟값을 저장하는 세그먼트 트리를 구현하면 된다.

```cpp
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
typedef long long ll;
const int INF = 1000000001;

ll buildSegtree(vector<ll>& A, vector<ll>& tree, int n, int s, int e)
{
    if (s == e) return tree[n] = A[s];
    
    int m = (s + e) / 2;
    return tree[n] = min(buildSegtree(A, tree, 2 * n, s, m), buildSegtree(A, tree, 2 * n + 1, m + 1, e));
}

ll _min(vector<ll>& tree, int n, int s, int e, int l, int r)
{
    if (e < l || r < s) return INF; // 최솟값을 구하는 문제이므로, 구간이 겹치지 않으면 큰 값을 반환
    if (l <= s && e <= r) return tree[n];
    
    int m = (s + e) / 2;
    return min(_min(tree, 2 * n, s, m, l, r), _min(tree, 2 * n + 1, m + 1, e, l ,r));
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, M; cin >> N >> M;
    
    int h = (int) ceil(log2(N)); // 트리의 높이
    vector<ll> A(N + 1), tree(1 << (h + 1));
    for(int i = 1; i <= N; i++) cin >> A[i];
    buildSegtree(A, tree, 1, 1, N);
    
    for(int i = 0; i < M; i++)
    {
        int a, b; cin >> a >> b;
        cout << _min(tree, 1, 1, N, a, b) << "\n";
    }
}
```

---

### [백준] 10999. 구간 합 구하기 2

[백준 10999. 구간 합 구하기 2 문제 링크](https://www.acmicpc.net/problem/10999)

하나의 값을 업데이트하는 대신 **구간을 업데이트**한다는 점만 제외하면 2042. 구간 합 구하기 문제와 동일하다.

Lazy propagation을 적용한 segment tree를 구현하여 해결할 수 있다.

```cpp

```

<br/>

## References

[1] [BAEKJOON, '세그먼트 트리 (Segment Tree)'](https://www.acmicpc.net/blog/view/9)  
[2] [bowbowbow, 'Segment Tree and Lazy Propagation'](https://bowbowbow.tistory.com/4)  
