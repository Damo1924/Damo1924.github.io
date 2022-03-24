---
title: "Finding the Eulerian Path/Cycle"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` 오일러 회로, 한붓그리기, 

## 1. Eulerian Path/Cycle

오일러 경로(Eulerian path)는 그래프의 모든 간선을 한 번씩 지나는 경로를 의미한다.

오일러 경로 중 시작점으로 돌아오는 경로를 오일러 회로(Eulerian cycle)라고 한다.

오일러 경로와 오일러 회로의 존재가능성은 **정정들의 차수(degree)**로 결정된다.

연결 무방향 그래프에서 차수가 홀수인 정점의 개수를 $x$라고 하자.

- 오일러 경로가 존재할 필요충분조건: $x = 0$ or $x = 2$
- 오일러 회로가 존재할 필요충분조건: $x = 0$

아래는 오일러 회로가 존재할 필요충분조건에 대한 간단한 증명 과정이다.

> $(\to)$ 오일러 회로가 존재한다면, **정점에 들어오는 간선의 개수와 나가는 간선의 개수가 동일**하므로 모든 정점의 차수가 짝수이다.
> 
> $(\gets)$ 사이클이 존재하지 않는 연결 그래프는 트리이다.
> 
> 트리는 루트 노드와 리프 노드의 차수가 1이기 때문에 반드시 홀수 노드를 갖는다.
> 
> 따라서 **모든 정점의 차수가 짝수인 그래프에는 사이클이 존재**한다.
> 
> 사이클을 찾아 그래프에서 사이클에 속한 간선을 모두 제거하면 여러 개의 연결 그래프로 분리된다.
> 
> 사이클을 제거하면 사이클에 속한 정점들의 차수가 2씩 감소하기 때문에 각 정점의 차수는 여전히 짝수이다.
> 
> 즉, 사이클을 제거해서 얻어진 연결 그래프들도 모든 정점의 차수가 짝수이므로 사이클이 존재한다.
> 
> 각 그래프에서 사이클을 찾아 사이클에 속한 간선을 제거하는 과정을 반복하면 모든 간선이 제거된다.
> 
> 따라서 **모든 정점의 차수가 짝수인 연결 그래프는 여러 개의 사이클로 나눌 수 있다.**
> 
> 이 사이클들을 하나의 사이클로 합치면 오일러 경로를 얻을 수 있다.

이제 주어진 그래프에서 오일러 회로를 구하는 방법에 대해 알아보자.

<br/>

## 2. Hierholzer's Algorithm

Hierholzer's algorithm은 오일러 경로/회로를 $O(E)$로 구할 수 있는 알고리즘이다.

> 오일러 회로는 아무 정점이나 시작 정점으로 잡아도 상관 없지만, 오일러 경로는 반드시 차수가 홀수인 정점에서 탐색을 시작해야한다.

알고리즘은 간단하게 아래와 같이 설명할 수 있다.

> **DFS로 그래프를 탐색하면서 인접한 모든 간선을 전부 탐색한 정점을 경로에 추가한다.**

각 간선을 한 번씩 탐색하기 때문에 시간복잡도는 $O(E)$이다.

이를 구현하는 방법은 다음과 같이 여러 가지가 있기 때문에 원하는 방법을 선택하면 된다.

- DFS: 재귀함수 or 스택
- 어떤 정점의 인접한 간선을 모두 탐색했는지 체크: 간선을 제거 or 간선을 탐색했다고 표시

아무래도 스택과 간선을 제거하는 방식이 메모리와 시간 양 측면에서 조금이라도 더 효율적이다.

---

### 스택 & 간선을 제거하는 방식

```cpp
stack<ii> g[N]; // graph
vector<bool> e; // edge check
vector<int> euler; // 오일러 회로

void getEulerCycle(int s)
{
    stack<int> cur;
    cur.push(s);
    while (!cur.empty())
    {
        int u = cur.top();
        
        while (!g[u].empty() && e[g[u].top().second]) g[u].pop();
        if (g[u].empty()) // 인접한 간선들을 모두 탐색한 경우
        {
            cur.pop();
            euler.push_back(u);
            continue;
        }
        
        auto [v, idx] = g[u].top();
        g[u].pop();
        e[idx] = 1;
        cur.push(v);
    }
}
```

스택에 각 정점에 인접한 간선 정보를 저장하여 각 스택의 크기가 0이 될 때까지 탐색하였다.

이 경우, `g[i]`에 인접한 정점의 번호와 함께 **간선의 번호**를 저장한다.

---

### 재귀함수 & 간선을 탐색했다고 표시하는 방식

```cpp
vector<ii> g[N]; // graph
int pos[N]; // g[i][pos[i]]까지 탐색하였음을 저장
vector<int> euler; // 오일러 회로

void dfs(int v)
{
    while (pos[v] < g[v].size())
    {
        auto [u, idx] = g[v][pos[v]];
        if (u == -1)
        {
            pos[v]++;
            continue;
        }
        
        g[u][idx].first = -1;
        g[v][pos[v]].first = -1;
        
        pos[v]++;
        dfs(u);
    }
    euler.push_back(v);
}
```

간선을 제거하는 대신 탐색한 간선을 표시해둔다.

이 경우, `g[i]`에 인접한 정점의 번호와 함께 **같은 간선의 인덱스**를 저장해야한다.

정점 $i, j$를 잇는 간선이면 아래와 같이 삽입해준다.

```cpp
g[i].push_back({ j, g[j].size() });
g[j].push_back({ i, g[i].size() - 1 });
```

<br/>

## 3. Related Problems

오일러 경로/회로와 관련된 문제들은 크게

- 오일러 경로/회로를 직접 구하는 문제
- 오일러 경로/회로가 존재할 조건을 이용하는 문제

로 나눌 수 있다.

---

### [백준] 1178. 간선 추가

[백준 1178. 간선 추가 문제 링크](https://www.acmicpc.net/problem/1178)

주어진 그래프에 최소한의 간선을 추가해서 오일러 경로가 존재하도록 만드는 문제이다.

---

### [백준] 17414. Sebin Loves Euler Circuit

[백준 17414. Sebin Loves Euler Circuit 문제 링크](https://www.acmicpc.net/problem/17414)

주어진 그래프에 최소한의 간선을 추가해서 오일러 회로가 존재하도록 만드는 문제이다.



<br/>

## References

[1] [Algorithms for Competitive Programming, 'Finding the Eulerian path in O(M)'](https://cp-algorithms.com/graph/euler_path.html)  
[2] [SlayStudy, 'Hierholzer's Algorithm'](https://slaystudy.com/hierholzers-algorithm/)  
