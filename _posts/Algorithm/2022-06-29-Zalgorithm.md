---
title: "Z algorithm"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:    
  - Algorithm
use_math: true
comments: true

---

`Tags` 문자열 알고리즘, Z array, 문자열 검색, 

## 1. Z array

문자열 $S$에 대하여 Z 배열의 원소 $Z\[i\]$ 은 다음과 같이 정의된다.

- $Z\[i\]$ : $S\[i\]$로 시작하는 부분문자열이면서 $S$의 접두사인 문자열들 중 길이가 가장 긴 것의 길이

<br/>

## 2. Z algorithm

Z 알고리즘은 Z 배열을 구하는 알고리즘이다.

문자열 $S$의 길이가 $N$이라고 하면, Z 알고리즘은 $O(N)$의 시간복잡도를 갖는다.

단순히 생각했을 때, $Z\[i\]$를 구하기 위해서는,

- $S\[0\]$과 $S\[i\]$를 비교
- $S\[1\]$과 $S\[i + 1\]$를 비교
- $\dots$
- $S\[k\]$과 $S\[i + k\]$를 비교
- $\dots$

위와 같은 과정을 두 문자가 같지 않을 때까지 반복해주면 된다.

이렇게 Z 배열을 구하면 $O(N^2)$이 걸리게 되는데, 다른 문자열 관련 알고리즘들과 마찬가지로 **이미 알고있는 정보**를 이용해서 시간을 단축할 것이다.

---

### 2-1. Algorithm

어떤 $i$에 대하여 $Z\[0\]$부터 $Z\[i-1\]$까지 구했을 때 $Z\[i\]$를 구해보자.

임의의 $j$에 대하여 다음을 정의하자.

- $S_j$ : $Z\[j\]$에 해당하는 부분문자열 ($S\[j\]$로 시작하는 부분문자열이면서 $S$의 접두사인 것들 중 길이가 가장 긴 것)
- $r_j$ : $S_j$의 오른쪽 끝 인덱스 ($Z\[j\] = r_j - j + 1$)
- $L, R$ : $r_0, \dots, r_j$ 중 가장 큰 것을 $r_k$라고 할 때, $R = r_k$, $L = k$

$Z\[i-1\]$까지 구했을 때 $L \leq i- 1 < i$ 이므로

1. $R < i$
2. $L < i \leq R$

와 같이 두 가지 케이스로 나누어서 생각할 수 있다.

**Case 1)** 이 경우에는 지금까지 구한 정보들을 이용할 수 없기 때문에 $S\[0\]$과 $S\[i\]$부터 차례대로 비교해나간다.

만약 $S_i$가 존재한다면 $L = i$, $R = r_i$ 로 갱신해준다.

반대로 $S_i$가 존재하지 않는다면 $L, R$을 갱신하지 않고, $Z\[i\] = 0$ 이 된다.

**Case 2)** 이 경우에는 지금까지 구한 정보를 이용해서 $Z\[i\]$를 빠르게 구할 수 있다.

<center><img src="https://user-images.githubusercontent.com/88201512/176568319-f71203b6-ef41-426f-92c5-cac42309ab29.jpg" width="70%" height="70%"></center>

왼쪽 끝 인덱스가 $l$, 오른쪽 끝 인덱스가 $r$인 부분문자열을 $S(l, r)$라고 할 때,

$S(L, R) = S(0, R - L)$ 이고 $S(i-L, R-L) = S(i, R)$ 이다.

따라서 $Z\[i\]$를 구하기 위해 $0 \leq j \leq R - i$ 인 $j$에 대하여 $S\[j\]$와 $S\[i + j\]$을 비교하는 것은 $S\[j\]$와 $S\[i-L+j\]$를 비교하는 것과 동일하다.

그런데 $S\[j\]$와 $S\[(i-L)+j\]$를 비교하는 것은 $Z\[i - L\]$을 구하면서 이미 수행한 과정이다.

그렇다면 다시 한 번 다음과 같이 경우를 나눌 수 있다.

- $Z\[i-L\] < R - i + 1$
- $R - i + 1 \leq Z\[i-L\]$

첫 번째 경우라면, 이미 두 문자가 서로 다른 위치를 알고 있기 때문에 추가로 비교할 필요 없이 $Z\[i\] = Z\[i-L\]$ 가 된다.

또한, $r_i = i + Z\[i\] - 1 \leq R$ 이므로 $L, R$은 갱신되지 않는다.

두 번째 경우라면, $Z\[i\]$는 최소 $R-i+1$ 라는 사실만 알 수 있다.

$Z\[i\]$의 정확한 값을 구하기 위해서는 $S\[R+1-i\]$와 $S\[R+1\]$부터 차례대로 비교해나가면 된다.

그렇게 $Z\[i\]$를 구한 후에 $L = i$, $R = i + Z\[i\] - 1$ 로 갱신해준다.

---

### 2-2. Time Complexity

Case 1에서는 자명히 $R$보다 큰 인덱스에 대해서만 비교한다.

