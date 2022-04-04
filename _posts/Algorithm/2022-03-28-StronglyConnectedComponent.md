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

`Tags` 강한연결요소, Kosaraju, Tarjan, DAG, Condensation, 2-SAT, 2150, 4196, 3977, 4013

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

> 유향 그래프 $G$의 응축(condensation)을 $G^{SCC}$이라고 할 때,
> 
> $G^{SCC}$은 $G$의 SCC를 정점으로 하고, 두 SCC에 속하는 정점들 사이의 간선들을 간선으로 하는 그래프이다.
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

유향 그래프 $G$의 응축 $G^{SCC}$가 DAG이므로 SCC들 사이에는 topological order가 존재한다.

DFS로 $G$를 탐색하면서 스택에 정점들을 삽입하는 순서를 생각해보면, 늦게 방문한 정점이 먼저 삽입되고, 처음에 방문한 정점이 가장 마지막에 스택에 삽입된다는 것을 알 수 있다.

$i$번째 SCC를 $C_i$라고 할 때, $C_i$에 속한 정점들 중 가장 마지막으로 스택에 삽입된 정점을 $u_i$라고 하자.

$G^{SCC}$에서 $C_i$부터 $C_j$로의 경로가 존재한다면, $u_i$가 $u_j$보다 스택에 늦게 삽입된다.

즉, $u_1, u_2, \dots$들의 스택에 삽입되는 순서는 **SCC들의 topological order의 역순**과 같다.

$C_i$들을 topological order로 정렬한 것을 $D_i$, $D_i$에 속한 정점 중 스택에 마지막으로 등장하는 정점을 $v_i$라고 하자.

간선들의 방향을 뒤집은 역방향 그래프에서 $v_i$부터 DFS로 탐색하면, $j \leq i$인 $D_j$에 속한 정점들에 도달할 수 있다.

스택에서 정점을 하나씩 뽑으면 $v_1, v_2, \dots$의 순서로 나오게 된다.

따라서 $v_i$부터 역방향 그래프를 탐색할 때에는 $j < i$인 $D_j$는 이미 모두 탐색되었기 때문에 $D_i$에 속하는 정점들만 탐색하게 된다.

---

### 2-2. Implementation

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

Tarjan's algorithm은 DFS를 한 번 수행하여 SCC를 구하는 알고리즘이다.

DFS로 그래프를 탐색하면서 각 정점을 방문한 순서를 저장해두고, 스택에 삽입한다.

그리고 어떤 정점에 대한 DFS 함수는 **해당 정점의 decendents의 방문 순서 중 가장 작은 값**을 반환하도록 한다.

만약 탐색 중인 부분 그래프가 사이클을 이루지 않는다면, 당연히 현재 정점의 방문 순서가 가장 먼저이기 때문에 위 값은 현재 정점의 방문 순서일 것이다.

하지만 사이클이 존재한다면 이미 방문했었던 정점을 만나게 되므로 위 값은 현재 정점의 방문 순서보다 작거나 같게 된다.

**그렇게 구한 값이 현재 정점의 방문 순서와 같다면, 스택에서 현재 정점을 뽑을 때까지 정점을 뽑고, 이 정점들은 하나의 SCC를 이룬다.**

위 조건을 만족하는 경우는 두 가지이다.

1. **현재 정점을 지나는 사이클이 없는 경우**
2. **어떤 SCC에 속한 정점들 중 현재 정점을 가장 먼저 방문한 경우**

첫 번째 케이스는 스택에 가장 위에 현재 정점이 위치하고 있기 때문에 해당 정점 하나가 하나의 SCC를 이루게 된다.

두 번째 케이스는 해당 SCC 위에 있는 정점들이 스택에 쌓여 있기 때문에 SCC를 구할 수 있다.

Tarjan's algorithm은 Kosaraju's algorithm보다 훨씬 직관적으로 받아들일 수 있기 때문에 알고리즘의 타당성에 대한 설명은 굳이 하지 않았다.

---

### 3-1. Implementation

각 정점의 방문 순서를 저장할 배열과 SCC에 속한 정점인지 체크할 배열이 필요하다.

```cpp
vector<int> g[10001]; // graph
int d[10001], idx = 0; // d[i]: depth (visited order)
bool chk[10001]; // check if it's in SCC
stack<int> st;
vector<vector<int>> scc;

int dfs(int u)
{
    d[u] = ++idx; // 방문 순서를 저장하고 스택에 삽입
    st.push(u);
    
    int res = d[u]; // u의 decendents의 방문 순서 중 가장 작은 값
    for (int v : g[u])
    {
        if (!d[v]) res = min(res, dfs(v));
        else if (!chk[v]) res = min(res, d[v]);
    }
    
    if (res == d[u])
    {
        vector<int> tmp;
        while (true)
        {
            int t = st.top();
            st.pop();
            tmp.push_back(t);
            chk[t] = 1;
            if (t == u) break;
        }
        scc.push_back(tmp);
    }
    return res;
}
```

