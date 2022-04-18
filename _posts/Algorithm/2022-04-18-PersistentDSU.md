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

`Tags` Union-Find, Dynamic Connectivity

## 1. Dynamic Connectivity

일반적인 [DSU(Union-Find)](https://damo1924.github.io/algorithm/UnionFind/)는 고정된 그래프에 있는 연결 요소들을 구하는 알고리즘이다.

그렇다면 **새로운 간선이 삽입되거나, 간선이 삭제될 때** 그래프의 연결 요소를 구하는 문제는 어떻게 풀 수 있을까?

이러한 문제를 [dynamic connectivity](https://en.m.wikipedia.org/wiki/Dynamic_connectivity)라고 부르며, **rollback** 기법을 사용해서 해결할 수 있다.

<br/>

## 2. DSU with Rollback

Dynamic connectivity 문제를 풀기 위해 rollback 기법을 적용한 DSU를 구현해보자.

기본적인 아이디어는 다음과 같다.

- $(l, r)$($0 \leq l < r \leq n$)라는 쿼리가 주어졌을 때, 연결 요소의 개수를 구해야한다.
- 전체 범위 $(0, n)$에 대한 세그먼트 트리를 구현한다. 즉, 세그먼트 트리의 각 노드에 해당하는 구간에 대해, DSU를 수행한다.
- 쿼리가 주어지면, 세그먼트 트리를 탐색하면서 주어진 구간에 속하는 노드들끼리 DSU를 수행한다.
- 답을 구한 후에 위 과정에서 수행한 DSU를 rollback한다.

먼저 rollback 기법을 적용한 DSU를 구현하였다.

```cpp
struct dsu_save
{
    int x, vx, y, vy;
    dsu_save() {}
    dsu_save(int _x, int _vx, int _y, int _vy)
        : v(_v), vx(_vx), y(_y), vy(_vy) {}
};

struct dsu_with_rollbacks
{
    vector<int> p, rnk; // parent, rank
    int comps; // connected components
    stack<dsu_save> st; // for rollback
    
    dsu_with_rollbacks() {}
    dsu_with_rollbacks(int n)
    {
        p.resize(n);
        rnk.resize(n);
        for (int i = 0; i < n; i++) p[i] = i, rnk[i] = 0;
        comps = n;
    }
    
    int _find(int x)
    {
        if (x == p[x]) return x;
        return _find(p[x]);
    }
    
    bool _union(int x, int y) // (x, y) union
    {
        x = _find(x); y = _find(y);
        if (x == y) return false;
        
        if (rnk[x] > rnk[y]) swap(x, y);
        st.push(dsu_save(x, rnk[x], y, rnk[y]));
        comps--;
        p[x] = y;
        if (rnk[x] == rnk[y]) rnk[y]++;
        return true;
    }
    
    void rollback() // (x, y) un-union
    {
        if (st.empty()) return;
        dsu_save q = st.top(); st.pop();
        
        comps++;
        p[q.x] = q.x; rnk[q.x] = q.vx;
        p[q.y] = q.y; rnk[q.y] = q.vy;
    }
};
```

다음으로는 그래프에 간선을 추가하거나 제거하는 오프라인 쿼리(offline query)를 처리할 수 있는 세그먼트 트리를 구현하였다.

```cpp
struct query
{
    bool isUnion;
    int x, y;
    query(int _x, int _y) : x(_x), y(_y) {}
}

struct dsu_segtree
{
    vector<vector<query>> q; // offline querys
    dsu_with_rollbacks dsu;
    int Q; // number of querys
    
    dsu_segtree() {}
    dsu_segtree(int _Q, int n) : Q(_Q)
    {
        dsu = dsu_with_rollbacks(n);
        q.resize(4 * Q + 4);
    }
    
    void insert_edge(int 
}
```

<br/>

## References

[1] [Algorithms for Competitive Programming, 'Deleting from a data structure in O(T(n)log n)'](https://cp-algorithms.com/data_structures/deleting_in_log_n.html)  
