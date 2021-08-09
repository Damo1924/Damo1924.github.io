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


<br/><br/>
# 2. Applications of References
## 2-1. References as function parameters
- 함수가 참조형을 변수로 전달받으면 **기존 변수의 값을 변경**할 수 있게 된다.
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
참조형이 아닌 일반적인 자료형으로 입력을 받을 경우, 함수는 기존 변수의 **복사본**을 전달받기 때문에 함수 내에서 값을 변경해도 기존의 변수에는 아무런 영향을 주지 못한다. 이때 참조형 `first`, `second`으로 함수에 값을 전달하면 위의 코드처럼 함수 내부에서 일어난 변화가 기존 변수 `a`, `b`에도 적용된다는 것을 알 수 있다.
- 크기가 큰 객체를 **복사 없이 함수로 전달**할 수 있다.
함수에 크기가 큰 객체를 전달해야하는 경우 참조형을 사용하지 않는다면 객체의 복사본을 생성하기 때문에 CPU의 작업 속도나 메모리를 낭비하게 된다. 참조형을 사용하면 복사본을 만들지 않기 때문에 보다 효율적인 코드를 짤 수 있다.

## 2-2. Using references to pass C-style arrays to functions
C-style 배열을 함수로 전달할 때 포인터를 이용하면 배열이 아닌 포인터를 전달하는 것이기 때문에 `sizeof()`와 같은 함수나 연산자들이 원하는대로 작동하지 않는다. 이는 배열을 참조형으로 전달함으로써 해결할 수 있는데, 이때 반드시 parameter에 배열의 크기를 정의해주어야 한다.
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

## 2-3. References as shortcuts





