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

`Tags` Sum of subtree, LCA, Segemnt tree, BIT, Sparse table, 2820 자동차 공장

## 1. Euler Tour Technique

**Euler Tour Technique(ETT)**란 양방향 간선을 가진 트리(undirected tree)를 **간선들의 수열(sequence)**로 표현하는 방법을 말한다.

방법은 아주 간단하다.

트리를 루트 노드부터 **DFS로 탐색**하면서 지나는 간선들을 리스트(배열)에 추가해주면 된다.

<center><img src="https://user-images.githubusercontent.com/88201512/158753559-ede072ef-935f-40d6-b1b4-3ec9fd4dedb8.jpg" width="50%" height="50%"></center>

예를 들어 위와 같은 트리를 ETT를 이용해서 표현하면 $(1, 5, 5, 2, 2, 1, 3, 4, 6, 6, 7, 7, 4, 3)$이 된다.

이렇게 트리를 일차원 배열로 나타냄으로써 우리는 **트리에서 주어진 구간 쿼리들을 일차원 배열에 대한 구간 쿼리**로 생각할 수 있게 된다.

그래서 ETT는 **segment tree**나 **sparse table**과 같이 구간 쿼리를 빠르게 처리할 수 있는 자료구조들과 함께 사용된다.

이번 포스팅에서는 ETT를 어떻게 활용할 수 있는지에 대해 다루어 볼 것이다.

<br/>

## 2. Queries of Subtrees

서브트리의 합을 구하거나 서브트리에 있는 노드들을 업데이트하는 쿼리를 처리하는데 사용할 수 있다.

트리를 간선들의 리스트로 표현하는 대신, 다음 규칙에 따라 **노드들의 리스트**로 표현하자.

> **각 노드를 방문할 때와 떠날 때 리스트에 추가**

트리의 노드의 개수를 $n$, 리스트를 $L$이라고 하면, 각 노드는 리스트에 두 번씩 추가되므로 $L$의 길이는 $2n$이다.

트리의 노드들이 $1$번부터 $n$번까지 번호가 매겨져 있다고 할 때, 다음과 같은 배열을 정의하자.

- `s[i]` : $i$번 노드가 리스트에 처음 등장하는 위치
- `e[i]` : $i$번 노드가 리스트에 마지막으로 등장하는 위치

그렇다면 다음과 같이 말할 수 있다.

> $L\[s\[i\]\]$부터 $L\[e\[i\]\]$까지는 $i$번 노드를 루트로 하는 서브트리이다.

따라서 서브트리에 있는 노드들의 합은 $L$에 대한 세그먼트 트리의 구간 합으로 구할 수 있다.

또, 서브트리에 있는 노드들의 업데이트는 $L$의 구간 업데이트이므로 lazy propagation을 이용해서 처리할 수 있다.

---

### Implementation

사실 문제를 풀 때는 앞서 말한 것처럼 리스트에 두 번씩 노드를 삽입할 필요는 없다.

우리가 필요한 정보는 노드 $i$의 서브트리에 있는 노드들의 번호이기 때문이다.

리스트에 노드를 방문할 때만 삽입한다고 했을 때, 노드 $i$에 대해 `s[i]`와 `e[i]`를 다음과 같이 정의해도 된다.

- `s[i]` : 리스트에서 $i$가 나타나는 위치
- `e[i]` : 노드 $i$의 서브트리에 있는 노드들 중 리스트에 마지막으로 나타나는 노드의 위치

이제 다음과 같은 DFS 함수를 이용해서 우리가 필요한 정보를 얻을 수 있다.

```cpp
int idx = 1;
void dfs(int i)
{
    s[i] = idx;
    for (int j : g[i]) // g[i]: 노드 i의 자식 노드들의 번호 저장
    {
        idx++;
        dfs(j);
    }
    e[i] = idx;
}
```

---

### [BOJ] 2820. 자동차 공장

[BOJ 2820. 자동차 공장 문제 링크](https://www.acmicpc.net/problem/2820)

자동차 공장에 $N$명의 직원이 있고, 각 직원은 $1$번부터 $N$번까지 번호가 있다.

가장 직위가 높은 사장의 번호는 $1$번이고, 사장을 제외한 모든 직원은 한 명의 상사가 있다.

모든 직원은 자신의 모든 부하 직원의 월급을 인상하거나 삭감할 수 있다.

다음과 같은 쿼리들이 $M$개 주어진다.

- $p$ $a$ $x$ : $a$의 모든 부하 직원의 월급을 $x$만큼 증가시킨다.
- $u$ $a$ : $a$의 월급을 출력한다.

**[SOLUTION]**

ETT와 세그먼트 트리를 이용해서 트리 위에서의 구간 쿼리 또는 구간 업데이트를 수행하는 가장 간단한 형태의 문제이다.

공장의 직원 체계는 하나의 트리이므로, ETT를 통해 리스트로 변환할 수 있다.

만들어진 리스트에 대한 세그먼트 트리를 구현하면 되는데,

- 첫 번째 쿼리는 리스트의 구간 업데이트
- 두 번째 쿼리는 한 원소의 값을 출력

이므로 굳이 lazy propagation을 사용하지 않고도 해결할 수 있다.

> [BOJ 16975. 수열과 쿼리 21](https://www.acmicpc.net/problem/16975)을 참고

직원 $i$의 부하 직원들은 구간 $\[s\[i\] + 1, e\[i\]\]$ 에 나타난다.

<br/>

## 3. Lowest Common Ancestor(LCA)

두 번째는 LCA를 구하는데 사용하는 것이다.

마찬가지로 트리를 노드들의 리스트로 표현하는데, 이번에는 **노드를 방문할 때**마다 리스트에 추가해준다.

> **부모 노드에서 방문하는 경우와 자식 노드에서 방문하는 경우가 있다.**

이렇게 하면 리프를 제외한 각 노드가 리스트에 두 번씩 추가되고, 다음과 같이 LCA를 구할 수 있다.

> 트리의 어떤 두 노드 $u, v$의 LCA는 리스트에서 $u, v$ 사이에 존재하는 노드 중 가장 레벨이 작은 노드이다.

더 자세한 내용은 LCA에 관한 [이 포스팅](https://damo1924.github.io/algorithm/LCA/)에서 다루고 있다.

<br/>

## References

[1] [Codeforces, ifsmirnov's blog, 'On Euler tour trees'](https://codeforces.com/blog/entry/18369)  
[2] [WIKIPEDIA, 'Euler tour technique'](https://en.m.wikipedia.org/wiki/Euler_tour_technique)  
