---
title: "Knapsack Problem"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` DP, Backtracking, Branch and Bound

## 0. Knapsack Problem

$n$개의 물건이 있을 때, $i$번째 물건의 무게를 $w_i$, 가치를 $v_i$라고 하자.

배낭에 넣을 수 있는 최대 무게가 $K$인 배낭이 있다.

이 배낭에 넣은 물건들의 가치의 합이 최대가 되도록 물건을 담고 싶다.

배낭에 담은 $i$번째 물건의 개수를 $x_i$라고 하면, $x_1, x_2, \dots, x_n$는 다음을 만족한다.

\begin{aligned}
\sum_{i = 1}^n w_ix_i \leq K
\end{aligned}

이때 가방에 담긴 물건들의 가치의 합 $\sum_{i=1}^n v_ix_i$이 최대가 되는 경우를 구하는 문제를 **knapsack problem**이라고 한다.

Knapsack problem은 $x_i$의 범위에 따라 다음과 같이 구분한다.

- **Bounded Knapsack Problem(BKP)**: 음이 아닌 정수 $c$가 주어졌을 때, 모든 $i$에 대해 $0 \leq x_i \leq c$를 만족하도록 제한을 둔 문제
- **Unbounded Knapsack Problem(UKP)**: $x_i$가 모든 음이 아닌 정수 값을 가질 수 있는 문제

특히 $c = 1$인 BKP를 **0-1 Knapsack Problem**이라고 부른다.

이번 포스팅에서는 0-1 knapsack problem을 해결하는 다양한 방법들에 대해 다루어 볼 것이다.

> 입력은 다음과 같이 주어진다.
> 
> - 첫 번째 줄에는 물건의 개수 `N`과 가방이 버틸 수 있는 무게 `K`가 주어진다.
> - 두 번째 줄부터 N개의 줄에 걸쳐 각 물건의 무게 `W[i]`와 가치 `V[i]`가 주어진다.

<br/>

## 1. Backtracking

DFS로 탐색하면서 백트래킹을 적용하는 방법이 있다.

백트래킹의 경우, 최악의 경우에는 모든 경우를 전부 탐색하게 되므로 시간복잡도는 $O(2^n)$이다.

### 1-1. Easy backtracking

모든 경우를 탐색하면서 가방에 담긴 무게가 $K$보다 큰 경우만 제거해주자.

각 물건을 선택하거나 선택하지 않는 경우로 나눌 수 있으므로 DFS를 사용하면 쉽게 전체 경우를 살펴볼 수 있다.

```cpp
#include <iostream>
using namespace std;

int N, K, ans;

int W[100], V[100];

