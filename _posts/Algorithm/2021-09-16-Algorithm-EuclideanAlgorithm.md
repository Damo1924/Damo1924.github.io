---
title: "유클리드 호제법 & 확장 유클리드 호제법"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

## 1. Euclidean Algorithm

유클리드 호제법은 두 자연수의 최대공약수를 구하는 알고리즘이다.

자연수 $a, b$가 주어질 때, 최대공약수 $\gcd(a, b)$는 다음과 같이 구할 수 있다.

\begin{align\*}
gcd(a, b) = gcd(b, r)
\end{align\*}

이때 $r$은 $a$를 $b$로 나눈 나머지이며, 증명과정은 다음과 같다.

---

**[proof]**

$a$를 $b$로 나눈 몫을 $q$, 나머지를 $r$이라고 하자.

\begin{align\*}
a = bq + r
\end{align\*}

$gcd(a, b) = G$라고 하면 $G \mid a, G \mid b$를 만족하고, $r = a - bq$이므로 $G \mid r$이 성립한다.

$r$이 $G$로 나누어떨어지므로, 어떤 자연수 $R$에 대해 다음과 같이 쓸 수 있다.

\begin{align}
gcd(b, r) = RG
\end{align}

반대로 $gcd(b, r) = g$라고 하면 $g \mid b, G \mid r$를 만족하고, $a = bq + r$이므로 $g \mid a$이 성립한다.

마찬가지로 $a$는 $b, r$의 최대공약수로 나누어떨어지므로, 어떤 자연수 $A$에 대해 다음과 같이 쓸 수 있다.

\begin{align}
gcd(a, b) = Ag
\end{align}

식 (1)에 식 (2)를 대입하면 다음을 얻을 수 있다.

\begin{align\*}
gcd(b, r) = RG = R \times gcd(a, b) = R \times A \times g = AR \times gcd(b, r)
\end{align\*}

즉, $AR = 1$이 성립함을 알 수 있다.

그런데 이때 $A, R$은 모두 자연수이므로 $A = R = 1$이 되고, 이를 식 (1)에 대입하면 $gcd(a, b) = gcd(b, r)$이 된다.

**Q.E.D**

---

이 유클리드 호제법을 이용하면 두 자연수 $a, b(a > b)$의 최대공약수를 $O(\log a)$ 정도의 시간복잡도로 구할 수 있다.

그 이유는 $a = bq + r$에서 $0 \leq r \leq b$이기 때문에 $2r < r + b \leq a$가 성립하기 때문이다.

이를 코드로 구현하는 것도 매우 간단하다.

```cpp
int GCD (int a, int b)
{
    return (a % b) ? GCD(b, a%b) : b;
}
```

$a$가 $b$로 나누어떨어질 때까지 반복해서 유클리드 호제법을 적용하는 재귀함수로 구현할 수 있다.

## 2. Extended Euclidean Algorithm

확장 유클리드 호제법은 유클리드 호제법을 확장시켜 정수해를 갖는 부정방정식의 해를 구하는 알고리즘을 의미한다.

