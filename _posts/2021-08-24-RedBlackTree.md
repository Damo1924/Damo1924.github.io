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

# 1. Introduction to Red-Black Trees
Red-black tree는 **self-balancing binary search tree**라는 이진 트리의 특수한 형태이다.

> **자가 균형 이진 탐색 트리 Self-balancing binary search tree**  
> 원소의 삽입과 삭제가 일어나는 경우에 자동으로 트리의 높이를 작게 유지하는 노드 기반의 이진 탐색 트리

> **이진 탐색 트리 Binary search tree**  
> 모든 노드에 대해 다음 조건을 만족하는 이진 트리를 이진 탐색 트리라고 한다.
> - 왼쪽 서브 트리에 있는 모든 노드의 key 값은 자신의 key 값보다 작아야 한다.
> - 오른쪽 서브 트리에 있는 모든 노드의 key 값은 자신의 key 값보다 커야 한다.

Red-black tree는 각각의 노드가 Red 또는 Black인 색깔 속성을 가지고 있는 이진 탐색 트리로, 이진 탐색 트리의 조건에 더해 다음과 같은 조건들을 만족해야 한다.
- **[조건1]** 노드는 Red 또는 Black 중 하나이다.
- **[조건2]** 루트(root) 노드는 Black이다.
- **[조건3]** 모든 리프 노드들(NIL leaves / null leaves)은 Black이다. (Null leaf: 트리의 끝을 나타내는 데만 쓰이는 노드)
- **[조건4]** Red 노드의 자식 노드는 항상 Black이다. 즉, Red 노드는 연속해서 나타날 수 없다.
- **[조건5]** 어떤 노드에서 해당 노드의 하위 리프(leaf) 노드에 도달하는 모든 경로에는 모두 같은 개수의 Black 노드가 있다.

위 조건들로 인해 red-black tree는 **루트 노드부터 가장 먼 리프 노드까지의 거리가 가장 가까운 리프 노드까지의 경로의 두 배보다 항상 작다.** 그 이유는 바로  최단 경로는 모두 Black 노드로만 구성되어 있고, 최장 경로는 Black 노드와 Red 노드가 번갈아 나오기 때문이다. 루트 노드와 리프 노드가 모두 Black 노드이므로 자연스럽게 최장 경로의 길이는 최단 경로의 두 배보다 커질 수 없게 되는 것이다.

이와 같은 red-black tree의 특징을 **roughly balanced**라고 부르는데, 트리에 노드를 삽입, 삭제, 검색할 때 worst-case의 시간복잡도는 트리의 높이에 의해 결정되기 때문에 **일반적인 이진 탐색 트리에 비해 더 효율적으로 삽입과 삭제, 검색이 가능**하다는 것을 알 수 있다.

다음은 red-black tree operations의 시간복잡도를 나타낸 표이다.

|Operations|Average-case|Worst-case|
|:---:|:---:|:---:|
|Search|$O(\log n)$|$O(\log n)$|
|Insert|$O(\log n)$|$O(\log n)$|
|Delete|$O(\log n)$|$O(\log n)$|

노드를 삽입, 삭제, 검색하는 작업의 시간복잡도가 모두 $O(\log n)$임을 알 수 있다. 또한 각 작업에 대해 최악의 경우에도 일정한 실행 시간을 보장한다는 장점이 있다.


<br/>
# 2. Insertion & Removal in Red-Black Tree
Red-black tree는 일반적인 이진 탐색 트리와 동일한 방법으로 노드를 삽입하거나 삭제하게 되면 위에서 다룬 조건들을 만족하지 않게 된다. 노드를 삽입, 삭제하고 나서도 조건을 만족하도록 하는 과정을 **rebalancing**이라고 부르며, 다음 두 작업을 통해 이루어진다.

- **Recoloring**: 노드의 색을 변환
- **Tree rotation**: 이진 트리에서 노드의 순서를 변경하지 않고 트리의 구조만 바꾸는 작업

경우에 따라서 recoloring과 tree rotation을 이용해서 red-black tree의 조건을 만족하도록 rebalancing하는데, 꽤나 복잡한 과정임에도 불구하고 시간복잡도는 $O(\log n)$이다. 삽입과 삭제가 이루어지는 과정에 대해 알아보기 전에 tree rotation이 어떻게 이루어지는지부터 알아보도록 하겠다.

## 2-1. Tree rotation
> An operation on a binary tree that changes the structure ***without interfering with the order of the elements.*** Tree rotation is used to **decrease its height** by moving smaller subtrees down and larger subtrees up, resulting in **improved performance of many tree operations.**

Tree rotation에는 두 가지 방향이 존재하는데, 시계방향 회전을 오른쪽 회전(right rotation), 반시계방향 회전을 왼쪽 회전(left rotation)이라고 한다.

<center><img width = "70%" src = "https://user-images.githubusercontent.com/88201512/130643150-46b0fab0-5181-48da-af77-9a09eb7a9871.jpg"></center>

각 노드를 다음과 같은 notation을 이용해서 표기하였다.
- `A`: 현재 주목하고 있는 노드
- `P`: A의 부모 노드
- `S`: A의 형제 노드
- `G`: P의 부모 노드
- `U`: P의 형제 노드

왜 Tree rotation이 그림과 같이 이루어지는지 알기 위해서는 그 제한조건에 대해 이해해야한다. Tree rotation은 다음 제한조건들을 지키면서 트리의 구조를 바꾸어야한다.

- **중위순회(in-order traversal)를 통해 방문한 노드의 순서가 동일해야한다.**  
  중위순회는 left subtree, root, right subtree 순으로 트리를 순회하는 방법이다.
- **이진 탐색 트리(binary search tree)의 조건을 만족해야한다.**  
  한 노드의 key 값을 k라고 할 때, left subtree에 있는 노드들은 모두 k보다 작고, right subtree에 있는 노드들은 모두 k보다 크다.

그림 1에서 트리 회전 전의 트리를 보자. 위의 두 가지 제한조건에 의해 tree rotation 이후의 트리는 다음을 만족해야한다.  
1) 중위순회를 했을 때 `A-P-S-G-U`의 순서로 노드를 순회해야한다.  
2) S의 키 값이 P보다는 크고 G보다는 작아야한다. 즉, S는 P의 right subtree에 위치함과 동시에 G의 left subtree에 위치해야한다.  
실제로 그림 1에서 tree rotation 이후의 트리 구조는 이를 잘 만족한다는 것을 확인할 수 있다.



<br/>
# References
[1] [WIKIPEDIA, 'Red-black tree'](https://en.m.wikipedia.org/wiki/Red%E2%80%93black_tree)  
[2] [WIKIPEDIA, 'Tree rotation'](https://en.m.wikipedia.org/wiki/Tree_rotation)  
