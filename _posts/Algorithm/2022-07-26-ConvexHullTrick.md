---
title: "동적계획법에서의 볼록껍질 최적화 (Convex Hull Trick, CHT)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:    
  - Algorithm
use_math: true
comments: true

---

`Tags` DP Optimization, 4008, 13263, 6171, 10067, 12795

## 1. Idea of the Convex Hull Trick

다음과 같은 점화식이 주어졌을 때, 이를 일반적으로 구하면 $O(n^2)$의 시간복잡도를 갖게 된다.

\begin{aligned}
DP_i = \min_{j < i} \left( DP_j + A_i \cdot B_j \right)
\end{aligned}

위 점화식은 다음과 같이 바꾸어서 생각할 수 있다.

- $DP_i$는 $j < i$ 를 만족한는 $j$에 대한 직선 $y = B_j x + DP_j$ 들의 $x = A_i$ 에서의 최솟값이다.

이때 **$B_j$가 $j$에 대하여 감소**한다는 조건을 추가하면, 다음과 같은 그래프를 그릴 수 있다.

<center><img src="https://user-images.githubusercontent.com/88201512/181435048-e067597e-dda0-4af0-b6d6-2a8b5b57d8e0.jpg" width="60%" height="60%"></center>

$DP_i$를 구하기 위해 필요한 것은 지금까지 구한 $DP_j$들에 대응되는 직선들의 가장 아랫부분들을 이은 빨간색 그래프이다.

> 모양이 볼록 껍질과 비슷하기 때문에 Convex Hull이라는 이름이 붙게 되었다.

따라서 각 직선이 어느 구간에서 최솟값을 가지는지 저장해둔다면, $A_i$가 속하는 구간을 이분탐색으로 찾음으로써 빠르게 $DP_i$를 구할 수 있게 되는 것이다.

이분탐색으로 원하는 직선을 찾고, 최솟값을 구하는 과정의 시간복잡도는 $O(\log n)$ 이므로, 직선을 효율적으로 관리할 수 있다면 시간복잡도를 개선할 수 있을 것이다.

> 같은 방법으로 **최댓값**을 구하는 문제도 처리할 수 있다.
> 
> 이 경우에는 **$B_j$가 $j$에 대하여 증가**해야하며, 그래프를 그리면 아래로 볼록한 볼록 껍질을 얻게 된다.

<br/>

## 2. How to deal with a New Line

$DP_i$를 구하고 나면, 직선 $y = B_i x + DP_i$ 가 어떤 구간에서 최솟값을 갖는지 구해야한다.

$B_j$가 $j$에 대하여 감소하기 때문에 위 직선이 마지막 구간 $\[x_i, \infty)$ 을 차지하게 될 것이다.

따라서 뒤에서부터 기존에 저장된 직선들과의 교점을 구해보면서 적절한 $x_i$를 찾아보면 된다.

맨 뒤에 있는 직선 $y = B_j x + DP_j$ 이 $x$좌표가 $x_j$ 이상인 구간에서 최솟값에 해당한다고 하면, 두 직선의 교점의 $x$좌표는

\begin{aligned}
x_{ji} = \frac{DP_i - DP_j}{B_j - B_i}
\end{aligned}

만약 $x_{ji} > x_j$ 이면, 직선 $y = B_j x + DP_j$이 최솟값인 구간도 존재하므로 그대로 새로운 직선을 추가해주면 되고, 이때 $x_i = x_{ji}$ 가 된다.

반대로 $x_{ji} \leq x_j$ 이면 직선 $y = B_j x + DP_j$이 최솟값이 되는 구간이 없어진다.

이 경우 해당 직선을 제거하고, 다시 마지막 직선과 교점을 구해 $x_i$를 구하는 과정을 반복해준다.

이 과정을 수행하기 위해 직선에 대해 알아야하는 정보는 해당 직선의 기울기와 $y$절편, 그리고 최솟값에 해당하는 구간의 시작 $x$좌표인 $x_i$이다.

