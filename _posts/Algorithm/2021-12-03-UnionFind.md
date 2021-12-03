---
title: "유니온 파인드 (Union - Find)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:    
  - Algorithm
use_math: true
comments: true

---

## 1. Union-Find Algorithm

유니온 파인드 알고리즘은 그래프 알고리즘의 일종으로, **두 노드가 같은 그래프에 속하는지 판별하는 알고리즘**이다.

노드를 합치는 **Union** 연산과 노드가 속한 트리의 루트 노드를 찾는 **Find** 연산으로 이루어진다.

노드를 트리 구조로 합치기 때문에 트리 구조로 이루어진 자료구조라고 할 수 있으며, **서로소 집합** 또는 **상호 베타적 집합(Disjoint-Set)**으로 불리기도 한다.

예를 들어 1, 2, 3, 4 노드를 하나로 묶고 싶다면 다음과 같이 배열을 이용해 연결해준다.

> `parent[2] = 1`, `parent[3] = 2`, `parent[4] = 3`

이 상황에서 어떤 두 노드가 연결되어 있는지 알고 싶다면 **두 노드가 속한 트리 구조의 루트 노드가 같은지 비교**하면 된다.

루트 노드가 같으면 연결되어 있는 것이고, 같지 않다면 연결되어 있지 않은 것을 의미한다.

그런데 위 방법처럼 연결하면 `1-2-3-4`와 같이 높이가 큰 트리 구조가 만들어지게 된다.

루트 노드를 찾는데 레벨에 비례하는 시간이 걸리기 때문에 위와 같은 트리 구조는 비효율적이다.

이를 해결하기 위해 노드를 연결하는 Union 연산을 할 때는 **연결하고자 하는 두 노드의 루트 노드들을 서로 연결**해준다.

<br/>

## 2. Union-Find Implementation

C++를 통해 유니온 파인드를 구현해보자.

이때 `parent[i]`는 노드 i의 부모 노드를 저장하는 배열을 의미한다.

위 배열의 초기 상태는 자기 자신을 가리키도록 `parent[i] = i`와 같이 설정해준다.

### 2-1. 루트 노드 찾는 함수: find

어떤 노드를 입력받아 해당 노드가 속한 트리의 루트 노드를 찾아 반환하는 함수를 구현해보자.

```cpp
int find (int x)
{
    if (parent[x] == x) return x; // 루트 노드를 발견하면 반환
    return find(parent[x]); // 루트 노드가 아니면 부모 노드를 재귀적으로 탐색
}
```

### 2-2. 노드를 합치는 함수: union

두 노드를 연결하는 함수를 구현해보자.

```cpp
void union (int x, int y)
{
    x = find(x);
    y = find(y);
    if (x == y) return;
    parent[y] = x;
}
```

두 노드를 연결하는 방법은 각 노드가 속한 트리의 루트 노드를 찾아 루트 노드를 연결해주는 것이다.

### 2-3. 두 노드가 연결되어 있는지 판별하는 함수: isUnion

```cpp
bool isUnion (int x, int y)
{
    x = find(x);
    y = find(y);
    if (x == y) return true;
    return false;
}
```

<br/>

## 3. Weighted Union

앞서 구현한 `union` 함수를 이용하면 높이가 높은 트리가 높이가 낮은 트리 밑으로 들어갈 수 있다.

이로 인해 트리의 높이가 계속 커지면, `find`와 `union`의 실행시간이 증가하게 된다.

이를 해결하기 위한 방법 중 하나는 항상 높이가 더 낮은 트리를 높이가 더 큰 트리 밑에 집어넣는 것이다.

이 방법을 **Weighted Union**이라고 부르며, 다음과 같은 배열을 사용한다.

> `rank[i]` = 노드 i를 루트로 하는 서브트리의 높이

하나의 노드로 이루어진 트리의 `rank` 값은 0이 된다.

```cpp
void union (int x, int y)
{
    x = find(x);
    y = find(y);
    if (rank[x] > rank[y]) parent[y] = x;
    else parent[x] = y;
    if (rank[x] == rank[y]) rank[y]++;
}
```

만약 두 트리의 높이가 동일한 경우에는 합쳤을 때 트리의 높이가 1 증가하기 때문에 이를 구현해주어야 한다.

이렇게 구현하면, 높이 1인 트리를 만드는데는 최소 2개의 노드가, 높이 2인 트리를 만드는데는 최소 4개의 노드가 필요함을 알 수 있다.

높이가 H인 트리를 만들기 위해서는 적어도 높이가 (H-1)인 트리가 두 개 필요하므로 귀납법에 의해 **높이가 H인 트리는 적어도** $2^H$**개의 노드를 포함하고 있음**을 알 수 있다.

트리에 있는 노드의 개수를 N이라 할 때, $2^H \leq N$ 이므로 $H \leq \log N$ 이 성립한다.

이때 `find`와 `union` 함수의 시간복잡도는 트리의 높이에 비례하므로 $O(\log N)$가 된다.

<br/>

## 4. Path Compression

Weight Union이 노드를 연결하는 과정에서 최적화를 한다면, 탐색 과정에서 최적화를 하는 방법도 있다.

2-1의 `find` 함수에서 `parent[x]`의 값을 루트 노드로 바꾸어줌으로써 효율을 개선할 수 있다.

```cpp
int find (int x)
{
    if (parent[x] == x) return x; // 루트 노드를 발견하면 반환
    return parent[x] = find(parent[x]); // 루트 노드를 찾아 부모 노드를 루트 노드로 만들어준다.
}
```

<br/>

## 5. Weighted Union with Path Compression

앞서 소개한 두 가지 최적화 방법을 모두 적용한 경우, $n$개의 노드에 대해 Union-Find를 $m$번 수행했을 때 worst-case 시간 복잡도는 $O(m \log^* n)$이다.

이때 $\log^* n$은 $n$에 $\log$를 $k$번 적용할 때 1 이하가 된다는 의미이다.

이는 **inverse Ackermann function**이라고 불리는 함수에 의해 bounded되어 있는데, 우리가 일반적으로 다루는 모든 수에 대해 5보다 작다고 한다. (사실상 상수 시간)

다음은 각 알고리즘에 대한 `union`, `find` 함수의 시간복잡도를 표로 나타낸 것이다.

| algorithm | union | find |
|:---:|:---:|:---:|
| union | $O(H)$ | $O(H)$ |
| weighted union | $O(\log N)$ | $O(\log N)$ |
| weighted union with path compression | $O(1)$ | $O(1)$ |

<br/>

## Reference

[1] [Robert Sedgewick, Kevin Wayne, Algorithms,  4th Edition, "Case Study: Union-Find"](https://algs4.cs.princeton.edu/15uf/)




