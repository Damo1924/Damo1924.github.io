---
title: "최소 신장 트리 (Minimum Spanning Tree, MST)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:    
  - Algorithm
use_math: true
comments: true

---

`Tags`  MST, Minimum Spanning Tree, Prim Algorithm, Kruskal Algorithm

## 1. Spanning Tree

신장 트리(spanning tree)는 연결 그래프의 모든 정점을 최소한의 간선으로 연결하는 부분 그래프이다.

정점의 개수를 $V$라고 하면 ($V-1$)개의 간선으로 모든 정점을 연결해야하며, 사이클이 없어야한다.

어떤 연결 그래프의 신장 트리는 유일하지 않고, BFS와 DFS를 통해 탐색하여 얻을 수 있다.

<br/>

## 2. Minimum Cost Spanning Tree

최소 비용 신장 트리는 간선에 가중치가 있는 가중치 그래프의 신장 트리 중 간선들의 가중치의 합이 최소가 되는 것을 말한다.

최소 비용 신장 트리를 찾는 대표적인 알고리즘으로 **프림 알고리즘(Prim algorithm)**과 **크루스칼 알고리즘(Kruskal algorithm)**이 있다.

이번 포스트에서는 위의 두 알고리즘에 대해 알아보고, 관련 문제도 풀어볼 것이다.

<br/>

## 3. Prim Algorithm

프림 알고리즘은 그리디 알고리즘에 기반하여 최소 비용 신장 트리를 찾는 알고리즘이다.

간단히 설명하면, **하나의 정점에서 시작해서 연결된 간선 중 가중치가 최소인 것을 계속 더해가는 방법**이다.

프림 알고리즘은 다음과 같은 단계를 따른다.

1. 최소 비용 신장 트리를 찾기 시작할 정점을 선택한다. (아무 정점이나 선택해도 된다.)
2. 트리와 아직 방문하지 않은 정점들을 연결하는 간선들 중 가중치가 가장 작은 것을 선택해서 트리에 더해준다.
3. 모든 정점이 트리에 포함될 때까지 2번을 반복한다.

이때 가중치가 가장 작은 간선을 구하기 위해 `priority_queue`를 이용함으로써 시간복잡도를 개선할 수 있다.

> `priority_queue`를 사용하지 않는다면 다음과 같은 배열을 사용해야한다.
> 
> `dist[i]` = 트리의 정점과 정점 i를 연결하는 간선의 가중치의 최솟값
> 
> 매번 위 배열을 순회하면서 최솟값을 찾아 해당 정점을 트리에 더해준다.
> 
> 트리에 새로운 정점을 더할 때마다 새로운 간선들을 탐색하며 `dist` 배열을 최솟값으로 갱신한다.

---

### [백준] 1197. 최소 스패닝 트리

