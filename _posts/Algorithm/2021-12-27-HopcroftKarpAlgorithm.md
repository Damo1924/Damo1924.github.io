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

`Tags` Bipartite graph, Maximum Matching, Dinic's algorithm

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

## 3. 알고리즘의 시간복잡도 구하기 & 타당성 증명

다음은 그래프 이론에서 사용하는 용어들이다.

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
> 즉, 그래프 위의 모든 사이클과 경로는 $M$에 속하는 간선들과 $M'$에 속하는 간선들이 번갈아 나타나게 된다.
> 
> 사이클의 경우, $M$과 $M'$에 속하는 간선들의 개수가 같아야 위 조건을 만족하므로 길이가 반드시 짝수이다.

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
> \begin{aligned}
> M' := M \oplus P \oplus P'
> \end{aligned}
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
> \begin{aligned}
> \left\vert M \oplus M' \right\vert \geq 2 \left\vert P \right\vert \dots (1)
> \end{aligned}
> 
> $M' = M \oplus P \oplus P'$라는 사실을 이용하면, $M \oplus M'$는 다음과 같이 정리된다.
> 
> \begin{aligned}
> M \oplus M' = M \oplus M \oplus P \oplus P' = P \oplus P
> \end{aligned}
> 
> 이를 이용하면 다음을 얻을 수 있다.
> 
> \begin{aligned}
> \left\vert M \oplus M' \right\vert = \left\vert P \oplus P' \right\vert = \left\vert P \right\vert + \left\vert P' \right\vert - 2 \left\vert P \cap P' \right\vert \dots (2)
> \end{aligned}
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

**[Corollary 1]** 모든 $i = 1, \dots k-1$에 대해 $\left\vert P_i \right\vert \leq \left\vert P_{i+1} \right\vert$이다.

---

**[Lemma 5]** $\left\vert P_1 \right\vert, \left\vert P_2 \right\vert, \dots, \left\vert P_k \right\vert$ 중 서로 다른 숫자의 개수는 $2 \lfloor \sqrt{k} \rfloor + 2$보다 작거나 같다.

> ***Proof.***
> 
> 상수 $t$를 다음과 같이 정의하자.
> 
> \begin{aligned}
> t := \lfloor k - \sqrt{k} \rfloor
> \end{aligned}
> 
> 매칭 $M_i$의 정의에 의해 $\left\vert M_t \right\vert = t$이고, **Lemma 3**에 의해
> 
> \begin{aligned}
> \left\vert P_{t+1} \right\vert \leq 2 \left\lfloor \frac{t}{k - t} \right\rfloor + 1 \leq 2 \lfloor \sqrt{k} \rfloor + 1
> \end{aligned}
> 
> 을 얻을 수 있다.
> 
> **Lemma 4**의 따름정리에 의해 다음이 성립한다.
> 
> \begin{aligned}
> \left\vert P_1 \right\vert \leq \left\vert P_2 \right\vert \leq \dots \leq \left\vert P_t \right\vert \leq \left\vert P_{t + 1} \right\vert \leq 2 \lfloor \sqrt{k} \rfloor + 1
> \end{aligned}
> 
> $P_1, P_2, \dots P_{t+1}$은 모두 augmenting path이므로 길이가 홀수이다.
> 
> 그러므로 $\left\vert P_1 \right\vert, \leq \left\vert P_2 \right\vert, \dots, \left\vert P_t \right\vert$는 $2 \lfloor \sqrt{k} \rfloor + 1$보다 작거나 같은 $\lfloor \sqrt{k} \rfloor + 1$개의 홀수 중 하나이다.
> 
> $\left\vert P_{t+1} \right\vert, \dots, \left\vert P_{k} \right\vert$들은 최대 $k - t = \lceil k \rceil$개의 서로 다른 숫자들로 이루어질 수 있기 때문에 전체 $\left\vert P_1 \right\vert, \left\vert P_2 \right\vert, \dots, \left\vert P_k \right\vert$ 중 서로 다른 숫자의 개수의 최댓값은 다음과 같다.
> 
> \begin{aligned}
> \lfloor \sqrt{k} \rfloor + 1 + \lceil k \rceil \leq 2 \lfloor \sqrt{k} \rfloor + 2
> \end{aligned}

---

