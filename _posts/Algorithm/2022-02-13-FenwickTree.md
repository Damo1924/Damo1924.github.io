---
title: "Fenwick Tree (Binary Indexed Tree, BIT)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` Segment tree, 

## 1. Fenwick Tree

> 펜윅 트리는 Binary indexed tree라는 이름으로 불리기도 하며, 줄여서 BIT라고 한다.

펜윅 트리는 **주어진 수열의 부분 수열들의 구간 합**을 빠르게 구하기 위해 고안된 자료구조이다.

부분 수열의 구간 합을 구하는 대표적인 방법은 **세그먼트 트리(segment tree)**를 이용하는 것이다.

펜윅 트리는 세그먼트 트리와 마찬가지로 구간 합을 구하는 작업과 값을 업데이트하는 작업을 모두 $O(\log n)$에 처리할 수 있다.

---

### 1-1. Structure

길이가 $n$인 수열 $a\[1\], a\[2\], \dots, a\[n\]$이 주어졌을 때,

정수 $i(1 \leq i \leq n)$에 대해 펜윅 트리의 노드 $i$에 저장된 값 $BIT\[i\]$는 다음과 같이 정의된다.

1. $i$가 홀수일 때: $i = 2x + 1$
  \begin{aligned}
  BIT\[2x + 1\] = a\[2x + 1\]
  \end{aligned}
2. $i$가 $2^k$의 배수이면서 $2^{k+1}$의 배수가 아닐 때: $i = 2^{k+1}x + 2^k$
  \begin{aligned}
  BIT\[2^{k+1}x + 2^k\] = \sum_{j = 1}^{2^k} a\[2^{k+1}x + j\]
  \end{aligned}

아래 그림은 $n = 16$일 때 펜윅 트리의 각 노드가 포함하는 범위를 표시한 것이다.

<center><img src="https://user-images.githubusercontent.com/88201512/153751102-f360bfdc-2039-4e4f-9752-30f6098948f4.jpg"></center>

---

### 1-2. Get Sum

펜윅 트리의 구조에 대해 공부했으니, 이제 구간 합을 구하는 방법과 값 업데이트를 반영하는 방법에 대해 알아보자.

먼저 구간 $\[1, b\]$의 합을 구하는 방법은 $b$를 **이진법**으로 표현하는 것이다.

예를 들어 $b = 11$에 대한 구간 합은 다음과 같이 구할 수 있다.

\begin{aligned}
\sum_{i = 1}^{11} a\[i\] = BIT\[11\] + BIT\[10\] + BIT\[8\]
\end{aligned}

> 각 숫자를 이진법으로 표현하면 $11 = 1011_2$, $10 = 1010_2$, $8 = 1000_2$이다.
> 
> $1011_2$에서 **가장 오른쪽에 있는 1**을 빼주면 $1010_2$을 얻을 수 있고,
> 
> $1010_2$에서 가장 오른쪽에 있는 1을 빼주면 $1000_2$를 얻을 수 있다.
> 
> 이진법으로 나타냈을 때, 가장 오른쪽에 있는 1을 빼주는 것은 비트 연산자를 이용해서 다음과 같이 구현할 수 있다.
> 
> ```cpp
> b &= (b - 1);
> ```

이처럼 주어진 $b$에 대해 $O(\log b)$로 구간 합을 구할 수 있다.

그렇다면 구간 $\[a, b\]$의 합은 어떻게 구할까?

바로 $\[1, b\]$에서 $\[1, a - 1\]$를 빼주는 것이다.

따라서 임의의 두 자연수 $a, b(a \leq b)$에 대해 구간 $\[a, b\]$의 합을 $O(\log n)$에 구할 수 있다.

구간 합을 구하는 함수 `_sum()`은 다음과 같이 구현할 수 있다.

```cpp
int _sum(vector<int>& tree, int x) // [1, x]의 구간 합
{
    int res = 0;
    while (x)
    {
        res += tree[x];
        x &= x - 1;
    }
    return res;
}

int _sum(vector<int>& tree, int a, int b) // [a, b]의 구간 합
{
    return _sum(tree, b) - _sum(tree, a - 1);
}
```

---

### 1-3. Update Value

어떤 정수 $i(1 \leq i \leq n)$에 대해 $a\[i\]$를 $v$로 바꾸면, $a\[i\]$를 포함하는 펜윅 트리의 노드들을 모두 업데이트해야한다.

예를 들어 $n = 16$일 때 $a\[5\]$의 값을 바꾸면, 다음 값들을 업데이트해야한다.

\begin{aligned}
BIT\[5\], BIT\[6\], BIT\[8\], BIT\[16\]
\end{aligned}

> 각 숫자를 이진법으로 표현하면, $5 = 00101_2$, $6 = 00110_2$, $8 = 01000_2$, $16 = 10000_2$이다.
> 
> 앞서 구간 합을 구할 때에는 가장 오른쪽에 있는 1을 빼주었다면, 이번에는 **가장 오른쪽에 있는 1을 더함**으로써 다음 숫자를 얻을 수 있다.
> 
> $i$의 가장 오른쪽 1에 해당하는 값은 `i & (-i)`로 얻을 수 있으므로, 다음과 같이 다음 숫자를 구할 수 있다.
> 
> ```cpp
> i += (i & (-i));
> ```

따라서 값을 업데이트하는데 $O(\log n)$의 시간복잡도가 필요하게 된다.

값을 업데이트하는 함수 `_update()`는 다음과 같이 구현할 수 있다.

