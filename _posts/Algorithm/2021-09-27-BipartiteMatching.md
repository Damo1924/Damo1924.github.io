---
title: "이분 매칭(Bipartite Matching) 알고리즘"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

## 1. Bipartite Matching

정점을 두 개의 집단으로 나누었을 때, 존재하는 모든 간선의 양 끝 정점이 서로 다른 집단에 속하는 그래프를 **이분 그래프(Bipartite Graph)**라고 부른다.

**이분 매칭(Bipartite Matching) 알고리즘**이란, 이분 그래프의 두 집단을 A, B라고 할 때 A 집단이 B 집단을 선택하는 방법에 대한 알고리즘이다.

A 집단이 B 집단을 선택하는 경우의 수는 다양하지만, 그 중 가장 효과적이라고 할 수 있는 것은 가장 많은 정점들이 연결되는 경우이다.

이를 **최대 매칭(Max Matching)**이라고 부르며, 일반적으로 이분 그래프에서 최대 매칭 문제는 최대 유량(Maximum Flow) 문제로 바꾸어서 해결한다.

두 정점 집단을 각각 A, B라고 하면 우리는 다음과 같은 그래프를 그릴 수 있다.

<img src="https://user-images.githubusercontent.com/88201512/134833829-bda6493a-0293-47bc-9682-7c482d03fbdb.jpg" width="80%" height="80%">

A, B에 속하는 정점 이외에 소스(source)와 싱크(sink)의 역할을 할 두 정점을 추가하고, 소스와 A에 속하는 정점들을 모두 연결하고 싱크와 B에 속하는 정점들을 모두 연결한 뒤, 모든 간선들의 용량을 1로 설정해준다.

이 그래프에 대해 최대 유량을 구하면 그 값은 기존 이분 그래프의 최대 매칭 수와 동일하므로,[이전 포스트](https://damo1924.github.io/algorithm/MaximumFlow/)에서 다룬 알고리즘들을 이용해서 해결할 수 있다.


<br/>

## 2. Using Ford-Fulkerson Algorithm

이 그래프에 대해 DFS/BFS와 Ford-Fulkerson Algorithm을 이용하면 $O(fE)$의 시간복잡도로 해결이 가능하다.

이때 모든 간선의 용량이 1이기 때문에 $f < V$이고, $O(VE)$에 해결이 가능하다는 것을 알 수 있다.