**[Lemma 6]** 모든 $i = 0, 1, \dots, k-1$에 대해서 $\left\vert P_i \right\vert = \left\vert P_{i+1} \right\vert$이면, $P_i$와 $P_{i+1}$은 서로 간선과 정점을 공유하지 않는다.

> ***Proof.***
> 
> $\left\vert P_{i+1} \right\vert = \left\vert P_i \right\vert$이면, **Lemma 4**에 의해 다음을 얻을 수 있다.
> 
> \begin{aligned}
> \left\vert P_i \cap P_{i+1} \right\vert = 0
> \end{aligned}
> 
> 즉, $P_i$와 $P_{i+1}$은 서로 간선을 공유하지 않는다.
> 
> 이때 $P_i$와 $P_{i+1}$이 어떤 정점 $v \in V$를 공유한다고 가정하자.
> 
> i) $v$가 $P_i$의 양 끝점인 경우
> 
> $P_i$ 위에 있으면서 $v$에 연결된 간선을 $e$라고 하면, $M_{i+1} = M_i \oplus P_i$이므로 $e \in M_{i+1}$이다.
> 
> $M_{i+1}$에 대한 augmenting path $P_{i+1}$이 정점 $v$를 지나야하므로 반드시 간선 $e$를 포함해야한다.
> 
> ii) $v$가 $P_i$의 양 끝점이 아닌 경우
> 
> $P_i$ 위에 있으면서 $v$에 연결된 간선 중 $M_i$에 속하는 간선을 $e$라고 하자.
> 
> 위와 마찬가지로 $e \in M_{i+1}$이므로 $P_i$는 반드시 간선 $e$를 포함해야한다.
> 
> i), ii) 두 경우 모두 $P_i$와 $P_{i+1}$이 간선을 공유하지 않는다는 것에 모순인 결과가 얻었다.
> 
> $\therefore$ 수학적 귀납법에 의해 $P_i$와 $P_{i+1}$은 서로 정점을 공유하지 않는다.

---

다음은 **Lemma 6**의 따름정리이다.

---

**[Corollary 2]** 서로 다른 $i, j$에 대해 $\left\vert P_i \right\vert = \left\vert P_j \right\vert$이면 $P_i$와 $P_j$는 정점을 공유하지 않는다.

> ***Proof.***
> 
> 일반성을 잃지 않고 $i < j$ 라고 할 수 있다.
> 
> $P_i$와 $P_j$가 정점을 공유한다고 가정하면, $i \leq s < j$ 를 만족하는 어떤 $s$에 대해 $P_s$와 $P_{s+1}$이 정점을 공유한다.
> 
> **Lemma 4**의 따름정리에 의해 $\left\vert P_s \right\vert = \left\vert P_{s+1} \right\vert$ 이다.
> 
> **Lemma 6**에 의해 $P_s$와 $P_{s+1}$은 서로 정점을 공유하지 않는다.
> 
> 이는 가정에 모순이므로 수학적 귀납법에 의해 $P_i$와 $P_j$는 정점을 공유하지 않는다.

---

우리는 **Lemma 5**를 통해 Hopcroft-Karp 알고리즘의 시간복잡도를 구할 수 있다.

DFS를 통해 $\left\vert P_i \right\vert = \dots = \left\vert P_j \right\vert$($i < j$)를 만족하는 augmenting path를 구하는 과정은 $O(V + E)$의 시간복잡도를 갖는다.

마지막에 직접 알고리즘을 구현할 때 다루겠지만, Augmenting path를 구하기 위해서는 BFS로 그래프 전체를 탐색할 필요가 있는데, 이 과정도 $O(V + E)$의 시간복잡도를 갖는다.

이때 **Lemma 6의 따름정리**에 의해 길이가 같은 경로들은 서로 정점을 공유하지 않기 때문에 여러 개의 경로들을 한 번에 구할 수 있음을 알 수 있다.

이제 위 과정을 최대 몇 번이나 반복하는지를 구하면 되는데, **Lemma 5**에 의해 $\left\vert P_i \right\vert$가 가질 수 있는 값의 개수는 $2 \lfloor \sqrt{k} \rfloor + 2$ 이하이다.

그러므로 반복되는 횟수는 $O(\sqrt{V})$라고 할 수 있고, Hopcroft-Karp algorithm의 시간복잡도는 $O(E \sqrt{V})$가 된다.

