---
title: "Merge Sort Tree"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` Segment tree, 13537 수열과 쿼리 1, 7469 K번째 수

## 1. Merge Sort Tree

머지 소트 트리는 **세그먼트 트리의 각 노드가 해당 노드의 구간에 있는 원소들을 정렬된 상태로 저장**한 것이다.

<center><img src="" width="65%" height="65%"></center>

어떤 수열에 대해 merge sort를 수행했을 때 각 단계에서 병합해서 얻을 수 있는 부분수열들을 저장하고 있다고 할 수 있다.

머지 소트 트리는 리프 노드에 수열의 원소들을 순서대로 넣어준 후, bottom-up 방식으로 두 자식 노드를 병합한 결과를 노드에 저장해주면 된다.

```cpp
void buildMergeSortTree(vector<vector<int>>& tree, vector<int>& a)
{
    int n = a.size();
    int h = ceil(log2(n)); // 트리의 높이
    tree.resize(1 << (1 + h));
    
    int idx = 1 << h; // 첫 번째 리프 노드의 인덱스
    for (int i = 0; i < n; i++) tree[i + idx].push_back(a[i]);
    
    for (int i = idx - 1; i >= 1; i--) {
        tree[i].resize(tree[2 * i].size() + tree[2 * i + 1].size());
        merge(tree[2 * i].begin(), tree[2 * i].end(), tree[2 * i + 1].begin(), tree[2 * i + 1].end(), tree[i].begin());
    }
}
```

> 정렬된 두 배열을 병합해주는 C++ STL의 `<algorithm>`에 정의되어 있는 `merge()` 함수를 이용하였다.

트리의 높이를 $H = \lceil \log N \rceil$일 때, 레벨이 $h(0 \leq h \leq H)$인 노드에 들어가는 수열의 길이는 $O(2^{H - h})$이다.

레벨이 $h$인 노드의 개수는 $2^h$개이므로 머지 소트 트리를 만드는 시간복잡도는 다음과 같다.

\begin{aligned}
\sum_{h = 0}^H \left( 2^h \times O(2^{H-h}) \right) = O(H \cdot 2^H) = O(N \log N)
\end{aligned}

이제 머지 소트 트리를 이용해서 해결할 수 있는 문제들을 살펴보자.

<br/>

## 2. 부분 수열에서 $k$보다 큰 원소의 개수 구하기

[백준 13537. 수열과 쿼리 1](https://www.acmicpc.net/problem/13537)

길이가 $N(1 \leq N \leq 10^5)$인 수열 $A_1, A_2, \dots, A_N$가 주어진다.

이때 다음과 같이 주어지는 $M(1 \leq M \leq 10^5)$개의 쿼리를 수행하면 된다.

- $i$ $j$ $k$: $A_i, \dots, A_j$로 이루어진 부분 수열 중 $k$보다 큰 원소의 개수

**[SOLUTION]**

머지 소트 트리의 노드에 부분 수열들이 정렬된 상태로 저장되어 있기 때문에 주어진 범위에 해당되는 노드들에서 `upper_bound()` 함수를 이용하면 $k$보다 큰 원소들의 개수를 구할 수 있다.

주어진 구간에 포함되는 노드의 개수는 $O(\log N)$이고, `upper_bound()`의 시간복잡도는 $O(\log N)$이므로 각 쿼리를 $O(\log^2 N)$에 처리할 수 있다.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

void buildMergeSortTree(vector<vector<int>>& tree, vector<int>& a)
{
    int n = a.size();
    int h = ceil(log2(n));
    tree.resize(1 << (1 + h));
    
    int idx = 1 << h;
    for (int i = 0; i < n; i++) tree[i + idx].push_back(a[i]);
    
    for (int i = idx - 1; i >= 1; i--) {
        tree[i].resize(tree[2 * i].size() + tree[2 * i + 1].size());
        merge(tree[2 * i].begin(), tree[2 * i].end(), tree[2 * i + 1].begin(), tree[2 * i + 1].end(), tree[i].begin());
    }
}

int cnt(vector<vector<int>>& tree, int n, int s, int e, int l, int r, int x)
{
    if (e < l || r < s) return 0;
    if (l <= s && e <= r)
    {
        int idx = upper_bound(tree[n].begin(), tree[n].end(), x) - tree[n].begin();
        return tree[n].size() - idx; // 현재 노드에서 k보다 큰 원소의 개수
    }
    
    int d = tree[2 * n].size(); // 범위를 절반씩 나눈 것이 아니라는 점에 유의!
    return cnt(tree, 2 * n, s, s + d - 1, l, r, x) + cnt(tree, 2 * n + 1, s + d, e, l, r, x);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N; cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];
    
    vector<vector<int>> tree;
    buildMergeSortTree(tree, A);
    
    int M; cin >> M;
    while (M--)
    {
        int i, j, k; cin >> i >> j >> k;
        cout << cnt(tree, 1, 0, N - 1, i - 1, j - 1, k) << "\n";
    }
}
```

<br/>

## 3. 부분 수열을 정렬했을 때 $k$번째 수 구하기

[백준 7469. K번째 수 문제 링크](https://www.acmicpc.net/problem/7469)

길이가 $n(1 \leq n \leq 10^5)$인 배열 $a_1, a_2, \dots, a_n$이 주어진다.

이때 다음과 같이 주어지는 $m(1 \leq m \leq 5000)$개의 쿼리를 수행하면 된다.

- $i$ $j$ $k$: 부분 수열 $a_i, \dots, a_j$를 정렬했을 때 $k$번째 수를 출력한다.

**[SOLUTION]**

주어진 범위에 해당하는 노드들에 저장된 부분 수열들을 병합(merge)해서 $k$번째 수를 구할 수 있다.

















