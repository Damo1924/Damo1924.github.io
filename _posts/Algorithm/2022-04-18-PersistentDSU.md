---
title: "DSU with Rollbacks (Persistent DSU)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:    
  - Algorithm
use_math: true
comments: true

---

`Tags` Union-Find, Dynamic Connectivity, 16911

## 1. Dynamic Connectivity

일반적인 [DSU(Union-Find)](https://damo1924.github.io/algorithm/UnionFind/)는 고정된 그래프에 있는 연결 요소들을 구하는 알고리즘이다.

그렇다면 **새로운 간선이 삽입되거나, 간선이 삭제될 때** 그래프의 연결 요소를 구하는 문제는 어떻게 풀 수 있을까?

이러한 문제를 [dynamic connectivity](https://en.m.wikipedia.org/wiki/Dynamic_connectivity)라고 부르며, **rollback** 기법을 사용해서 해결할 수 있다.

<br/>

## 2. DSU with Rollback (BOJ 16911. 그래프와 쿼리)

Dynamic connectivity 문제를 풀기 위해 rollback 기법을 적용한 DSU를 구현해보자.

문제에서 요구하는 것에 따라서 필요한 변수가 달라질 수 있기 때문에, 다음 문제를 기준으로 구현하도록 하겠다.

> [BOJ 16911. 그래프와 쿼리](https://www.acmicpc.net/problem/16911)
> 
> $N$개의 정점으로 이루어진 그래프 $G$가 있을 때, 두 정수 $A, B$($1 \leq A, B \leq N$, $A \neq B$)에 대해 다음 쿼리들이 주어진다.
> 
> - $1$ $A$ $B$ : 정점 $A$와 정점 $B$를 연결하는 간선을 추가한다.
> - $2$ $A$ $B$ : 정점 $A$와 정점 $B$를 연결하는 간선을 제거한다.
> - $3$ $A$ $B$ : 정점 $A$에서 정점 $B$로 가는 경로가 있으면 1, 없으면 0을 출력한다.
> 
> 초기에 $G$에는 간선이 없고, 첫 번째와 두 번째 쿼리는 쿼리를 수행할 수 있을 때만 주어진다.

가장 대표적인 dynamic connectivity 문제로, 기본적인 아이디어는 다음과 같다.

1. 모든 쿼리를 입력받은 후, 각 간선들이 몇 번째 쿼리에 추가되고 몇 번째 쿼리에 제거되는지 구한다.
2. 위에서 구한 정보를 이용해서 각 노드가 해당 노드가 대표하는 구간에 존재하는 간선들을 저장하는 세그먼트 트리를 구현한다.
3. 이렇게 구한 세그먼트 트리의 **리프 노드**들은 **각 쿼리를 수행한 순간의 그래프**를 의미한다.
4. 따라서 DFS로 세그먼트 트리를 탐색하면서 쿼리에 대한 답을 구할 수 있다.

4번 과정에서 세그먼트 트리를 탐색할 때 **rollback** 기법을 사용하여 빠르게 처리할 수 있다.

단, 1번 과정에서 알 수 있듯이 이 방법은 **오프라인 쿼리(offline query)**인 경우에만 사용할 수 있다.

각 간선은 세그먼트 트리의 $O(\log M)$개의 노드에 저장되고, 세그먼트 트리의 각 노드에 저장된 간선을 추가하는데 $O(\log N)$이므로,

하나의 간선을 처리하는데 $O(\log M \log N)$이다.

따라서 알고리즘의 전체 시간복잡도는 $O(M \log M \log N)$이 된다.

먼저, rollback이 가능한 DSU부터 구현하였다.

```cpp
struct dsu_save // for rollback
{
    int x, vx, y, vy;
    dsu_save() {}
    dsu_save(int _x, int _vx, int _y, int _vy)
        : x(_x), vx(_vx), y(_y), vy(_vy) {}
};

struct dsu_with_rollbacks
{
    vector<int> p, rnk; // parent, rank
    stack<dsu_save> st; // for rollback
    
    dsu_with_rollbacks() {}
    dsu_with_rollbacks(int n)
    {
        p.resize(n);
        rnk.resize(n);
        for (int i = 0; i < n; i++) p[i] = i, rnk[i] = 0;
    }
    
    int _find(int x)
    {
        if (x == p[x]) return x;
        return _find(p[x]); // no path compression
    }
    
    bool _union(int x, int y) // (x, y) union
    {
        x = _find(x); y = _find(y);
        if (x == y) return true;
        
        if (rnk[x] > rnk[y]) swap(x, y);
        st.push(dsu_save(x, rnk[x], y, rnk[y]));
        p[x] = y;
        if (rnk[x] == rnk[y]) rnk[y]++;
        return false;
    }
    
    void rollback() // (x, y) un-union
    {
        if (st.empty()) return;
        dsu_save q = st.top(); st.pop();
        
        p[q.x] = q.x; rnk[q.x] = q.vx;
        p[q.y] = q.y; rnk[q.y] = q.vy;
    }
};
```

새로운 간선을 추가하거나 제거하기 전 상태를 스택에 저장하여 다시 불러올 수 있도록 하는 것이 핵심이기 때문에, 부모 노드의 번호를 바꾸는 path compression은 사용하지 않는다.

따라서 persistent DSU는 각 연산을 $O(\log N)$로 처리하게 된다.

다음으로는 앞에서 설명한 세그먼트 트리를 구현하였다.

```cpp
struct query
{
    int x, y;
    query() {}
    query(int _x, int _y) : x(_x), y(_y) {}
};

struct dsu_segtree
{
    vector<query> queries;
    vector<vector<query>> tree;
    dsu_with_rollbacks dsu;
    int Q; // Number of queries
    
    dsu_segtree() {}
    dsu_segtree(int _Q, int n) : Q(_Q)
    {
        queries.resize(Q);
        tree.resize(4 * Q + 4);
        dsu = dsu_with_rollbacks(n);
    }
    
    void add_query(int t, int s, int e, int l, int r, query q)
    {
        if (e < l || r < s) return;
        if (l <= s && e <= r)
        {
            tree[t].push_back(q);
            return;
        }
        
        int m = (s + e) / 2;
        add_query(2 * t, s, m, l, r, q);
        add_query(2 * t + 1, m + 1, e, l, r, q);
    }
    
    void dfs(int t, int s, int e, vector<bool>& ans)
    {
        int cnt = 0;
        for (query& q : tree[t])
            if (!dsu._union(q.x, q.y)) cnt++;
        
        if (s == e) ans[s] = (dsu._find(queries[s].x) == dsu._find(queries[s].y));
        else
        {
            int m = (s + e) / 2;
            dfs(2 * t, s, m, ans);
            dfs(2 * t + 1, m + 1, e, ans);
        }
        
        while (cnt--) dsu.rollback(); 
    }
};
```

- `add_query()` : $(l, r)$의 쿼리 구간에 존재하는 간선 $q$를 세그먼트 트리에 저장하는 함수
- `dfs()` : 세그먼트 트리를 DFS로 탐색하여 리프 노드($s = e$)에서 쿼리의 답을 구하는 함수

<br/>

## 3. Related Problems

위에서 푼 문제 외에도 다른 값들을 구하는 문제들이 있다.



<br/>

## References

[1] [Algorithms for Competitive Programming, 'Deleting from a data structure in O(T(n)log n)'](https://cp-algorithms.com/data_structures/deleting_in_log_n.html)  
[2] [USACO, 'Offline Deletion'](https://usaco.guide/adv/offline-del?lang=cpp)  
