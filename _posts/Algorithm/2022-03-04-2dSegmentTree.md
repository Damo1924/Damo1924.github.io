---
title: "2D Segment Tree"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` Dynamic segment tree

## 1. 2D Segment Tree

2D segment tree는 **크기가 $N \times M$인 이차원 배열에서 값의 업데이트와 구간 쿼리를 $O(\log N \cdot \log M)$에 처리할 수 있는 자료구조**이다.

간단히 설명하면 **각 노드가 세그먼트 트리인 세그먼트 트리**라고 할 수 있다.

`vector<vector<int>> tree`와 같은 이차원 벡터를 통해 2D segment tree를 구현해보자.

바깥쪽 세그먼트 트리는 행(row)을, 바깥쪽 세그먼트 트리의 각 노드인 안쪽 세그먼트 트리는 열(col)을 의미한다.

> 메모리를 최대한 적게 사용하기 위해 [Bottom-Up 방식](https://damo1924.github.io/algorithm/BottomUpSegmentTree/)으로 세그먼트 트리를 구현할 것이다.
> 
> 길이가 $N$인 수열에 대한 세그먼트 트리를 구현하는데 길이가 $2N$인 배열이 필요하므로,
> 
> 크기가 $N \times M$인 이차원 수열에 대한 2D 세그먼트 트리를 구현하는데는 크기가 $2N \times 2M$인 이차원 배열이 필요하다.

---

### 1-1. Build Tree

2차원 배열의 $i$행 $j$열 값을 $a_{i, j}$($0 \leq i, j < n$)이라고 하자.

Bottom-Up 방식으로 구현한 세그먼트 트리에서 $a_k$($0 \leq k < m$)은 $n + k$번 노드에 대응된다.

이 사실을 이용하면 다음과 같은 순서대로 2D 세그먼트 트리를 구현할 수 있다.

1. 바깥쪽 세그먼트 트리의 리프 노드들(안쪽 세그먼트 트리)의 리프 노드들에 $a_{i, j}$를 저장한다.
2. 바깥쪽 세그먼트 트리의 리프 노드들의 나머지 노드들을 구한다.
3. 바깥쪽 세그먼트 트리의 나머지 노드들을 구한다.

```cpp
void buildSegtree(vector<vector<int>>& tree, vector<vector<int>>& a, int n)
{
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            tree[i + n][j + n] = a[i][j];
    
    for (int i = n; i < 2 * n; i++)
        for (int j = n - 1; j > 0; j--)
            tree[i][j] = tree[i][2 * j] + tree[i][2 * j + 1];
    
    for (int i = n - 1; i > 0; i--)
        for (int j = 1; j < 2 * n; j++)
            tree[i][j] = tree[2 * i][j] + tree[2 * i + 1][j];
}
```

---

### 1-2. Update

$a_{x, y}$를 $v$로 바꾸었을 때, 트리를 업데이트하는 함수를 구현해보자.

먼저 $x$행을 대표하는 노드(= 바깥쪽 트리의 리프 노드)를 업데이트해준다.

그 다음 바깥쪽 트리의 부모 노드를 차례대로 업데이트해준다.

```cpp
void _update(vector<vector<int>>& tree, int n, int x, int y, int diff)
{
    for (int j = y + n; j; j /= 2) tree[x + n][j] += diff; // 바깥쪽 트리의 리프 노드 업데이트
    for (int i = (x + n) / 2; i; i /= 2) // 바깥쪽 트리의 나머지 노드 업데이트
        for (int j = y + n; j; j /= 2)
            tree[i][j] = tree[2 * i][j] + tree[2 * i + 1][j];
}
```

---

### 1-3. Get Sum

2D 세그먼트 트리에서 주어진 영역 $\[x_1, x_2\] \times \[y_1, y_2\]$의 합을 구하는 방법은 다음과 같다.

- 바깥쪽 세그먼트 트리에서 $\[x_1, x_2\]$에 해당하는 노드들 찾는다.
- 위에서 찾은 노드들에서 $\[y_1, y_2\]$에 해당하는 노드들에 저장된 값을 모두 더해준다.

먼저 바깥쪽 트리의 $x$번 노드에서 구간 $\[y_1, y_2\]$의 합을 구하는 함수부터 구현하였다.

```cpp
int _sum(vector<vector<int>>& tree, int n, int x, int y1, int y2)
{
    y1 += n; y2 += n;
    int res = 0;
    while (y1 <= y2)
    {
        if (y1 % 2 != 0) res += tree[x][y1++];
        if (y2 % 2 == 0) res += tree[x][y2--];
        y1 /= 2; y2 /= 2;
    }
    return res;
}
```

위 함수를 이용하면 주어진 영역의 합을 구하는 함수를 구현할 수 있다.

```cpp
int _sum(vector<vector<int>>& tree, int n, int x1, int x2, int y1, int y2)
{
    x1 += n; x2 += n;
    int res = 0;
    while (x1 <= x2)
    {
        if (x1 % 2 != 0) res += _sum(tree, n, x1++, y1, y2);
        if (x2 % 2 == 0) res += _sum(tree, n, x2--, y1, y2);
        x1 /= 2; x2 /= 2;
    }
    return res;
}
```

---

### [백준] 11658. 구간 합 구하기 3

[백준 11658. 구간 합 구하기 3 문제 링크](https://www.acmicpc.net/problem/11658)

$N \times N$($1 \leq N \leq 1024$) 크기의 표가 주어질 때, 다음과 같은 쿼리 $M$($1 \leq M \leq 10^5$)개가 주어진다.

- $0$ $x$ $y$ $c$ : $x$행 $y$열의 값을 $c$로 바꾼다.
- $1$ $x_1$ $y_1$ $x_2$ $y_2$ : $x_1$행 $y_1$열부터 $x_2$행 $y_2$열까지의 합을 출력한다.

**[SOLUTION]**

$N$이 최대 $1024$이므로 2D 세그먼트 트리를 앞선 방법으로 구현해도 메모리 초과가 발생하지 않는다.

**소스코드**

<br/>

## 2. Memory Optimization



## References

[1] [Samsung Software Membership, blisstoner, '2D Segment Tree](http://www.secmem.org/blog/2019/11/15/2D-segment-tree/)
