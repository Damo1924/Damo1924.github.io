---
title: "최대 유량(Maximum Flow) 문제"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

## 1. Maximum Flow Problem

최대 유량(Maximum Flow) 문제는 그래프의 두 지점 사이를 지날 수 있는 최대 유량을 구하는 문제이다.

총 세 개의 노드 A, B, C로 이루어진 그래프가 있다.

이때 A와 B 사이의 간선은 최대 10만큼의 유량이 통과할 수 있고, B와 C 사이의 간선은 최대 5만큼의 유량이 통과할 수 있으며, A와 C는 연결되어 있지 않다.

그렇다면 A에서 C로 흐를 수 있는 최대 유량을 얼마일까?

어렵지 않게 5라고 답할 수 있다.

이처럼 그래프의 각 간선이 통과할 수 있는 최대 유량을 가질 때, 어떤 시작 지점부터 도착 지점까지 흐를 수 있는 최대 유량을 구하는 문제를 최대 유량 문제라고 한다.

다음은 최대 유량 문제에서 사용하는 용어들이다.

- **유량 네트워크(Flow network)**: 각 간선에 용량이 주어진 그래프
- **소스(source)**: 시작 지점
- **싱크(sink)**: 도착 지점
- **용량(capacity)**: 각 간선에 대해서 흐를 수 있는 최대 유량

이때 **유량(flow)**이란, 다음 조건을 만족하는 값을 의미한다.

- **용량의 제한(capacity constraint)**: 유량은 그 간선의 용량을 초과할 수 없다.
- **유량의 보존(conservation of flows)**: 소스와 싱크를 제외한 정점에는 들어오는 유량와 나가는 유량이 동일하다.

그렇다면, 이를 해결할 수 있는 알고리즘에 대해 알아보자.


<br/>
## 2. Ford-Fulkerson Algorithm

포드-풀커슨 알고리즘은 다음과 같다.

---

1) 소스에서 싱크까지 모든 간선의 용량이 0보다 큰 경로를 구한다.

> 이러한 경로를 **증가 경로**라고 부른다.

2) 위에서 찾은 경로를 지날 수 있는 최대 용량(f)을 구한다.

3) 해당 간선들을 지나는 유량에 f를 더한다.

4) 해당 간선들의 반대 방향 간선들을 지나는 유량에 f를 뺀다.

5) 위 과정(1 ~ 4)를 더 이상 증가 경로가 존재하지 않을 때까지 반복한다.

---

이 알고리즘은 증가 경로를 찾는 방법에 대해 제시하지 않았다.

그러므로 대표적인 그래프 탐색 방법인 DFS 또는 BFS를 통해 증가 경로를 찾으면 되는데, 어느 방법이든 $O(f \cdot E)$의 시간 복잡도를 갖는다.

이때 $f$는 유량의 총 크기이다.

그런데 증가 경로를 BFS로 찾는 경우, 시간 복잡도가 $O(VE^2)$임이 증명되었고, 따라서 최대 유량 문제를 풀 때는 일반적으로 BFS를 사용한다.

BFS를 사용하는 알고리즘을 Edmonds-Karp Algorithm이라고 부른다.


<br/>
## 3. Edmonds-Karp Algorithm & Implementation

에드몬드-카프 알고리즘은 포드-풀커슨 알고리즘에서 증가 경로를 찾는 방법만을 제시한 것이므로 알고리즘 자체는 동일하지만, 이번에는 코드를 구현하는 관점에서 알고리즘을 정리해보았다.

---

1) BFS를 통해 시작 지점에서 도착 지점까지 이어지는 경로를 하나 찾고, 배열을 하나 선언하여 경로를 저장한다.

2) 위에서 찾은 경로를 따라가면서 해당 경로로 지나갈 수 있는 최대 유량을 구한다.

3) 경로를 따라가면서 각 간선을 통과하는 유량에 앞에서 구한 값을 더해준다. 이때, 각 간선의 반대 방향으로 음의 유량이 지난다고 생각할 수 있으므로 각 간선의 반대 방향 유량에 앞에서 구한 값을 빼준다.

> 예를 들어 A에서 B로 가는 간선에 10만큼의 유량이 흐른다면 B에서 A로 가는 유량은 -10이라고 할 수 있다.
>
> 이를 고려해주어야 하는 이유는 B에서 A로 가는 경로가 존재할 수 있기 때문이다.
>
> B에서 A 방향으로 가는 경로를 발견했을 때, 해당 간선을 통과할 수 있는 최대 유량은 10 - 0 = 10이 아니라 10 - (-10) = 20이다.
>
> 즉, A에서 B로 가는 유량 10, B에서 A로 가는 유량 20을 더하면 B에서 A로 10만큼의 유량이 흐르는 것이므로 용량을 초과하지 않으면서 두 경로를 최대한으로 이용할 수 있게 된다.

