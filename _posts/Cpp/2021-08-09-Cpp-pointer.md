---
title: "[C++] Pointers"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Cpp
---

# 1. Basics of pointers
## 1-1. 포인터란?
코드를 실행하면 컴파일러는 변수에 메모리를 할당하고, 그 위치에 데이터를 저장한다. 이 데이터를 호출하기 위해서는 데이터가 메모리의 어느 위치에 저장되어 있는지 알아야 하는데, 이때 데이터가 저장된 메모리의 시작 주소를 주소 값이라고 한다.
**포인터는 변수가 저장된 메모리 상의 주소 값을 저장하는 변수이다.**

## 1-2. 포인터 선언하기
```cpp
int *ptr;
```
포인터는 `datatype *pointer_name;`의 형태로 선언한다. `datatype`에는 가리킬 변수의 자료형(int, double, ...)이 들어가는데, 그 이유는 데이터가 저장된 메모리 공간의 크기(bytes)를 알 수 있도록 하기 위해서이다. 각 데이터는 시작 주소부터 해당 자료형의 크기만큼의 공간에 저장된다. 즉, 위 코드에서 20이라는 정수는 ptr에 저장된 주소를 시작으로 4byte 크기의 메모리 공간에 저장되어 있다는 의미이다. 만약 포인터를 통해 데이터에 접근하려고 할 때 데이터의 자료형을 모른다면 올바른 값을 읽어올 수 없게 된다. 그렇기 때문에 포인터를 선언할 때는 정확한 자료형을 사용해야 하는 것이다.

## 1-3. 주소 연산자와 참조 연산자
```cpp
int var = 20;
int *ptr;
ptr = &var;
    
cout << "&var = " << &var << endl;
cout << "ptr = " << ptr << endl;
cout << "var = " << var << endl;
cout << "*ptr = " << *ptr << endl;
```
```
&var = 0x7fde669584
ptr = 0x7fde669584
var = 20
*ptr = 20
```
- **주소 연산자(ampersand)** `&` : 변수 이름 앞에 사용하며, 해당 변수의 주소값을 반환한다.
- **참조 연산자(aestrisk)** `*` : 포인터(주소) 앞에 사용하며, 해당 포인터(주소)에 저장된 값을 반환한다. 이를 **역참조(Dereferencing)**이라고 부르기도 한다. 또, 포인터를 선언할 때 변수 앞에 사용한다.

## 1-4. 포인터의 크기 & 포인터 연산(pointer arithmetic)
포인터의 크기는 주소에 저장된 자료형과는 무관하게 항상 일정하다. 32비트 실행 파일은 32비트 메모리 주소를 사용하므로 4byte이고, 64비트 실행 파일은 64비트 메모리 주소를 사용하므로 8byte이다.
```cpp
int n = 20;
int *ptr_n = &n;
    
double d = 1.5;
double *ptr_d = &d;
    
cout << "size of ptr_n = " << sizeof(ptr_n) << endl;
cout << "size of ptr_d = " << sizeof(ptr_d) << endl;
cout << "ptr_n = " << ptr_n << endl;
cout << "ptr_n + 1 = " << ptr_n + 1 << endl;
cout << "ptr_d = " << ptr_d << endl;
cout << "ptr_d + 1 = " << ptr_d + 1 << endl;
```
```
size of ptr_n = 8
size of ptr_n = 8
ptr_n = 0x7ff6c9b23c
ptr_n + 1 = 0x7ff6c9b240
ptr_d = 0x7ff6c9b230
ptr_d = 0x7ff6c9b238
```
포인터는 위의 코드와 같이 정수에 대한 **+** 연산이 가능하다. 재미있는 점은 데이터형에 따라서 그 결과가 달라진다는 것이다. 정수형 포인터에 1을 더해주면 주소값이 4만큼 증가하지만, 실수형 포인터에 1을 더해주면 주소값이 8만큼 증가한다는 것을 알 수 있다. 이처럼 포인터 산술 표현식을 계산할 때 피연산자에 가리키고 있는 객체의 크기를 곱하는 것을 **스케일링(scaling)**이라고 한다.

## 1-5. 널 포인터(Null pointer)
포인터에 주소값을 할당하기 전까지 포인터는 어떤 가비지 주소를 가리키게 된다.
메모리 주소 외에도 포인터가 저장할 수 있는 값이 하나 있는데, 바로 null 값이다. 이는 포인터가 아무것도 가리키지 않는다는 것을 의미하는 특수 값으로, null 값을 가진 포인터를 **Null pointer**라고 한다. C++에서 포인터를 null 값으로 초기화하기 위해서는 `0`이나 `NULL`값을 할당하면 된다.
```cpp
int *ptr1 = 0;
double *ptr2 = NULL;
if (ptr1) cout << "This is not a null pointer" << endl;
else cout << "This is a null pointer" << endl;
```
```
This is a null pointer
```
포인터는 null이면 false로, null이 아니면 true로 반환되므로 위와 같이 조건부를 사용하여 포인터가 어떤 주소를 가리키고 있는지 판단할 수 있다.

