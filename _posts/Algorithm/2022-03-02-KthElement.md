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

`Tags` kth element

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

아래는 구간합을 구하는 펜윅 트리의 두 함수이다.

```cpp
void _update(vector<int> tree, int n, int diff)
{
    int N = tree.size();
    while (n <= N)
    {
        tree[n] += diff;
        n += (n & -n);
    }
}

int _sum(vector<int> tree, int x) // [1, x] 구간합
{
    int res = 0;
    while (x)
    {
        res += tree[x];
        x &= -x;
    }
    return res;
}
```

집합에 새로운 원소 $X$를 추가하고 싶으면 `_update(tree, X, 1)`,

집합에 있는 원소 $Y$를 삭제하고 싶으면 `_update(tree, Y, -1)`을 해준다.

$k$번째 원소를 이분탐색으로 구하는 함수는 다음과 같다.

```cpp
int kth_min(vector<int> tree, int k)
{
    int s = 1, e = N;
    while (s < e)
    {
        int m = (s + e) / 2;
        if (_sum(m) < k) s = m + 1;
        else e = m;
    }
    return s;
}
```

---

### [SOLUTION 2] Segment Tree

이번에는 이분 탐색 없이 세그먼트 트리만 이용해서 $k$번째 수를 구하는 방법에 대해 알아보자.

앞선 방법에서도 사용한 구간합 세그먼트 트리를 그대로 사용하면 된다.

다만, 구간합 함수 대신 **해당 노드에서 $k$번째 수를 구하는 함수**를 구현해야한다.

어떤 노드에서 $k$번째 수를 구하기 위해서는 **왼쪽 자식 노드에 있는 원소의 개수를 $k$와 비교**해서 어느 자식 노드를 탐색할지 정해야한다.

이때 오른쪽 자식 노드로 가는 경우에는 $k$에서 왼쪽 자식 노드의 개수를 빼준다.

이 함수를 이용하면 $k$번째 수를 구하는 쿼리를 $O(\log n)$에 처리할 수 있다.

**Time Complexity**: $O(q \log n)$

이때 $q$는 쿼리(= 원소 추가/삭제, $k$번째 수 구하기)의 개수를 의미한다.

아래는 세그먼트 트리의 두 함수들이다.

```cpp
void _update(vector<int>& tree, int n, int s, int e, int x, int diff)
{
    if (e < x || x < s) return;
    
    tree[n] += diff;
    if (s == e) return;
    
    int m = (s + e) / 2;
    insert(tree, 2 * n, s, m, x);
    insert(tree, 2 * n + 1, m + 1, e, x);
}

int kth_min(vector<int>& tree, int n, int s, int e, int k)
{
    if (s == e) return s;
    
    int m = (s + e) / 2;
    if (k <= tree[2 * n]) return kth_min(tree, 2 * n, s, m, k);
    return kth_min(tree, 2 * n + 1, mid + 1, e, k - tree[2 * n]);
}
```

집합에 새 원소 $X$를 추가하고 싶으면 `_update(tree, 1, 1, N, X, 1)`,

기존 원소 $Y$를 삭제하고 싶으면 `_update(tree, 1, 1, N, Y, -1)`를 해준다.

---

### [SOLUTION 3] Fenwick Tree(BIT)

앞서 구간합을 구하는 세그먼트 트리를 이용해서 $k$번째 원소를 구할 수 있었기 때문에 BIT로도 구할 수 있다.

BIT는 세그먼트 트리보다 빠르면서 메모리도 적게 사용하기 때문에 주로 BIT를 이용해서 푼다.

물론 시간복잡도는 세그먼트 트리와 동일하게 쿼리당 $O(\log n)$이다.

아래는 BIT의 두 함수들이다.

```cpp
void _update(vector<int> tree, int n, int diff)
{
    int N = tree.size();
    while (n <= N)
    {
        tree[n] += diff;
        n += (n & -n);
    }
}

int kth_min(vector<int> tree, int k)
{
    int N = tree.size(), h = (int) floor(log2(tree.size())), res = 0;
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

<br/>

## [PROBLEM 3] 임의의 집합의 $k$번째 원소 구하기

집합의 원소를 삽입/삭제하는 과정이 너무 많이 일어나면 위에서 소개한 방법으로는 해결할 수 없다.

문제는 다음과 같이 주어진다.

> [백준 7469. K번째 수](https://www.acmicpc.net/problem/7469)
> 
> 길이가 $n$인 수열에서, 임의의 구간 $\[l, r\]$($1 \leq l \leq r \leq n$)의 $k$($1 \leq k \leq r - l + 1$)번째 원소를 구하여라.

이 경우에는 Merge sort tree를 이용하거나 2D Segment tree를 이용해야한다.

---

### [SOLUTION 1] Merge Sort Tree + Binary Search














