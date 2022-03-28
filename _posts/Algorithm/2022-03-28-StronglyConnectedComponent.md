---
title: "Strongly Connected Component (SCC)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` 강한 연결 요소, Kosaraju's algorithm, Tarjan's algorithm

## 1. Strongly Connected Component

유향 그래프(directed graph)에서 **모든 정점이 다른 모든 정점에 대해 도달 가능**하면 해당 그래프를 **강하게 연결되었다(strongly connected)**라고 한다.

**강한 연결 요소(strongly connected component, SCC)**는 유향 그래프의 부분 그래프 중 강하게 연결된 것을 말한다.

단, **강하게 연결되는 특성이 유지되는 한 포함할 수 있는 정점과 간선을 모두 포함해야한다.**

이는 다음과 같이 표현할 수 있다.

> 주어진 유향 그래프를 $G = (V, E)$의 강한 연결 요소 $C \subseteq V$는 다음을 만족한다.
> 
> - 임의의 두 정점 $u, v \in C$는 강하게 연결되어있다.
> - 임의의 두 정점 $u \in C$, $v \in V - C$는 강하게 연결되어 있지 않다.

SCC는 다음과 같은 특징을 갖는다.

- 유향 그래프에 있는 사이클 위의 정점들은 서로 강하게 연결되어 있으므로 하나의 SCC에 포함된다.
- SCC가 존재하지 않는 유향 그래프에는 사이클이 존재하지 않는다.
- 유향 그래프의 **응축(condensation)**은 **유향 비순환 그래프(directed acyclic graph)**이다.

> 유향 그래프 $G$의 응축(condensation)을 $G'$이라고 할 때,
> 
> $G'$은 $G$의 SCC를 정점으로 하고, 두 SCC에 속하는 정점들 사이의 간선들을 간선으로 하는 그래프이다.
> 
> 단, 그래프의 응축은 multiple edges를 포함하지 않기 때문에 두 SCC 사이에 여러 개의 간선들이 존재해도 하나의 간선으로 생각한다.

SCC를 선형 시간에 구하는 여러 알고리즘이 존재하는데, 이번 포스팅에서는 **Kosaraju's algorithm**과 **Tarjan's algorithm**에 대해 살펴볼 것이다.

<br/>

## 2. Kosaraju's Algorithm

Kosaraju's algorithm은 DFS 두 번을 통해 SCC를 구하는 알고리즘으로, 다음과 같은 과정으로 이루어진다.

- 주어진 그래프를 DFS로 탐색하면서 **인접한 정점들을 이미 모두 방문한 정점을 스택(stack)에 삽입**해준다.
- 주어진 그래프의 모든 간선을 역방향으로 뒤집은 그래프에 대해 스택에 저장된 순서대로 DFS를 수행하면, **각 DFS로 탐색되는 정점들**은 SCC를 이루게 된다.

DFS를 두 번 수행하기 때문에 알고리즘의 시간복잡도는 $O(V + E)$이다.

알고리즘을 구현하는 것 자체는 쉽지만, 왜 이러한 알고리즘을 통해 SCC를 구할 수 있는지 이해하기 위해 직접 증명해보기로 하였다.

---

### 2-1. Proof of Correctness

첫 번째 DFS를 수행하는 동안, 정점 $v$를 처음 방문한 시점을 $s(v)$, 마지막으로 방문한 시점을 $f(v)$라고 정의하자.

또, 강한 연결 요소 $C$에 대해 $s(C) = \min_{v \in C} s(v)$, $f(C) = \max_{v \in C} f(v)$라고 정의하자.

주어진 그래프와 역방향 그래프를 구현하여 각 그래프를 탐색하는 DFS 함수를 구현해주면 된다.

```cpp
vector<int> g[10001], inv[10001]; // g: graph, inv: inverse graph
bool chk[10001]; // vertex check
stack<int> st; // result of dfs1
vector<vector<int>> scc;

void dfs1(int u)
{
    chk[u] = 1;
    for (int v : g[u]) if (!chk[v]) dfs1(v);
    st.push(u); // 주변 정점을 모두 방문했으면 스택에 추가
}

void dfs2(int u, int idx)
{
    chk[u] = 0;
    scc[idx].push_back(u); // 연결된 정점들은 모두 같은 SCC에 포함
    for (int v : inv[u]) if (chk[v]) dfs2(v, idx);
}
```

이제 위 함수들을 이용해서 SCC를 구해줄 수 있다.

```cpp
for (int i = 1; i <= v; i++) if (!chk[i]) dfs1(i);
    
int i = 0;
while (!st.empty())
{
    int u = st.top();
    st.pop();
    if (chk[u])
    {
        scc.push_back({ });
        dfs2(u, i++);
    }
}
```

<br/>

## 3. Tarjan's Algorithm

<br/>

## References

[1] [
