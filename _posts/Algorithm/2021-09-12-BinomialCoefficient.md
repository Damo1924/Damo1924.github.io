---
title: "Various Algorithms to Calculate Binomial Coefficients"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

# 1. Binomial Coefficients
이항 계수(binomial coefficient)는 $(a + b)^{n}$을 전개하였을 때 $a^{r} b^{n-r} (0 \leq r \leq n)$의 계수를 의미하며, 다음과 같이 구할 수 있다.

\begin{align\*}
$\binom{n}{r} = \frac{n!}{r!(n-r)!}$
\end{align\*}

위 공식은 수학적 귀납법이나 조합을 이용해서 증명할 수 있다.


<br/>
# 2. Pascal Triangle
프랑스의 수학자 파스칼이 이항 계수를 계산하기 위해 13살 때 사용했다고 해서 이름 붙여진 삼각형 형태의 배열이다.

<img src="https://user-images.githubusercontent.com/88201512/132992449-be0a3835-7100-4213-b41c-b0ccb849e8d7.PNG">

위 삼각형의 숫자들은 바로 윗 줄의 인접한 두 숫자를 더해서 얻어진다.

파스칼 삼각형의 k번째 줄은 $(a + b)^{k-1}$을 전개한 다항식의 각 항의 계수와 동일하다는 특징을 가지고 있는데, 이는 이항 계수의 대표적인 성질로부터 기인한다.

\begin{align\*}
\binom{n}{r} = \binom{n-1}{r} + \binom{n-1}{r-1}
\end{align\*}

**[proof 1]**

\begin{align\*}
\binom{n-1}{r} + \binom{n-1}{r-1} &= \frac{(n-1)!}{r!(n-r-1)!} + \frac{(n-1)!}{(r-1)!(n-r)!} \\\\  
&= (n-1)!\times\left(\frac{n-r}{r!(n-r)!} + \frac{r}{r!(n-r)!}\right) \\\\  
&= \frac{n!}{r!(n-r)!} \\\\  
&= \binom{n}{r}
\end{align\*}

**[proof 2]**

$(1+x)^{n+1} = (1+x)\times(1+x)^n$가 항등식임을 이용하자.

먼저 좌변의 경우,

\begin{align\*}
(1+x)^{n+1} = \dots + \binom{n+1}{r}x^r + \dots
\end{align\*}

과 같이 전개했을 때 $x^r$의 계수가 $\binom{n+1}{r}$이다.

우변의 경우,

\begin{align\*}
(1+x)\times(1+x)^n &= (1+x)\left(\dots + \binom{n}{r-1}x^{r-1} + \binom{n}{r}x^r + \dots\right) \\\\  
&= \dots + \left(\binom{n}{r-1} + \binom{n}{r}\right)x^r + \dots
\end{align\*}

이므로, 양변의 $x^r$의 계수가 동일하다는 점을 통해 증명이 완료된다.


<br/>
# 3. 파스칼의 소정리 & 오일러 정리

