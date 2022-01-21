---
title: "삼분 탐색(Ternary Search)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` Parametric Search, 8986 전봇대

## 1. What is Ternary Search?

삼분 탐색은 **볼록 함수에서 극값이나 최대/최솟값을 찾을 때** 사용하는 방법이다.

이분 탐색이 항상 단조 증가/감소하는 함수에만 사용할 수 있었던 것에 비해, 삼분 탐색은 더 많은 함수에 대해 적용할 수 있다는 장점이 있다.

방법 자체는 이분 탐색과 크게 다르지 않다.

아래로 볼록한 함수 $f(x)$의 최솟값을 찾는 경우를 생각해보자.($x$는 정수값만을 가진다고 가정)

주어진 $x$값의 구간을 $\[s, e)$라고 하면, 해당 구간을 삼등분하는 두 값 $p, q$는 다음과 같다.

\begin{aligned}
p = \left\lfloor \frac{2s + e}{3} \right\rfloor, q = \left\lfloor \frac{s + 2e}{3} \right\rfloor
\end{aligned}

전체 구간은 $\[s, p)$, $\[p, q)$, $\[q, e)$로 나누어진다.

여기서 $f(p)$와 $f(q)$ 값에 따라 두 가지 경우로 나눌 수 있다.

1. $f(p) > f(q)$: 구간 $\[s, p)$에서 최솟값을 가질 수 없으므로 탐색 범위를 $\[p, e)$로 줄인다.
2. $f(p) < f(q)$: 구간 $\[q, e)$에서 최솟값을 가질 수 없으므로 탐색 범위를 $\[s, q)$로 줄인다.

위 과정을 한 번 수행할 때마다 구간의 길이가 $\frac{2}{3}$으로 줄어들기 때문에,

\begin{aligned}
T(n) = T \left( \frac{2n}{3} \right) + 1
\end{aligned}

이라 할 수 있고, 이는 master theorem에 의해 $\Theta (\log n)$의 시간복잡도를 갖는다.

> **Master Theorem**은 재귀함수의 시간복잡도를 구하는데 이용되는 정리로, 자세한 내용은 [이 포스트]()에서 다루고 있다.

<br/>

## 2. When To Use It?

단순히 볼록 함수에서 사용한다고 했으나, 그렇다고 무조건적으로 삼분 탐색을 이용할 필요는 없다.

예를 들어 미분이 가능한 볼록 함수의 경우에는 도함수가 단조 증가/감소하기 때문에 도함수를 구해서 이분탐색을 사용하면 최대/최솟값을 구할 수 있다.

이처럼 볼록 함수의 극값이나 최대/최솟값을 구할 때 반드시 삼분 탐색을 이용하기보다는, **미분이 불가능하거나 도함수를 구하기 어려운 경우**에 사용하게 된다.

또, 삼분 탐색을 이용할 때 주의해야하는 점은 **기울기가 0인 구간**의 존재 유무이다.

만약 구간을 나누는 $p, q$가 모두 기울기가 0인 구간에 포함된다면, 아래 그림처럼 어느 쪽으로 구간을 좁혀야하는지 알 수 없게 된다.

<center><img src="https://user-images.githubusercontent.com/88201512/150106671-7671e38a-5ebb-43e1-99d8-69d81a67005c.jpg" width="45%" height="45%"></center>

(물론 기울기가 0인 구간이 최솟값에 해당된다면 상관없다.)

<br/>

## 3. Implementation

삼분 탐색을 이용해서 해결할 수 있는 문제를 풀어볼 것이다.

### [백준] 8986. 전봇대

