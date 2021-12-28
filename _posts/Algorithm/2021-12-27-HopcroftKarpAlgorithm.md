---
title: "Hopcroft-Karp Algorithm"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` Bipartite graph, Maximum Matching, Dinic's algorithm, Berge's lemma

## 1. 이분 그래프의 최대 매칭을 구하는 방법들

이분 그래프의 최대 매칭을 구하는 방법에는 크게 두 가지가 있다.

1. 이분 매칭 알고리즘 사용
2. 최대 유량 문제로 변환

이분 그래프의 정점의 개수를 V, 간선의 개수를 E라고 하자.

이분 그래프의 두 정점 집합의 크기를 각각 N, M이라고 한다. (N + M = V)

이분 매칭 알고리즘은 N개의 정점에 대해 크기가 M인 `visited` 배열을 초기화하고, DFS를 수행하므로 시간복잡도는 다음과 같다.

\begin{aligned}
O(NM) + O(N(V + E)) = O(VE)
\end{aligned}

주어진 이분 그래프에 소스와 싱크를 추가하여 최대 유량 문제로 변환하였다.

이때 Edmond-Karp 알고리즘을 사용할 때의 시간복잡도는 다음과 같다.

\begin{aligned}
O(fE) = O(VE)
\end{aligned}

이때 $f$는 최대 유량인데, 이 경우에는 최대 유량이 전체 정점의 개수 V보다 작기 때문에 위와 같이 표현할 수 있다.

그러나 Edmond-Karp 알고리즘을 이용하는 풀이는 이분 매칭 알고리즘을 이용하는 풀이보다 평균적으로 더 오래 걸리며, 메모리도 더 많이 사용한다.

그렇기 때문에 일반적으로 이분 그래프의 최대 매칭을 구하는 문제는 이분 매칭 알고리즘을 사용해서 해결한다.

> 위에서 다룬 이분 그래프의 최대 매칭 문제를 푸는 알고리즘에 대해 궁금하다면 [이 포스팅](https://damo1924.github.io/algorithm/BipartiteMatching/)을 참고.

<br/>

## 2. Hopcroft-Karp Algorithm

이제 본격적으로 Hopcroft-Karp 알고리즘에 대해 알아보자.

Hopcroft-Karp 알고리즘은 이분 그래프의 최대 매칭 문제를 $O(E \sqrt{V})$로 해결할 수 있다.

만약 간선이 많은 밀집 그래프라면, $O(V^{2.5})$가 된다.

이는 위에서 살펴본 두 가지 풀이보다 확실히 더 작은 시간복잡도를 갖고 있음을 알 수 있다.

Hopcroft-Karp Algorithm은 다음과 같다.

---

1. 이분 그래프 $G(U \cup V, E)$에 대해서 $M \subseteq E$인 매칭 $M$을 생각하자.
2. $M$을 공집합으로 놓고, 다음 과정을 반복한다.
3. $M$에 대한 augmenting path 중 길이가 가장 짧은 것들의 집합 $P = \\{P_1, P_2, \dots, P_k\\}$를 구한다. 만약 집합 $P$가 공집합이면 종료한다.
4. 매칭 $M$을 $M \oplus (P_1 \cup P_2 \cup \dots \cup P_k)$로 갱신한다.

---

이때 $M \oplus P_i$는 augmenting path $P_i$에 있는 간선들 중 $M$에 속하는 것들은 매칭에서 제거하고, $M$에 속하지 않는 것들을 매칭에 추가하는 작업을 뜻한다.

이 방법을 통해 augmenting path로 매칭의 크기를 늘릴 수 있게 된다.

3번 과정에서 집합 $P$의 원소들을 구하는 과정은 BFS와 DFS로 구현하기 때문에 $O(E)$의 시간복잡도를 가지고, 이 과정이 최대 $\sqrt{V}$번 반복되기 때문에 전체 알고리즘의 시간복잡도는 $O(E \sqrt{V})$가 된다.

이제, 알고리즘의 타당성을 증명해보고, 시간복잡도를 어떻게 구하는지 살펴보자.

<br/>

## 3. 알고리즘의 타당성 증명

알고리즘의 타당성을 증명해보기 위해 이전 포스팅들에서 다루었던 그래프 관련 개념들과 정리들을 사용할 것이다.

- **Matching**: 끝점을 공유하지 않는 간선들의 집합
- **Matched / Exposed**: 어떤 정점이 matched 되었다는 것은 Matching에 있는 간선들 중 해당 정점을 끝점으로 하는 간선이 존재한다는 것이고, 그렇지 않다면 그 정점이 exposed 되었다고 표현한다.
- **Alternating Path**: 그래프 상에 존재하는 경로들 중 매칭에 포함되는 간선들과 매칭에 포함되지 않은 간선들이 번갈아 나타나는 경로
- **Augmenting Path**: 양 끝 정점이 모두 매칭되지 않은 alternating path

---

**[Lemma 1]** 그래프 $G$의 임의의 매칭 $M$과 $M'$에 대해 $M$과 $M'$의 대칭차(symmetric difference)에 속하는 간선들만을 선택하여 만든 그래프를 $G'$이라고 하자. $G'$은 다음의 연결요소(connected componentes)들로 구성되어 있다.

1. An isolated **vertex**
2. An even **cycle** whose edges alternate between $M$ and $M'$
3. A **path** whose edges alternate between $M$ and $M'$, with distinct endpoints

> ***Proof.***
> 
> 그래프 $G'= (M - M') \cup (M' - M)$의 각 정점은 최대 두 개의 간선과 연결되어 있을 수 있다.
> 
> 모든 정점의 차수(degree)가 2 이하인 그래프는 독립된 정점(isolated vertice), 사이클(cycle), 경로(path)로 구성된다.
> 
> 또한, 차수가 2인 정점에 연결된 두 간선들은 반드시 하나는 $M$, 다른 하나는 $M'$에 속한다.
> 
> 즉, 그래프 위의 모든 사이클과 경로는 $M$에 속하는 간선들과 $M'$에 속하는 간선들이 번갈아 나타나게 된다.(alternates between M & M')
> 
> 사이클의 경우, $M$과 $M'$에 속하는 간선들의 개수가 같아야 위 조건을 만족하므로 길이가 반드시 짝수이다.(even cycle)

---

**[Lemma 2]**(Berge's Lemma) 매칭 $M$이 최대 매칭일 필요충분조건은 $M$에 대한 augmenting path가 존재하지 않는 것이다.

> ***Proof.***
> 
> $(\to)$
> 
> 최대 매칭 $M$에 대한 augmenting path $P$가 존재하면, $M \oplus P$는 $M$보다 크기가 1 더 큰 매칭이다.
> 
> 이는 $M$이 최대 매칭이라는 것에 모순이다.
> 
> $\therefore$ 귀납법에 의해 $M$이 최대 매칭이면 $M$에 대한 augmenting path는 존재하지 않는다.
> 
> $(\gets)$
> 
> 그래프 $G$의 두 매칭 $M$과 $M'$에 대해 $M'$의 크기가 $M$보다 더 크다고 하자.
> 
> $M$과 $M'$의 대칭차집합인 그래프 $D = (M - M') \cup (M' - M)$를 생각하자.
> 
> **Lemma 1**에 의해 $D$에는 $M$과 $M'$에 속하는 간선들이 번갈아 나타나는 경로가 존재한다.
> 
> $M'$이 $M$보다 크기가 크기 때문에 $D$에는 $M$보다 $M'$에 속하는 간선들이 더 많은 경로 $P$가 존재한다.
> 
> $P$는 그래프 $G$의 매칭 $M$에 대한 augmenting path이다.
> 
> 가정에 의해 $M'$의 크기가 $M$보다 크기 때문에 $M$은 최대 매칭이 아니다.
> 
> $\therefore$ 매칭 $M$이 최대 매칭이 아니면, $M$에 대한 augmenting path가 존재한다.
> 
> 명제가 참이면 대우도 참이다.

---

**[Lemma 3]** 그래프 $G$의 최대 매칭을 $M_{max}$라고 할 때, $G$의 임의의 매칭 $M(M \neq M_{max})$에 대해 길이가 $L$을 넘지 않는 augmenting path가 존재한다.

\begin{aligned}
L = 2 \left\lfloor \frac{\left\vert M \right\vert}{\left\vert M_{max} \right\vert - \left\vert M \right\vert} \right\rfloor + 1
\end{aligned}

> ***Proof.***
> 
> **Lemma 2**를 증명할 때와 동일한 상황을 생각하자.
> 
> 그래프 $G$의 두 매칭 $M$과 $M'$에 대해 $M'$의 크기가 $M$보다 더 크다.
> 
> $M$과 $M'$의 대칭차집합인 그래프 $D = (M - M') \cup (M' - M)$를 생각하자.
> 
> **Lemma 1**에 의해 $D$에는 $M$과 $M'$에 속하는 간선들이 번갈아 나타나는 경로가 존재한다.
> 
> $M'$이 $M$보다 크기가 크기 때문에 $D$에는 $M$보다 $M'$에 속하는 간선들이 더 많은 경로 $P_i$가 존재한다.
> 
> $P_i$는 그래프 $G$의 매칭 $M$에 대한 augmenting path이고, 이러한 경로들 중 서로 정점을 공유하지 않는 경로들의 집합을 $P = \\{P_1, P_2, \dots, P_k\\}$라고 하면 다음이 성립한다.
> 
> \begin{aligned}
> \left\vert M' \right\vert - \left\vert M \right\vert \leq \left\vert P \right\vert
> \end{aligned}
> 
> 비둘기집 원리에 의해 어떤 $P_i \in P$는 $M$에 포함된 간선 $\left\lfloor \frac{\left\vert M \right\vert}{\left\vert M_{max} \right\vert - \left\vert M \right\vert} \right\rfloor$개 포함하고 있음을 알 수 있다.
> 
> $P_i$는 $M$에 대한 augmenting path이므로 $P_i$의 길이는 $L = 2 \left\lfloor \frac{\left\vert M \right\vert}{\left\vert M_{max} \right\vert - \left\vert M \right\vert} \right\rfloor + 1$이 된다.
> 
> $\therefore$ $M$이 최대 매칭이 아닐 때, 조건을 만족하는 $M$에 대한 augmenting path가 존재한다.

---

**[Lemma 4]** 매칭 $M$에 대한 augmenting path 중 길이가 가장 짧은 것을 $P$라고 하자. 새로운 매칭 $M \oplus P$에 대한 임의의 augmenting path $P'$에 대해 $\left\vert P' \right\vert \geq \left\vert P \right\vert + 2 \left\vert P \cap P' \right\vert$이 성립한다.

> ***Proof.***
> 
> 새로운 매칭 $M'$을 다음과 같이 정의하자.
> 
> $M' := M \oplus P \oplus P'$
> 
> $M'$은 $M$에서 augmenting path의 간선들을 매칭에 더하고 빼는 작업을 두 번 수행한 매칭이므로 $\left\vert M' \right\vert = \left\vert M \right\vert + 2$이다.
> 
> $M$과 $M'$의 대칭차집합에 속한 간선들로 구성된 그래프 $D$를 생각하자.
> 
> **Lemma 1**에 의해 $D$에는 $M$과 $M'$에 속하는 간선들이 번갈아 나타나는 경로가 존재하고, 이 경로는 $M$에 대한 augmenting path이다.
> 
> $\left\vert M' \right\vert = \left\vert M \right\vert + 2$이므로 서로 정점을 공유하지 않는 $M$에 대한 augmenting path가 적어도 두 개 존재한다.
> 
> 이때 $P$는 $M$에 대한 augmenting path 중 가장 짧은 것이므로 $M$과 $M'$의 대칭차 $M \oplus M'$에 대해 다음이 성립한다.
> 
> (1) $\left\vert M \oplus M' \right\vert \geq 2 \left\vert P \right\vert$
> 
> $M' = M \oplus P \oplus P'라는 사실을 이용하면, $M \oplus M'$는 다음과 같이 정리된다.
> 
> $M \oplus M' = M \oplus M \oplus P \oplus P' = P \oplus P$
> 
> 이를 이용하면 다음을 얻을 수 있다.
> 
> (2) $\left\vert M \oplus M' \right\vert = \left\vert P \oplus P' \right\vert = \left\vert P \right\vert + \left\vert P' \right\vert - 2 \left\vert P \cup P' \right\vert$
> 
> 식 (1)과 (2)를 이용하면 $\left\vert P' \right\vert \geq \left\vert P \right\vert + 2 \left\vert P \cap P' \right\vert$가 된다.

---

그래프 $G(V, E)$의 매칭 $M_i \subseteq E$를 생각하자.

$M_i$의 augmenting path 중 길이가 가장 짧은 것을 $P_i$라고 하자.

이때 $M_{i+1}$는 $M_i \oplus P_i$로 정의한다.

$M_0$을 공집합으로 정의한다면, 모든 $i = 0, \dots, k$에 대해 $\left\vert M_i \right\vert = i$를 만족한다.

$k$는 그래프 $G$의 최대 매칭의 크기가 된다.

아래는 **Lemma 4**의 따름정리이다.

---

**[Corollary]** 모든 $i = 1, \dots k-1$에 대해 $\left\vert P_i \right\vert \leq \left\vert P_{i+1} \right\vert$이다.

---

**[Lemma 5]** $\left\vert P_1 \right\vert, \left\vert P_2 \right\vert, \dots, \left\vert P_k \right\vert$ 중 서로 다른 숫자의 개수는 $2 \lfloor \sqrt{k} \rfloor + 2$보다 작거나 같다.

> ***Proof.***
> 
> 상수 $t$를 다음과 같이 정의하자.
> 
> $t := \lfloor k - \sqrt{k} \rfloor$
> 
> 매칭 $M_i$의 정의에 의해 $\left\vert M_t \right\vert = t$이고, **Lemma 3**에 의해
> 
> $\left\vert P_{t+1} \right\vert \leq 2 \left\lfloor \frac{t}{k - t} \right\rfloor + 1 \leq 2 \lfloor \sqrt{k} \rfloor + 1$
> 
> 을 얻을 수 있다.
> 
> **Lemma 4**의 따름정리에 의해 다음이 성립한다.
> 
> $\left\vert P_1 \right\vert \leq \left\vert P_2 \right\vert \leq \dots \leq \left\vert P_t \right\vert \leq \left\vert P_{t + 1} \right\vert \leq 2 \lfloor \sqrt{k} \rfloor + 1$
> 
> $P_1, P_2, \dots P_{t+1}$은 모두 augmenting path이므로 길이가 홀수이다.
> 
> 그러므로 $\left\vert P_1 \right\vert, \leq \left\vert P_2 \right\vert, \dots, \left\vert P_t \right\vert$는 $2 \lfloor \sqrt{k} \rfloor + 1$보다 작거나 같은 $\lfloor \sqrt{k} \rfloor + 1$개의 홀수 중 하나이다.
> 
> $\left\vert P_{t+1} \right\vert, \dots, \left\vert P_{k} \right\vert$들은 최대 $k - t = \lceil k \rceil$개의 서로 다른 숫자들로 이루어질 수 있기 때문에 전체 $\left\vert P_1 \right\vert, \left\vert P_2 \right\vert, \dots, \left\vert P_k \right\vert$ 중 서로 다른 숫자의 개수의 최댓값은 다음과 같다.
> 
> $\lfloor \sqrt{k} \rfloor + 1 + \lceil k \rceil \leq 2 \lfloor \sqrt{k} \rfloor + 2$

---

**[Lemma 6]** 서로 다른 $i, j$에 대해서 $\left\vert P_i \right\vert = \left\vert P_j \right\vert$이면, $P_i$와 $P_j$는 서로 정점을 공유하지 않는다.

> ***Proof.***
> 
> 


Hopcroft-Karp 알고리즘은 크게 두 가지 방법으로 설명이 가능하다.

1. Hungarian algorithm처럼 **Augmenting Path**를 이용하는 방법
2. 최대 유량 문제로 바꾸어서 **Dinic's Algorithm**을 이용하는 방법

두 가지 방법으로 알고리즘을 이해해보도록 하자.

---

### 2-1. Using Augmenting Path

> Augmenting Path를 이용한 방법은 **Hungarian Algorithm**과 동일한 원리이다.
> 
> [할당 문제와 헝가리안 알고리즘](https://damo1924.github.io/algorithm/HungarianAlgorithm1/)
> 
> [헝가리안 알고리즘의 구현](https://damo1924.github.io/algorithm/HungarianAlgorithm2/)
> 
> 만약 자세한 설명이나 증명을 원한다면 두 번째 포스팅을 참고!

Augmenting Path는 다음과 같은 특징을 가지고 있다.

**1) 그래프의 어떤 매칭이 Maximum matching이기 위한 필요충분조건은 매칭에 대한 Augmenting path가 존재하지 않는 것이다.**

**2) Augmenting Path를 이용하면 현재 매칭보다 크기가 1 커진 매칭을 얻을 수 있다.**

그러므로 **현재 매칭에 대한 Augmenting Path를 찾고, 해당 경로를 이용해서 매칭의 크기를 늘려가면 최대 매칭을 구할 수 있을 것이다.**

---

### 2-2. Using Dinic's Algorithm

주어진 이분 그래프에 소스와 싱크를 추가해서 최대 유량 문제로 바꾸면 Dinic's algorithm을 사용할 수 있게 된다.

> Dinic's algorithm에 대한 설명은 [이 포스팅](https://damo1924.github.io/algorithm/MaximumFlow/#4-dinics-algorithm)을 참고

Dinic's algorithm은 그래프의 각 간선에 흐를 수 있는 최대 유량이 주어져 있을 때, 소스(source)에서 싱크(sink)로 흐를 수 있는 최대 유량을 구하는 문제를 해결하는데 사용하는 알고리즘이다.

일반적인 그래프에 대한 시간복잡도는 $O(V^2 E)$인데, 특히 모든 간선의 용량이 1인 경우에는 $O(\min(V^{2/3}, E^{1/2})E)$가 된다.

지금 다루고 있는 **이분 그래프에 소스와 싱크를 추가한 그래프**에 대해서는 $O(E \sqrt{V})$의 시간복잡도를 갖는다.





## References

[1] [WIKIPEDIA, 'Berge's lemma'](https://en.m.wikipedia.org/wiki/Berge%27s_lemma)  
[2] [WIKIPEDIA, 'Hopcroft-Karp algorithm'](https://en.m.wikipedia.org/wiki/Hopcroft%E2%80%93Karp_algorithm)  

