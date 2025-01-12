---
title: "[C++] static"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Cpp
use_math: true

---

# 1. Memory Structure
프로그램은 다음과 같은 과정을 통해 실행된다.

1. 사용자가 프로그램 실행 요청
2. 운영체제(OS)에서 프로그램의 정보를 읽어 메모리에 로드(load)
3. CPU는 프로그램의 코드를 따라 메모리를 관리하고 명령문을 실행

이처럼 프로그램을 실행하면 컴퓨터의 운영체제는 메모리(RAM)에 공간을 할당하는데, 다음의 4가지 종류의 메모리 공간을 할당해준다.

- **코드(code) 영역**: 우리가 작성한 **소스코드**가 저장되는 공간으로, 실행 파일을 구성하는 명령어들(함수, 제어문, 상수 등)이 저장된다.
- **데이터(data) 영역**: **전역변수**와 **정적변수**가 할당되는 공간으로, 프로그램의 시작과 동시에 할당되고, 프로그램이 종료되어야 메모리가 소멸된다.
- **힙(heap) 영역**: 프로그래머가 **동적 할당(dynamic memory allocation)** 통해 메모리를 할당 또는 해제하는 메모리 공간이다.
- **스택(stack) 영역**: 프로그램이 자동으로 사용하는 **임시 메모리 공간**으로, 함수 호출 시 생성되는 **지역변수**와 **매개변수**가 저장되며, 함수 호출이 완료되면 소멸된다.

Heap과 Stack 영역은 메모리 상의 같은 공간을 공유하는데, Heap은 메모리 위쪽 주소부터 할당되고 Stack은 메모리 아래쪽부터 할당된다. 그러다보면 각 영역이 상대 영역을 침범하는 일이 발생할 수 있는데, 이를 각각 **Heap Overflow**, **Stack overflow**라고 부른다.


<br/>
# 2. 지역(Local) 변수 & 전역(Global) 변수
## 2-1. 지역 변수(Local variable)
지역 변수란 **블록** 내에서 선언된 변수를 의미하며, 다음과 같은 특징을 갖는다. 이때 블록(block)이란 중괄호 영역을 뜻한다.

- **변수가 선언된 블록 내에서만 유효**하다.
- 지역 변수는 임시 메모리 공간인 스택 영역에 저장되기 때문에 해당 블록이 종료되면 메모리에서 소멸된다.
- 지역 변수는 **초기화하지 않으면 아무런 의미가 없는 값으로 자동적으로 초기화**된다.
- **함수의 매개변수** 또한 함수 내에서 정의된 지역 변수로 취급된다.

## 2-2. 전역 변수(Global variable)
전역 변수란 함수의 외부에서 선언된 변수를 의미하며, 다음과 같은 특징을 갖는다.

- 전역 변수는 프로그램의 어느 곳에서나 접근이 가능하다.
- 데이터 영역에 저장되기 때문에 **프로그램이 종료되어야 메모리에서 소멸**된다.
- 전역 변수는 직접 초기화하지 않아도 **0으로 자동적으로 초기화**된다.

프로그램이 여러 개의 파일로 구성된 경우에는 `extern` 키워드를 사용해서 다른 파일에 정의된 전역 변수를 현재 위치에서도 사용할 수 있다.

아래 코드를 통해 지역 변수와 전역 변수의 차이점에 대해서 간단히 확인해 보았다.
```cpp
#include <iostream>
using namespace std;

int g_var;

void func()
{
    int var = 10;
    g_var = 10;
}

int main()
{
    int var;
    
    cout << g_var << endl;
    cout << var << endl;
    
    func();
    cout << g_var << endl;
    cout << var << endl;
}
```
```
0 // 전역 변수는 자동으로 0으로 초기화
48 // 지역 변수는 쓰레기값으로 초기화
10 // 전역 변수는 어느 곳에서나 접근 가능
48 // 지역 변수는 해당 블록 내에서만 유효
```


<br/>
# 3. 정적(Static) 변수
`static`은 C 언어와 C++ 등의 프로그래밍 언어의 키워드로서, 변수나 클래스의 멤버를 static으로 선언하여 사용할 수 있다.

## 3-1. 정적 변수
static으로 선언된 변수를 **정적 변수(static variable)**이라고 부르며 다음과 같은 특징을 갖는다.

**1) 함수 내에 선언된 정적 변수는 한 번만 초기화되고, 전역 변수처럼 프로그램 실행 전반에 걸쳐 변수의 수명이 유지된다.**
```cpp
#include <iostream>
using namespace std;

void func()
{
    static int x = 0; // 최초로 실행될 때 단 한 번만 수행된다.
    x++;
    cout << x << " ";
}

int main()
{
    for (int i = 0; i < 5; i++)
        func();
}
```
```
1 2 3 4 5
```
만약 함수 내의 변수 `x`를 static으로 선언하지 않았다면, 함수를 호출할 때마다 스택 영역에 x가 새롭게 선언되면서 출력 결과가 다음과 같았을 것이다.
```
1 1 1 1 1
```
하지만 static으로 선언해줌으로써 x는 함수가 끝나도 소멸하지 않고 유지된다.

**2) 전역 변수에 선언된 static은 선언된 파일 내에서만 참조를 허용한다.**