4) 결과값에 위에서 구한 유량을 더해준다.

5) 위 과정(1 ~ 4)를 더 이상 시작 지점에서 끝 지점으로 가는 새로운 경로가 없을 때까지 반복한다.

---

앞에서 언급했듯이, 에드몬드-카프 알고리즘의 시간복잡도는 $O(VE^2)$으로 알려져 있다.

이를 증명해보도록 하자.

---

**[proof]**

BFS를 이용해서 소스에서 싱크까지의 경로를 찾는데 $O(E)$이므로 위 사실을 증명하기 위해서는 증가 경로를 많아야 $VE$ 번 찾는다는 사실을 보이면 된다.

어떤 그래프의 최단 경로의 길이를 $D$라고 하자.

최단 경로를 하나 탐색하면 적어도 하나의 간선은 해당 간선에 흐르는 유량이 용량과 같아지게 되며, 더 이상 최단 경로가 $D$인 경로 중에는 해당 간선을 통과하는 경로가 존재하지 않게 된다.

만약 길이가 $D$이면서 해당 간선의 반대 방향으로 지나는 경로가 존재한다고 가정하면, $D-1$인 경로가 존재하게 되어 최단 경로가 $D$라는 전제에 모순이다.

그러므로 최단 경로의 길이가 $D$인 동안은 최대 $E$번 증가 경로를 찾게 된다는 것을 알 수 있다.

최단 경로의 길이는 1부터 $V-1$까지 가능하므로 위의 과정이 반복되는 횟수는 $VE$ 보다 작다고 할 수 있다.

따라서 에드몬드-카프 알고리즘의 시간복잡도는 $O(VE^2)$이다.

**Q.E.D**

---

이를 이용해서 간단한 문제 하나를 풀어보도록 하자.

---

### [백준] 6086. 최대 유량

