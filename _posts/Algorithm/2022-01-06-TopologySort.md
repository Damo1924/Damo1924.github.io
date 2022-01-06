---
title: "위상 정렬(Topology Sort)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` 2252 줄 세우기, 1005 ACM Craft

## 1. Topology Sort

위상 정렬(Topology Sort)은 **순서가 정해져있는 작업들**을 어떤 순서로 처리해야하는지 결정할 때 사용하는 알고리즘이다.

순서가 정해져있는 작업이라함은 어떤 작업을 처리하기 위해 그 전에 다른 작업들을 처리해두어야 하는 것을 의미한다.

위상 정렬은 **DAG(Directed Acyclic Graph)**에만 적용이 가능한데, 이는 **사이클이 발생하지 않는 방향 그래프**를 뜻한다.

당연하게도, 주어진 그래프에 사이클이 존재하면 위상 정렬을 수행할 수 없다.

위상 정렬은 스택(stack)이나 큐(queue)를 통해 구현할 수 있는데, 주로 큐를 이용한다.

---

1. 모든 정점을 큐에서 꺼낼 때까지 아래 2~3 과정을 반복한다.
2. 진입 차수가 0인 정점들을 모두 큐에 삽입한다.
3. 큐에서 정점 하나를 꺼내 해당 정점에 연결된 간선들을 모두 제거한다.
4. 큐에서 꺼낸 순서가 처리해야하는 작업의 순서가 된다.

---

이때 어떤 정점의 **진입 차수**란 해당 정점을 도착 정점으로 하는 간선의 개수를 의미한다.

위 과정을 보면, 모든 정점이 한 번씩 큐에 삽입되고 제거되므로 $O(V)$, 모든 간선을 한 번씩 제거하는 과정이 있으므로 $O(E)$의 시간복잡도를 가진다.

따라서 위상 정렬의 시간복잡도는 $O(V + E)$이다.

이제 위상 정렬로 해결할 수 있는 문제들을 살펴보자.

<br/>

## [백준] 2252. 줄 세우기

**[PROBLEM]**

N명의 학생들을 키 순서대로 줄을 세우려고 한다.

그런데 학생들의 키에 대한 정보는 없고, 어떤 두 학생 중 어느 학생이 더 큰지에 대한 정보가 주어진다.

일부 학생들의 키를 비교한 결과가 주어졌을 때, 학생들을 키 순서대로 줄을 세운 결과를 구하여라.

**[INPUT]**

첫째 줄에 학생 수 N과 키를 비교한 횟수 M이 주어진다. ($1 \leq N \leq 32000$, $1 \leq M \leq 100000$)

두 번째 줄부터 M개의 줄에 걸쳐 키를 비교한 두 학생의 번호 A, B가 주어진다.

이는 A학생이 B학생 앞에 서야한다는 의미이다.

**[OUTPUT]**

첫째 줄에 학생들을 키 순서대로 줄을 세운 결과를 출력한다.

답이 여러 가지인 경우에는 아무거나 출력한다.

---

### [Solution] 위상 정렬

위상 정렬을 사용하면 쉽게 답을 구할 수 있다.

위상 정렬의 시간복잡도는 $O(N + M)$이므로 충분히 시간 내에 해결이 가능하다.

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M;

vector<int> graph[32001]; // graph[i]: 학생 i가 더 앞에 와야하는 학생들의 번호

int deg[32001]; // 각 정점의 진입 차수

