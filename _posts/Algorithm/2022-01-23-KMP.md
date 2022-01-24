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

`Tags` 문자열 검색 알고리즘

## 0. String Searching Algorithm

문자열 검색 알고리즘은 **어떤 문자열 안에 다른 문자열이 포함되어 있는지 탐색**하고, 만약 포함되어 있다면 그 위치까지 찾는 알고리즘이다.

이때 검색되는 쪽의 문자열을 **텍스트(text)**, 찾고자 하는 문자열을 **패턴(pattern)**이라고 한다.

즉, 문자열 탐색 알고리즘은 텍스트에서 패턴을 찾아내는 것이라고 할 수 있다.

가장 단순한 방법은 아래와 같이 브루트 포스(brute force)법으로 검색을 하는 것이다.

<center><img src="https://user-images.githubusercontent.com/88201512/150712279-9144c34e-fdb6-4f95-978e-920b2e141e2d.jpg" width="60%" height="60%"></center>

그림의 `i`와 `j`는 비교하고 있는 텍스트와 패턴의 인덱스를 의미한다.

텍스트의 길이를 $N$, 패턴의 길이를 $M$이라고 하면, 시간복잡도는 $O(NM)$이다.

이번 포스팅에서는 좀 더 효율적으로 문자열을 검색할 수 있는 알고리즘들에 대해 다루어 볼 것이다.

<br/>

## 1. KMP Algorithm

KMP 알고리즘은 텍스트와 패턴의 겹치는 문자열을 이용해서 불필요한 탐색을 줄이는 알고리즘이다.

> KMP는 이를 고안한 D. E. Knuth, J. H. Morris, V. R. Pratt의 이름에서 따온 것이다.

아래 예시를 보자.

<center><img src="https://user-images.githubusercontent.com/88201512/150712462-13bde7ea-32e6-453b-a6e9-b1ab29e169f7.jpg" width="60%" height="60%"></center>

브루트 포스법에서는 탐색에 실패하면 패턴의 첫 번째 글자부터 다시 비교하였었다.

그러나 KMP 알고리즘은 지금까지 탐색한 텍스트(ABCAB)의 앞과 뒤에 겹치는 부분(AB)가 있다는 정보를 토대로, 중간 단계를 건너뛰고 AB로 시작하는 텍스트와 패턴을 비교하게 된다.

이때 텍스트와 패턴의 첫 두 글자가 AB로 동일하다는 사실을 알고 있으므로 세 번째 글자부터 탐색하면 된다.

다른 예시를 보자.

<center><img src="" width="60%" height="60%"></center>

이번에는 탐색한 텍스트의 앞과 뒤에 겹치는 부분이 없다.







## Reference





