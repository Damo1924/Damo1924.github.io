---
title: "Fast Fourier Transform"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` Cooley-Tukey, 2-radix DIT FFT, Bit reversal, 큰 수 곱셈

<br/>

## 1. Introduction

두 다항식 $A(x), B(x)$가 각각

\begin{aligned}
A(x) = a_0 + a_1 x + a_2 x^2 + \dots + a_{n-1} x^{n-1} = \sum_{j=0}^{n-1} a_j x_j
\end{aligned}

\begin{aligned}
B(x) = b_0 + b_1 x + b_2 x^2 + \dots + b_{n-1} x^{n-1} = \sum_{j=0}^{n-1} b_j x_j
\end{aligned}

로 주어질 때, 두 다항식의 곱 $C(x) = A(x)B(x)$ 를

\begin{aligned}
C(x) = c_0 + c_1 x + c_2 x^2 + \dots + c_{2n-2} x^{2n-2} = \sum_{j=0}^{2n-2} c_j x_j
\end{aligned}

와 같이 쓸 수 있다. 이때 $c_i = a_0 b_i + a_1 b_{i-1} + \dots + a_i b_0$ 이다.

두 다항식을 전개하는 방법으로 $C(x)$를 구하면 $O(n^2)$ 의 시간복잡도로 구할 수 있다.

이번 포스팅에서 공부할 **고속 푸리에 변환(Fast Fourier Transform)**은 $O(n^2)$ 보다 빠르게 두 다항식의 곱을 계산하는 알고리즘이다.

<br/>

## 2. Basic Idea

### 2-1. Lagrange's Interpolation

고속 푸리에 변환 알고리즘의 핵심 아이디어는 **라그랑주 보간법(Lagrange's interpolation)**에 기반한다.

- $n$개의 점 $\left( x_k, f(x_k) \right)$ 을 지나는 $n-1$차 다항함수 $f(x)$는 유일하게 존재한다.

즉, 두 다항식의 곱 $C(x) = A(x)B(x)$ 을 표현하기 위해서는 $2n-1$개의 $x$값에 대한 함수값을 알아야한다.

서로 다른 $2n-1$개의 점 $x_0, x_1, \dots, x_{2n-2}$ 에 대하여

\begin{aligned}
C(x_k) = A(x_k)B(x_k)
\end{aligned}

이므로 $A(x_k)$와 $B(x_k)$의 값을 안다면 $C(x_k)$의 값을 계산할 수 있다.

---

### 2-2. Discrete Fourier Transform

다항식 $A(x) = a_0 + a_1 x + a_2 x^2 + \dots + a_{n-1} x^{n-1}$ 에 대하여,

복소수 $w \in \mathbb{C}$을 primitive $n$-th root of unity라고 할 때,

> **primitive $n$-th root of unity** $w$ : $w^n = 1$ 의 해
> 
> \begin{aligned}
> w = e^{\frac{2 \pi i}{n}\} = \cos \frac{2 \pi}{n} + i \cdot \sin \frac{2 \pi}{n}
> \end{aligned}

서로 다른 $n$개의 점 $w^0, w^1, w^2, \dots, w^{n-1}$ 에서의 함수값

\begin{aligned}
A(w^k) = \sum_{j=0}^{n-1} a_j (w^k)^j
\end{aligned}

들을 구할 수 있다. 이때 변환 $\mathbb{C} \to \mathbb{C}$ 

\begin{aligned}
(a_0, a_1, \dots, a_{n-1}) \mapsto \left( A(w^0), A(w^1), \dots, A(w^{n-1}) \right)
\end{aligned}

을 **이산 푸리에 변환(Discrete Fourier Transform, DFT)**라고 한다.

---

### 2-3. Inverse transform of DFT

반대로, DFT를 수행한 결과

\begin{aligned}
y_k = A(w^k) = \sum_{j = 0}^{n-1} a_j(w^k)^j
\end{aligned}

를 알고 있을 때, 역으로 $a_0, a_1, \dots, a_{n-1}$ 을 구하는 방법에 대하여 알아보자.

DFT는 아래와 같이 행렬로 표현할 수 있다.

\begin{aligned}
\begin{pmatrix} y_0 \\\\   y_1 \\\\   y_2 \\\\   \vdots \\\\   y_{n-1} \end{pmatrix} =
\begin{pmatrix} 1 & 1 & 1 & \dots & 1 \\\\   1 & w & w^2 & \dots & w^{n-1} \\\\   1 & w^2 & w^4 & \dots & w^{2(n-1)} \\\\   \vdots & \vdots & \vdots & \ddots & \vdots \\\\   1 & w^{n-1} & w^{2(n-1)} & \dots & w^{(n-1)(n-1)} \end{pmatrix}
\begin{pmatrix} a_0 \\\\   a_1 \\\\   a_2 \\\\   \vdots \\\\   a_{n-1} \end{pmatrix}
\end{aligned}

양변에 역행렬을 곱해주면,

\begin{aligned}
\begin{pmatrix} a_0 \\\\   a_1 \\\\   a_2 \\\\   \vdots \\\\   a_{n-1} \end{pmatrix} = \frac{1}{n}
\begin{pmatrix} 1 & 1 & 1 & \dots & 1 \\\\   1 & w^{-1} & w^{-2} & \dots & w^{-(n-1)} \\\\   1 & w^{-2} & w^{-4} & \dots & w^{-2(n-1)} \\\\   \vdots & \vdots & \vdots & \ddots & \vdots \\\\   1 & w^{-(n-1)} & w^{-2(n-1)} & \dots & w^{-(n-1)(n-1)} \end{pmatrix}
\begin{pmatrix} y_0 \\\\   y_1 \\\\   y_2 \\\\   \vdots \\\\   y_{n-1} \end{pmatrix}
\end{aligned}

을 얻을 수 있다. 즉, DFT의 역변환은 다음과 같다.

- $(y_0, y_1, \dots, y_{n-1})$ 을 $w^{-1}$ 에 대하여 DFT를 수행한 후, $n$으로 나누어주면 $(a_0, a_1, \dots, a_{n-1})$ 을 얻을 수 있다.

---

### 2-4. Idea

두 다항식의 곱은 다음과 같이 계산할 수 있다.

1. $A(x), B(x)$ 에 대해 DFT 수행
2. 위 결과를 이용하여 $C(w^0), C(w^1), \dots, C(w^{2n-2})$ 를 계산
3. 위 결과에 대해 역변환 DFT 수행

하지만 DFT를 그대로 계산하면 $O(n^2)$이기 때문에 이렇게 계산하는 것이 아무런 의미가 없다.

따라서 DFT를 빠르게 구할 수 있는 방법이 필요하다.

<br/>

## 3. Cooley-Tukey Algorithm

쿨리-튜키 알고리즘은 DFT를 구하기 위해 **분할 정복(divide and conquer)**을 이용하는 방법으로, 대표적인 FFT 알고리즘 중 하나이다.

크기가 합성수 $N = N_1N_2$인 DFT를 크기가 $N_2$인 DFT $N_1$개로 나타냄으로써 시간을 단축한다.

쿨리-튜키 알고리즘은 구현하는 방법이나 알고리즘을 적용하기 위한 특정한 조건에 따라 다양한 변형이 존재하는데,

그 중 가장 간단하고 보편적인 형태인 **radix-2 DIT FFT**에 대해 알아보자.

> DIT: Decimation In Time

---

### 3-1. Divide & Conquer

**radix-2 DIT FFT**는 구해야하는 DFT를 짝수항과 홀수항으로 나누어서 각각에 대한 DFT를 구해주는 알고리즘이다.

$n = 2^k$ 일 때, $n-1$차 다항식

\begin{aligned}
f(x) = a_{n-1}x^{n-1} + a_{n-2}x^{n-2} + \dots + a_2x^2 + a_1x + a_0
\end{aligned}

에 대하여, 두 다항식

\begin{aligned}
f_{even}(x) = a_{n-2} x^{(n-2)/2} + a_{n-4} x^{(n-4)/2} \dots + a_4 x^2 + a_2 x + a_0 = \sum_{i=0}^{(n-2)/2} a_{2i} x^i
\end{aligned}

\begin{aligned}
f_{odd}(x) = a_{n-1} x^{(n-2)/2} + a_{n-3}x^{(n-4)/2} + \dots + a_5 x^2 + a_3 x + a_1 = \sum_{i=0}^{(n-2)/2} a_{2i+1} x^i
\end{aligned}

을 정의하면 다음이 성립한다.

\begin{aligned}
f(x) = f_{even} \left( x^2 \right) + x \cdot f_{odd} \left( x^2 \right)
\end{aligned}

어떤 복소수 $w$에 대하여,

\begin{aligned}
f(w) = f_{even} \left( w^2 \right) + w \cdot f_{odd} \left( w^2 \right)
\end{aligned}

\begin{aligned}
f(-w) = f_{even} \left( w^2 \right) - w \cdot f_{odd} \left( w^2 \right)
\end{aligned}

이므로, $f_{even} \left( w^2 \right)$ 과 $f_{odd} \left( w^2 \right)$ 의 값을 알고 있다면 $O(1)$로 $f(w)$ 와 $f(-w)$ 을 구할 수 있다.

---

### 3-2. Algorithm

이제 2절에서 다룬 DFT 아이디어와 위의 분할정복을 합쳐보자.

$n = 2^m$ 꼴일 때, $w$를 primitive $n$-th root of unity라고 하자.

모든 $0 \leq k < n$ 에 대하여 $f(w^k)$를 구해야하는데, 이는 $f_{even}(w^{2k})$과 $f_{odd}(w^{2k})$로부터 구할 수 있다.

이때 $w = e^{\frac{2 \pi i}{n}\}$ 이므로,

\begin{aligned}
w^{2k} = e^{\frac{4 \pi ki}{n}\} = e^{\frac{2 \pi ki}{n/2}\} = w_{n/2}^k
\end{aligned}

이다. 이때 $w_{n/2}$는 primitive $\frac{n}{2}$-th root of unity이다.

그런데 $f_{even}(x)$와 $f_{odd}(x)$는 모두 $\frac{n}{2}-1$ 차 다항식이므로, **$f_{even}(w^{2k})$와 $f_{odd}(w^{2k})$는 각 다항식에 DFT를 수행해준 결과**임을 알 수 있다.

즉, 아래와 같이 정리할 수 있다.

- $n$차 다항식 $f(x)$에 DFT를 수행한 결과는 $f_{even}(x)$와 $f_{odd}(x)$에 DFT를 수행한 결과로부터 $O(n)$으로 구할 수 있다.

이를 분할정복으로 구현하면 총 $O(\log n)$ 개의 단계를 거치게 되므로 전체 시간복잡도는 $O(n \log n)$ 이 된다.

---

### 3-3. Implementation

> C++ STL의 `<complex>`에서는 복소수 자료형이 정의되어 있어 덧셈, 뺄셈, 곱셈 등이 가능하다.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <complex>
using namespace std;
typedef complex<double> cpx;
typedef long long ll;
const double PI = acos(-1);

void fft(vector<cpx> &a, cpx w) {
    int n = a.size();
    if (n == 1) return;
    
    vector<cpx> even(n / 2), odd(n / 2);
    for (int i = 0; i < n; i++) {
        if (i % 2) odd[i / 2] = a[i];
        else even[i / 2] = a[i];
    }
    
    fft(even, w * w);
    fft(odd, w * w);
    
    cpx wk(1);
    for (int k = 0; k < n / 2; k++) {
        a[k] = even[k] + odd[k] * wk;
        a[k + n / 2] = even[k] - odd[k] * wk;
        wk *= w;
    }
}

void multiply(vector<ll> &A, vector<ll> &B, vector<ll> &res) {
    vector<cpx> a(A.begin(), A.end()), b(B.begin(), B.end());
    int n = 2;
    while (n < a.size() + b.size()) n *= 2;
    a.resize(n); b.resize(n);
    
    double angle = 2 * PI / n;
    cpx w(cos(angle), sin(angle));
    fft(a, w); fft(b, w);
    for (int i = 0; i < n; i++) a[i] *= b[i];
    fft(a, cpx(1) / w);
    res.resize(n);
    for (int i = 0; i < n; i++) res[i] = (ll)round(a[i].real() / n);
}
```

