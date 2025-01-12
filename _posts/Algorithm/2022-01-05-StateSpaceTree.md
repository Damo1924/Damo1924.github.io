---
title: "상태공간트리(State-Space Tree)와 탐색 기법들"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` Backtracking, Branch and Bound, A* algorithm

## 1. State-Space Tree

상태공간트리는 문제 해결 과정의 중간 상태들을 노드로 구현한 트리이다.

상태공간트리의 Leaf Node는 문제의 해를 의미하며, 상태공간트리를 탐색함으로써 이 중 최적해(optimum)를 구할 수 있다.

다음의 외판원 순회 문제(TSP)를 생각해보자.

<center><img src="https://user-images.githubusercontent.com/88201512/148074252-150aaace-047d-425b-99e2-599b202a8a0f.jpg" width="70%" height="70%"></center>

위 그래프와 인접행렬에 대한 상태공간트리를 그려보면 다음과 같다.

<center><img src="https://user-images.githubusercontent.com/88201512/148084786-fbc484f9-6606-4ad8-8c37-4000d5ae3a4f.jpg" width="70%" height="70%"></center>

만약 이 트리를 완전탐색하면, 모든 경우의 수를 전부 탐색하는 것이므로 $O(N!)$의 시간복잡도를 갖는다.

도시의 개수 $N$이 10만 넘어가도 완전탐색으로 시간 내에 해결하는 것이 불가능하기 때문에 더 효율적인 방법을 사용해야한다.

이번 포스팅에서는 TSP와 같은 최적해를 구하는 문제들을 상태공간트리를 탐색하여 해결하는 방법들에 대해 다룰 것이다.

<br/>

## 2. Backtracking

상태공간트리의 루트 노드부터 리프 노드까지 DFS로 탐색하며 최적해를 구하는 방법이다.

백트래킹은 탐색을 진행하다가 **더 이상 탐색이 불가능하면, 해당 노드에 대한 탐색을 중단**한다.

이를 **가지치기(pruning)**이라고 부른다.

> 대표적인 백트래킹 문제로 [백준 9663. N-Queen](https://www.acmicpc.net/problem/9663)가 있다.
> 
> 한 줄에 퀸을 하나씩 놓다가, 어느 순간 서로 공격하지 못하도록 퀸을 놓을 수 없게 된다면 해당 노드에 대한 탐색을 중단한다.

<br/>

## 3. Branch and Bound

분기한정법은 최적해가 존재할 가능성이 없는 부분에 대해서는 탐색을 하지 않음으로써 시간을 절약하는 방법이다.

상태공간트리의 어떤 노드에 대해 **유망한지(promising) 판단**하여 유망하지 않다면 해당 노드에 대한 탐색을 중단하는 것을 **가지치기(pruning)**이라고 한다.

예를 들어 어떤 값의 최솟값을 구하는 문제에서, 현재까지 구한 최솟값보다 탐색 중인 노드로 얻을 수 있는 최솟값이 더 크다면 해당 노드에 대한 탐색을 중단하는 것이다.

그렇기 때문에 **분기한정법은 지금까지 구한 최적해가 좋을수록 탐색할 노드의 수가 줄어들게 된다.**

그러므로 **초기에 좋은 해를 찾아서 이후 탐색할 노드들에 대해서 가지치기가 더 많이 일어나도록 해주는 것이 중요하다.**

> 분기한정법은 **최적해를 구하는 문제**에서만 사용할 수 있다.
> 
> 대표적으로 **0-1 Knapsack problem**, **Traveling Salesman problem(TSP)** 등이 있다.
> 
> 각 문제를 분기한정법으로 해결하는 과정은 아래 링크에서 다루고 있다.
> 
> [0-1 Knapsack problem](https://damo1924.github.io/algorithm/01KnapsackProblem/#3-branch-and-bound)
> 
> [Traveling Salesman problem(TSP)](https://damo1924.github.io/ps/BAEKJOON-2098/#solution-2-branch-and-bound)
> 
> 이때 Knapsack problem에서 **무게 당 가치가 높은 물건부터 가방에 넣는 이유는 초기에 좋은 해를 찾기 위함이다.**

더 좋은 해를 빨리 구하기 위한 방법으로 우선순위 큐(priority queue)를 이용해서 탐색하는 Best-First-Search 방식을 택할 수도 있다.

최댓값을 구하는 경우에는 bound가 큰 노드에 우선순위를 부여하고, 최솟값을 구하는 경우에는 bound가 작은 노드에 우선순위를 부여하면 된다.

> **[백트래킹 vs. 분기한정법]**
> 
> 분기한정법은 상태공간트리를 이용하고, 가지치기를 통해 불필요한 탐색을 하지 않는다는 점에서 백트래킹과 비슷한 점이 있다.
> 
> 하지만 백트래킹은 오직 DFS를 통해 트리를 탐색하는 반면, 분기한정법은 DFS, BFS, Best-First-Search(최고 우선 탐색) 등 탐색 방법에 대한 제한이 없다.
> 
> 또한, 백트래킹은 결정 문제 등에서도 사용할 수 있지만, 분기한정법은 최적해를 구하는 문제에 대해서만 사용할 수 있다는 차이점이 있다.

<br/>

## 4. A* algorithm

주어진 출발 지점에서 목표 지점까지 가는 최단 경로를 찾아내는 그래프 탐색 알고리즘이다.

**A* 알고리즘은 각 정점** $v$**에 대해 해당 꼭짓점을 통과하는 최상의 경로를 추정한 휴리스틱 추정값** $h(v)$을 이용한다.

휴리스틱 추정값을 기반으로 각 정점에 대한 평가 함수를 구하고, 우선순위 큐를 이용해 평가 함수로 구한 값의 순서대로 정점을 방문하면서 최단 경로를 찾는 알고리즘이다.

우선순위 큐를 이용하여 최단 경로를 구하는 알고리즘이라는 점에서 다익스트라 알고리즘과 비슷하다.

다만,다익스트라는 출발 지점으로부터 다른 모든 정점까지의 최단 거리를 구하는 알고리즘이지만, A* 알고리즘은 도착 지점까지 정해져 있다.

A* 알고리즘은 출발 지점으로부터 도착 지점까지의 최단 경로를 찾기 위해 각 정점마다 다음과 같은 평가 함수 $f(v)$를 정의한다.

\begin{aligned}
f(v) = g(v) + h(v)
\end{aligned}

- $g(v)$: 출발 정점으로부터 정점 $v$까지의 경로 가중치
- $h(v)$: 정점 $v$로부터 목표 정점까지의 **추정 경로 가중치**

A* 알고리즘은 $h(v)$를 어떻게 구하느냐에 따라서 얼마나 빨리 최단 경로를 찾을 수 있는지가 달라지게 된다.

> A* 알고리즘에 대한 자세한 내용은 [이 포스팅](https://damo1924.github.io/algorithm/AstarSearchAlgorithm/)에서 다루고 있다.









