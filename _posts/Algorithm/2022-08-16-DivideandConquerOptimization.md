---
title: "동적계획법에서의 분할정복 최적화 (Divide and Conquer Optimization)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:    
  - Algorithm
use_math: true
comments: true

---

`Tags` DP Optimization, 11001, 

## 1. Preconditions to use Divide & Conquer optimization method

두 정수 $m, n$이 주어졌을 때, $1 \leq i \leq m$, $1 \leq j \leq n$ 을 만족하는 두 정수 $i, j$에 대하여 다음 점화식이 성립한다고 하자.

\begin{aligned}
dp(i, j) = \min_{k < j} \left( dp(i - 1, k) + c(k, j) \right)
\end{aligned}

이때 $c(k, j)$는 $O(1)$에 구할 수 있는 값이다.

이를 최적화 없이 구하고자 한다면 $O(mn^2)$의 시간복잡도가 걸린다.

위의 점화식의 최솟값에 해당하는 $k$를 $opt(i, j)$라고 하고, (만약 그러한 $k$가 여러 개라면 그 중 가장 작은 값)

\begin{aligned}
opt(i, j) \leq opt(i, j + 1)
\end{aligned}

가 성립한다고 하자. 그렇다면 각 $i$에 대하여 분할정복을 통해 $O(n \log n)$의 시간복잡도로 $dp$값들을 구할 수 있게 된다.

$1 \leq i \leq m$ 이므로 전체 시간복잡도는 $O(mn \log n)$이다.

<br/>

## 2. Monotonicity condition & Monge array

앞서 사용한 $opt(i, j) \leq opt(i, j + 1)$ 라는 조건을 **monotonicity condition**이라고 부른다.

어떤 2차원 배열 $c(i, j)$가 **Monge array**이면, 임의의 $a \leq b \leq c \leq d$에 대하여

\begin{aligned}
c(a, c) + c(b, d) \leq c(a, d) + c(b, c)
\end{aligned}

를 만족하며, 이는 **monotonicity condition의 충분조건**이다.

이는 $opt(i, j)$의 정의를 이용하여 간단히 증명할 수 있다.

임의의 두 정수 $j_1 < j_2$ 에 대하여 $opt(i, j_1) = x_1$, $opt(i, j_2) = x_2$ 라고 하자.

이때 $x_1 > x_2$ 라고 가정하면,

- $dp(i, x_2) + c(x_2, j_2) \leq dp(i, x_1) + c(x_1, j_2)$
- $dp(i, x_1) + c(x_1, j_1) < dp(i, x_2) + c(x_2, j_1)$

가 성립한다.

> 두 번째 부등식에서 등호가 빠진 이유는 최솟값에 해당하는 $k$가 여러 개라면 그 중 가장 작은 것을 $opt$로 정의했기 때문이다.

두 식을 더하면,

\begin{aligned}
c(x_1, j_1) + c(x_2, j_2) < c(x_1, j_2) + c(x_2, j_1)
\end{aligned}

을 얻을 수 있다. 이때 $x_2 < x_1 \leq j_1 < j_2$ 이므로 위 식은 Monge array의 정의에 모순이다.

따라서 귀류법에 의해 $c(i, j)$가 Monge array이면 monotonicity condition이 성립함이 증명된다.

<br/>

## 3. Implementation

분할정복으로 구현해주면 된다.

```cpp

```

<br/>

## 4. Related Problems

### [BOJ] 11001. 김치

[BOJ 11001. 김치 문제 링크](https://www.acmicpc.net/problem/11001)

$i$번째 날에 넣고, $j$번째 날에 꺼낸 김치의 맛은 $(j - i) \cdot T_j + V_i$ 이다.

어떤 $i$에 대하여 $i$번째 날에 넣은 김치의 맛의 최댓값을 $A_i$라고 하면,

\begin{aligned}
A_i = \max_{i \leq k \leq j} \left( (k - i) \cdot T_k + V_i \right)
\end{aligned}

라고 쓸 수 있다. 이때 $A_i, A_{i+1}$에 해당하는 $k$값을 각각 $k_i, k_{i+1}$라고 하면,

- $(k_{i+1} - i) \cdot T_{k_{i+1}\} + V_i \leq (k_i - i) \cdot T_{k_i} + V_i$
- $(k_i - i - 1) \cdot T_{k_i} + V_{i+1} \leq (k_{i+1} - i - 1) \cdot T_{k_{i+1}\} + V_{i+1}$

이 성립한다. 두 식을 더해주면,

\begin{aligned}
T_{k_{i+1}\} \leq T_{k_i}
\end{aligned}

를 얻을 수 있고, $T_j$는 단조감소하므로 $k_i \leq k_{i+1}$ 임을 알 수 있다.

즉, 분할정복 최적화를 사용할 수 있는 문제이다.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;
const int mxN = 1e5 + 1;

int N, D, T[mxN], V[mxN];
ll ans = 0;
void dnc_opt(int s, int e, int l, int r) {
    if (s > e) return;
    int m = (s + e) / 2;
    pair<ll, int> res = { 0, -1 };
    int L = max(l, m), R = min(r, m + D);
    for (int i = L; i <= R; i++)
        res = max(res, { 1ll * (i - m) * T[i] + V[m], i });
    ans = max(ans, res.first);
    dnc_opt(s, m - 1, l, res.second);
    dnc_opt(m + 1, e, res.second, r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> D;
    for (int i = 1; i <= N; i++) cin >> T[i];
    for (int i = 1; i <= N; i++) cin >> V[i];
    dnc_opt(1, N, 1, N);
    cout << ans;
}
```

---






