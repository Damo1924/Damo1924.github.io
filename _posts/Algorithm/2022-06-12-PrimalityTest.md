---
title: "여러 가지 소수 판별법 (Various Primality Tests)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` 

## 4. Miller-Rabin Primality Test

###  4-1. Algorithm

**밀러-라빈 소수 판별법**은 **페르마 소정리**를 확장하여 얻어지는 **확률적 알고리즘**이다.

홀수인 소수 $n$은 어떤 양의 정수 $s$와 홀수 $d$에 대하여 아래와 같이 나타낼 수 있다.

\begin{aligned}
n - 1 = 2^s d
\end{aligend}

페르마 소정리에 의해 $a^{n-1} - 1 \equiv 0 \pmod {n}$ 이 성립하고, 좌변을 인수분해하면

\begin{aligned}
a^{n-1} - 1 &= a^{2^s d} - 1 \\\\  
&= (a^{2^{s-1} d} + 1)(a^{2^{s-1} d} - 1) \\\\  
&\vdots
&= (a^{2^{s-1} d} + 1)(a^{2^{s-2} d} + 1) \dots (a^d + 1)(a^d - 1)
\end{aligend}

를 얻을 수 있으므로, 인수들 중 적어도 하나는 소수 $x$의 배수여야 한다.

이를 이용해서 $n$이 소수인지 판별하려고 할 때, 어떤 정수 $a$에 대하여

- $a^d \not\equiv 1 \pmod {n}$
- $a^{2^r d} \not\equiv -1 \pmod {n}$ (for all $0 \leq r \leq s - 1$)

이 성립하면, **$a$는 $n$이 합성수라는 것에 대한 강한 증거(strong witness)**가 된다.

만약 위 두 식 중 하나라도 성립하지 않으면 $a$는 $n$이 합성수라는 것에 대한 **강한 거짓증거(strong liar)**가 되고, $n$은 **확률적 소수(probably prime)**라고 부른다.

이제 $n$보다 작은 양의 정수들 중 무작위로 $a$를 선택한 후, 위의 두 식을 만족하는지 확인하는 과정을 반복함으로써 소수인지 판별하면 된다.

검사를 수행한 $a$의 개수를 $k$라고 하면, 전체 시간복잡도는 $O(k \log ^3 n)$이다.



> $n$의 크기가 작을 경우에는 

---

### 4-2. Implementation








