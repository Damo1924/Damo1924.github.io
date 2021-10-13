---
title: "최단 경로 문제"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

## 1. Shortest Path Problem

그래프 이론에서 어떤 두 정점 사이의 최단 경로를 찾는 문제를 **최단 경로 문제**라고 부른다.

최단 경로 문제는 다음과 같이 나눌 수 있다.

- **단일-쌍 최단 경로 문제**: 어떤 정점 $v$에서 다른 정점 $v'$로 가는 최단 경로를 찾는 문제
- **단일-출발 최단 경로 문제**: 어떤 정점 $v$에서 그래프 내의 모든 다른 정점까지의 최단 경로들를 찾는 문제
- **단일-도착 최단 경로 문제**: 모든 정점들로부터 어떤 정점 $v$로 도착하는 최단 경로들을 찾는 문제
- **전체-쌍 최단 경로 문제**: 그래프 내의 모든 정점 쌍들 사이의 최단 경로들을 찾는 문제

다음은 최단 경로 문제들을 해결하기 위한 주요 알고리즘들이다.

- **Dijkstra algorithm**: 단일-쌍, 단일-출발, 단일-도착 최단 경로 문제
- **Bellman-Ford algorithm**: 단일-출발 최단 경로 문제
- **A* algorithm**: 단일-쌍 최단 경로 문제
- **Floyd-Warshall algorithm**: 전체-쌍 최단 경로 문제



## Reference

[1] [위키백과, '최단 경로 문제'](https://ko.m.wikipedia.org/wiki/%EC%B5%9C%EB%8B%A8_%EA%B2%BD%EB%A1%9C_%EB%AC%B8%EC%A0%9C)  
