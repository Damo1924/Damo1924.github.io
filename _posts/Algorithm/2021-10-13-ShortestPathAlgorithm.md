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


<br/>
## 2. Dijkstra Algorithm


<br/>
## 3. Bellman-Ford Algorithm


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

위 아이디어를 잘 이해하고 있다면 구현은 굉장히 간단하다.

---

### [백준] 11404. 플로이드

$n$개의 도시와 도시 사이를 이동하는 $m$개의 버스가 있다.

각 버스는 출발 도시, 도착 도시, 비용으로 이루어져있다.

이때, 모든 i, j에 대해서 도시 i에서 j로 가는데 필요한 최소 비용을 출력한다.

**[Solution}**

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

### 최단 경로 재현하기

플로이드-워셜 알고리즘은 간단한 변형을 통해 $i$에서 $j$까지의 최단 경로 자체를 구할 수 있다.

이를 위해 다음과 같은 2차원 배열을 정의하자.

> `path[i][j]` = 정점 i에서 j로 가는 최단 경로에서 i 다음에 오는 정점의 번호

초기값은 모든 i, j에 대해 `path[i][j] = 0`으로 두고, 정점 i와 j를 연결하는 간선이 있으면 `path[i][j] = j`를 저장한다.

반복문을 수행하면서 `map[i][j] > map[i][k] + map[k][j]`가 성립하면 map을 갱신함과 동시에 `path[i][j] = path[i][k]`로 갱신한다.

위 과정을 마치면 정점 u, v에 대해 `u != v`일 동안 `u = path[u][v]`로 갱신해가면서 u를 출력하면 u에서 v로 가는 경로를 얻을 수 있다.

다음은 위 문제에서 임의의 u, v에 대해 u에서 v로 가는 최단 경로를 출력하는 코드를 추가한 코드이다.

```cpp
#include <iostream>
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
    
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (i == j || map[i][j] == INF) cout << "0 ";
            else cout << map[i][j] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
    
    int u = 2, v = 1;
    if (path[u][v] == 0) cout << "No Path!";
    else
    {
        cout << u << " ";
        while (u != v)
        {
            u = path[u][v];
            cout << u << " ";
        }
    }
}
```


<br/>
## Reference

[1] [위키백과, '최단 경로 문제'](https://ko.m.wikipedia.org/wiki/%EC%B5%9C%EB%8B%A8_%EA%B2%BD%EB%A1%9C_%EB%AC%B8%EC%A0%9C)  
[2] [위키백과, '플로이드-워셜 알고리즘'](https://ko.m.wikipedia.org/wiki/%ED%94%8C%EB%A1%9C%EC%9D%B4%EB%93%9C-%EC%9B%8C%EC%85%9C_%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98)  
[3]
