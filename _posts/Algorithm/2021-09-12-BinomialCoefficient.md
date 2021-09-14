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

## 1. Binomial Coefficients
이항 계수(binomial coefficient)는 $(a + b)^{n}$을 전개하였을 때 $a^{r} b^{n-r} (0 \leq r \leq n)$의 계수를 의미하며, 다음과 같이 구할 수 있다.

\begin{align\*}
\binom{n}{r} = \frac{n!}{r!(n-r)!}
\end{align\*}

위 공식은 수학적 귀납법이나 조합을 이용해서 증명할 수 있다.


<br/>
## 2. Pascal Triangle
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

**Q.E.D**

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

이므로, 양변의 $x^r$의 계수가 동일하다는 점을 통해 증명이 완료된다. **Q.E.D**


<br/>
## 3. Fermat's little theorem & Euler's theorem

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

> 어떤 두 수 $i, j(0 < i < j < p)$가 존재해서 $ia$와 $ja$를 $p$로 나눈 나머지가 같다고 하자.
>
> 그러면 $(j-i)a$는 $p$로 나누어 떨어진다. 이때 $0 < j-i < p$이므로 $j-i$는 $p$의 배수가 아니다.
>
> 즉, 이는 $a$가 $p$와 서로소라는 가정에 모순이므로 귀류법에 의해 증명된다.

**Lemma 2.** $0 < i < p$인 $i$에 대해 $ia$는 $p$의 배수가 아니다.

> $p$의 배수인 $ia$가 존재한다고 가정하면 $i$는 $p$의 배수가 아니므로 마찬가지로 $a$가 $p$와 서로소라는 가정에 모순이므로 참이다.

이제 페르마의 소정리를 증명하자.

집합 $A, B$를 다음과 같이 정의하자.

{% raw %}
\begin{align\*}
A = \\{ x \mid x = ia, i \in B \\} , B = \\{ 1, 2, \dots, p-1 \\}
\end{align\*}
{% endraw %}

Lemma 1에 의해 집합 $A, B$의 크기는 같다. 즉, 다음 합동식이 성립한다.

\begin{align\*}
a \times 2a \times 3a \times \dots \times (p-1)a \equiv 1 \times 2 \times \dots \times (p-1) \not\equiv 0 \pmod{p}
\end{align\*}

양변을 $(p-1)!$을 나누면 다음을 얻는다.

\begin{align\*}
a^{p-1} \equiv 1 \pmod{p}
\end{align\*}

**Q.E.D**

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
\end{align\*}

이를 이용하면 다음이 성립한다는 사실을 알 수 있다.

\begin{align\*}
(k+1)^p \equiv k^p + 1 \pmod{p}
\end{align\*}

$\therefore$ 1, 2로부터 수학적 귀납법에 의해 임의의 정수 $a$에 대해 $a^p \equiv a \pmod{p}$가 성립한다. **Q.E.D**

---

다만, 페르마의 소정리는 모든 소수가 만족시키는 필요조건이지만, 충분조건은 아니다.

\begin{align\*}
a^{b-1} \equiv 1 \pmod{b}
\end{align\*}

위 합동식을 만족시키면서 소수가 아닌 숫자 $b$를 **카마이클 수(Carmichael number)**라고 부르며, 무한히 많이 존재한다고 한다.

---

페르마의 소정리를 일반화한 것이 바로 **오일러 정리**이다.

임의의 정수 $a$와 $n$이 서로소일 때, 오일러 정리에 따라 다음이 성립한다.

\begin{align\*}
a^{\phi (n)} \equiv 1 \pmod{n}
\end{align\*}

이때 $\phi (n)$은 오일러 파이 함수라고 불리며, $n$과 서로소인 1부터 $n$까지의 정수의 개수와 같다.

---

<br/>
## 4. Lucas Theorem

음이 아닌 정수 $n$과 $r$, 소수 $p$에 대해서 $n$과 $r$을 $p$진법으로 나타내면 다음과 같다.

\begin{align\*}
n &= n_k p^k + n_{k-1} p^{k-1} + n_{k-2} p^{k-2} + \dots + n_1 p + n_0 \\\\  
r &= r_k p^k + r_{k-1} p^{k-1} + r_{k-2} p^{k-2} + \dots + r_1 p + r_0
\end{align\*}

이때 뤼카의 정리에 의해 다음이 성립한다.

\begin{align\*}
\binom{n}{r} \equiv \prod_{i=0}^k \binom{n_i}{r_i} \pmod p
\end{align\*}

**[proof]**

이항정리로부터 다음과 같이 쓸 수 있다.

