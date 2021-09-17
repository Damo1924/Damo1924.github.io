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


<br/>
## 2. Extended Euclidean Algorithm

확장 유클리드 호제법은 유클리드 호제법을 확장시켜 부정방정식의 해를 구하는 알고리즘을 의미한다.

두 정수 $a, b$에 대해 $g = \gcd(a, b)$라고 할 때, 베주 항등식(Bezout's Identity)의 명제에 의해 다음 방정식을 만족시키는 정수해 $(x, y)$는 항상 존재한다.

\begin{align\*}
ax + by = g
\end{align\*}

위 방정식의 정수해 $(x, y)$를 구하는 방법의 핵심 아이디어는 유클리드 호제법을 이용하는 것이다.

---

**[방법 1]**

두 정수 $a, b$에 대해 유클리드 호제법을 반복하는 과정은 다음과 같다.

\begin{align\*}
a &= bq_0 + r_2 \\\\  
b &= r_2 q_1 + r_3 \\\\  
r_2 &= r_3 q_2 + r_4 \\\\  
\dots \\\\  
r_{i-1} &= r_i q_{i-1} + r_{i+1} \\\\  
\dots \\\\  
r_{n-1} &= r_n q_{n-1} + r_{n+1}
\end{align\*}

유클리드 호제법은 $r_{n+1} = 0$이 되는 순간 종료되며, 이때 $r_n = gcd(a, b) = g$가 성립한다.

즉, $ax + by = g$의 해를 구하는 것은 $r_n$을 $a$와 $b$의 선형결합으로 표현하는 것과 동일하다.

그러므로, $r_i$를 다음과 같이 표현하자.

\begin{align\*}
r_i = s_i a + t_i b
\end{align\*}

이때, $r_{i+1} = r_{i-1} - r_i q_{i-1}$으로부터

\begin{align\*}
s_{i+1}a + t_{i+1}b &= (s_{i-1}a + t_{i-1}b) - (s_i a + t_i b) q_{i-1} \\\\  
&= (s_{i-1} - s_i q_{i-1})a + (t_{i-1} - t_i q_{i-1})b
\end{align\*}

을 얻을 수 있고, 다음 점화식을 얻을 수 있다.

\begin{align\*}
s_{i+1} = s_{i-1} - s_i q_{i-1}, t_{i+1} = t_{i-1} - t_i q_{i-1}, q_{i} = \left[ \frac{r_i}{r_{i+1}} \right]
\end{align\*}

$r_i, s_i, t_i$의 초기값은 다음과 같다.

\begin{align\*}
a = r_0 = 1 \times a + 0 \times b, s_0 = 1, t_0 = 0
\end{align\*}

\begin{align\*}
b = r_1 = 0 \times a + 1 \times b, s_1 = 0, t_1 = 1
\end{align\*}

만약 $ax + by = c$이고 $c$가 $gcd(a, b)$의 배수이면 위의 방법으로 구한 $s, t$에 적절한 정수를 곱해줌으로써 해를 얻을 수 있다.

방법 1을 통해 확장 유클리드 호제법을 구현한 코드는 다음과 같다.

```cpp
int solve (int a, int b, int &s, int &t)
{
    int r1 = a, s1 = 1, t1 = 0;
    int r2 = b, s2 = 0, t2 = 1;
    
    int tmp;
    while (r2)
    {
        tmp = s2;
        s2 = s1 - (a / b) * s2;
        s1 = tmp;
        
        tmp = t2;
        t2 = t1 - (a / b) * t2;
        t1 = tmp;
        
        tmp = r2;
        r2 = r1 % r2;
        r1 = tmp;
    }
    
    s = s2, t = t2;
    return r1;
}
```

---

**[방법 2]**

이 방법은 유클리드 호제법을 거꾸로 따라가면서 $s, t$를 구하는 방법이다.

방법 1은 각 $r_i$를 $a, b$로 표현하였다면, 이번에는 다음과 같이 표현할 것이다.

\begin{align\*}
s_i a_i + t_i b_i = \gcd(a_i, b_i) = G
\end{align\*}

이때 $a_i, b_i$는 유클리드 호제법을 거꾸로 따라갔을 때 나오는 숫자들로, $\gcd(a_i, b_i)$는 모두 같은 값을 갖는다.

\begin{align\*}
a_{i+1} &= k_{i+1} a_i + b_i \\\\  
b_{i+1} &= a_i
\end{align\*}

이를 이용해서 점화식을 풀면 다음과 같다.

\begin{align\*}
s_i a_i + t_i b_i &= G \\\\  
&= s_{i+1} a_{i+1} + t_{i+1} b_{i+1} \\\\  
&= s_{i+1} (k_{i+1} a_i + b_i) + t_{i+1} a_i \\\\  
&= (s_{i+1} k_{i+1} + t_{i+1}) a_i + s_{i+1} b_i
\end{align\*}

\begin{align\*}
\therefore s_{i+1} k_{i+1} + t_{i+1} = s_i, s_{i+1} = t_i
\end{align\*}

이를 정리하면 다음을 얻을 수 있다.

\begin{align\*}
t_{i+1} = s_i - s_{i+1} k_{i+1} = s_i - k_{i+1} t_i, s_{i+1} = t_i
\end{align\*}

이때 $a_{i+1} = k_{i+1} a_i + b_i$이므로, $k_{i+1} = \left[ \frac{a_{i+1}}{a_i} \right]$이다.

초기값은 유클리드 호제법이 종료되는 시점인 $b_0 = 0$일 때이므로 다음과 같다.

\begin{align\*}
a_0 = G, b_0 = 0, s_0 = 1, t_0 = 0
\end{align\*}

이는 재귀함수로 다음과 같이 구현할 수 있다.

```cpp
int solve (int a, int b, int& s, int& t)
{
    if (b == 0)
    {
        s = 1;
        t = 0;
        return a;
    }
    
    int gcd = solve(b, a%b, s, t);
    int temp = t;

    t = s - (a / b) * t;
    s = temp;

    return gcd;
}
```

---


<br/>
## 3. Modular Multiplicative Inverse

모듈러 연산의 곱셈의 역원을 구하는 것은 확장 유클리드 호제법을 이용하는 대표적인 케이스이다.

\begin{align\*}
ax \equiv 1 \pmod n
\end{align\*}

위 합동식을 만족하는 $x$를 찾는 것은 다음 방정식의 정수해 $(x, y)$를 구하는 것과 동일하다.

\begin{align\*}
ax + ny = 1
\end{align\*}

만약 $\gcd(a, n)$이 1이 아니라면 위 방정식이 정수해를 갖지 않으므로 역원도 존재하지 않는다.

$\gcd(a, n) = 1$이면 방정식의 정수해가 존재하고, 그러므로 확장 유클리드 호제법을 통해 역원을 찾을 수 있다.


