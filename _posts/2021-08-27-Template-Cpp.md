---
title: "Templates in C++"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Cpp
use_math: true

---

# 1. Templates
> To **pass datatype as a parameter** so that we don't need to write the same code for different datatypes.

## 1-1. 템플릿이란?
C++를 이용해서 코딩을 하다보면 동일한 함수를 자료형만 다르게 만들어야하는 경우가 있다. 다음 예시를 보자.
```cpp
void swapInt(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}

double swapChar(char& x, char& y) {
    char temp = x;
    x = y;
    y = temp;
}
```
정수형 변수들을 swap하는 함수와 문자형 변수들을 swap하는 함수를 따로 정의해주었다. 그런데 템플릿을 이용하면 다음과 같이 하나의 함수로 깔끔하게 표현할 수 있다.
```cpp
template <typename T> // template, typename 키워드를 사용
void swap(T x, T y) {
    T temp = x;
    x = y;
    y = temp;
}
```
단순히 코드의 길이가 짧아졌을 뿐만 아니라 함수 이름도 자료형에 따라서 따로 정할 필요 없이 헷갈리지 않게 사용할 수 있다는 것을 알 수 있다.

이처럼 템플릿이란 **매개변수의 타입에 따라 함수나 클래스를 생성하는 메커니즘**을 의미한다. 또, 템플릿을 이용해서 데이터보다는 그 알고리즘에 중점을 두는 프로그래밍 방법을 **일반화 프로그래밍(generic programming)**이라고 하며, 앞선 예시와 같이 템플릿을 이용해서 정의된 함수를 **generic function**이라고 부른다.

템플릿을 이용해서 여러 데이터 타입에 대한 클래스를 생성할 수도 있다. 우리가 자주 사용하는 여러 컨테이너들(vector, pair, list, ...)이 클래스 템플릿을 이용해서 정의되어 있기 때문에 원하는 자료형을 저장할 수 있는 컨테이너를 자유롭게 이용할 수 있는 것이다.
```cpp
#include <iostream>
```


## 1-2. 템플릿의 작동 방식: 템플릿의 인스턴스화(template instantiation)
그렇다면 템플릿은 어떤 방식으로 작동할까?
```cpp
int main()
{
    int a = 10, b = 20;
    swap(a, b); // 정수형 변수에 대한 swap 함수를 생성하여 실행
    cout << "a = " << a << ", b = " << b << endl;
    
    char x = 'A', y = 'B';
    swap(x, y); // 문자형 변수에 대한 swap 함수를 생성하여 실행
    cout << "x = " << x << ", y = " << y << endl;
    
    swap(b, a); // 앞서 생성한 정수형 변수에 대한 함수가 실행된다.
}
```
```
a = 20, b = 10
x = B, y = A
```
위에서 `swap(a, b)`와 `swap(x, y)`는 각 자료형에 대해 처음 함수를 호출하였으므로, **C++ 컴파일러가 해당 자료형에 맞는 함수를 생성**한다. 이를 **함수 템플릿의 인스턴스화(template instantiation)**이라고 부르며, 이렇게 생성된 인스턴스들은 템플릿에 해당 타입이 사용될 때마다 호출된다.

템플릿의 작동 방식을 이해하고 나면, **Generic programming**에 대해 다음과 같이 설명할 수 있다.
> **Generic programming**: a style of computer programming in which algorithms are written in terms of types *to-be-specified-later* that are then *instantiated* when needed for specific types provided as parameters.

## 1-3. 템플릿 특수화(template specialization)
> To get a special behavior for a particular data type.

C++의 템플릿은 특정 타입에 대해 특별한 동작을 정의할 수 있는 템플릿 특수화(template specialization)가 가능하다.

예를 들어 다양한 자료형에 대한 `sort()` 함수가 필요하다고 하자. 이때 문자형을 제외한 나머지 자료형들에 대해서는 quicksort를 사용한다고 하자. 문자형의 경우, 가능한 값이 256개 뿐이기 때문에 counting sort가 더 나은 정렬 방법이다. 이럴 때 필요한 것이 바로 template specialization이다.
```cpp
template <typename T>
void sort (T arr[], int size)
{
    // Quicksort
}

template <>
void sort<char> (char arr[], int size)
{
    // Counting sort
}
```
먼저 일반적인 자료형에 대한 함수 템플릿을 정의한 후에, `template <>`으로 특정 자료형에 대한 특수한 정의를 해주면 된다. 



템플릿(template)은 

# References
[1] [Geeksforgeeks, 'Templates in C++'](https://www.geeksforgeeks.org/templates-cpp/)  
[2] [WIKIPEDIA, 'Generic programming'](https://en.m.wikipedia.org/wiki/Generic_programming)  
[3] [TCPschool.com, '함수 템플릿'](http://tcpschool.com/cpp/cpp_template_function)  
[4] [Geeksforgeeks, 'Template Specialization in C++'](https://www.geeksforgeeks.org/template-specialization-c/)  
[5] 