\begin{align}
\sum_{r=0}^{n} \binom{n}{r} x^r &= (1 + x)^n \\\\  
&= (1+x)^{n_k p^k + n_{k-1} p^{k-1} + n_{k-2} p^{k-2} + \dots + n_1 p + n_0} \\\\  
&= \prod_{i=0}^k \\{(1+x)^{p_i}\\}^{n_i}
\end{align}

이때 $(1+x)^{p^n}$은 이항정리에 의해 다음을 만족한다.

\begin{align\*}
(1+x)^{p^n} = \binom{p^n}{0} x^0 + \binom{p^n}{1} x^1 + \dots + \binom{p^n}{p^n} x^{p^n}
\end{align\*}

$p$가 소수이므로 모든 $1 \leq i \leq p^n - 1$에 대해서 $\binom{p^n}{i}$는 $p$로 나누어 떨어지므로 다음이 성립한다.

\begin{align}
(1+x)^{p^n} \equiv 1 + x^{p^n} \pmod p
\end{align}

수식 (3), (4)로부터 다음을 얻을 수 있다.

\begin{align}
\prod_{i=0}^k \\{(1+x)^{p_i}\\}^{n_i} \equiv \prod_{i=0}^k \\{1+x^{p^i}\\}^{n_i} \pmod p \\\\  
\end{align}

우변의 식을 이항정리를 이용해서 전개한 후 정리하면,

\begin{align}
\prod_{i=0}^k \\{1+x^{p^i}\\}^{n_i} &= \prod_{i=0}^k \\{ \sum_{r_i = 0}^{n_i} \binom{n_i}{r_i} x^{r_i p^i} \\} \\\\  
&= \left(\binom{n_0}{0} x^0 + \binom{n_0}{1} x^{p^0} + \dots + \binom{n_0}{n_0} x^{n_0 p^0} \right) \dots \left(\binom{n_k}{0} x^0 + \binom{n_k}{1} x^{p^k} + \dots + \binom{n_k}{n_k} x^{n_k p^k} \right) \\\\  
&= \sum_{r=0}^n \left(\prod_{i=0}^k \binom{n_i}{r_i} \right) x^r
\end{align}

를 얻을 수 있고, 수식 (3), (8)로부터 원하는 결과를 얻을 수 있다.

\begin{align}
\sum_{r=0}^{n} \binom{n}{r} x^r = \sum_{r=0}^n \left(\prod_{i=0}^k \binom{n_i}{r_i} \right) x^r
\end{align}

식 (9)는 항등식이므로 $x^r$의 계수는 동일하다.

\begin{align\*}
\therefore \binom{n}{r} = \prod_{i=0}^k \binom{n_i}{r_i}
\end{align\*}

**Q.E.D**

---
**Lemma 1.** $p$가 소수이므로 모든 $1 \leq i \leq p^n - 1$에 대해서 $\binom{p^n}{i}$는 $p$로 나누어 떨어진다.

매우 자명해 보여서 넘어갈려 했으나 증명을 좀 더 엄밀하게 하기 위해 추가하였다.

\begin{align\*}
\binom{n}{r} = \frac{n!}{r!(n-r)!}
\end{align\*}

위 공식에서 분자($n!$)과 분모($r!(n-r)!$)를 소인수분해 했을 때 분자의 $p$의 개수가 항상 많다는 것을 보이면 된다. ($r = 0, n$인 경우 제외)

먼저 분자에 있는 $p$의 개수는 다음과 같다.

\begin{align\*}
\left[ \frac{n}{p} \right] + \left[ \frac{n}{p^2} \right] + \dots + \left[ \frac{n}{p^k} \right] = \sum_{i=1}^k \left[ \frac{n}{p^i} \right]
\end{align\*}

이때 $k$는 $p^k \leq n$을 만족하는 가장 큰 정수이다.

분모에 있는 $p$의 개수는 $r$과 $n-r$ 각각에 대한 개수를 더해줌으로써 구할 수 있다.

\begin{align\*}
\left( \left[ \frac{r}{p} \right] + \left[ \frac{r}{p^2} \right] + \dots + \left[ \frac{r}{p^k} \right] \right) + \left( \left[ \frac{n-r}{p} \right] + \left[ \frac{n-r}{p^2} \right] + \dots + \left[ \frac{n-r}{p^k} \right] \right) \\\\  
= \sum_{i=1}^k \left( \left[ \frac{r}{p^i} \right] + \left[ \frac{n-r}{p^i} \right] \right)
\end{align\*}

정수 $a, b, m (a \leq b)$에 대해 가우스 기호는 다음 부등식을 만족한다.

