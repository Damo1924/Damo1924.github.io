---
title: "헝가리안 알고리즘(Hungarian algorithm) 구현하기(with. Konig's Theorem)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` Assignment Problem, Bipartite graph, Minimum Vertex Cover, Maximum Matching, Berge's Lemma

이번 포스팅은 [저번 포스팅](https://damo1924.github.io/algorithm/HungarianAlgorithm1/)에서 공부한 헝가리안 알고리즘을 어떻게 구현해야하는지에 다루고 있다.

저번 포스팅은 사실 꽤 이해하기 쉬운 내용들이었지만, 이를 $O(N^3)$에 구현하는 것은 또다른 문제이다.

만약 Konig's Theorem을 Augmenting path를 이용해서 증명하는 과정에 대해 알지 못한다면 [이 포스트](https://damo1924.github.io/algorithm/BipartiteMatching/#3-minimum-vertex-cover--konigs-theorem)를 먼저 완벽히 이해하고 오는 것을 추천한다.

<br/>

## 1. Finding Vertex Cover with Augmenting Path

지난 포스팅에서 다룬 헝가리안 알고리즘은 다음과 같이 요약할 수 있다.

> 직원의 집합을 $I$, 작업의 집합을 $J$, 어떤 직원 $i \in I$가 작업 $j \in J$를 하는데 필요한 비용을 $c(i, j)$라고 하자. ($\left\vert I \right\vert = \left\vert J \right\vert = N$)
> 
> $c(i, j)$를 원소로 하는 행렬 $C_{ij}$에 대해 각 행과 열에서 최솟값을 찾아 해당 행과 열의 각 원소에서 최솟값을 빼준다.
> 
> $I$와 $J$의 원소들을 노드로 하고, $C_{ij} = 0$을 만족시키는 $i \in I$와 $j \in J$를 잇는 간선으로 이루어진 이분 그래프를 생각하자.
> 
> 이 이분 그래프의 Minimum Vertex Cover의 크기가 N일 때까지 행렬의 행과 열에 적당한 값을 더하거나 빼주는 과정을 반복한다.

행렬을 만들고 각 행과 열에서 최솟값을 찾아 빼주는 과정은 $O(N^2)$이면 가능하고, 행렬의 행과 열에 더하거나 빼줄 적당한 값을 찾는 것도 $O(N)$이면 가능하다.

위 과정대로 알고리즘을 구현함에 있어 가장 큰 문제는 **매번 Minimum Vertex Cover의 크기**를 구해야한다는 것이다.

Minimum Vertex Cover의 크기를 구하는 것은 최대 유량 문제로 바꾸어서 Edmond-Karp Algorithm을 이용하면 $O(VE)$일 뿐더러, 저번 포스팅에서는 이 과정을 계속해서 수행하다보면 결국에는 결과를 얻을 수 있다는 사실만 증명했지 그 과정이 몇 번 동안 수행되는지에 대해서는 증명한 바가 없다.

그래서 위 문제를 해결하기 위해 Konig's Theorem의 증명에서 사용한 개념들과 각종 소정리들을 이용할 것이다.











## Reference

[1] [Samsung Softwarer Membership, '헝가리안 알고리즘'](http://www.secmem.org/blog/2021/04/18/hungarian-algorithm/)  

