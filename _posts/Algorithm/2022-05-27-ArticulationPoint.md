---
title: "단절점과 단절선(Articulation Point & Bridge)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:    
  - Algorithm
use_math: true
comments: true

---

`Tags` DFS

## 1. Articulation Point

하나의 연결 요소(connected component)로 이루어진 그래프에서 제거했을 때 그래프가 두 개 또는 그 이상의 연결 요소로 나누어지는 정점을 **단절점(articulation point)**라고 부른다.

단절점은 다음과 같은 성질을 가지고 있다.

- 단절점에 인접한 정점들은 단절점을 통해서만 연결된다.

만약 단절점을 지나지 않는 우회로가 존재한다면, 단절점을 제거해도 연결 요소의 개수가 그대로임을 알 수 있다.

이를 이용해서 그래프의 단절점들을 구하기 위해 그래프에 대한 DFS tree를 그리면, 다음과 같이 단절점을 구할 수 있다.

- 어떤 정점 $v$가 단절점이 아니기 위해서는 DFS tree에서 $v$의 자손인 정점들 중 $v$를 지나지 않고 $v$ 이전에 방문한 정점에 갈 수 있어야한다.

단, DFS tree의 루트 노드는 따로 처리해준다.

- 루트 노드는 자식 노드가 $2$개 이상이면 단절점이다.

이는 루트 노드의 각 자식 노드를 루트로 하는 서브트리에 속하는 정점들은 루트 노드를 통해서만 연결될 수 있기 때문이다.

DFS를 한 번 수행하므로 시간복잡도는 $O(V + E)$ 이다.

---

### [BOJ] 11266. 단절점

[BOJ 11266. 단절점 문제 링크](https://www.acmicpc.net/problem/11266)

주어진 그래프의 단절점들을 구하는 문제이다.




