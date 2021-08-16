---
title: "User defined data type in C++: Struct, Class"
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
struct Student {
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
학생들의 이름, 나이, 키를 저장할 변수들과 저장된 정보를 출력해서 보여주는 멤버 함수를 정의하였다. 이때 기존 C 언어에서는 구조체 내에 함수를 정의하는 것이 불가능했는데, C++에서는 위와 같이 함수를 구조체 내에 정의할 수 있게 되었다. C 에서는 다음과 같이 멤버 함수를 정의하였다.
```cpp
struct Student {
    ...
};

void Student::printInfo(){
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Height: " << height << endl;
}

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
struct Student{
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
};

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
: 2차원 평면 위의 점의 좌표를 원점 대칭시키는 함수를 포인터를 통해 구현한 코드이다. 이때 새로운 연산자 arrow operator `->`가 등장한다. 이는 멤버를 가진 객체들을 가리키는 포인터에 사용하는 역참조(dereference) 연산자이다. 객체의 멤버들의 주소로 직접 접근할 수 있게 해주며, `ptr->x`는 `(*ptr).x`와 동일하다.

## 1-6. 중첩 구조체(Nesting structures)
구조체는 다른 구조체의 멤버로 사용할 수 있다.
```cpp
#include <iostream>
using namespace std;

struct point {
    double x;
    double y;
};

struct triangle {
    point A;
    point B;
    point C;
};

int main() {
    triangle T = { {0, 0}, {1, 0}, {0, 1} };
    cout << T.A.x << endl;
}
```
```
0
```
: 이처럼 중첩 구조체를 사용할 경우에는 dot operator를 여러 번 사용함으로써 원하는 멤버에 접근할 수 있다.

## 1-7. 구조체의 크기, 패딩(Structure Padding)
아래와 같은 구조체의 객체의 크기는 얼마일까?
```cpp
struct abc {
    char a;
    int b;
    double c;
};
```
단순히 `a`는 1byte, `b`는 4byte, `c`는 8byte이므로 1+4+8 = 13 byte가 될 것이라고 추측해볼 수 있지만, 그렇지 않다.
```cpp
abc object;
cout << "size of structure: " << sizeof(object) << endl;
```
```
size of structure: 16
```
직접 크기를 출력해보면 16byte임을 알 수 있다. 이는 **메모리에 효율적으로 접근하기 위해서 컴파일러가 Padding bytes를 추가하기 때문**이다. 32 bit 시스템에서는 CPU 한 사이클 당 4 byte의 메모리를, 64 bit 시스템에서는 한 사이클 당 8 byte의 메모리를 읽어온다. 만약 Padding byte 없이 그대로 저장하게 되면 한 번의 사이클로 읽어올 수 있는 값을 두 번의 사이클로 읽어오게 되므로 효율적이지 못하게 된다. 그래서 컴파일러는 CPU의 한 사이클에 해당하는 메모리의 크기로 끊어서 struct의 변수들을 저장한다. 이러한 데이터 정렬, 접근 방식을 **data structure alignment**라고 부른다.

앞선 예시를 64 bit 시스템에서 실행시키면, `a`와 `b`를 차례대로 저장을 한 다음 8 - (1 + 4) = 3 byte 만큼의 padding byte를 추가하고 `c`를 저장하게 된다. 그렇기 때문에 크기가 16 byte라는 결과가 나온 것이다. 아래는 멤버 변수들의 순서를 달리 바꾸어 본 결과이다.
```cpp
struct acb {
    char a;
    double c
    int b;
} object;

int main()
{
    cout << "size of structure: " << sizeof(object) << endl;
}
```
```
size of structure: 24
```
멤버 변수의 순서를 바꾼 결과, 이번에는 구조체의 크기가 24가 되었다. `a`에 이어 `c`를 저장해야 하기 때문에 7 byte만큼의 padding byte를 추가한다. 그 다음 `c`와 `b`를 저장하면서 총 24 byte를 사용하게 되는 것이다.

그런데 이 케이스에서 마지막 정수형 변수 `b`를 저장하기만 하면 되는데 왜 4 byte가 아닌 8 byte가 필요한지 의문점이 생길 수도 있다. 그 이유는 구조체의 멤버 변수들과 동시에 구조체 객체 자체도 padding을 통해 저장하기 때문이다. 다음과 같이 구조체 배열을 만든 경우를 생각해보자.
```cpp
acb object[3];
```
만약 마지막 정수형 변수에 4 byte를 할당하고 구조체를 크기 20 byte(= 8 + 8 + 4)로 저장한다면, 구조체의 크기가 8의 배수가 되지 않아서 데이터를 읽어올 때 불필요한 CPU 사이클이 발생하게 된다. 즉, 마지막 4 byte의 추가된 메모리는 구조체 자체로 인한 padding byte인 것이다.

1-7의 내용은 Reference 4, 5와 유튜브 영상(https://www.youtube.com/watch?v=aROgtACPjjg)을 참고해서 작성하였다.


<br/>
# 2. C++의 구조체 확장, 클래스(Class)
1절에서는 구조체의 기본적인 내용들에 대해서 알아보았다. 2절에서는 C++의 구조체/클래스의 특징과 기능에 대해서 알아보도록 하겠다.

> 원래 구조체는 C 언어에서 사용하던 사용자 정의 자료형이다. C++로 넘어오면서 C의 구조체에서는 없었던 것들이 추가되면서 만들어진 새로운 사용자 정의 자료형이 바로 클래스(class)이다. 그런데 C++에서 C와의 호환성을 위해 구조체를 사용할 수 있도록 한 것이다. C의 구조체와 C++의 클래스와의 차이는 엄청나지만, 사실상 C++에서 구조체와 클래스는 거의 차이가 없다고 봐도 무방할 정도이다. 가장 확실한 차이는 접근 제어 지시자의 기본값이 다르다는 것인데, 이 부분만 조심한다면 struct를 class로, class를 struct로 바꾸어 써도 아무런 문제 없이 코드가 돌아갈 가능성이 매우 높다.

## 2-1. 접근 제어 지시자(Access specifiers)
C의 구조체와 C++의 구조체의 가장 큰 차이점은 바로 접근 제어 지시자의 유무이다. 접근 제어 지시자에는 public, private, protected가 있는데, 이를 통해 멤버에 대한 접근에 제한을 둘 수 있다.
- **public**: 어디서든 접근이 가능하다.
- **private**: 외부에서 접근이 불가능하다.
- **protected**: 외부에서 접근이 불가능하나, 상속된 파생 클래스에서는 접근이 허용된다.

> C++의 구조체에서 **접근 제어 지시자가 생략된 경우에는 기본적으로 public 멤버**로 간주된다. 그러나 **클래스에서는 접근 제어 지시자가 생략된 경우에는 private 맴버**로 간주된다.

아래는 접근 제어 지시자를 사용해서 구조체를 정의해 본 코드이다.
```cpp
#include <iostream>
#include <string>
using namespace std;

struct Student {
private: // 외부에서 접근이 불가능한 멤버들
    string name;
    int age;
    double height;
public: // 외부에서 접근이 가능한 멤버들
    void printInfo();
    void setInfo(string _name, int _age, double _height);
};

void Student::printInfo(){
    cout << "Name: " << name << endl;
    cout << "Age: " << age << endl;
    cout << "Height: " << height << endl;
}

void Student::setInfo(string _name, int _age, double _height){
    name = _name;
    age = _age;
    height = _height;
}

int main(){
    Student s;
    s.setInfo("Kim", 23, 181.1);
    s.printInfo();
}
```
```
Name: Kim
Age: 23
Height: 181.1
```
학생의 정보를 저장할 멤버 변수들을 외부에서 접근할 수 없도록 private로 지정해두면 `s.name = "Kim"` 과 같이 멤버에 접근해서 초기화하는 것이 불가능하다. 그래서 객체를 초기화할 수 있도록 `setInfo()` 함수를 정의해 주었다. 이처럼 접근 제어 지시자를 이용해서 멤버에 대한 접근을 제한할 수 있다.

## 2-2. 생성자(Constructor)
위에서 멤버 변수들을 private으로 설정했기 때문에 변수들을 초기화하기 위한 추가적인 함수를 정의해 주어야 했다. 이때 **생성자(Constructor)를 이용하면 추가적인 함수 없이, 객체 생성과 동시에 초기화할 수 있게 된다.** 생성자는 객체 생성시에 호출되는 함수로, 만약 생성자를 구현하지 않는다면 아무런 인자를 받지 않고 아무런 일도 하지 않는 디폴트 생성자가 존재하게 된다. 생성자를 정의할 때에는 반환형 없이 구조체의 이름과 동일한 이름을 사용한다.
```cpp
#include <iostream>
#include <string>
using namespace std;

struct Student {
private:
    string name;
    int age;
    double height;
public:
    Student(string _name, int _age, double _height); // 생성자: 반환형 X, 구조체 이름과 동일한 이름, 매개변수 지정
};

Student::Student(string _name, int _age, double _height){ // 마찬가지로 반환형을 적지 않는다.
    name = _name;
    age = _age;
    height = _height;
}

int main(){
    Student s("Kim", 23, 181.1); // 객체 생성과 동시에 초기화
}
```
또한, 생성자로 함수의 일종이므로 **함수 오버로딩(function overloading)**이 가능하다. 전달한 인자의 개수나 자료형에 따라서 생성자의 기능을 다르게 정의할 수 있다. 예를 들어 다음과 같이 **default constructor**를 정의해서 사용할 수 있다.
```
#include <iostream>
using namespace std;

struct Rectangle {
private:
    int w, h;
public:
    Rectangle(); // 아무런 인자도 받지 않는 default constructor
    Rectangle(int, int);
    int area(){return w*h;}
};

Rectangle::Rectangle(){
    w = 10; // 생성자에 값을 입력해서 초기화해주지 않으면 스스로 설정해둔 값으로 초기화된다.
    h = 10;
}

Rectangle::Rectangle(int _w, int _h){
    w = _w;
    h = _h;
}

int main(){
    Rectangle A; // default constructor는 괄호 없이 객체를 선언하면 자동으로 호출된다.
    Rectangle B (5, 10);
    cout << "A의 넓이: " << A.area() << endl;
    cout << "B의 넓이: " << B.area() << endl;
}
```
```
A의 넓이: 100
B의 넓이: 50
```

사실 C++ 11에서는 위처럼 default constructor를 정의하지 않고 아래와 같이 일반 멤버 변수에 직접 초기값을 할당할 수 있다.
```cpp
struct Rectangle {
private:
    int w = 1, h = 1;
}
```
이를 **멤버 초기화(Member initialization)**이라고 부른다. 그런데 멤버 초기화를 생성자와 함께 이용할 수도 있다. 아래 코드를 보자.
```cpp
struct Rectangle {
private:
    int w = 1, h = 1;
public:
    Rectangle(int _w, int _h) : w(_w), h(_h) {}
}
```
다음 세 코드는 멤버 변수들을 초기화하는 동일한 기능을 한다.
> `Rectangle(int _w, int _h) { w = _w; h = _h; }`
> `Rectangle(int _w, int _h) : w(_w) { h = _h; }`
> `Rectangle(int _w, int _h) : w(_w), h(_h) {}`

이처럼 멤버 초기화를 이용한 생성자는 상속한 클래스의 변수들을 초기화할 때 사용된다.

## 2-3. 연산자 오버로딩(Operator overloading)
연산자 오버로딩이란 사용자 정의 자료형에 관한 연산자를 정의하여 좀 더 편하게 사용할 수 있게 만들어주는 C++의 문법적인 기능을 말한다. 물론 함수로도 구현해도 상관없지만, 연산자를 이용하면 조금 더 직관적이고 편리하게 사용 가능하기 때문에 알아두는 것이 좋다.

연산자는 피연산자(operand)의 개수에 따라 **단항 연산자**와 **이항 연산자**로 나뉘는데, 오버로딩을 할 때에도 연산자가 단항인지 이항인지를 고려해야 한다. 다음은 단항 연산자와 이항 연산자로 사용되는 `-`에 대해 연산자 오버로딩을 해본 코드이다.
```cpp
#include <iostream>
using namespace std;

struct point {
    double x;
    double y;
};

// 단항 연산자
point operator-(point A){
    point res;
    res.x = -A.x;
    res.y = -A.y;
    return res;
}

// 이항 연산자
point operator-(point A, point B){
    point res;
    res.x = A.x - B.x;
    res.y = A.y - B.y;
    return res;
}

int main(){
    point A = {3, 5}, B = {1, 2};
    point C = -A, D = A-B;
    cout << "C: (" << C.x << ", " << C.y << ")" << endl;
    cout << "D: (" << D.x << ", " << D.y << ")" << endl;
}
```
```
C: (-3, -5)
D: (2, 3)
```
연산자 오버로딩을 할 때에는 마치 함수를 정의하듯이 반환형(구조체 이름)과 연산자 종류, 그리고 괄호 안에 피연산자를 넣어준다. 단항 연산자는 피연산자를 한 개, 이항 연산자를 피연산자 두 개를 콤마로 구분해서 넣어준다. 이렇게 연산자 오버로딩을 하고 하면, 사용자 정의 자료형에 대해서도 연산자를 사용할 수 있게 된다.

구조체나 클래스 안에서 연산자 오버로딩을 하는 경우라면, 첫 번째 인자를 제외하고 정의한다. 첫 번째 인자를 입력하지 않아도 그 구조체의 객체를 가리킨다고 생각하면 된다. 다음은 구조체 안에서 연산자 오버로딩을 하여 앞선 예시와 동일한 연산자 오버로딩을 한 코드이다.
```cpp
struct point {
    double x;
    double y;
    
