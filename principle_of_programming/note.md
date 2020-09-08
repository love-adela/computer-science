# [Principles of Programming](https://sf.snu.ac.kr/courses/)

* [허충길 교수님](http://sf.snu.ac.kr/gil.hur)
  * Research Topics
    * Software Verification: 프로그램이 수학적으로 엄밀하게 verified되었는지 확인
    * Low-level Language Semantics(C/C++/LLVM/Rust)
    * Relaxed-Memory Concurrency
* 자료: https://github.com/snu-sf-class/pp202002
* 준비물 : laptop

## Overview

technical한 내용보다는 사용자 관점에서 이해하기 좋은 원리를 가르치려고 한다.

1. Functional Programming with Function Applications
   * Functional Programming이 맞다고 말하는게 아니라, 이런 것도 있다는 것을 알려줌.
2. Objected Oriented Programming
3. Type Classes for Interface
    > Type class가 거의 모든 OOP보다 나아요.
4. Imperative Programming with Memory Updates

## Imperative vs Functional Programming

### Imperative Programming

* 한 줄 한 줄 실행하는 방식
* 메모리에서 값을 읽어옴 -> 계산 -> 다시 메모리에 씀
* 반복은 기본적으로 loop으로 한다.
* 프로시져 (A하고나서 B를 하고 그 다음 C를 해라.)
* 컴퓨터 수준에서 **how to do**를 구체적으로 명시해준다.
* Imperative 프로그래밍을 할 때는 기계가 이해하는 것을 사람이 제어할 수 있기 때문에 efficent 하다. 사람에 따라서는 '기계적으로 짜는 것이 더 생각하는게 더 쉽다'고 여기는 사람도 있음.
* *좌향좌 우향우 앞으로 5걸음 걸어!*
* Comment로 코드의 목적 등을 기술함.

```
// Imperative Programming Example
// 1부터 n까지의 합을 구체적으로 구함
// 자세히 보지 않는 이상 Summation하는 것이 잘 안 보인다.
sum = 0;
i = n;
while (i >0) {
    sum = sum + i;
    i = i -1;
}
```

### Functional Programming

* 기본적으로 계산의 결과를 declarative하게 **what to do**를 기술하는 것이 주 목적.
* 메모리 없이 순전히 값의 흐름으로 연산을 할 수 있다. 연산할 때마다 변수 선언을 하지 않으니까.
* Composition of function applications(함수 합성)이 가능하다.
* 반복은 recursion call로 이뤄짐.
* 컴파일러가 정말 많은 일을 한다. 컴파일러가 컴퓨터가 이해하게끔 how to do를 generate해주기 때문이다. 컴파일러가 똑똑해야 한다.
* 훨씬 쉽게 빨리 짤 수 있고, 오류도 적기 때문에 safe code를 작성하게 된다.
* 메모리를 조금 사용하고 빨리 돌아가야 하는 코드에는 부적합하다. 메모리를 얼마나 사용해야 하는지 모르는 등의 문제가 있기 때문에.
* *물 떠와!*

* Functional하게 짜면 훨씬 길어지고 복잡해지는 문제가 생기기도 한다. 예를 들어 Union Find 알고리즘을 짤 때는 Imperative하게 짜는 것이 더 간단하다.

```
// Functional Programming
def sum(n) =
    if (n <= 0)
        0
    else
        n + sum(n-1)
```

### Both Imperative & Functional Style Supported

* 많은 언어가 Imperative 스타일과 Functional 스타일로 짤 수 있다는 특징이 있다.
  * More imperative : Jave, Javescript, C++, Python, Rust, ...
    * 러스트로 프로그래밍 하는 사람이 프로그래밍을 잘 짜는 사람이 될 수도 있다.
  * More functional : OCaml, SML, Lisp, Scheme, ...
  * Middle : Scala
  * Purely functional : Haskell
    * 메모리를 지원하지 않는 것일 뿐이지 imperative하게 짤 수는 있음.
    * Monadic programming : 효율은 functional이지만, 메모리 없이 메모리를 읽고 쓰는 imperative 프로그래밍을 흉내 낼 수 있게 됨.

* 하나의 알고리즘이나 코드에서 imperative하거나 functional한 스타일을 동시에 사용할 수 있음.

## Why Scala?

* Imperative, Functional 스타일을 둘다 지원한다.
* OOP와 Typeclass를 둘다 지원한다다
* Java와 호환이된다. Java 라이브러리를 다 쓸 수 있고 서로 링크할 수 있다.
* 프로그래밍은 협업. 남이 이해할 수 있는 코드를 짜는 것이 중요하기 때문에 스칼라를 활용하는 것도 좋은 방법임.

## Object Oriented Programming

* OOP: 프로그램을 짤 때 모듈별로 잘게 쪼개서 추상화 등 목적에 맞게금 쓰이도록 프로그래밍을 관리할 수 있음.
* OOP의 Classes / Objects는 data + methods(ie, functions)
* 인터페이스와 구현을 분리할 수 있다. 사용자에게 구현 디테일을 숨기고 프로그래밍이 가능하게 한다.
  * 핸들을 돌리고, 앞으로 나가는 등의 조작을 할 뿐이지 차가 어떻게 그런 작동하는지는 다 몰라도 된다. 현대차, 테슬라, 포르쉐 등 어떤 차를 몰더라도 기본적인 조작은 같 듯, 코드 재활용을 할 수 있다. 구현을 바꿔가며 Linking이 가능함.

```
class Point(x:Int, y:Int) {
    //data
    val px: Int = x
    val py: Int = y
    //mehotds
    def plus(q:Point): Point =
        new Point(px +q.px, py+q.py)
    def print(): Unit =
    println("Point:(" + px + "," + py + ")")
}

abstract class Point(x:Int, y:Int) {
    // abstraction. 내부에서 어떻게 구현되는지는 알리지 않는다.
    def plus(q:Point): Point
    def print(): Unit
}

val p1: Point = new Point(3, 4)
val p2: Point = new Point(1, 10)
val p3: Point = p1.plus(p2)
p3.print()
```

## 결론

인터페이스를 많이 쓰는게 프로그래밍을 잘 할 수 있게 하기도 한다. 큰 회사에서는 각각의 팀이 구체적이고 깊은 내부 코드를 공유하지 않고, 인터페이스만 공유하는 식으로 협업을 하기도 한다. 의존하면 안되는 동작에 실수로 의존하게 되는 경우를 막을 수 있다.

> Computer Science is an abstraction of mechanization

CS는 복잡한 영역을 다루게 되고, 점점 더 도메인이 고도화될 거기 때문에 사람들이 추상적인 상태(high level)에서 프로그래밍을 하게금 하는 것이 CS 학문의 목적이 된다.

### 질의응답

Q. Unit은 뭔가요?

A. 가능한 값이 하나 뿐인 Singleton set. 값을 주긴 줘야 하는데 주고 싶지 않을 때는 Unit을 사용한다.
(Python NoneType과 비슷함.) 정보량이 0. Unit의 타입은 하나 밖에 없는데, 이를 리턴하는 수 밖에 없다.

Q. C에서의 void와 같나요?

A. C에서 void를 리턴하는게 스칼라에서 Unit을 리턴하는 것과 같은데, void(공집합)라는 이름이 적절하지 않다.

void라는 이름은 마치 공집합을 반환한다는것처럼 해석되는데, 만약 정말로 공집합을 리턴한다면 이건 가능한 값이 없는 타입을 리턴한다는 뜻이다. 예를들어 exit() 함수나 exec() 함수처럼 리턴을 안하는 함수가 여기에 해당한다. `a = exit(1)`, `a = exec("asd")` 이렇게 코딩할경우 `a`에는 값이 절대 안들어옴. 이런 타입이 공집합이고, 스칼라에선 scala.Nothing이라고 부른다. Bottom type이라고 부름.

## Part 1. Functional Programming with Function Applications

### 1.1 Values, Names, Functions, and Evaluations

* value: primitive하기도 하고 새로운 데이터타입에 따라 정의되기도 한다.
* type: set of values
  * 미리 정의된 타입 :
    * int : {-214783648, ..., -1, 0, 1, ..., 2147483647} // 32-bit
    * double : 64bit floating point numbers // real numbers in practice
    * boolean: {true, false}
    * string
    * ...
  * 모든 expression에 타입을 붙일 수 있다.
    ```
    foo -> ((x:Int)x):Int
    ```
* Expressions
  * values, names, primitive operations(`+`, `*`), 등의 조합
* Name -> 중요
  * 복잡한 Expression이 있을 때 value를 빼서 이름을 붙이는 것.
  * identify가 목적이다.
    * expression의 이름은 a, b
        ```
        def a = 1 + (2 + 3) // 6
        def b = 3 + a * 4  // 27
        b
        ```
  * 본질적으로 Function에서 파라미터를 전달하는 등의 역할을 하기도 한다.
  * 중요! a 라는 이름을 붙이면 바꿀 수 없다. storage가 아니기 때문이다.
    ```
    val a: Int = 1+2 // a는 1+2를 가리킨다. (저장x)
    ```
  * b가 가리키는 것이 value일수도 있고 expression일 수 있다. 모드가 따로 있으므로 프로그래머가 취사선택하여 expression으로 표현할 수 있다.

* 메모
  * functional programming에서는 같은 변수에 값을 덮어 씌우는 방식을 사용하지 않는다. 이는 imperative programming에 해당함.

* Evaluation
  * Reducing an expression into a value
  * Strategy
    * Take a name and operator (outer to inner)
    * (name) Replace the name with its associated expression
    * (name) Evaluate the expression
    * (operator) Evaluate its operands (left to right)
    * (operator) Apply the operator to its operands
  * Example
        ```
        // b를 만나기 전까지 5를 계산
        // b를 definition에 의해 (3+a*4)로 replace.
        // 다시 a를 definition에 의해 replace.
        5 + b ~ 5 +(3+a*4) ~ 5 +(3+(1+(2+3))*4) ~ ... ~ 32
        ```
  * operation을 할 때의 우선순위를 명시적으로 정의하기 때문에 괄호를 사용해야 한다. 이외로는 우선순위가 내부적으로 정해져있음.

## 1.2 Functions and Substitution

* Functions -> 중요
  * Name을 generalize한 것으로 확장된 개념임.
  * 파라미터가 있는 Expression을 가리키는 이름임.
  * Name에 바인딩할 수 있다.
    * Name 이기 때문에 바뀌지 않는다.
    * storage 아님.
        ```
        // f는 expression을 가리키는 이름.
        def f(x:Int): Int = x + a
        ```
  * 패턴을 만드는 것

* substitution
  * 함수형 프로그래밍의 핵심

* Evaluation by substitution
  * ...
  * (function) Evaluate its operands (left to right)
  * (function)
    * Replace the function application by the expression of the function
    * Replace its parameters with the operands

## 1.3 Simple Recursion

Imperative programming에서 loop이 없으면 실행시키고 싶은 횟수만큼 코드를 반복해서 써야 한다. 조금씩 다른 계산이 되기 때문에 변수에 값이 업데이트 되는 특징이 있다.

* Recursion
  * Use X in the definition of X
  * Powerful mechanism for repitition
  * Nothing special but just rewriting
  * 패턴을 반복시키는 것

```
// 함수 이름이 함수 본인 body에 다시 나타날 수 있다.
def sum(n:Int): Int =
  if (n<=0)
    0
  else
    n + sum(n-1) // n이 expression으로 치환된다.
```

## 1.4 Termination / Divergence

끝나지 않는 연산

* Termination: 하나의 값으로 reduce 되는 식
* Divergence: 영원히 reduce 하는 식

```scala
def loop:
  Int = loop // Nothing = loop
```

### 1.5 Evaluation Strategy: Call-by-value, Call-by-name

실행하면 같은 값으로 나올까? 대부분 같은데 다를 수 있다.

* Call by value
  * 먼저 argument에 대입해서 계산하고 적용한다.
  * 장점: argument 식을 한 번만 계산한다.
  * 단점: 무한 loop에 빠질 수 있다.
  * syntax: by default
  * `val a = 1 + 2 + 3`
    * expression을 먼저 evaluate하고 그 다음 이름에 바인딩함.
    * val이나 field 사용함.

* Call by name
  * evaluating 하지 않고도 argument에 함수를 적용한다.
  * 장점: 함수가 argument를 사용하지 않을 때 대입해서 계산하지 않는다.
  * syntax: `=>`
    * `def one(x:Int, y: => Int) = 1`
  * `def x = e`
    * 함수 정의에 주로 사용된다.
    * def나 method 사용함.

### 1.6 Conditional Expressions

* if - else
  * if (b) e1 else e2
  * b : Boolean expression
  * e1, e2 : expression of the same type

* Rewrite rules
  * if (true) e1 else e2 -> e1
  * if (false) e1 else e2 -> e2

```scala
def abs(x: Int):Int = if (x >= 0) x else -x
```

### 1.7 Boolean Expressions

결과를 boolean으로 내는 식

* `true`, `false`
* `!b` // negation
* `b && b` // call-by-value && call-by-name
* `b || b`
* `e <= e`, `e >= e`, `e < e`, `e > e`, `e == e`, `e != e`

rewrite rules

* `!true` -> `false`
* `!false` -> `true`
* `true` && `b` -> b // 첫번째가 true면 b가 계산
* `false` && `b` -> false // 첫번째가 false면 b가 계산되지 않음
* `true` || `b` -> true
* `false` || `b` -> b

write two functions by yourself

* `and(x, y)` == x && y

```scala
def and (x:Boolean, y:=>Boolean) = 
  if (x) y else false
```

* `or(x, y)` == x || y

```scala
def or(x:Boolean, y:=>Boolean) =
  if (x) true else y
```

calculate square roots with Newton's method

```scala
def improve(guess:Double, x:Double) =
  (guess + x/guess) / 2

def isGoodEnough(guess:Double, x:Double) =
  ((guess*guess/x) >= 0.9) &&
  ((guess*guess/x) <= 1.1)
  ??? // guess * guess is 99.9% close to x

// recursive 함수일 때는 무조건 user가 return type을 써준다.
def sqrtIter(guess:Double, x:Double) : Double =
  is (isGoodEnough(guess, x)) guess
  else sqrtIter(improve(guess, x), x)

def sqrt(x:Double): Double = sqrtIter(guess=1, x)
```
