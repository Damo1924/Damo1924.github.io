---
title: "자연수를 제곱수들의 합으로 표현하는 방법"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` NumberTheory, 17633, 17646, Gaussian intergers, Euclidean algorithm

이 포스팅은 아래 문제들을 풀기 위해 필요한 내용에 대해 다루고 있다.

- [BOJ 17633. 제곱수의 합(More Huge)](https://www.acmicpc.net/problem/17633)
- [BOJ 17646. 제곱수의 합 2(More Huge)](https://www.acmicpc.net/problem/17646)

<br/>

## 1. Theorems about Sum of Squares

아래 세 정리를 통해 주어진 자연수가 최소 몇 개의 제곱수들의 합으로 나타내질 수 있는지 판별할 수 있다.

> **Theorem 1.** (Lagrange's four-square theorem)
> 
> 모든 자연수는 네 정수의 제곱의 합으로 나타낼 수 있다.
> 
> 즉, 임의의 자연수 $n$에 대하여 $n = a_1^2 + a_2^2 + a_3^2 + a_4^2$ 을 만족하는 네 정수 $a_1, a_2, a_3, a_4$ 가 존재한다.

[Lagrange's four-square theorem의 증명](https://damo1924.github.io/math/FourSquareTheorem/)

> **Theorem 2.** (Legendre's three-square theorem)
> 
> 자연수 $n$이 세 정수의 제곱의 합으로 나타낼 수 있기 위한 필요충분조건은
> 
> $n$이 $4^a(8b + 7)$ 의 꼴이 아니라는 것이다.($a, b$는 음이 아닌 정수)

[Legendre's three-square theorem의 증명](https://damo1924.github.io/math/ThreeSquareTheorem/)

> **Theorem 3.1.** (Fermat's theorem on sums of two squares)
> 
> 홀수인 소수 $p$가 두 정수의 제곱의 합으로 나타낼 수 있기 위한 필요충분조건은 $p \equiv 1 \pmod{4}$ 이다.

> **Theorem 3.2.** (Sum of two squares theorem)
> 
> $1$보다 큰 정수가 두 정수의 제곱의 합으로 나타낼 수 있기 위한 필요충분조건은 정수를 소인수분해했을 때 $p^k$를 포함하지 않는 것이다.
> 
> 이때 $p$는 $4$로 나눈 나머지가 $3$인 소수이고, $k$는 홀수이다.

[Fermat's theorem on sums of two squares의 증명](https://damo1924.github.io/math/SumofTwoSquares/)

 따라서 자연수 $N$에 다음과 같은 과정을 통해 몇 개의 제곱수로 표현할 수 있는지 구할 수 있다.
 
 1. $N$이 $4^a(8b + 7)$ 꼴의 자연수인지 확인 $\to$ 맞다면 최소 네 제곱수의 합으로 표현 가능하다.
 2. $N$을 소인수분해 했을 때, $4$로 나눈 나머지가 $3$인 소수가 홀수 개만큼 있는지 확인 $\to$ 있다면 $N$은 최소 세 제곱수의 합으로 표현 가능하다.
 3. $N$이 제곱수인지 확인 $\to$ 제곱수이면 한 개, 아니면 두 개의 제곱수의 합으로 표현 가능하다.

이를 이용하면 [BOJ 17633. 제곱수의 합(More Huge)](https://www.acmicpc.net/problem/17633)을 해결할 수 있다.

소인수분해는 [밀러-라빈 소수판별법(Miller-Rabin primality test)](https://damo1924.github.io/algorithm/MillerRabinPrimalityTest/)을 이용하는 [폴라드 로 알고리즘(Pollard's rho algorithm](https://damo1924.github.io/algorithm/PollardRhoAlgorithm/)을 통해 $O(\sqrt[4]{n})$ 로 수행할 수 있다.

이제 [BOJ 17646. 제곱수의 합 2(More Huge)](https://www.acmicpc.net/problem/17646)을 해결하기 위해 직접 제곱수의 합으로 표현하는 방법에 대하여 알아보자.

<br/>

## 2. 




## References

[1] [SECMEM, ho94949, '제곱수의 합'](http://www.secmem.org/blog/2019/10/18/sum-of-squares/)  
[2] 