[백준 1197. 최소 스패닝 트리 문제 링크](https://www.acmicpc.net/problem/1197)

그래프가 주어졌을 때 MST의 가중치 합을 출력하는 문제이다.

`priority_queue`를 이용한 Prim Algorithm으로 해결한 코드이다.

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
const int maxV = 10000;
typedef pair<int, int> p;

vector<p> graph[maxV + 1];

bool visited[maxV + 1];

struct compare
{
    bool operator() (p A, p B) { return A.second > B.second; }
};

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int V, E;
    cin >> V >> E;
    
    int a, b, c;
    while (E--)
    {
        cin >> a >> b >> c;
        graph[a].push_back({b, c});
        graph[b].push_back({a, c});
    }
    
    int ans = 0;
    priority_queue<p, vector<p>, compare> pq;
    pq.push({1, 0}); // 탐색을 시작할 정점을 선택: 1
    while (!pq.empty())
    {
        int n = pq.top().first, d = pq.top().second;
        pq.pop();
        
        if (visited[n]) continue; // 이미 트리에 포함된 정점이면 continue
        visited[n] = 1;
        ans += d; // 가중치가 가장 작은 간선의 가중치를 더해준다.
        
        for (int i = 0; i < graph[n].size(); i++) // 새롭게 트리에 더해진 정점 n과 연결된 간선들을 priority queue에 push해준다.
        {
            int N = graph[n][i].first, D = graph[n][i].second;
            if (!visited[N])
            {
                pq.push({N, D});
            }
        }
    }
    
    cout << ans;
}    
```

프림 알고리즘은 각 간선이 한 번씩 priority queue에 삽입되고 제거되므로 $O(E \log E)$의 시간복잡도를 갖는다.

$E \leq V^2$ 이므로 프림 알고리즘의 최종 시간복잡도는 $O(E \log V)$가 된다.

<br/>

## 4. Kruskal Algorithm

크루스칼 알고리즘도 프림 알고리즘처럼 그리디 알고리즘에 기반하여 MST를 찾는 알고리즘이다.

프림 알고리즘은 임의로 선택한 정점에서 시작해서 연결된 간선들 중 가중치가 가장 작은 것을 택하여 트리에 더하는 방식이었다.

크루스칼 알고리즘은 **간선들을 가중치 순서대로 오름차순 정렬한 뒤, 가중치가 작은 간선부터 탐색하는 방법**이다.

이때 중요한 것은 **사이클을 형성하지 않도록 선택**해야한다는 것이다.

크루스칼 알고리즘을 구현하기 위해 [Union-Find Algorithm]()을 이용한다.

> 현재 간선으로 연결된 두 정점이 속한 트리의 루트 노드가 같으면 이미 두 정점은 같은 트리에 속해있으므로 간선을 선택하면 사이클이 생기게 된다.
>
> 그러므로 가중치가 가장 작은 간선에 대해 만약 두 정점이 속한 트리의 루트 노드가 다르다면 Union을 해주면 된다.

---

### [백준] 4386. 별자리 만들기

[백준 4386. 별자리 만들기 문제 링크](https://www.acmicpc.net/problem/4386)

N개의 별이 2차원 평면 위에 놓여 있을 때, 별을 일직선으로 연결하여 별자리를 만들려고 한다.

두 별을 연결하는데에 두 별 사이의 거리만큼의 비용이 들 때, N개의 별을 모두 이어서 하나의 별자리를 만드는 최소 비용을 구하는 문제이다.

좌표를 입력받아 모든 간선의 가중치(두 점 사이의 거리)를 계산하고, 간선들을 가중치에 대해 오름차순으로 정렬한다.

이후 가중치가 작은 것부터 같은 트리에 속하지 않은 두 정점을 `union`해주면서 가중치의 합을 구한다.

전체 코드는 다음과 같다.

```cpp
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>
using namespace std;

double x[100], y[100], edge[100][100]; // 별의 x, y 좌표와 두 별 사이의 거리를 저장

int parent[100]; // Union-Find에 필요한 부모 노드를 저장하는 배열

bool compare (pair<int, int> A, pair<int, int> B) // 간선들을 가중치에 대한 오름차순으로 정렬하기 위한 비교함수
{
    return edge[A.first][A.second] < edge[B.first][B.second];
}

// Union-Find
int find (int x)
{
    if (parent[x] == x) return x;
    return parent[x] = find(parent[x]);
}

bool _union (int x, int y) // union 함수가 true를 반환할 때만 가중치를 더해준다.
{
    x = find(x);
    y = find(y);
    if (x == y) return false;
    parent[x] = y;
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N;
    cin >> N;
    
    vector<pair<int, int>> vec;
    vec.reserve(10000);
    for (int i = 0; i < N; i++) cin >> x[i] >> y[i];
    for (int i = 0; i < N; i++)
    {
        for (int j = i + 1; j < N; j++)
        {
            vec.push_back({i, j});
            edge[i][j] = sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
        }
    }
    
    sort(vec.begin(), vec.end(), compare);
    
    for (int i = 0; i < N; i++) parent[i] = i;
    double ans = 0;
    for (int i = 0; i < vec.size(); i++)
    {
        if (_union(vec[i].first, vec[i].second))
            ans += edge[vec[i].first][vec[i].second];
    }
    cout << ans;
}
```

간선들을 정렬하는데 $O(E \log E)$, 그리고 각 간선에 대해 'union' 해주는데 $O(1)$이 걸린다.

따라서 Kruskal Algorithm의 시간복잡도는 $O(E \log E) + O(1) \times E$가 되고, 이를 정리하면 $O(E \log V)$를 얻을 수 있다.

이는 앞서 살펴본 Prim Algorithm과 동일하다.

> `union` 작업이 $O(1)$의 시간복잡도를 가지기 위해서는 Weighted Union with Path Compression을 사용해야한다.
> 
> 위 코드는 단순히 Path Compression만을 적용한 것으로, 트리의 높이에 비례하는 시간복잡도를 갖는다.



