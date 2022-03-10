---
title: "2D Segment Tree"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` Dynamic segment tree

## 1. 2D Segment Tree

2D segment tree는 **크기가 $N \times M$인 이차원 배열에서 값의 업데이트와 구간 쿼리를 $O(\log N \cdot \log M)$에 처리할 수 있는 자료구조**이다.

간단히 설명하면 **각 노드가 세그먼트 트리인 세그먼트 트리**라고 할 수 있다.

바깥쪽 세그먼트 트리는 행(row)을, 바깥쪽 세그먼트 트리의 각 노드인 안쪽 세그먼트 트리는 열(col)을 대표하는 노드를 가진 세그먼트 트리를 의미한다.

즉 바깥쪽 세그먼트 트리의 리프 노드는 각 행을 대표하며, 안쪽 세그먼트 트리의 리프 노드는 각 열을 대표한다.

이때 바깥쪽 세그먼트 트리의 노드들에는 안쪽 세그먼트 트리가 저장되어 있는 형태이다.

이제 2D 세그먼트 트리를 직접 구현해 볼 것이다.

<br/>

## 2. Bottom-Up 2D Segment Tree Implementation

[Bottom-Up 방식](https://damo1924.github.io/algorithm/BottomUpSegmentTree/)으로 세그먼트 트리를 구현하면 Top-Down 방식보다 메모리를 절약할 수 있다.

또한, 반복문만을 이용해서 쿼리를 처리할 수 있기 때문에 재귀함수 호출이 많이 일어나는 Top-Down 방식보다 더 빠르게 동작한다.

그래서 오프라인 쿼리가 주어지는 문제라면 Bottom-Up으로 구현하는 것이 여러모로 좋다.

---

길이가 $N$인 수열에 대한 세그먼트 트리를 구현하는데 길이가 $2N$인 배열이 필요하므로,

크기가 $N \times M$인 이차원 수열에 대한 2D 세그먼트 트리를 구현하는데는 크기가 $2N \times 2M$인 이차원 배열이 필요하다.

```cpp
class Seg2D {
public:
    int n;
    vector<vector<int>> node;
    Seg2D(int n) : n(n), node(2 * n, vector<int>(2 * n)) {}
};
```

이제 위 클래스의 멤버 함수들을 구현해보자.

---

### 1-1. Build Tree

2차원 배열의 $i$행 $j$열 값을 $a_{i, j}$($0 \leq i, j < n$)이라고 하자.

Bottom-Up 방식으로 구현한 세그먼트 트리에서 $a_k$($0 \leq k < m$)은 $n + k$번 노드에 대응된다.

이 사실을 이용하면 다음과 같은 순서대로 2D 세그먼트 트리를 초기화할 수 있다.

1. 바깥쪽 세그먼트 트리의 리프 노드들(안쪽 세그먼트 트리)의 리프 노드들에 $a_{i, j}$를 저장한다.
2. 바깥쪽 세그먼트 트리의 리프 노드들의 나머지 노드들을 구한다.
3. 바깥쪽 세그먼트 트리의 나머지 노드들을 구한다.

```cpp
void init(vector<vector<int>>& a)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            node[i + n][j + n] = a[i][j];
    
    for (int i = n; i < 2 * n; i++)
        for (int j = n - 1; j > 0; j--)
            node[i][j] = node[i][2 * j] + node[i][2 * j + 1];
    
    for (int i = n - 1; i > 0; i--)
        for (int j = 1; j < 2 * n; j++)
            node[i][j] = node[2 * i][j] + node[2 * i + 1][j];
}
```

---

### 1-2. Update Value

$a_{x, y}$를 $v$로 바꾸었을 때, 트리를 업데이트하는 함수를 구현해보자.

먼저 $x$행을 대표하는 노드(= 바깥쪽 트리의 리프 노드)를 업데이트해준다.

그 다음 바깥쪽 트리의 부모 노드를 차례대로 업데이트해주면 된다.

```cpp
void upd(int x, int y, int diff)
{
    for (int i = (x + n); i; i /= 2)
        for (int j = y + n; j; j /= 2)
            node[i][j] = node[2 * i][j] + node[2 * i + 1][j];
}
```

---

### 1-3. Query (Get Sum)

2D 세그먼트 트리에서 주어진 영역 $\[x_1, x_2\] \times \[y_1, y_2\]$의 합을 구하는 방법은 다음과 같다.

- 바깥쪽 세그먼트 트리에서 $\[x_1, x_2\]$에 해당하는 노드들 찾는다.
- 위에서 찾은 노드들에서 $\[y_1, y_2\]$에 해당하는 노드들에 저장된 값을 모두 더해준다.

먼저 바깥쪽 트리의 $x$번 노드에서 구간 $\[y_1, y_2\]$의 합을 구하는 함수부터 구현하였다.

```cpp
int query(int x, int y1, int y2)
{
    y1 += n; y2 += n;
    int res = 0;
    while (y1 <= y2)
    {
        if (y1 % 2 != 0) res += node[x][y1++];
        if (y2 % 2 == 0) res += node[x][y2--];
        y1 /= 2; y2 /= 2;
    }
    return res;
}
```

위 함수를 이용하면 주어진 영역의 합을 구하는 함수를 구현할 수 있다.

```cpp
int query(int x1, int x2, int y1, int y2)
{
    x1 += n; x2 += n;
    int res = 0;
    while (x1 <= x2)
    {
        if (x1 % 2 != 0) res += _sum(x1++, y1, y2);
        if (x2 % 2 == 0) res += _sum(x2--, y1, y2);
        x1 /= 2; x2 /= 2;
    }
    return res;
}
```

---

<details>
<summary> [Bottom-Up 2D Segment Tree] </summary>
<div markdown="1">

```cpp
class Seg2D {
public:
    int n;
    vector<vector<int>> node;
    Seg2D(int n) : n(n), node(2 * n, vector<int>(2 * n)) {}
    