<br/>

## 4. Date Reordering for In-Place Algorithms

앞에서 구현한 FFT 함수는 호출될 때마다 입력으로 주어진 배열만큼의 새로운 배열을 잡아야하고, 그러다보니 시간이 비교적 오래걸린다는 단점이 있다.

그러다보니 추가적인 자료구조를 사용하지 않는 **in-place algorithm**을 찾기 위한 많은 연구가 진행되었는데,

그 중 대표적인 data reordering technique인 **bit reversal**에 대해 알아보자.

---

### 4-1. Bit Reversal

먼저, 앞에서 구현한 FFT 함수가 어떤 배열들을 추가로 만드는지 관찰해보자.

예를 들어, $n = 8$ 일 때 DFT를 구하는 과정을 생각해보자.

함수가 호출될 때마다 입력을 짝수항과 홀수항으로 나누기 때문에 아래와 같이 표현된다.

<center><img src="https://user-images.githubusercontent.com/88201512/175852679-79c9e2bf-2f84-4b3d-a5da-8e80e5d83250.jpg" width="60%" height="60%"></center>

따라서 총 $O(n \log n)$ 만큼의 메모리를 사용하게 된다. 그런데 애초부터

\begin{aligned}
a_0, a_1, a_2, a_3, a_4, a_5, a_6, a_7
\end{aligned}