또, Case 2에서는 $R$보다 작거나 같은 인덱스에 대한 비교 결과를 전에 구해두었던 $Z\[i - L\]$로부터 알 수 있기 때문에 마찬가지로 $R$보다 큰 인덱스에 대해서만 비교를 하게 된다.

즉, 마지막으로 비교했던 위치($R+1$)부터 다시 비교해나가며 $R$을 갱신해주기 때문에 알고리즘의 시간복잡도는 $O(N)$임을 알 수 있다.

---

### 2-3. Implementation

다음은 Z 배열을 구하는 코드이다.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int z[1000000];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    
    string s; cin >> s;
    int n = s.size();
    
    z[0] = n;
    int L = 0, R = 0;
    for (int i = 1; i < n; i++) {
        if (R < i) L = R = i;
        else if (z[i - L] < R - i + 1) {
            z[i] = z[i - L];
            continue;
        }
        else L = i;
        
        while (R < n && s[R - i] == s[R]) R++;
        R--;
        z[i] = R - L + 1;
    }
}
```

<br/>

## 3. String Search using Z algorithm

Z 알고리즘을 이용하면 텍스트 내에서 패턴을 빠르게 탐색할 수 있다.

텍스트 $T$와 패턴 $P$에 대하여 새로운 문자열 $S = P?T$ 를 만들자.

이때 $?$은 **텍스트와 패턴 모두에 포함되지 않는 임의의 문자**이다.

그렇다면 아래와 같이 텍스트 내의 패턴의 위치를 탐색할 수 있다.

- 새로운 문자열 $S$의 Z 배열을 구한다.
- 패턴의 길이를 $M$이라고 할 때, **$Z\[i\] = M$ 을 만족하는 $i$**들을 모두 찾는다.
- 위에서 찾은 $i$에서 $M + 1$을 빼주면 텍스트 내에서 패턴이 나타나는 위치가 된다.

텍스트와 패턴 사이에 집어넣은 임의의 문자로 인해 $Z\[i\]$의 값은 $M$을 넘지 못한다.

따라서 $Z\[i\] = M$ 인 $i$들은 $S$ 내의 패턴의 위치가 되고, 텍스트에서의 위치로 바꾸지 위해서는 $M+1$을 빼주어야한다.

KMP 알고리즘과 마찬가지로 $O(N + M)$의 시간복잡도로 문자열을 검색할 수 있음을 알 수 있다.

이때 $N$은 텍스트의 길이, $M$은 패턴의 길이이다.

<br/>

## 4. Finding Borders of a String

Z 알고리즘만의 특장점은 문자열의 **border**를 다른 알고리즘에 비해 쉽게 구할 수 있다는 것이다.

이때 문자열의 border란 해당 문자열보다 길이가 짧은 부분문자열들 중 **접두사(prefix)인 동시에 접미사(suffix)인 문자열**을 의미한다.

문자열 $S$의 접미사 $S\[i\]S\[i+1\] \dots S\[n-1\]$ 이 border가 되기 위한 필요충분조건은

\begin{aligned}
i + z\[i\] = n
\end{aligned}

이다.

<br/>

## 5. Related Problems

### [BOJ] 13713. 문자열과 쿼리

[BOJ 13713. 문자열과 쿼리 문제 링크](https://www.acmicpc.net/problem/13713)

주어진 문자열 $S$에 대하여 $S$와 $S\[1\] \dots S\[i\]$의 공통 접미사의 길이를 구하는 문제이다.

$S$를 뒤집어서 Z 배열을 구해줌으로써 해결할 수 있다.

---

### [BOJ] 16229. 반복 패턴

[BOJ 16229. 반복 패턴 문제 링크](https://www.acmicpc.net/problem/16229)

길이가 $N$인 주어진 문자열에 최대 $K$개의 글자를 뒤에 추가하여 패턴이 반복되는 형태로 만드는 문제이다.

길이가 $i$인 패턴이 존재한다면 $Z\[i\] = N - i$ 를 만족해야하고,

최대 $K$개의 글자를 추가할 수 있으므로 $i - (n%i) \leq k$ 를 만족해야한다.

이때 $n % i$ 는 $n$을 $i$로 나눈 나머지인데, $n$이 $i$로 나누어 떨어지는 경우에는 $i$이다.

---

### [BOJ] 13576. Prefix와 Suffix

[BOJ 13576. Prefix와 Suffix 문제 링크](https://www.acmicpc.net/problem/13576)

주어진 문자열의 **접두사(prefix)인 동시에 접미사(suffix)인 문자열**, 즉 문자열의 border를 구하는 문제이다.

<br/>

## References

[1] [Codeforces, paladin8's blog, 'Z Algorithm'](https://codeforces.com/blog/entry/3107)  
[2] [GeeksforGeeks, 'Z algorithm'](https://www.geeksforgeeks.org/z-algorithm-linear-time-pattern-searching-algorithm/)  
[3] [Algorithms a contest approach, 'Borders of a string'](http://algorithmsforcontests.blogspot.com/2012/08/borders-of-string.html)  