static으로 선언한 전역 변수는 같은 프로그램 내의 다른 파일에서 사용할 수 없게 된다.

## 3-2. static 멤버 변수
앞서 살펴본 정적 변수는 기존 C 언어에서도 존재하던 개념이다. C++에서는 추가적으로 클래스의 멤버를 static으로 선언할 수 있게 되었는데, 이를 **정적 멤버 변수** 또는 **클래스 변수**라고 부르며 다음과 같은 특징을 가진다.

- 클래스 당 하나씩만 생성
- 해당 클래스의 모든 객체들이 공유하는 변수
- **객체 생성 전에도 이미 생성되어 있으며, 클래스 이름을 통해 접근이 가능하다.**
- 생성된 객체의 개수와 관계없이 메모리 공간에 한 번만 할당
- 실제로는 **객체 외부에 존재하는 변수로, 객체는 해당 변수에 접근할 수 있는 권한이 주어진 것**
- 전역 변수처럼 프로그램이 종료되어야 소멸

정적 멤버 변수는 **객체가 생성될 때 동시에 생성되는 변수가 아닌, 이미 메모리 할당이 이루어진 변수이므로 클래스 내부에서 초기화하지 않고 반드시 전역 범위에서 초기화를 해야 한다.** 이 경우에는 설령 private이더라도 클래스 외부에서 정의가 가능하도록 되어있다.

```cpp
#include <iostream>
using namespace std;

class className {
public:
    static int var; // static 멤버 변수 선언
    
    void printInfo() { cout << var << endl; }
};

int className::var = 10; // static 멤버 변수 정의: 반드시 전역 범위에서 초기화해야한다!!

int main()
{
    // int className::var = 10; 오류발생! - 정적 멤버 변수는 전역 범위에서 초기화

    cout << className::var << endl; // 10 - 객체 생성을 하지 않았음에도 존재하며, 클래스 이름으로 접근하는 것이 가능하다.
    cout << &className::var << endl; // 0x30000bb008
    
    className c1;
    className c2;
    
    cout << c1.var << endl; // 10
    cout << &c1.var << endl; // 0x30000bb008
    
    cout << c2.var << endl; // 10
    cout << &c2.var << endl; // 0x30000bb008
    
    c1.var = 20;
    
    cout << c1.var << endl; // 20
    cout << c2.var << endl; // 20
    cout << className::var << endl; // 20
}
```
위 코드의 결과를 통해 다음을 확인할 수 있다.
- 클래스 자체로 직접 접근하던, 각 객체를 통해 접근하던 정적 멤버 변수는 모두 같은 주소값을 가진다.
- 즉, 객체와는 독립적으로 존재하는 유일한 변수이다.

## 3-3. static 멤버 함수
정적 멤버 함수도 정적 멤버 변수와 동일한 특성을 가진다.

객체의 멤버로 존재하는 것이 아니기 때문에 다음과 같은 코드는 에러를 발생시킨다.
```cpp
#include <iostream>
using namespace std;

class className {
private:
    int num1;
    static int num2;
public:
    className(int n): num1(n) { }
    static void Adder(int n) {
        num1 += n; // Error!!
        num2 += n;
    }
};

int className::num2 = 0;

int main()
{
    cout << "No error" << endl;
}
```
정적 멤버 함수 `Adder()`는 객체의 멤버가 아니므로 객체의 멤버 변수인 `num1`에 접근 권한이 없기 때문이다. 

이를 통해 다음과 같은 결론을 얻을 수 있다.
- static으로 선언된 멤버 함수에서는 일반 멤버 변수를 사용할 수 없다.
- 그러므로 멤버 함수 내에서 인스턴스 변수를 사용하지 않는다면 static을 붙여 함수 호출시간을 줄일 수 있다.

## 3-4. static const 멤버 변수
static const 멤버 변수는 **클래스 내에서 초기화하는 것이 가능**하다.
```cpp
class className {
private:
    static const int var = 10;
};
```

## 3-5. static 멤버 변수를 클래스 내부에서 초기화하는 방법
클래스 내부에 또다른 클래스를 정의한 뒤, 그 클래스의 생성자 내부에서 정적 멤버 변수를 초기화할 수 있다.
```cpp
class className {
public:
    // 내부 클래스 정의
    class _init {
    public:
        _init() {
            var = 10; // 생성자를 통한 정적 멤버 변수 초기화
        }
    };

private:
    static int var;
    static _init s_initializer; // 내부 클래스의 객체 생성은 static으로!
};
```


<br/>
# References
[1] [TCPschool, '메모리의 구조'](http://tcpschool.com/c/c_memory_structure)  
[2] [TCPschool, '변수의 유효 범위'](http://tcpschool.com/c/c_function_variableScope)  
[3] [WIKIPEDIA, '정적 변수'](https://ko.m.wikipedia.org/wiki/%EC%A0%95%EC%A0%81_%EB%B3%80%EC%88%98)  
[4] [WikiDocs, C++ 언어, '06-03. C++에서의 static'](https://wikidocs.net/21186)  
[5] [ansohxxn.github.io, 'C++ Chapter 8.10: 정적 멤버 변수'](https://ansohxxn.github.io/cpp/chapter8-10/)  
