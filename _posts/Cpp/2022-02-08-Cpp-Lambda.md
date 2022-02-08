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

맨 앞에 있는 대괄호 `\[\]`는 **개시자(introducer)**라고 부르며, 괄호 사이에 외부 변수를 넣으면 해당 변수를 람다 함수 내부에서 사용할 수 있게 해준다.

두 번째로 소괄호 `()` 안에는 함수가 전달받을 **인자(parameter)**들이 들어간다.

세 번째로는 함수의 **반환 타입(return type)**을 화살표 `->` 다음에 적어준다.(반환 타입이 `void`이면 생략 가능)

마지막으로 중괄호 `{}` 안에는 함수의 내용(statement)가 들어간다.

람다 함수는 두 가지 형태로 선언할 수 있는데, 아래와 같이 이름이 없는 형태와

```cpp
sort(v.begin(), v.end(), [](int i, int j) -> bool { return i > j; });
```





## References

[1] [모두의 코드, '씹어먹는 C++ 토막글 2. 람다(lambda) 함수'](https://modoocode.com/196)  
[2] 





