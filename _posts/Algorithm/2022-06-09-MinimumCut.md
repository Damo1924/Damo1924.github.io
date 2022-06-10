---
title: "최소 컷 문제 (Minimum Cut Problem)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` Max-flow min-cut theorem, Stoer-Wagner algorithm, 최대 유량 최소 컷 정리, 스토어-바그너

## 1. Minimum Cut Problem

그래프 $G = (V, E)$에 대하여, **cut** $C = (S, T)$는 $V$를 두 부분집합 $S$, $T$로 나눈 분할이다.

이때 $u \in S$, $v \in T$를 만족하는 간선 $(u, v)$들의 집합을 **cut-set**이라 부른다.

두 정점 $s, t \in V$에 대하여 **s-t cut**은 $s \in S$, $t \in T$를 만족하는 cut이다.

> 방향그래프(directed graph)에 대하여, s-t cut의 cut-set은 소스(source)가 속하는 부분집합의 정점에서 싱크(sink)가 속하는 부분집합의 정점으로 향하는 간선으로만 이루어져 있다.

**Weight of cut**은 아래와 같이 정의된다.

- 가중치가 없는 경우(Unweighted graph): cut-set의 크기
- 가중치가 있는 경우(Weighted graph): cut-set에 포함된 간선들의 가중치의 합

**최소 컷(minimum cut)**이란 weight이 최소인 cut을 의미한다.

최소 컷을 구하는 문제는 소스와 싱크의 유무에 따라서 나눌 수 있다.

1. 소스와 싱크가 주어진 경우
2. 소스와 싱크가 주어지지 않은 경우: **Global minimum cut problem**

1번은 **최대 유량 최소 컷 정리**에 따라서 소스에서 싱크로의 최대 유량을 구함으로써 해결할 수 있다.

무향 그래프에서 2번 문제는 **스토어-바그너 알고리즘**을 이용해서 해결할 수 있다.

이번 포스팅에서는 위 두 가지 문제를 해결하는 방법들에 대해서 다룰 것이다.

> 마찬가지로 최대 컷(maximum cut)도 정의할 수 있는데, 임의의 그래프의 최대 컷을 구하는 문제는 NP-complete이다.

<br/>

## 2. Minimum Cut Problem with Terminal Nodes

### 2-1. Max-Flow Min-Cut Theorem

다음과 같은 네트워크를 생각하자.

- 방향그래프(directed graph) $G = (V, E)$
- 소스(source) $s \in V$, 싱크(sink) $t \in V$
- 간선 $(u, v) \in E$의 최대 용량(capacity) $c_{uv}$, 간선에 흐르는 유량(flow) $f_{uv}$

$s$에서 $t$로의 유량은 다음과 같이 정의된다.

\begin{aligned}
\left\vert f \right\vert = \sum_{v:(s,v) \in E} f_{sv} = \sum_{v:(v,t) \in E} f_{vt}
\end{aligned}

$s \in S$, $t \in T$를 만족하는 s-t cut $C = (S, T)$의 cut-set을 $X_C$라 하면 s-t cut의 capacity는 다음과 같이 정의된다.

\begin{aligned}
c(S, T) = \sum_{(u, v) \in X_C} c_{uv}
\end{aligned}

이때 최대 유량 최소 컷 정리(max-flow min-cut theorem)는 다음과 같다.

> 방향그래프와 소스, 싱크가 주어졌을 때, 최대 유량은 최소 컷의 용량과 같다.
> 
> 즉, $\left\vert f \right\vert$의 최댓값과 $c(S, T)$의 최솟값이 같다.

따라서 소스와 싱크가 정해진 최소 컷 문제는 소스에서 싱크로 흐를 수 있는 최대 유량을 구함으로써 해결할 수 있다.

---

### 2-2. Proof of Max-Flow Min-Cut Theorem

포드-풀커슨 알고리즘(Ford-Fulkerson algorithm)으로 구한 그래프에 흐르는 유량 $f$를 생각하자.

알고리즘에서 최종 유량을 흘려보낸 후 얻을 수 있는 **residual graph** $G_f$에 대하여 정점들의 두 부분집합을 정의하자.

- $A$ : $G_f$에서 $s$로부터 도달 가능한 정점들의 집합
- $A^C$ : $V - A$

정점들의 임의의 부분집합 $A$에 대하여

\begin{aligned}
f = f_{out}(A) - f_{in}(A)
\end{aligned}