[백준 6086. 최대 유량 문제 링크](https://www.acmicpc.net/problem/6086)

첫 줄에 간선의 개수 N($1 \leq N \leq 700$)이 주어지고 둘째 줄부터 각 간선의 정보가 주어진다.

각 노드의 이름은 알파벳 소문자(a ~ z)와 대문자(A ~ Z)이며, 간선의 용량은 1000 이하의 자연수이다.

이때 A에서 Z까지의 최대 유량을 구하는 문제로, Edward-Karp Algorithm을 이용하면 시간 내에 해결할 수 있다.

Edmond-Karp Algorithm을 이용해서 최대 유량을 반환하는 함수 `maxFlow()`와 노드의 이름이 문자로 주어지므로 이를 0 ~ 51의 정수로 변환해주는 `index()` 함수를 구현하였다.

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int Max = 52, Inf = 1000000000;

int n;

int p[Max]; // path
int c[Max][Max]; // capacity
int f[Max][Max]; // flow

vector<int> g[Max]; // graph

int maxFlow(int start, int end)
{
    int ans = 0;

    while (1)
    {
        fill(p, p + Max, -1); // 경로를 -1로 초기화

        queue<int> q;
        q.push(start);
        while (!q.empty() && p[end] == -1)
        {
            int x = q.front();
            q.pop();
            for (int i = 0; i < g[x].size(); i++)
            {
                int y = g[x][i];

                // 방문하지 않은 노드 중 용량이 남은 경우
                if (c[x][y] - f[x][y] > 0 && p[y] == -1)
                {
                    q.push(y);
                    p[y] = x; // 경로 저장
                }
            }
        }

        if (p[end] == -1) break; // 더 이상 도착 지점에 도달하는 경로가 없는 경우

        int flow = Inf; // 찾은 경로를 지나는 최대 유량
        for (int i = end; i != start; i = p[i])
            flow = min(flow, c[p[i]][i] - f[p[i]][i]);

        for (int i = end; i != start; i = p[i])
        {
            f[p[i]][i] += flow;
            f[i][p[i]] -= flow;
        }
        ans += flow;
    }

    return ans;
}

int index(char c)
{
    if (c >= 'a') return c - 71;
    else return c - 65;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n;
    for (int i = 0; i < n; i++)
    {
        char a, b;
        int tmp, A, B;
        cin >> a >> b >> tmp;
        A = index(a);
        B = index(b);

        g[A].push_back(B);
        g[B].push_back(A);
        c[A][B] += tmp;
        c[B][A] += tmp;
    }

    cout << maxFlow(0, 25);
}
```


<br/>
## 4. Dinic's Algorithm

Dinic's Algorithm은 $O(V^2E)$의 시간복잡도는 갖는 최대 유량을 구하는 알고리즘이다.

먼저, Dinic's Algorithm을 이해하기 위해서는 다음 두 가지 개념에 대해 알아야한다.

- **레벨 그래프(Level Graph)**: 그래프의 모든 정점에 레벨을 매긴 그래프
- **차단 유량(Blocking Flow)**: 레벨 그래프에서 레벨이 높은 정점에서 레벨이 낮은 정점으로 유량이 흐르지 못할 때의 최대 유량

레벨 그래프는 소스의 레벨을 0으로 두고, 레벨 i인 정점과 인접한 정점들 중 아직 레벨을 부여받지 않은 정점의 레벨을 i+1로 매기는 과정을 반복함으로써 만들 수 있다.

즉, 최단 경로의 관점에서 이해하면 각 정점의 레벨은 소스로부터 레벨까지의 최단 경로의 길이라고 생각할 수 있다.

같은 관점에서 차단 유량은 최단 경로들을 지나는 모든 유량을 더한 것이라고 이해할 수 있다.

이를 바탕으로 Dinic's Algorithm에 대해 알아보자.

---

1) BFS를 통해 그래프의 각 정점에 레벨을 부여한다.

2) DFS를 통해 각 최단 경로를 순회하면서 차단 유량을 구한다.

3) 위 과정(1 ~ 2)을 BFS를 통해 싱크에 레벨을 부여하지 못할 때까지 반복한다.

---

Edmond-Karp Algorithm에서는 BFS를 통해 최단 경로를 발견하면 해당 경로를 지날 수 있는 유량을 더해주었다면, Dinic's Algorithm에서는 DFS를 이용해서 최단 경로를 탐색해서 유량을 구한다는 차이점이 있다.

그렇기 때문에 Edmond-Karp Algorithm은 경로를 저장하기 위한 배열을 사용했지만, Dinic's Algorithm을 구현하기 위해서는 경로를 기억하는 배열 대신 각 정점의 레벨을 저장해둘 배열을 선언해서 사용하게 된다.

다음으로 Dinic's Algorithm이 $O(V^2E)$의 시간복잡도를 가진다는 사실을 증명해보자.

---

**[proof]**

먼저, BFS를 통해 각 정점에 레벨을 부여하는 과정의 시간복잡도는 $O(E)$이다.

그리고 Edmond-Karp Algorithm의 시간복잡도를 증명할 때와 마찬가지로 한 최단 경로를 지날 수 있는 유량을 탐색해주고 나면, 적어도 하나의 간선은 용량을 꽉 채우게 되고, 해당 간선을 지나는 최단 경로는 존재하지 않는다는 사실을 이용하면 차단 유량을 구하는 과정의 시간복잡도는 $O(VE)$이다.

즉, 각 최단 경로 길이마다 $O(VE + E) = O(VE)$의 시간복잡도를 갖는다.

최단 경로의 길이는 1부터 $V-1$까지 가능하므로 Dinic's Algorithm의 시간복잡도는 $O(V^2E)$임을 알 수 있다.

**Q.E.D**

---

Dinic's Algorithm은 **모든 간선의 용량이 1인 경우** 매우 강력하다는 특징을 가지고 있다.

이 경우, 무려 $O(\min \\{ V^{2/3}, E^{1/2} \\} E)$의 시간복잡도를 가진다.

---

**[proof]**

모든 간선의 용량이 1이므로 DFS로 각 경로마다 지날 수 있는 용량이 항상 1로 고정된다.

그러므로 각 최소 경로 길이마다 차단 용량을 구하는 작업이 $O(E)$ 내에 가능하다는 것을 알 수 있다.

이제 차단 용량을 구하는 과정의 반복 횟수가 $O(V^{2/3})$와 $O(E^{1/2})$를 초과하지 않는다는 사실을 보이면 된다.

이는 Max-Flow Min-Cut Theorem을 이용해서 증명이 가능하다.

먼저, 다음 두 개의 Lemma를 증명하자.

**Lemma 1.** 소스와 싱크 사이의 최단 거리가 $E^{1/2}$ 이상인 네트워크에서 $E^{1/2}$ 이하의 크기를 갖는 Cut이 존재한다.

> **[proof]**
> 
> 소스와의 거리가 $D$인 정점과 소스와의 거리가 $D+1$인 정점을 연결하는 간선들의 집합을 $S(D)$라고 정의하자.
> 
> $0 \leq i \leq E^{1/2}$를 만족하는 자연수 $i$에 대해서 집합 $S(i)$에 있는 간선들을 제거하면 소스와 싱크의 연결이 끊기므로 각각의 $S(i)$는 Cut이다.
> 
> 집합 $S(i)$에 있는 간선들의 용량의 합을 $C_i$라고 하자.
> 
> $0 \leq i \leq E^{1/2}$를 만족하는 모든 자연수 $i$에 대해서 $C_i > E^{1/2}$가 성립한다고 가정하면, $\sum_i C_i > E$가 성립한다.
> 
> 그러나 모든 간선의 용량이 1이므로 간선의 용량을 모두 더해도 $E$보다 클 수는 없기 때문에 모순이다.
> 
> 즉, 귀류법에 의해 $C_i \leq E^{1/2}$를 만족하는 $i$가 적어도 하나 존재한다.
> 
> $\therefore$ $E^{1/2}$ 이하의 크기를 갖는 Cut이 반드시 존재한다.

**Lemma 2.** 소스와 싱크 사이의 최단 거리가 $2V^{2/3}$ 이상인 네트워크에서 $V^{2/3}$ 이하의 크기를 갖는 Cut이 존재한다.

> **[proof]**
> 
> 소스와의 거리가 $D$인 정점들의 집합을 $P(D)$라고 정의하자.
> 
> $0 \leq i \leq 2V^{2/3}$를 만족하는 자연수 $i$에 대해서 집합 $P(i)$와 $P(i+1)$을 연결하는 간선들은 하나의 Cut을 이루고, 그 크기를 $C_i$라고 하자.
> 
> 집합 $P(i)$와 $P(i+1)$을 연결하는 간선은 최대 $n(P(i)) \times n(P(i+1))$ 개이므로, $C_i \leq n(P(i))n(P(i+1))$가 성립한다.
> 
> 이때 $0 \leq i \leq 2V^{2/3}$를 만족하는 자연수 $i$에 대해서 $n(P(i)) \times n(P(i+1)) > V^{2/3}$가 성립한다고 가정하자.
> 
> 산술평균과 기하평균의 관계로부터 $a, b$가 음이 아닌 실수일 때 $\sqrt{ab} \leq \frac{a + b}{2}$가 성립한다.
> 
> 이를 이용하면 $n(P(i)), n(P(i+1))$는 음이 아닌 정수이므로 $\sqrt{n(P(i))n(P(i+1))} \leq \frac{n(P(i)) + n(P(i+1))}{2}$가 성립함을 알 수 있고, 다음을 얻을 수 있다.
> 
> $V^{2/3} < n(P(i)) \times n(P(i+1)) \leq \frac{(n(P(i)) + n(P(i+1)))^2}{4}$
> 
> $2V^{1/3} < n(P(i)) + n(P(i+1))$
> 
> 위 식을 $0 \leq i \leq 2V^{2/3}$를 만족하는 자연수 $i$에 대해서 모두 더하면 다음과 같다.
> 
> $4V < \sum_i \left(n(P(i)) + n(P(i+1)) \right) < 2 \sum_i n(P(i))$
> 
> 즉, 모든 정점의 개수의 합이 $2V$보다 커지게 되므로 모순이다.
> 
> 따라서 귀류법에 의해 $n(P(i)) \times n(P(i+1)) \leq V^{2/3}$를 만족하는 $i$가 적어도 하나 존재한다.
> 
> $\therefore$ $V^{2/3}$ 이하의 크기를 갖는 Cut이 반드시 존재한다.

Max-Flow Min-Cut Theorem에 의해 Max-Flow의 크기와 Min-Cut의 크기는 동일하므로 앞서 증명한 Lemma에 의해 다음과 같이 쓸 수 있다.

> Maxinum Flow의 값은 항상 $E^{1/2}$ 이하이며, 또한 항상 $V^{2/3}$ 이하이다.

그러므로 차단 용량을 구하는 횟수는 항상 $\min \\{ V^{2/3}, E^{1/2} \\}$ 이하이다.

$\therefore$ Dinic's Algorithm의 시간복잡도는 $O(\min \\{ V^{2/3}, E^{1/2} \\} E)$이다.

**Q.E.D**

---

마지막으로 Dinic's Algorithm을 사용해서 최대 유량 문제를 해결해보자.

---

### [백준] 2367. 파티

[백준 2367. 파티 문제 링크](https://www.acmicpc.net/problem/2367)

N명의 사람이 파티를 하기 위해 D 종류의 음식을 준비하려고 한다.

각 사람은 자신이 할 수 있는 요리 중 K개의 요리를 각각 한 접시씩 가져올 수 있다.

음식이 남지 않게 하기 위해 각 음식마다 준비해야하는 접시의 최댓값을 정해두었을 때, 파티에 준비될 수 있는 접시의 최대 개수를 구하는 문제이다.

최대 유량 문제들은 직접적으로 그 형태가 드러나기보다는 이처럼 최대 유량 문제인지를 숨기는 경우가 많다.

먼저, 최대 유량 문제로 변환하기 위해 적절한 그래프 하나를 그려보자.

소스와 싱크, 그리고 N명의 사람들과 D 종류의 음식에 해당하는 정점으로 이루어진 그래프를 다음과 같이 그릴 수 있다.

<img src="https://user-images.githubusercontent.com/88201512/134772866-340e8b4f-a538-42cf-9f52-84a14d763333.jpg" width="80%" height="80%">

이 그래프를 최대 유량 문제에 적용할 때 주의할 점은 각 간선은 정해진 방향으로만 흐를 수 있다는 것이다.

그렇기 때문에 한 쪽 방향으로만 용량을 입력해주어야 한다.

전체 코드는 다음과 같다.

```cpp
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int n, d, k, ans;

vector<int> graph[302]; // 0: source, 1 ~ 200: 사람, 201 ~ 300: 요리, 301: sink
int c[302][302]; // capacity
int f[302][302]; // flow
int level[302]; // bfs를 통해 구할 각 정점의 레벨
int path[302]; // dfs 경로

bool bfs() // 각 정점에 level 부여하기
{
    fill(level, level + 302, -1);

    level[0] = 0;
    queue<int> q;
    q.push(0);
    while (!q.empty())
    {
        int x = q.front();
        q.pop();
        for (int i = 0; i < graph[x].size(); i++)
        {
            int y = graph[x][i];
            if (c[x][y] - f[x][y] > 0 && level[y] == -1)
            {
                level[y] = level[x] + 1;
                q.push(y);
            }
        }
    }
    return level[301] != -1;
}

bool dfs(int x, int flow) // level을 통해 최단 경로 탐색
{
    if (x == 301)
    {
        for (int i = x; i != 0; i = path[i])
        {
            f[path[i]][i] += flow;
            f[i][path[i]] -= flow;
        }
        ans += flow;
        return true;
    }

    for (int i = 0; i < graph[x].size(); i++)
    {
        int y = graph[x][i];
        if (c[x][y] - f[x][y] > 0 && level[y] == level[x] + 1)
        {
            path[y] = x;
            if (dfs(y, min(flow, c[x][y] - f[x][y]))) return true;
        }
    }
    return false;
}

void maxDish()
{
    while (bfs())
    {
        while (1)
        {
            if (!dfs(0, 1000000000)) break;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> n >> k >> d;
    for (int i = 1; i <= d; i++)
    {
        int tmp;
        cin >> tmp; // 각 요리의 최대 접시 수
        c[200 + i][301] = tmp;
        graph[200 + i].push_back(301);
        graph[301].push_back(200 + i);
    }

    for (int i = 1; i <= n; i++)
    {
        c[0][i] = k; // 각 사람이 가져올 수 있는 접시의 수는 k
        graph[0].push_back(i);
        graph[i].push_back(0);

        int z;
        cin >> z; // i번째 사람이 할 수 있는 요리의 종류
        for (int j = 0; j < z; j++)
        {
            int food;
            cin >> food; // i번째 사람이 할 수 있는 요리의 종류
            graph[i].push_back(200 + food);
            graph[200 + food].push_back(i);
            c[i][200 + food] = 1; // 각 사람은 한 요리당 접시 하나만 가져갈 수 있음
        }
    }

    maxDish();
    cout << ans;
}
```

## References
[1] [구사과, '유량 관련 알고리즘 증명'](https://koosaga.com/133)  
[2] [WIKIPEDIA, 'Dinic's algorithm'](https://en.m.wikipedia.org/wiki/Dinic%27s_algorithm)  
