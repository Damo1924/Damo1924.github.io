---
title: "[C++] Stream & Buffer & Fast I/O"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Cpp
use_math: true

---

# 1. Stream & Buffer
C++에서의 Fast I/O에 대한 글을 보던 중, stream과 buffer라는 처음 보는 개념이 등장해서 공부하게 되었다.

C++프로그램은 파일이나 콘솔의 입출력을 직접 다루지 않고, **스트림(stream)**이라는 흐름을 통해 다룬다. 이때 스트림이란 운영체제에 의해 생성되는 실제의 입력이나 출력이 표현된 데이터의 흐름을 의미하며, **프로그램과 입출력 장치 사이에서 데이터를 중계하는 역할**을 한다. 스트림은 내부에 **버퍼(buffer)**라는 **임시 메모리 공간**을 가지고 있고, 이를 통해 입출력을 좀 더 효율적으로 처리할 수 있게 된다.

키보드에서 입력이 발생할 때마다 입력을 하나씩 버퍼로 전송하다가 버퍼가 가득 차거나 개행 문자가 나타나면 버퍼의 내용을 한 번에 프로그램으로 전달하는 방식으로 입력이 이루어진다. 이처럼 버퍼를 이용해서 입력을 하면 다음과 같은 장점이 있다.
- 문자를 묶어서 한 번에 전달하기 때문에 하나씩 프로그램으로 전달하는 것보다 빠르다.
- 문자를 잘못 입력했을 경우에 수정이 가능하다.

C++에서는 주로 `iostream` 헤더 파일에 있는 표준 입출력 클래스들인 `cin`과 `cout`을 통해 입력과 출력을 하는데, 이들은 각각 입력 스트림과 출력 스트림을 의미한다.
```cpp
std::cout << "Output";
```
: 이는 출력할 데이터인 "Output"을 삽입 연산자 `<<`을 통해 출력 스트림 `cout`에 삽입한다는 의미이다. 출력 스트림에 입력된 데이터는 스트림을 통해 출력 장치로 전달되어 출력된다.
```cpp
std::cin >> variable;
```
: 이는 입력된 데이터를 입력 스트림 `cin`에서 추출하여 `variable`이라는 변수에 저장한다는 의미이다.


<br/>
# 2. Fast I/O in C++
## 2-1. stdio와의 동기화 끊기 & cin과 cout을 untie하기
가장 보편적으로 사용하는 방식이다. 기본적으로 `<iostream>` 헤더 파일에서 제공하는 `cin`과 `cout`은 `<stdio.h>`에서 제공하는 `scanf`와 `printf`보다 느린 입출력 방식이다. 입력이 적다면 어느 것을 사용해도 상관없지만, 입력이 많으면 `cin`과 `cout`으로는 통과되지 않을 수도 있다. 그래서 다음의 두 줄의 코드를 추가해줌으로써 `cin`과 `cout`을 더 빠르게 작동하도록 만들어 줄 수 있다.

```cpp
std::ios_base::sync_with_stdio(false);
```
: C++의 cin/cout이 느린 이유는 **C의 입출력 스트림과 C++의 입출력 스트림의 동기화(synchronization)** 때문이다. 입출력 스트림이 동기화되어있다는 것은 **동일한 버퍼를 사용**한다는 것을 의미한다. 기본적으로 C++의 모든 표준 입출력 스트림은 동기화되어 있어, C 스타일의 입출력 방식(scanf, printf, ...)과 C++ 스타일의 입출력 방식(cin, cout)을 혼용해서 사용해도 우리가 예상한 결과를 얻을 수 있는 것이다.

그런데 위 코드를 실행하면 C의 입출력 스트림과 C++의 입출력 스트림의 **동기화가 끊어지게 된다.** 이는 **C++의 입출력 스트림들이 자신들만의 독립적인 버퍼를 가지게 되는 것을 의미**하며, 사용자의 입장에서는 마치 입력이 가속되는 효과를 얻는 것처럼 보이게 된다.

```cpp
std::cin.tie(NULL);
```
: 기본적으로 `cin`과 `cout`은 tie 되어있다. 앞서 설명한 버퍼의 개념을 통해 이를 이해할 수 있는데, **사용자가 cout을 이용해서 무언가를 출력한 뒤어 cin으로 입력을 받는다면 먼저 출력이 일어나고(flush, 버퍼가 비워짐) 입력을 받게 된다.** 즉, tied streams는 한 스트림에서 입출력이 이루어지기 전에 다른 스트림이 자동적으로 flush 됨을 의미한다. 입력과 출력을 한 번씩 하는 경우라면 아무런 상관도 없겠지만, 여러 테스트 케이스가 있어 입력과 출력이 반복적으로 이루어지는 경우에는 cin을 통해 입력을 받을 때마다 cout을 flush하기 때문에 시간이 오래 걸리게 된다.

위 코드는 **cin과 cout을 untie**하는 역할을 한다. 이러면 더 이상 출력이 먼저 이루어지지 않고, **출력 버퍼가 가득 찬 후에야 출력이 발생**하게 되고, 이는 우리의 코드가 조금 더 빨리 작동하게 만들어 준다.

