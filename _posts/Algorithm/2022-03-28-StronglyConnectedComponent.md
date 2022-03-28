---
title: "Strongly Connected Component(SCC)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` 강한 연결 요소, Kosaraju's algorithm, Tarjan's algorithm

## 1. Strongly Connected Component

유향 그래프(directed graph)에서 **모든 정점이 다른 모든 정점에 대해 도달 가능**하면 해당 그래프를 **강하게 연결되었다(strongly connected)**라고 한다.

**강한 연결 요소(strongly connected component, SCC)**는 유향 그래프의 부분 그래프 중 강하게 연결된 것을 말한다.

단, **강하게 연결되는 특성이 유지되는 한 포함할 수 있는 정점과 간선을 모두 포함해야한다.**

SCC는 다음과 같은 특징을 갖는다.

- 유향 그래프에 있는 사이클 위의 정점들은 서로 강하게 연결되어 있으므로 하나의 SCC에 포함된다.
- SCC가 존재하지 않는 유향 그래프에는 사이클이 존재하지 않는다.
- 유향 그래프의 **응축(condensation)**은 **유향 비순환 그래프(directed acyclic graph)**이다.

> 유향 그래프 $G$의 응축(condensation)을 $G'$이라고 할 때,
> 
> $G'$은 $G$의 SCC를 정점으로 하고, 두 SCC에 속하는 정점들 사이의 간선들을 간선으로 하는 그래프이다.
> 
> 단, 그래프의 응축은 **multiple edges**를 포함하지 않기 때문에 두 SCC 사이에 여러 개의 간선들이 존재해도 하나의 간선으로 생각한다.

SCC를 선형 시간에 구하는 여러 알고리즘이 존재하는데, 이번 포스팅에서는 **Kosaraju's algorithm**과 **Tarjan's algorithm**에 대해 살펴볼 것이다.

<br/>

## 2. Kosaraju's Algorithm

<br/>

## 3. Tarjan's Algorithm

<br/>

## References

[1] [
