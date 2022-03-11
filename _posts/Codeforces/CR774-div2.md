---
title: "[CF#7] Codeforces Round #774 (Div. 2, except F)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Codeforces
use_math: true
comments: true

---

`Tags` 

## Result & Review

정말 역대급으로 많이 틀린 대회였다.

B번에서 3번, C번에서 2번, D번에서 2번 WA를 받았고, D번은 결국 풀지 못했다.

패널티를 하도 많이 받아서 엄청 등수가 떨어질 줄 알았는데, 생각보다 선방했다.

앞 문제들이 평소보다 까다롭긴 한 것 같다.

<img src="https://user-images.githubusercontent.com/88201512/157785745-caeb084f-d62f-4360-9ca8-b75b3cade6e5.jpg">

레이팅은 6점이 떨어져서 1593이다 ㅜㅜ

<br/>

## A. Squarer Counting

[A번 문제 링크](https://codeforces.com/contest/1646/problem/A)

**[PROBLEM]**

길이가 $n+1$인 수열 $a_1, a_2, \dots, a_{n+1}$에 대해 전체 수열의 합을 $s$라고 하자.

모든 $i$($1 \leq i \leq n + 1$)에 대해 $0 \leq a_i < n$ 또는 $a_i = n^2$이 성립한다.

$n$과 $s$의 값이 주어질 때, 수열에 $n^2$이 몇 개나 있는지 구하여라.

**[INPUT]**

첫 번째 줄에는 테스트케이스의 개수 $t$($1 \leq t \leq 2 \cdot 10^4$)가 주어진다.

각 테스트케이스에 대해 두 정수 $n, s$($1 \leq n < 10^6$, $0 \leq s \leq 10^18$)가 주어진다.

**[OUTPUT]**

각 테스트케이스에 대해 수열에 있는 $n^2$의 개수를 출력한다.

---

### [SOLUTION] Math

$n^2$이 아닌 원소 $n + 1$개의 합의 최댓값은 $(n + 1)(n - 1) = n^2 - 1$이다.

이 값은 $n^2$보다 항상 작기 때문에 수열에 있는 $n^2$의 개수는 $\lfloor \frac{s}{n^2} \rfloor$이다.

```cpp
#include <iostream>
using namespace std;
typedef long long ll;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int t; cin >> t;
    while (t--)
    {
        ll n, s; cin >> n >> s;
        cout << s / (n * n) << "\n";
    }
}
```

<br/>

## B. Quality vs Quantity

[B번 문제 링크](https://codeforces.com/contest/1646/problem/B)

**[PROBLEM]**

음이 아닌 정수로 이루어진 길이가 $n$인 수열 $a_1, a_2, \dots, a_n$이 주어진다.

처음에는 모든 원소가 'unpainted' 상태이고, 각 원소를 'Red' 또는 'Blue'로 칠하거나 그대로 내버려둘 수 있다.

색깔 $c$에 대해 $Count(c)$는 $c$로 칠해진 원소의 개수, $Sum(c)$는 $c$로 칠해진 원소의 합을 의미한다.

주어진 수열 $a$에 대해 다음을 만족하도록 원소들을 칠할 수 있는지 판단하여라.

\begin{aligned}
Sum(Red) > Sum(Blue), Count(Red) < Count(Blue)
\end{aligned}

**[INPUT]**

첫 번째 줄에는 테스트케이스의 개수 $t$($1 \leq t \leq 2 \cdot 1000$)가 주어진다.

각 테스트케이스는 다음과 같이 이루어진다.

첫 번째 줄에는 정수 $n$($3 \leq n \leq 2 \cdot 10^5$)가 주어진다.

두 번째 줄에는 $n$개의 정수 $a_1, \dots, a_n$($0 \leq a_i \leq 10^9$)가 주어진다.

**[OUTPUT]**

각 테스트케이스에 대해 조건을 만족하도록 원소들을 칠할 수 있으면 "YES"를, 없으면 "NO"를 출력한다.

---

### [SOLUTION] Constructive algorithm










