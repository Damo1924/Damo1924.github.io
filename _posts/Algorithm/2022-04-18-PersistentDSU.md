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

`Tags` Union-Find, Dynamic Connectivity, 16911, 16695

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
struct dsu_with_rollbacks
{
    vector<int> p; // root: p = -rank, else: p = parent
    stack<ii> st; // for rollback
    
    dsu_with_rollbacks() {}
    dsu_with_rollbacks(int n) : p(n, -1) {}
    
    int find(int u)
    {
        if (p[u] < 0) return u;
        return find(p[u]);
    }
    
    bool merge(int u, int v)
    {
        u = find(u); v = find(v);
        if (u == v) return false;
        
        if (p[u] > p[v]) swap(u, v);
        st.push({ v, p[v] });
        p[u] += p[v];
        p[v] = u;
        return true;
    }
    
    void rollback()
    {
        if (st.empty()) return;
        auto [u, sz] = st.top(); st.pop();
        p[p[u]] -= sz;
        p[u] = sz;
    }
};
```

새로운 간선을 추가하거나 제거하기 전 상태를 스택에 저장하여 다시 불러올 수 있도록 하는 것이 핵심이기 때문에, 부모 노드의 번호를 바꾸는 path compression은 사용하지 않는다.

Weight compression을 위해 따로 rank 배열을 사용하기보다는 부모 노드의 번호를 저장하는 배열 하나로 처리하였다.

루트 노드라면 음의 부호를 붙인 rank 값을 저장하였고, rank의 초깃값은 $-1$이다.

따라서 persistent DSU는 각 연산을 $O(\log N)$로 처리하게 된다.

다음으로는 앞에서 설명한 세그먼트 트리를 구현하였다.

```cpp
struct query {
    int u, v;
};

vector<query> q;

struct dsu_segtree
{
    vector<vector<query>> tree;
    dsu_with_rollbacks dsu;
    int Q; // Number of queries
    
    dsu_segtree(int _Q, int n) : Q(_Q)
    {
        dsu = dsu_with_rollbacks(n);
        tree.resize(4 * Q + 4);
    }
    
    void add_query(int t, int s, int e, int l, int r, int idx)
    {
        if (e < l || r < s) return;
        if (l <= s && e <= r)
        {
            tree[t].push_back(q[idx]);
            return;
        }
        
        int m = (s + e) / 2;
        add_query(2 * t, s, m, l, r, idx);
        add_query(2 * t + 1, m + 1, e, l, r, idx);
    }
    
    void dfs(int t, int s, int e, vector<bool>& ans)
    {
        int cnt = 0;
        for (auto& [u, v] : tree[t])
            if (dsu.merge(u, v)) cnt++;
        
        if (s == e) ans[s] = (dsu.find(q[s].u) == dsu.find(q[s].v));
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

### [Codeforces] Connect and Disconnect

[Codeforces. Connect and Disconnect 문제 링크](https://codeforces.com/gym/100551/problem/A)

마찬가지로 그래프에 간선을 추가하고 제거하는 쿼리들이 주어지는데, 이번에는 세 번째 종류의 쿼리마다 **그래프의 연결 요소의 개수**를 구해야한다.

초기에는 그래프에 간선이 하나도 없기 때문에 그래프의 연결 요소의 개수는 정점의 개수인 $N$이다.

이때 그래프에 새로운 간선이 추가되어 서로 다른 연결 요소에 속하던 두 정점이 연결된다면, 연결 요소의 개수가 1만큼 줄어들게 된다.

반대로, rollback을 하면 두 정점이 연결되기 전으로 돌아가므로 연결 요소의 개수가 1만큼 늘어난다.

따라서, 앞서 구현한 `dsu_with_rollbacks` 구조체에 그래프에 있는 연결 요소의 개수를 나타내는 멤버 변수 `comps`를 추가한 다음, 위 내용을 그대로 적용해주면 된다.

- 생성자: `comps = n;`
- Union: `comps--;`
- Rollback: `comps++;`

이제 세그먼트 트리를 DFS로 탐색해서 쿼리에 대한 답을 구해줄 수 있다.

---

### [BOJ] 16695. The Bridge on the River Kawaii

[BOJ 16695. The Bridge on the River Kawaii 문제 링크](https://www.acmicpc.net/problem/16695)

간선에 가중치가 있어 두 정점 사이의 경로 중 가중치의 최댓값이 가장 작은 것을 구하는 쿼리가 주어진다.

**[HINT]** 간선의 가중치로 가능한 값이 $10$개뿐이다.

---

### [Codeforces] Narrow Components

[Codeforces. Narrow Components 문제 링크](https://codeforces.com/contest/1661/problem/E)

행렬의 각 원소 중 일부(free인 셀)를 노드로 하고, 인접한 두 노드를 잇는 간선으로 이루어진 그래프를 생각하자.

이렇게 만들어진 그래프는 고정된 그래프인 대신, 쿼리로 들어오는 구간에 해당하는 부분그래프에 있는 연결요소의 개수를 구하는 문제가 된다.

**[HINT]** 부분행렬에 해당하는 그래프의 연결 요소의 개수를 저장하는 세그먼트 트리를 구현한 뒤, 세그먼트 트리의 각 노드에 대해 persistent dsu를 구현한다.

> 자세한 풀이는 [이 포스트](https://damo1924.github.io/codeforces/ECR126-div2/#solution-2-persistent-dsuunion-find--segment-tree)에서 다루고 있다.

<br/>

## References

[1] [Algorithms for Competitive Programming, 'Deleting from a data structure in O(T(n)log n)'](https://cp-algorithms.com/data_structures/deleting_in_log_n.html)  
[2] [USACO, 'Offline Deletion'](https://usaco.guide/adv/offline-del?lang=cpp)  
