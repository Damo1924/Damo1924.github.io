---
title: "Persistent Segment Tree (+ Dynamic Segment Tree)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` 11012 Egg

## 1. When do we use a Persistent Segment Tree?

Persistent segment tree는 **여러 개의 세그먼트 트리를 효율적으로 관리하는 자료구조**이다.

어떤 상황에서 persistent segment tree를 사용할 수 있는지 간단한 예시를 통해 알아보자.

---

다음과 같은 문제는 세그먼트 트리를 이용해서 쉽게 풀 수 있다.

> 길이가 $N$인 선분 위에 $M$개의 점이 있다.
> 
> 이때 특정 구간에 포함되어 있는 점의 개수를 구하는 쿼리를 $Q$개 처리해야한다.

만약 $N$이 작다면 **구간 합 구하기** 문제처럼 DP로 $O(N + Q)$로 해결할 수도 있다.

이번에는 위 문제를 2차원 좌표평면으로 확장시켜보자.

> 좌표평면 상의 크기가 $N \times N$인 영역에 $M$개의 점이 있다.
> 
> 이때 특정 영역에 포함되어 있는 점의 개수를 구하는 쿼리를 $Q$개 처리해야한다.

이 문제도 마찬가지로 $N$이 작다면 **2차원 영역의 합 구하기** 문제처럼 DP로 $O(N^2 + NQ)$로 해결할 수 있다.

<center><img src="https://user-images.githubusercontent.com/88201512/156280197-01accddf-726b-475f-86da-d73d058fef1f.jpg" width="60%" height="60%"></center>

하지만 $N$이 $10^6$ 정도로 커지면 DP로 시간 내에 해결할 수 없게 된다.

이때 가장 먼저 떠오르는 방법은 바로 세그먼트 트리를 $x$좌표마다 구현하는 것이다.

이러면 각 쿼리를 $O(\log N)$에 처리할 수 있게 되지만, 문제는 공간복잡도가 $O(N^2)$이 되어 메모리초과가 발생할 확률이 매우 높다.

> 세그먼트 트리를 구현하는데 필요한 배열의 크기는,
> 
> 트리의 높이 $h = \lceil \log N \rceil$에 대해 $2^{h + 1} < 4N$이다.
> 
> 따라서 각 $x$좌표마다 세그먼트 트리를 구현하는데 필요한 배열의 크기는 $O(N^2)$이다.

바로 이런 상황에서 persistent segment tree를 사용할 수 있다.

---

그렇다면 persistent segment tree는 어떻게 적은 메모리를 이용해서 여러 개의 세그먼트 트리를 관리할 수 있는지 알아보도록 하자.

이에 대해 이해하기 위해서는 먼저 **Dynamic Segment Tree**를 알아야한다.

<br/>

## 2. Dynamic Segment Tree & Implementation

일반적인 시간제한을 가진 문제에서 세그먼트 트리가 나타낼 수 있는 구간의 길이는 $10^5$ 정도이다.

그렇기 때문에 주어지는 좌표값들의 범위를 $0$부터 $10^5$으로 제한하는 문제들이 많다.

만약 이러한 제한이 없다면, **좌표 압축(coordinate compression)**을 사용해서 세그먼트 트리를 구성해야한다.

그런데 **좌표 압축 기법은 모든 쿼리를 입력받은 후에 처리가 가능할 때**에만 사용이 가능하다.

즉, **오프라인 쿼리**인 경우에만 좌표 압축을 통해 해결이 가능한 것이다.

> 그렇다면 좌표값이 $10^9$까지 주어질 수 있으면서 각 쿼리를 실시간으로 처리해야하는 **온라인 쿼리**가 주어지는 문제는 어떻게 해결할 수 있을까?

온라인 쿼리를 처리하기 위해서는 세그먼트 트리를 미리 구축해두는 것이 아니라 **필요한 만큼만 새로운 노드를 생성**해야한다.

따라서 dynamic segment tree는 일반적인 세그먼트 트리와는 달리 **왼쪽 자식과 오른쪽 자식의 인덱스를 저장**하고 있어야한다.

아래와 같이 트리의 노드를 정의하고, 벡터를 이용해서 세그먼트 트리를 구현하였다.

```cpp
struct node {
    int l, r, val;
}

node make_node(int l, int r, int val)
{
    node N;
    N.l = l; N.r = r; N.val = val;
    return N;
}

vector<node> tree(2); // tree[1]: root node
```

세그먼트 트리의 업데이트는 다음과 같이 구현할 수 있다.

```cpp
void _update(int n, int s, int e, int i, int diff)
{
    if (i < s || e < i) return;
    
    tree[n] += diff;
    if (s != e)
    {
        int m = (s + e) / 2;
        if (i <= m)
        {
            if (tree[n].l == 0) // 왼쪽 자식 노드가 없는 경우
            {
                tree.push_back(make_node(0, 0, 0)); // 새로운 노드를 추가하고,
                tree[n].l = tree.size() - 1; // 인덱스를 저장
            }
            _update(tree[n].l, s, m, i, diff);
        }
        else
        {
            if (tree[n].r == 0) // 오른쪽 자식 노드가 없는 경우
            {
                tree.push_back(make_node(0, 0, 0));
                tree[n].r = tree.size() - 1;
            }
            _update(tree[n].r, m + 1, s, i, diff);
        }
    }
}
```

만약 $i$가 속하는 구간을 대표하는 노드가 없으면, 새로운 노드를 만들어서 연결시켜주는 것이다.

