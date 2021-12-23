---
title: "헝가리안 알고리즘의 구현(with. C++)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` Assignment Problem, Bipartite graph, Minimum Vertex Cover, Maximum Matching, Berge's Lemma

## 1. 기존 알고리즘의 개선이 필요한 이유

이번 포스팅은 [지난 포스팅](https://damo1924.github.io/algorithm/HungarianAlgorithm1/)에서 공부한 헝가리안 알고리즘을 어떻게 구현해야하는지에 대해 다루고 있다.

지난 포스팅에서 다룬 헝가리안 알고리즘은 다음과 같았다.

>
> 직원들의 집합 $I$, 작업들의 집합 $J$라고 하자. ($\left\vert I \right\vert = \left\vert J \right\vert = N$)
>
> 어떤 직원 $i \in I$가 작업 $j \in J$를 처리할 때 필요한 비용을 $c(i, j)$라고 한다.
>
> 1. $i$행 $j$열의 원소가 $c(i, j)$인 행렬 $C$를 생각한다.
> 2. 모든 행에 대해서 각 행에서 가장 작은 값을 빼준다.
> 3. 모든 열에 대해서 각 열에서 가장 작은 값을 빼준다.
> 4. $I$, $J$의 원소들을 노드로 하고, $C_{ij} = 0$인 $(i, j)$를 잇는 간선을 그린 이분 그래프를 생각한다. 이 이분 그래프의 Minimum Vertex Cover를 $I' + J'$이라고 하자.
> 5. $\left\vert I' \right\vert + \left\vert J' \right\vert = N$일 때까지 아래 과정을 반복한다.
>   - $i \notin I'$, $j \notin J'$을 만족하는 $(i, j)$ 쌍에 대해 $C_{ij}$의 최솟값을 $m$이라고 하자.
>   - $I'$에 속하지 않은 행들의 각 원소에서 $m$을 뺀다.
>   - $J'$에 속하는 열들의 각 원소에 $m$을 더한다.
>   - 갱신된 행렬에 대해 다시 $I'$과 $J'$를 구한다.
> 6. 최종적으로 얻어진 행렬에서 $C_{ij} = 0$인 $(i, j)$들에 대해 직원 $i$를 작업 $j$에 할당한다.
>

이대로 알고리즘을 구현함에 있어 가장 큰 문제는 **매번 Minimum Vertex Cover의 크기를 구해야한다는 것**이었다.

이분 그래프의 Minimum Vertex Cover의 크기를 구하는 문제는 일반적으로 최대 유량 문제로 바꾸어서 Edmond-Karp Algorithm을 이용한다.

Edmond-Karp 알고리즘의 시간복잡도는 $O(VE)$으로, 직원과 작업의 수인 $N$으로 표현하면 $O(N^3)$이다.

이러한 작업을 반복문을 수행할 때마다 하는 것은 매우 비효율적이다.

또한, 저번 포스팅에서 증명한 것은 이 과정을 계속해서 반복하다보면 결국에는 답을 얻을 수 있다라는 것일 뿐, 이 과정을 최대 몇 번 반복하면 답을 얻을 수 있는지에 대한 단서는 없었다.

그러므로 효율적인 알고리즘을 구현하기 위해서는 빠른 시간 내에 이분 그래프의 minimum vertex cover의 크기를 구하는 것이 필요하다.

<br/>

## 2. 문제 정의

> - **Matching**: 어느 두 간선도 끝점을 공유하지 않는 간선들의 부분집합으로, 어떤 정점이 매칭되었다는 것은 matching에 있는 간선들 중 해당 정점을 끝점으로 하는 간선이 존재한다는 것을 의미한다.
> - **Alternating path**: 그래프 상에 존재하는 경로들 중 matching에 포함되는 간선들과 matching에 포함되지 않는 간선들이 번갈아 나타나는 경로
> - **Augmenting path**: 양쪽 끝 정점이 모두 매칭되지 않은 alternating path

위 알고리즘의 5번 과정을 반복하고 있는 상황을 생각하자.

현재 행렬을 $C$라고 할 때, $C_{ij} = 0$을 만족하는 직원 $i$와 작업 $j$를 잇는 간선들의 집합을 $E_c$라고 정의하자.

$I$, $J$의 원소들과 $E_c$에 속하는 간선들로 이루어진 이분 그래프를 $G$라고 한다.

**[목표]** $G$의 Minimum vertex cover의 크기

그래프 $G$의 Maximum matching을 $M_{max} \subseteq E_c$이라고 하자.

$U$: $I$의 원소 중 $M_{max}$에 대해 매칭되지 않은 정점들의 집합

$Z$: $U$의 정점들로부터 $M_{max}$에 대한 alternating path를 통해 접근이 가능한 정점들의 집합

$S = Z \cap I$

$T = Z \cap J$

$N(S)$: $S$의 정점들에 인접한 정점들의 집합

> **[Konig's Theorem]** 이분 그래프의 Minimum vertex cover의 크기와 Maximum matching의 크기는 동일하다.
>
> **[Berge's Lemma]** 그래프의 어떤 매칭이 Maximum matching이기 위한 필요충분조건은 매칭에 대한 Augmenting path가 존재하지 않는 것이다.
>
> **[Lemma 1]** $U$의 정점에서 $S$의 정점까지의 alternating path는 $M_{max}$에 포함된 간선으로 끝나고, $U$의 정점에서 $T$의 정점까지의 alternating path는 $M$에 포함되지 않은 간선으로 끝난다.
>
> **[Lemma 2]** $N(S) = T$
>
> **[Lemma 3]** 집합 $V = (I \setminus S) \cup T$는 그래프 $G$의 Minimum vertex cover이다.

위 정리들에 대한 증명은 [이 포스트](https://damo1924.github.io/algorithm/BipartiteMatching/#3-minimum-vertex-cover--konigs-theorem)를 참고.

<br/>

## 3. Finding Minimum Vertex Cover with Augmenting Path

먼저 이분 그래프의 Minimum Vertex Cover의 크기는 Konig's theorem에 의해 Maximum matching의 크기와 같다.

또한 Berge's Lemma로부터 Augmenting path가 존재하는 매칭은 Maximum matching이 아니므로, augmenting path가 존재하지 않는 매칭을 구하면 해당 매칭은 Maximum matching이 된다.

이분 그래프에서는 어떤 매칭에 대한 augmenting path를 이용하면 해당 매칭보다 크기가 더 큰 매칭을 구할 수 있는데, 그 방법은 다음과 같다.

> Augmenting path의 양 끝 간선은 매칭에 포함되지 않는 간선이므로 해당 경로에는 매칭에 포함되지 않는 간선이 매칭에 포함된 간선보다 하나 더 많다.
> 
> 그러므로 augmenting path를 따라가면서 매칭에 포함된 간선은 매칭에서 제거하고, 매칭에 포함되지 않은 간선을 매칭에 추가하면 기존 매칭보다 크기가 1 더 커진 매칭을 얻을 수 있다.

그러므로 현재 매칭 $M$에 대해 다음과 같이 케이스를 나눌 수 있다.

1. $M$에 Augmenting path가 존재하는 경우: Maximum matching이 아니므로 해당 경로를 이용해서 매칭의 크기를 증가시킨다.
2. $M$에 Augmenting path가 존재하지 않는 경우: 현재 매칭이 Maximum matching이므로 매칭의 크기가 Minimum vertex cover의 크기가 된다.
  - 현재 매칭의 크기가 $N$이면 반복문을 종료하고 결과를 반환한다.
  - 현재 매칭의 크기가 $N$보다 작으면 행렬에 적절한 연산을 적용해서 매칭의 augmenting path가 존재하도록 한다.

따라서 주어진 매칭에 대해서 augmenting path를 찾을 수 있다면, 이분 그래프의 minimum vertex cover도 구할 수 있다.

<br/>

## 4. Finding Augmenting Path

주어진 매칭 $M$에 대한 augmenting path를 구하는 과정에 대해 알아보자.

**1)** $I$에서 매칭되지 않은 정점 $u$를 선택하여 집합 $S = \\{u\\}$, $T$는 공집합으로 놓는다.

> 집합 $S$는 augmenting path에 포함된 $I$의 정점들, 집합 $T$는 augmenting path에 포함된 $J$의 정점들을 의미한다.

**2)** $N(S) = T$이면 현재까지 구한 Augmenting path에서 더 늘리는 것이 불가능하므로 행렬을 변환해서 간선을 갱신한다.

**3)** $N(S) \neq T$을 만족할 때, $j \in N(S) - T$인 정점 $j$를 하나 선택한다.

**3-1)** 만약 $j$가 매칭되지 않은 정점이면 현재 경로는 augmenting path이므로 경로를 이용해서 매칭의 크기를 늘린 후, 1번으로 돌아간다.

