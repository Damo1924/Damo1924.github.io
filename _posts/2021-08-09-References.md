---
title: "References in C++"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Cpp
---

# 1. Reference variables
## 1-1. 참조형 변수란?
참조형 변수(reference variables)는 다른 객체 또는 값의 별칭(alias)으로 사용되는 변수 타입으로, 자료형 뒤에 `&`을 붙여서 선언할 수 있다.
```cpp
int x = 10;
int& ref = x;
```

## 1-2. 참조형 변수의 특징
1. **References as aliases**: 참조형 변수는 참조하는 기존의 변수와 완전히 동일하게 작동한다는 특징을 가지고 있다.
```cpp
x = 20;
cout << "x = " << x << ", ref = " << ref << endl;
```
```
x = 20, ref = 20
```
기존 변수의 값을 변경하면 참조형 변수의 값도 변한다.
```cpp
ref = 30;
cout << "x = " << x << ", ref = " << ref << endl;
```
```
x = 30, ref = 30
```
마찬가지로 참조형 변수의 값을 변경해도 기존 변수의 값까지 변하게 된다는 것을 알 수 있다.
2. **References must be initialized**: 참조형 변수는 포인터와 다르게 null 값을 저장할 수 없어 선언과 동시에 초기화해야한다.
3. **References can not be reassigned**:참조형 변수는 초기화된 후에 다른 변수를 참조하도록 변경할 수 없다. 


<br/>
# 2. 함수 호출 방식
C/C++에서 함수는 두 가지 방법(call-by-value, call-by-reference)으로 호출될 수 있다. 이때 함수에 전달되는 매개변수를 **실제 매개변수**, 함수가 전달받은 매개변수를 **형식 매개변수**라고 부른다.

## 2-1. Call-by-value
값에 의한 호출 방식은 함수 호출시 전달되는 변수(실제 매개변수)의 **복사본**을 함수의 인자(형식 매개변수)로 전달한다. 복사된 인자는 함수 내에서만 사용되는 local value이기 때문에 함수 내에서 값이 달라져도 기존 변수의 값은 달라지지 않는다.

## 2-2. Call-by-reference
참조에 의한 호출 방식은 함수 호출시 인자로 전달되는 변수의 reference를 전달한다. 실제 매개변수와 형식 매개변수 모두 동일한 메모리를 참조하기 때문에 함수 내에서 값이 달라지면 실제 매개변수의 값도 달라지게 된다.
주로 다음과 같은 상황에서 call-by-reference를 사용한다.
1. **함수 내에서 실제 매개변수를 변경하고 싶을 때**  
```cpp
#include<iostream>
using namespace std;

void swap (int& first, int& second)
{
    int temp = first;
    first = second;
    second = temp;
}

int main()
{
    int a = 2, b = 3;
    swap(a, b);
    cout << "a = " << a << ", b = " << b;
    return 0;
}
```
```
a = 3, b = 2
```
Call-by-value의 경우, 함수는 기존 변수의 **복사본**을 전달받기 때문에 함수 내에서 값을 변경해도 기존의 변수에는 아무런 영향을 주지 못한다. 이때 참조형 `first`, `second`으로 함수에 값을 전달하면 위의 코드처럼 함수 내부에서 일어난 변화가 기존 변수 `a`, `b`에도 적용된다는 것을 알 수 있다.

2. **크기가 큰 객체를 함수로 전달하고자 할 때**  
함수에 크기가 큰 객체를 전달해야하는 경우 참조형을 사용하지 않는다면 객체의 복사본을 생성하기 때문에 CPU의 작업 속도나 메모리를 낭비하게 된다. 참조형을 사용하면 복사본을 만들지 않기 때문에 보다 효율적인 코드를 짤 수 있다.

3. C-style 배열을 함수로 전달할 때  
C-style 배열을 함수로 전달할 때 포인터를 이용하면 배열이 아닌 포인터를 전달하는 것이기 때문에 `sizeof()`와 같은 함수와 연산자들이 원하는대로 작동하지 않는다. 이는 배열을 참조형으로 전달함으로써 해결할 수 있는데, 이때 반드시 parameter에 배열의 크기를 정의해주어야 한다.
```cpp
#include <iostream>
using namespace std;

void printElements(int (&arr)[4])
{
    for (int i = 0; i < sizeof(arr)/sizeof(int); i++) cout << arr[i] << " ";
}
int main()
{
    int data[] = {1, 3, 5, 6};
    printElement(data);
}
```
```
1 3 5 6
```

## 2-3. Call-by-assignment
파이썬에서 사용하는 함수 호출 방식이다. 모든 것이 객체(object)인 파이썬에서는 객체를 immutable object와 mutable object로 구분하는데, call-by-assignment는 이에 따라 호출 방식을 달리한다.
1. **Immutable objects**: int, double, string, tuple, ...  
변하지 않는 객체인 immutable object들이 함수의 인자로 전달되면 처음에는 call-by-reference로 호출하지만, 값이 변경되면 call-by-value로 동작하여 실제 매개변수가 달리지지 않는다.
2. **Mutable objects**: list, dict, set, ...  
변하는 객체인 mutable object들이 함수의 인자로 전달되면 call-by-reference로 동작하여 실제 매개변수가 달라질 수 있다.




