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

### 1-2-1. 