0은 포인터 유형이 아니어서 null pointer로 사용하기에는 문제가 있고, NULL은 기술적으로 C++의 일부가 아닌 전처리기 매크로이기 때문에 C++11에서는 `nullptr`이라는 새로운 키워드(keyword)를 도입하였다. 이는 포인터를 null pointer로 초기화하는데 사용할 수 있는 r-value 상수이다.
```cpp
int *ptr = nullptr;
```
만약 포인터를 선언만 해두고 값을 할당하지 않은 상황이라면, `nullptr`을 이용해서 초기화해주는 것이 좋다. <br/>


<br/>
# 2. Array name as Pointers
C++에서 배열의 이름은 배열의 첫 번째 원소의 주소값을 가지고 있으며, 마치 포인터처럼 사용할 수 있는 특징을 가지고 있다.
```cpp
int data[5] = {1, 2, 3, 4, 5};
cout << "data = " << data << endl;
cout << "&data[0] = " << &data[0] << endl;
cout << "*data = " << *data << endl;
```
```
data = 0x7fd7ea70f0
&data[0] = 0x7fd7ea70f0
*data = 1
```
이처럼 배열을 정의한 후에 배열의 이름인 `data`를 출력해보면, 배열의 첫 번째 원소의 주소값인 `&data[0]`와 동일한 주소값을 가진다는 것을 알 수 있다. 또한, 포인터처럼 참조 연산자를 이용하면 배열의 원소에 접근하는 것도 가능하다.

그렇다면 포인터를 선언하여 배열의 이름으로 값을 할당해보자.
```cpp
int *ptr = data;
cout << "ptr = " << ptr << endl;
cout << "&ptr[0] = " << &ptr[0] << endl;
cout << "*ptr = " << *ptr << endl;
cout << "ptr[0] = " << ptr[0] << endl;
```
```
ptr = 0x7fd7ea70f0
&ptr[0] = 0x7fd7ea70f0
*ptr = 1
ptr[0] = 1
```
앞서 배열의 이름이 포인터와 같은 특징을 가지고 있다고 했는데, 이젠 반대로 포인터를 마치 배열처럼 사용할 수 있다는 것을 알 수 있다. 먼저 `ptr`에 저장된 주소값은 배열의 첫 번째 원소의 주소값과 동일하고, 역참조를 했을 때도 첫 번째 원소인 1을 반환한다는 것을 알 수 있다. 특이한 점은 배열에서 사용하던 [k] 연산자를 이용해서 k번째 원소에 접근할 수 있다는 것이다.

이번에는 배열에 포인터의 + 연산을 사용해보자.
```cpp
cout << "data + 1 = " << data + 1 << endl;
cout << "&data[1] = " << &data[1] << endl;
cout << "*(data + 1) = " << *(data + 1) << endl;
```
```
data + 1 = 0x7fd7ea70f4
&data[1] = 0x7fd7ea70f4
*(data + 1) = 2
```
배열의 첫 번째 원소의 주소값에 1을 더하면 주소값이 4만큼 증가(data + 1)하였고, 이는 배열의 두 번째 원소의 주소값(&data[1])과 동일하다는 사실을 확인할 수 있었다. 이 결과로부터 배열의 원소들은 메모리 상에 연속적으로 저장되어 있다는 사실을 알 수 있다. 즉, `data+k`는 **인덱스가 k인 원소의 주소값**을 의미하고, `*(data+k)`는 `data[k]`와 동일한 값을 반환한다.

이렇게 보면 결국 '배열은 포인터라고 할 수 있지 않을까?'라는 생각이 들게 된다. 하지만 이는 잘못된 생각이며, 배열과 포인터는 다음과 같은 차이가 있다.
1. **Result of sizeof()**: 변수의 크기를 byte 단위로 반환하는 `sizeof()`를 배열과 포인터에 대해 구해보면 서로 다른 값을 반환한다.
```cpp
cout << "sizeof(data) = " << sizeof(data) << endl;
cout << "sizeof(ptr) = " << sizeof(ptr) << endl;
```
```
sizeof(data) = 20
sizeof(ptr) = 8
```
배열을 인자로 넣은 경우에는 배열 전체의 크기(= 배열의 길이 x 데이터형의 크기 = 5 x 4 = 20)를 반환하고, 포인터를 인자로 넣은 경우에는 포인터에 저장된 주소 값의 크기인 8byte(32bit라면 4byte)를 반환한다. 이는 함수에 배열을 포인터를 통해 전달할 때 배열의 크기를 알 수 없게 되는 문제(Decay of an array)를 초래하는 원인이다. 그래서 배열을 함수에 전달할 때는 배열의 크기를 같이 전달하는 것이 일반적이다.
2. **Result of &**: 피연산자의 주소값을 반환하는 &을 적용해보면, `&data`는 배열의 첫 번째 원소의 주소값(= data, &data[0])을, `&ptr`은 포인터가 저장된 주소를 반환한다.
```cpp
cout << "&data = " << &data << endl;
cout << "&ptr = " << &ptr << endl;
```
```
&data = 0x7fd7ea70f0
&ptr = 0x7fd7ea70e8
```
3. **값 할당하기**: 포인터의 경우에는 다른 값을 할당하는 것이 가능하지만, 배열의 경우 값을 할당하는 것이 불가능하다.
```cpp
int a = 20;
ptr = &a; //possible
data = &a; //impossible
```

