---
title: "Finding Palindrome using Manacher's Algorithm"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:    
  - Algorithm
use_math: true
comments: true

---

`Tags` 문자열 알고리즘, 펠린드롬, 

## 1. Idea of the algorithm

Manacher's algorithm은 **주어진 문자열에 존재하는 모든 펠린드롬**을 빠르게 찾는 알고리즘이다.

문자열의 길이를 $N$이라고 하면, 알고리즘의 시간복잡도는 $O(N)$이다.

---

문자열에 존재하는 모든 펠린드롬을 찾는 것은, 다음과 같이 정의되는 배열 $A$를 구하는 것과 동일하다.

- $A\[i\]$ : **$i$번째 문자를 중심으로 하는 가장 긴 펠린드롬의 반지름의 길이**

이때 펠린드롬의 반지름이란 대칭인 부분의 길이를 의미한다.

예를 들어 펠린드롬 문자열 `BCACB`의 반지름은 $2$이다.

그런데 이렇게 배열 $A$를 구한다고 해도, **길이가 짝수인 펠린드롬**은 구하지 못한다는 것을 알 수 있다.

따라서 길이가 짝수인 펠린드롬까지 구해주기 위해서 **문자열을 이루는 문자 사이사이에 문자열에 포함되지 않는 임의의 문자를 삽입**해준다.

예를 들어 문자열 `ABBA`가 주어지면, `A#B#B#A`로 바꾸어준 후에 앞서 정의한 배열 $A$를 구해주는 것이다.

---

이제 배열 $A$를 $O(N)$에 구하는 방법을 알면 되는데, 일반적으로 구하면 $O(N^2)$이 걸리게 된다.

다른 문자열 알고리즘들처럼 알고 있는 정보를 활용하여 시간복잡도를 줄일 것이다.

> 바로 전 포스팅에서 다룬 [Z algorithm](https://damo1924.github.io/algorithm/Zalgorithm/)과 상당히 비슷하다.

<br/>

## 2. Manacher's Algorithm

주어진 문자열을 변형시켜 얻은 새로운 문자열을 $S$, 그 길이를 $N$이라고 하자.

어떤 $i$에 대하여, $A\[0\], A\[1\], \dots, A\[i-1\]$ 를 구한 상황에서 $A\[i\]$를 구할 것이다.

$0 \leq j < i$ 인 모든 $j$에 대하여 $j + A\[j\]$ 의 최댓값을 $r$, 최댓값에 대응되는 $j$를 $p$라고 하자.

\begin{aligned}
r = p + A\[p\]
\end{aligned}

$i$와 $r$의 대소 관계에 따라서 두 가지 케이스로 나누어서 구해준다.

1. $r < i$
2. $i \leq r$

1번의 경우에는 이전에 구한 값들로부터 얻을 수 있는 정보가 없기 때문에 $S\[i - 1\]$과 $S\[i+1\]$부터 차례대로 비교해나가며 $A\[i\]$를 구해준다.

2번의 경우에는 $S\[i\]$가 $S\[p\]$를 중심으로 하는 펠린드롬에 속한다는 것을 이용할 수 있다.

펠린드롬에서 $i$의 대칭점 $2p - i$에 대하여 $A\[i\]$는 최소 $\min(r-i, A\[2p-i\])$ 임을 알 수 있다.

<center><img src="https://user-images.githubusercontent.com/88201512/176627249-d5e83b7d-5118-4ce4-9b92-1cbdc5642434.jpg" width="70%" height="70%"></center>

마찬가지로 그 다음부터 양 끝 문자끼리 차례대로 비교해나가며 $A\[i\]$를 구해주면 된다.

<br/>

## 3. Implementation

주어진 문자열의 A 배열을 구하는 코드이다.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int a[200010];
void manacher(string &s) {
    int n = s.size(), r = 0, p = 0;
    for (int i = 1; i < n; i++) {
        if (r < i) a[i] = 0;
        else a[i] = min(a[2 * p - i], r - i);
        
        a[i]++;
        while (s[i - a[i]] == s[i + a[i]]) a[i]++;
        a[i]--;
        
        if (r < i + a[i]) r = i + a[i], p = i;
    }
}
```

위 코드는 새로운 문자열을 만들 때, 양 끝에 서로 다른 문자를 추가했을 때의 코드이다.

그렇게 하지 않으면 아래와 같이 while문을 수정해야한다.

```cpp
while (0 <= i - a[i] && i + a[i] < n && s[i - a[i]] == s[i + a[i]]) a[i]++;
```

<br/>

## 4. Related Problems

### [BOJ] 13275. 가장 긴 펠린드롬 부분 문자열

[BOJ 13275. 가장 긴 펠린드롬 부분 문자열 문제 링크](https://www.acmicpc.net/problem/13275)

말 그대로 주어진 문자열의 **가장 긴 펠린드롬**의 길이를 구하는 문제이다.

앞에서 설명한 것처럼 문자 사이사이에 문자열에 포함되지 않은 어떤 문자를 삽입하여 새로운 문자열을 만드는데,

좀 더 간편하게 답을 구하기 위해 아래와 같이 새로운 문자열을 만들어주었다.

```cpp
string s, t = "!#"; cin >> s;
int n = s.size();
for (int i = 0; i < n; i++) {
    t += s[i];
    t += "#";
}
t += "?";
```

이제 문자열 $t$에 대하여 $A$ 배열을 구하고, 배열의 최댓값이 가장 긴 펠린드롬의 길이가 된다.

<br/>

## References

[1] 

