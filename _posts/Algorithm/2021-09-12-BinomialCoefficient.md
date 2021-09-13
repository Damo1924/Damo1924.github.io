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
\binom{n}{r} = \frac{n!}{r!(n-r)!}
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
# 3. Fermat's little theorem & Euler's theorem

$p$가 소수이고, $a$가 정수일 때, 페르마의 소정리는 다음과 같다.

\begin{align\*}
a^p \equiv a \pmod{p}
\end{align\*}

위 합동식은 $p \mid a$일 때 자명하게 성립하며, $p \nmid a$이면 다음과 같이 쓸 수 있다.

\begin{align\*}
a^{p-1} \equiv 1 \pmod{p}
\end{align\*}

이 경우에 대한 증명은 다음과 같다.

**[proof 1]**

**Lemma 1.** $a$와 서로소인 소수 $p$에 대해 $a, 2a, 3a, \dots, (p-1)a$들을 $p$로 나누었을 때 나머지는 모두 다르다.

어떤 두 수 $i, j(0 < i < j < p)$가 존재해서 $ia$와 $ja$를 $p$로 나눈 나머지가 같다고 하자.

그러면 $(j-i)a$는 $p$로 나누어 떨어진다. 이때 $0 < j-i < p$이므로 $j-i$는 $p$의 배수가 아니다.

즉, 이는 $a$가 $p$와 서로소라는 가정에 모순이므로 귀류법에 의해 증명된다.

**Lemma 2.** $0 < i < p$인 $i$에 대해 $ia$는 $p$의 배수가 아니다.

$i$는 $p$의 배수가 아니므로 마찬가지로 $a$가 $p$와 서로소라는 가정에 모순이므로 참이다.

이제 페르마의 소정리를 증명하자.

집합 $A, B$를 다음과 같이 정의하자.

\begin{align\*}
A = \{x \mid x = ia, i \in B\} \\\\  
B = \{1, 2, \dots, p-1\}
\end{align\*}

Lemma 1에 의해 집합 $A, B$의 크기는 같다. 즉, 다음 합동식이 성립한다.

\begin{align\*}
a \times 2a \times 3a \times \dots \times (p-1)a \equiv 1 \times 2 \times \dots \times (p-1) \not\equiv \pmod{p}
\end{align\*}

양변을 $(p-1)!$을 나누면 다음을 얻는다.

\begin{align\*}
a^{p-1} \equiv 1 \pmod{p}
\end{align\*}

**[proof 2]**

수학적 귀납법을 이용하자.

1) $a = 0$인 경우

$0^p \equiv 0 \pmod{p}$이므로 성립한다.

2) $a = k$일 때 성립한다고 가정

이항정리에 의해 다음과 같이 쓸 수 있다.

\begin{align\*}
(k+1)^p = \displaystyle\sum_{i=0}^{p} \binom{p}{i} k^i
\end{align\*}

이때 $\binom{p}{i} = \frac{p!}{i!(p-i)!}$이고, $p$가 소수이므로 $1 \leq i \leq p-1$인 $i$에 대해서는 다음이 성립한다.

\begin{align\*}
\binom{p}{i} k^i \equiv 0 \pmod{p} \\\\  
(k+1)^p \equiv k^p + 1 \pmod{p}
\end{align\*}

$\therefore$ 1, 2로부터 수학적 귀납법에 의해 임의의 정수 $a$에 대해 $a^p \equiv a \pmod{p}$가 성립한다.


<br/>
다만, 페르마의 소정리는 모든 소수가 만족시키는 필요조건이지만, 충분조건은 아니다.

\begin{align\*}
a^{b-1} \equiv 1 \pmod{b}
\end{align\*}

위 합동식을 만족시키면서 소수가 아닌 숫자 $b$를 **카마이클 수(Carmichael number)**라고 부르며, 무한히 많이 존재한다고 한다.


<br/>
페르마의 소정리를 일반화한 것이 바로 **오일러 정리**이다.

임의의 정수 $a$와 $n$이 서로소일 때, 오일러 정리에 따라 다음이 성립한다.

\begin{align\*}
a^{\phi (n)} \equiv 1 \pmod{n}
\end{align\*}


<br/>
# 4. Algorithms to calculate Binomial Coefficients

이제 앞서 다룬 내용들을 이용해서 이항 계수를 빠르게 구하는 알고리즘들에 대해 알아보자.

## 4-1. Algorithm using Pascal triangle