마찬가지로 $\[l, r\]$ 구간의 합을 구하는 함수는 다음과 같이 구현할 수 있다.

```cpp
int _sum(int n, int s, int e, int l, int r)
{
    if (r < s || e < l) return 0;
    if (l <= s && e <= r) return tree[n].val;
    
    int m = (s + e) / 2, res = 0;
    if (l <= m)
    {
        if (tree[n].l == 0)
        {
            tree.push_back(make_node(0, 0, 0));
            tree[n].l = tree.size() - 1;
        }
        res += _sum(tree[n].l, s, m, l, r);
    }
    if (m < r)
    {
        if (tree[n].r == 0)
        {
            tree.push_back(make_node(0, 0, 0));
            tree[n].r = tree.size() - 1;
        }
        res += _sum(tree[n].r, m + 1, e, l, r);
    }
    return res;
}
```

<br/>

## 3. Persistent Segment Tree & Implementation

이제 dynamic segment tree를 구현했던 방식을 이용해서 persistent segment tree를 구현해보자.

각 $x$좌표마다 세그먼트 트리를 만드는 대신,

- 가장 작은 $x$에 대해 세그먼트 트리를 하나 만들고, ($O(N)$)
- 새로운 점이 추가될 때마다 업데이트되는 노드만 새로 생성한다. ($O(\log N)$)

와 같은 방법을 통해 하나의 세그먼트 트리로 문제를 해결할 수 있다.

전체 점의 개수를 $M$개라고 하면 공간복잡도는 $O(N + M \log N)$이다.

먼저, 일반적인 세그먼트 트리를 하나 만들어준다.

```cpp
struct node {
    int l, r, val;
}

node make_node(int l, int r, int val)
{
    node N;
    N.l = l; N.r = r; N.val = val;
    return N;
}

vector<node> tree(2); // tree[1]: root node

void buildSegtree(int n, int s, int e)
{
    if (s == e) return;
    int m = (s + e) / 2;
    
    tree.push_back(make_node(0, 0, 0));
    tree[n].l = tree.size() - 1;
    buildSegtree(tree[n].l, s, m);
    
    tree.push_back(make_node(0, 0, 0));
    tree[n].r = tree.size() - 1;
    buildSegtree(tree[n].r, m + 1, e);
}
```

Persistent segment tree의 업데이트 함수는 **기존에 업데이트될 노드들을 복사해서 새로 만들고, 새로 만든 노드들을 업데이트**한다.

```cpp
void _update(int n, int s, int e, int i, int diff)
{
    if (i < s || e < i) return;
    
    tree[n].val += diff; // 현재 노드에 업데이트 진행
    if (s != e)
    {
        int m = (s + e) / 2;
        if (i <= m)
        {
            tree.push_back(tree[tree[n].l]); // 기존 노드를 복사해서 새로운 노드를 생성하고,
            tree[n].l = tree.size() - 1; // 현재 노드와 새로운 노드를 연결한다.
            _update(tree[n].l, s, m, i, diff); // 새로운 노드에서 업데이트 진행
        }
        else
        {
            tree.push_back(tree[tree[n].r]);
            tree[n].r = tree.size() - 1;
            _update(tree[n].r, m + 1, e, i, diff);
        }
    }
}
```

세그먼트 트리에서 구간의 합을 구하는 함수는 앞서 구현한 그대로이다.

```cpp
int _sum(int n, int s, int e, int l, int r)
{
    if (r < s || e < l) return 0;

    if (l <= s && e <= r) return tree[n].val;
    
    int m = (s + e) / 2, res = 0;
    if (l <= m) res += _sum(tree[n].l, s, m, l, r);
    if (m < r) res += _sum(tree[n].r, m + 1, e, l, r);
    return res;
}
```

Persistent segment tree의 각 루트 노드의 인덱스를 기억해야하므로 다음과 같은 배열을 사용한다.

> `root_idx[i]` : $x$좌표가 $i$인 점들까지 업데이트한 세그먼트 트리의 루트 노드

일반적으로 $x$좌표의 범위는 $0$부터 $10^5$으로 주어지기 때문에 `root_idx[0] = 1`이다.

이때 새로운 루트 노드는 **전 단계의 루트 노드를 복사**해서 생성한다.

```cpp
if (root_idx[i] == 0)
{
    tree.push_back(tree[root_idx[i - 1]]);
    root_idx[i] = tree.size() - 1;
}
```

여기서 새로운 점 $(i, j)$를 추가한다고 하면, 아래와 같이 업데이트할 수 있다.

```cpp
_update(root_idx[i], 0, 100000, y, 1);
```

마지막으로 $a \leq x \leq b$, $c \leq y \leq d$인 직사각형 영역에 있는 점들의 개수를 구하고 싶다면, 아래와 같이 구할 수 있다.

```cpp
int ans = _sum(root_idx[b], 0, 100000, c, d);
if (a != 0) ans -= _sum(root_idx[a - 1], 0, 100000, c, d);
```

<center><img src="https://user-images.githubusercontent.com/88201512/156280317-3b965f18-09ca-42e0-b8ad-5ca982d1dd15.jpg" width="60%" height="60%"></center>

경계값인 $a = 0$만 예외처리를 해주었다.

<br/>

## 4. Related Problems

[백준 11012. Egg 문제 링크](https://www.acmicpc.net/problem/11012)

> [백준 11012. Egg 풀이](https://damo1924.github.io/ps/BAEKJOON-11012/)