**3-2)** $j$가 매칭된 정점이면, 현재 경로에 $j$와 $j$와 매칭된 정점 $k$를 추가하고 2번으로 돌아간다.

> $S = S \cup \\{k\\}$, $T = T \cup \\{j\\}$
> 
> 이때 저장되는 augmenting path는 일자 경로가 아니라 트리의 형태이다.

<br/>

## 5. How to change the Matrix after finding the Minimum Vertex Cover

마지막으로 더 이상 매칭의 크기를 늘리지 못할 때 행렬에 어떤 연산을 적용해주어야 하는지 알아보자.

매칭되지 않은 어떤 정점 $u \in I$에서 출발한 augmenting path가 존재한다고 해보자.

해당 augmenting path 위의 정점들을 $s_1, \dots, s_k \in S$, $t_1, \dots, t_k, t_{k+1} \in T$라고 하면, augmenting path는 다음과 같은 순서대로 정점을 지나게 된다.

\begin{aligned}
u, t_1, s_1, t_2, s_2, \dots, t_k, s_k, t_{k+1}
\end{aligned}

이때 자연수 $p$($1 \leq p \leq k$)에 대해 $t_p$과 $s_p$를 잇는 간선은 매칭에 속하며, 나머지 간선들은 매칭에 속하지 않는다.

