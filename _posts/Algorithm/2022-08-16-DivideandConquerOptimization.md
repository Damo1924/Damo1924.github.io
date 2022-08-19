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
ll dp[mxM][mxN], c[mxN][mxN];
void dnc_opt(int i, int s, int e, int l, int r) {
    if (s > e) return;
    int m = (s + e) / 2;
    pair<ll, int> res = { 1e18, -1 };
    for (int k = l; k <= r; k++)
        res = min(res, { dp[i - 1][k] + c[m][k] });
    dp[i][m] = res.first;
    dnc_opt(i, s, m - 1, l, res.second);
    dnc_opt(i, m + 1, e, res.second, r);
}
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

날짜의 수를 $N$, 숙성 시간의 최댓값을 $D$라고 할 때, 최적화를 사용하지 않으면 $O(ND)$이 걸리지만,

분할정복 최적화를 사용하면 $O(N \cdot \min(D, \log N))$ 으로 해결할 수 있게 된다.

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

### [BOJ] 13261. 탈옥

[BOJ 13261. 탈옥 문제 링크](https://www.acmicpc.net/problem/13261)

$L$개의 칸으로 이루어진 감옥이 있고, 각 칸에는 죄수가 한 명씩 들어있다.

$i$번 칸에 있는 죄수의 탈옥 능력을 수치로 나타낸 것을 $C_i > 0$라고 한다.

감옥에는 최대 $G$명의 간수를 배치할 수 있고, 각 간수는 연속한 여러 개의 칸들을 감시할 수 있다.

이때 감옥의 탈옥 위험도는 모든 $i$에 대하여 $C_i$와 $i$번 칸을 감시하고 있는 간수가 감시하고 있는 죄수의 수를 곱한 것을 모두 더한 것이다.

감옥의 탈옥 위험도의 최솟값을 구하기 위해 다음과 같은 dp 배열을 정의하자.

- $dp(i, j)$ : 간수를 $i$명 고용하여 만들 수 있는 $1$번 칸부터 $j$번 칸까지의 탈옥 위험도의 최솟값

그렇다면 구하고자 하는 값은 $dp(G, L)$이 되고, 다음과 같은 점화식을 세울 수 있다.

\begin{aligned}
dp(i, j) = \min_{i - 1 \leq k < j} \left( dp(i - 1, k) + c(k, j) \right)
\end{aligned}

이때 비용 $c(k, j)$는 $i$번째 간수가 $k+1$번 칸부터 $j$번 칸까지를 감시할 때 발생하는 탈옥 위험도이다.

\begin{aligned}
c(k, j) = (j - k) \cdot \sum_{x = k + 1}^j C_x
\end{aligned}

위 비용 함수가 monotonicity condition을 만족한다는 것은 쉽게 알 수 있다.

Naive하게 구하면 $O(GL^2)$이지만, 분할정복 최적화를 이용하면 $O(GL \log L)$ 의 시간복잡도로 해결할 수 있다.

> $C_i$들의 prefix sum을 미리 구해두면 $c(k, j)$를 $O(1)$에 구할 수 있다.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long ll;

int L, G, C[8001];
ll S[8001], dp[801][8001];
void dnc_opt(int i, int s, int e, int l, int r) {
    if (s > e) return;
    int m = (s + e) / 2;
    pair<ll, int> res = { 1e18, -1 };
    int L = max(l, i - 1), R = min(r, m - 1);
    for (int k = L; k <= R; k++)
        res = min(res, { dp[i - 1][k] + 1ll * (m - k) * (S[m] - S[k]), k });
    dp[i][m] = res.first;
    dnc_opt(i, s, m - 1, l, res.second);
    dnc_opt(i, m + 1, e, res.second, r);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    cin >> L >> G;
    for (int i = 1; i <= L; i++) {
        cin >> C[i];
        S[i] = S[i - 1] + C[i];
        dp[1][i] = S[i] * i;
    }
    if (L <= G) cout << S[L];
    else {
        for (int i = 2; i <= G; i++) dnc_opt(i, 1, L, 1, L);
        cout << dp[G][L];
    }
}
```