<br/>

## 4. 최대 유량 문제로 변환 & Dinic's Algorithm 적용

이분 그래프의 최대 매칭 문제는 최대 유량 문제로 변환하여 해결할 수 있다.

주어진 이분 그래프에 소스와 싱크를 추가해서 최대 유량 문제로 바꾸면 Dinic's algorithm을 사용할 수 있게 된다.

> Dinic's algorithm에 대한 설명은 [이 포스팅](https://damo1924.github.io/algorithm/MaximumFlow/#4-dinics-algorithm)을 참고

Dinic's algorithm의 일반적인 그래프에 대한 시간복잡도는 $O(V^2 E)$인데, 특히 모든 간선의 용량이 1인 경우에는 $O(\min(V^{2/3}, E^{1/2})E)$가 된다.

지금 다루고 있는 **이분 그래프에 소스와 싱크를 추가한 그래프**에 대해서는 $O(E \sqrt{V})$의 시간복잡도를 갖는다.

알고리즘에 대해 간략히 설명하면 다음과 같다.

> BFS를 통해 각 정점에 **레벨**을 부여하고, DFS로 **차단 유량(blocking flow)**을 구하는 작업을 반복하는 알고리즘

이를 앞에서 공부한 augmenting path의 관점으로 바라보면,

- BFS를 통해 각 정점에 레벨을 부여하는 것: Augmenting path 찾기
- DFS로 차단 유량을 구하는 것: 각 augmenting path를 탐색하면서 매칭을 업데이트

로 생각할 수 있다.

아래 그림은 이분 그래프에 소스와 싱크를 추가한 다음, 유량을 어느 정도 흘려준 상태의 그래프이다.

<img src="https://user-images.githubusercontent.com/88201512/147640305-38713c7a-16c3-4b80-b76b-c22b57f4552e.jpg" width="65%" height="65%">

노란색으로 표시된 간선은 유량이 흐르고 있는 간선을, 회색 간선은 유량이 흐를 수 있는 간선을 의미한다.

이때 유량이 흐른다는 것은 순방향으로 흐른다는 뜻이며, 노란색 간선의 경우 유량이 역방향으로 흐를 수 있다.

이를 이분 매칭의 관점에서 생각해보면 노란 간선으로 연결된 정점들은 서로 매칭되었다고 할 수 있을 것이다.

그렇다면, 각 정점에 레벨을 부여해보자.

<img src="https://user-images.githubusercontent.com/88201512/147640327-b27ee473-1e82-4d7b-8469-9336841cbb68.jpg" width="65%" height="65%">

레벨을 부여하는 방법은, 현재 정점에서 유량이 흐를 수 있는 정점으로 이동하면서 레벨을 1씩 늘려주는 것이다.

노란색 간선은 역방향으로 유량이 흐를 수 있기 때문에 위 그림처럼 레벨을 부여할 수 있게 된다.

이제 레벨이 증가하는 경로를 따라가며 해당 경로에 유량을 흘려주면 된다.

> 이분 매칭 그래프에서는 모든 간선의 유량이 1이므로 경로에 흐를 수 있는 최대 유량이 항상 1이다.

<img src="https://user-images.githubusercontent.com/88201512/147640344-8af53dcd-32ec-489f-ba94-b8b6284dafbf.jpg" width="65%" height="65%">

그런데 **레벨이 증가하는 경로에서 싱크와 소스를 빼고 본다면, augmenting path임을 알 수 있다.**

소스와 싱크를 제외한 경로는 1-2-3-4-5인데, 매칭에 속하지 않는 간선(=회색 간선)과 매칭에 속하는 간선(=노란색 간선)이 번갈아 등장하고, 양 끝이 모두 매칭에 속하지 않는 경로이므로 augmenting path이다.

즉, **Dinic's algorithm에서 레벨 그래프를 통해 구한 최단 경로는 이분 매칭 문제의 augmenting path로 생각할 수 있다.**

이 경로에 유량을 흘려주면 다음과 같다.

<img src="https://user-images.githubusercontent.com/88201512/147640376-890b359a-fa00-4e51-8001-d1f6d05a9702.jpg" width="65%" height="65%">

유량을 흘려준 결과, 경로 위의 회색 간선이 노란색으로, 노란 간선이 색으로 바뀌게 되었다.

