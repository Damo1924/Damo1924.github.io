---
title: "최단 경로 문제"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

## 1. Shortest Path Problem

그래프 이론에서 어떤 두 정점 사이의 최단 경로를 찾는 문제를 **최단 경로 문제**라고 부른다.

최단 경로 문제는 다음과 같이 나눌 수 있다.

- **단일-쌍 최단 경로 문제**: 어떤 정점 $v$에서 다른 정점 $v'$로 가는 최단 경로를 찾는 문제
- **단일-출발 최단 경로 문제**: 어떤 정점 $v$에서 그래프 내의 모든 다른 정점까지의 최단 경로들를 찾는 문제
- **단일-도착 최단 경로 문제**: 모든 정점들로부터 어떤 정점 $v$로 도착하는 최단 경로들을 찾는 문제
- **전체-쌍 최단 경로 문제**: 그래프 내의 모든 정점 쌍들 사이의 최단 경로들을 찾는 문제

다음은 최단 경로 문제들을 해결하기 위한 주요 알고리즘들이다.

- **Dijkstra algorithm**: 단일-쌍, 단일-출발, 단일-도착 최단 경로 문제
- **Bellman-Ford algorithm**: 단일-출발 최단 경로 문제
- **A* algorithm**: 단일-쌍 최단 경로 문제
- **Floyd-Warshall algorithm**: 전체-쌍 최단 경로 문제

이번 포스트에서는 다익스트라 알고리즘, 벨만-포드 알고리즘, 플로이드-워셜 알고리즘에 대해 다루도록 하겠다.


<br/>
## 2. Dijkstra Algorithm

다익스트라 알고리즘은 **가중 그래프에서 두 정점 사이의 최단 경로를 찾는 알고리즘**이다.

기존 알고리즘은 어떤 두 정점 사이의 최단 경로를 구하는 것이였지만, 일반적으로는 한 정점에서 그래프의 다른 정점들까지의 최단 경로들을 찾는 형태로 사용한다.

다익스트라 알고리즘은 다음과 같다.

---

1. 큐 `q`에 모든 **미방문 꼭짓점**을 저장해둔다.
2. 모든 꼭짓점에 대해 현재까지 해당 꼭짓점까지의 최단 거리를 저장할 배열 `dist[i]`를 선언하고, 초기값을 저장한다. 출발하는 꼭짓점은 0, 나머지 꼭짓점은 충분히 큰 값 `INF`로 초기화한다.
3. 큐를 탐색해서 `dist`에 저장된 값이 가장 작은 꼭짓점 `v`에 대해 연결된 꼭짓점을 탐색한다.
4. `v`를 거쳐 도달한 경로의 길이가 `dist`에 저장된 길이보다 작으면 `dist`의 값을 갱신한다.
5. `v`에 연결된 모든 꼭짓점에 대해 4번 작업을 수행했다면, `v`를 큐에서 제거한다.
6. 3~5 과정을 큐에 원소가 없거나 큐에 남아있는 원소들에 해당하는 `dist` 배열의 값이 모두 `INF`일 때까지 반복한다.
7. `dist`에 저장된 값이 각 꼭짓점에 이르는 최단 경로의 길이가 된다.

---

모든 꼭짓점을 한 번씩 방문하므로 각 작업이 $O(\left\vert V \right\vert)$번 수행된다.

각 작업은 큐에 들어있는 꼭짓점들 중 `dist`값이 가장 작은 꼭짓점을 찾는 것과 해당 꼭짓점에 연결된 꼭짓점을 모두 탐색하는 것으로 구성된다.

큐를 탐색해서 최솟값을 가진 꼭짓점을 찾는데 $O(\left\vert V \right\vert^2)$, 모든 꼭짓점에 대해 연결된 꼭짓점들을 탐색하는 것은 모든 간선을 탐색하는 것과 같으므로 $O(\left\vert E \right\vert)$이다.

그러므로 전체 시간복잡도는 $O(\left\vert V \right\vert^2 + \left\vert E \right\vert)$인데, 항상 $\left\vert E \right\vert < \left\vert V \right\vert^2$이므로 $O(\left\vert V \right\vert^2)$로 정리할 수 있다.

하지만, 큐를 선형 탐색하는 대신 **우선순위 큐**를 사용하는 방법이 등장하게 되면서 최솟값을 가진 꼭짓점을 찾는 작업이 $O(\left\vert V \right\vert \log \left\vert V \right\vert)$의 시간복잡도를 가지게 됨에 따라 다익스트라 알고리즘의 시간복잡도는 다음과 같이 표현된다.

