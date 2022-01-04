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

<img src="https://user-images.githubusercontent.com/88201512/148074252-150aaace-047d-425b-99e2-599b202a8a0f.jpg" width="70%" height="70%">

위 그래프와 인접행렬에 대한 상태공간트리를 그려보면 다음과 같다.

<img src="https://user-images.githubusercontent.com/88201512/148084786-fbc484f9-6606-4ad8-8c37-4000d5ae3a4f.jpg" width="70%" height="70%">

만약 이 트리를 완전탐색하면, 모든 경우의 수를 전부 탐색하는 것이므로 $O(N!)$의 시간복잡도를 갖는다.

이번 포스팅에서는 TSP와 같은 최적해를 구하는 문제들을 상태공간트리를 탐색하여 해결하는 방법들에 대해 다룰 것이다.

<br/>

## 2. Backtracking



<br/>

## 3. Branch and Bound



<br/>

## 4. A* algorithm



## Reference

[1]