대신

\begin{aligned}
a_0, a_4, a_2, a_6, a_1, a_5, a_3, a_7
\end{aligned}

의 순서로 저장되어 있으면 이웃한 것들끼리 DFT를 수행해주면 된다는 것을 알 수 있다.

이웃한 것들까지 DFT를 수행하고, 그 자리에 결과를 저장해주면 되므로 추가적인 배열을 사용하지 않아도 된다.

그러기 위해서는 각 $i$에 대해 $a_i$가 어느 위치에 가야하는지를 알아야한다.

앞에서 본 그림처럼 짝수항을 앞($0 \sim \frac{n}{2}-1$), 홀수항을 뒤($\frac{n}{2} \sim n-1$)로 위치를 옮긴다고 하자.

$i$를 이진법으로 나타낸 것을 $(b_j b_{j-1} \dots b_2 b_1 b_0)\_{(2)}$ 라고 할 때,

- $b_0 = 0$ 이면 짝수이므로 $(b_j b_{j-1} \dots b_2 b_1)\_{(2)}$,
- $b_0 = 1$ 이면 홀수이므로 $\frac{n}{2} + (b_j b_{j-1} \dots b_2 b_1)\_{(2)}$

위치로 가게 된다. 그런데 이는 기존 $i$에서 $b_0$를 가장 앞으로 옮긴