\begin{align\*}
O(\left\vert E \right\vert + \left\vert V \right\vert \log \left\vert V \right\vert)
\end{align\*}

우선순위 큐를 이용한 다익스트라 알고리즘의 구현은 가중치가 없는 그래프에서 BFS로 최단 경로를 찾는 것과 그 형태가 유사하다.

가중치가 없는 그래프에서 최단 경로를 구할 때는 **방문 여부를 체크**하면서 BFS를 수행하였는데, 가중치가 생기면 늦게 방문해도 거리가 더 짧은 경로가 존재할 수도 있기 때문에 단순히 방문 여부만을 체크해서는 안 된다.

그래서 다익스트라 알고리즘은 방문 여부 대신 **현재까지의 최단 거리**를 저장한다.

또한, 큐에 정점 번호와 함께 해당 정점까지의 거리를 추가해서 저장해둔 최단 거리와 비교할 수 있도록 한다.

만약 큐에 있는 점점까지의 거리가 현재까지의 최단 거리보다 길다면 탐색할 필요 없이 넘어간다.

마찬가지로 큐에 원소를 추가할 때도 최단 거리보다 탐색 중인 경로가 더 짧은 경우에만 큐에 원소를 추가하고 최단 거리를 갱신한다.

우선순위 큐를 이용한 다익스트라 알고리즘은 **음이 아닌 가중치를 가지는 무작위 유향 그래프에서 단일-출발 최단 경로 문제 알고리즘 중 시간복잡도가 가장 작은 알고리즘**이라고 한다.

---

### [백준] 1753. 최단경로

