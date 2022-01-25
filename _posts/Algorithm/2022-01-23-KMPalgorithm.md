---
title: "KMP Algorithm"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` 문자열 검색 알고리즘, failure function, 1786 찾기, 4354 문자열 제곱, 1305 광고

## 0. String Searching Algorithm

문자열 검색 알고리즘은 **어떤 문자열 안에 다른 문자열이 포함되어 있는지 탐색**하고, 만약 포함되어 있다면 그 위치까지 찾는 알고리즘이다.

이때 검색되는 쪽의 문자열을 **텍스트(text)**, 찾고자 하는 문자열을 **패턴(pattern)**이라고 한다.

즉, 문자열 탐색 알고리즘은 텍스트에서 패턴을 찾아내는 것이라고 할 수 있다.

가장 단순한 방법은 아래와 같이 브루트 포스(brute force)법으로 검색을 하는 것이다.

<center><img src="https://user-images.githubusercontent.com/88201512/150712279-9144c34e-fdb6-4f95-978e-920b2e141e2d.jpg" width="60%" height="60%"></center>

그림의 `i`와 `j`는 비교하고 있는 텍스트와 패턴의 인덱스를 의미한다.

텍스트의 길이를 $N$, 패턴의 길이를 $M$이라고 하면, 시간복잡도는 $O(NM)$이다.

이번 포스팅에서는 좀 더 효율적으로 문자열을 검색할 수 있는 KMP 알고리즘에 대해 다루어 볼 것이다.

<br/>

## 1. KMP Algorithm

KMP 알고리즘은 텍스트와 패턴의 겹치는 문자열을 이용해서 불필요한 탐색을 줄이는 알고리즘이다.

> KMP는 이를 고안한 D. E. Knuth, J. H. Morris, V. R. Pratt의 이름에서 따온 것이다.

### 1-1. IDEA

아래 예시를 보자.

<center><img src="https://user-images.githubusercontent.com/88201512/150723218-2dc3c693-cf7f-45eb-bd52-e5159d332f02.jpg" width="60%" height="60%"></center>

브루트 포스법에서는 탐색에 실패하면 패턴의 첫 번째 글자부터 다시 비교하였었다.

그러나 KMP 알고리즘은 지금까지 탐색한 패턴(ABCA)의 앞과 뒤에 겹치는 부분(A)가 있다는 정보를 토대로, 불필요한 중간 단계를 건너뛰고 탐색을 진행한다.

텍스트의 네 번째 글자 A부터 시작하는 문자열과 패턴을 비교해야하는데, 이미 첫 번째 글자인 A가 겹친다는 사실을 알고 있으므로 그 다음 글자부터 탐색하면 된다.

다른 예시를 보자.

<center><img src="https://user-images.githubusercontent.com/88201512/150717491-13de56f9-4274-4b1b-bd70-a98dc3a3716f.jpg" width="50%" height="50%"></center>

이번에는 지금까지 탐색한 패턴(AB)의 앞과 뒤에 겹치는 부분이 없으므로 패턴의 첫 번째 글자부터 탐색해야한다.

그 대신, 텍스트의 두 번째 글자(B)부터 시작하는 문자열(BCA)과 세 번째 글자 (C)부터 시작하는 문자열(CAB)에 대해서는 굳이 탐색할 필요가 없다.

그러므로 텍스트의 다음 글자인 A와 패턴의 첫 번째 글자부터 비교를 이어나가면 된다.

---

### 1-2. Algorithm

위 내용을 명료하게 정리하기 위해서 다음과 같은 용어들을 사용할 것이다.

> **접두사(prefix)** & **접미사(suffix)**
> 
> `ABC`의 접두사는 `A`, `AB`, `ABC`이고 접미사는 `C`, `BC`, `ABC`이다.

탐색한 패턴의 앞과 뒤에 겹치는 부분에 대한 정보를 저장하는 배열 `pi`를 정의하자.

> `pi[j]` = 패턴에서 인덱스 0~j에 해당하는 부분 문자열에 대해 다음 조건을 만족하는 접두사 중 가장 긴 것의 길이
> 
> - **접두사와 접미사가 동일**
> - **접두사가 해당 부분 문자열과 동일하지 않다.**
> 
> 이를 KMP 알고리즘의 **failure function**이라고 부른다.

이 배열을 이용하면 탐색 과정에서 다른 부분이 발견되었을 때, **패턴의 몇 번째 글자부터 다시 탐색해야 하는지**를 바로 알 수 있게 된다.

KMP 알고리즘은 다음과 같다.

**1.** 비교할 텍스트의 인덱스를 `i`, 패턴의 인덱스를 `j`라고 하자.  
**2.** `i`를 1씩 증가시키면서 다음 과정을 반복한다.  
    **2-1.** `text[i] == pattern[j]`이면 `j++`  
    **2-2.** `text[i] != pattern[j]`이면 `j = pi[j - 1]`로 바꾸고 2-1로 돌아간다.
  
즉, `pi`배열을 구했다면 $O(N)$의 시간복잡도로 탐색이 가능하다는 것을 알 수 있다.

재미있는 점은 위 과정과 비슷하게 `pi`배열마저 $O(M)$으로 구할 수 있다는 것이다.

**1.** 비교할 패턴의 인덱스를 `i`, 접두사의 바로 다음 글자에 해당하는 인덱스를 `j`라고 하자.  
**2.** `i`를 1씩 증가시키면서 다음 과정을 반복한다.  
    **2-1.** `pattern[i] == pattern[j]`이면 `pi[i] = ++j`  
    **2-2.** `pattern[i] != pattern[j]`이면 `j = pi[j - 1]`으로 바꾸고 2-1로 돌아간다.
  
따라서 전체 알고리즘의 시간복잡도는 $O(N + M)$이다.
  
---

### 1-3. Implementation: [백준] 1786. 찾기

이제 직접 KMP 알고리즘을 구현해보도록 하자.

[백준 1786. 찾기 문제 링크](https://www.acmicpc.net/problem/1786)

길이가 1 이상 100만 이하인 두 문자열 T, P가 주어질 때 P가 T의 몇 번째 글자에 나타나는지 구하는 문제이다.

`pi`배열을 구하는 `getPi()` 함수와 겹치는 부분을 구하는 `KMP()` 함수를 구현하여 해결하였다.

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int N, M;

string T, P;

int pi[1000000];

vector<int> matched;

void getPi()
{
    int j = 0;
    for (int i = 1; i < M; i++)
    {
        while (j > 0 && P[i] != P[j]) j = pi[j - 1];
        if (P[i] == P[j]) pi[i] = ++j;
    }
}

void KMP()
{
    getPi();
    int j = 0;
    for (int i = 0; i < N; i++)
    {
        while (j > 0 && T[i] != P[j]) j = pi[j - 1];
        if (T[i] == P[j])
        {
            if (j == M - 1)
            {
                matched.push_back(i - M + 2);
                j = pi[j];
            }
            else j++;
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    getline(cin, T);
    getline(cin, P);
    N = T.size();
    M = P.size();
    
    KMP();
    cout << matched.size() << "\n";
    for (int i = 0; i < matched.size(); i++) cout << matched[i] << " ";
}
```