vector<int> line; // 줄 순서

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    
    int a, b;
    for (int i = 0; i < M; i++)
    {
        cin >> a >> b;
        graph[a].push_back(b);
        deg[b]++;
    }
    
    queue<int> q;
    
    // 진입차수가 0인 정점들을 큐에 삽입
    for (int i = 1; i <= N; i++)
        if (deg[i] == 0) q.push(i);
    
    // 모든 정점들을 큐에서 삭제
    for (int i = 1; i <= N; i++)
    {
        int x = q.front();
        line.push_back(x);
        q.pop();
        
        // x에 연결된 간선을 제거 = 간선에 연결된 다른 정점의 진입차수 -1
        for (int j = 0; j < graph[x].size(); j++)
        {
            int y = graph[x][j];
            deg[y]--;
            if (deg[y] == 0) q.push(y);
        }
    }
    
    for (int i = 0; i < line.size(); i++) cout << line[i] << " ";
}
```

<br/>

## [백준] 1005. ACM Craft

**[PROBLEM]**

ACM Craft라는 게임에서 어떤 건물을 짓기 위해서는 특정 건물들이 이미 지어진 상태여야한다.

건물을 짓는데는 시간이 필요한데, 여러 건물을 동시에 짓는 것도 가능하다.

게임을 승리하기 위해서는 특정 건물을 지어야한다.

각 건물을 짓는데 걸리는 시간과 각 건물을 짓기 위해 미리 지어야하는 건물들이 주어진다.

특정 건물을 지을 때까지 걸리는 최소시간을 구하여라.

**[INPUT]**

첫째 줄에 테스트케이스의 개수 T가 주어진다.

각 테스트케이스는 다음과 같이 주어진다.

첫째 줄에 건물의 개수 N, 건물 간의 건설 순서 규칙의 개수 K가 주어진다. ($2 \leq N \leq 1000$, $1 \leq K \leq 100000$)

둘째 줄에는 각 건물당 건설에 걸리는 시간 $D_1, D_2, \dots, D_N$이 공백을 사이에 두고 주어진다. ($0 \leq D_i \leq 100000$)

셋째 줄부터 K개 줄에 걸쳐 건물의 건설 순서 X, Y가 주어진다.

이는 건물 Y를 짓기 위해서는 건물 X를 미리 지어야한다는 의미이다.

마지막 줄에는 승리하기 위해 주어야 할 건물의 번호 W가 주어진다.

($1 \leq X, Y, W \leq N$)

**[OUTPUT]**

건물 W를 다 지을 때까지 필요한 최소 시간을 출력한다.

모든 테스트케이스는 모든 건물이 건설 가능하도록 주어진다.

---

### [Solution 1] 위상 정렬

마찬가지로 위상 정렬을 이용하면 쉽게 해결할 수 있는 문제이다.

다만, 건물을 동시에 지을 수 있기 때문에 다음과 같은 배열을 추가로 사용하였다.

> `minTime[i]` = i번째 건물을 짓기 시작할 때까지 걸리는 최소 시간

어떤 건물을 짓기 시작할 때까지 걸리는 최소 시간은 해당 건물을 짓기 위해 필요한 다른 건물들을 짓는데까지 걸리는 시간 중 최댓값이다.

그러므로 큐에서 건물 번호를 하나 뽑고 연결된 간선들을 지움과 동시에 간선들을 통해 연결된 다른 정점의 `minTime`을 갱신해주면 된다.

전체 코드는 다음과 같다.

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, K, W, D[1001];

vector<int> graph[1001];

int deg[1001];

int minTime[1001];

bool topologySort() // 위상 정렬
{
    queue<int> q;
    for (int i = 1; i <= N; i++)
        if (deg[i] == 0) q.push(i);
    
    for (int i = 1; i <= N; i++)
    {
        if (q.empty()) return false;
        
        int x = q.front();
        q.pop();
        
        for (int j = 0; j < graph[x].size(); j++)
        {
            int y = graph[x][j];
            minTime[y] = max(minTime[y], minTime[x] + D[x]); // 연결된 정점들에 대해 minTime 갱신
            deg[y]--;
            if (deg[y] == 0) q.push(y);
        }
    }
    return true;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int T;
    cin >> T;
    while (T--)
    {
        // 초기화
        for (int i = 1; i <= 1000; i++)
        {
            graph[i].clear();
            minTime[i] = 0;
        }
        
        // INPUT
        cin >> N >> K;
        for (int i = 1; i <= N; i++) cin >> D[i];
        
        int a, b;
        for (int i = 0; i < K; i++)
        {
            cin >> a >> b;
            graph[a].push_back(b);
            deg[b]++;
        }
        
        topologySort();
        
        cin >> W;
        cout << minTime[W] + D[W] << "\n";
    }
}
```

---

### [Solution 2] 재귀함수 + DP

사실 이 문제는 굳이 위상 정렬을 사용할 필요가 없는 문제이다.

앞 풀이에서 각 건물에 대한 `minTime`을 갱신했던 것처럼 동적계획법을 이용하면 간단히 해결할 수 있다.

아래는 동적계획법을 이용해서 승리하기 위한 건물을 지을 때까지 걸리는 시간을 반환하는 재귀함수이다.

```cpp
int solve (int w)
{
    if (graph[w].empty()) return D[w];
    if (dp[w] != -1) return dp[w];
    
    int res = 0;
    for (int i = 0; i < graph[w].size(); i++)
        res = max(res, solve(graph[w][i]));
    dp[w] = res + D[w];
    return dp[w];
}
```



