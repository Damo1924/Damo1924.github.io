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

그래서 이번 포스팅에서는 이 알고리즘을 사용해서 어떤 문제들을 풀 수 있는지 그 예시들을 살펴보도록 하겠다.

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

## [백준] 2470. 두 용액

[백준 2470. 두 용액](https://www.acmicpc.net/problem/2470)

앞 문제와 거의 비슷한 문제이기 때문에 문제에 대한 설명을 생략하겠다.

$N$개의 정수가 주어질 때 두 정수를 더한 값들 중 0에 가장 가까운 경우를 찾아 두 정수를 출력하면 된다.

마찬가지로 두 포인터를 오름차순으로 정렬된 수열의 양 끝에 둔다.

만약 두 포인터가 가리키고 있는 두 정수의 합이 0보다 작으면 0에 더 가까운 값을 찾기 위해 왼쪽 포인터를 오른쪽으로 한 칸 옮긴다.

반대로 두 정수의 합이 0보다 크면 0에 더 가까운 값을 찾기 위해 오른쪽 포인터를 왼쪽으로 한 칸 옮겨준다.

이때 두 정수의 합이 0이라면 바로 해당하는 두 정수를 출력하면 된다.

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
    
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) cin >> a[i];
    
    sort(a, a + N); // 오름차순 정렬
    
    int x, y, s = 0, e = N - 1, sum = 2000000000; // 두 정수를 저장할 변수 x, y
    while (s < e)
    {
        int tmp = a[s] + a[e];
        if (abs(tmp) < sum) // 합의 절댓값이 더 작은 두 정수를 찾으면 갱신
        {
            x = a[s];
            y = a[e];
            sum = abs(tmp);
        }
        if (tmp < 0) s++;
        else if (tmp > 0) e--;
        else break; // 두 정수의 합이 0이라면 바로 반복문을 종료한다.
    }
    
    cout << x << " " << y;
}
```

<br/>

## [백준] 1806. 부분합

[백준 1806. 부분합](https://www.acmicpc.net/problem/1806)

**[PROBLEM]**

10,000 이하의 자연수로 이루어진 길이 N인 수열이 주어진다.

이 수열에서 연속된 수들의 부분합 중 S 이상이 되는 것 중 가장 짧은 것의 길이를 구하여라.

**[INPUT]**

첫째 줄에 수열의 크기 N과 S가 주어진다. ($10 \leq N \leq 10^5$, $0 < S \leq 10^8$)

둘째 줄에 N개의 숫자가 주어진다.

**[OUTPUT]**

부분합이 S 이상인 부분수열들 중 가장 짧은 것의 길이를 출력한다.

만약 부분합이 S 이상인 부분수열이 존재하지 않는다면 0을 출력한다.

**[SOLUTION]**

앞선 두 문제는 주어진 수열에서 임의로 두 숫자를 뽑아 그 합에 대해 탐색하는 문제였다면, 이 문제는 주어진 수열에서 부분합을 구하는 문제이다.

부분합 문제의 경우, 두 포인터를 수열의 양쪽 끝에 두고 시작하면 어느 포인터를 움직여도 부분합이 감소하므로 의미가 없다.

하나의 포인터는 부분합이 증가하도록, 나머지 하나는 부분합이 감소하도록 하기 위해서는 **두 포인터를 같은 위치에 두면 된다.**

부분수열의 첫 숫자를 가리키는 포인터를 오른쪽으로 옮기면 부분합이 감소하고, 부분수열의 마지막 숫자를 가리키는 포인터를 오른쪽으로 옮기면 부분합이 증가한다.

그러므로 부분합이 S보다 크면 부분수열의 시작 위치를 가리키는 포인터를 오른쪽으로 옮기고, 부분합이 S보다 작으면 부분수열의 끝 위치를 가리키는 포인터를 오른쪽으로 옮기면 된다.

전체 코드는 다음과 같다.

```cpp
#include <iostream>
using namespace std;

int a[100000];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int N, S;
    cin >> N >> S;
    for (int i = 0; i < N; i++) cin >> a[i];
    
    int s = 0, e = 0, len = 100001, sum = a[0];
    while (true)
    {
        if (sum >= S) // 조건을 만족하는 경우
        {
            if (len > e - s + 1) len = e - s + 1; // 길이가 더 짧으면 길이를 갱신
            if (s == e) break; // 조건을 만족하면서 길이가 1인 부분수열이 존재하므로 반복문을 종료하고 1을 출력하면 된다.
            else
            {
                sum -= a[s];
                s++;
            }
        }
        else
        {
            e++;
            if (e == N) break;
            sum += a[e];
        }
    }
    
    if (len == 100001) cout << "0";
    else cout << len;
}
```