이 경로를 이용해서 매칭의 크기를 늘리게 되면 기존에 매칭되어 있지 않던 정점 $u$는 $t_1$과 매칭된다.

동시에 $t_p$와 $s_p$ 사이의 간선이 매칭에서 삭제되는 대신, $s_p$와 $t_{p+1}$ 사이의 간선이 매칭에 추가된다.

즉, 위 과정을 수행해도 기존에 매칭되었던 정점들인 $s_1, \dots, s_k \in S$, $t_1, \dots, t_k, t_{k+1} \in T$는 여전히 매칭되어 있음을 알 수 있다.

매칭이 되어있지 않던 정점인 $u \in I$와 $t_{p+1} \in J$가 새롭게 매칭되면서 매칭의 크기가 늘어나게 되는 것이다.

그런데, 매칭이 되어있지 않은 정점 $u \in I$에서 시작한 augmenting path가 존재하지 않는다면 어떻게 해야할까?

다음과 같은 $u$에서 출발한 alternating path를 생각하자.

\begin{aligned}
u, t_1, s_1, t_2, s_2, \dots, t_k, s_k
\end{aligned}

집합 $S = \\{u, s_1, \dots, s_k\\}$와 $T = \\{t_1, \dots, t_k\\}$에 대해서 $N(S) = T$인 상황이다.

Augmenting path를 만들기 위해서는 아직 매칭에 포함되지 않은 어떤 정점 $v \in J - T$를 집합 $S$의 원소 중 하나와 연결하는 간선이 필요하다.

이때 $v$는 $S$의 어떤 원소와 연결되어도 상관이 없는데, 그 이유는 해당 원소 뒤에 $v$를 연결하면 $u$부터 $v$까지는 augmenting path이기 때문이다.

그렇다면 어떤 $v \in J - T$를 선택해야할까?

여기에 대한 답은 저번 포스팅에서 다룬 알고리즘에 나와있다.

다음은 헝가리안 알고리즘의 일부분이다.

> **4)** $I$, $J$의 원소들을 노드로 하고, $C_{ij} = 0$인 $(i, j)$를 잇는 간선을 그린 이분 그래프를 생각한다. 이 이분 그래프의 Minimum Vertex Cover를 $I' + J'$이라고 하자.
> **5)** $\left\vert I' \right\vert + \left\vert J' \right\vert = N$일 때까지 아래 과정을 반복한다.
> - $i \notin I'$, $j \notin J'$을 만족하는 $(i, j)$ 쌍에 대해 $C_{ij}$의 최솟값을 $m$이라고 하자.
> - $I'$에 속하지 않은 행들의 각 원소에서 $m$을 뺀다.
> - $J'$에 속하는 열들의 각 원소에 $m$을 더한다.
> - 갱신된 행렬에 대해 다시 $I'$과 $J'$를 구한다.

이분 그래프 $G$의 Minimum vertex cover를 $V$라고 하면, $I'$과 $J'$은 다음과 같다.

\begin{aligned}
I' = V \cap I, J' = V \cap J
\end{aligned}

이때 **Lemma 3**에 의해 Minimum vertex cover $V = K = (I \setminus S) \cup T$이다.

그러므로 $I' = I \setminus S$이고, $J' = T$가 된다.