    void init(vector<vector<int>>& a)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                node[i + n][j + n] = a[i][j];
    
        for (int i = n; i < 2 * n; i++)
            for (int j = n - 1; j > 0; j--)
                node[i][j] = node[i][2 * j] + node[i][2 * j + 1];
    
        for (int i = n - 1; i > 0; i--)
            for (int j = 1; j < 2 * n; j++)
                node[i][j] = node[2 * i][j] + node[2 * i + 1][j];
    }
    
    void upd(int x, int y, int diff)
    {
        for (int i = (x + n); i; i /= 2)
            for (int j = y + n; j; j /= 2)
                node[i][j] += diff;
    }
    
    int query(int x, int y1, int y2)
    {
        y1 += n; y2 += n;
        int res = 0;
        while (y1 <= y2)
        {
            if (y1 % 2 != 0) res += node[x][y1++];
            if (y2 % 2 == 0) res += node[x][y2--];
            y1 /= 2; y2 /= 2;
        }
        return res;
    }
    
    int query(int x1, int x2, int y1, int y2)
    {
        x1 += n; x2 += n;
        int res = 0;
        while (x1 <= x2)
        {
            if (x1 % 2 != 0) res += query(x1++, y1, y2);
            if (x2 % 2 == 0) res += query(x2--, y1, y2);
            x1 /= 2; x2 /= 2;
        }
        return res;
    }
};
```

</div>
</details>

---

### [백준] 11658. 구간 합 구하기 3

[백준 11658. 구간 합 구하기 3 문제 링크](https://www.acmicpc.net/problem/11658)

$N \times N$($1 \leq N \leq 1024$) 크기의 표가 주어질 때, 다음과 같은 쿼리 $M$($1 \leq M \leq 10^5$)개가 주어진다.

- $0$ $x$ $y$ $c$ : $x$행 $y$열의 값을 $c$로 바꾼다.
- $1$ $x_1$ $y_1$ $x_2$ $y_2$ : $x_1$행 $y_1$열부터 $x_2$행 $y_2$열까지의 합을 출력한다.

> $N$이 최대 $1024$이므로 2D 세그먼트 트리를 앞선 방법으로 구현해도 메모리 초과가 발생하지 않는다.

<details>
<summary> [SOLUTION] </summary>
<div markdown="1">

```cpp
#include <iostream>
#include <vector>
using namespace std;

class Seg2D {
// ...
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, M; cin >> N >> M;
    vector<vector<int>> a(N, vector<int>(N));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> a[i][j];
    
    Seg2D tree(N);
    tree.init(a);
    