> 잘 생각해보면 최댓값을 구하는 경우에도 동일한 과정을 거쳐 직선을 처리할 수 있다는 것을 알 수 있다.

<br/>

## 3. Time Complexity

직선들을 벡터에 저장해둔다고 하면 각 직선을 한 번씩 벡터에 삽입하고, 최대 한 번씩 벡터에서 제거하기 때문에 $DP_n$까지 구하는데 $O(n)$의 시간복잡도를 갖는다.

앞서 말했듯이 $x = A_i$ 가 속하는 구간을 찾을 때마다 $O(\log n)$이 걸리기 때문에 전체 시간복잡도는 $O(n \log n)$ 임을 알 수 있다.

이때 **$A_i$가 $i$에 대하여 증가**한다는 조건을 추가하면 모든 직선을 저장할 필요 없이 구간이 $A_i$보다 작다면 제거해버리면 되기 때문에 시간복잡도가 $O(n)$이 된다.

<br/>

## 4. Implementation

구현하는 방법은 다양하기 때문에 자신이 사용하기 편한 코드를 사용하자.

나는 벡터를 이용하여 구현하였다.

---

### 4-1. Using binary search: $O(n \log n)$

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;
typedef long long ll;

struct Line {
    ll a, b, p; // y = ax + b, x = p 부터 최대/최소값
    bool operator<(const Line& l) const { return p < l.p; }
};
struct LineContainer : vector<Line> {
    ll div(ll a, ll b) { return a / b + ((a ^ b) > 0 && a % b); } // 올림
    void add(ll a, ll b) {
        while (!empty()) {
            Line prv = back();
            ll p = div(b - prv.b, prv.a - a);
            if (p <= prv.p) pop_back();
            else {
                push_back({ a, b, p });
                return;
            }
        }
        push_back({ a, b, 0 });
    }
    ll query(ll x) { // return max/min value at x
        Line tmp = { 0, 0, x };
        auto l = *prev(upper_bound(begin(), end(), tmp));
        return l.a * x + l.b;
    }
};
```

---

### 4-2. When query increases: $O(n)$

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
using namespace std;
typedef long long ll;

int idx = 0;
struct Line {
    ll a, b, p; // y = ax + b, x = p
    bool operator<(const Line& l) const { return p < l.p; }
};
struct LineContainer : vector<Line> {
    ll div(ll a, ll b) { return a / b + ((a ^ b) > 0 && a % b); }
    void add(ll a, ll b) {
        while (!empty()) {
            Line prv = back();
            ll p = div(b - prv.b, prv.a - a);
            if (p <= prv.p) pop_back();
            else {
                push_back({ a, b, p });
                return;
            }
        }
        push_back({ a, b, 0 });
    }
    ll query(ll x) {
        if (idx >= size()) idx = size() - 1;
        while (idx < size() && at(idx).p <= x) idx++;
        return at(idx - 1).a * x + at(idx - 1).b;
    }
};
```

<br/>

## 5. Related Problems

DP 점화식을 세웠을 때 볼록껍질 최적화를 사용 가능한지 확인하고 적용해준다.

점화식을 적절한 형태로 변경하는 작업이 필요한 경우가 많다.

---

### [BOJ] 13263. 나무 자르기