모든 정점에 대해 한 번씩 함수가 실행되므로 시간복잡도는 $O(V + E)$이다.

<br/>

## 4. Related Problems

SCC를 구하는 두 가지 알고리즘은 같은 시간복잡도를 갖기 때문에 자신이 편한 알고리즘을 사용하면 된다.

SCC로 해결할 수 있는 가장 대표적인 문제는 **2-SAT problem**인데, 아래 포스팅에서 따로 다루었다.

> [2-SAT problem](https://damo1924.github.io/algorithm/2SATproblem/)

아래 문제들은 앞서 공부한 알고리즘을 알고 있으면 쉽게 풀 수 있는 문제들이다.

---

### [BOJ] 2150. Strongly Connected Component

[BOJ 2150. Strongly Connected Component 문제 링크](https://www.acmicpc.net/problem/2150)

주어진 방향 그래프의 SCC를 모두 구하는 문제이다.

---

### [BOJ] 4196. 도미노

[BOJ 4196. 도미노 문제 링크](https://www.acmicpc.net/problem/4196)

"$x$번 도미노는 쓰러지면서 $y$번 도미노를 쓰러뜨린다"와 같은 도미노들 사이의 관계가 주어질 때, 모든 도미노를 쓰러뜨리기 위해 손으로 쓰러뜨려야 하는 도미노들의 최소 개수를 구하는 문제이다.

도미노들을 정점으로 하는 방향 그래프 $G$에 대해 $G^{SCC}$를 구한 후, 진입 차수가 0인 정점(SCC)의 개수를 구해야한다.

가장 직관적인 방법은 각 도미노들이 속하는 SCC의 번호를 저장하고, 이를 통해 $G^{SCC}$의 간선 정보를 찾는 것이다.

Tarjan's algorithm으로 접근하면 위와 같이 풀 가능성이 높다.

Kosaraju's algorithm을 이용해도 같은 방법으로 풀 수 있지만, 알고리즘의 원리를 생각해보면 집입 차수를 계산하는 과정 없이도 해결할 수 있다는 것을 알 수 있다.

두 번째 DFS를 역방향 그래프에 대해 수행하는 이유는 현재 정점이 속하는 SCC에서 탐색이 가능한 다른 SCC들에 도달할 수 없도록 하기 위해서였다.

그런데 이번 문제에서는 연결된 SCC들을 모두 하나의 도미노만으로 전부 쓰러뜨릴 수 있기 때문에 **두 번째 DFS를 역방향 그래프가 아니라 정방향 그래프에 대해 수행함으로써 답을 구할 수 있다.**

---

### [BOJ] 3977. 축구 전술

[BOJ 3977. 축구 전술 문제 링크](https://www.acmicpc.net/problem/3977)

주어진 방향 그래프 $G$의 응축 $G^{SCC}$의 각 정점의 진입 차수를 구했을 때, 진입 차수가 0인 정점(SCC)가 유일한지 확인한다.

유일하다면 해당 SCC에 있는 정점들의 번호를 출력하고, 유일하지 않다면 시작 지점을 정할 수 없으므로 "Confused"를 출력한다.

---

### [BOJ] 4013. ATM

[BOJ 4013. ATM 문제 링크](https://www.acmicpc.net/problem/4013)

주어진 그래프 $G$로부터 $G^{SCC}$를 구하고, $G^{SCC}$에서 DP를 이용해서 최댓값을 구하는 문제이다.

아이디어 자체는 어렵지 않지만 워낙 필요한 배열이 많기 때문에 변수명을 주의해서 사용한다.

<br/>

## References

[1] [ACM-ICPC 상 탈 사람, 'SCC(Strongly Connected Component)'](https://jason9319.tistory.com/m/98)  
[2] [web.stanford.edu, 'Fundamental Graph Algorithms'](https://www.google.com/url?sa=t&rct=j&q=&esrc=s&source=web&cd=&ved=2ahUKEwjiwNCtxer2AhUKDN4KHbdIBe0QFnoECAMQAQ&url=https%3A%2F%2Fweb.stanford.edu%2Fclass%2Farchive%2Fcs%2Fcs161%2Fcs161.1138%2Flectures%2F04%2FSmall04.pdf&usg=AOvVaw1XASogccN6o2LFBFDoZGCf)  
