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

`Tags` 2042 구간 합 구하기, 10999 구간 합 구하기 2, 10868 최솟값, 12899 데이터 구조, k번째 수

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

어떤 노드에 $A\[l\] + \dots + A\[r\]$이 저장되어 있고, $m = \left\lfloor \frac{l + r}{2} \right\rfloor$이라고 하면,

왼쪽 자식 노드에는 $A\[l\] + \dots + A\[m\]$, 오른쪽 자식 노드에는 $A\[m + 1\] + \dots + A\[r\]$을 저장하게 된다.

세그먼트 트리도 일반적인 트리처럼 배열에 저장한다고 할 때, 다음과 같다.

- 루트 노드의 인덱스는 1
- 어떤 노드의 인덱스가 $x$일 때, 왼쪽 자식 노드의 인덱스는 $2x$, 오른쪽 자식 노드의 인덱스는 $2x + 1$

아래 그림은 세그먼트 트리의 각 노드의 인덱스와 저장하고 있는 범위를 나타낸 것이다.

<center><img src="https://user-images.githubusercontent.com/88201512/153126398-195894ad-e55c-445d-8241-6254f29da5a1.jpg" width="75%" height="75%"></center>

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

---

### 3-1. Algorithm

세그먼트 트리의 어떤 노드 $n$이 나타내는 구간을 $s$부터 $e$라고 하자.

$s$부터 $e$까지의 구간에 어떤 값 $d$가 더해졌다는 정보를 $lazy\[n\] = d$로 표현할 것이다.

이 정보를 처리해서 세그먼트 트리에 저장된 값을 업데이트하는 과정은 다음과 같다.

1. 노드 $n$에 저장된 값인 $tree\[n\]$에는 $(e - s + 1) \times lazy\[n\]$를 더해준다.
2. 노드 $n$이 리프 노드이면($s = e$) 더 이상 정보를 전파할 곳이 없으므로 종료.
3. 노드 $n$이 리프 노드가 아니면, 해당 노드의 왼쪽 자식 노드와 오른쪽 자식 노드에 업데이트 정보를 전파해준다.
4. 업데이트 정보가 여러 번 적용되는 것을 방지하기 위해 $lazy\[n\]$의 값을 0으로 바꾸어준다.

위 과정만 보면, 트리를 DFS로 탐색하면서 업데이트된 구간과 겹치는 모든 노드에 정보를 전파하는 것처럼 보일 것이다.

그런데 해당되는 모든 노드를 업데이트하는 것은 결국 $O(n \log n)$이라서 하나씩 업데이트하는 것과 별반 다르지 않다는 사실을 알 수 있다.

이는 **정보를 게으르게 전파함으로써** 해결할 수 있다.

이게 무슨 말이냐면, 다음을 만족하는 **구간의 대표 노드에게만 정보를 전파**해두라는 의미이다.

> 업데이트한 구간을 $l, r$($l \leq r$), 노드 $n$에 해당하는 구간을 $s, e$($s \leq e$)라고 하면 구간 대표 노드는 다음을 만족한다.
> 
> \begin{aligned}
> l \leq s, e \leq r
> \end{aligned}
> 
> 즉, 업데이트한 구간에 완전히 포함되는 노드를 뜻한다.

그렇다면 이 정보를 **언제** 자식 노드들에 전파할까?

바로 **해당 노드 또는 해당 노드의 자손 노드의 값이 필요할 때** 업데이트를 적용해주면서 전파하게 된다.

예를 들어 $n = 10$인 세그먼트 트리에서 구간 $\[2, 7\]$에 업데이트를 해주면 다음과 같다.

<center><img src="https://user-images.githubusercontent.com/88201512/153135286-107d3e91-9870-4170-b5e2-f644d7019824.jpg" width="70%" height="70%"></center>

이처럼 굳이 노드에 저장된 값을 업데이트할 필요가 없으면, 구간의 대표 노드들에만 업데이트 정보를 저장해두는 것이다.

여기서 만약 구간 $\[3, 5\]$의 부분합을 구하는 명령이 주어지면 아래와 같은 순서로 전파된다.