\begin{align\*}
\left[ \frac{a}{m} \right] + \left[ \frac{b-a}{m} \right] \leq \left[ \frac{b}{m} \right]
\end{align\*}

이를 적용하면 $1 \leq i \leq k$를 만족하는 정수 $i$에 대해 다음 부등식이 성립한다.

\begin{align\*}
\left[ \frac{r}{p^i} \right] + \left[ \frac{n-r}{p^i} \right] \leq \left[ \frac{n}{p^i} \right]
\end{align\*}

\begin{align\*}
\therefore \sum_{i=1}^k \left( \left[ \frac{r}{p^i} \right] + \left[ \frac{n-r}{p^i} \right] \right) \leq \sum_{i=1}^k \left[ \frac{n}{p^i} \right]
\end{align\*}

**Q.E.D**

---

**수식 (7)에서 (8) 유도하기**

이 부분도 직관적이지 않은 것 같아서 이해를 돕기 위해 추가하였다.

식 (7)은 $i$가 0부터 $k$까지, 즉 $k+1$개의 다항식의 곱이다. 이를 전개한 결과는 각 다항식에서 하나씩 선택해서 곱한 것들을 모두 합한 것이다.

\begin{align\*}
(7) = \sum_{i = 0, 0 \leq r_i \leq n_i}^{k} \binom{n}{r_0} \dots \binom{n}{r_k} x^{r_0 p^0 + r_1 p^1 + \dots + r_k p^k}
\end{align\*}

위 식에서 $x$의 지수 $r_0 p^0 + r_1 p^1 + \dots + r_k p^k$는 뤼카 정리를 소개하면서 $r$을 $p$진법으로 나타낸 식과 동일하다는 것을 알 수 있다.

그러므로 위 식은 다음과 같이 쓸 수 있다.

\begin{align\*}
\sum_{i = 0}^{k} \binom{n}{r_0} \dots \binom{n}{r_k} x^{r_0 p^0 + r_1 p^1 + \dots + r_k p^k} = \sum_{r=0}^n \left(\prod_{i=0}^k \binom{n_i}{r_i} \right) x^r
\end{align\*}

---

<br/>
## 5. Algorithms to calculate Binomial Coefficients

이제 앞서 다룬 내용들을 이용해서 이항 계수를 빠르게 구하는 알고리즘들에 대해 알아보자.

### 5-1. Algorithm using Pascal triangle

먼저, $\binom{n}{r} = \binom{n-1}{r} + \binom{n-1}{r-1}$을 이용해서 재귀적으로 문제를 해결할 수 있다.