```cpp
void _update(vector<ll>& tree, int n, int diff)
{
    int N = tree.size();
    while (n <= N)
    {
        tree[n] += diff;
        n += (n & (-n));
    }
}
```

> 수열 $a\[i\]$의 값을 따로 바꾸어주는 것을 빼먹지 않도록 주의!

<br/>

## 2. Fenwick Tree vs Segment Tree

펜윅 트리와 세그먼트 트리 모두 구간 합을 구하고 값을 업데이트하는 쿼리를 $O(\log n)$에 처리할 수 있는 자료구조이다.

실제로 구간 합을 구하는 대부분의 문제에서 두 방법 중 어느 것을 선택해도 큰 차이가 없다.

물론 차이점이 아예 없는 것은 아니기 때문에, 아래 차이점들을 참고해서 어떤 것을 사용할지 선택하면 된다.

1. **세그먼트 트리는 펜윅 트리보다 다양한 값들을 저장할 수 있다.**
  > 펜윅 트리는 $\[i, j\]$의 구간 합을 $\[1, j\]$에서 $\[1, i - 1\]$을 빼서 구한다. 이렇게 구간 합을 구할 수 있는 이유는 **덧셈의 역연산**이 존재하기 때문이다. **최댓값**이나 **최솟값**과 같이 역연산이 존재하지 않는 연산에 대해서는 펜윅 트리를 사용할 수 없다. 반면 세그먼트 트리는 직접 $\[i, j\]$ 구간에 접근하기 때문에 최댓값이나 최솟값도 문제 없이 구할 수 있다.
2. **펜윅 트리는 세그먼트 트리의 메모리 사용량의 절반만큼만 사용한다.**
  > 주어진 구간의 길이가 $n$이면 펜윅 트리는 길이가 $n$인 배열로도 충분하다. 반면 세그먼트 트리는 트리의 높이를 $h = \lceil \log n \rceil$이라고 할 때, 길이가 $2^{h + 1}$인 배열이 필요하다.
3. **펜윅 트리의 연산보다 세그먼트 트리의 연산이 더 큰 상수 시간 인자를 갖는다.**
  > 두 자료구조의 연산들은 모두 $O(\log n)$의 동일한 시간복잡도를 갖지만, 생략된 상수 시간을 비교하면 세그먼트 트리가 더 크다.

앞서 말했듯이 정말 대부분의 문제에서는 두 방법 중 어느 것을 택해도 무난히 통과가 가능하지만, 가끔 아래와 같이 펜윅 트리를 사용해야 널널히 통과가 가능한 문제가 등장한다.

> [백준 8217. 유성](https://www.acmicpc.net/problem/8217)
> 
> 이처럼 **다차원 트리**를 사용해야하는 문제들에서 세그먼트 트리의 상수 시간 문제가 더 부각된다.
> 
> 풀이는 [이 포스트]()에서 다루고 있다.

개인적인 생각으로는 펜윅 트리가 세그먼트 트리보다 메모리나 시간적인 측면 모두 더 나은 부분이 있긴 하지만, 세그먼트 트리의 활용도가 훨씬 뛰어나기 때문에 주로 세그먼트 트리를 사용하다가 위 문제처럼 세그먼트 트리로 통과가 어려운 문제의 경우에만 펜윅 트리를 사용하는 것이 좋은 것 같다.

<br/>

## 3. Related Problems

세그먼트 트리로 해결했던 구간 합 쿼리를 처리하는 문제들은 모두 펜윅 트리로 해결할 수 있다.

### [백준] 2042. 구간 합 구하기

[백준 2042. 구간 합 구하기 문제 링크](https://www.acmicpc.net/problem/2042)

길이가 $N(1 \leq N \leq 10^6)$인 수열이 주어질 때, 구간 합을 구하는 쿼리와 값을 업데이트하는 쿼리를 최대 20000번 처리해야한다.

> [세그먼트 트리 풀이](https://damo1924.github.io/algorithm/SegmentTree/#%EB%B0%B1%EC%A4%80-2042-%EA%B5%AC%EA%B0%84-%ED%95%A9-%EA%B5%AC%ED%95%98%EA%B8%B0)

**[SOLUTION]**

앞서 구현한 펜윅 트리의 함수들을 그대로 적용하면 된다.

```cpp
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

ll _sum(vector<ll>& tree, int x)
{
    ll res = 0;
    while (x)
    {
        res += tree[x];
        x &= x - 1;
    }
    return res;
}

ll _sum(vector<ll>& tree, int a, int b)
{
    return _sum(tree, b) - _sum(tree, a - 1);
}

void _update(vector<ll>& tree, int n, ll diff)
{
    int N = tree.size();
    while (n <= N)
    {
        tree[n] += diff;
        n += (n & (-n));
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, M, K; cin >> N >> M >> K;
    
    vector<ll> A(N + 1), tree(N + 1);
    for(int i = 1; i <= N; i++)
    {
        cin >> A[i];
        _update(tree, i, A[i]);
    }
    
    for(int i = 0; i < M + K; i++)
    {
        ll a, b, c; cin >> a >> b >> c;
        if (a == 1)
        {
            _update(tree, b, c - A[b]);
            A[b] = c;
        }
        else cout << _sum(tree, b, c) << "\n";
    }
}
```

<br/>

## References

[1] [WIKIPEDIA, 'Fenwick tree'](https://en.m.wikipedia.org/wiki/Fenwick_tree)  
[2] [stackoverflow, 'Fenwick tree vs Segment tree](https://stackoverflow.com/questions/64190332/fenwick-tree-vs-segment-tree)  