이는 마치 **augmenting path 위의 간선들 중 매칭에 속하는 간선은 매칭에서 제거하고, 매칭에 속하지 않은 간선은 매칭에 추가하는 것과 같다.**

그 결과, 더 이상 싱크 정점에서 소스 정점까지 경로를 찾을 수 없게 되었다.

<img src="https://user-images.githubusercontent.com/88201512/147640414-6972222b-b62a-4b96-b1ad-5644f40ec3ac.jpg" width="65%" height="65%">

소스 정점의 레벨을 갱신할 수 없다는 뜻은 **더 이상 augmenting path가 존재하지 않는다는 것**을 의미하므로, 최대 매칭을 구한 것이다.

이처럼 Hopcroft-Karp algorithm은 최대 유량 문제의 Dinic's algorithm의 특수한 경우로 생각할 수 있다.

<br/>

## 5. 알고리즘 구현하기

Hopcroft-Karp algorithm은 실제로 Dinic's algorithm과 매우 비슷하게 구현할 수 있다.

BFS를 통해 레벨을 부여하고, DFS로 매칭을 시도해주면 된다.

직접 이분 매칭 문제를 풀어보자.

### [백준] 11375. 열혈강호

[백준 11375. 열혈강호 문제 링크](https://www.acmicpc.net/problem/11375)

N명의 직원과 M개의 일이 있고, 각 직원이 할 수 있는 일이 주어질 때 최대 몇 개의 일을 할 수 있는지 구하는 문제이다.

Hopcroft-Karp algorithm으로 구현해보자.

```cpp
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int N, M; // 직원의 수 N, 일의 개수 M

int maxWork = 0; // 최대로 할 수 있는 일의 개수

vector<int> graph[1001]; // 직원 - 할 수 있는 일

int level[1001]; // bfs를 통해 구할 각 직원의 레벨

int A[1001], B[1001]; // 매칭된 정점의 번호

void bfs()
{
    queue<int> q;
    for (int i = 1; i <= N; i++) // 각 정점에 대해,
    {
        if (A[i] == 0) // 아직 매칭이 안된 정점의 레벨을 0으로 초기화
        {
            level[i] = 0;
            q.push(i);
        }
        else level[i] = -1; // 매칭된 정점의 레벨은 -1로 초기화
    }
    
    while (!q.empty()) // BFS로 이분 그래프를 탐색하면서 레벨을 부여한다.
    {
        int x = q.front();
        q.pop();
        for (int i = 0; i < graph[x].size(); i++)
        {
            int y = graph[x][i];
            if (B[y] != 0 && level[B[y]] == -1)
            {
                level[B[y]] = level[x] + 1;
                q.push(B[y]);
            }
        }
    }
}

bool dfs(int x) // 이분 매칭 알고리즘의 원리를 이용
{
    for (int i = 0; i < graph[x].size(); i++)
    {
        int y = graph[x][i];
        if (B[y] == 0 || (level[B[y]] == level[x] + 1 && dfs(B[y]))) // 매칭되지 않았거나, 매칭을 변경할 수 있는 경우
        {
            A[x] = y;
            B[y] = x;
            return true;
        }
    }
    return false;
}

void solve()
{
    while (true)
    {
        bfs(); // O(V + E)
        
        int match = 0;
        for (int i = 1; i <= N; i++)
            if (A[i] == 0 && dfs(i)) match++; // 
        
        if (match == 0) break; // 더 이상 매칭이 불가능하면 break;
        maxWork += match;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> M;
    
    int a, b;
    for (int i = 1; i <= N; i++)
    {
        cin >> a;
        while (a--)
        {
            cin >> b;
            graph[i].push_back(b);
        }
    }

    solve();
    cout << maxWork;
}
```

## References

[1] [WIKIPEDIA, 'Berge's lemma'](https://en.m.wikipedia.org/wiki/Berge%27s_lemma)  
[2] [WIKIPEDIA, 'Hopcroft-Karp algorithm'](https://en.m.wikipedia.org/wiki/Hopcroft%E2%80%93Karp_algorithm)  
[3] [Gazelle and Computer Science, '호프크로프트-카프 알고리즘(Hopcroft-Karp Algorithm)'](https://gazelle-and-cs.tistory.com/35)  