[백준 11051. 이항 계수 2 문제 링크](https://www.acmicpc.net/problem/11051)

위 문제는 자연수 $N(1 \leq N \leq 1000)$과 정수 $K(0 \leq K \leq N)$이 주어졌을 때 $\binom{N}{K}$를 10,007로 나눈 나머지를 구하는 프로그램이다.

값을 재귀적으로 구하는 함수를 정의하고, 같은 값을 반복적으로 구하는 것을 방지하기 위해 DP까지 사용해줌으로써 문제를 해결할 수 있다.

```cpp
#include <iostream>
using namespace std;

int dp[1001][1001];

int solve(int n, int k)
{
	if (k > n / 2) return solve(n, n - k);
	if (k == 0) return 1;
	if (dp[n][k] != 0) return dp[n][k];

	dp[n][k] = (solve(n - 1, k) + solve(n - 1, k - 1)) % 10007;
	return dp[n][k];
}

int main()
{
	int N, K;
	cin >> N >> K;

	cout << solve(N, K);
}
```

이때 `dp[i][j]`는 $\binom{i}{j}$를 10,007로 나눈 값을 의미한다.

그러나 이 방법은 시간과 공간 복잡도가 $O(nr)$로, N이 100,00 이상부터는 재귀 깊이(recursion depth)가 커지면서 시간이 상당히 소요된다. 그렇기 때문에 더 큰 N에 대해서는 다음 방법을 이용한다.

---

### 5-2. Algorithm using Fermat's little theorem

이 방법을 이용하면 $N$이 100,0000 정도일 때까지 빠르게 이항계수를 구할 수 있다.

다만, 페르마의 소정리를 이용하기 때문에 나누는 수가 반드시 소수여야한다.

[백준 11401. 이항 계수 3 문제 링크](https://www.acmicpc.net/problem/11401)

위 문제는 $N$이 400,0000까지 들어올 수 있을 때, 이항계수를 1,000,000,007로 나눈 나머지를 구하는 문제이다.

이렇게 큰 $N$에 대해서는 이항계수를 직접 계산해서 구해야한다.

이항 계수를 구하는 공식을 정리하면,

\begin{align\*}
\binom{n}{r} = \frac{n!}{r!(n-r)!} = \frac{n(n-1) \dots (n-r+1)}{r!}
\end{align\*}

이므로 $n(n-1) \dots (n-r+1)$과 $r!$를 주어진 소수로 나눈 나머지를 분할 정복을 통해 구해준다.

분모와 분자를 나눈 나머지로부터 이항 계수의 나머지를 구하기 위해서는 페르마의 소정리를 이용해서 $\pmod p$**에 대한 곱셈의 역원**을 구해야한다.

페르마의 소정리에 의해

\begin{align\*}
a^{p-1} \equiv 1 (mod p) \\\\  
\end{align\*}

이므로 $a$의 $\pmod p$에 대한 곱셈의 역원은 $a^{p-2}$이다. 따라서 이항 계수는 다음을 만족한다.

\begin{align\*}
\binom{n}{r} = \frac{n(n-1) \dots (n-r+1)}{r!} \equiv n(n-1) \dots (n-r+1) \times (r!)^{p-2} \pmod {p}
\end{align\*}

$a^{p-2}$도 마찬가지로 분할 정복을 이용해서 빠르게 계산해줄 수 있다.

전체 코드는 다음과 같다.

```cpp
#include <iostream>
using namespace std;

const int mod = 1000000007;

// 분할 정복을 이용해서 이항 계수의 분모, 분자 계산
long long mul(int x, int y)
{
    if (x == y) return x;

    int mid = (x + y) / 2;
    return mul(x, mid) * mul(mid + 1, y) % mod;
}

// 분할 정복을 이용해서 x^y 계산
long long pow(int x, int y)
{
    if (y == 1) return x;
    long long temp = pow(x, y / 2);
    if (y % 2 == 0) return temp * temp % mod;
    return temp * temp % mod * x % mod;
}

int main()
{
    int n, k;
    cin >> n >> k;
    if (k > n / 2) k = n - k;

    if (k == 0) cout << 1;
    else {
        long long a = mul(n - k + 1, n), b = mul(1, k);
        cout << a * pow(b, mod - 2) % mod;
    }
}
```

이 방법으로 이항 계수를 구하면 시간복잡도 $O(n \log p)$가 걸리게 된다.

---

### 5-3. Algorithm using Lucas Theorem

$n$의 값이 엄청 크고 비교적 소수 $p$의 크기가 작을 때에는 뤼카 정리를 이용한 알고리즘을 통해 매우 빠르게 이항계수를 계산할 수 있다.

[백준 11402. 이항 계수 4 문제 링크](https://www.acmicpc.net/problem/11402)

뤼카 정리를 적용하기 위해 $n, r$를 $p$진법으로 나타낸 것의 각 자리 숫자를 구하고, 그에 대한 이항계수는 페르마의 소정리를 이용한 알고리즘으로 구해준다.

코드를 구현하는 것은 비교적 간단하지만, $n_i < r_i$인 경우를 따로 처리해주어야 한다는 것을 파악하지 못해 좀 오래걸렸다.

```cpp
#include <iostream>
using namespace std;

int mul (int x, int y, int p)
{
    if (x == y) return x;
    
    int mid = (x+y)/2;
    return mul(x, mid, p) * mul(mid+1, y, p) % p;
}

int pow (int x, int y, int p)
{
    if (y == 1) return x;
    int temp = pow(x, y/2, p);
    if (y % 2 == 0) return temp * temp % p;
    return (temp * temp % p) * x % p;
}

int main()
{
    // Fast I/O
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    long long n, r;
    int p;
    cin >> n >> r >> p;
    if (r > n/2) r = n - r;
    
    int ans = 1;
    while (r != 0)
    {
        int N = n % p, R = r % p;
        n /= p;
        r /= p;
        if (R == 0) continue;
        else if (N < R)
        {
            ans = 0;
            break;
        }
        ans = (mul(N - R + 1, N, p) * pow(mul(1, R, p), p - 2, p) % p) * ans % p;
    }
    
    cout << ans;
}
```


<br/>
# References
[1] [Rebro의 코딩 일기장, 'PS를 위한 정수론 - (4) 이항 계수 (nCr mod p) 구하는 다양한 방법](https://rebro.kr/107?category=449699)  
[2] [위키백과, '페르마의 소정리'](https://ko.m.wikipedia.org/wiki/%ED%8E%98%EB%A5%B4%EB%A7%88%EC%9D%98_%EC%86%8C%EC%A0%95%EB%A6%AC)  
