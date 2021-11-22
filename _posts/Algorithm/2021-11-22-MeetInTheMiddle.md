---
title: "Meet in the Middle Algorithm"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

## Meet in the Middle Algorithm

Meet in the Middle Algorithm은 전체 input을 반으로 나누어서 문제를 해결하는 알고리즘을 의미한다.

단순히 문제를 두 번 푸는 것이 어떤 효과가 있는지 의문이 들 수 있지만, 시간 복잡도가 exponential한 문제에서는 고려해볼 만한 전략이다.

대표적으로 원소들의 합이 특정 값이 되는 부분집합의 개수를 구하는 문제를 해결하는데 이용된다.

전체 집합의 원소의 개수를 $n$이라고 할 때, 만들 수 있는 부분집합의 개수는 $2^n$이다.

$n = 30$ 정도만 되어도 $10^9$을 넘어가기 때문에 brute force로는 해결이 어렵다.

이럴 때 전체 집합을 반으로 쪼갠다면 $O(2^n)$을 $O(2 \times 2^{n/2}) = O(2^{n/2})$로 줄일 수 있게 된다.

그렇다면 직접 문제를 풀어보자.

## [백준] 1450. 냅색문제

**[PROBLEM]**

N개의 물건과 최대 C만큼의 무게를 견딜 수 있는 가방이 있다.

이때 N개의 물건을 적절히 선택하여 가방에 넣는 방법의 수를 구하여라.

**[INPUT]**

첫째 줄에 N과 C가 주어진다. (N은 30 이하의 자연수, C는 $10^9$ 이하의 음이 아닌 정수)

둘째 줄에 각 물건의 무게가 주어지며, 무게는 모두 $10^9$ 이하인 자연수이다.

**[OUTPUT]**

가방에 물건을 넣는 방법의 수를 출력한다.

**[SOLUTION]**

Meet in the Middle Algorithm을 사용하자.

전체 물건을 두 집합으로 나눈 후, 각 집합에 대해 모든 부분집합의 원소들의 합을 구한다.

전체 물건의 개수 N의 최댓값이 30이므로 반으로 나눈 두 집합에는 최대 15개의 물건이 들어갈 수 있는데, $2^15 = 32768$이므로 무리 없이 계산이 가능하다.

각 집합에 대해 모든 부분집합의 원소들의 합을 구해 벡터에 저장하자.

이제 두 집합의 물건을 동시에 포함하는 경우의 수를 구해주기 위해 각 벡터를 정렬한 다음 Two pointer algorithm을 이용하자.

전체 코드는 다음과 같다.

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
const int MAX = 1000000000;

int N, C, W[30];

vector<int> v;

void dfs (int idx, int sum, int M)
{
    if (sum > C) return; // C를 초과한 경우는 제외
    if (idx == M)
    {
        v.push_back(sum);
        return;
    }
    
    dfs(idx + 1, sum, M); // W[idx]를 포함하지 않는 부분집합
    dfs(idx + 1, sum + W[idx], M); // W[idx]를 포함하는 부분집합
}

int main()
{
    cin >> N >> C;
    for (int i = 0; i < N; i++) cin >> W[i];
    
    dfs(0, 0, N / 2); // 첫 N/2개의 물건들에 대해 계산
    sort(v.begin(), v.end()); // 위 결과를 정렬
    int lim = v.size();
    dfs(N / 2, 0, N); // 나머지 물건들에 대해 계산
    sort(v.begin() + lim, v.end()); // 위 결과를 정렬
    
    int e = v.size() - 1, ans = 0;
    for (int i = 0; i < lim; i++) // Two pointer (i, e)를 이용해서 선형 시간복잡도로 두 집합의 물건을 동시에 포함하는 경우를 계산
    {
        while (e >= lim && v[i] + v[e] > C) e--;
        if (e == lim - 1) break;
        ans += e - lim + 1;
    }
    cout << ans;
}
```

먼저 각 집합에 대해 모든 부분집합의 원소들의 합을 구하는 작업은 $O(2^{N/2})$의 시간복잡도를 가진다.

마지막에 Two pointer algorithm을 이용하여 전체 경우의 수를 구하는 작업은 $O(m)$의 시간복잡도를 가진다.

이때 $m$은 각 집합의 부분집합 중 원소들의 합이 C 이하인 것들의 개수이므로 $O(2^{N/2})$이다.

<br/>

## [백준] 






