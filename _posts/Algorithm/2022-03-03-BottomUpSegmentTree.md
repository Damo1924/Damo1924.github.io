---
title: "Bottom-Up Implementation of Segment Tree"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags`

2D Segment Tree를 공부하다가 이에 대한 [포스팅](http://www.secmem.org/blog/2019/11/15/2D-segment-tree/)에서 세그먼트 트리를 Bottom-Up 방식으로 구현하는 방법을 보게 되어 따로 정리해두려고 한다.

## 1. Bottom-Up Segment Tree

세그먼트 트리는 Top-Down 방식뿐만 아니라 Bottom-Up 방식으로도 구현할 수 있다.

Top-Down 방식으로 구현하는 방법은 아래 포스팅에서 다루고 있다.

> [Top-Down Implementation of Segment Tree](https://damo1924.github.io/algorithm/SegmentTree/#2-segment-tree-implementation)

---

### 1-1. Build Segment Tree

길이가 $n$인 수열 $a_0, a_1, \dots, a_{n - 1}$의 각 원소 $a_k$($0 \leq k < n$)은 트리의 $n + k$번 노드에 대응된다.

> Bottom-Up 방식으로 구현하면 길이가 $2n$인 배열이 필요하다.

그 다음 $n - 1$번 노드부터 $1$번 노드까지 자식 노드들의 합을 구해 저장함으로써 트리를 완성한다.

이때 $i$번 노드의 두 자식 노드의 번호는 Top-Down 방식과 동일하게 $2i$, $2i + 1$로 구할 수 있다.

```cpp
void buildSegtree(vector<int>& tree, vector<int>& a)
{
    int n = a.size();
    for (int i = 0; i < n; i++) tree[n + i] = a[i];
    for (int i = n - 1; i; i--) tree[i] = tree[2 * i] + tree[2 * i + 1];
}
```

---

### 1-2. Update

$a_i$에 $x$를 더했다면, $n + i$번 노드부터 시작해서 부모 노드로 올라가면서 $x$를 더해주면 된다.

```cpp
void _update(vector<int>& tree, int i, int diff)
{
    for (int idx = tree.size() / 2 + i; idx; idx /= 2) tree[idx] += diff;
}
```

---

### 1-3. Get Sum

정수 $l, r$($l \leq r$)에 대해 $a_l$부터 $a_r$까지의 합을 구하는 함수를 구현해보자.

`l_idx`를 $n + l$, `r_idx`를 $n + r$이라고 둔 후, `l_idx <= r_idx`를 만족할 때까지 부모 노드로 올라가면서 합을 구할 것이다.

이때 다음과 같이 경우를 나누어야한다.

- `l_idx`번 노드가 왼쪽 자식인 경우
- `l_idx`번 노드가 오른쪽 자식인 경우

만약 `l_idx`번 노드가 왼쪽 자식이면 오른쪽 자식 노드도 구간 내에 포함되므로 부모 노드로 올라가면 된다.

그런데 `l_idx`번 노드가 오른쪽 자식이면 왼쪽 자식 노드는 구간 내에 포함되지 않기 때문에 부모 노드로 올라가면 안된다.

그 대신 현재 노드의 값을 더하고 `l_idx`의 값을 1 늘려준다.

마찬가지로 `r_idx`번 노드에 대해서도 왼쪽 자식인 경우와 오른쪽 자식인 경우로 나누어준다.

`r_idx`번 노드가 오른쪽 자식이면 왼쪽 자식 노드도 구간 내에 포함되므로 부모 노드로 올라간다.

반대로 왼쪽 자식이면 오른쪽 자식 노드는 구간 내에 포함되지 않으므로 현재 노드의 값을 더해주고 `r_idx`의 값을 1 감소시킨다.

```cpp
int _sum(vector<int>& tree, int l, int r)
{
    int n = tree.size() / 2;
    l += n; r += n;
    
    int res = 0;
    while (l <= r)
    {
        if (l % 2 != 0) res += tree[l++];
        if (r % 2 == 0) res += tree[r--];
        l /= 2; r /= 2;
    }
    return res;
}
```

---

### 1-4. Top-Down vs. Bottom-Up

사실 어느 것을 사용해도 큰 상관은 없다.

하지만, Top-Down으로 세그먼트 트리를 구현하기 위해서는 길이가 최소 $2n$, 최대 $4n$인 배열이 필요한 것에 비해 Bottom-Up으로 구현하면 길이가 $2n$인 배열을 사용하기 때문에 메모리 측면에서 더 낫다고 볼 수 있다.

Top-Down이나 Bottom-Up 모두 `_update()`와 `_sum()`을 재귀함수를 사용하지 않고 구현할 수 있기 때문에 시간 상으로는 큰 차이가 없다.