위 사실을 이용하면 알고리즘의 **5)** 부분을 다음과 같이 쓸 수 있다.

> - $i \in S$, $j \notin T$를 만족하는 $(i, j)$ 쌍에 대해 $C_{ij}$의 최솟값을 $m$이라 한다.
> - $S$에 속하는 행들의 각 원소에서 $m$을 뺀다.
> - $T$에 속하는 열들의 각 원소에 $m$을 더한다.
> - 갱신된 행렬에 대해 다시 $S$와 $T$를 구한다.

<br/>

## 6. Some neat methods to Improve Time Complexity

**1) Labeling**

각 행과 열에 Labeling을 한다는 것은 해당 행이나 열에 빼준 값을 저장해주는 것이다.

> `L_x[i]` = i행의 원소들에 공통적으로 빼준 값  
> `L_y[i]` = i열의 원소들에 공통적으로 빼준 값

원래는 행렬을 업데이트할 때마다 모든 원소에 특정 값을 빼거나 더해야한다.

하지만 Labeling을 하면 굳이 모든 원소에 값을 더하거나 빼는 대신 `L_x`와 `L_y`에만 더하거나 빼주면 된다.

$O(N^2)$이 걸리는 작업을 $O(N)$으로 처리할 수 있게 된다.

---

**2) Calculating Minimum** $m$ **in** $O(N)$

행렬을 업데이트하기 위해서는 조건을 만족하는 값들 중 최솟값 $m$을 구해야한다.

마찬가지로 이 작업도 행렬의 모든 원소를 체크하면서 조건을 만족하는 값을 구해야하기 때문에 $O(N^2)$의 시간복잡도를 가진다.

다음 두 배열을 추가적으로 이용하면 $O(N)$의 시간복잡도로 최솟값을 구할 수 있다.

> `slack[j]` = $i \in S$에 대해 `c[i][j] - L_x[i] - L_y[j]`의 최솟값을 저장  
> `slack_x[j]` = `slack[j]`에 저장된 최솟값에 해당하는 $i \in S$를 저장

집합 $S$에 새로운 원소가 추가될 때마다 `slack`을 더 작은 값으로 갱신시켜주면, `slack` 배열을 탐색하여 최솟값을 구할 수 있게 된다.

<br/>

## 7. C++ Implementation of Hungarian Algorithm

지금까지 공부한 내용을 토대로 헝가리안 알고리즘을 구현해보자.

### [백준] 14216. 할 일 정하기 2