<center><img src="https://user-images.githubusercontent.com/88201512/153135748-15036f48-12f4-4a26-b56e-99635a34bc0f.jpg" width="80%" height="80%"></center>

지금도 필요한 노드의 값만 업데이트해주는 것을 알 수 있다.

---

### 3-2. Implementation

이제 lazy propagation을 적용한 세그먼트 트리를 구현해보자.

먼저, 노드 $n$에 업데이트 정보 $lazy\[n\]$을 적용하고 자식 노드들로 전파하는 함수를 구현하였다.

```cpp
void lazyPropagation(vector<ll>& tree, vector<ll>& lazy, int n, int s, int e)
{
    tree[n] += (e - s + 1) * lazy[n]; // 구간의 길이만큼 곱해서 더해준다.
    if (s != e) // 리프 노드가 아니라면, 자식 노드로 정보를 전파
    {
        lazy[2 * n] += lazy[n];
        lazy[2 * n + 1] += lazy[n];
    }
    lazy[n] = 0; // 업데이트를 처리한 노드는 lazy[n]을 0으로 바꾸어준다.
}
```

이제 이 함수를 구간 업데이트 함수 `_updateRange()`와 부분합을 구하는 함수 `_sum()`에 적용시켜준다.

```cpp
ll _sum(vector<ll>& tree, vector<ll>& lazy, int n, int s, int e, int l, int r)
{
    if (lazy[n] != 0) lazyPropagation(tree, lazy, n, s, e); // 업데이트 정보가 남아있으면 처리해준다.
    
    if (e < l || r < s) return 0;
    if (l <= s && e <= r) return tree[n];
    
    int m = (s + e) / 2;
    return _sum(tree, lazy, 2 * n, s, m, l, r) + _sum(tree, lazy, 2 * n + 1, m + 1, e, l ,r);
}

void _updateRange(vector<ll>& tree, vector<ll>& lazy, int n, int s, int e, int l, int r, ll diff)
{
    if (lazy[n] != 0) lazyPropagation(tree, lazy, n, s, e); // 업데이트 정보가 남아있으면 처리해준다.
    
    if (r < s || e < l) return;
    
    if (l <= s && e <= r) // 구간 대표 노드까지만 정보를 전파하고 종료!
    {
        lazy[n] = diff;
        lazyPropagation(tree, lazy, n, s, e);
        return;
    }
    
    int m = (s + e) / 2; // 구간 대표 노드가 아니라면, 자식 노드들에게 전파
    _updateRange(tree, lazy, 2 * n, s, m, l, r, diff);
    _updateRange(tree, lazy, 2 * n + 1, m + 1, e, l, r, diff);
    
    tree[n] = tree[2 * n] + tree[2 * n + 1]; // 자식 노드의 정보를 부모 노드에 적용
}
```

마지막 `tree[n] = tree[2 * n] + tree[2 * n + 1];`가 필요한 이유는 **자손 노드에 저장된 업데이트 정보를 조상 노드가 필요로 하는 상황**이 나올 수 있기 때문이다.

예를 들어 구간 $\[3, 4\]$에 업데이트가 발생한 뒤 구간 $\[1, 5\]$의 부분합을 구해야한다면, $\[3, 4\]$에 해당하는 노드에 적용된 업데이트를 조상 노드들에게도 적용시켜야한다.

---

### 3-3. Aplications

위의 코드는 구간에 속하는 원소들에 $k$만큼 더해두고, 구간에 속하는 원소들의 합을 구하는 쿼리를 처리하는 세그먼트 트리이다.

하지만 **구간 업데이트에 사용하는 연산**과 **구간 쿼리를 구할 때 사용하는 연산**이 다를 수 있다.

위 두 가지 연산을 주어진 문제에 맞게 적절히 바꾸어서 구현하는 것이 중요하다.

<br/>

## 4. Related Problems

세그먼트 트리를 이용해서 문제를 풀어보자.

### [BOJ] 2042. 구간 합 구하기