    point operator-(){
        point res;
        res.x = -x; // dot operator 없이 변수 명을 그대로 사용
        res.y = -y;
        return res;
    }
    
    point operator-(point B){
        point res;
        res.x = x - B.x;
        res.y = y - B.y;
        return res;
    }
};
```

## 2-4. 상속(Inheritance)
상속은 **어떤 클래스의 변수와 함수들을 그대로 물려받아 사용하고 싶을 때 사용**한다. 클래스를 상속하기 위해서는 상속받을 클래스의 이름 옆에 `:`와 접근 제한자, 그리고 상속할 클래스의 이름을 붙여주면 된다. 상속하는 클래스를 **부모 클래스(base class, super class)**, 상속받은 클래스를 **자식 클래스(derived class, sub class)**라고 부른다.

부모 클래스 앞에 오는 접근 제한자는 **제한자보다 접근 범위가 넓은 멤버를 모두 제한자로 바꾸어 상속한다는 의미**를 가진다. 예를 들어 private 상속을 하게 되면 public과 protected 모두 private보다 접근 범위가 넓기 때문에 부모 클래스의 모든 멤버가 private로 상속된다. 반대로 public 상속을 하게 되면 public보다 접근 범위가 넓은 것은 없기 때문에 부모 클래스의 멤버들이 기존에 정의된 상태 그대로 상속된다.

다음은 클래스 상속을 이용한 예시이다.
```cpp
#include <iostream>
#include <string>
using namespace std;

class Human{ // Base class
private:
    string name;
    int age;
public:
    Human(string _name, int _age): name(_name), age(_age) { }
    void printInfo(){
        cout << "Name: " << name << ", Age: " << age << endl;
    }
};

class Student: public Human { // Derived class, public inheritance
private:
    int grade;
    string major;
public:
    Student(string _name, int _age, int _grade, string _major): Human(_name, _age){ // Member initialization
        grade = _grade;
        major = _major;
    }
    void printInfo_S(){
        printInfo(); // Member function from the Base class is usable
        cout << " - Grade: " << grade << ", Major: " << major << endl;
    }
};

int main() {
    Student s("Park", 22, 2, "Biology");
    s.printInfo(); // Member function from the Base class is usable
    cout << "\n";
    s.printInfo_S();
}
```
```
Name: Park, Age: 22

Name: Park, Age: 22
 - Grade: 2, Major: Biology
```
이처럼 상속을 이용하면 기존에 정의된 클래스를 이용해서 보다 편리하게 새로운 클래스를 정의할 수 있다. 멤버 초기화를 이용해서 Base class의 멤버 변수들을 초기화하였다.

위 코드에서 `Student` 클래스의 `printInfo_S()` 함수는 부모 클래스에 있는 `printInfo()` 함수와 겹치지 않게 하기 위해 이름에 `_S`를 붙여주었다. 그런데 함수 구분하지 않고 그냥 덮어쓰고 싶다면 부모 클래스에 있는 함수의 이름을 그대로 사용하면 된다. 이를 **상속 오버라이딩(Inheritance overriding)**이라고 하는데, 부모 클래스에 이미 정의된 함수를 **재정의**한다는 의미이다.
```cpp
class Student: public Human {
private:
    int grade;
    string major;
public:
    Student(string _name, int _age, int _grade, string _major): Human(_name, _age){ // Member initialization
        grade = _grade;
        major = _major;
    }
    void printInfo(){
        Human::printInfo(); // 범위 지정 연산자(::)를 통해 부모 클래스의 함수를 호출할 수 있다.
        cout << " - Grade: " << grade << ", Major: " << major << endl;
    }
};
```


<br/>
# References
[1] [Geeksforgeeks, 'Structures in C++'](https://www.geeksforgeeks.org/structures-in-cpp/)  
[2] [Geeksforgeeks, 'Difference between C structures and C++ structures](https://www.geeksforgeeks.org/difference-c-structures-c-structures/?ref=rp)  
[3] [cplusplus, 'Data structures'](https://www.cplusplus.com/doc/tutorial/structures/)  
[4] [Stack Overflow, 'Structure Padding'](https://stackoverflow.com/questions/29813803/structure-padding)  
[5] [Geeksforgeeks, 'Structure Member Alignment, Padding and Data Packing'](https://www.geeksforgeeks.org/structure-member-alignment-padding-and-data-packing/)  
[6] [cplusplus, 'Classes'](http://www.cplusplus.com/doc/tutorial/classes/)  
[7] [Geeksforgeeks, 'Structue vs class in C++](https://www.geeksforgeeks.org/structure-vs-class-in-cpp/)  