\begin{aligned}
(b_0 b_j b_{j-1} \dots b_3 b_2 b_1)\_{(2)}
\end{aligned}

로 표현된다. 마찬가지로, $(b_j b_{j-1} \dots b_2 b_1)\_{(2)}$ 은 $b_1$이 $0$인지 $1$인지에 따라 위치가 결정되므로

\begin{aligned}
(b_1 b_j b_{j-1} \dots b_4 b_3 b_2)\_{(2)}
\end{aligned}

로 가게 된다. 이를 계속 반복해주면 결국 $a_i$는 **$i$를 이진법으로 표현한 것을 거꾸로 뒤집은**

\begin{aligned}
(b_0 b_1 b_2 \dots b_{j-1} b_j)\_{(2)}
\end{aligned}

의 위치로 옮기면 된다는 사실을 알 수 있다.

따라서 $(b_j b_{j-1} \dots b_2 b_1 b_0)\_{(2)}$ 에 있는 값과 $(b_0 b_1 b_2 \dots b_{j-1} b_j)\_{(2)}$ 에 있는 값을 swap해주면 된다.

---

### 4-2. Implementation

Bit reversal을 적용한 radix-2 DIT FFT를 구현해보았다.

```cpp
#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>
#include <complex>
using namespace std;
typedef complex<double> cpx;
typedef long long ll;
const double PI = acos(-1);

void fft(vector<cpx> &a, bool inv) {
    int n = a.size();
    
    for (int i = 1, j = 0; i < n; i++) { // bit reversal
        int bit = (n >> 1);
        for (; j >= bit; bit >>= 1) j -= bit;
        j += bit;
        if (i < j) swap(a[i], a[j]);
    }
    
    for (int len = 2; len <= n; len <<= 1) {
        double angle = 2 * PI / len * (inv ? -1 : 1);
        cpx w(cos(angle), sin(angle)); // primitive len-th root of unity
        for (int j = 0; j < n; j += len) {
            cpx wk(1); // w^k
            for (int k = 0; k < len / 2; k++) {
                cpx even = a[j + k], odd = a[j + k + len / 2] * wk;
                a[j + k] = even + odd;
                a[j + k + len / 2] = even - odd;
                wk *= w;
            }
        }
    }
    if (inv) for (int i = 0; i < n; i++) a[i] /= n;
}

void multiply(vector<ll> &A, vector<ll> &B, vector<ll> &res) {
    vector<cpx> a(A.begin(), A.end()), b(B.begin(), B.end());
    int n = 2;
    while (n < a.size() + b.size()) n *= 2;
    a.resize(n); b.resize(n);
    fft(a, 0); fft(b, 0); // calculate each DFT
    for (int i = 0; i < n; i++) a[i] *= b[i]; // get n points
    fft(a, 1); // inverse DFT
    res.resize(n);
    for (int i = 0; i < n; i++) res[i] = (ll)round(a[i].real());
}
```

