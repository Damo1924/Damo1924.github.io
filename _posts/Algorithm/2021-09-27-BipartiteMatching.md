---
title: "이분 매칭(Bipartite Matching) 알고리즘과 이분 그래프에서의 확장"
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
    for (int i = 1; i <= N; i++) // A의 모든 정점에 대해 반복
    {
        fill(visited, visited + M + 1, 0);
        if (dfs(i)) ans++; // 매칭 성공하면 +1
    }
    
    cout << ans;
}
```

### 관련 문제들

[백준 2188. 축사 배정](https://www.acmicpc.net/problem/2188)

매우 직관적인 이분 매칭 문제이므로 위 코드를 그대로 이용하면 해결할 수 있다.

[백준 1733. 등번호](https://www.acmicpc.net/problem/1733)

이 문제는 조금 특수한 문제로, 정점의 개수가 1,000,000까지 주어질 수 있기 때문에 위 방법을 그대로 사용하면 시간초과가 발생한다.

이처럼 정점의 개수가 많은 경우에는 `visited` 배열을 초기화하는데 매우 많은 시간이 소요되므로 초기화하지 않으면서 방문 여부를 체크할 수 있는 방법을 생각해야 한다.

자세한 풀이는 [이 포스트](https://damo1924.github.io/ps/BAEKJOON-1733/)에서 다루고 있다.


<br/>
## 2. Changing into Maximum Flow Problem

이분 그래프에서 최대 매칭 문제는 최대 유량(Maximum Flow) 문제로 바꾸어서 해결할 수도 있다.

두 정점 집단을 각각 A, B라고 하면 우리는 다음과 같은 그래프를 그릴 수 있다.

<center><img src="https://user-images.githubusercontent.com/88201512/134833829-bda6493a-0293-47bc-9682-7c482d03fbdb.jpg" width="70%" height="70%"></center>

A, B에 속하는 정점 이외에 소스(source)와 싱크(sink)의 역할을 할 두 정점을 추가하고, 소스와 A에 속하는 정점들을 모두 연결하고 싱크와 B에 속하는 정점들을 모두 연결한 뒤, 모든 간선들의 용량을 1로 설정해준다.

이 그래프에 대해 최대 유량을 구하면 그 값은 기존 이분 그래프의 최대 매칭 수와 동일하므로,[이전 포스트](https://damo1924.github.io/algorithm/MaximumFlow/)에서 다룬 알고리즘들을 이용해서 해결할 수 있다.

---

### Using Ford-Fulkerson Algorithm

이 그래프에 대해 DFS/BFS와 Ford-Fulkerson Algorithm을 이용하면 $O(fE)$의 시간복잡도로 해결이 가능하다.

이때 모든 간선의 용량이 1이기 때문에 $f < V$이고, $O(VE)$에 해결이 가능하다는 것을 알 수 있다.

Edmond-Karp Algorithm을 이용해서 이분 매칭 문제를 풀면 다음과 같은 순서대로 경로를 탐색하게 된다. (소스를 S, 싱크를 T라고 하자)

<center><img src="https://user-images.githubusercontent.com/88201512/134845238-a116f396-4976-488c-9940-c9bac49e9bc1.jpg" width="70%" height="70%"></center>

먼저 1번 경로(최단 경로)부터 탐색한 후, 2번 경로처럼 음의 유량을 포함하는 경로들을 탐색하게 된다.
  
이렇게 최대 유량 알고리즘들을 그대로 사용해도 큰 문제는 없지만, 앞서 설명한 DFS를 이용한 알고리즘에 비해 다음과 같은 단점들이 존재한다.
  
1. 간선 정보를 저장하는데 많은 메모리를 사용하게 된다.
2. 음의 유량을 고려해주기 위해 추가적인 배열을 필요로 한다.

코드의 길이나 시간적인 관점에서도 뚜렷한 강점이 없어 주로 앞서 설명한 방법을 통해 문제를 해결하는 편이다.

---

### Using Dinic's Algorithm

Dinic's Algorithm을 이용한다면 더 효과적인 시간복잡도로 최대 매칭을 구할 수 있다.

모든 간선의 용량이 1이라는 사실로부터 차단 용량(blocking flow)를 구하는데 $O(E)$가 필요하다.

차단 용량을 구하는 과정이 $\sqrt{V}$번만 반복되므로 $O(E \sqrt{V})$의 시간복잡도를 가지며, 이를 **Hopcroft-Karp Algorithm**이라고 부른다.


<br/>
## 3. Minimum Vertex Cover & Konig's Theorem

**Vertec Cover**란 다음 조건을 만족하는 정점들의 부분집합을 의미한다.

> **그래프의 모든 간선은 Vertex Cover의 정점 중 하나 이상에 인접해야 한다.**

이 중 크기가 가장 작은 부분집합을 **Minimum Vertex Cover**라고 부른다.

일반적인 그래프의 Minimum Vertex Cover는 다항시간 내에 풀 수 없다고 알려져 있다.

하지만 이분 그래프에서는 **쾨닉의 정리(Konig's Theorem)**을 이용하여 이를 해결할 수 있는데, 이에 대해 알아보도록 하자.

---

### Konig's Theorem

> **이분 그래프의 Minimum Vertex Cover의 크기와 Maximum Matching의 크기는 동일하다.**

증명을 하기 전에, 증명에 필요한 몇 가지 개념들에 대해 정리해보았다.

- **Matching**\: 어느 두 간선도 끝점을 공유하지 않는 그래프에 있는 간선들의 부분집합으로, 어떤 정점이 매칭되었다는 것은 matching에 있는 간선들 중에 해당 정점을 끝점으로 하는 간선이 존재한다는 것을 의미한다.

- **Alternaing path**\: 그래프 상에 존재하는 경로들 중 matching에 포함되는 간선들과 matching에 포함되지 않는 간선들이 번갈아 나타나는 경로

- **Augmenting path**\: 양쪽 끝 정점이 모두 매칭되지 않은 alternating path

---

**proof**

**Lemma 1.** 이분 그래프에서 Minimum Vertex Cover의 크기는 Maximum Matching의 크기보다 크거나 같다.

> Maximum Matching보다 작은 Vertex Cover가 존재한다고 가정하자.
> 
> 그러면 적어도 하나의 매칭은 해당 매칭의 두 정점이 모두 Vertex Cover에 속하지 않을 것이다.
> 
> $\therefore$ Maximum Matching의 크기 $\leq$ Minimum Vertex Cover의 크기 **Q.E.D**

Lemma 1에 의해 만약 maximum matching의 크기와 같은 크기를 갖는 vertex cover가 존재한다면, 그것이 minimum vertex cover가 된다는 것을 알 수 있다.

**Lemma 2 (Berge's lemma).** Maximum matching들은 augmenting path를 가지지 않는다.

> Augmenting path를 가지는 matching이 존재한다고 가정하자.
> 
> Augmenting path에 있는 각 간선들에 대해, matching에 포함되면 matching에서 제거하고 matching에 포함되지 않으면 matching에 추가하는 작업을 수행하자.
> 
> Augmenting path는 alternating path의 특징을 만족하므로, 위 과정을 거쳐도 matching에는 여전히 끝점을 공유하는 간선이 존재하지 않게 된다.
> 
> 그런데 Augmenting path는 양끝 간선이 모두 matching에 포함되지 않으므로 우리는 기존 matching보다 크기가 1 큰 matching을 얻게 된다.
> 
> $\therefore$ Augmenting path를 가지는 matching은 maximum matching이 아니다.
> 
> 참인 명제의 대우도 참. **Q.E.D**

다음과 같이 정의하자.

$G(V, E)$: bipartite graph (V: vertices, E: edges)

이분그래프 $G$의 두 정점들의 부분집합을 각각 $X, Y$라고 한다.

$M$: Maximum matching of $G$

$U$: $X$의 정점들 중 $M$에 대해 매칭되지 않은 정점들의 집합

$Z$: $U$의 정점들로부터 $M$에 대한 alternating path를 통해 접근이 가능한 정점들의 집합

$S = Z \cap X$, $T = Z \cap Y$

$N(S)$: $S$의 정점들에 인접한 정점들의 집합

**Lemma 3.** $U$의 정점에서 $S$의 정점까지의 alternating path는 $M$에 포함된 간선으로 끝나고, $U$의 정점에서 $T$의 정점까지의 alternating path는 $M$에 포함되지 않은 간선으로 끝난다.

> $U$의 정점에서 시작하는 alternating path의 첫 번째 간선은 $M$에 포함되지 않는다.
> 
> $X$의 임의의 정점에서 $X$의 다른 정점까지의 경로의 길이는 짝수이고, $X$의 임의의 정점에서 $Y$의 어떤 정점까지의 경로의 길이는 홀수이다.
> 
> 이로부터 $U$부터 $S$까지의 경로의 길이는 짝수이고, $T$까지의 경로의 길이는 홀수임을 알 수 있다.
> 
> 경로의 길이가 짝수면 첫 번째와 마지막 간선의 $M$에 대한 포함관계가 다르고, 경로의 길이가 홀수면 동일한 포함관계를 갖기 때문에 명제가 증명된다. **Q.E.D**

**Lemma 4.** $N(S) = T$

> $U$의 정점부터 정점 $u \in T$까지의 alternating path에서 $u$의 바로 전 정점은 $S$에 포함된다는 사실로부터 $N(S) \subseteq T$이다.
> 
> 정점 $u \in N(S)$가 $M$에 포함되지 않는 간선에 의해 정점 $v \in S$와 연결되었다면, $v$까지의 alternating path는 $u$까지 연장될 수 있다. 그러므로 $u \in T$이다.
> 
> 반대로 정점 $u \in N(S)$가 $M$에 포함되는 간선에 의해 정점 $v \in S$와 연결되었다면, $u$는 $v$까지의 alternating path에 반드시 포함된다.
> 
> Lemma 3에 의해 $v$까지의 alternating path는 반드시 $M$에 포함되는 간선으로 끝나므로 $u$는 $v$까지의 alternating path에 있는 정점이다. 즉, $u \in T$이다.
> 
> 이로부터 $T \subseteq N(S)$이고, $N(S) \subseteq T$도 성립하므로 $N(S) = T$이다. **Q.E.D**

집합 $K = (X \setminus S) \cup T$라고 하자.

$u \in X$, $v \in Y$, $u, v \notin K$인 정점 $u, v$에 대해 간선 $e = (u, v)$가 존재한다고 가정하자.

그러면 $u \in S$, $v \notin T$인데, 이는 Lemma 4에 의해 $v \in N(S)$이지만 $v \notin T$이므로 모순이다.

그러므로 모든 간선들은 적어도 하나의 끝점이 $K$에 포함된다.

$\therefore$ $K$는 vertex cover이다.

이제 $K$의 모든 정점들이 $M$에 의해 매칭되고, $M$의 어떤 간선도 $K$의 두 정점을 연결하지 않는다는 것을 보임으로써 $\left\vert K \right\vert = \left\vert M \right\vert$임을 증명하자.

$X$의 정점들 중 매칭되지 않은 정점들은 모두 $U$에 포함되므로, $S$에도 포함된다.

그러므로 $K \cap X = X \setminus S$의 모든 정점들은 $M$에 대해 매칭된다는 것을 알 수 있다.

반대로 $K \cap Y = T$의 정점들 중 매칭되지 않은 정점이 존재한다면, $U$부터 해당 정점까지의 alternating path가 양끝 간선이 모두 matching에 포함되지 않기 때문에 augumenting path가 된다.

그러나 이는 Lemma 2에 의해 모순이므로 $K \cap Y = T$의 모든 정점들도 $M$에 대해 매칭되었음을 알 수 있다.

$\therefore$ $K$의 모든 정점은 $M$에 대해 매칭되었다. $\dots (1)$

만약 어떤 간선 $e \in M$의 양 끝점이 모두 집합 $K$에 속해있다면 반드시 한 끝점 $u$는 $K \cap X$에 속하고, 다른 끝점 $v$는 $K \cap Y$에 속해있을 것이다.

$K \cap Y = T$이므로 Lemma 3에 의해 $v$까지의 alternating path는 matching에 포함되지 않은 간선으로 끝난다는 것을 알 수 있다.

이때 위 alternating path는 간선 $e$를 통해 $u$로 연장될 수 있는데, 그럼 $u$는 $U$로부터 alternating path로 연결될 수 있는 정점이므로 $u \in S$이고, 이는 $u \in X \setminus S$에 대해 모순이다.

$\therefore$ $M$의 모든 간선들 중 양 끝점이 모두 $K$에 속한 간선은 존재하지 않는다. $\dots (2)$

(1), (2)에 의해 $\left\vert K \right\vert = \left\vert M \right\vert$가 되고, Lemma 1로부터 $K$가 minimum vertex cover이라는 것이 증명된다.

---

증명이 꽤나 복잡하고 한 번에 이해하기 어렵기는 하지만, 정리 자체는 매우 간단하고 적용하기 쉽다.

단순히 이분 그래프에서 minimum vertex cover의 크기를 구하는 문제는 최대 유량의 크기를 구하는 문제로 생각하고 풀면 된다.

다음 문제는 아주 대표적인 minimum vertex cover의 크기를 구하는 문제이다.

---

### [백준] 1867. 돌멩이 제거

[백준 1867. 돌멩이 제거 문제 링크](https://www.acmicpc.net/problem/1867)

n행 n열 격자에 k개의 돌멩이를 격자 당 최대 하나씩 올려두었다.

돌멩이를 전부 제거하려고 하는데, 한 번에 한 행이나 한 열에 있는 돌멩이를 모두 제거할 수 있다.

이때 돌멩이를 모두 제거하는데 필요한 최소 횟수를 구하는 문제이다.

n개의 행을 하나의 정점 집합, n개의 열을 다른 정점 집합이라 하고, (i, j)에 돌멩이가 있으면 i행과 j열을 연결해준다.

그렇다면 모든 돌멩이를 제거하는 최소 횟수는 minimum vertex cover의 크기가 된다.

Konig's Theorem에 의해 이분 그래프에서 minimum vertex cover의 크기는 maximum matching의 크기와 같으므로 매칭의 크기를 구해 출력하면 된다.

---


<br/>
## 4. Maximum Independent Set

**Independent Set**이란 집합 내의 어떤 두 정점도 하나의 간선으로 연결되지 않는 정점들의 부분집합을 말한다.

그 중 집합의 크기가 가장 큰 것을 **Maximum Independent Set**이라고 부른다.

Minimum Vertex Cover와 마찬가지로 일반적인 그래프에서 Maximum Independent Set을 구하는 것은 다항시간 안에 풀 수 없다.

하지만 이분 그래프의 Maximum Independent Set은 Minimum Vertex Cover의 여집합이다.

Vertex Cover는 모든 간선들의 끝점을 적어도 하나는 포함하고 있는 집합이므로 Vertex Cover의 여집합에서는 어떤 두 정점을 선택해도 두 정점을 연결하는 간선이 존재하지 않음을 알 수 있다.

그러므로 어떤 Vertex Cover의 여집합은 Independent Set이다.

반대로 어떤 Independent Set의 여집합은 Independent Set의 원소들을 끝점으로 가지는 간선을 모두 포함하므로 Vertex Cover라고 할 수 있다.

즉, 이분 그래프의 정점 개수를 $V$, Minimum Vertex Cover를 $C$, Maximum Independent Set을 $S$라고 하면 다음이 성립한다.

$V = \left\vert C \right\vert + \left\vert S \right\vert$

---

### [백준] 11014. 컨닝 2

[백준 11014. 컨닝 2 문제 링크](https://www.acmicpc.net/problem/11014)

이 문제는 이분 그래프의 Maximum Independent Set의 크기를 구하는 문제이다.

자세한 풀이는 [이 포스트](https://damo1924.github.io/ps/BAEKJOON-1014/#2-%EC%9D%B4%EB%B6%84-%EB%A7%A4%EC%B9%AD%EC%9D%84-%EC%9D%B4%EC%9A%A9%ED%95%9C-%ED%92%80%EC%9D%B4)를 참고하자.

---

## References

[1] [안경잡이개발자, '이분 매칭(Bipartite Matching)'](https://blog.naver.com/PostView.nhn?blogId=ndb796&logNo=221240613074)  
[2] [구사과, '유량 관련 알고리즘 증명'](https://koosaga.com/133)  
[3] [CODEFORCES, BessieTheCow's blog, 'Konig's Theorem'](https://codeforces.com/blog/entry/78255)  
[4] [Samsung Software Membership, Acka1357, '최대 이분 매칭에 관한 몇 가지 정리'](http://www.secmem.org/blog/2019/12/15/theorem-about-bipartite-matching/#minimum-vertex-cover)  