[BOJ 2042. 구간 합 구하기 문제 링크](https://www.acmicpc.net/problem/2042)

수의 개수 $N(1 \leq N \leq 10^6)$, 수의 변경이 일어나는 횟수 $M(1 \leq M \leq 10^4)$, 구간의 합을 구하는 횟수 $K(1 \leq K \leq 10^4)$가 주어진다.

명령은 세 정수 $a, b, c$로 주어진다.

$a = 1$이면 $b$번째 수를 $c$로 바꾸라는 의미이고, $a = 2$이면 $b$번째 수부터 $c$번째 수까지의 합을 출력하면 된다.

**[SOLUTION]**

앞에서 구현한 세그먼트 트리 코드를 그대로 이용하면 된다.

<details>
<summary> 전체 코드 </summary>
<div markdown="1">
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
</div>
</details>

---

### [BOJ] 10868. 최솟값

[BOJ 10868. 최솟값 문제 링크](https://www.acmicpc.net/problem/10868)

수의 개수 $N(1 \leq N \leq 10^5)$과 연산의 개수 $M(1 \leq M \leq 10^5)$가 주어진다.

각 연산은 두 정수 $a, b$로 이루어져 있고, $a$번째 정수부터 $b$번째 정수까지의 정수들 중 최솟값을 출력하면 된다.

**[SOLUTION]**

부분합 대신 최솟값을 저장하는 세그먼트 트리를 구현하면 된다.

<details>
<summary> 전체 코드 </summary>
<div markdown="1">
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
</div>
</details>

---

### [BOJ] 10999. 구간 합 구하기 2

[BOJ 10999. 구간 합 구하기 2 문제 링크](https://www.acmicpc.net/problem/10999)

하나의 값을 업데이트하는 대신 **구간을 업데이트**한다는 점만 제외하면 2042. 구간 합 구하기 문제와 동일하다.

**[SOLUTION]**

Lazy propagation을 적용한 segment tree를 구현하여 해결할 수 있다.

<details>
<summary> 전체 코드 </summary>
<div markdown="1">
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

void lazyPropagation(vector<ll>& tree, vector<ll>& lazy, int n, int s, int e)
{
    tree[n] += (e - s + 1) * lazy[n];
    if (s != e)
    {
        lazy[2 * n] += lazy[n];
        lazy[2 * n + 1] += lazy[n];
    }
    lazy[n] = 0;
}

ll _sum(vector<ll>& tree, vector<ll>& lazy, int n, int s, int e, int l, int r)
{
    if (lazy[n] != 0) lazyPropagation(tree, lazy, n, s, e);
    
    if (e < l || r < s) return 0;
    if (l <= s && e <= r) return tree[n];
    
    int m = (s + e) / 2;
    return _sum(tree, lazy, 2 * n, s, m, l, r) + _sum(tree, lazy, 2 * n + 1, m + 1, e, l ,r);
}

void _updateRange(vector<ll>& tree, vector<ll>& lazy, int n, int s, int e, int l, int r, ll diff)
{
    if (lazy[n] != 0) lazyPropagation(tree, lazy, n, s, e);
    
    if (r < s || e < l) return;
    
    if (l <= s && e <= r)
    {
        lazy[n] = diff;
        lazyPropagation(tree, lazy, n, s, e);
        return;
    }
    
    int m = (s + e) / 2;
    _updateRange(tree, lazy, 2 * n, s, m, l, r, diff);
    _updateRange(tree, lazy, 2 * n + 1, m + 1, e, l, r, diff);
    
    tree[n] = tree[2 * n] + tree[2 * n + 1];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, M, K; cin >> N >> M >> K;
    
    vector<ll> A(N + 1);
    for(int i = 1; i <= N; i++) cin >> A[i];
    
    int h = (int) ceil(log2(N));
    vector<ll> tree(1 << (h + 1)), lazy(1 << (h + 1));
    buildSegtree(A, tree, 1, 1, N);
    
    for(int i = 0; i < M + K; i++)
    {
        ll a, b, c, d; cin >> a >> b >> c;
        if (a == 1)
        {
            cin >> d;
            _updateRange(tree, lazy, 1, 1, N, b, c, d);
        }
        else cout << _sum(tree, lazy, 1, 1, N, b, c) << "\n";
    }
}
```
</div>
</details>

---

### [BOJ] 12899. 데이터 구조

[BOJ 12899. 데이터 구조 문제 링크](https://www.acmicpc.net/problem/12899)

자연수를 저장하는 데이터 구조 $S$에 대해 다음 쿼리를 처리하는 문제이다.

- $1$ $X$: $S$에 자연수 $X$를 추가한다.
- $2$ $X$: $S$에서 $X$번째로 작은 수를 출력하고 해당 수를 $S$에서 삭제한다.

**[SOLUTION]**

세그먼트 트리를 이용하면 $K$번째 수를 $O(\log n)$에 찾을 수 있다.

이때 세그먼트 트리의 각 노드에는 해당 노드의 구간에 속하는 $S$에 저장된 수들의 개수를 저장한다.

<details>
<summary> 전체 코드 </summary>
<div markdown="1">

```cpp
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
const int maxN = 2000000;

void insert(vector<int>& tree, int n, int s, int e, int x) // x를 추가하는 함수
{
    if (e < x || x < s) return;
    
    tree[n]++; // x를 포함하는 노드에 1씩 더해준다.
    if (s == e) return;
    
    int m = (s + e) / 2;
    insert(tree, 2 * n, s, m, x);
    insert(tree, 2 * n + 1, m + 1, e, x);
}

int kth_min(vector<int>& tree, int n, int s, int e, int k) // k번째로 작은 수를 반환하고 삭제
{
    tree[n]--; // $k$번째로 작은 수가 포함된 노드에 1씩 빼준다.
    if (s == e) return s;
    
    int mid = (s + e) / 2;
    if (tree[2 * n] < k) return kth_min(tree, 2 * n + 1, mid + 1, e, k - tree[2 * n]);
    return kth_min(tree, 2 * n, s, mid, k);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N; cin >> N;
    int h = (int) ceil(log2(maxN));
    vector<int> tree(1 << (h + 1), 0);
    for (int i = 0; i < N; i++)
    {
        int T, X; cin >> T >> X;
        if (T == 1) insert(tree, 1, 1, maxN, X);
        else cout << kth_min(tree, 1, 1, maxN, X) << "\n";
    }
}
```
</div>
</details>

---

### [BOJ] 1395. 스위치

[BOJ 1395. 스위치 문제 링크](https://www.acmicpc.net/problem/1395)

$N$개의 스위치에 대하여, 구간에 속하는 스위치들을 반전시키는 쿼리와 구간에 속하는 스위치들 중 켜져 있는 것의 개수를 구하는 쿼리가 주어지는 문제이다.

구간에 속하는 스위치들 중 켜져 있는 것의 개수를 구해야하므로, 각 스위치의 상태를 저장하고, 구간 합을 구하는 쿼리를 처리할 수 있어야한다.

그렇다면 스위치를 반전시키는 것은 어떻게 구현해야할까?

세그먼트 트리의 어떤 노드에 해당하는 구간의 길이를 $l$, 해당하는 구간에 있는 켜진 스위치의 개수를 $x$라고 하면,

반전시키면 켜진 스위치의 개수는 $l - x$ 가 된다는 것을 쉽게 알 수 있다.

또한, 스위치를 두 번 반전시키면 원래 상태로 돌아온다는 점을 이용하면 업데이트 정보 $lazy$에 반전시키는 작업이 홀수 번 들어왔으면 $1$, 짝수 번 들어왔으면 $0$을 저장해도 충분함을 알 수 있다.

따라서 `lazyPropagation()` 함수를 아래와 같이 바꿀 수 있다.

```cpp
void lazyPropagation(vector<int>& tree, vector<bool>& lazy, int n, int s, int e)
{
    tree[n] = (e - s + 1) - tree[n];
    if (s != e)
    {
        lazy[2 * n] ^= 1;
        lazy[2 * n + 1] ^= 1;
    }
    lazy[n] = 0;
}
```

<br/>

## References

[1] [BAEKJOON, '세그먼트 트리 (Segment Tree)'](https://www.acmicpc.net/blog/view/9)  
[2] [bowbowbow, 'Segment Tree and Lazy Propagation'](https://bowbowbow.tistory.com/4)  
