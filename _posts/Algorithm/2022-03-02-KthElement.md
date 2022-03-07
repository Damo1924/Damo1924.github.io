---
title: "k번째 원소 구하기"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` kth element, Segment tree, BIT, Merge sort tree, Persistent segment tree, 2D segment tree, Binary search

## $k$th Element Problems

이번 포스팅에서는 $k$번째 원소를 구하는 다양한 문제들에 대해 다루어 볼 것이다.

자주 만날 수 있는 $k$번째 원소 문제는 크게 세 가지로 나눌 수 있다.

- **[PROBLEM 1]** 집합의 $k$번째 원소 구하기
- **[PROBLEM 2]** 원소의 삽입/삭제가 일어나는 집합의 $k$번째 원소를 구하기
- **[PROBLEM 3]** 임의의 집합의 $k$번째 원소 구하기

각 문제들을 어떤 알고리즘을 이용해서 해결할 수 있는지 정리해보았다.

<br/>

## [PROBLEM 1] 집합의 $k$번째 원소 구하기

> [백준 11004. K번째 수](https://www.acmicpc.net/problem/11004)
> 
> 길이가 $n$인 수열 $a_1, a_2, \dots, a_n$이 주어진다.
> 
> 수열 $a$를 오름차순으로 정렬했을 때, 앞에서부터 $k$번째에 있는 수를 구하여라.

---

### [SOLUTION] Sorting

주어진 수열을 오름차순으로 정렬한 후에 $k$번째 원소를 출력하면 된다.

**Time complexity**: $O(n \log n)$

<details>
<summary> [백준] 11004. K번째 수 </summary>
<div markdown="1">

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, k; cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end());
    cout << a[k - 1];
}
```

</div>
</details>

<br/>

## [PROBLEM 2] 원소의 삽입/삭제가 일어나는 집합의 $k$번째 원소 구하기

이러한 문제들은 다양한 형태로 주어질 수 있다.

가장 직관적인 형태로는 아래와 같은 문제가 있다.