이고, s-t cut $C = (A, A^C)$에 대하여

\begin{aligned}
c(A, A^C) = \sum_{(u, v) \in X_C} c_{uv}
\end{aligned}

이다. 따라서 $f = c(A, A^C)$가 성립하기 위해서는 아래 두 조건을 만족해야한다.

- $A$의 정점에서 $A^C$의 정점으로 향하는 모든 간선에는 해당 간선의 최대 용량만큼 유량이 흘러야한다. (**fully saturated**)
- $A^C$의 정점에서 $A$의 정점으로 향하는 모든 간선에는 유량이 흐르지 않아야한다. (**zero flow**)

먼저, $x \in A$, $y \in A^C$인 간선 $(x, y)$ 중 포화되지 않은 것이 존재한다고 가정하자.

$f_{xy} < c_{xy}$ 이므로 $G_f$에서 $s$에서 $y$까지의 경로가 존재하게 되고, 이는 모순이다.

따라서 $A$의 정점에서 $A^C$의 정점으로 향하는 모든 간선은 포화되어 있다.

다음으로 $x \in A$, $y \in A^C$인 간선 $(y, x)$ 중 유량이 흐르는 간선이 존재한다고 가정하자.

$f_{yx} > 0$ 이므로 $G_f$에는 유량이 흐를 수 있는 $x$에서 $y$로의 역방향 간선이 존재한다.

즉, $G_f$에서 $s$에서 $y$까지의 경로가 존재하게 되고, 마찬가지로 모순이 발생한다.

따라서 $A^C$의 정점에서 $A$의 정점으로 향하는 모든 간선에는 유량이 흐르지 않는다.

두 조건이 성립한다는 것을 증명했으므로, $f = c(A, A^C)$가 성립함을 알 수 있다.

이때 $f$는 포드-풀커슨 알고리즘으로 구한 값이므로 **최대 유량**이다.

---

### [BOJ] 14286. 간선 끊어가기 2

