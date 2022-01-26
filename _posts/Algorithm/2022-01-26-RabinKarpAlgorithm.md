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
H &=& 104 \times 2^4 + 101 \times 2^3 + 108 \times 2^2 + 108 \times 2^1 + 111 \times 2^0 \\\\  
&=& 3231
\end{aligned}

이렇게 구한 해시 값들을 비교해서 동일한 문자열을 찾는 알고리즘이다.

여기까지 보고 나면, 텍스트의 길이가 $N$, 패턴의 길이가 $M$일 때의 시간복잡도는 $O(NM)$이라고 생각할 수 있다.

> 찾으려는 문자열을 **패턴(pattern)**, 검색 대상을 **텍스트(text)**라고 부른다.

텍스트의 부분 문자열 중 길이가 $M$인 것들의 해시 값을 모두 구해서 비교해야하기 때문이다.

하지만, 아래 그림에서 알 수 있듯이 **각 부분 문자열에 대한 해시 값의 계산은 상수 시간**에 이루어진다.

<center><img src="https://user-images.githubusercontent.com/88201512/151127209-b13ffde3-c6ed-4865-b6b0-478d6d5afcb5.jpg" width="60%" height="60%"></center>

따라서 첫 번째 부분 문자열의 해시 값만 구하면, 나머지 문자열들의 해시 값은 빠르게 구할 수 있게 된다는 것을 알 수 있다.

이로 인해 **라빈-카프 알고리즘의 시간복잡도**는 $O(N + M)$이다.

<br/>

## 2. Limits

사실 위의 알고리즘은 매우 명확한 한계점 두 가지가 있다.

어떤 두 문자열의 해시 값이 다르면 당연히 다른 문자열이지만, 반대로 **해시 값이 같다고 해서 반드시 같은 문자열이라고는 말할 수 없다**는 점이다.

이는 해시의 치명적인 문제인 **해시 충돌(hash collision)**이 발생할 수 있기 때문이다.




## 3. Improvement











