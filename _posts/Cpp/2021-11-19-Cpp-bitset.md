---

title: "[C++] Bitset"

toc: true

toc_label: "On this page"

toc_icon: "chevron-right"

categories:

  - Cpp

use_math: true

comments: true

---

# 1. Bitset

`std::bitset`은 간단히 말해 비트들을 저장하는 클래스이다.

bool 원소들로 이루어진 배열과 같은 역할을 하면서도 사용하는 메모리 공간에 대해 최적화가 되어있기 때문에 각 원소가 오직 1 bit만을 차지한다.

대부분의 시스템에서 가장 작은 자료형인 char가 1 byte의 크기를 차지한다는 것을 생각하면 bitset은 8배 정도 메모리를 적게 차지한다고 볼 수 있는 것이다.

Bitset은 메모리 공간을 적게 사용한다는 점 외에도 유용한 멤버 함수들과 비트연산자를 이용할 수 있다는 장점이 있다.

만약 공간을 최적으로 사용하면서 크기가 변하는 클래스를 사용하고 싶다면 `vector<bool>`을 사용하면 된다.

## 1-1. Bitset 선언하기

Bitset은 `<bitset>` 헤더 파일에 정의되어 있으며, 괄호 안에 크기(=비트의 개수)를 써주면 된다.

```cpp
#include <bitset>
std::bitset<16> b;
```

위와 같이 선언하면 비트 16개, 즉 2 byte짜리 bitset이 만들어지게 된다.

## 1-2. Member functions of Bitset

### 1-2-1. (constructor)

**1) default: 0으로 초기화**  
**2) integer value: 정수 값을 받아 비트 형태로 저장**  
**3) string: 0 과 1로 이루어진 문자열을 비트 형태로 저장**

```cpp
#include <iostream>
#include <bitset>

int main()
{
    std::bitset<16> A;
    std::bitset<16> B (777);
    std::bitset<16> C ("10110001");
    std::cout << "A = " << A << "\n";
    std::cout << "B = " << B << "\n";
    std::cout << "C = " << C << "\n";
}
```

```
A = 0000000000000000
B = 0000001100001001
C = 0000000010110001
```

이처럼 bitset을 출력하면 0 또는 1인 비트 형태로 출력된다.

또한 정수(B)나 문자열(C)를 이용해서 생성하면 가장 오른쪽 비트들부터 값이 저장된다.

### 1-2-2. Bit access: operator[], count, size, any, none, all

**1) operator[]: 해당 비트의 참조형을 반환한다.**  
**2) count: 값이 1인 비트의 개수를 반환한다.**  
**3) size: bitset에 있는 전체 비트의 개수를 반환한다.**  
**4) any: 값이 1인 비트가 하나라도 있으면 true, 아니면 false**  
**5) none: 값이 1인 비트가 하나도 없으면 true, 아니면 false**  
**6) all: 모든 비트의 값이 1이면 true, 아니면 false**

```cpp
#include <iostream>
#include <bitset>
using namespace std;

int main()
{
    bitset<5> A ("11110");
    A[3] = 0; // 10110
    
    cout << A.count() << "\n"; // 3
    cout << A.size() << "\n"; // 5
}
```

이때 주의할 점은 **bitset의 인덱스는 가장 오른쪽 비트가 0이라는 것**이다.

### 1-2-3. Bit operations: set, reset, flip

**1) set: 전체 비트의 값을 1로 만든다.**  
**2) reset: 전체 비트의 값을 0으로 만든다.**  
**3) flip: 전체 비트의 값을 뒤집는다.**

```cpp
#include <iostream>
#include <bitset>
using namespace std;

int main()
{
    bitset<5> A ("10110");
    
    A.set(); // 11111
    A.reset(); // 00000
    
    A.set(2); // 00100
    A.flip(); // 11011
}
```

이 세 가지 멤버 함수는 인덱스를 인자로 입력하면 해당 비트 하나에만 작업을 수행한다.

### 1-2-4. Bitset operations: to_string, to_ulong, to_ullong

**1) to_string: bitset을 출력했을 때의 결과와 동일한 문자열을 반환한다.**  
**2) to_ulong: unsigned long integer로 변환한 값을 반환한다.**  
**3) to_ullong: unsigned long long으로 변환한 값을 반환한다.**

```cpp
#include <iostream>
#include <bitset>
using namespace std;

int main()
{
    bitset<10> A ("111001"); // 0000111001
    string s = A.to_string(); // 0000111001
    cout << A.to_ulong() << "\n"; // 57
}
```

## 1-3. Bitset operators

Bitset은 다음과 같이 비트연산자를 그대로 사용할 수 있다.

```cpp
#include <iostream>
#include <bitset>
using namespace std;

int main()
{
    bitset<4> A ("1001");
    bitset<4> B ("0011");
    
    cout << (A ^ B) << "\n"; // 1010 (XOR)
    cout << (A & B) << "\n"; // 0001 (AND)
    cout << (A | B) << "\n"; // 1011 (OR)
    
    cout << (~A) << "\n"; // 0110 (NOT)
    cout << (A << 1) << "\n"; // 0010
    cout << (A >> 1) << "\n"; // 0100
    
    cout << (A == B) << "\n"; // 0 (false)
    cout << (A != B) << "\n"; // 1 (true)
}
```

# References

[1] [Cplusplus, 'bitset'](https://www.cplusplus.com/reference/bitset/bitset/)  
