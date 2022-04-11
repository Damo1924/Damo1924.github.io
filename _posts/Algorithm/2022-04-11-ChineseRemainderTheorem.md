---
title: "중국인의 나머지 정리(Chinese Remainder Theorem, CRT)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` 정수론, 합동식, 확장 유클리드 알고리즘, 베주 항등식, 

## 1. Chinese Remainder Theorem

### 1-1. Theorem

$1$보다 크고 서로 서로소(coprime)인 $k$개의 정수 $n_1, n_2, \dots, n_k$와 $N = n_1 n_2 \dots n_k$을 생각하자. 

중국인의 나머지 정리는 아래 연립 합동식(congruence)의 해가 존재한다는 것이다.

\begin{aligned}
x \equiv a_1 \pmod{n_1} \\\\  
x \equiv a_2 \pmod{n_2} \\\\  
\dots \\\\  
x \equiv a_k \pmod{n_k}
\end{aligned}

이때 모든 $i$에 대해 $a_i$는 $0 \leq a_i < n_i$를 만족하는 정수이다.

특히, $0 \leq x < N$을 만족하는 해 $x$는 유일하다.

---

### 1-2. Proof

**[Uniqueness]**

$x, y$($x > y$)를 주어진 연립 합동식의 해라고 하자.

모든 $i$에 대해 $x \equiv y \pmod{n_i}$이므로, $x - y$는 $n_i$의 배수이다.

즉, 어떤 양의 정수 $m$에 대해 $x - y = mN$이다.

따라서 $0 \leq x < N$을 만족하는 해 $x$는 유일하다.

**[Existence]**

연립 합동식의 해의 존재성은 직접 해를 구함으로써 보일 수 있다.

먼저 두 개의 합동식으로 이루어진 연립합동식의 해를 구한 뒤, 이를 확장하여 일반적인 연립합동식의 해를 구할 것이다.

**Case 1) 두 개의 합동식으로 이루어진 연립합동식의 해**

$n_1, n_2$가 서로소이고, $1$보다 큰 정수일 때, 다음과 같은 연립합동식을 생각하자.

\begin{aligned}
x \equiv a_1 \pmod{n_1} \\\\  
x \equiv a_2 \pmod{n_2}
\end{aligned}

**베주 항등식(Bézout’s identity)**에 의해 $m_1n_1 + m_2n_2 = 1$을 만족하는 두 정수 $m_1, m_2$가 존재한다.

> Bézout’s identity: 두 정수 $a, b$의 최대공약수를 $d$라고 할 때, $ax + by = d$를 만족하는 정수 $x, y$가 존재한다.
> 
> 이때 $x, y$를 $(a, b)$에 대한 Bézout coefficient라고 부르며, 이들은 유일하지 않다.

$m_1, m_2$는 [확장 유클리드 알고리즘(extended Euclidean algorithm)](https://damo1924.github.io/algorithm/EuclideanAlgorithm/#2-extended-euclidean-algorithm)을 통해 구할 수 있다.

$m_1, m_2$를 구했다면 연립합동식의 해 $x$는 다음과 같다.

\begin{aligned}
x = a_1m_2n_2 + a_2m_1n_1
\end{aligned}

아래와 같이 식을 적절히 변형하면,

\begin{aligned}
x &= a_1m_2n_2 + a_2m_1n_1 \\\\  
&= a_1(1 - m_1n_1) + a_2m_1n_1 \\\\  
&= a_1 + (a_2 - a_1)m_1n_1
\end{aligned}

를 얻을 수 있고, 따라서 $x \equiv a_1 \pmod{n_1}$을 만족한다.

두 번째 합동식도 만족시킨다는 것을 비슷한 방식으로 증명할 수 있다.

**Case 2) 일반적인 경우**

앞에서 증명한 사실을 통해 아래와 같은 일반적인 연립합동식의 해가 존재한다는 것을 증명할 수 있다.

\begin{aligned}
x \equiv a_1 \pmod{n_1} \\\\  
x \equiv a_2 \pmod{n_2} \\\\  
\dots \\\\  
x \equiv a_k \pmod{n_k}
\end{aligned}

$0$보다 크거나 같고, $n_1n_2$보다 작은 첫 두 합동식의 해를 $a_{1, 2}$라고 하면, 첫 두 합동식의 해들을 다음 합동식을 만족한다.

\begin{aligned}
x \equiv a_{1, 2} \pmod{n_1n_2}
\end{aligned}

$n_1n_2$는 다른 $n_i$들과 여전히 서로소이기 때문에 기존 $k$개의 합동식으로 이루어졌던 연립합동식을 $k-1$개의 합동식으로 바꿀 수 있다.

이 과정을 반복함으로써 기존 연립합동식의 해를 구할 수 있다.

---

### 1-3. Implementation

$a_1, a_2, \dots, a_k$와 $n_1, n_2, \dots, n_k$가 주어졌을 때, 연립합동식의 해를 구하는 프로그램을 구현해보자.

앞서 해의 존재성을 증명할 때 언급했듯이, **확장 유클리드 알고리즘**을 이용할 것이다.

```cpp
int EEA(int a, int b, int& s, int& t) // Expended Euclidian Algorithm
{
    if (b == 0) { s = 1; t = 0; return a; }
    
    int gcd = EEA(b, a % b, s, t);
    int temp = t;
    t = s - (a / b) * t;
    s = temp;
    return gcd;
}

int CRT(vector<int>& a, vector<int>& n) // Chinese Remainder Theorem
{
    int m1, m2;
    for (int i = 1; i < a.size(); i++)
    {
        EEA(n[i - 1], n[i], m1, m2);
        ll sol = (1ll) * a[i - 1] * m2 * n[i] + (1ll) * a[i] * m1 * n[i - 1];
        n[i] *= n[i - 1];
        a[i] = sol % n[i];
        if (a[i] < 0) a[i] += n[i];
    }
    return a.back();
}
```

두 개의 식으로 이루어진 연립합동식의 해를 반복해서 구해줌으로써 전체 연립합동식의 해를 얻을 수 있다.

두 정수 $a, b$의 최대공약수를 구할 때 유클리드 호제법의 시간복잡도는 $O(\log (\max(a, b)))$이므로 전체 시간복잡도는 $O(k \log N)$이다.

<br/>

## References

[1] [WIKIPEDIA, 'Chinese Remainder Theorem'](https://en.m.wikipedia.org/wiki/Chinese_remainder_theorem)  
[2] [WIKIPEDIA, 'Bézout's identity'](https://en.m.wikipedia.org/wiki/B%C3%A9zout%27s_identity)  
