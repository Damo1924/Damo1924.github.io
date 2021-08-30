---
title: "Red-Black Tree"
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

> **이진 탐색 트리 Binary search tree(BST)**  
> 모든 노드에 대해 다음 조건을 만족하는 이진 트리를 이진 탐색 트리라고 한다.
> - 왼쪽 서브 트리에 있는 모든 노드의 key 값은 자신의 key 값보다 작아야 한다.
> - 오른쪽 서브 트리에 있는 모든 노드의 key 값은 자신의 key 값보다 커야 한다.

## 1-1. Properties of red-black trees
Red-black tree는 각각의 노드가 Red 또는 Black인 색깔 속성을 가지고 있는 이진 탐색 트리로, 이진 탐색 트리의 조건에 더해 다음 조건들을 만족해야 한다.
- **[조건1]** 노드는 Red 또는 Black 중 하나이다.
- **[조건2]** 루트(root) 노드는 Black이다.
- **[조건3]** 모든 리프 노드들(NIL leaves / null leaves)은 Black이다. (Null leaf: 트리의 끝을 나타내는 데만 쓰이는 노드)
- **[조건4]** Red 노드의 자식 노드는 항상 Black이다. 즉, Red 노드는 연속해서 나타날 수 없다.
- **[조건5]** 어떤 노드에서 해당 노드의 하위 리프(leaf) 노드에 도달하는 모든 경로에는 모두 같은 개수의 Black 노드가 있다.

위 조건들로 인해 red-black tree는 **루트 노드부터 가장 먼 리프 노드까지의 거리가 가장 가까운 리프 노드까지의 경로의 두 배보다 항상 작다.** 그 이유는 바로  최단 경로는 모두 Black 노드로만 구성되어 있고, 최장 경로는 Black 노드와 Red 노드가 번갈아 나오기 때문이다. 루트 노드와 리프 노드가 모두 Black 노드이므로 자연스럽게 최장 경로의 길이는 최단 경로의 두 배보다 커질 수 없게 되는 것이다.

이와 같은 red-black tree의 특징을 **roughly balanced**라고 부르는데, 트리에 노드를 삽입, 삭제, 검색할 때 worst-case의 시간복잡도는 트리의 높이에 의해 결정되기 때문에 **일반적인 이진 탐색 트리에 비해 더 효율적으로 삽입과 삭제, 검색이 가능**하다는 것을 알 수 있다.

## 1-2. Height of red-black trees
1-1에서 살펴본 red-black tree의 속성들로부터 트리의 높이에 대한 다음 명제를 증명해보도록 하겠다.

**[명제]** Red-black tree의 높이를 $h$라고 할 때, $h = O(\log_{2} n)$이다.

Red-black tree의 임의의 노드 $v$에 대해 다음과 같이 정의한다.
- $h(v) = v$의 높이  
- $bh(v) = v$부터 가장 먼 leaf node까지의 경로에 있는 black node의 개수($v$ 제외)

먼저, 다음 두 가지 보조 정리를 증명해야한다.

**[Lemma 1]** $(v$의 서브트리에 있는 노드의 개수$) \geq 2^{bh(v)}-1$
> <img width = "70%" src = "https://user-images.githubusercontent.com/88201512/130709506-62721284-0bb3-444e-a807-109134d0b1a8.jpg">

**[Lemma 2]** $bh(r) >= \frac{h}{2}$
> Red-black tree의 조건 4로부터 red node가 연속해서 나올 수 없기 때문에 경로 상의 black node의 개수는 항상 높이의 절반보다 크거나 같다.

Root node를 $r$이라고 할 때, **Lemma 1, 2**로부터 다음을 얻을 수 있다.
> $(r$의 서브트리에 있는 노드의 개수$) \geq 2^{bh(r)} - 1 \geq 2^{\frac{h}{2}} - 1$

Red-black tree에 있는 노드의 총 개수를 $n$이라고 할 때, $n$에 대해 정리하면 다음과 같다.
> $n \geq 2^{\frac{h}{2}}$
> 
> $\log_{2} n \geq \frac{h}{2}$
> 
> $\therefore h \leq 2\log_{2} n$

Big O notation에서는 계수를 무시할 수 있으므로, $h = O(\log_{2} n)$을 얻을 수 있다. $\square$

## 1-3. Time complexity of red-black tree operations

|Operations|Average-case|Worst-case|
|:---:|:---:|:---:|
|Search|$O(\log n)$|$O(\log n)$|
|Insert|$O(\log n)$|$O(\log n)$|
|Delete|$O(\log n)$|$O(\log n)$|

노드를 삽입, 삭제, 검색하는 작업의 시간복잡도가 모두 $O(\log n)$임을 알 수 있다. 특히 red-black tree는 각 작업에 대해 최악의 경우에도 일정한 실행 시간을 보장한다는 장점이 있다.