[BOJ 14286. 간선 끊어가기 2 문제 링크](https://www.acmicpc.net/problem/14286)

무향 그래프에서 소스와 싱크가 주어졌을 때 최소 컷을 구하는 문제이다.

---

### [BOJ] 1420. 학교 가지마!

[BOJ 1420. 학교 가지마! 문제 링크](https://www.acmicpc.net/problem/1420)

도현이는 직사각형 모양의 도시에 살고 있으며, 도시는 빈 칸 또는 벽으로 이루어져 있다.

도현이는 현재 위치에서 인접한 빈 칸으로 이동하여 학교에 가려고 한다.

도현이가 학교를 가지 못하도록 하기 위해서 빈 칸을 벽으로 바꿀 때, 바꾸어야하는 벽의 최소 개수를 구하는 문제이다.

> 도현이의 위치를 소스, 학교의 위치를 싱크로 두고 인접한 빈 칸들을 간선으로 연결해 준 그래프를 생각하자.
> 
> 소스에서 싱크로 흐를 수 있는 유량을 0으로 만들기 위해 **정점에 유량이 흐르지 못하도록** 바꾸어야한다.
> 
> 따라서 정점을 분리하여 최대 용량이 1인 간선으로 연결해주면, 구하고자 하는 값은 해당 그래프의 최소 컷, 즉 최대 유량과 같아진다.

---

### [BOJ] 13161. 분단의 슬픔

[BOJ 13161. 분단의 슬픔 문제 링크](https://www.acmicpc.net/problem/13161)

슬픔이 최소가 되도록 $N$명의 **사람들을 두 진영으로 나누는 방법을 구하는 문제**이다.

$i$번 사람과 $j$번 사람이 서로 다른 진영에 들어가면 $w(i,j)$만큼의 슬픔이 발생한다.

아무런 조건이 없으면 모두 한 진영에 속하게 하면 되기 때문에, 반드시 어떤 진영에 속해야하는 사람들이 조건으로 주어진다.

> A진영에 반드시 속해야하는 사람들을 소스와 연결하고, B진영에 반드시 속해야하는 사람들을 싱크와 연결한다.
> 
> 두 사람이 다른 진영에 속할 때 발생하는 슬픔이 최대 유량인 간선으로 사람들을 연결해준다.
> 
> 이때 구하고자 하는 값은 위 그래프의 최소 컷임을 알 수 있다.

단순히 슬픔의 최솟값만 구하는 것이 아니라 직접 사람들을 두 진영으로 나누는 방법을 출력해야하는데, 이는 **디닉 알고리즘에서 마지막 BFS를 실행하고 얻어지는 레벨(lev) 배열**을 통해 구할 수 있다.

레벨이 초깃값 $-1$이 아니라면 소스에서 접근이 가능한 정점이므로 A진영에 속하는 사람임을 알 수 있다.

> 모든 $i, j$($i \neq j$)에 대하여 $w(i, j)$가 주어지기 때문에 $E \geq (V-1)V$ 이다.
> 
> 시간 제한이 상당히 빡빡해서 에드몬드-카프 알고리즘으로는 시간초과가 발생한다. 꼭 디닉 알고리즘을 사용할 것!

---

### [BOJ] 1210. 마피아

[BOJ 1210. 마피아 문제 링크](https://www.acmicpc.net/problem/1210)

마피아가 고속도로를 통해 원하는 지점으로 이동할 수 없도록 최소한의 비용으로 톨게이트를 점거하는 방법을 구하는 문제이다.

위의 "[BOJ] 1420. 학교 가지마" 문제처럼 정점에 유량이 흐르지 못하도록 하는 문제이다.

단, 점거해야하는 톨게이트의 번호를 직접 구해야한다.

> 마찬가지로 정점 분리를 하고 그 사이에 최대 유량이 점거 비용인 간선으로 연결해준 후 디닉 알고리즘으로 최대 유량을 구해준다.
> 
> 점거해야하는 톨게이트를 구하려면, **분리된 두 정점 중 소스로부터 한쪽 정점에만 방문 가능한 톨게이트**를 찾으면 된다.

---

### [BOJ] 1070. 김지민의 침략

[BOJ 1070. 김지민의 침략 문제 링크](https://www.acmicpc.net/problem/1070)

직사각형 모양의 왕국은 하나의 수도와 알파벳으로 나타내지는 지형들, 그리고 지나갈 수 없는 지역으로 이루어져 있다.

왕국을 통치하는 임한수는 알파벳으로 나타내지는 지형들에 장애물을 적절히 배치하여 왕국의 바깥 경계로부터 수도로 침략할 수 없도록 하려고 한다.

지형에 따라서 설치해야하는 장애물의 크기가 다르며, **필요한 장애물의 개수가 최소**일 때 필요한 장애물의 크기의 합을 구하는 문제이다.

만약 **장애물의 개수가 최소인 경우가 여러 개라면 그 중 장애물들의 크기의 합이 최소인 것**을 출력하면 된다.

> 결국 수도로 가기 위해서는 수도와 인접한 네 지역 중 하나를 거쳐야한다.
> 
> 따라서 경계에 위치한 지역들을 소스와 연결하고, 수도를 싱크로 둔 그래프의 최소 컷은 $4$ 이하임을 알 수 있다.
> 
> 각 지형에 설치해야하는 장애물의 크기는 $10^6$ 이하이므로 장애물들의 크기의 총 합은 $4 \cdot 10^6$ 이하이다.
> 
> 즉, **정점을 분리**하여 그 사이를 **최대 유량이 "(매우 큰 값) + (해당 지역에 설치해야하는 장애물의 크기)" 인 간선으로 연결**해준 후 최대 유량을 구하자.
> 
> 그렇다면 **설치해야하는 장애물들의 크기의 합은 최대 유량을 (매우 큰 값)으로 나눈 나머지**이다.

<br/>

## 3. Global Minimum Cut Problem

### 3-1. Stoer-Wagner algorithm

Weighted undirected graph $G = (V, E, w)$에 대하여 $G$의 global minimum cut을 $C$라고 하자.

임의의 두 정점 $s, t \in V$ 는 $C$의 같은 부분집합에 속하거나 서로 다른 부분집합에 속한다.

이를 이용하면 s-t minimum cut에 대하여 다음과 같이 말할 수 있다.

- $s, t$가 $C$에 대하여 **다른** 부분집합에 속하는 경우: s-t minimum cut이 global minimum cut이다.
- $s, t$가 $C$에 대하여 **같은** 부분집합에 속하는 경우: $s$와 $t$를 하나의 정점으로 합쳐도 global minimum cut은 변하지 않는다.

따라서 어떤 두 정점 $s, t$를 선택하여 최소 컷을 구하고, 두 정점을 합쳐가며 전체 정점이 하나가 될 때까지 반복해주면 global minimum cut을 얻을 수 있음을 알 수 있다.

하지만 어떤 두 정점을 선택하여 매번 Edmond-Karp algorithm 또는 Dinic algorithm을 이용하는 것은 비효율적이다.

정해진 두 정점이 아니라 임의의 두 정점 사이의 최소 컷을 구해도 괜찮다는 사실을 이용하면 빠르게 처리를 할 수 있게 된다.

1. 임의의 정점을 하나 선택하여 집합 $A$에 넣는다.
2. 집합 $A$와 가장 **tightly connected**인 정점을 찾아 $A$에 추가한다.
3. 집합 $A$에 속하지 않은 정점이 하나가 될 때까지 2번 과정을 반복한다.
4. 가장 마지막에 추가된 정점을 $s$, 집합에 속하지 않은 하나의 정점을 $t$라고 했을 때, s-t minimum cut은 $t$의 **tightness**와 같다.

집합 $A$에 속하지 않은 정점 $v$에 대하여 $v$의 tightness는 $\sum_{u \in A} w(u, v)$ 로 정의된다.

위 과정(minimum cut phase)을 통해 최소 컷을 구하고 **edge contraction**을 통해 두 정점을 합쳐주는 과정을 반복하면 global minimum cut을 구할 수 있다.

---

### 3-2. Proof of Stoer-Wagner algorithm

최소 컷을 구하는 과정을 증명하기 위해 아래와 같이 **active vertex**를 정의하자.

- 집합 $A$에 추가된 순서대로 정점들을 나열했을 때, s-t cut에 대하여 직전 정점과 반대편에 놓이게 되는 정점

> 가장 마지막 정점 $t$는 정의에 의해 반드시 active vertex이다.

또, 어떤 active vertex $v$에 대하여 집합 $A_v$와 컷 $C_v$를 아래와 같이 정의하자.

- $A_v$ : $v$ 이전에 추가된 정점들의 집합
- $C_v$ : $A_v \cup v$ 를 s-t cut과 동일하게 분할하는 cut

$C_v$의 weight를 $w(C_v)$라고 할 때, 귀납법을 이용하여 아래 식이 성립함을 보일 것이다.

\begin{aligned}
w(A_v, v) \leq w(C_v)
\end{aligned}

첫 번째 active vertex $v$는 $C_v = (A_v, v)$ 이므로 $w(A_v, v) = w(C_v)$ 이다.

이제 임의의 active vertex $u$에 대하여 직전의 active vertex를 $v$라고 할 때, $w(A_v, v) \leq w(C_v)$ 이면 $w(A_u, u) \leq w(C_u)$ 임을 보이자.

집합 $A$에 새로운 원소를 추가할 때 항상 tightness가 가장 큰 정점을 선택하기 때문에 $w(A_v, u) \leq w(A_v, v)$ 이 성립한다.

또, $v$부터 $u$ 이전 정점까지는 모두 $C$에 대하여 $u$와 반대편에 놓이므로 $w(C_v) + w(A_u - A_v, u) = w(C_u)$ 이다.

위 식들을 이용하면,

\begin{aligned}
w(A_u, u) &= w(A_v, u) + w(A_u - A_v, u) \\\\  
&\leq w(A_v, v) + w(A_u - A_v, u) \\\\  
&\leq w(C_v) + (A_u - A_v, u) = w(C_u)
\end{aligned}

를 얻을 수 있고, 귀납법에 의해 다음이 성립한다.

> 모든 active vertex $v$에 대하여 $w(A_v, v) \leq w(C_v)$ 가 성립한다.

이때 마지막 정점 $t$는 항상 active vertex이므로 $w(A_t, t) \leq w(C_t)$ 이고, $C_t = C$ 이므로 다음이 증명된다.

> Minimum cut phase로 얻은 두 정점 $s, t$에 대하여, s-t minimum cut의 weight는 $w(A_t, t)$, 즉 $t$의 tightness와 같다.

---

### 3-3. Time complexity

그래프 $G = (V, E)$에 대하여 minimum cut phase를 총 $V-1$번 수행하게 된다.

Minimum cut phase의 시간복잡도를 $O(f(V, E))$라고 하면, 전체 시간복잡도는 $O(f(V, E) \cdot V)$이다.

만약 **가장 tightness가 큰 정점을 선형탐색**으로 매번 구해주면 $O(V)$, 정점을 총 $V-1$번 찾게되므로 $f(V, E) = V^2$이다.

선형탐색 대신 **피보나치 힙**을 이용하면, 정점 $v$를 집합 $A$에 추가할 때

- $v$를 피보나치 힙에서 제거
- 집합 $A$에 속하지 않은 정점들 중 $v$와 연결된 것들의 tightness를 업데이트

를 수행해야한다.

각 정점을 피보나치 힙에서 한 번씩 제거하므로 $O(V \log V)$, 간선의 개수만큼 tightness를 업데이트해주므로 $O(E)$의 시간복잡도를 가진다.

따라서 피보나치 힙을 이용하면 $f(V, E) = V \log V + E$ 이다.

---

### 3-4. Implementation - Linear search

시간복잡도: $O(V^3)$

```cpp
#include <iostream>
#include <memory.h>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;
const int N = 500;

int n, w[N][N], t[N]; // w(i, j), tight(i)
bool merged[N], inA[N];

int upd(int v) { // update tightness
    int mx = -1, idx;
    for (int i = 0; i < n; i++) {
        if (!merged[i] && !inA[i]) {
            t[i] += w[v][i];
            if (t[i] > mx) {
                mx = t[i];
                idx = i;
            }
        }
    }
    return idx; // return next vertex
}

int stoer_wagner() {
    int ans = 1e9;
    memset(merged, 0, sizeof merged);
    for (int k = 1; k < n; k++) {
        memset(inA, 0, sizeof inA);
        memset(t, 0, sizeof t);
        
        int next, prev;
        for (int i = 0; i < n; i++) if (!merged[i]) { // 1. choose any vertex and insert into A
            inA[i] = 1, prev = i, next = upd(i);
            break;
        }
        
        for (int i = 0; i < n - k - 1; i++) { // 2. insert the "most tightly connected" vertex into A
            prev = next, inA[next] = 1;
            next = upd(next);
        }
        
        ans = min(ans, t[next]);
        merged[next] = 1;
        for (int i = 0; i < n; i++) { // merge s & t (edge contraction)
            w[i][prev] += w[i][next];
            w[prev][i] += w[next][i];
        }
    }
    return ans;
}
```

---

### [BOJ] 13367. Weeping Fig

[BOJ 13367. Weeping Fig 문제 링크](https://www.acmicpc.net/problem/13367)

주어진 그래프의 global minimum cut를 구하는 문제이다.

---

### [BOJ] 14060. Paths in Multigraph

[BOJ 14060. Paths in Multigraph 문제 링크](https://www.acmicpc.net/problem/14060)

두 정점 사이에 여러 개의 간선이 존재하는 multigraph가 주어질 때, 그래프를 두 부분으로 분리하기 위해 제거해야하는 간선의 개수를 구하는 문제이다.

두 정점 $u, v$을 연결하는 간선의 가중치 $w(u, v)$를 주어진 multigraph에서 $u, v$를 연결하는 간선의 개수로 놓고 global minimum cut을 구하면 된다.

---

### [BOJ] 16230. 우리는 진실을 잊고 살잖아

[BOJ 16230. 우리는 진실을 잊고 살잖아 문제 링크](https://www.acmicpc.net/problem/16230)

그래프에 특정 간선의 존재 여부를 알려주는 프로그램이 있고, 가능한 모든 순서쌍 $(i, j)$를 무작위로 섞어 순서대로 프로그램에 넣는다.

주어진 무향 그래프가 연결 그래프인지 알 수 있기 위해 필요한 최소 정보의 개수와 최대 정보의 개수를 구하는 문제이다.

> 연결 그래프임을 알기 위해 필요한 최대 정보의 수: (전체 간선의 개수) - (global minimum cut) + 1
> 
> 연결 그래프임을 알기 위해 필요한 최소 정보의 수: (spanning tree의 간선의 개수) = $V - 1$
> 
> 연결 그래프가 아님을 알기 위해 필요한 최대 정보의 수: (전체 간선의 개수) - ((연결 요소의 개수) - 1) + 1
> 
> 연결 그래프가 아님을 알기 위해 필요한 최소 정보의 수: $M \times (N - M)$, 이때 $M$은 크기가 가장 작은 연결요소의 크기

<br/>

## References

[1] [WIKIPEDIA, 'Max-flow min-cut theorem'](https://en.m.wikipedia.org/wiki/Max-flow_min-cut_theorem)  
[2] [WIKIPEDIA, 'Stoer-Wagner algorithm'](https://en.m.wikipedia.org/wiki/Stoer%E2%80%93Wagner_algorithm)  
