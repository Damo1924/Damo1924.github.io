---

title: "[C++] Lambda function"

toc: true

toc_label: "On this page"

toc_icon: "chevron-right"

categories:

  - Cpp

use_math: true

comments: true

---

## 1. Why do we have to use the Lambda Function?

코딩을 하다보면 함수 내에 함수를 정의하고 싶은 경우가 생긴다.

예를 들어 아래와 같은 함수를 구현하는 상황을 생각해보자.

```cpp
int f(vector<int>& v, int k)
{
    for(int i = 0; i < k; i++)
    {
        // (1)
        sort(v.begin(), v.end(), cmp);
        // ...
    }
    // ...
}
```

정렬 기준에 해당하는 비교함수 `cmp()`가 지역변수인 `i`에 따라 변한다면, (1) 위치에 정의하면 깔끔한 코드가 된다.

하지만 C++는 함수 내에 함수의 구현을 지원하지 않기 때문에 어쩔 수 없이 `i`를 전역변수로 선언하고, `cmp()` 함수를 외부에 정의해서 사용해야한다.

이렇게 되면 한눈에 함수 `f`가 어떤 기능을 하는지 알아보기 힘들뿐더러 코드도 깔끔하지 않다는 단점이 발생한다.

이럴 때 사용하는 것이 바로 **람다(lambda) 함수**로, 깔끔하고 보기 좋은 코드를 짜는데 굉장히 유용한 도구이다.

<br/>

## 2. Lambda Function

람다는 다음과 같이 4개의 부분으로 구성된다.

<center><img src="" width="60%" height="60%"></center>

맨 앞에 있는 대괄호 `[]`는 **개시자(introducer)**라고 부르며, 괄호 사이에 외부 변수를 넣으면 해당 변수를 람다 함수 내부에서 사용할 수 있게 해준다.

두 번째로 소괄호 `()` 안에는 함수가 전달받을 **인자(parameter)**들이 들어간다.

세 번째로는 함수의 **반환 타입(return type)**을 화살표 `->` 다음에 적어준다.

반환 타입이 `void`이거나 함수가 단일 return문인 경우에는 반환 타입을 생략해도 된다.

마지막으로 중괄호 `{}` 안에는 함수의 내용(statement)가 들어간다.

람다 함수는 이름이 없는 임시적인 객체와

```cpp
sort(v.begin(), v.end(), [](int i, int j) { return i > j; });
```

이름이 있는 객체

```cpp
auto cmp = [](int i, int j) { return i > j; };
sort(v.begin(), v.end(), cmp);
```

두 가지 형태로 선언이 가능하다.

이렇게 선언된 객체들은 마치 함수 객체(function object)처럼 행동하기 때문에 일반적인 함수처럼 사용하는 것도 가능하다.

```cpp
auto sum = [](vector<int>& v) -> int {
    int res = 0;
    for(int i = 0; i < v.size(); i++) res += v[i];
    return res;
};
cout << sum(vec) << endl;
```

<br/>

## 3. Capture

람다 함수의 가장 중요한 기능인 **캡처(capture)**에 대해서 알아보자.

지금까지 본 간단한 예시들에 나온 람다 함수들은 사실 일반적인 함수로 정의해도 큰 불편함이 없다.

예시로 든 람다 함수들은 필요한 변수들을 모두 인자로 받는 함수들이었기 때문이다.

이제 맨 처음에 예시로 든 상황을 다시 생각해보자.

```cpp
int f(vector<int>& v, int k)
{
    for(int i = 0; i < k; i++)
    {
        sort(v.begin(), v.end(), cmp);
        // ...
    }
    // ...
}
```

우리는 지역변수 $i$에 따라 달라지는 비교 함수 `cmp()`를 구현하고자 한다.

그러기 위해서는 인자로 $i$를 넘겨주어야하지만, `sort()`의 비교 함수에 알맞은 형태로 구현해야해서 불가능하다.

이럴 때 필요한 것이 바로 캡처이다.

캡처는 **인자로 전달하지 않아도 외부 변수들을 람다 함수 내부에서 사용할 수 있도록** 해주는데, 다음과 같이 4가지 형태가 존재한다.

1. `[&]() { }`: 외부의 모든 변수들을 레퍼런스로 가져온다.
2. `[=]() { }`: 외부의 모든 변수들을 값으로 가져온다.
3. `[=, &x, &y] { }`, `[&, =x, =y] { }`: 외부의 모든 변수들을 값/레퍼런스로 가져오되, `x`와 `y`만 레퍼런스/값으로 가져온다.
4. `[x, &y] { }`: 지정한 변수들을 지정한 바에 따라 가져온다.

여기서 캡처가 되는 개체들은 **람다 함수가 정의된 위치에서 접근이 가능한 개체들**이다.

즉, 앞선 예시에서 $i$를 캡처하면 굳이 인자로 전달하지 않아도 람다 함수 내에서 $i$를 사용할 수 있게 되는 것이다.

<br/>

## References

[1] [모두의 코드, '씹어먹는 C++ 토막글 2. 람다(lambda) 함수'](https://modoocode.com/196)  
[2] [Microsoft, 'C++ 람다 식'](https://docs.microsoft.com/ko-kr/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170)