이처럼 배열과 포인터는 서로 비슷한 특징을 가지고 있지만 분명히 다르다. 그렇다면 배열을 포인터처럼, 포인터는 배열처럼 사용할 수 있는 이유는 무엇일까?

그 이유는 C++ 컴파일러(compiler)에서 배열의 원소에 접근하는데 포인터 연산을 사용하기 때문이다. 컴파일러는 코드 상에서 배열의 특정 원소에 접근하기 위해 `arr[k]`를 사용하면 `*(arr+k)`로 받아들인다고 한다. 이로 인해 배열 arr에 대해 `*(arr+k)`, 그리고 포인터 ptr에 대해 `ptr[k]` 같은 표현들을 사용할 수 있는 것이다. <br/>


<br/>
# 3. Passing by pointer
함수의 인자로 변수를 전달할 때, 포인터를 사용하면 다음과 같은 효과를 얻을 수 있다.
1. 함수에서 실제 변수가 저장된 메모리 주소를 가지고 작동하기 때문에 실제 변수의 값을 변경할 수 있다.
2. 복사본(copy)를 생성하지 않기 때문에 메모리나 시간 측면에서 효율적이다.

다음은 포인터를 이용한 함수의 대표적인 예시들이다.
```cpp
#include <iostream>
using namespace std;

void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

int main()
{
    int a = 5, b = 10;
    swap(&a, &b);
    cout << "a = " << a << ", b = ", << b << endl;
}
```
```
a = 10, b = 5
```
두 정수를 교환하는 `swap()` 함수를 포인터를 이용해서 구현하였다. 포인터, 즉 변수가 저장된 메모리 상의 주소값을 함수의 인자로 사용하기 때문에 함수를 호출할 때 인자로 각 변수의 주소값인 `&a`, `&b`를 넣어주어야 한다. 코드를 실행해보면 함수 내부에서 일어난 교환이 실제 변수에도 일어났다는 것을 확인할 수 있다.

```cpp
#include <iostream>
using namespace std;

void printElement(int* arr, int len)
{
    for (int i = 0; i < len; i++) cout << *(arr + i) << " ";
}

int main()
{
    int *data = {1, 3, 5, 6};
    printElement(data, 4);
}
```
```
1 3 5 6
```
이번에는 배열을 전달받아 각 원소를 공백으로 구분하여 출력하는 함수를 만들어 보았다. 배열의 변수명은 그 자체로 주소값을 가지기 때문에 그대로 넘겨주었다. 중요한 점은 배열이 아닌 포인터를 전달한 것이기 때문에 함수 `printElement()`은 배열의 길이를 알 방법이 없으므로 배열의 길이를 함께 전달해주어야한다는 것이다.


<br/>
# 4. C-stlye string symbolic constants
일반적으로 C-stlye string은 다음과 같이 고정 배열을 이용해서 만든다.
```cpp
char str[] = "Hello";
cout << str << endl;
```
```
Hello
```
포인터를 이용해도 동일한 결과를 얻을 수 있다.
```cpp
char *str = "Hello";
cout << str << endl;
```
```
Hello
```
이처럼 포인터를 통해 정의한 문자열을 **문자열 기호 상수(string symbolic constants)**라고 부른다.

고정 배열을 통해 만들어진 문자열의 경우, 길이가 6인 고정 배열에 메모리를 할당하고 "Hello\0"로 초기화한다. 배열의 원소를 자유롭게 변경할 수 있으며,지역 변수로 처리되므로 범위를 벗어나면 배열에서 사용하는 메모리가 다른 용도로 사용할 수 있다. 결국 하나의 배열이기 때문에 포인터 연산을 통해 각 원소에 접근, 수정이 가능하다.

포인터를 통해 정의된 문자열 기호 상수의 경우에는 배열처럼 저장되는 것이 아닌, 문자열 자체를 읽기 전용 메모리에 저장하여 이를 가리키는 포인터를 설정하게 된다. 기호 상수는 수정이 불가능하고 프로그램 수명 내내 지속되므로 범위 지정 문제가 발생하지 않는다.
```cpp
const char* getName()
{
    return "Park";
}
```
만약 위 함수가 다른 지역 변수의 주소를 반환하는 함수라면, 함수가 종료됨에 따라서 지역 변수는 없어지고 주소값만 반환하게 된다. String literals는 static duration을 가지기 때문에 "Park"는 없어지지 않고 함수를 통해 반환된 주소값으로 접근할 수 있게 된다. <br/>



# References
[1] [Geeksforgeeks, 'Pointers in C and C++'](https://www.geeksforgeeks.org/pointers-in-c-and-c-set-1-introduction-arithmetic-and-array/)<br/>
[2] [LearnCpp.com, 'C-style string symbolic constants'](https://www.learncpp.com/cpp-tutorial/c-style-string-symbolic-constants/)<br/>

