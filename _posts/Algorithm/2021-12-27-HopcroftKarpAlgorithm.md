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

`Tags` Bipartite graph, Maximum Matching, Dinic's algorithm, Hungarian algorithm

## 1. 이분 그래프의 최대 매칭을 구하는 방법들

이분 그래프의 최대 매칭을 구하는 방법에는 크게 두 가지가 있다.

1. 이분 매칭 알고리즘 사용
2. 최대 유량 문제로 변환

이분 그래프의 정점의 개수를 V, 간선의 개수를 E라고 하자.

이분 그래프의 두 정점 집합의 크기를 각각 N, M이라고 한다. (N + M = V)

이분 매칭 알고리즘은 N개의 정점에 대해 크기가 M인 `visited` 배열을 초기화하고, DFS를 수행하므로 시간복잡도는 다음과 같다.

\begin{aligned}
$O(NM) + O(N(V + E)) = O(VE)$
\end{aligned}

주어진 이분 그래프에 소스와 싱크를 추가하여 최대 유량 문제로 변환하였다.

이때 Edmond-Karp 알고리즘을 사용할 때의 시간복잡도는 다음과 같다.

\begin{aligned}
$O(fE) = O(VE)$
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

</br>

## 3. 알고리즘의 타당성 증명

알고리즘의 타당성을 증명해보기 위해 이전 포스팅들에서 다루었던 그래프 관련 개념들과 정리들을 사용할 것이다.

- **Matching**: 끝점을 공유하지 않는 간선들의 집합
- **Matched / Exposed**: 어떤 정점이 matched 되었다는 것은 Matching에 있는 간선들 중 해당 정점을 끝점으로 하는 간선이 존재한다는 것이고, 그렇지 않다면 그 정점이 exposed 되었다고 표현한다.
- **Alternating Path**: 그래프 상에 존재하는 경로들 중 매칭에 포함되는 간선들과 매칭에 포함되지 않은 간선들이 번갈아 나타나는 경로
- **Augmenting Path**: 양 끝 정점이 모두 매칭되지 않은 alternating path

**[Berge's Lemma]** 어떤 매칭 $M$이 최대 매칭일 필요충분조건은 $M$에 대한 augmenting path가 존재하지 않는 것이다.

혹시라도 위 내용에 대한 증명이나 자세한 설명을 원한다면, 아래 두 포스팅을 참고하길 바란다.

> [쾨니그의 정리(Konig's Theorem)와 증명](https://damo1924.github.io/algorithm/BipartiteMatching/#konigs-theorem)
> 
> [Augmenting Path를 이용한 헝가리안 알고리즘의 구현](https://damo1924.github.io/algorithm/HungarianAlgorithm2/)








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