[백준 8986. 전봇대 문제 링크](https://www.acmicpc.net/problem/8986)

x축 위에 N개의 전봇대가 나열되어 있다.($1 \leq N \leq 100000$)

이 전봇대들을 이웃한 두 전봇대 사이의 거리가 모두 일정하도록 일부 전봇대들을 옮기려고 한다.

이때 이동해야하는 전봇대들의 거리의 합이 최소인 경우를 구하는 문제이다.

단, 전봇대는 항상 정수 좌표에만 있을 수 있으며 가장 왼쪽에 위치한 전봇대의 위치는 0으로 고정되어 있으며 움직일 수 없다.

**[Solution]**

전봇대들의 초기 위치를 $x_0, x_1, \dots, x_{N-1}$이라 하고, 이웃한 전봇대 사이의 거리를 $d$라고 하면, 전봇대들의 이동거리 합 $f(d)$는 다음과 같다.

\begin{aligned}
f(d) = \sum_{i = 0}^{N-1} \left\vert id - x_i \right\vert
\end{aligned}

우리는 $f(d)$를 최소로 만드는 $d$의 값을 구하고자 한다.

함수 $f(d)$의 그래프가 어떤 형태를 가질지 생각해보자.

1. 절댓값들의 합으로 이루어진 함수이므로, 각 절댓값이 0이 되는 $d$값을 경계로 함수가 달라지게 된다.
2. 각 구간에서 $f(d)$의 그래프는 선분이며, 오른쪽에 있는 구간일수록 기울기가 점차 커지게 된다.

즉, 아래 그래프와 같은 형태를 가질 것이다.

<center><img src="https://user-images.githubusercontent.com/88201512/149664037-82ff46ee-60c1-4c6a-a804-be06bce56b0a.jpg" width="60%" height="60%"></center>

따라서 $f(d)$는 항상 아래로 볼록한 함수로, 삼분 탐색을 적용할 수 있다는 사실을 알 수 있다.

전체 코드는 다음과 같다.

```cpp
#include <iostream>
using namespace std;
typedef long long ll;

int N;

ll X[100000];

ll f(int d)
{
    ll sum = 0;
    for (int i = 0; i < N; i++) sum += abs((ll) i * d - X[i]);
    return sum;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N;
    for (int i = 0; i < N; i++) cin >> X[i];
    
    int s = 0, e = X[N-1];
    while (s + 2 < e)
    {
        int p = (2 * s + e) / 3, q = (s + 2 * e) / 3;
        if (f(p) > f(q)) s = p;
        else e = q;
    }
    if (s + 1 == e) cout << min(f(s), f(s + 1));
    else cout << min(f(s), min(f(s + 1), f(s + 2)));
}
```

삼분 탐색을 통해 최솟값에 해당하는 $d$를 찾는데 $O(\log N)$, 매번 $f(d)$를 계산하는데 $O(N)$이므로 총 시간복잡도는 $O(N \log N)$이다.

> 이처럼 삼분 탐색을 이용하는 문제의 핵심은 문제에서 **최대/최솟값을 구해야하는 함수가 삼분 탐색을 이용할 수 있는 함수인지 판단**하는 것이 가장 중요하다.

**[Additional Solution]**

다만, 이 문제의 경우에는 반드시 삼분탐색을 이용해서 풀지 않아도 된다.

$f(d)$의 최솟값은 **일차함수의 기울기가 음수에서 양수로 바뀌는 부분**이므로 각 구간의 기울기를 구함으로써 최솟값을 얻을 수 있다.

이를 위해서는 전봇대들을 절댓값 0이 되는 위치에 따라 정렬해주어야 한다.

```cpp
#include <iostream>
#include <algorithm>
using namespace std;
typedef long long ll;

struct utilityPole {
    ll x; // 초기 x 좌표
    int k; // x_k
    double y; // k * d - x_k = 0인 d값 = x_k / k
} UP[100000];

bool compare(utilityPole A, utilityPole B) { return A.y < B.y; }

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int N, x0;
    cin >> N;
    cin >> x0;
    for (int i = 1; i < N; i++)
    {
        cin >> UP[i].x;
        UP[i].k = i;
        UP[i].y = (double) UP[i].x / i;
    }
    
    // 1. 구간 순서대로 정렬
    sort(UP, UP + N, compare);
    
    // 2. 최솟값이 포함된 구간 찾기
    ll co = (ll) N * (N - 1) / 2; // 첫 번째 구간에서의 기울기 * (-1)
    int i;
    for (i = 0; i < N; i++)
    {
        co -= 2 * UP[i].k; // 구간이 변할 때마다 기울기 갱신
        if (co <= 0) break; // 부호가 변하면 break
    }
    
    // 3. 최솟값 구하기
    ll d = (ll) UP[i].y, ans1 = 0, ans2 = 0;
    for (int j = 0; j < N; j++)
    {
        ans1 += abs((ll) UP[j].k * d - UP[j].x);
        ans2 += abs((ll) UP[j].k * (d + 1) - UP[j].x);
    }
    cout << min(ans1, ans2);
}
```









