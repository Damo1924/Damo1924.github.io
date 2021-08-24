---
title: "Red-Black Tree with C++"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

# 1. Red-Black Tree란?
Red-black tree는 **self-balancing binary search tree**라는 이진 트리의 특수한 형태이다.

> **자가 균형 이진 탐색 트리 Self-balancing binary search tree**
> : 원소의 삽입과 삭제가 일어나는 경우에 자동으로 트리의 높이를 작게 유지하는 노드 기반의 이진 탐색 트리

> **이진 탐색 트리 Binary search tree**
> : 모든 노드에 대해 다음 조건을 만족하는 이진 트리를 이진 탐색 트리라고 한다.
> - 왼쪽 서브 트리에 있는 모든 노드의 key 값은 자신의 key 값보다 작아야 한다.
> - 오른쪽 서브 트리에 있는 모든 노드의 key 값은 자신의 key 값보다 커야 한다.

Red-black tree는 각각의 노드가 Red 또는 Black인 색깔 속성을 가지고 있는 이진 탐색 트리로, 이진 탐색 트리의 조건에 더해 다음과 같은 조건들을 만족해야 한다.
- 노드는 Red 또는 Black 중 하나이다.
- 루트(root) 노드는 Black이다.
- Red 노드의 자식 노드는 항상 Black이다. 즉, Red 노드는 연속해서 나타날 수 없다.
- 어떤 노드에서 해당 노드의 하위 리프(leaf) 노드에 도달하는 모든 경로에는 모두 같은 개수의 Black 노드가 있다.

위 조건들로 인해 red-black tree는 **루트 노드부터 가장 먼 리프 노드까지의 거리가 가장 가까운 리프 노드까지의 경로의 두 배보다 항상 작다.** 그 이유는 최단 경로는 모두 Black 노드로만 구성되어 있고, 최장 경로는 Black 노드와 Red 노드가 번갈아 나오기 때문이다. 루트 노드와 리프 노드가 모두 Black 노드이므로 자연스럽게 최장 경로의 길이는 최단 경로의 두 배보다 커질 수 없게 되는 것이다.

이와 같은 red-black tree의 특징을 **roughly balanced**라고 부르는데, 트리에 노드를 삽입, 삭제, 검색할 때 worst-case의 시간복잡도는 트리의 높이에 의해 결정되기 때문에 **일반적인 이진 탐색 트리에 비해 더 효율적으로 삽입과 삭제, 검색이 가능**하다는 것을 알 수 있다.



