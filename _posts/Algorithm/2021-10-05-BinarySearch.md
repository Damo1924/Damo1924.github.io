---
title: "이분 탐색(Binary Search) 알고리즘"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

## 1. Binary Search Algorithm

이분 탐색 알고리즘은 정렬된 리스트에서 탐색 범위를 절반씩 줄여나가며 데이터를 탐색하는 알고리즘이다.

탐색할 범위(`start` ~ `end`)의 중앙(`(start + end) / 2`)값과 찾으려는 값을 비교해가며 탐색한다.

정렬되어 있는 데이터에서만 사용할 수 있다는 한계가 있지만, 탐색 범위를 매번 절반으로 줄이기 때문에 $O(\log N)$의 시간복잡도를 가진다는 장점이 있다.

매우 간단하면서도 강력한 알고리즘이기 때문에 다양한 문제에서 다양한 형태로 활용된므로 꼭 알아두자.

구현하는 방법으로는 재귀함수와 반복문이 있는데, 재귀함수 호출에 시간이 소요된다는 점으로 인해 PS에서는 일반적으로 반복문을 사용한다.

**[재귀함수로 구현한 이분 탐색 알고리즘]**

```cpp
int binarySearch (int start, int end, int x)
{
    if (start > end) return -1;
    
    int mid = (start + end) / 2;
    if (A[mid] < x) return binarySearch(start, mid - 1, x);
    else if (A[mid] > x) return binarySearch(mid + 1, end, x);
    else return mid;
}
```

**[반복문으로 구현한 이분 탐색 알고리즘]**

```cpp
int start = 0, end = N - 1, idx = -1;
while (start <= end)
{
    int mid = (start + end) / 2;
    if (A[mid] < x) start = mid + 1;
    else if (A[mid] > x) end = mid - 1;
    else
    {
        idx = mid;
        break;
    }
}
```


<br/>
## 2. 관련 문제

다음 문제들은 이분 탐색을 응용해서 해결할 수 있는 대표적인 문제들이다.

이 문제들을 풀면서 사용할 이분 탐색의 응용을 Parametric Search라고도 하는데, 이는 최댓값이나 최솟값을 구하는 문제에서 유용하게 사용될 수 있다.

---

### [백준] 1300. K번째 수

