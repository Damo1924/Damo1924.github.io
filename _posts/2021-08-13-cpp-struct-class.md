---
title: "Struct & Class in C++"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Cpp
use_math: true

---

# 1. Struct
## 1-1. 구조체란?
프로그래밍을 하다 보면 객체를 표현하기 위해 여러 개의 변수가 필요한 경우가 있다. 예를 들어 학생들을 표현하기 위해 이름, 생일, 키 등의 정보가 필요하다고 하자. 학생 수가 적다면 큰 문제가 없지만, 학생 수가 많아질수록 각 학생에 대해 변수들을 선언하고 변수들을 함수에 전달하기 힘들어진다. 이런 문제를 해결해 줄 수 잇는 것이 바로 **구조체(structure)**이다.  
구조체는 여러 개의 변수를 그룹으로 묶어서 편하게 관리할 수 있도록 하는 데이터 유형을 **집계 데이터 유형(aggregate data type)** 중 하나로, 사용자가 직접 정의하는 자료형(user-defined data type)이다. 

## 1-2. 구조체 정의하기
구조체는 `struct`를 이용해서 정의하고, 중괄호 안에 포함시키고자 하는 멤버(member)들을 선언해준다.
- **Data Member**: 구조체에 포함할 변수들
- **Member Functions**: 구조체 내부에 선언된 함수들

아래 코드는 `Student`라는 구조체를 만들어 본 코드이다.
```cpp
struct Student
{
    string name;
    int age;
    double height;
    void printInfo(){
        cout << "Name: " << name << endl;
        cout << "Age: " << age << endl;
        cout << "Height: " << height << endl;
    }
}
```
학생들의 이름, 나이, 키를 저장할 변수들과 저장된 정보를 출력해서 보여주는 멤버 함수를 정의하였다.

## 1-3. 구조체 선언하기 & 초기화하기
구조체를 정의한 다음, 이를 사용하기 위해 구조체를 선언하고 초기화하는 방법에 대해 알아보자.  
구조체의 선언은 일반적인 변수들을 선언하듯이 해줄 수 있다.
```cpp
Student s;
```
만약 여러 개의 객체를 한 번에 다루고 싶다면, 다음과 같이 배열로 선언할 수도 있다.
```cpp
Student students[10];
```

구조체의 멤버 변수들은 중괄호를 이용해서 선언과 동시에 초기화할 수 있다.
```cpp
Student s = {"Kim", 19, 173.5};
```

**Dot operator** `.`를 이용해서 구조체의 각 멤버 변수에 접근해여 값을 저장하는 방법도 있다. 
```cpp
s.name = "Kim";
s.age = 19;
s.height = 173.5;
```
Dot operator를 통해 구조체 내부에 정의한 함수도 호출할 수 있다.
```cpp
s.printInfo();
```
Name: Kim
Age: 19
Height: 173.5
```























# References
[1] [Geeksforgeeks, 'Structures in C++'](https://www.geeksforgeeks.org/structures-in-cpp/)
[2] [Geeksforgeeks, 'Difference between C structures and C++ structures](https://www.geeksforgeeks.org/difference-c-structures-c-structures/?ref=rp)