void dfs(int idx, int w, int v)
{
    if (w > K) return; // 백트래킹: 가방에 담긴 무게의 합이 K보다 크면 pruning
    if (idx == N)
    {
        if (ans < v) ans = v;
        return;
    }
    
    dfs(idx + 1, w, v); // idx를 선택하지 않는 경우
    dfs(idx + 1, w + W[idx], v + V[idx]); // idx를 선택하는 경우
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> K;
    for (int i = 0; i < N; i++) cin >> W[i] >> V[i];
    
    dfs(0, 0, 0);
    cout << ans;
}
```

---

### 1-2. Improved Backtracking

DFS로 탐색할 때, 지금까지의 가방에 담은 물건들의 무게를 $w$, 가치의 합을 $v$라고 하자.

앞선 백트래킹 풀이에서는 $w > K$일 때만 pruning을 해주었지만, 이번에는 조금 더 강력한 기준을 사용해서 코드의 수행 시간을 단축시켜보자.

다음의 추가적인 변수를 정의하자.

- $w_{total}$: $w$ + (앞으로 담을 수 있는 물건들의 무게)
- $v_{bound}$: $v$ + (앞으로 담을 수 있는 물건들의 가치) + (남는 무게만큼의 partial value)
- $c_i$: 각 물건의 무게 1 당 가치 ($= v_i / w_i$)

상태공간트리에서 해당 노드가 유망한지(promising) 판단하는 방법은 다음과 같다.

---

1. $w_{total} = w$, $v_{bound} = v$로 초기화
2. $w_{total}$이 $K$를 초과하기 직전까지 Greedy하게 물건을 선택한다. (= $c_i$가 큰 물건부터 선택)
3. 가방에 담을 수 있는 남은 무게($= K - w_{total}$)만큼 다음 물건의 가치를 $v_{bound}$에 더해준다.
4. 만약 $v_{bound}$가 지금까지 구한 최댓값 $v_{max}$보다 작거나 같다면 해당 노드는 유망하지 않다.

---

물건들을 $c_i$에 대한 내림차순으로 정렬했을 때, 2번 과정에서 $m$번째 물건을 담았을 때 무게가 초과하게 되었다고 하자.

2번 과정에서 구한 $w_{total}$는 다음과 같다.

\begin{aligned}
w_{total} = w + \sum_{j = i + 1}^{m-1} w_j
\end{aligned}

3번 과정에서 구한 $v_{bound}$는 다음과 같다.

\begin{aligned}
v_{bound} = v + \sum_{j = i + 1}^{m-1} v_j + (K - w_{total}) \times c_m
\end{aligned}

DFS로 탐색하면서 각 노드에 대해 $v_{bound}$를 계산해서 해당 노드의 유망성을 판단하면 된다.

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int N, K, maxV;

int W[100], V[100];

double c[100];

bool compare(pair<int, int> A, pair<int, int> B)
{
    double c1 = ((double) A.second) / A.first;
    double c2 = ((double) B.second) / B.first;
    return c1 > c2;
}

bool isPromising(int idx, int w, int v)
{
    // 1
    int wTotal = w, j = idx;
    double vBound = v;
    
    // 2
    while (j < N && wTotal <= K)
    {
        wTotal += W[j];
        vBound += V[j];
        j++;
    }
    if (wTotal > K)
    {
        wTotal -= W[j-1];
        vBound -= V[j-1];
    }
    
    // 3
    if (j < N) vBound += (K - wTotal) * c[j];
    
    // 4
    return vBound > maxV;
}

void dfs(int idx, int w, int v)
{
    if (w <= K && v > maxV) maxV = v;
    if (idx == N) return;
    
    if (isPromising(idx, w, v))
    {
        dfs(idx + 1, w , v);
        dfs(idx + 1, w + W[idx], v + V[idx]);
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    cin >> N >> K;
    
    pair<int, int> WV[100];
    for (int i = 0; i < N; i++) cin >> WV[i].first >> WV[i].second;
    
    sort(WV, WV + N, compare); // 무게 1 당 가치가 높은 순으로 정렬
    
    for (int i = 0; i < N; i++)
    {
        W[i] = WV[i].first;
        V[i] = WV[i].second;
        c[i] = ((double) WV[i].second) / WV[i].first;
    }
    
    dfs(0, 0, 0);
    cout << maxV;
}
```

<br/>

## 2. Dynamic Programming

두 번째 풀이는 동적계획법을 사용하는 것이다.

배낭 문제의 가장 대표적인 풀이라고 할 수 있다.

### 2-1. Easy DP

다음과 같은 dp 배열을 생각하자.

> `dp[i][w]` = i번째 물건까지 탐색한 상황에서 배낭에 담긴 물건들의 무게가 w보다 작거나 같을 때의 최댓값

이때 `dp[i][w]`는 다음과 같이 구할 수 있다.

\begin{aligned}
dp[i][w] =
\begin{cases}
\max(dp[i-1][w], v_i + dp[i-1][w-w_i]), & \mbox{if } w_i \leq W \\  
dp[i-1][w], & \mbox{if } w_i > W
\end{cases}
\end{aligned}