> [백준 12899. 데이터 구조](https://www.acmicpc.net/problem/12899)
> 
> 자연수들의 부분집합 $S$에 대해 다음 쿼리들이 주어진다.
> 
> - $S$에 자연수 $X$를 추가
> - $S$에서 $k$번째로 작은 수를 출력하고 해당 수를 $S$에서 삭제

다음 문제도 같은 종류의 문제이다.

> [백준 1572. 중앙값](https://www.acmicpc.net/problem/1572)
> 
> 길이가 $n$인 수열 $a_1, a_2, \dots, a_n$이 주어진다.
> 
> 정수 $m, k$($1 \leq m \leq n$, $1 \leq k \leq m$)가 주어질 때, 다음을 구하여라.
> 
> - 길이가 $m$인 모든 연속부분수열의 $k$번째 원소들의 합

길이가 $n$인 수열의 중앙값은 수열을 정렬하였을 때 $\frac{N+1}{2}$번째 원소라는 점을 이용한다.

길이가 일정한 연속부분수열의 다음 연속부분수열은 다음 수를 추가하고, 첫 번째 수를 제거하여 얻을 수 있다.

이러한 문제들을 Segment tree 또는 Fenwick tree(BIT)를 이용해서 풀 수 있다.

> 만약 주어지는 수의 범위가 $10^5$보다 크다면, **좌표 압축 기법**을 사용해준다.

---

### [SOLUTION 1] Fenwick Tree(BIT) + Binary Search

구간합을 구하는 세그먼트 트리나 펜윅 트리와 함께 이분 탐색을 이용하는 방법이다.

트리가 나타내는 구간의 길이를 $n$이라 하면,

집합의 원소들 중 어떤 수 $x$보다 작은 원소의 개수를 구하는데 $O(\log n)$,

$x$보다 작은 원소의 개수는 $x$에 대한 증가함수이므로 이분탐색으로 $k$번째 원소를 찾는데 $O(\log n)$이다.

따라서 전체 시간복잡도는 다음과 같다.

**Time complexity**: $O(q_1 \cdot \log n + q_2 \cdot \log^2 n)$

이때 $q_1$은 집합에 원소를 삽입/삭제하는 쿼리의 개수, $q_2$는 집합의 $k$번째 원소를 구하는 쿼리의 개수이다.

다만, $k$번째 원소를 구하는 쿼리를 처리하는데 $O(\log^2 n)$이라서 앞으로 소개할 두 가지 방법을 사용하는 것이 더 좋다.

<details>
<summary> [백준] 12899. 데이터 구조 SOLUTION </summary>
<div markdown="1">

```cpp
#include<iostream>
#include<vector>
#include<math.h>
using namespace std;
typedef long long ll;

void _update(vector<int>& tree, int N, int n, int diff)
{
    while (n < N)
    {
        tree[n] += diff;
        n += (n & -n);
    }
}

int _sum(vector<int>& tree, int x)
{
    int res = 0;
    while (x)
    {
        res += tree[x];
        x &= x - 1;
    }
    return res;
}

int kth_min(vector<int>& tree, int k)
{
    int s = 1, e = 2000000;
    while (s < e)
    {
        int m = (s + e) / 2;
        if (_sum(tree, m) < k) s = m + 1;
        else e = m;
    }
    return s;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int Q; cin >> Q;
    vector<int> tree(2000001);
    while (Q--)
    {
        int t, x; cin >> t >> x;
        if (t == 1) _update(tree, 2000001, x, 1);
        else
        {
            int ans = kth_min(tree, x);
            cout << ans << "\n";
            _update(tree, 2000001, ans, -1);
        }
    }
}
```

</div>
</details>

---

### [SOLUTION 2] Segment Tree

이번에는 이분 탐색 없이 세그먼트 트리만 이용해서 $k$번째 수를 구하는 방법에 대해 알아보자.

앞선 방법에서도 사용한 구간합 세그먼트 트리를 그대로 사용하면 된다.

다만, 구간합 함수 대신 **해당 노드에서 $k$번째 수를 구하는 함수**를 구현해야한다.

어떤 노드에서 $k$번째 수를 구하기 위해서는 **왼쪽 자식 노드에 있는 원소의 개수를 $k$와 비교**해서 어느 자식 노드를 탐색할지 정해야한다.

이때 오른쪽 자식 노드로 가는 경우에는 $k$에서 왼쪽 자식 노드의 개수를 빼준다.

```cpp
int kth_min(vector<int>& tree, int n, int s, int e, int k)
{
    if (s == e) return s;
    
    int m = (s + e) / 2;
    if (k <= tree[2 * n]) return kth_min(tree, 2 * n, s, m, k);
    return kth_min(tree, 2 * n + 1, mid + 1, e, k - tree[2 * n]);
}
```

이 함수를 이용하면 $k$번째 수를 구하는 쿼리를 $O(\log n)$에 처리할 수 있다.

**Time Complexity**: $O(q \log n)$

이때 $q$는 쿼리(= 원소 추가/삭제, $k$번째 수 구하기)의 개수를 의미한다.

<details>
<summary> [백준] 12899. 데이터 구조 SOLUTION </summary>
<div markdown="1">
```cpp
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;
const int maxN = 2000000;

void insert(vector<int>& tree, int n, int s, int e, int x)
{
    if (e < x || x < s) return;
    
    tree[n]++;
    if (s == e) return;
    
    int m = (s + e) / 2;
    insert(tree, 2 * n, s, m, x);
    insert(tree, 2 * n + 1, m + 1, e, x);
}

int kth_min(vector<int>& tree, int n, int s, int e, int k)
{
    tree[n]--; // $k$번째 원소를 구함과 동시에 삭제
    if (s == e) return s;
    
    int m = (s + e) / 2;
    if (k <= tree[2 * n]) return kth_min(tree, 2 * n, s, m, k);
    return kth_min(tree, 2 * n + 1, mid + 1, e, k - tree[2 * n]);
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

### [SOLUTION 3] Fenwick Tree(BIT)

앞서 구간합을 구하는 세그먼트 트리를 이용해서 $k$번째 원소를 구할 수 있었기 때문에 BIT로도 구할 수 있다.

BIT는 세그먼트 트리보다 빠르면서 메모리도 적게 사용하기 때문에 주로 BIT를 이용해서 푼다.

물론 시간복잡도는 세그먼트 트리와 동일하게 쿼리당 $O(\log n)$이다.

아래는 $k$번째 원소를 반환하는 함수이다.

```cpp
int kth_min(vector<int>& tree, int N, int h, int k) // N: 전체 구간의 길이, h: 트리의 높이
{
    int res = 0;
    for (int i = h; i >= 0; i--)
    {
        int tmp = res + (1 << i);
        if (tmp < N && tree[tmp] < k)
        {
            k -= tree[tmp];
            res = tmp;
        }
    }
    if (!k) return res;
    return res + 1;
}
```

위 코드에서 `tmp`를 세그먼트 트리의 `m = (s + e) / 2`라고 생각하면 이해가 쉬울 것이다.

세그먼트 트리에서 $\[1, N\]$부터 시작해 점점 범위를 좁혀나가는 것을 펜윅 트리로 구현한 것 뿐이다.

<details>
<summary> [백준] 12899. 데이터구조 SOLUTION </summary>
<div markdown="1">
```cpp
#include<iostream>
#include<vector>
#include<math.h>
using namespace std;

void _update(vector<int>& tree, int N, int n, int diff)
{
    while (n < N)
    {
        tree[n] += diff;
        n += (n & -n);
    }
}

int kth_min(vector<int>& tree, int N, int h, int k)
{
    int res = 0;
    for (int i = h; i >= 0; i--)
    {
        int tmp = res + (1 << i);
        if (tmp < N && tree[tmp] < k)
        {
            k -= tree[tmp];
            res = tmp;
        }
    }
    if (!k) return res;
    return res + 1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N = 2000001, h = (int) floor(log2(N));
    vector<int> tree(2000001, 0);
    
    int Q; cin >> Q;
    while (Q--)
    {
        int T, X; cin >> T >> X;
        if (T == 1) _update(tree, N, X, 1);
        else
        {
            int ans = kth_min(tree, N, h, X);
            cout << ans << "\n";
            _update(tree, N, ans, -1);
        }
    }
}
```
</div>
</details>

<br/>

## [PROBLEM 3] 임의의 집합의 $k$번째 원소 구하기

집합의 원소를 삽입/삭제하는 과정이 너무 많이 일어나면 위에서 소개한 방법으로는 해결할 수 없다.

문제는 다음과 같이 주어진다.

> [백준 7469. K번째 수](https://www.acmicpc.net/problem/7469)
> 
> 길이가 $n$인 수열에서, 임의의 구간 $\[l, r\]$($1 \leq l \leq r \leq n$)의 $k$($1 \leq k \leq r - l + 1$)번째 원소를 구하여라.

이 경우에는 Merge sort tree를 이용하거나 Persistent segment tree / 2D Segment tree를 이용해야한다.

---

### [SOLUTION 1] Merge Sort Tree + Binary Search

Merge sort tree는 노드에 해당 구간의 부분수열이 정렬된 상태로 저장되어 있다.

임의의 구간이 주어졌을 때 해당 구간에 포함되는 노드의 개수는 $O(\log n)$,

각 노드들에서 어떤 수 $x$보다 작거나 같은 수의 개수를 이분 탐색으로 구하는데 $O(\log n)$이다.

따라서 $O(\log^2 n)$으로 주어진 구간에 있는 $x$보다 작거나 같은 수의 개수를 구할 수 있다.

```cpp
int cnt(vector<vector<int>>& tree, int n, int s, int e, int l, int r, int x)
{
    if (e < l || r < s) return 0;
    if (l <= s && e <= r) return upper_bound(tree[n].begin(), tree[n].end(), x) - tree[n].begin();
    
    int d = tree[2 * n].size();
    return cnt(tree, 2 * n, s, s + d - 1, l, r, x) + cnt(tree, 2 * n + 1, s + d, e, l, r, x);
}
```

$x$보다 작거나 같은 수의 개수는 $x$에 대한 증가함수이므로 이분 탐색을 이용해서 $k$번째 수를 찾을 수 있다.

```cpp
int kth_min(vector<vector<int>>& tree, int N, int l, int r, int k)
{
    int s = -1e9, e = 1e9;
    while (s <= e)
    {
        int m = (s + e) / 2;
        if (cnt(tree, 1, 1, N, l, r, m) < k) s = m + 1;
        else e = m - 1;
    }
    return s;
}
```

> 위 이분 탐색 코드에서 `while (s < e)`, `else e = m`이라 하면, 중간에 어떤 $m$에 대해 해당 구간에 $m$이 여러 개 있다면 무한루프가 발생한다.
> 
> 이를 방지하기 위해 `e = m - 1`로 갱신하도록 구현하였다.

Merge sort tree를 만드는데 $O(n \log n)$, 각 쿼리마다 $O(\log^3 n)$이므로 전체 시간복잡도는 다음과 같다.

**Time complexity**: $O(n \log n + q \log^3 n)$

이 방법은 트리의 각 노드가 수들을 모두 저장하고 있기 때문에 주어지는 수의 범위에 관계없이 좌표 압축을 하지 않아도 된다는 장점이 있다.

<details>
<summary>[백준] 7469. K번째 수 SOLUTION</summary>
<div markdown="1">

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

void buildMergeSortTree(vector<vector<int>>& tree, vector<int>& a)
{
    int n = a.size() - 1;
    int h = ceil(log2(n));
    tree.resize(1 << (1 + h));
    
    int idx = 1 << h;
    for (int i = 1; i <= n; i++) tree[i - 1 + idx].push_back(a[i]);
    
    for (int i = idx - 1; i >= 1; i--) {
        tree[i].resize(tree[2 * i].size() + tree[2 * i + 1].size());
        merge(tree[2 * i].begin(), tree[2 * i].end(), tree[2 * i + 1].begin(), tree[2 * i + 1].end(), tree[i].begin());
    }
}

int cnt(vector<vector<int>>& tree, int n, int s, int e, int l, int r, int x)
{
    if (e < l || r < s) return 0;
    if (l <= s && e <= r) return upper_bound(tree[n].begin(), tree[n].end(), x) - tree[n].begin();
    int d = tree[2 * n].size();
    return cnt(tree, 2 * n, s, s + d - 1, l, r, x) + cnt(tree, 2 * n + 1, s + d, e, l, r, x);
}

int kth_min(vector<vector<int>>& tree, int N, int l, int r, int k)
{
    int s = -1e9, e = 1e9;
    while (s <= e)
    {
        int m = (s + e) / 2;
        if (cnt(tree, 1, 1, N, l, r, m) < k) s = m + 1;
        else e = m - 1;
    }
    return s;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, M; cin >> N >> M;
    
    vector<int> A(N + 1);
    for (int i = 1; i <= N; i++) cin >> A[i];
    
    vector<vector<int>> tree;
    buildMergeSortTree(tree, A);
    
    while (M--)
    {
        int i, j, k; cin >> i >> j >> k;
        cout << kth_min(tree, N, i, j, k) << "\n";
    }
}
```
</div>
</details>

---

### [SOLUTION 2] Persistent Segment Tree

Persistent segment tree는 각 업데이트가 이루어졌을 때의 세그먼트 트리의 상태를 기억하는 장치로 사용할 수도 있기 때문에 $k$번째 원소를 구하는 문제에서 유용하게 사용할 수 있다.

구간 $\[l, r\]$의 $k$번째 수를 구하고 싶다면, **수열의 $r$번째 수를 트리에 업데이트한 순간과 $l - 1$번째 수를 트리에 업데이트한 순간의 차이를 이용하면 된다.**

**Problem 2**의 segment tree를 이용한 풀이에서 $k$번째 원소를 반환하는 함수의 원리를 그대로 이용해보자.

```cpp
int kth_min(vector<int>& tree, int n, int s, int e, int k)
{
    if (s == e) return s;
    
    int m = (s + e) / 2;
    if (k <= tree[2 * n]) return kth_min(tree, 2 * n, s, m, k);
    return kth_min(tree, 2 * n + 1, mid + 1, e, k - tree[2 * n]);
}
```

위 함수는 $k$와 "전체 수열" 중 $\[s, m\]$에 속하는 수의 개수(=구간에 왼쪽 자식 노드의 값, `tree[2 * n]`)을 비교해서 범위를 줄여나간다.

여기서 "전체 수열"을 "$l$번째 수부터 $r$번째 수"로 바꾸어주자.

> $k$와 수열의 $l$번째 수부터 $r$번째 수 중 $\[s, m\]$에 속하는 수의 개수를 비교한다.

```cpp
struct node {
    int l, r; // l, r: 왼쪽/오른쪽 자식 노드
    int val; // val: 노드에 저장된 값
};

int kth_min(vector<node>& tree, int i, int j, int s, int e, int k)
{
    if (s == e) return s;
    
    int m = (s + e) / 2;
    int cnt = tree[tree[j].l].val - tree[tree[i].l].val;
    if (k <= cnt) return kth_min(tree, tree[i].l, tree[j].l, s, m, k);
    return kth_min(tree, tree[i].r, tree[j].r, m + 1, e, k - cnt);
}
```

위 함수에 쓰인 매개변수 `i, j`는 다음을 의미한다.

- `i`: $l-1$번째 수를 트리에 업데이트한 순간, 구간 $\[s, e\]$을 대표하는 노드의 인덱스
- `j`: $r$번째 수를 트리에 업데이트한 순간, 구간 $\[s, e\]$을 대표하는 노드의 인덱스

이처럼 persistent segment tree를 이용하면, 각 쿼리를 $O(\log n)$으로 처리할 수 있게 된다.

**Time complexity**: $O(n \log n + q \log n)$

Merge sort tree를 이용한 방식보다 시간복잡도의 측면에서 더 효율적이라고 할 수 있다.

반대로 좌표값의 범위가 넓을 때에는 좌표압축을 이용해야한다는 단점이 있다.

<details>
<summary>[백준] 7469. K번째 수 SOLUTION</summary>
<div markdown="1">

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

struct node {
    int l, r, val;
};

node make_node(int l, int r, int val)
{
    node N;
    N.l = l; N.r = r; N.val = val;
    return N;
}

void buildSegtree(vector<node>& tree, int n, int s, int e)
{
    if (s == e) return;
    int m = (s + e) / 2;
    
    tree.push_back(make_node(0, 0, 0));
    tree[n].l = tree.size() - 1;
    buildSegtree(tree, tree[n].l, s, m);
    
    tree.push_back(make_node(0, 0, 0));
    tree[n].r = tree.size() - 1;
    buildSegtree(tree, tree[n].r, m + 1, e);
}

void _update(vector<node>& tree, vector<int>& x, int n, int s, int e, int i, int diff)
{
    if (i < x[s] || x[e] < i) return;
    
    tree[n].val += diff;
    if (s != e)
    {
        int m = (s + e) / 2;
        if (i <= x[m])
        {
            tree.push_back(tree[tree[n].l]);
            tree[n].l = tree.size() - 1;
            _update(tree, x, tree[n].l, s, m, i, diff);
        }
        else
        {
            tree.push_back(tree[tree[n].r]);
            tree[n].r = tree.size() - 1;
            _update(tree, x, tree[n].r, m + 1, e, i, diff);
        }
    }
}

int kth_min(vector<node>& tree, int i, int j, int s, int e, int k)
{
    if (s == e) return s;
    
    int m = (s + e) / 2;
    int cnt = tree[tree[j].l].val - tree[tree[i].l].val;
    if (k <= cnt) return kth_min(tree, tree[i].l, tree[j].l, s, m, k);
    return kth_min(tree, tree[i].r, tree[j].r, m + 1, e, k - cnt);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int n, m; cin >> n >> m;
    
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    
    // 좌표 압축
    vector<int> x = a;
    sort(x.begin(), x.end());
    x.erase(unique(x.begin(), x.end()), x.end());
    
    int s = x.size();
    vector<node> tree(2);
    tree[1] = make_node(0, 0, 0);
    buildSegtree(tree, 1, 0, s - 1);
    
    vector<int> root_idx(n + 1, 0);
    root_idx[0] = 1;
    
    // 수열을 트리에 업데이트
    for (int i = 0; i < n; i++)
    {
        if (root_idx[i + 1] == 0)
        {
            tree.push_back(tree[root_idx[i]]);
            root_idx[i + 1] = tree.size() - 1;
        }
        _update(tree, x, root_idx[i + 1], 0, s - 1, a[i], 1);
    }
    
    while (m--)
    {
        int i, j, k; cin >> i >> j >> k;
        cout << x[kth_min(tree, root_idx[i - 1], root_idx[j], 0, s - 1, k)] << "\n";
    }
}
```
</div>
</details>

---

### [SOLUTION 3] 2D Segment Tree






