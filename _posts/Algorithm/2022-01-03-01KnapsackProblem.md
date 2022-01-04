---
title: "0-1 Knapsack Problem"
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

모든 경우를 탐색하면서 가방에 담긴 무게가 $K$보다 큰 경우를 제거해주자.

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

<br/>

## 2. Dynamic Programming

두 번째 풀이는 동적계획법을 사용하는 것이다.

배낭 문제의 가장 대표적인 풀이라고 할 수 있다.

물건이 $n$개 있고, 가방의 최대 용량이 $K$이면, 시간복잡도는 $O(nK)$이다.

### 2-1. Easy DP

다음과 같은 dp 배열을 생각하자.

> `dp[i][w]` = i번째 물건까지 탐색한 상황에서 배낭에 담긴 물건들의 무게가 w보다 작거나 같을 때의 최댓값

이때 `dp[i][w]`는 다음과 같이 구할 수 있다.

\begin{aligned}
dp[i][w] =
\begin{cases}
\max(dp[i-1][w], v_i + dp[i-1][w-w_i]), & \mbox{if } w_i \leq w \\\\  
dp[i-1][w], & \mbox{if } w_i > w
\end{cases}
\end{aligned}

우리가 구하고자 하는 값은 $N$번째 물건까지 전부 탐색했을 때 가방에 담긴 물건들의 무게가 $K$ 이하인 경우이므로 `dp[N][K]`이다.

반복문을 통해 dp 배열의 값들을 채워주면 된다.

```cpp
#include <iostream>
using namespace std;

int dp[101][100001];

int N, K;

int W[101], V[101];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N >> K;
    for (int i = 1; i <= N; i++) cin >> W[i] >> V[i];
    
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= K; j++)
        {
            if (j >= W[i]) dp[i][j] = max(dp[i - 1][j], V[i] + dp[i - 1][j - W[i]]);
            else dp[i][j] = dp[i - 1][j];
        }
    }
    
    cout << dp[N][K];
}
```

---

### 2-2. Improved DP

이번에는 조금 더 시간적, 공간적으로 효율적인 방식으로 위 풀이를 개선해보자.

위 풀이에서 dp 배열이 어떻게 채워지는지 보자.

`dp[i][j]`를 구하는데 `dp[i-1][j]` 또는 `dp[i-1][j-w]`를 사용한다.

그러므로 굳이 2차원 배열을 사용하지 말고 `j`를 큰 쪽부터 갱신해나가면 된다.

```cpp
#include <iostream>
using namespace std;

int dp[100001]; // 일차원 배열만 사용해도 된다.

int N, K;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N >> K;
    
    int w, v;
    for (int i = 0; i < N; i++)
    {
        cin >> w >> v;
        for (int j = K; j >= w; j--) dp[j] = max(dp[j], v + dp[j - w]); // j를 큰 쪽부터 갱신
    }
    
    cout << dp[K];
}
```

<br/>

## 3. Branch and Bound

이번에는 분기한정법(branch and bound)를 이용해서 풀어보자.

분기한정법은 DFS, BFS 어느 방법으로도 구현해도 괜찮지만, 백트래킹으로 해결한 것과 같이 DFS를 사용해보았다.

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

백트래킹 방식과 마찬가지로 최악의 경우에는 전체 경우의 수를 전부 탐색하게 되므로 $O(2^n)$의 시간복잡도를 갖는다.

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

## 4. Analysis

백트래킹 방법과 분기한정법은 $O(2^n)$, 동적계획법은 $O(nK)$의 시간복잡도를 갖는다.

Knapsack problem은 아직까지 해결할 수 있는 polynomial algorithm이 알려져 있지 않다.

일반적으로 동적계획법이나 분기한정법을 이용하는데, 분기한정법은 $n$이 커질수록 시간복잡도가 크게 증가한다는 단점이 있고, 동적계획법은 가방의 용량이 매우 커질 때 비효율적이라는 단점이 있다.

다만, 백트래킹이나 분기한정법의 경우에는 시간복잡도로 효율성을 판단하기는 어렵다는 점에 주의해야한다.

아래 문제는 $n$이 100까지, $K$가 100,000까지 주어질 수 있는 0-1 knapsack problem이다.

[백준 12865. 평범한 배낭 문제 링크](https://www.acmicpc.net/problem/12865)

$n$이 크기 때문에 분기한정법으로는 시간초과가 발생하지만, 동적계획법으로는 충분히 해결 가능하다.

<br/>

## Reference

[1] [WIKIPEDIA, 'Knapsack problem'](https://en.m.wikipedia.org/wiki/Knapsack_problem)  





