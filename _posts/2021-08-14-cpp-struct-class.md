---
title: "User defined data type in C++: Struct, Class (+ operator overloading)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Cpp
use_math: true

---

# 1. Struct
## 1-1. 구조체란?
 프로그래밍을 하다 보면 객체를 표현하기 위해 여러 개의 변수가 필요한 경우가 있다. 예를 들어 학생들을 표현하기 위해 이름, 생일, 키 등의 정보가 필요하다고 하자. 학생 수가 적다면 큰 문제가 없지만, 학생 수가 많아질수록 각 학생에 대해 변수들을 선언하고 변수들을 함수에 전달하기 힘들어진다. 이런 문제를 해결해 줄 수 잇는 것이 바로 **구조체(structure)**이다. 구조체는 여러 개의 변수를 그룹으로 묶어서 편하게 관리할 수 있도록 하는 데이터 유형을 **집계 데이터 유형(aggregate data type)** 중 하나로, 사용자가 직접 정의하는 자료형(user-defined data type)이다. 

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
};
```
학생들의 이름, 나이, 키를 저장할 변수들과 저장된 정보를 출력해서 보여주는 멤버 함수를 정의하였다.

## 1-3. 구조체 선언하기 
구조체의 선언은 일반적인 변수들을 선언하듯이 해줄 수 있다.
```cpp
Student a, b, c;
```
만약 여러 개의 객체를 한 번에 다루고 싶다면, 다음과 같이 배열로 선언할 수도 있다.
```cpp
Student students[10];
```

아래와 같이 `struct`로 구조체를 정의함과 동시에 객체를 선언할 수도 있다.
```cpp
struct Student
{
    ...
} a, b, c;
```

## 1-4. 구조체 초기화하기
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
```
Name: Kim
Age: 19
Height: 173.5
```

## 1-5. 구조체 포인터
구조체는 다른 자료형들과 마찬가지로 함수에 전달하고 반환값으로도 사용할 수 있으며, 포인터를 선언해서 활용할 수도 있다.
```cpp
#include <iostream>
using namespace std;

struct point {
    double x;
    double y;
}

void ori_symmetry(point* A) {
    double temp = A->x;
    A->x = A->y;
    A->y = temp;
}

int main() {
    point A = {1, 2};
    ori_symmetry(&A);
    cout << "(" << A.x << ", " << A.y << ")" << endl;
}
```
```
(2, 1)
```
: 2차원 평면 위의 점의 좌표를 원점 대칭시키는 함수를 포인터를 통해 구현한 코드이다. 이때 새로운 연산자 arrow operator `->`가 등장한다.  
- **Arrow operator(->)**: 멤버를 가진 객체들을 가리키는 포인터에 사용하는 역참조(dereference) 연산자이다. 객체의 멤버들의 주소로 직접 접근할 수 있게 해주며, `ptr->x`는 `(*ptr).x`와 동일하다.

## 1-6. 중첩 구조체(Nesting structures)
구조체는 다른 구조체의 멤버로 사용할 수 있다.
```cpp
#include <iostream>
using namespace std;

struct point {
    double x;
    double y;
}

struct triangle {
    point A;
    point B;
    point C;
}

int main() {
    triangle T = { {0, 0}, {1, 0}, {0, 1} };
    cout << T.A.x << endl;
}
```
```
0
```


<br/>
# 2. Class
## 2-1. 



# References
[1] [Geeksforgeeks, 'Structures in C++'](https://www.geeksforgeeks.org/structures-in-cpp/)  
[2] [Geeksforgeeks, 'Difference between C structures and C++ structures](https://www.geeksforgeeks.org/difference-c-structures-c-structures/?ref=rp)  
[3] [cplusplus, 'Data structures'](https://www.cplusplus.com/doc/tutorial/structures/)  
[4] [cplusplus, 'Classes'](http://www.cplusplus.com/doc/tutorial/classes/)  






