---
title: "할당 문제(Assignment problem)과 헝가리안 알고리즘(Hungarian algorithm)"
toc: true
toc_label: "On this page"
toc_icon: "chevron-right"
categories:
  - Algorithm
use_math: true
comments: true

---

`Tags` Assignment Problem, MCMF, SPFA

이번 포스팅의 주제인 헝가리안 알고리즘은 커녕 SPFA와 MCMF에 대해서도 알지 못했던 내가 어떻게 헝가리안 알고리즘에 대해 공부할 생각을 하게 되었는지부터 이야기를 해야할 것 같다.

비트마스크 기법을 적용한 DP를 공부하면서 [백준 1131. 할 일 정하기 1](https://www.acmicpc.net/problem/1311) 문제를 풀었는데, 유난히 빠르게 푼 분들의 코드를 보니 헝가리안 알고리즘이라는 것을 사용하고 있었다.

이 문제를 처음에 보았을 때도 이분 매칭 문제랑 비슷하다는 생각을 했었는데, 실제로 그러한 알고리즘이 있다는 것을 알게 되니 빨리 공부하고 싶었다.

그런데 조금 찾아본 결과, 헝가리안 알고리즘은 MCMF보다 빠르게 할당 문제를 풀 수 있는 방법이라고 해서 먼저 [MCMF]()에 대해서 공부하려했고, 그러다보니 [SPFA]()에 대해서도 공부하게 된 것이다.

그렇게 먼 길을 돌아 대망의 헝가리안 알고리즘에 이르렀다.

지금부터 **할당 문제**가 무엇이고, 할당 문제를 해결하는 **헝가리안 알고리즘**에 대해 알아본 후 직접 문제를 풀어볼 것이다.

## 1. Assignment Problem

할당 문제(assignmnet problem)은 다음과 같은 문제를 말한다.

> N명의 직원과 M개의 작업이 있다.
> 
> 모든 직원은 M개의 작업을 전부 수행할 수 있는데, 각 직원마다 각 작업을 하는데 필요한 비용이 다르다.
> 
> 모든 직원이 최대 하나의 작업을 할 수 있을 때, 최대한 많은 작업을 할 수 있도록 만들고 싶어한다.
> 
> 이때 전체 비용이 최소가 되도록 직원에게 작업을 할당하는 방법을 구하여라.

이때 직원의 수가 더 많다면 각 직원이 작업을 하는데 필요한 비용이 0인 작업을 (N-M)개 더 추가하고, 작업의 수가 더 많다면 모든 작업을 비용 0으로 수행할 수 있는 직원 (M-N)명을 추가하자.

<img src="https://user-images.githubusercontent.com/88201512/146673091-19b467b3-8842-4fdc-9040-ccf55278a803.jpg" width="70%" height="70%">

이렇게 직원의 수와 일의 수를 동일하게 만들 수 있으므로, 위 문제는 다음과 같이 일반화가 가능하다.

> 직원의 집합을 I, 작업의 집합을 J라고 하자. ($\left\vert I \right\vert = \left\vert J \right\vert$)
> 
> 어떤 직원 $i \in I$가 작업 $j \in J$를 처리할 때 필요한 비용을 $c(i, j)$라고 한다.
> 
> **I에서 J로 가는 일대일 대응(bijection)** $f: I \to J$ 중 필요한 비용의 합이 가장 작은 것을 구하여라.

즉, $\sum_{i \in I} c(i, f(i))$가 최소가 되는 $f$를 구하는 문제가 된다.

앞서 본 그림과 같이 이분 그래프(bipartite graph)로 생각하면, 모든 직원이 모든 작업을 할 수 있으므로 **완전 이분 그래프(complete bipartite graph**가 된다.

이때 직원의 수와 작업의 수가 동일하므로 우리는 **완전 이분 그래프에서 비용의 합이 최소가 되는 Perfect Matching을 찾는 문제**라고 할 수 있다.

<br/>

## 2. Solving with MCMF

앞서 이야기했듯이, 할당 문제는 MCMF 문제로 바꾸어서 해결할 수 있다.



<br/>

## References

[1] [WIKIPEDIA, 'Assignment problem'](https://en.m.wikipedia.org/wiki/Assignment_problem)  
[2] [WIKIPEDIA, 'Hungarian algorithm'](https://en.m.wikipedia.org/wiki/Hungarian_algorithm)  
[3] [Gazelle and Computer Science, '할당 문제 & 헝가리안 알고리즘 (Assignment Problem & Hungarian Algorithm)'](https://gazelle-and-cs.tistory.com/29)  
