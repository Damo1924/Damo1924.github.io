---
title: "최소 비용 신장 트리 (Minimum Cost Spanning Tree)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:    
  - Algorithm
use_math: true
comments: true

---

`Tags`: Spanning Tree, Prim Algorithm, Kruskal Algorithm

## 1. Spanning Tree

신장 트리(spanning tree)는 연결 그래프의 모든 정점을 최소한의 간선으로 연결하는 부분 그래프이다.

정점의 개수를 $V$라고 하면 ($V-1$)개의 간선으로 모든 정점을 연결해야하며, 사이클이 없어야한다.

어떤 연결 그래프의 신장 트리는 유일하지 않고, BFS와 DFS를 통해 탐색하여 얻을 수 있다.

<br/>

## 2. Minimum Cost Spanning Tree

최소 비용 신장 트리는 간선에 가중치가 있는 가중치 그래프의 신장 트리 중 간선들의 가중치의 합이 최소가 되는 것을 말한다.

최소 비용 신장 트리를 찾는 대표적인 알고리즘으로 **프림 알고리즘(Prim algorithm)**과 **크루스칼 알고리즘(Kruskal algorithm)**이 있다.

이번 포스트에서는 위의 두 알고리즘에 대해 알아보고, 관련 문제도 풀어볼 것이다.

<br/>

## 3. Prim Algorithm

프림 알고리즘은 그리디 알고리즘에 기반하여 최소 비용 신장 트리를 찾는 알고리즘이다.

간단히 설명하면, **하나의 정점에서 시작해서 연결된 간선 중 가중치가 최소인 것을 계속 더해가는 방법**이다.

프림 알고리즘은 다음과 같은 단계를 따른다.

1. 최소 비용 신장 트리를 찾기 시작할 정점을 선택한다. (아무 정점이나 선택해도 된다.)
2. 트리와 아직 방문하지 않은 정점들을 연결하는 간선들 중 가중치가 가장 작은 것을 선택해서 트리에 더해준다.
3. 모든 정점이 트리에 포함될 때까지 2번을 반복한다.

















