---
title: "헝가리안 알고리즘(Hungarian algorithm) 구현하기(with. Augmenting path)"
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

하지만 해당 알고리즘의 시간복잡도는 $O(VE)$으로, 직원과 작업의 수인 $N$으로 표현하면 $O(N^3)$이다.

이러한 작업을 반복문을 수행할 때마다 하는 것은 매우 비효율적이다.

또한, 저번 포스팅에서 증명한 것은 이 과정을 계속해서 반복하다보면 결국에는 답을 얻을 수 있다라는 것일 뿐, 이 과정을 최대 몇 번 반복하면 답을 얻을 수 있는지에 대한 단서는 없었다.

그러므로 효율적인 알고리즘을 구현하기 위해서는 빠른 시간 내에 이분 그래프의 minimum vertex cover의 크기를 구하는 것이 필요하다.

<br/>

## 2. 문제 정의

> - **Matching**: 어느 두 간선도 끝점을 공유하지 않는 간선들의 부분집합으로, 어떤 정점이 매칭되었다는 것은 matching에 있는 간선들 중 해당 정점을 끝점으로 하는 간선이 존재한다는 것을 의미한다.
> - **Alternating path**: 그래프 상에 존재하는 경로들 중 matching에 포함되는 간선들과 matching에 포함되지 않는 간선들이 번갈아 나타나는 경로
> - **Augmenting path**: 양쪽 끝 정점이 모두 매칭되지 않은 alternating path

위 알고리즘의 5번 과정을 반복하고 있는 상황을 생각하자.

현재 행렬을 $c$라고 할 때, $c_{ij} = 0$을 만족하는 직원 $i$와 작업 $j$를 잇는 간선들의 집합을 $E_c$라고 정의하자.

$I$, $J$의 원소들과 $E_c$에 속하는 간선들로 이루어진 이분 그래프를 $G$라고 한다.

**[목표]** $G$의 Minimum vertex cover의 크기

그래프 $G$의 Maximum matching을 $M_{max} \subseteq E_c$이라고 하자.

$U$: $I$의 원소 중 $M_{max}$에 대해 매칭되지 않은 정점들의 집합

$Z$: $U$의 정점들로부터 $M_{max}$에 대한 alternating path를 통해 접근이 가능한 정점들의 집합

$S = Z \cap X$

$T = Z \cap Y$

$N(S)$: $S$의 정점들에 인접한 정점들의 집합

> **[Konig's Theorem]** 이분 그래프의 Minimum vertex cover의 크기와 Maximum matching의 크기는 동일하다.
>
> **[Berge's Lemma]** 그래프의 어떤 매칭이 Maximum matching이기 위한 필요충분조건은 매칭에 대한 Augmenting path가 존재하지 않는 것이다.
>
> **[Lemma 1]** $U$의 정점에서 $S$의 정점까지의 alternating path는 $M_{max}$에 포함된 간선으로 끝나고, $U$의 정점에서 $T$의 정점까지의 alternating path는 $M$에 포함되지 않은 간선으로 끝난다.
>
> **[Lemma 2]** $N(S) = T$
>
> **[Lemma 3]** 집합 $K = (X \setminus S) \cup T$는 그래프 $G$의 Minimum vertex cover이다.

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
  - 현재 매칭의 크기가 $N$보다 작다면 반복문을 수행한다.

따라서 주어진 매칭에 대해서 augmenting path를 찾을 수 있다면, 이분 그래프의 minimum vertex cover도 구할 수 있다.

<br/>

## 4. Finding Augmenting Path

주어진 매칭 $M$에 대한 augmenting path를 구하는 과정에 대해 알아보자.

**1)** $I$에서 매칭되지 않은 정점 $u$를 선택하여 집합 $S = \\{u\\}$, $T = \\empty$이라 한다.

> 집합 $S$는 augmenting path에 포함된 $I$의 정점들, 집합 $T$는 augmenting path에 포함된 $J$의 정점들을 의미한다.

**2)** $N(S) = T$이면 현재까지 구한 Augmenting path에서 더 늘리는 것이 불가능하므로 행렬을 변환해서 간선을 갱신한다.

**3)** $N(S) \neq T$을 만족할 때, $j \in N(S) - T$인 정점 $j$를 하나 선택한다.

**3-1)** 만약 $j$가 매칭되지 않은 정점이면 현재 경로는 augmenting path이므로 경로를 이용해서 매칭의 크기를 늘린 후, 1번으로 돌아간다.

**3-2)** $j$가 매칭된 정점이면, 현재 경로에 $j$와 $j$와 매칭된 정점을 추가하고 2번으로 돌아간다.










## Reference

[1] [Samsung Softwarer Membership, '헝가리안 알고리즘'](http://www.secmem.org/blog/2021/04/18/hungarian-algorithm/)  

