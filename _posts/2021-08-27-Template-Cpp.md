# 1. Template
> To **pass datatype as a parameter** so that we don't need to write the same code for different datatypes.

C++를 이용해서 코딩을 하다보면 동일한 함수를 자료형만 다르게 만들어야하는 경우가 있다. 다음 예시를 보자.
```cpp
int sumInt(int x, int y) {
    return x + y;
}

double sumDouble(double x, double y) {
    return x + y;
}
```
정수형과 실수형에 대한 덧셈 결과를 반환하는 함수를 따로 정의해주었다. 그런데 템플릿을 이용하면 다음과 같이 깔끔하게 표현할 수 있다.
```cpp
template <typename T>
T _sum(T x, T y) {
    return x + y;
}
```
단순히 코드의 길이가 짧아졌을 뿐만 아니라 함수 이름도 자료형에 따라서 따로 정할 필요 없이 헷갈리지 않게 사용할 수 있다는 것을 알 수 있다.

이렇게 템플릿에 대해 알아두면 
템플릿(template)은 
