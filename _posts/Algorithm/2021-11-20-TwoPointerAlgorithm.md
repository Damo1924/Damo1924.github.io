---
title: "Two Pointer Algorithm"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

## Two Pointer Algorithm

투 포인터 알고리즘은 두 개의 포인터를 이용해서 리스트를 탐색하는 알고리즘이다.

이름에 포인터가 들어가서 처음에는 어려운 알고리즘인줄 알았으나 정말 간단한, 심지어 Merge sort를 구현할 때 사용했던 방법이었다.

아마 많은 PS러들이 이 알고리즘을 따로 공부하지 않고서도 자연스럽게 사용하고 있을 것이라 생각한다.

그래서 이번 포스팅에서는 이 알고리즘을 사용해서 어떤 문제들을 풀 수 있는지 그 예시들을 살펴보았다.

<br/>

## [백준] 3273. 두 수의 합

[백준 3273. 두 수의 합](https://www.acmicpc.net/problem/3273)

**[PROBLEM]**

$n$개의 서로 다른 양의 정수 $a_1$, $a_2$, ..., $a_n$으로 이루어진 수열이 있다.

자연수 $x$가 주어질 때, $a_i + a_j = x$를 만족하는 $i$, $j$ ($i < j$)의 쌍의 개수를 구하여라.

**[INPUT]**

첫째 줄에 수열의 크기 $n$이 주어진다. ($1 \leq n \leq 100,000$)

둘째 줄에 $n$개의 숫자가 주어지며, 마지막 줄에는 $x$가 주어진다. ($1 \leq x \leq 2,000,000)

**[OUTPUT]**

조건을 만족하는 ($i$, $j$) 쌍의 개수를 출력한다.

**[SOLUTION]**

주어진 수열을 오름차순으로 정렬한 후에 포인터 하나를 왼쪽 끝에, 다른 포인터 하나를 오른쪽 끝에 둔다.

포인터가 가리키는 두 원소의 합이 $x$보다 작거나 같으면 합을 증가시키기 위해 왼쪽 포인터를 오른쪽으로 한 칸 옮긴다.

반대로 두 원소의 합이 $x$보다 크면 합을 감소시키기 위해 오른쪽 포인터를 왼쪽으로 한 칸 옮긴다.

이 과정을 두 포인터가 만날 때까지 반복하면서 두 원소의 합이 $x$와 같을 때마다 개수를 세주면 답을 얻을 수 있다.

전체 코드는 다음과 같다.

```cpp
#include <iostream>
#include <algorithm>
using namespace std;

int a[100000];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, x;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> a[i];
    cin >> x;
    
    sort(a, a + n); // 오름차순 정렬
    
    int s = 0, e = n - 1, ans = 0; // Two pointers: s, e
    while (s < e)
    {
        int sum = a[s] + a[e];
        if (sum == x) ans++;
        if (sum <= x) s++;
        else e--;
    }
    cout << ans;
}
```

아주 간단한 알고리즘이지만 효과는 매우 강력하다.

서로 다른 $n$개의 숫자들 중 두 개를 뽑는 경우의 수는 $O(n^2)$이지만, 이 알고리즘으로는 $O(n \log n)$의 시간복잡도로 문제를 해결할 수 있다.

**[BETTER SOLUTION]**

사실 이 문제는 좀 더 효과적인 방법이 있다.

바로 주어진 수열에 $i$와 $(x - i)$가 동시에 존재하는 경우의 수를 계산하면 된다.

다음 코드를 보자.

```cpp
#include <iostream>
#include <bitset>
using namespace std;
const int Max = 1000000;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    bitset<1000001> a;
    int n, m, x;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> m;
        a[m] = 1;
    }
    cin >> x;
    
    int ans = 0;
    for (int i = 1; i < x/2; i++)
    {
        if (i > Max || x - i > Max) continue;
        else if (a[i] && a[x - i]) ans++;
    }
    if ((x % 2 == 1) && a[x/2] && a[x/2 + 1]) ans++;
    cout << ans;
}
```

$a_i$의 최댓값이 1,000,000이므로 `bitset`을 이용해서 메모리의 사용을 최소화하였다.

또한 $i$의 범위를 1부터 `x/2`까지 제한해서 동일한 케이스를 두 번 더하지 않도록 해주었다.

다만 이로 인해 $x$가 홀수인 경우에는 `x/2`와 `x/2 + 1`를 추가로 확인해야했다.

이 방법은 수열을 정렬할 필요가 없기 때문에 입력의 최댓값을 $m$이라 하면 $O(m)$의 시간복잡도를 갖는다.

해당 문제의 경우에는 수열의 길이의 최댓값이 100,000이고 각 숫자의 최댓값이 1,000,000이라서 10배 차이밖에 나지 않으므로 두 번째 방법이 더 효율적이다.

그러므로 문제의 제한 조건을 잘 고려해서 방법을 선택하면 된다.

<br/>

## [백준] 








