---
title: "좌표 압축 기법(Coordinate Compression)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` Segment tree, Fenwick tree, BIT, 2517 달리기, 18407 가로 블록 쌓기

## 1. Coordinate Compression

좌표 압축 기법은 말 그대로 주어진 좌표를 압축해서 보다 작은 범위의 좌표로 표현하는 방법이다.

주로 세그먼트 트리(segment tree)나 펜윅 트리(fenwick tree, BIT)와 함께 사용하여 구간 쿼리를 처리하는데 쓰인다.

다음과 같은 문제를 생각해보자.

---

$x$축 위에 있는 $N$($1 \leq N \leq 10^5$)개의 점의 좌표가 주어질 때, 아래 쿼리를 처리해야한다.

- $x_1$ $x_2$ : $x_1 \leq x \leq x_2$를 만족하는 $x$의 개수를 출력한다.

이러한 쿼리가 $M$($1 \leq M \leq 10^5$)개가 주어진다.

---

만약 주어지는 좌표의 범위가 $10^5$ 이하라면 세그먼트 트리나 펜윅 트리를 이용해서 $O(M \log n)$으로 쿼리들을 처리할 수 있을 것이다.

하지만 좌표의 범위가 절댓값이 $10^9$ 이하인 정수로 주어진다면 어떻게 될까?

시간이 오래 걸릴 뿐만 아니라, 트리를 배열로 구현하기 위해 사용해야하는 배열의 크기가 매우 크다는 문제가 발생한다.

이럴 때 사용하는 방법이 바로 **좌표 압축**인 것이다.

좌표의 범위가 $10^9$이라고 해도, 주어지는 좌표의 개수는 $10^5$이므로 좌표를 $1$부터 $10^5$까지의 정수로 표현할 수 있다.

<br/>

## 2. Implementation

구현하는 방법은 매우 간단하다.

`<algorithm>`에 정의된 `unique()` 함수로 인덱싱을 하고, `lower_bound()`를 통해 해당 인덱스를 구할 수 있다.

```cpp
int N; cin >> N;
vector<int> v(N);
for (int i = 0; i < N; i++) cin >> v[i];

sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());

int q; cin >> q;
int idx = lower_bound(v.begin(), v.end(), q) - v.begin();
```

원하는 값의 인덱스를 $O(\log n)$으로 구할 수 있다.

<br/>

## 3. Related Problems

### [백준] 2517. 달리기