[백준 1300. K번째 수 문제 링크](https://www.acmicpc.net/problem/1300)

$10^5$보다 작거나 같은 자연수 N이 주어질 때, N x N 배열 A의 각 성분은 다음과 같이 주어진다.

`A[i][j] = i * j`

배열 A의 모든 성분들을 일차원 배열 B에 넣고 오름차순으로 정렬했을 때, `B[k]`의 값을 구하는 문제이다.

(단, 배열 A와 B의 인덱스는 1부터 시작하며, k는 $10^9$보다 작거나 같다.)

**[풀이]**

배열 B가 정렬되어 있으므로 $N^2$ 이하의 어떤 자연수 $n$에 대해 $n$이 몇 번째 원소인지는 다음과 같은 방법으로 찾을 수 있다.

배열 A에서 각 열에 대해 $n$보다 작거나 같은 숫자의 개수를 구해서 모두 더해주면 마지막 $n$의 인덱스를 구할 수 있다.

주의해야하는 점은 $n \leq N$인 경우와 $n > N$인 경우를 구분해야한다는 것이다.

<img src = "https://user-images.githubusercontent.com/88201512/135961393-f678fd5b-e6ec-48ff-b4b2-b090e7b39af4.jpg" width = "70%" height = "70%">

나는 위 그림처럼 `min()`을 이용해서 두 케이스에 대해 모두 사용할 수 있도록 구현하였다.

```cpp
int cnt = 0;
for (int i = 0; i < min(n, N); i++) cnt += min(n / i, N);
```

이렇게 구한 `cnt`보다 `k`가 작거나 같다면 더 작은 `n`에 대해서 탐색을 이어나가고, `cnt`보다 `k`가 크다면 더 큰 `n`에 대해서 탐색을 해나가면 된다.

여기서 이분 탐색 알고리즘을 이용해서 구해지는 `n`이 구하고자 하는 값이 된다.

전체 코드는 다음과 같다.

```cpp
#include <iostream>
using namespace std;
typedef long long ll;

int N, k;

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> N >> k;

	int start = 1, end = (N > 33000) ? 1000000000 : N * N, n = 0;

	while (start <= end)
	{
		int mid = (start + end) / 2;

		ll cnt = 0;
		for (int i = 1; i <= min(mid, N); i++) cnt += min(mid / i, N);

		if (cnt >= k)
		{
			end = mid - 1;
			n = mid;
		}
		else
		{
			start = mid + 1;
		}
	}

	cout << n;
}
```

---

### [백준] 2631. 숫자구슬

[백준 2631. 숫자구슬 문제 링크](https://www.acmicpc.net/problem/2613)

100 이하의 자연수가 적혀 있는 숫자 구슬 N개가 일자로 놓여 있다.

이 숫자 구슬들을 M개의 그룹으로 나누었을 때 각각의 그룹에 있는 숫자들의 합의 최댓값이 최소가 되도록 하려 한다.

이때 위 값을 구하고 각 그룹에 몇 개의 구슬이 있어야 하는지를 출력하는 문제이다.

(단, 각 그룹에는 적어도 하나의 구슬이 있어야하며, 그룹의 합의 최대값이 최소가 되도록 하는 경우가 둘 이상이라면 그 중 하나만 출력한다.)

**[풀이]**

이분 탐색을 이용해서 그룹의 합의 최댓값 중 최솟값을 구해보자.

이분 탐색을 사용하기 위해 적절한 조건 함수를 만들어주어야 하는데, 해당 함수는 다음과 같은 기능을 해야한다.

- 각 그룹의 합의 최댓값을 입력받아 해당 값을 넘지 않도록 구슬들을 그룹으로 나눈다.
- **각 그룹에 적어도 하나의 구슬이 있어야하기 때문에 적절히 그룹을 나눈다.**
- 만약 나누어진 그룹의 개수가 M과 같으면 각 그룹에 있는 구슬의 개수를 저장한다.
- 만약 나누어진 그룹의 개수가 M보다 작거나 같으면 true, 아니라면 false를 반환한다.

이와 같은 함수를 구현했다면, 이분 탐색의 초기 조건을 구해준다.

그룹을 나누는 것이 가능한 값들 중 가장 작은 것은 숫자 구슬들 중 가장 큰 숫자이고, 가능한 값들 중 가장 큰 것은 모든 숫자 구슬들의 합이다.

위 값을 구해 각각 `start`, `end`로 두고 이분 탐색을 사용하면 답을 구할 수 있다.

전체 코드는 다음과 같다.

```cpp
#include <iostream>
using namespace std;

int N, M, A[300], B[300]; // A: 숫자 구슬에 적힌 숫자들의 배열, B: 각 그룹에 속해 있는 구슬의 개수를 저장할 배열

bool check (int m)
{
    int a_idx = 0, b_idx = 0, tmp[300];
    while (1)
    {
        // 각 그룹에 적어도 하나의 구슬이 있어야하므로 남은 구슬의 개수와 남은 그룹의 개수가 동일하면 각 그룹에 하나씩 넣는다.
        if (N - a_idx == M - b_idx)
        {
            while (b_idx < M) tmp[b_idx++] = 1;
            break;
        }
        
        // m을 넘지 않게 그룹을 형성한다.
        int sum = 0, cnt = 0;
        while (sum <= m && a_idx < N)
        {
            sum += A[a_idx++];
            cnt++;
        }
        
        // 마지막 그룹은 따로 처리
        if (sum <= m && a_idx == N)
        {
            tmp[b_idx++] = cnt;
            break;
        }
        
        tmp[b_idx++] = cnt - 1; // 위에서 구한 그룹에 속하는 구슬의 개수를 저장
        a_idx--;
    }
    
    if (b_idx == M) // 그룹의 개수가 정확히 M개이면 배열 B에 저장
        for (int i = 0; i < M; i++) B[i] = tmp[i];
    return b_idx <= M; // 그룹의 개수가 M보다 작거나 같으면 true, 아니면 false를 반환
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    cin >> N >> M;
    int start = 0, end = 0;
    for (int i = 0; i < N; i++)
    {
        cin >> A[i];
        if (start < A[i]) start = A[i];
        end += A[i];
    }
    
    int mid, ans = 0;
    while (start <= end)
    {
        mid = (start + end) / 2;
        if (check(mid)) // 조건 함수가 true를 반환하면 현재 값을 저장하고, 더 작은 값이 있는지 탐색
        {
            end = mid - 1;
            ans = mid;
        }
        else start = mid + 1; // 조건 함수가 false를 반환하면 조건을 만족하는 값을 찾기 위해 더 큰 값을 탐색
    }
    
    cout << ans << "\n";
    for (int i = 0; i < M; i++) cout << B[i] << " ";
}
```
