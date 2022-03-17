---
title: "Euler Tour Technique(ETT)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` Segemnt tree, BIT, Sparse table

## 1. Euler Tour Technique

**Euler Tour Technique(ETT)**란 양방향 간선을 가진 트리(undirected tree)를 **간선들의 수열(sequence)**로 표현하는 방법을 말한다.

방법은 아주 간단하다.

트리를 루트 노드부터 **DFS로 탐색**하면서 지나는 간선들을 리스트(배열)에 추가해주면 된다.

<center><img src="https://user-images.githubusercontent.com/88201512/158753559-ede072ef-935f-40d6-b1b4-3ec9fd4dedb8.jpg" width="60%" height="60%"></center>

예를 들어 위와 같은 트리를 ETT를 이용해서 표현하면 $(1, 5, 5, 2, 2, 1, 3, 4, 6, 6, 7, 7, 4, 3)$이 된다.

이렇게 트리를 일차원 배열로 나타냄으로써 우리는 **트리에서 주어진 구간 쿼리들을 일차원 배열에 대한 구간 쿼리**로 생각할 수 있게 된다.

따라서 ETT는 **segment tree**나 **sparse table**과 같이 구간 쿼리를 빠르게 처리할 수 있는 알고리즘들과 함께 사용하여 **트리에 대한 구간 쿼리**를 처리하는데 쓰인다.

이번 포스팅에서는 ETT를 어떻게 활용할 수 있는지에 대해 다루어 볼 것이다.

<br/>

