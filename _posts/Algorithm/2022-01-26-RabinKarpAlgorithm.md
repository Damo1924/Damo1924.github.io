---
title: "Rabin-Karp Algorithm"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` 문자열 검색 알고리즘, 라빈-카프 알고리즘, 해시, hash, 정수론

## 1. Introduction

라빈-카프 알고리즘(Rabin-Karp algorithm)은 문자열을 빠르게 검색하기 위해 **해시(hash)**를 이용하는 알고리즘이다.

길이가 $n$인 어떤 문자열 $S$의 해시 값 $H$는 다음과 같이 구한다.

\begin{aligned}
H = S\[0\] \times 2^{n-1} + S\[1\] \times 2^{n-2} + \dots + S\[n-1\] \times 2^0
\end{aligned}

이때 문자열을 이루는 각 문자 $S\[i\]$의 자리에는 **아스키 코드**로 표현한 숫자가 들어가게 된다.

예를 들어 `"hello"`의 해시 값은 다음과 같다.

\begin{aligned}
H &= 104 \times 2^4 + 101 \times 2^3 + 108 \times 2^2 + 108 \times 2^1 + 111 \times 2^0 \\\\  
&= 3231
\end{aligned}

이렇게 구한 해시 값들을 비교해서 동일한 문자열을 찾는 알고리즘이다.

여기까지 보고 나면, 텍스트의 길이가 $N$, 패턴의 길이가 $M$일 때의 시간복잡도는 $O(NM)$이라고 생각할 수 있다.

> 찾으려는 문자열을 **패턴(pattern)**, 검색 대상을 **텍스트(text)**라고 부른다.

텍스트의 부분 문자열 중 길이가 $M$인 것들의 해시 값을 모두 구해서 비교해야하기 때문이다.

하지만, 아래 그림에서 알 수 있듯이 **각 부분 문자열에 대한 해시 값의 계산은 상수 시간**에 이루어진다.

<center><img src="https://user-images.githubusercontent.com/88201512/151127209-b13ffde3-c6ed-4865-b6b0-478d6d5afcb5.jpg" width="50%" height="50%"></center>

따라서 첫 번째 부분 문자열의 해시 값만 구하면, 나머지 문자열들의 해시 값은 빠르게 구할 수 있게 된다는 것을 알 수 있다.

이로 인해 **라빈-카프 알고리즘의 시간복잡도**는 $O(N + M)$이다.

<br/>

## 2. Limits

사실 위의 알고리즘은 매우 명확한 한계점 두 가지가 있다.

첫 번째 한계점은 **해시 충돌(hash collision)**이 발생할 수 있다는 점이다.

어떤 두 문자열의 해시 값이 다르면 당연히 다른 문자열이지만, 반대로 **해시 값이 같다고 해서 반드시 같은 문자열이라고는 말할 수 없다**.

만약 **해시 값이 동일한 문자열들에 대해서는 글자 하나하나를 비교**한다고 하면, **최악의 경우 시간복잡도**가 $O(NM)$이 된다.

> 텍스트와 패턴 모두 전부 같은 알파벳으로 이루어진 경우, 총 $(N - M + 1)M$번의 비교를 해야한다.

두 번째 한계점은 문자열의 길이가 길어지게되면 **해시 값이 매우 커진다**는 점이다.

패턴의 길이가 100 정도만 되어도 해시 값은 `long long`의 범위마저 초과한다.

그러므로 단순히 2의 거듭제곱을 곱해 더하는 것으로 해시 값을 정의하는 것으로는 의미있는 결과를 내기 어렵다.

<br/>

## 3. Improvement

### 3-1. Re-Definition

다음과 같이 해시 값을 재정의하자.

\begin{aligned}
H = S\[0\] \times a^{n-1} + S\[1\] \times a^{n-2} + \dots + S\[n-1\] \times a^0 \pmod{m}
\end{aligned}

적절한 $p$와 $a$($1 < a < p$)를 선택해야한다.

$p$는 **적당히 큰 소수**, $a$는 $p$의 **원시근**이면서 너무 작지 않은($> 200$) 수인 것이 좋다고 한다.

> **원시근(Primitive Roots)**
> 
> 소수 $p$와 $1 \leq a < p$인 임의의 정수 $a$에 대해 $a^0, a^1, \dots, a^{p-2}$을 $p$로 나눈 나머지가 모두 다르다면 $a$를 $p$의 원시근이라고 한다.

---

### 3-2. Why?

왜 위와 같이 해시 값을 정했는지 그 이유를 대충 유추해보자.

일단 길이가 100인 문자열조차 처리하지 못한다는 문제점을 해결하기 위해 **모듈러 연산**을 적용하였을 것이다.

모듈러 연산을 적용함으로써 값이 너무 커진다는 한계점을 해결하였지만, 이렇게 되면 **해시 충돌이 더 많이 발생**하게 된다.

해시 충돌을 최대한 줄이기 위해서 $p$를 소수로, $a$를 $p$의 원시근으로 설정한 것이다.

> $p$가 $10^9$ 정도의 소수이면 해시 값이 같을 때 99.90%로 같은 문자열이라고 한다.

해시 값은 마치 **문자열을** $a$**진법으로 표현**한 것이라고 생각할 수 있는데, **아스키코드의 범위가 126까지**이므로 $a$를 200보다 큰 정수로 정하면 모듈러 연산을 하기 전의 값이 겹칠 일은 없게 된다.

> 주로 $a = 302$, $p = 1000000007$을 사용한다고 한다.

<br/>

## 4. Implementation

직접 라빈-카프 알고리즘을 사용해서 문제를 풀어보자.

### [백준] 1786. 찾기

[백준 1786. 찾기 문제 링크](https://www.acmicpc.net/problem/1786)

문자열 T, P가 주어질 때, T에 P가 몇 번 나타나는지, 그리고 어느 위치에 나타나는지를 출력하는 문제이다.

**[Solution]**

$p = 1000000007$, $a = 302$로 라빈-카프 알고리즘을 구현하였다.

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;
typedef long long ll;
const int a = 302;
const int p = 1000000007;

// h : 문자열 s의 앞부분부터 길이 l만큼의 부분 문자열에 해시 값
// b : a^(l-1)을 p로 나눈 나머지
pair<int, int> _hash(string& s, int l)
{
    ll h = 0, b = 1;
    for (int i = l - 1; i > 0; i--)
    {
        h = (h + s[i] * b) % p;
        b = (b * a) % p;
    }
    h = (h + s[0] * b) % p;
    return make_pair(h, b);
}

vector<int> RabinKarp(string& T, string& P)
{
    int N = T.size(), M = P.size();
    
    ll H = _hash(P, M).first;
    
    pair<int, int> hb = _hash(T, M);
    ll h = hb.first, b = hb.second;
    
    vector<int> res;
    if (h == H) res.push_back(1);
    for (int i = 1; i <= N - M; i++)
    {
        h = ((h - T[i - 1] * b) * a + T[i + M - 1]) % p;
        if (h < 0) h += p;
        
        if (h == H) res.push_back(i + 1);
    }
    return res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    string T, P;
    getline(cin, T);
    getline(cin, P);
    
    vector<int> v = RabinKarp(T, P);
    cout << v.size() << "\n";
    for (int i = 0; i < v.size(); i++) cout << v[i] << " ";
}
```

입력될 수 있는 문자열의 최대 길이가 $10^6$이기 때문에 반례가 충분히 존재하겠지만, 테스트케이스에는 없는 듯 하다.

---

### [백준] 1605. 반복 부분문자열






<br/>

## Reference

[1] [BaaaaaaaarkingDog, '0x0E강-문자열(KMP, 라빈 카프)'](https://blog.encrypted.gg/857)  
[2] 