[BOJ 13263. 나무 자르기 문제 링크](https://www.acmicpc.net/problem/13263)

나무를 길이 $1$만큼 자를 때마다 전기톱을 충전하여야 하는데, 전기톱의 충전 비용은 완전히 자른 나무의 번호의 최댓값이 $i$일 때 $b_i$이다.

$i$번째 나무의 높이는 $a_i$이며, $a_i$는 $i$에 대하여 증가하고, $b_i$는 $i$에 대하여 감소한다.

초기에 전기톱은 충전된 상태로 있으며, $a_1 = 1$ 이고 $b_n = 0$ 이다.

즉, 높이가 가장 큰 $n$번째 나무를 완전히 자르고 나면 나머지 나무들을 추가 충전 비용 없이 모두 자를 수 있게 된다.

그러므로 DP 배열을 다음과 정의하고 점화식을 세울 수 있다.

- $DP\[i\]$ : $i$번째 나무를 완전히 자르는데 필요한 최소 비용
- $DP\[i\] = \min_{j < i} \left( DP\[j\] + b_j a_i \right)$

따라서 $DP\[i\]$ 는 직선 $y = b_j x + DP\[j\]$ 들이 있을 때 $x = a_i$ 에서의 최솟값이 되고,

$b_j$가 $j$에 대하여 감소하므로, 이는 CHT를 이용해서 $O(n \log n)$으로 해결할 수 있다.

또한 $a_i$가 $i$에 대하여 증가하기 때문에 $O(n)$으로도 해결할 수 있다.

---

### [BOJ] 6171. 땅따먹기

[BOJ 6171. 땅따먹기 문제 링크](https://www.acmicpc.net/problem/6171)

아래와 같이 땅의 가격이 매겨질 때, $N$개의 땅을 모두 사기 위한 최소 비용을 구하는 문제이다.

- (여러 땅의 묶음의 가격) = (해당 땅들 중 가로의 길이의 최댓값) $\times$ (해당 땅들 중 세로의 길이의 최댓값)

땅을 연속된 그룹으로만 묶을 수 있는 것이 아니라 아무렇게나 묶을 수 있기 때문에 CHT를 사용하는 문제라고 생각하기 어렵다.

어떤 땅이 다른 땅에 포함된다면(가로와 세로의 길이가 모두 작거나 같다면), 해당 땅은 고려할 필요가 없다.

이 사실을 이용하면,

1. 땅들을 가로의 길이에 대해 정렬한다.
2. 가로의 길이가 가장 긴 땅을 선택하고, 해당 땅보다 세로의 길이가 같거나 짧은 땅들과 묶는다.
3. 위에서 묶은 땅들을 제외하고 남은 땅이 없을 때까지 2번 과정을 반복한다.

와 같은 과정을 통해 최소 비용에 영향을 주는 땅들만 남길 수 있다.

2번 과정에서 선택된 땅들을 가로의 길이에 대한 내림차순으로 정렬한다면, 자연스럽게 세로의 길이에 대한 오름차순으로도 정렬된다.

이때 $i$번째 땅의 가로의 길이를 $b_i$, 세로의 길이를 $a_i$라고 하면 다음과 같이 DP 배열을 정의할 수 있다.

- $DP\[i\]$ : $i$번째 땅까지 모두 사는데 필요한 최소 비용
- $DP\[i\] = \min_{j < i} \left( DP\[j\] + a_i b_{j+1} \right)$

CHT를 이용하면 $O(n)$으로 해결할 수 있다.

---

### [BOJ] 4008. 특공대

[BOJ 4008. 특공대 문제 링크](https://www.acmicpc.net/problem/4008)

$n$명의 병사들이 있고, $i$번 병사의 전투력은 $x_i$로 주어진다.

연속한 병사들로 하나의 특공대를 꾸리면 특공대의 전투력은 속해 있는 병사들의 전투력의 합이다.

그런데 다음부터는 어떤 상수 $a, b, c$에 대하여 특공대의 전투력을 다음과 같이 계산한다고 한다.

- 기존 전투력을 $x$라고 할 때, 새로운 전투력은 $ax^2 + bx + c$ 이다.

이때 적절히 특공대를 꾸려서 얻을 수 있는 최대의 새로운 전투력을 구하는 문제이다.

$j+1$번 병사부터 $i$번째 병사까지를 하나의 특공대로 만들면, 기존 전투력은 부분합 $s_k$를 이용하여 $s_i - s_j$ 로 구할 수 있다.

$DP\[i\]$를 $i$번 병사까지로 얻을 수 있는 최대의 전투력이라고 정의하자. 그렇다면,

\begin{aligned}
DP\[i\] = \min_{j < i} \left( DP\[j\] + a(s_i - s_j)^2 + b(s_i - s_j) + c \right)
\end{aligned}

와 같은 점화식을 얻을 수 있다. 위 식에서 $j$와 관련없는 항들을 빼서 정리하면,

\begin{aligned}
DP\[i\] = \min_{j < i} \left( -2a s_j \cdot s_i + DP\[j\] + a s_j^2 - b s_j \right) + a s_i^2 + b s_i + c
\end{aligned}

가 된다. 이때 $a$가 음수이고 $s_j$는 $j$에 대하여 증가하기 때문에 직선 $y = -2a s_j x + DP\[j\] + a s_j^2 - b s_j$ 의 기울기가 점차 증가한다는 것을 알 수 있다.

따라서 CHT를 이용하여 $O(n)$으로 해결할 수 있게 된다.

---

### [BOJ] 10067. 수열 나누기

[BOJ 10067. 수열 나누기 문제 링크](https://www.acmicpc.net/problem/10067)

음이 아닌 정수들로 이루어진 길이가 $n$인 수열에 대하여 선택한 부분수열을 두 조각으로 나누는 작업을 $k$번 수행하려고 한다.

부분수열을 나누었을 때 각 부분에 있는 원소들의 합을 곱한 만큼 점수를 얻을 수 있다.

이때 얻을 수 있는 최대 점수와 나누는 방법을 구하는 문제이다.

이 문제의 핵심은 크게 세 가지이다.

- 자르는 위치를 결정했다면 어느 순서로 자르던 간에 얻는 점수는 동일하므로 앞에서부터 자를 위치를 선택하면 된다.
- $i$번째 자르는 위치로 $j$번 원소의 오른쪽을 선택했을 때 얻을 수 있는 최대 점수를 $DP\[j\]\[i\]$로 정의하면, 각 $i$마다 CHT를 이용해서 $O(n)$으로 구할 수 있다.
- 역추적을 해서 나누는 방법을 얻을 수 있다.

<br/>

## 6. What if $B_j$ is not sorted?

추가적으로 $B_j$가 $j$에 대하여 감소하거나 증가하는 성질을 띠지 않는 경우를 살펴보자.

이런 경우라면 **이진 탐색 트리를 사용하여 $B_j$를 정렬된 순서대로 직선들을 관리**함으로써 문제를 해결할 수 있다.

직선을 삽입하고, 해당 직선과 **양쪽으로** 인접한 직선들과의 교점을 구하여 최대 또는 최소에 해당하지 않는 직선들을 삭제해주어야 한다.

이진 탐색 트리는 삽입과 삭제에 $O(\log n)$이 걸리기 때문에 시간복잡도는 $O(n \log n)$으로 동일하다.

---

### 6-1. Implementation using set

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;
typedef long long ll;

struct Line {
    mutable ll a, b, p; // y = ax + b, x = p 까지 최대값
    bool operator<(const Line& l) const { return a < l.a; }
    bool operator<(ll x) const { return p < x; }
};
struct LineContainer : multiset<Line, less<>> {
    const ll inf = 9e18;
    ll div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); } // 내림
    bool isect(iterator x, iterator y) {
        if (y == end()) { x->p = inf; return 0; }
        if (x->a == y->a) x->p = (x->b > y->b ? inf : -inf);
        else x->p = div(y->b - x->b, x->a - y->a);
        return x->p >= y->p;
    }
    void add(ll a, ll b) {
        auto z = insert({ a, b, 0 }), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
    }
    ll query(ll x) { // return max value
        auto l = *lower_bound(x);
        return l.a * x + l.b;
    }
};
```

---

### [BOJ] 12795. 반평면 땅따먹기

[BOJ 12795. 반평면 땅따먹기 문제 링크](https://www.acmicpc.net/problem/12795)

여러 개의 직선들이 기울기가 정렬되지 않은 상태로 주어지면서, 중간중간 특정 $x$값에서의 최댓값을 구해야한다.

<br/>

## References

[1] [secmem.org, koosaga, '동적 계획법을 최적화하는 9가지 방법 (Chapter 1)'](https://www.secmem.org/blog/2019/11/15/dpopt-ch1/)  
[2] [Codeforces, meooow, 'Convex Hull Trick - Geometry being useful'](https://codeforces.com/blog/entry/63823)  

