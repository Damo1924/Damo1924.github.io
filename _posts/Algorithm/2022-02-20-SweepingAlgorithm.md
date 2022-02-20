---
title: "스위핑 알고리즘(Sweeping Algorithm)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` 

## 1. Sweeping Algorithm

스위핑 알고리즘은 정렬된 순서대로 탐색을 해나가는 기법을 말한다.

사실 어떤 알고리즘이라고 부를만큼 복잡한 매커니즘이 있는 것은 아니지만, 특정 문제들에서 굉장히 강력한 모습을 보여준다.

다른 알고리즘들과 함께 이용되는 경우가 많기 때문에 스위핑 알고리즘을 이용해야겠다는 생각을 하기 쉽지 않다.

이번 포스팅에서는 스위핑 알고리즘을 이용하는 여러가지 문제들을 직접 풀어볼 것이다.

<br/>

## [백준] 2170. 선 긋기

[백준 2170. 선 긋기 문제 링크](https://www.acmicpc.net/problem/2170)

**[PROBLEM]**

$x$축 위에 $N$개의 선을 그으려고 한다.

이때 겹치는 부분의 길이를 한 번씩만 계산할 때, 그은 선의 총 길이를 구하여라.

**[INPUT]**

첫 번째 줄에 선의 개수 $N$($1 \leq N \leq 10^6$)가 주어진다.

다음 $N$개의 줄에 걸쳐 각 선의 시작점과 끝점의 좌표 $x, y$($-10^9 \leq x < y \leq 10^9$)가 주어진다.

**[OUTPUT]**

선들의 총 길이를 출력한다.

---

### [SOLUTION] Sweeping algorithm

스위핑 알고리즘을 설명하는데 있어 가장 대표적인 문제 중 하나이다.

선들을 시작 좌표를 기준으로 정렬한 뒤, 순서대로 탐색하면서 선들의 길이를 측정해준다.

현재까지 탐색한 선의 끝 좌표를 $y$, 다음 선의 시작 좌표를 $x$라고 하면 다음과 같이 경우를 나눌 수 있다.

1. $y < x$ : 선이 끊어진 경우
2. $x \leq y$ : 선이 이어지는 경우

경우에 맞게 처리해주면 $O(N)$에 답을 구할 수 있다.

선들을 정렬해야하므로 전체 시간복잡도는 $O(N \log N)$이다.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int N; cin >> N;
    vector<pair<int, int> v(N);
    for (int i = 0; i < N; i++) cin >> v[i].first >> v[i].second;
    sort(v.begin(), v.end());

    ll ans = 0;
    int x = v[0].first, y = v[0].second;
    for (int i = 1; i < N; i++)
    {
        if (v[i].first <= y) y = max(y, v[i].second);
        else { ans += y - x; x = v[i].first; y = v[i].second; }
    }
    ans += y - x;
    cout << ans;
}
```

<br/>

## [백준] 2836. 수상 택시

[백준 2170. 선 긋기 문제 링크](https://www.acmicpc.net/problem/2836)

**[PROBLEM]**

상근이가 살고 있는 도시에는 큰 강이 흐르고 있고, 강가를 따라서 $0$번부터 $M$번까지의 집들이 배치되어 있다.

인접한 집 사이의 거리는 모두 1이다.

상근이는 수상 택시를 타고 $0$번 집에서 $M$번 집으로 이동하려고 한다.

수상 택시를 타려는 $N$명의 사람들의 탑승 지점과 목적지가 주어질 때, 상근이가 $0$번 집부터 $M$번 집으로 가기 위한 최소 이동거리를 구하여라.

**[INPUT]**

첫 번째 줄에 두 정수 $N, M$이 주어진다.($N \leq 300000; 3 \leq M \leq 10^9$)

다음 $N$개의 줄에는 탑승자들의 탑승 지점과 목적지가 $0$ 이상 $M$ 이하의 정수로 주어진다.

**[OUTPUT]**

상근이의 최소 이동 거리를 출력한다.

---

### [SOLUTION] Sweeping algorithm

택시를 타려는 사람 중 일부는 정방향(상근이와 같은 방향)으로, 나머지는 역방향으로 이동하려고 한다.

정뱡향으로 이동하는 사람들은 따라 추가적인 이동거리를 발생시키지 않는다.

역방향으로 이동하는 사람들은 그 거리의 2배만큼의 추가적인 이동거리를 발생시킨다.

그렇기 때문에 **역방향으로 이동하는 사람들을 모아 그 경로의 총 길이**를 $L$이라고 하면, 상근이의 최소 이동거리는 다음과 같다.

\begin{aligned}
M + 2L
\end{aligned}

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    int N, M; cin >> N >> M;
    
    vector<ii> v;
    for (int i = 0; i < N; i++)
    {
        int s, e; cin >> s >> e;
        if (s > e) v.push_back({ e, s });
    }
    sort(v.begin(), v.end());

    ll reverse = 0;
    int x = v[0].first, y = v[0].second;
    for (int i = 1; i < v.size(); i++)
    {
        if (y < v[i].first) { reverse += y - x; x = v[i].first; y = v[i].second; }
        else y = max(y, v[i].second);
    }
    reverse += y - x;
    cout << M + 2 * reverse;
}
```

<br/>

## [백준] 5419. 북서풍

[백준 5419. 북서풍 문제 링크](https://www.acmicpc.net/problem/5419)

**[PROBLEM]**

강한 북서풍이 불고 있기 때문에 북쪽이나 서쪽으로 항해가 불가능하다.

바다 위에 작은 섬이 $n$개가 있고, 각 섬은 좌표 평면의 한 점으로 나타낼 수 있다.

$y$좌표가 증가하는 방향이 북쪽, $x$좌표가 증가하는 방향이 동쪽이다.

이때 북서풍을 타고 항해할 수 있는 섬의 쌍의 개수를 구하여라.

**[INPUT]**

첫 번째 줄에는 테스트케이스의 개수가 주어진다.

각 테스트케이스의 첫 번째 줄에는 섬의 개수 $n$($1 \leq n \leq 75000$)이 주어진다.

다음 $n$개의 줄에 걸쳐 각 섬의 좌표 $x_i, y_i$($-10^9 \leq x_i, y_i \leq 10^9$)가 주어진다.

단, 두 섬의 좌표가 같은 경우는 없다.

**[OUTPUT]**

각 테스트케이스에 대해 북서풍을 타고 항해할 수 있는 섬의 쌍의 개수를 출력한다.

---

### [SOLUTION] Sweeping algorithm + Segment tree