    while (M--)
    {
        int w; cin >> w;
        if (w == 0)
        {
            int x, y, c; cin >> x >> y >> c;
            x--; y--;
            tree.upd(x, y, c - a[x][y]);
            a[x][y] = c;
        }
        else
        {
            int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
            cout << tree.query(x1 - 1, x2 - 1, y1 - 1, y2 - 1) << "\n";
        }
    }
}
```

</div>
</details>

<br/>

## 2. Memory Optimization

앞에서 푼 문제처럼 이차원 배열을 다루는 문제라면, $N$이 $10^3$ 정도로 주어지기 때문에 메모리 초과가 발생하지 않는 선에서 해결할 수 있다.

하지만 좌표평면에 여러 개의 점이 주어지고 어떤 영역 내의 점의 개수를 구하는 문제와 같이 세그먼트 트리가 나타내야할 구간의 길이가 커지면, 앞서 구현한 2D 세그먼트 트리로는 메모리 초과가 발생할 가능성이 높다.

이를 해결하기 위해 기존 세그먼트 트리에서 자주 사용했던 **좌표 압축** 기법을 이차원으로 확장시켜보자.

그렇다고 단순히 $x$좌표, $y$좌표에 대해 좌표 압축을 하면 안된다.

쿼리의 개수를 $q$라고 하면 $O(q^2)$이므로 쿼리가 $10^5$개씩 주어지면 여전히 메모리 초과가 발생한다.

이는 **바깥쪽 세그먼트 트리의 각 노드에 쿼리를 처리하기 위해 필요한 값들에 대한 세그먼트 트리를 구현**함으로써 해결할 수 있다.

예를 들어 `update(1, 2, 10)`과 같은 쿼리가 주어진다면, $x = 1$을 포함하는 바깥쪽 세그먼트 트리의 노드들에만 $y = 2$를 저장하는 것이다.

쿼리로 주어지는 좌표값들을 저장할 수 있도록 클래스에 새로운 이차원 벡터 `y_idx`를 추가하자.

```cpp
class Seg2D {
public:
    int n;
    vector<vector<int>> node, y_idx;
    Seg2D(int n) : n(n), node(2 * n), y_idx(2 * n) {}
}
```

`y_idx[i]`에는 바깥쪽 세그먼트 트리의 $i$번 노드(= 안쪽 세그먼트 트리)에 구축해야할 $y$좌표값들이 저장된다.

쿼리들을 입력받음과 동시에 다음 함수들을 이용해서 `y_idx`에 값을 추가한다.

```cpp
void _upd(int x, int y)
{
    for (int i = x + n; i; i /= 2) y_idx[i].push_back(y);
}

void _query(int x1, int x2, int y1, int y2)
{
    x1 += n; x2 += n;
    while (x1 <= x2)
    {
        if (x1 % 2 != 0)
        {
            y_idx[x1].push_back(y1);
            y_idx[x1++].push_back(y2);
        }
        if (x2 % 2 == 0)
        {
            y_idx[x2].push_back(y1);
            y_idx[x2--].push_back(y2);
        }
        x1 /= 2; x2 /= 2;
    }
}
```

이제 각 $i$에 대해 `y_idx[i]`를 압축해주자.

```cpp
void compress()
(
    for (int i = 0; i < 2 * n; i++)
    {
        if (y_idx[i].empty()) continue;
        sort(y_idx.begin(), y_idx.end());
        y_idx.erase(unique(y_idx.begin(), y_idx.end()), y_idx.end());
        a[i].resize(y_idx[i].size() * 2);
    }
}
```

모든 $i$에 대해 `y_idx[i]`를 압축했으므로 안쪽 세그먼트 트리를 업데이트하거나 쿼리를 처리할 때 `lower_bound()`를 이용해야한다.

이를 적용한 전체 클래스는 다음과 같다.

<details>
<summary> [Bottom-Up 2D Segment Tree - Memory Optimization] </summary>
<div markdown="1">

```cpp
class Seg2D {
public:
    int n;
    vector<vector<int>> node, y_idx;
    Seg2D(int n) : n(n), node(2 * n), y_idx(2 * n) {}
    
    void _upd(int x, int y)
    {
        for (int i = x + n; i; i /= 2) y_idx[i].push_back(y);
    }
    
