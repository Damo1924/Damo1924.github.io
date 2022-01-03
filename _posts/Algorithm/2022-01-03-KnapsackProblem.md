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

---

입력은 다음과 같이 주어진다.

- 첫 번째 줄에는 물건의 개수 `N`과 가방이 버틸 수 있는 무게 `K`가 주어진다.
- 두 번째 줄부터 N개의 줄에 걸쳐 각 물건의 무게 `W[i]`와 가치 `V[i]`가 주어진다.

---

## 1. Backtracking

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

이때 시간복잡도는 $O(2^n)$이다.

<br/>

## 2. Improved Backtracking

DFS로 탐색할 때, 지금까지의 가방에 담은 물건들의 무게를 $w$, 가치의 합을 $v$라고 하자.

앞선 백트래킹 풀이에서는 $w > K$일 때만 pruning을 해주었지만, 이번에는 조금 더 강력한 기준을 사용해서 코드의 수행 시간을 단축시켜보자.

다음의 추가적인 변수를 정의하자.

- $w_total$: $w$ + (앞으로 담을 수 있는 물건들의 무게)
- $v_bound$: $v$ + (앞으로 담을 수 있는 물건들의 가치) + (남는 무게만큼의 partial value)
- $c_i$: 각 물건의 무게 1 당 가치 ($= v_i / w_i$)

상태공간트리에서 해당 노드가 유망한지(promising) 판단하는 방법은 다음과 같다.

---

1. $w_total = w$, $v_bound = v$로 초기화
2. $w_total$이 $K$를 초과하기 직전까지 $Greedy하게 물건을 선택한다. (= $c_i$가 큰 물건부터 선택)
3. 가방에 담을 수 있는 남은 무게($= K - w_total$)만큼 다음 물건의 가치를 $v_bound$에 더해준다.
4. 만약 $v_bound$가 지금까지 구한 최댓값 $v_max$보다 작거나 같다면 해당 노드는 유망하지 않다.

---

물건들을 $c_i$에 대한 내림차순으로 정렬했을 때, 2번 과정에서 $m$번째 물건을 담았을 때 무게가 초과하게 되었다고 하자.

2번 과정에서 구한 $w_total$는 다음과 같다.

\begin{aligned}
w_total = w + \sum_{j = i + 1}^{m-1} w_j
\end{aligned}

3번 과정에서 구한 $v_bound$는 다음과 같다.

\begin{aligned}
v_bound = v + \sum_{j = i + 1}^{m-1} v_j + (K - w_total) \times c_m
\end{aligned}

DFS로 탐색하면서 각 노드에 대해 $v_bound$를 계산해서 해당 노드의 유망성을 판단하면 된다.