<br/>

## 2. Failure Function 관련 문제들

Failure function을 이용하면 문자열 검색 외에도 문자열의 규칙을 찾는 문제들을 해결할 수 있다.

### [백준] 4354. 문자열 제곱

[백준 4353 문자열 제곱 문제 링크](https://www.acmicpc.net/problem/4354)

두 문자열 사이의 곱셈의 결과를 두 문자열을 이어붙이는 것으로 정의하면, 문자열의 제곱은 다음과 같이 정의된다.

- $a^0$ = (빈 문자열)
- $a^{n + 1} = a \times a^n$

즉, 문자열 $a$에 대해 $a^n$은 $a$를 $n$번 이어붙인 문자열이다.

입력으로 문자열 S가 주어질 때, 어떤 문자열 $a$에 대해 $S = a^n$을 만족하는 $n$의 최댓값을 구하는 문제이다.

**[Solution]**

반복되는 문자열로 표현이 불가능한 어떤 문자열 $a$에 대해, 문자열 $a^n$의 failure function을 떠올려보자.

$a^n$의 접두사와 접미사가 같은 접두사 중 $a^n$이 아니면서 가장 길이가 긴 것은 $a^{n-1}$이다.

따라서 어떤 문자열이 $a^n$으로 표현된다면, $a$의 길이를 failure function을 통해 구할 수 있다는 것을 알 수 있다.

주어진 문자열을 $S$, $S$의 길이를 $N$, failiure function을 $pi(k)$($0 \leq k < N$)이라고 하자.

$S$가 어떤 문자열 $a$에 대해 $a^n$($n \neq 1$)로 표현된다면, $n$의 최댓값 $n_m$은 다음과 같이 구할 수 있다.

\begin{aligned}
n_m = \frac{N}{N - pi(N - 1)}
\end{aligned}

> ***proof.***
> 
> $S$가 어떤 문자열 $a$에 대해 $a^n$으로 표현된다면 $n$은 다음과 같이 구할 수 있다.
> 
> \begin{aligned}
> n = \frac{N}{N - L}
> \end{aligned}
> 
> 이때 $L$은 문자열 $a^{N-1}$의 길이이다.
> 
> Failure function의 정의에 의해 $L$의 최댓값은 $pi(N-1)$이다.
> 
> $\therefore$ $n$의 최댓값은 failure function을 통해 구할 수 있다.

만약 $S$가 **규칙이 없는 문자열**이라면 위 값은 자연수가 아니라 유리수 값을 가지게 된다.

전체 코드는 다음과 같다.

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int solve(string& s)
{
    int n = s.size(), j = 0;
    vector<int> pi(n, 0);
    for (int i = 1; i < n; i++)
    {
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) pi[i] = ++j;
    }
    
    int a = n - pi[n - 1];
    if (n % a == 0) return n / a;
    else return 1;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    while (true)
    {
        string S;
        getline(cin, S);
        if (S == ".") break;
        cout << solve(S) << "\n";
    }
}
```

---

### [백준] 1305. 광고

[백준 1305. 광고 문제 링크](https://www.acmicpc.net/problem/1305)

크기가 $L$인 광고판에 길이 $N$인 문구를 무한히 이어붙여 띄우고 있다.

1초가 지날 때마다 광고 문구가 한 칸씩 옆으로 이동한다.

어느 순간 광고판을 바라보았을 때의 상태가 입력으로 주어졌을 때, 가능한 광고 문구의 길이 $N$의 최솟값을 구하는 문제이다.

**[Solution]**

이 문제를 풀기 위해 고려해야하는 조건이 두 가지가 있다.

1. 광고판의 시작과 끝 부분에는 길이 $N$인 광고 문구가 중간에 짤린 채로 나타날 수 있다.
2. 시간이 지남에 따라 광고판에 나타나는 문구가 달라진다.

먼저, 두 번째 조건부터 살펴보자.

> **광고판을 본 시점이 결과(길이의 최솟값)에 영향을 줄까?**

길이가 $N$인 광고 문구를 $a_1a_2 \dots a_N$라고 하면, 시간이 $T$($0 < T < N$)만큼 지났을 때의 광고판은 다음과 같다.

\begin{aligned}
a_{T+1} \dots a_N / a_1 \dots a_N / a_1 \dots a_N / \dots
\end{aligned}

위 광고판은 다음과 같이 생각할 수도 있다.

\begin{aligned}
a_{T+1} \dots a_N a_1 \dots a_T / a_{T + 1} \dots a_N a_1 \dots a_T / \dots
\end{aligned}

따라서 광고판을 본 시점은 결과에 영향을 미치지 않는다는 것을 알 수 있다.

이를 통해 첫 번째 조건도 간단하게 바꿀 수 있다.

광고판을 본 시점이 의미가 없다는 것은 **광고판에 나타난 문구 중 처음 N 글자를 광고 문자**로 생각해도 된다는 의미이다.

그러므로 광고판의 끝 부분에만 `L % N`만큼의 짤린 광고 문구가 나타난 것으로 생각해도 된다.

아래 그림을 보자.

<center><img src="" width="60%" height="60%"></center>

입력된 광고판의 상태에 대해 **failure function**을 구하면 광고 문구의 길이 $N$의 최솟값을 구할 수 있음을 알 수 있다.

전체 코드는 다음과 같다.

```cpp
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int solve(int l, string& s)
{
    int j = 0;
    vector<int> pi(l, 0);
    for (int i = 1; i < l; i++)
    {
        while (j > 0 && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) pi[i] = ++j;
    }
    return l - pi[l - 1];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    int L; // 광고판의 크기
    string S; // 광고판에 나타난 문구
    cin >> L;
    cin.ignore(10, '\n');
    getline(cin, S);
    
    cout << solve(L, S);
}
```

<br/>

## Reference

[1] [WIKIPEDIA, 'Knuth-Morris-Pratt algorithm'](https://en.m.wikipedia.org/wiki/Knuth%E2%80%93Morris%E2%80%93Pratt_algorithm)  
[2] 이지스 퍼블리싱, Bohyoh Shibata, '자료구조와 함께 배우는 알고리즘 입문'  