    void _query(int x1, int x2, int y1, int y2)
    {
        x1 += n; x2 += n;
        while (x1 <= x2)
        {
            if (x1 % 2 != 0)
            {
                y_idx[x1].push_back(y1);
                y_idx[x1++].push_back(y2);
            }
            if (x2 % 2 == 0)
            {
                y_idx[x2].push_back(y1);
                y_idx[x2--].push_back(y2);
            }
            x1 /= 2; x2 /= 2;
        }
    }
    
    void compress()
    {
        for (int i = 0; i < 2 * n; i++)
        {
            if (y_idx[i].empty()) continue;
            sort(y_idx.begin(), y_idx.end());
            y_idx.erase(unique(y_idx.begin(), y_idx.end()), y_idx.end());
            node[i].resize(y_idx[i].size() * 2);
        }
    }
    
    void upd(int x, int y, int diff)
    {
        for (int i = (x + n); i; i /= 2)
        {
            int j = lower_bound(y_idx[i].begin(), y_idx[i].end(), y) - y_idx[i].begin();
            for (j += y_idx[i].size(); j; j /= 2)
                node[i][j] += diff;
        }
    }
    
    int query(int x, int y1, int y2)
    {
        y1 = lower_bound(y_idx[x].begin(), y_idx[x].end(), y1) - y_idx[x].begin();
        y2 = lower_bound(y_idx[x].begin(), y_idx[x].end(), y2) - y_idx[x].begin();
        y1 += y_idx[x].size(); y2 += y_idx[x].size();
        
        int res = 0;
        while (y1 <= y2)
        {
            if (y1 % 2 != 0) res += node[x][y1++];
            if (y2 % 2 == 0) res += node[x][y2--];
            y1 /= 2; y2 /= 2;
        }
        return res;
    }
    
    int query(int x1, int x2, int y1, int y2)
    {
        x1 += n; x2 += n;
        int res = 0;
        while (x1 <= x2)
        {
            if (x1 % 2 != 0) res += query(x1++, y1, y2);
            if (x2 % 2 == 0) res += query(x2--, y1, y2);
            x1 /= 2; x2 /= 2;
        }
        return res;
    }
};
```

</div>
</details>

<br/>

## 3. Top-Down 2D Segment Tree

Top-Down 방식은 [Dynamic Segment Tree](https://damo1924.github.io/algorithm/PersistentSegmentTree/#2-dynamic-segment-tree--implementation)를 이용해서 효율적으로 쿼리들을 처리할 수 있다.

주어진 영역에 대해 구하고자 하는 값을 함수 `int f(int a, int b)`라고 하자.

`f(a, b)`는 두 값을 더하는 `sum(a, b)`, 최댓값이나 최솟값을 구하는 `max(a, b)`, `min(a, b)`, 최대공약수를 구하는 `gcd(a, b)` 등이 가능하다.

먼저, 안쪽 세그먼트 트리 클래스를 구현해보자.

```cpp
class Seg1D {
public:
    class Node {
    public:
        int l, r;
        ll val;
    };
    
    vector<Node> node;
    Seg1D(): node(2, {0, 0, 0}) {} // root = node[1]
};
 ```

$i$번째 원소를 $k$로 업데이트하는 함수는 다음과 같다.

```cpp
    void upd_leaf(int n, int s, int e, int i, ll k)
    {
        if (i < s || e < i) return;
        if (s == e) node[n].val = k;
        else
        {
            int m = (s + e) / 2;
            if (i <= m)
            {
                if (node[n].l == 0)
                {
                    node.push_back({0, 0, 0});
                    node[n].l = node.size() - 1;
                }
                upd_leaf(node[n].l, s, m, i, k);
            }
            else
            {
                if (node[n].r == 0)
                {
                    node.push_back({0, 0, 0});
                    node[n].r = node.size() - 1;
                }
                upd_leaf(node[n].r, m + 1, e, i, k);
            }
            
            node[n].val = f(node[node[n].r].val, node[node[n].l].val);
        }
    }