<br/>
# 2. Insertion & Deletion in Red-Black Tree
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
- `P`: A의 부모 노드 (A.Parent)
- `S`: A의 형제 노드 (A.Sibling)
- `G`: P의 부모 노드 (A.Grandparent)
- `U`: P의 형제 노드 (A.Uncle)

왜 Tree rotation이 그림과 같이 이루어지는지 알기 위해서는 그 제한조건에 대해 이해해야한다. Tree rotation은 다음 제한조건들을 지키면서 트리의 구조를 바꾸어야한다.

- **중위순회(in-order traversal)를 통해 방문한 노드의 순서가 동일해야한다.**  
  중위순회는 left subtree, root, right subtree 순으로 트리를 순회하는 방법이다.
- **이진 탐색 트리(binary search tree)의 조건을 만족해야한다.**  
  한 노드의 key 값을 k라고 할 때, left subtree에 있는 노드들은 모두 k보다 작고, right subtree에 있는 노드들은 모두 k보다 크다.

그림 1에서 트리 회전 전의 트리를 보자. 위의 두 가지 제한조건에 의해 right tree rotation 이후의 트리는 다음을 만족해야한다.

1) 중위순회를 했을 때 `A-P-S-G-U`의 순서로 노드를 순회해야한다.  
2) S의 키 값이 P보다는 크고 G보다는 작아야한다. 즉, S는 P의 right subtree에 위치함과 동시에 G의 left subtree에 위치해야한다.  

실제로 그림 1에서 tree rotation 이후의 트리 구조는 이를 잘 만족한다는 것을 확인할 수 있다.

## 2-2. Insertion
Red-black tree에 노드를 삽입할 때는 삽입하는 노드(A)의 초기 상태는 Red이다. 트리의 rebalancing은 아래 4가지 케이스로 나누어서 생각해볼 수 있다.
1. `A = root`
2. `A.Uncle = Red`
3. `A.Uncle = Black` (triangle)
4. `A.Uncle = Black` (line)

이제 각 케이스에 대해 rebalancing이 어떻게 이루어지는지 알아보자.

**1) A가 루트인 경우**
- **A를 black node로 recoloring**

**2) A.Uncle이 Red인 경우**
- **P와 U를 black, G를 red로 recoloring**

<img width = "70%" src = "https://user-images.githubusercontent.com/88201512/130733249-e6376f09-e728-40a7-bbed-92adf725a31f.jpg">

(위 그림에서 G는 전체 트리의 루트가 아닌, 서브 트리의 노드이므로 red node가 될 수 있다.)

**3) A.Uncle이 Black인 경우 (triangle)**
- **P에 대한 left rotation**
- **G에 대한 right rotation**
- **A를 black, G를 red로 recoloring**

<img width = "70%" src = "https://user-images.githubusercontent.com/88201512/130733254-8e59022b-346d-491f-81d4-702436bb018b.jpg">

**4) A.Uncle이 Black인 경우 (line)**
- **G에 대한 right rotation**
- **P를 black, G를 red로 recoloring**

<img width = "70%" src = "https://user-images.githubusercontent.com/88201512/130733255-7263188c-3b56-4125-916d-53c023830825.jpg">

Rebalancing이 제대로 이루어졌는지 알아보기 위해서는 red-black tree의 조건4와 조건5를 체크해보면 된다.

한 눈에 보아도 red node가 연속으로 등장하는 경우는 없으므로 조건4는 모두 만족한다.

Root부터 leaf까지의 경로에서 등장하는 black node의 숫자가 모두 동일하다는 것을 확인하기 위해서는 서브 트리의 루트부터 시작해서 각 노드까지 등장한 black node의 개수가 같아야한다. 예를 들어 2번 케이스는 서브 트리의 루트인 G부터 A, S, U 까지의 경로에서 등장하는 black node의 개수가 전부 1개씩 증가하게 된다. 개수가 달라지긴 했지만, 결국 모든 경로에 대해 1개씩 동일하게 증가한 것이므로 조건5를 만족하게 된다. 이처럼 3, 4번 케이스에 대해서도 확인해보면 모두 조건5를 만족한다는 것을 알 수 있다.

## 2-3. Deletion
Red-black tree에서 노드를 삭제하는 것은 삽입하는 과정보다도 까다롭다.

노드를 삭제하는 과정을 크게 두 부분으로 나눌 수 있다.
1. **삭제할 노드의 자리에 들어갈 *replacement* 찾기**
2. **트리를 red-black tree의 조건을 만족하도록 rebalancing**

먼저, replacement를 찾는 방법은 다음과 같다.
- 삭제한 노드의 자식 노드들이 모두 NIL인 경우: **replacement = NIL**
- 삭제한 노드의 자식 노드들 중 하나만 NIL인 경우: **replacement = non-NIL child**
- 삭제한 노드의 자식 노드들 모두 NIL이 아닌 경우: **replacement = leftmost non-NIL node in the right subtree**(삭제한 노드의 오른쪽 서브 트리에 있는 노드 중 NIL을 제외하고 가장 왼쪽에 있는 노드)