[백준 2517 달리기 문제 링크](https://www.acmicpc.net/problem/2517)

$N$($3 \leq N \leq 500000$)명이 참여하고 있는 달리기 시합이 진행되고 있다.

모든 선수가 반환점을 넘은 순간, 앞에서부터 각 선수의 실력이 정수로 주어진다.(숫자가 클수록 실력이 좋음을 의미한다.)

각 선수의 입장에서 자신보다 앞에서 달리고 있는 선수들 중 실력이 자기보다 좋은 선수를 앞지르는 것은 불가능하지만, 실력이 자기보다 좋지 못한 선수는 앞지르는 것이 가능하다.

이를 통해 각 선수는 자신이 앞으로 얻을 수 있는 최선의 등수를 알 수 있다.

선수들의 평소 실력을 현재 달리고 있는 순서대로 입력 받아 각 선수의 최선의 등수를 출력하는 문제이다.

**[SOLUTION] BIT + Coordinate Compression**

앞에 있는 선수들 중 자신보다 실력이 좋지 못한 선수의 수를 구해서 현재 등수에서 빼면 최선의 등수를 구할 수 있다.

따라서 세그먼트 트리 또는 펜윅 트리(BIT)에 좌표 압축을 적용해서 지금까지 주어진 실력값을 저장하면 빠르게 최선의 등수를 구할 수 있다.

> 펜윅 트리(BIT)에 대한 자세한 내용은 [이 포스트](https://damo1924.github.io/algorithm/FenwickTree/)에서 다루고 있다.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

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

int _sum(vector<int>& tree, int a, int b)
{
    return _sum(tree, b) - _sum(tree, a - 1);
}

void _update(vector<int>& tree, int x)
{
    int n = tree.size();
    while (x < n)
    {
        tree[x]++;
        x += (x & -x);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N; cin >> N;
    vector<int> v(N + 1), w(N + 1);
    for (int i = 1; i <= N; i++)
    {
        cin >> v[i];
        w[i] = v[i];
    }

    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    vector<int> tree(N + 1);

    for (int i = 1; i <= N; i++)
    {
        int idx = lower_bound(v.begin(), v.end(), w[i]) - v.begin();
        cout << i - _sum(tree, idx) << "\n";
        _update(tree, idx);
    }
}
```

---

### [백준] 18407. 가로 블록 쌓기

[백준 18407. 가로 블록 쌓기 문제 링크](https://www.acmicpc.net/problem/18407)

가로 블록만 등장하는 테트리스 게임을 하려고 한다.

총 $N$($1 \leq N \leq 10^5$)개의 가로 블록이 주어지며, 떨어지는 순서대로 $1$번부터 $N$번까지 번호가 매겨져 있다.

$i$번 블록의 높이는 $1$, 너비는 $w_i$이고, 왼쪽 벽으로부터 거리가 $d_i$인 곳에 떨어뜨려야 한다.($1 \leq w_i, d_i \leq 10^9$)

모든 블록을 쌓았을 때 높이를 구하여라.

**[SOLUTION] Segment Tree with Lazy Propagation + Coordinate Compression**

세그먼트 트리에 좌표 압축을 적용하면 된다.

블럭이 놓이는 범위 $\[d_i, d_i + w_i\]$의 최대 높이 $h_i$를 구해 해당 구간을 $h_i + 1$로 업데이트해주면 된다.

구간 업데이트를 수행해야하므로 lazy propagation을 이용하자.

> Segment Tree와 Lazy Propagation에 대한 자세한 내용은 [이 포스트](https://damo1924.github.io/algorithm/SegmentTree/)에서 다루고 있다.

좌표 압축을 수행하는데 $O(N \log N)$, 각 블럭의 범위의 인덱스를 구하는데 $O(\log N)$, 최대 높이를 구하고 구간 업데이트를 하는데 $O(\log N)$이다.

따라서 전체 시간복잡도는 $O(N \log N)$이다.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
using namespace std;

void lazyPropagation(vector<int>& tree, vector<int>& lazy, int n, int s, int e)
{
    tree[n] = lazy[n];
    if (s != e)
    {
        lazy[2 * n] = lazy[n];
        lazy[2 * n + 1] = lazy[n];
    }
    lazy[n] = 0;
}

int _max(vector<int>& tree, vector<int>& lazy, int n, int s, int e, int l, int r)
{
    if (lazy[n] != 0) lazyPropagation(tree, lazy, n, s, e);

    if (e < l || r < s) return 0;
    if (l <= s && e <= r) return tree[n];

    int m = (s + e) / 2;
    return max(_max(tree, lazy, 2 * n, s, m, l, r), _max(tree, lazy, 2 * n + 1, m + 1, e, l, r));
}

void _updateRange(vector<int>& tree, vector<int>& lazy, int n, int s, int e, int l, int r, int h)
{
    if (lazy[n] != 0) lazyPropagation(tree, lazy, n, s, e);

    if (e < l || r < s) return;

    if (l <= s && e <= r)
    {
        lazy[n] = h;
        lazyPropagation(tree, lazy, n, s, e);
        return;
    }

    int m = (s + e) / 2;
    _updateRange(tree, lazy, 2 * n, s, m, l, r, h);
    _updateRange(tree, lazy, 2 * n + 1, m + 1, e, l, r, h);

    tree[n] = max(tree[2 * n], tree[2 * n + 1]);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N; cin >> N;
    vector<int> w(N), d(N), v(2 * N);
    for (int i = 0; i < N; i++)
    {
        cin >> w[i] >> d[i];
        v[i] = d[i]; v[i + N] = d[i] + w[i];
    }

    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());

    int n = v.size();
    int h = (int)ceil(log2(n));
    vector<int> tree(1 << (h + 1)), lazy(1 << (h + 1));

    for (int i = 0; i < N; i++)
    {
        int l = lower_bound(v.begin(), v.end(), d[i]) - v.begin();
        int r = lower_bound(v.begin(), v.end(), d[i] + w[i]) - v.begin() - 1;
        _updateRange(tree, lazy, 1, 0, n - 1, l, r, _max(tree, lazy, 1, 0, n - 1, l, r) + 1);
    }
    cout << _max(tree, lazy, 1, 0, n - 1, 0, n - 1);
}
```