## 2-2. getchar()을 이용한 입력 함수 구현하기
`getchar()` 함수는 `<stdio.h>`, `<cstdio>` 헤더 파일에 정의된 함수로, **표준입력으로부터 입력받은 문자를 정수형(int)으로 하나씩 반환하는 함수**이다. 문자 하나씩 입력을 받기 때문에 다른 표준입력 함수들에 비해 더 빠르다. 이를 이용해서 임의의 정수를 빠르게 입력받는 함수를 만들 수 있다.
```cpp
int readInt()
{
    int ret = 0, flg = 1;
    char now = getchar();
    
    while (now == 10 || now == 32) now = getchar();
    if (now == '-') flg = -1, now = getchar();
    while (now >= 48 && now <= 57) {
        ret = ret * 10 + now - 48;
        now = getchar();
    }
    return ret;
}
```
- **ret**: 입력받은 정수
- **flg**: 양수이면 1, 음수이면 -1
- **now**: `getchar()`을 통해 한 문자씩 입력받아 저장

첫 번째 while 문은 숫자 입력 전에 들어오는 개행(10)이나 공백(32)을 건너뛰도록 한다. 그 다음에 위치한 if 문은 입력이 음수인 경우 `flg`를 -1로 갱신하는 역할을 한다. 마지막 while 문은 숫자 입력('0': 48 ~ '9': 57)에 대해 `ret`를 갱신해준다. 가끔 vertical tab와 같이 예상하지 못한 whitespace가 들어오는 경우를 제외하고는 위 함수를 이용해서 입력을 받을 수 있다.

**비트연산자**를 이용하면 좀 더 빠른 입력 함수를 만들 수 있다.
```cpp
int readInt()
{
    int t, r = getchar() & 15;
    while ((t = getchar()) & 16) r = r * 10 + (t & 15);
    return r;
}
```
: `getchar()` 함수를 통해 0부터 9까지의 숫자 문자들이 48부터 57까지의 정수로 반환되는데, 48은 2진법으로 110000으로 나타낼 수 있다. 즉, `getchar() & 15`로부터 0부터 9까지의 숫자를 바로 얻을 수 있고, `getchar() & 16`은 숫자라면 1이지만 개행(10)이나 공백(32)의 경우에는 0이 되어 while 문이 종료된다. 다만, 위 코드는 음이 아닌 정수만 받아올 수 있음에 유의하자.

## 2-3. 직접 버퍼를 만들고 읽어오는 방법
`getchar()`가 다른 표준입력 함수(scanf, cin)에 비해 빠르긴 하지만, 결국 한 번에 한 문자씩 입력 스트림의 버퍼에서 읽어오는 것이기 때문에 직접 버퍼를 만들어서 읽어오는 것이 더 효율적이다. 이를 구현하기 위해서는 `fread()`를 이용해야 한다.

`fread()`는 파일을 읽어올 때 사용하는 함수로, 다음과 같은 구조를 가지고 있다.
```cpp
size_t fread(
    void *buffer,
    size_t size,
    size_t count,
    FILE *stream
);
```
- **buffer**: 데이터를 저장할 문자열 주소
- **size**: 읽어올 데이터의 크기
- **count**: 읽어올 데이터의 개수
- **stream**: 읽을 파일의 포인터

`fread()`는 입력 *stream*으로부터 *size* byte의 데이터 *count*개를 읽어온 후, *buffer*에 저장한다. 이를 이용해서 `getchar()` 대신 사용할 수 있는 함수를 만들 수 있다.
```cpp
char buf[1 << 17];

char read() {
    static int idx = 1 << 17;
    if (idx == 1 << 17) {
        fread(buf, 1, 1 << 17, stdin);
        idx = 0;
    }
    return buf[idx++];
}
```
- **idx**: 정적(static) 변수로, buffer에서 반환할 데이터의 index를 의미
- **buf**: 1 << 17 크기의 문자 배열(buffer 역할)
- **stdin**: 표준입력(standard input)

가장 처음 read()가 호출되면, `fread()`를 통해 입력버퍼로부터 1 << 17 byte의 데이터를 받아와서 자체 버퍼 buf에 저장한다. 그 후 `idx = 0`으로 갱신해서 buf의 첫 번째 원소부터 읽어나간다. 만약 버퍼를 끝까지 읽었다면(idx = 1 << 17), 다시 입력버퍼로부터 1 << 17 byte의 데이터를 받아와서 자체 버퍼에 저장하는 과정을 반복한다. 이제 이 `read()` 함수를 2-2에서 구현한 `readInt()` 함수에서 `getchar()` 대신 써주면 된다.

## 2-4. 추가적인 방법들
위에서 다룬 방법들보다 더 빠른 입력을 원한다면, `<unistd.h>` 헤더 파일에 있는 `syscall` 함수를 사용하거나 리눅스에서 직접 하드웨어에 접근하는 `mmap` 함수를 사용하면 된다. 다만 아직 컴퓨터나 C++ 언어에 대한 지식이 많이 부족한 내가 공부하기에는 조금 벅찬 것 같아 추후에 기회가 된다면 더 공부해보도록 하겠다.


<br/>
# References
[1] [talALGO, 'Fast I/O'](https://panty.run/fastio/)  
[2] [TCPschool, '스트림과 버퍼'](https://tcpschool.com/cpp/cpp_io_streamBuffer)  
[3] [stackoverflow, 'Significance of ios_base::syne_with_stdio(flase); cin.tie(NULL);'](https://stackoverflow.com/questions/31162367/significance-of-ios-basesync-with-stdiofalse-cin-tienull)  
[4] [Microsoft, 'fread'](https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/fread?view=msvc-160)  
