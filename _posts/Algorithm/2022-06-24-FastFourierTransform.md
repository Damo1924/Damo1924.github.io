---
title: "Fast Fourier Transform Algorithm"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` Cooley-Tukey, 

<br/>

## 1. Fourier Transform


<br/>

## 2. Cooley-Tukey Algorithm

쿨리-튜키 알고리즘은 **분할 정복**을 이용하는 방법으로, 대표적인 FFT 알고리즘 중 하나이다.

$n-1$차 다항식

\begin{aligned}
f(x) = a_{n-1}x^{n-1} + a_{n-2}x^{n-2} + \dots + a_2x^2 + a_1x + a_0
\end{aligned}

에 대하여, 두 다항식

\begin{aligned}
f_{even}(x) = a_{2 \lfloor (n-1)/2 \rfloor} x^{\lfloor (n-1)/2 \rfloor} + \dots + a_4 x^2 + a_2 x + a_0 = \sum_{i=0}^{\lfloor (n-1)/2 \rfloor} a_{2i} x^i
\end{aligned}

\begin{aligned}
f_{odd}(x) = a_{2 \lfloor (n-2)/2 \rfloor + 1} x^{\lfloor (n-2)/2 \rfloor} + \dots + a_5 x^2 + a_3 x + a_1 = \sum_{i=0}^{\lfloor (n-2)/2 \rfloor} a_{2i+1} x^i
\end{aligned}

을 정의하면, 다음이 성립한다.

\begin{aligned}
f(x) = f_{even} \left( x^2 \right) + x \cdot f_{odd} \left( x^2 \right)
\end{aligned}

어떤 $w$에 대하여,

\begin{aligned}
f(w) = f_{even} \left( w^2 \right) + w \cdot f_{odd} \left( w^2 \right)
\end{aligned}

\begin{aligned}
f(-w) = f_{even} \left( w^2 \right) - w \cdot f_{odd} \left( w^2 \right)
\end{aligned}

이므로, $f_{even} \left( w^2 \right)$ 과 $f_{odd} \left( w^2 \right)$ 의 값을 알고 있다면 $O(1)$로 $f(w)$ 와 $f(-w)$ 을 구할 수 있다.

이를 분할정복으로 구현하면

- 총 $O(\log n)$의 단계를 거치게 되고
- 각 단계에서 $f_{even}$ 과 $f_{odd}$ 의 값을 계산하는데 $O(n)$

이므로 전체 시간복잡도는 $O(n \log n)$ 이 된다.




