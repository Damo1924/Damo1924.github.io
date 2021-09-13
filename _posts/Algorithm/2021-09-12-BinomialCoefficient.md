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
$\binom{n}{r} = \binom{n-1}{r} + \binom{n-1}{r-1}
\end{align\*}

**-proof 1 (수학적 귀납법)**

1) $r = 1$인 경우

$\binom{n}{1} = n$, $\binom{n-1}{1} + \binom{n-1}{0} = (n-1) + 1 = n$이므로 성립한다.

2) $r = k$일 때 성립한다고 가정하자.

\begin{align\*}
\binom{n-1}{k+1} + \binom{n-1}{k} &= \frac{(n-1)!}{(k+1)!(n-k-2)!} + \frac{(n-1)!}{k!(n-k-1)!} \\\\  
&= (n-1)!\times\left(\frac{n-k-1}{(k+1)!(n-k-1)!} + \frac{k+1}{(k+1)!(n-k-1)!}\right) \\\\  
&= \frac{n!}{(k+1)!(n-k-1)!} \\\\  
&= \binom{n}{k+1}
\end{align\*}

$\therefore$ 1), 2)로부터 수학적 귀납법에 의해 $\binom{n}{r} = \binom{n-1}{r} + \binom{n-1}{r-1}$가 성립한다. **Q.E.D**