[백준 1753.최단경로 문제 링크](https://www.acmicpc.net/problem/1753)

꼭짓점의 개수 V, 간선의 개수 E, 출발점의 번호 K가 주어진다.

이후 E개 줄에 걸쳐 각 간선에 대한 정보가 주어질 때, K로부터 V개의 각 꼭짓점들까지의 최단 경로의 길이를 구하는 문제이다.

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int, int> p;
const int INF = 1000000000;

vector<p> graph[20001];

int dist[20001];

struct compare {
    bool operator() (p A, p B) { return A.second > B.second; }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int V, E, K;
    cin >> V >> E >> K;
    
    for (int i = 1; i <= V; i++) dist[i] = INF; // 출발점은 0, 나머지는 INF로 초기화
    dist[K] = 0;
    
    int u, v, w;
    while (E--)
    {
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }
    
    priority_queue<p, vector<p>, compare> pq; // 거리가 가까운 순서대로 정렬하여 저장하는 우선순위 큐
    pq.push({K, 0});
    while (!pq.empty())
    {
        int cur = pq.top().first, d = pq.top().second;
        pq.pop();
        
        if (dist[cur] < d) continue; // 배열에 저장된 거리보다 크다면 무시
        
        for (int i = 0; i < graph[cur].size(); i++)
        {
            int next = graph[cur][i].first, D = d + graph[cur][i].second;
            if (dist[next] > D) // 연결된 꼭짓점 중 저장된 거리보다 cur를 거쳐서 가는 경로가 더 짧은 경우
            {
                dist[next] = D;
                pq.push({next, D});
            }
        }
    }
    
    for (int i = 1; i <= V; i++)
    {
        if (dist[i] == INF) cout << "INF\n";
        else cout << dist[i] << "\n";
    }
}
```

---

다익스트라 알고리즘은 이처럼 일반적으로 한 꼭짓점에서 다른 모든 꼭짓점까지의 최단 거리를 구하는데 사용하는데, 주어진 조건에 따라서 변형 가능성이 굉장히 많다.


<br/>
## 3. Bellman-Ford Algorithm

벨만-포드 알고리즘은 **한 정점에서 다른 모든 정점까지의 최단 경로를 구하는 알고리즘**으로, 다익스트라와 동일한 문제를 해결하는 알고리즘이다.

그런데, 다익스트라는 앞서 말했듯이 음이 아닌 가중치를 갖는 유향 그래프의 단일-출발 최단 경로 문제를 해결하는 가장 효율적인 알고리즘이다.

즉, 벨만-포드 알고리즘은 다익스트라보다 비효율적인 탐색 방법이다.

그럼에도 이를 사용하는 이유는 다익스트라는 **음이 아닌 가중치**를 가진 그래프에서만 사용할 수 있다는 한계점을 가지고 있기 때문이다.

다익스트라는 **현재까지의 최단 경로보다 더 짧은 경로를 발견**하면 최단 경로를 갱신하고 해당 경로를 따라 탐색을 이어나가는 알고리즘이다.

이를 음의 가중치를 가지는 그래프에 적용하면 **음의 사이클**이 발생할 수 있는데, 이것이 우리가 벨만-포드 알고리즘을 사용하는 이유이다.

음의 사이클이란 그래프에서 **가중치의 총합이 음수가 되는 사이클**을 말하는데, 다익스트라는 음의 사이클을 만나면 사이클 위의 정점들까지의 거리를 음의 무한대, 계속해서 더 작은 값으로 갱신하게 되는 것이다.

벨만-포드 알고리즘은 **음의 사이클이 발생해서 최단거리를 구할 수 없다**는 것을 알 수 있는 알고리즘으로, 다음과 같다.

---

1. 



<br/>
## 4. Floyd-Warshall Algorithm

플로이드-워셜 알고리즘은 **가중 그래프에서 모든 정점 쌍 사이의 최단 경로들을 찾는 알고리즘**이다.

1부터 $N$까지 번호가 매겨진 $N$개의 정점들로 이루어진 그래프 $G$를 생각하자.

정점 $i$에서 정점 $j$로 가는 경로 중 정점들의 부분집합 $\\{1, 2, \dots, k\\}$에 속하는 정점들로만 이루어진 최단 경로를 반환하는 함수 $f(i, j, k)$를 정의하자.

이때 우리가 구하고자 하는 것은 $\\{1, 2, \dots, N\\}$에 있는 정점들로 이루어진 최단 경로이므로 $f(i, j, N)$라고 할 수 있다.

각각의 정점들의 쌍 $(i, j)$에 대해서 다음의 두 가지 경우로 나누어서 생각할 수 있다.

1. 정점 $k$를 통과하지 않는 경로
2. 정점 $k$를 통과하는 경로

첫 번째 경우, 경로는 $\\{1, 2, \dots, k-1\\}$에 있는 정점들로만 이루어져있으므로 $f(i, j, k-1)$이다.

두 번째 경우, 전체 경로를 $i$에서 $k$까지 가는 경로와 $k$에서 $j$까지 가는 경로로 나눌 수 있다.

$i$에서 $k$를 거쳐 $j$로 가는 최단 경로는 $i$에서 $k$까지의 최단 경로와 $k$에서 $j$까지의 최단 경로를 합친 것이므로 $f(i, k, k-1) + f(k, j, k-1)$이라고 할 수 있다.

그러므로 자연수 $k$에 대해 다음 관계가 성립한다.

\begin{align\*}
f(i, j, k) = min\left(f(i, j, k-1), f(i, k, k-1) + f(k, j, k-1)\right)
\end{align\*}

$f(i, j, 0)$은 $i$에서 $j$까지 가는 경로 중 어떤 정점도 지나지 않는 최단 경로를 의미하므로, $i$와 $j$ 사이의 간선의 가중치임을 알 수 있다.

이를 이용하면 $O(\left\vert V \right\vert^3)$의 시간복잡도로 모든 꼭짓점 쌍 사이의 최단 거리를 구할 수 있다.

> 다익스트라 알고리즘을 모든 꼭짓점에 대해 사용해주어도 모든 꼭짓점 쌍 사이의 최단 거리를 구할 수 있는데, 그 경우 $O(\left\vert V \right\vert \left\vert E \right\vert + \left\vert V \right\vert^2 \log \left\vert E \right\vert)$의 시간복잡도를 가지게 된다.
> 
> 그러므로 간선이 많은 밀집 그래프에서 플로이드-워셜 알고리즘을 사용하면 효율적으로 문제를 해결할 수 있음을 알 수 있다.

---

### [백준] 11404. 플로이드

[백준 11404. 플로이드 문제 링크](https://www.acmicpc.net/problem/11404)

$n$개의 도시와 도시 사이를 이동하는 $m$개의 버스가 있다.

각 버스는 출발 도시, 도착 도시, 비용으로 이루어져있다.

이때, 모든 i, j에 대해서 도시 i에서 j로 가는데 필요한 최소 비용을 출력한다.

**[Solution]**

플로이드-워셜 알고리즘을 구현해보는 연습 문제이다.

```cpp
#include <iostream>
using namespace std;
const int INF = 1000000000; // 정점의 개수 * 가중치의 최댓값 보다 큰 숫자로 설정

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    int map[101][101]; // map[i][j]: i에서 j로 가는 최단 경로의 길이
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            map[i][j] = INF;
    
    int a, b, c;
    while(m--)
    {
        cin >> a >> b >> c;
        map[a][b] = min(map[a][b], c); // 출발 도시와 도착 도시가 동일한 버스가 존재할 수 있으므로 그 중 최솟값을 저장한다.
    }
    
    for (int k = 1; k <= n; k++) // k를 1부터 n까지 증가시키면서 f(i, j, k)를 구해준다.
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                map[i][j] = min(map[i][j], map[i][k] + map[k][j]);
    
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j || map[i][j] == INF) cout << "0 "; // map[i][i]는 i에서 i로 되돌아오는 사이클의 최단 길이를 의미한다.
            else cout << map[i][j] << " ";
        }
        cout << "\n";
    }
}
```

---


플로이드-워셜 알고리즘은 간단한 변형을 통해 $i$에서 $j$까지의 최단 경로 자체를 구할 수 있다.

이를 위해 다음과 같은 2차원 배열을 정의하자.

> `path[i][j]` = 정점 i에서 j로 가는 최단 경로에서 i 다음에 오는 정점의 번호

초기값은 모든 i, j에 대해 `path[i][j] = 0`으로 두고, 정점 i와 j를 연결하는 간선이 있으면 `path[i][j] = j`를 저장한다.

반복문을 수행하면서 `map[i][j] > map[i][k] + map[k][j]`가 성립하면 map을 갱신함과 동시에 `path[i][j] = path[i][k]`로 갱신한다.

위 과정을 마치면 정점 u, v에 대해 `u != v`일 동안 `u = path[u][v]`로 갱신해가면서 u를 출력하면 u에서 v로 가는 경로를 얻을 수 있다.

---

### [백준] 11780. 플로이드 2

[백준 11780. 플로이드 2 문제 링크](https://www.acmicpc.net/problem/11780)

앞선 문제에 더해 각 최단 경로를 출력하는 문제이다.

```cpp
#include <iostream>
#include <vector>
using namespace std;
const int INF = 1000000000;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int n, m;
    cin >> n >> m;
    
    int map[101][101];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            map[i][j] = INF;
    
    int path[101][101];
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            path[i][j] = 0;
    
    int a, b, c;
    while(m--)
    {
        cin >> a >> b >> c;
        if (map[a][b] > c)
        {
            map[a][b] = c;
            path[a][b] = b;
        }
    }
    
    for (int k = 1; k <= n; k++)
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                if (map[i][j] > map[i][k] + map[k][j])
                {
                    map[i][j] = map[i][k] + map[k][j];
                    path[i][j] = path[i][k];
                }
    
    // 최단 경로 길이 출력
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j || map[i][j] == INF) cout << "0 ";
            else cout << map[i][j] << " ";
        }
        cout << "\n";
    }
    
    // 각 최단 경로 출력
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            vector<int> v;
            int u = i;
            if (u == j || path[u][j] == 0) cout << "0\n";
            else
            {
                v.push_back(u);
                while (u != j)
                {
                    u = path[u][j];
                    v.push_back(u);
                }
                cout << v.size();
                for (int k = 0; k < v.size(); k++) cout << " " << v[k];
                cout << "\n";
            }
        }
    }
}
```


<br/>
## Reference

[1] [위키백과, '최단 경로 문제'](https://ko.m.wikipedia.org/wiki/%EC%B5%9C%EB%8B%A8_%EA%B2%BD%EB%A1%9C_%EB%AC%B8%EC%A0%9C)  
[2] [위키백과, '데이크스트라 알고리즘'](https://ko.m.wikipedia.org/wiki/%EB%8D%B0%EC%9D%B4%ED%81%AC%EC%8A%A4%ED%8A%B8%EB%9D%BC_%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98)  
[3] [위키백과, ']()  
[4] [위키백과, '플로이드-워셜 알고리즘'](https://ko.m.wikipedia.org/wiki/%ED%94%8C%EB%A1%9C%EC%9D%B4%EB%93%9C-%EC%9B%8C%EC%85%9C_%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98)  
[3]
