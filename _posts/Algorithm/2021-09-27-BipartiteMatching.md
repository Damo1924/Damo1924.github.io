---
title: "이분 매칭(Bipartite Matching) 알고리즘"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

## 1. Bipartite Matching

정점을 두 개의 집단으로 나누었을 때, 존재하는 모든 간선의 양 끝 정점이 서로 다른 집단에 속하는 그래프를 **이분 그래프(Bipartite Graph)**라고 부른다.

**이분 매칭(Bipartite Matching) 알고리즘**이란, 이분 그래프의 두 집단을 A, B라고 할 때 A 집단이 B 집단을 선택하는 방법에 대한 알고리즘이다.

A 집단이 B 집단을 선택하는 경우의 수는 다양하지만, 그 중 가장 효과적이라고 할 수 있는 것은 가장 많은 정점들이 연결되는 경우이다.

이를 **최대 매칭(Max Matching)**이라고 부르며, 다음과 같은 알고리즘을 사용한다.

---

1) 정점들의 집단을 각각 A, B라고 할 때, A의 정점(A1)을 연결되어 있는 B의 임의의 정점(B1)과 매칭시킨다.

1-1) B1이 매칭되지 않았었다면, 매칭이 추가적으로 이루어졌으므로 지금까지의 최대 매칭 수에 1을 더해준다.

1-2) B1이 이미 매칭되어 있었다면, 기존에 B1와 매칭되었던 정점(A2)을 A2와 연결된 다른 정점(B2)에 매칭시킨다. 이 과정을 재귀적으로 수행해서 최종적으로 모든 매칭이 성공적으로 이루어지면 최대 매칭 수에 1을 더하고, 만약 매칭이 하나라도 불가능해지면 최대 매칭 수를 유지한다.

2) 1번 과정을 A의 모든 정점에 대해서 수행하면 최대 매칭 수를 얻을 수 있다.

---

이해를 돕기 위해서 다음과 같이 A, B에 정점이 3개씩 있는 간단한 예를 들어보았다.

<center><img src="" width = "100%" height = "100%"></center>

위 그림은 다음 과정을 표현한 그림이다.

1. A1을 B1과 매칭
2. A2를 B1과 매칭 - B1가 A1과 이미 매칭되어 있으므로, A1을 B2와 매칭
3. A3를 B2와 매칭 - B2가 A1과 이미 매칭되어 있으므로, A1을 B3와 매칭

이를 코드로 구현하면 다음과 같다.

```cpp
#include <iostream>
#include <vector>
using namespace std;

int N; // A의 정점 개수
int M; // B의 정점 개수

vector<int> graph[maxN]; // 간선 정보 저장 (A -> B)
int match[maxM]; // 매칭 정보 저장 (match[i] = j: B_i와 A_j가 매칭)
bool visited[maxM]; // 방문 정보 저장 (B_i를 방문했었다면 true)

bool dfs (int x) // 매칭을 늘리는데 성공하면 true, 아니면 fasle를 반환하는 함수
{
    for (int i = 0; i < graph[x].size(); i++)
    {
        int y = cow[x][i]; // A_x와 연결된 B의 정점 B_y
        
        if (visited[y]) continue; // 방문했었다면 다음 정점으로
        visited[y] = 1;
        
        if (match[y] == 0 || dfs(match[y])) // B_y가 매칭된 적이 없거나 매칭되었던 정점을 옮기는 것이 가능하다면 true
        {
            match[y] = x; // 매칭 정보 저장
            return true;
        }
    }
    return false; // 매칭을 실패한 경우
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N >> M;
    
    int X, Y;
    for (int i = 1; i <= N; i++)
    {
        cin >> X;
        while (X--)
        {
            cin >> Y;
            graph[i].push_back(Y);
        }
    }
    
    int ans = 0;
    for (int i = 1; i <= N; i++)
    {
        fill(visited, visited + M + 1, 0);
        if (dfs(i)) ans++;
    }
    
    cout << ans;
}
```

일반적으로 이분 그래프에서 최대 매칭 문제는 최대 유량(Maximum Flow) 문제로 바꾸어서 해결한다.

두 정점 집단을 각각 A, B라고 하면 우리는 다음과 같은 그래프를 그릴 수 있다.

<center><img src="https://user-images.githubusercontent.com/88201512/134833829-bda6493a-0293-47bc-9682-7c482d03fbdb.jpg" width="70%" height="70%"></center>

A, B에 속하는 정점 이외에 소스(source)와 싱크(sink)의 역할을 할 두 정점을 추가하고, 소스와 A에 속하는 정점들을 모두 연결하고 싱크와 B에 속하는 정점들을 모두 연결한 뒤, 모든 간선들의 용량을 1로 설정해준다.

이 그래프에 대해 최대 유량을 구하면 그 값은 기존 이분 그래프의 최대 매칭 수와 동일하므로,[이전 포스트](https://damo1924.github.io/algorithm/MaximumFlow/)에서 다룬 알고리즘들을 이용해서 해결할 수 있다.

이 그래프에 대해 DFS/BFS와 Ford-Fulkerson Algorithm을 이용하면 $O(fE)$의 시간복잡도로 해결이 가능하다.

이때 모든 간선의 용량이 1이기 때문에 $f < V$이고, $O(VE)$에 해결이 가능하다는 것을 알 수 있다.

Dinic's Algorithm을 이용한다면 더욱 효과적인 시간복잡도로 최대 매칭을 구할 수 있다.

모든 간선의 용량이 1이라는 사실로부터 차단 용량(blocking flow)를 구하는데 $O(E)$가 필요하다.

차단 용량을 구하는 과정이 $\sqrt{V}$번만 반복되므로 $O(E \sqrt{V})$의 시간복잡도를 가지며, 이를 **Hopcroft-Karp Algorithm**이라고 부른다.


<br/>
## 2. Bipartite Matching

Edmond-Karp Algorithm을 이용해서 이분 매칭 문제를 풀면 다음과 같은 순서대로 경로를 탐색하게 된다. (소스를 S, 싱크를 T라고 하자)

<center><img src=https://user-images.githubusercontent.com/88201512/134845238-a116f396-4976-488c-9940-c9bac49e9bc1.jpg" width="70%" height="70%"></center>

먼저 1번 경로(최단 경로)부터 탐색한 후, 2번 경로처럼 음의 유량을 포함하는 경로들을 탐색하게 된다.
  
이렇게 최대 유량 알고리즘들을 그대로 사용해도 큰 문제는 없지만, 일반적으로 이분 매칭 문제를 해결할 때 사용하는 알고리즘은 따로 있다.

하지만 이렇게 구현하면 다음과 같은 단점들이 나타난다.
  
1. 간선 정보를 저장하는데 많은 메모리를 사용하게 된다.
2. 음의 유량을 고려해주기 위해 추가적인 배열을 필요로 한다.

  

위 그림에서 1, 2번 경로를 탐색한 결과는 A1과 B2, 그리고 A2와 B1이 매칭된 것이 전부이다.

즉, 복잡하게 음의 유량을 고려해주는 것보다는 단순히 A1과 B1을 매칭한 상태에서 A2를 B1과 매칭시켜야한다면 A2를 B1과 매칭시킨 후, A1이 다른 정점에 연결될 수 있는지 확인해보고 매칭시키는 것이 더 효율적이다.