```

Dynamic segment tree의 업데이트 함수와 동일하게 구현해주면 된다.

이때 함수 이름이 `upd_leaf()`인 이유는 **바깥쪽 세그먼트 트리의 리프 노드**를 업데이트할 때만 사용할 함수이기 때문이다.

바깥쪽 세그먼트 트리의 리프 노드를 제외한 나머지 노드를 업데이트할 때 사용할 함수를 따로 정의하자.

```cpp    
    void upd_parent(Seg1D& lc, int lc_n, Seg1D& rc, int rc_n, int n, int s, int e, int i)
    {
        if (i < s || e < i) return;
        if (s != e)
        {
            int m = (s + e) / 2;
            if (i <= m)
            {
                if (node[n].l == 0)
                {
                    node.push_back({0, 0, 0});
                    node[n].l = node.size() - 1;
                }
                upd_parent(lc, lc.node[lc_n].l, rc, rc.node[rc_n].l, node[n].l, s, m, i);
            }
            else
            {
                if (node[n].r == 0)
                {
                    node.push_back({0, 0, 0});
                    node[n].r = node.size() - 1;
                }
                upd_parent(lc, lc.node[lc_n].r, rc, rc.node[rc_n].r, node[n].r, m + 1, e, i);
            }
        }
        node[n].val = f(lc.node[lc_n].val, rc.node[rc_n].val);
    }
```

`upd_parent()`는 바깥쪽 세그먼트 트리의 노드를 해당 노드의 두 자식 노드에서 업데이트된 부분을 합치는 작업을 수행한다.

각 매개변수는 다음을 의미한다.

- `lc` / `rc`: 업데이트하려는 바깥 세그먼트 트리의 노드의 왼쪽 자식(left child) / 오른쪽 자식(right child)
- `n` : 현재 세그먼트 트리에서 `[s, e]` 구간을 대표하는 노드의 인덱스
- `lc_n` / `rc_n` : `lc` / `rc`에서 `[s, e]` 구간을 대표하는 노드의 인덱스

각 세그먼트 트리마다 특정 구간을 대표하는 노드의 인덱스가 다를 수 있으므로 각각의 인덱스를 모두 매개변수로 전달해주어야한다.

마지막으로 주어진 쿼리를 처리하는 함수를 구현한다.

```cpp
    ll query(int n, int s, int e, int l, int r)
    {
        if (r < s || e < l) return 0; // 함수 f에 따라 적절한 값을 사용 (ex) min() - INF
        if (l <= s && e <= r) return node[n].val;
        
        int m = (s + e) / 2;
        ll res = 0;
        if (l <= m && node[n].l != 0) res = f(res, query(node[n].l, s, m, l, r));
        if (m < r && node[n].r != 0) res = f(res, query(node[n].r, m + 1, e, l, r));
        return res;
    }
```

쿼리가 어떤 값을 구하는지에 따라서 적절한 상수 값을 사용해야함에 주의하자.

<details>
<summary> [Top-Down 1D Dynamic Segment Tree] </summary>
<div markdown="1">

```cpp
class Seg1D {
public:
    class Node {
    public:
        int l, r;
        ll val;
    };
    
    vector<Node> node;
    Seg1D(): node(2, {0, 0, 0}) {} // root = node[1]
    
    void upd_leaf(int n, int s, int e, int i, ll k)
    {
        if (i < s || e < i) return;
        if (s == e) node[n].val = k;
        else
        {
            int m = (s + e) / 2;
            if (i <= m)
            {
                if (node[n].l == 0)
                {
                    node.push_back({0, 0, 0});
                    node[n].l = node.size() - 1;
                }
                upd_leaf(node[n].l, s, m, i, k);
            }
            else
            {
                if (node[n].r == 0)
                {
                    node.push_back({0, 0, 0});
                    node[n].r = node.size() - 1;
                }
                upd_leaf(node[n].r, m + 1, e, i, k);
            }
            
            node[n].val = f(node[node[n].r].val, node[node[n].l].val);
        }
    }
    
    void upd_parent(Seg1D& lc, int lc_n, Seg1D& rc, int rc_n, int n, int s, int e, int i)
    {
        if (i < s || e < i) return;
        if (s != e)
        {
            int m = (s + e) / 2;
            if (i <= m)
            {
                if (node[n].l == 0)
                {
                    node.push_back({0, 0, 0});
                    node[n].l = node.size() - 1;
                }
                upd_parent(lc, lc.node[lc_n].l, rc, rc.node[rc_n].l, node[n].l, s, m, i);
            }
            else
            {
                if (node[n].r == 0)
                {
                    node.push_back({0, 0, 0});
                    node[n].r = node.size() - 1;
                }
                upd_parent(lc, lc.node[lc_n].r, rc, rc.node[rc_n].r, node[n].r, m + 1, e, i);
            }
        }
        node[n].val = f(lc.node[lc_n].val, rc.node[rc_n].val);
    }
    
