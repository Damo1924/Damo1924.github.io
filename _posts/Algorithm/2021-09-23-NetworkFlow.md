---
title: "네트워크 플로우(Network Flow) 문제"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

## 1. Network Flow

네트워크 플로우는 특정한 지점에서 다른 지점으로 얼마나 많은 데이터가 흐르고 있는지를 측정하는 알고리즘이다.

이는 교통 체증 해결이나 네트워크 데이터 전송 등 다양한 분야에서 활용되고 있는 알고리즘이다.

그래프에서 각 간선마다 보낼 수 있는 최대 **유량(Flow)**을 **용량(Capacity)**이라고 하며, 그래프의 모든 간선에 대해 용량이 주어질 때 A에서 B로 최대로 보낼 수 있는 유량의 크기를 구하는 문제를 **최대 유량(Max Flow) 문제**라고 한다.

이러한 최대 유량 문제를 해결하는 것이 바로 네트워크 플로우 알고리즘이다.

## 1-1. Edmonds-Karp Algorithm

최대 유량 문제는 일반적으로 모든 경우의 수를 전부 탐색하여 최대 유량을 구하는데, 이때 BFS를 사용하는 방법을 에드워드-카프 알고리즘이라고 부른다.

먼저, BFS를 통해 시작 지점에서 도착 지점까지 