이렇게 삭제한 노드 자리에 들어갈 replacement를 선택했다면, 트리를 다시 red-black tree가 되도록 reblancing해 주어야 한다. 각 케이스에 대해 어떻게 트리를 수정해야하는지 표로 정리하였다.

|Case|Deleted node|Replacement|Rebalancing|
|:---:|:---:|:---:|:---:|
|1|Red|Red or NIL|**Done**|
|2|Red|Black|Color the replacement Red, and proceed to the appropriate case|
|3|Black|Red|Color the replacement Black|
|4|Black|Black or NIL|Proceed to the appropriate case|


노드를 삭제하는 과정도 삽입과 마찬가지로 **recoloring**과 **tree rotation**을 통해 이루어진다. 삽입 과정에서는 **Uncle node(U)**의 색깔에 따라서 경우를 나누었다면, 삭제는 **Sibling node(S)**의 색깔에 따라서 경우를 나눈다.

노드를 삭제하는 과정은 상당히 복잡하고 처음에는 이해하기 어렵다. 이해를 돕기 위해 **double black** 표기를 사용하는데, black node가 삭제되고 black child로 대체되는 경우에 해당 child를 double black으로 표시한다. 그렇다면 우리의 목표는 double black을 single black으로 만드는 것이라고 할 수 있다.

노드를 삭제하는 과정은 다음과 같다.
1. **standard BST delete**를 수행한다.

|삭제할 노드의 자식 노드 수|삭제 방법|
|:---:|:---:|
|0(leaf node)|해당 노드를 삭제|
|1|해당 노드를 삭제하고 자식 노드로 대체|
|2|해당 노드의 **inorder successor**(또는 inorder predecessor)를 찾아 대체|

- **Inorder successor**: 해당 노드의 오른쪽 서브트리에 있는 노드 중 가장 값이 작은 것
- **Inorder predecessor**: 해당 노드의 왼쪽 서브트리에 있는 노드 중 값이 가장 큰 것


2. 해당하는 케이스를 수행한다. 이때, 삭제할 노드를 **A**, 삭제된 노드를 대체할 노드를 **X**, 삭제할 노드의 형제 노드를 **S**라고 하자.
  2-1.**A** 또는 **X**가 **Red**: A를 삭제하고 X를 black으로 칠한다.
  이렇게 하면 삭제된 노드를 지나는 경로에 있는 black node의 개수가 일정하므로 조건5를 만족하게 된다. (A와 X는 부모-자식 관계이므로 둘 다 red node일 수는 없다.)
  
  2-2. **A**와 **X**가 모두 **Black**: A를 삭제하고 X를 double black으로 칠한다.
    1) **S**가 black, **S**의 자식 노드 중 적어도 하나가 red인 경우
    S의 red child를 **R**이라고 하자. 그러면 다음과 같이 S와 R이 어느 쪽 자식인지에 따라서 케이스를 나눌 수 있다.
    
    |S의 위치|R의 위치|Case|
    |:---:|:---:|:---:|
    |Left|Left or Both children of s are red|LL|
    |Left|Right|LR|
    |Right|Right or Both children of s are red|RR|
    |Right|Left|RL|
    
    2) **S**가 black, **S**의 모든 자식 노드가 black인 경우
    A의 부모 노드 P에 대해서 다음과 같이 나눌 수 있다.
    |P의 색깔|recoloring|
    |:---:|:---:|
    |Red|A와 P를 모두 black으로 칠한다.|
    |Black|A를 black, P를 double black으로 칠하고 new A = P 로 한 뒤 double black이 없어질 때까지 재귀적으로 반복한다.|
    
    3) **S**가 red인 경우
    S가 어느 쪽 자식인지에 따라 케이스를 나눌 수 있다.
    |S의 위치|rotation & recoloring|
    |:---:|:---:|
    |Left|P에 대해 right rotation - P를 red, S를 black으로 recoloriredng - P와 A를 black으로 칠해 double black 제거|
    |Right|P에 대해 left rotation - P를 red, S를 black으로 recoloring - P와 A를 |
    
  2-3. **X**가 root: X를 black으로 칠한다.
  

<br/>
# References
[1] [WIKIPEDIA, 'Red-black tree'](https://en.m.wikipedia.org/wiki/Red%E2%80%93black_tree)  
[2] [Youtube, '자료구조 - 균형탐색이진트리 - Red-Black 트리', Chan-Su shin](https://youtu.be/SHdYv41iCmE)  
[3] [WIKIPEDIA, 'Tree rotation'](https://en.m.wikipedia.org/wiki/Tree_rotation)  
[4] [Geeksforgeeks, 'Red-Black Tree | Set 3 (Delete)'](https://www.geeksforgeeks.org/red-black-tree-set-3-delete-2/)  