    ll query(int n, int s, int e, int l, int r)
    {
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return node[n].val;
        
        int m = (s + e) / 2;
        ll res = 0;
        if (l <= m && node[n].l != 0) res = f(res, query(node[n].l, s, m, l, r));
        if (m < r && node[n].r != 0) res = f(res, query(node[n].r, m + 1, e, l, r));
        return res;
    }
};
```

</div>
</details>

이렇게 정의한 `Seg1D` 클래스를 노드에 저장하는 이차원 세그먼트 트리 `Seg2D` 클래스를 정의하자.

세그먼트 트리의 노드에 저장하는 값이 정수에서 세그먼트 트리로 바뀌었다는 점만 제외하면 완전히 같은 클래스이므로 어렵지 않게 구현할 수 있다.

<details>
<summary> [Top-Down 2D Dynamic Segment Tree] </summary>
<div markdown="1">
  
```cpp
class Seg2D {
public:
    class Node {
    public:
        int l, r;
        Seg1D tree;
    };
    
    int R, C; // R x C 크기의 이차원 배열
    vector<Node> node;
    Seg2D(int R, int C): R(R), C(C), node(2, {0, 0, Seg1D()}) {}
    
    void upd(int n, int s, int e, int i, int j, ll k)
    {
        if (i < s || e < i) return;
        if (s == e) node[n].tree.upd(1, 0, C - 1, j, k);
        if (s != e)
        {
            int m = (s + e) / 2;
            if (i <= m)
            {
                if (node[n].l == 0)
                {
                    node.push_back({0, 0, Seg1D()});
                    node[n].l = node.size() - 1;
                }
                upd(node[n].l, s, m, i, j, k);
            }
            else
            {
                if (node[n].r == 0)
                {
                    node.push_back({0, 0, Seg1D()});
                    node[n].r = node.size() - 1;
                }
                upd(node[n].r, m + 1, e, i, j, k);
            }
            node[n].tree._upd(node[node[n].r].tree, 1, node[node[n].l].tree, 1, 1, 0, C - 1, j);
        }
    }
    
    void upd(int i, int j, ll k) { upd(1, 0, R - 1, i, j, k); }
    
    ll query(int n, int s, int e, int i1, int i2, int j1, int j2)
    {
        if (i2 < s || e < i1) return 0;
        if (i1 <= s && e <= i2) return node[n].tree.query(1, 0, C - 1, j1, j2);
        
        int m = (s + e) / 2;
        ll res = 0;
        if (i1 <= m && node[n].l != 0) res = gcd2(res, query(node[n].l, s, m, i1, i2, j1, j2));
        if (m < i2 && node[n].r != 0) res = gcd2(res, query(node[n].r, m + 1, e, i1, i2, j1, j2));
        return res;
    }
    
    ll query(int i1, int i2, int j1, int j2) { return query(1, 0, R - 1, i1, i2, j1, j2); }
};
```

</div>
</details>

<br/>

## 4. Comparision between two methods

이렇게 세그먼트 트리를 구현하는 두 가지 방법에 대해 알아보았는데, 이를 어떤 문제에서 사용해야할까?

두 방식의 가장 큰 차이는 Bottom-Up은 오프라인 쿼리에서만 사용할 수 있지만, Top-Down은 온라인 쿼리에서도 사용할 수 있다는 것이다.

일차원 세그먼트 트리에서는 Bottom-Up 방식이 Top-Down 방식보다 메모리가 적다는 장점이 있었지만, 이차원 세그먼트 트리에서는 항상 그렇지도 않다.

쿼리들에 대한 정보를 저장하는 배열과 좌표압축을 위한 배열을 추가로 사용해야하기 때문이다.

<br/>

## References

[1] [Samsung Software Membership, blisstoner, '2D Segment Tree](http://www.secmem.org/blog/2019/11/15/2D-segment-tree/)