실제로 bit reversal을 하지 않은 코드보다 2배 정도 더 빠르며, 메모리도 적게 사용한다.

<br/>

## 5. Related Problems

### [BOJ] 1067. 이동

[BOJ 1067. 이동 문제 링크](https://www.acmicpc.net/problem/1067)

수열에 맨 마지막 원소를 맨 앞으로 가져오는 것을 순환 이동이라고 한다.

두 수열 $x_0, x_1, \dots, x_{n-1}$ 과 $y_0, y_1, \dots, y_{n-1}$ 이 주어졌을 때,

두 수열에 자유롭게 순환 이동을 적용하여 얻을 수 있는 점수 $S$의 최댓값을 구하는 문제이다.

\begin{aligned}
S = x_0 y_0 + x_1 y_1 + \dots x_{n-1} y_{n-1}
\end{aligned}

두 수열의 원소를 계수로 갖는 두 다항식(하나는 정방향, 다른 하나는 역방향)을 곱하면 $n$차항의 계수가 점수 $S$와 같아진다.

얻을 수 있는 점수는 총 $n$개인데, $n$개를 전부 계산하기 위해서는 한 다항식을 두 번 이어붙이면 된다.

그러면 $n$차항부터 $2n-1$차항까지의 계수들이 두 수열로부터 얻을 수 있는 점수가 되고, 이 중 최댓값을 찾으면 된다.

---

### [BOJ] 10531. Golf Bot

[BOJ 10531. Golf Bot 문제 링크](https://www.acmicpc.net/problem/10531)

$N$개의 서로 다른 거리로 공을 보낼 수 있는 골프 기계를 최대 두 번 이용하여 공을 홀에 넣을 수 있는지 판단하는 문제이다.

골프 기계가 공을 보낼 수 있는 거리 $d$에 대하여 $d$차항의 계수를 $1$로 하고, 상수항이 $1$인 다항식을 제곱하면 된다.

---

### [BOJ] 15576. 큰 수 곱셈 (2)

[BOJ 15576. 큰 수 곱셈 (2) 문제 링크](https://www.acmicpc.net/problem/15576)

자릿수가 최대 $300000$ 인 두 정수가 주어질 때, 두 정수의 곱을 출력하는 문제이다.

정수를 다항식처럼 생각해서 FFT를 이용해주면 된다.

처음에는 다항식에서 $x = 10$ 으로 두고 구현하였는데, 생각해보니 $x = 1000$ 으로 두면 훨씬 빠르다는 것을 알게 되었다.

문자열로 두 정수를 입력받고, 각 정수를 세 자리씩 끊어서 해당하는 차수의 항의 계수로 놓는다.

곱하고 나면 계수가 $1000$을 넘어가는 항이 있기 때문에 $1000$으로 나눈 나머지만 남겨두고 몫은 다음 항에 더해준다.

```cpp
void mul(string s, string t) {
    int n = s.size(), m = t.size();
    vector<ll> a(n / 3 + 1), b(m / 3 + 1), res;
    for (int i = 0; i < n; i += 3)
        for (int j = 3; j; j--) if (n - i - j >= 0)
            a[i / 3] = a[i / 3] * 10 + s[n - i - j] - '0';
    for (int i = 0; i < m; i += 3)
        for (int j = 3; j; j--) if (m - i - j >= 0)
            b[i / 3] = b[i / 3] * 10 + t[m - i - j] - '0';
    multiply(a, b, res);
    for (int i = 1; i < res.size(); i++) {
        res[i] += res[i - 1] / 1000;
        res[i - 1] %= 1000;
    }
    int i = res.size() - 1;
    while (i >= 0 && !res[i]) i--;
    if (i < 0) cout << 0;
    else {
        cout << res[i--];
        for (; i >= 0; i--) {
            cout.width(3); cout.fill('0');
            cout << res[i];
        }
    }
}
```

<br/>

## References

[1] [WIKIPEDIA, 'Cooley-Tukey FFT algorithm'](https://en.m.wikipedia.org/wiki/Cooley%E2%80%93Tukey_FFT_algorithm)  
[2] [WIKIPEDIA, 'Fast Fourier transform'](https://en.m.wikipedia.org/wiki/Fast_Fourier_transform)  