[백준 14216. 할 일 정하기 2 문제 링크](https://www.acmicpc.net/problem/14216)

할 일 정하기 1 문제는 N의 범위가 20까지여서 DP로 풀 수 있었지만, 이 문제는 N의 범위가 500까지 주어진다.

헝가리안 알고리즘의 시간복잡도는 $O(N^3)$이므로 충분히 해결 가능하다.

```cpp
#include <iostream>
using namespace std;
const int maxN = 500;
const int INF = 1000000000;

int N;

int c[maxN][maxN]; // 행렬값

int L_x[maxN], L_y[maxN]; // 각 행, 각 열에 빼준 값을 저장

int match_x[maxN], match_y[maxN]; // 매칭 정보를 저장

int augPath_x[maxN], augPath_y[maxN]; // Augmenting path에서 인접한 노드를 저장

bool inS[maxN], inT[maxN]; // S, T에 포함되면 true, 아니면 false

int slack[maxN], slack_x[maxN]; // 각 열의 최솟값과 최솟값이 위치하고 있는 행을 저장

int hungarian()
{
    for (int i = 0; i < N; i++) match_x[i] = match_y[i] = -1;

    // 각 행에서 최솟값 제거 O(N^2)
    for (int i = 0; i < N; i++)
    {
        int tmp = INF;
        for (int j = 0; j < N; j++) tmp = min(tmp, c[i][j]);
        L_x[i] += tmp;
    }
    // 각 열에서 최솟값 제거 O(N^2)
    for (int i = 0; i < N; i++)
    {
        int tmp = INF;
        for (int j = 0; j < N; j++) tmp = min(tmp, c[j][i] - L_x[j]);
        L_y[i] += tmp;
    }

    int M = 0; // 매칭의 크기
    while (M != N) // 매칭의 크기가 N이 될 때까지 최대 N번 반복
    {
        // augmenting path, 집합 S, T 초기화
        for (int i = 0; i < N; i++)
        {
            augPath_x[i] = augPath_y[i] = -1;
            inS[i] = inT[i] = 0;
        }

        // 아직 매칭이 되지 않은 I의 원소 u를 찾아 집합 S에 넣는다.
        int u;
        for (int i = 0; i < N; i++)
        {
            if (match_x[i] == -1)
            {
                inS[i] = 1;
                u = i;
                break;
            }
        }
        // 집합 S에 u가 삽입되었으므로 slack을 u행으로 초기화해준다.
        for (int i = 0; i < N; i++)
        {
            slack[i] = c[u][i] - L_x[u] - L_y[i];
            slack_x[i] = u;
        }

        // augmenting path를 찾아 매칭의 크기를 증가시킨다. O(N^2)
        while (true)
        {
            // N(S) - T 의 원소 중 임의의 원소를 선택
            int j = -1;
            for (int i = 0; i < N; i++)
                if (slack[i] == 0 && !inT[i]) j = i;

            // 0. N(S) = T인 경우 - 행렬 업데이트하기
            // slack[j] = S에 속하는 행 i에 대해 c[i][j] - L_x[i] - L_y[j]의 최솟값
            // 그러므로 j가 T에 속하지 않는다는 조건을 만족하는 slack[j] 중 최솟값 m을 찾으면 된다.
            if (j == -1)
            {
                int m = INF;
                for (int i = 0; i < N; i++)
                    if (!inT[i]) m = min(m, slack[i]);

                // S에 속하는 행들에 m을 빼고, T에 속하는 행들에 m을 더해준다.
                for (int i = 0; i < N; i++)
                {
                    if (inS[i]) L_x[i] += m;
                    if (inT[i]) L_y[i] -= m;
                }

                // 행렬을 업데이트했으므로 새로운 간선으로 연결된 J - T의 원소 v를 찾는다.
                for (int i = 0; i < N; i++)
                {
                    if (!inT[i])
                    {
                        slack[i] -= m; // 동일하게 m을 빼주었으므로 slack에 저장된 값들에 m을 빼준 것이 여전히 최솟값이다.
                        if (slack[i] == 0) j = i; // v
                    }
                }
            }

            // 1. 경로에 추가할 j가 매칭이 되지 않은 free vertex인 경우
            // 경로에 j를 추가하면 해당 경로는 augmenting path가 된다.
            // 매칭에 있는 간선은 매칭에서 삭제하고 매칭에 없는 간선은 매칭에 추가함으로써 매칭의 크기를 1 증가시킨다.
            if (match_y[j] == -1)
            {
                augPath_y[j] = slack_x[j]; // slack[j] == 0인 j가 S의 어떤 원소에 연결되었는지 경로를 저장
                while (j != -1) // 경로를 역추적하면서 매칭 정보를 수정
                {
                    int i = augPath_y[j];
                    match_y[j] = i;
                    int next_j = match_x[i];
                    match_x[i] = j;
                    j = next_j;
                }
                // augPath: next_j - i - j
                // 기존에 매칭에 속한 (next_j, i) 대신 (i, j)를 매칭에 넣는다.

                M++; // 매칭의 크기 증가
                break; // 새로운 매칭에 대해 augmenting path를 처음부터 찾는다.
            }

            // 2. 경로에 추가할 j가 매칭이 된 정점인 경우
            else
            {
                int k = match_y[j]; // j가 매칭된 정점
                // 경로에 두 정점을 추가: (기존 경로) + (j - k)
                augPath_x[k] = j;
                augPath_y[j] = slack_x[j];
                // S에 k 추가, T에 j 추가
                inS[k] = 1;
                inT[j] = 1;

                // S에 새로운 원소 k가 추가되었으므로 slack을 작은 값으로 갱신
                for (int i = 0; i < N; i++)
                {
                    if (c[k][i] - L_x[k] - L_y[i] < slack[i])
                    {
                        slack[i] = c[k][i] - L_x[k] - L_y[i];
                        slack_x[i] = k;
                    }
                }
            }
        }
    }

    // 최소 비용은 행렬의 각 행과 열에서 공통으로 빼준 값을 모두 더한 것이다.
    int res = 0;
    for (int i = 0; i < N; i++)
    {
        res += L_x[i];
        res += L_y[i];
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N;
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            cin >> c[i][j];

    cout << hungarian();
}
```

위 코드는 Reference [1]의 글을 참조해서 작성하였다.

<br/>

## Reference

[1] [Samsung Softwarer Membership, '헝가리안 알고리즘'](http://www.secmem.org/blog/2021/04/18/hungarian-algorithm/)  

