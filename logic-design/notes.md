# Week 1, Mon
---

* 이 Course의 학습목표
  - Digital Logic Design에 대해서 배운다.
  - Digital Abstraction

## 1.1 Digital Systems

1. 기반 : Digital Logic Design
2. 특징 : Digital Abstraction - 모든 값(전선의 전압, 진동수, 질량의 위치...)을 살펴보는게 아니라 이산적인 부분집합의 값만 고려하는 것
3. 활용 : 계산, 데이터 가공, 제어, 통신, 측정 -> 신뢰성, 통합성

4. 참고
  * Analog: Continuous
  
  * Digital: Discrete, Discontinuous, Quantized, Binary Values (1's and 0's / True and False / High and Low / On and), Bit(Binary Digits)
  
5. Design Level

  * System Design : 전체시스템을 서브시스템으로 분리
  * Logic Design : 특정 기능을 수행하기 위해 기본 논리 블록을 연결시키는 방법을 결정함
  * Circuit Design : 전기전자회로에서 특정한 부품을 연결시키는 방법을 특화함

## 1.2 Switching Circuits (회선교환)

### 1.2.1 Digital Circuit

1과 0을 나타내기 위해 주로 특정 전압 레벨에 의존한다.

1. Logic Levels

- 1과 0을 나타내기 위해 이산적이고 물리적인 전압으로 정의.
- 예를 들어, 0는 ground와 0v로, 1는 Vdd와 5v로 정의.
- 4.99v, 3.2v는 **Error** 또는 **Noise**라고 로.

2. Noise

- Anything that degrades the signal (resistance, power, supply noise, coupling to neighboring wires, etc)
- 아날로그와 달리 repeater나 regenerator로 noise를 제거할 수 있으므로 robust 하다.

3. Digital Circuit 종류

- Combinational Circuit(조합회로): 출력이 현재 입력에만 의존
- Sequential Circuit(순차회로): 출력이 현재와 과거 입력에 의존 (Memory 기능이 있음)

# Week 1, Wed
---

학습목표
- The basics of Logic Design
  - Boolean algebra, Logic minimization, State, Timing, CAD tools
  - How to specify/simulate/compile/realize our designs
    - HDLs(Hardware Description Languages)로 디자인하기
    - 시뮬레이션하기
    - 컴파일 후 실제 프로그래머블 하드웨어에 맵핑하기 (FPGA, Field Programmable Gate Array)  
  - 디지털 시스템의 **state**에 대해서 알아본다. - Analogous to variables in software systems
- Computation
- Combinational vs Sequential Digital Circuits

## 1.3 Logic Design

### 1.3.1 설계란?

* 주어진 문제 명세를 사용 가능한 부품들로 해결하는 것
* size, cost, power 같은 정량적인 것과 아름다움, 우아함 같은 정성적인 것을  충족시킬 수 있음.

### 1.3.2 논리 설계란?

* 특정 제어, 자료 조작, 커뮤니케이션 기능과 상호연결을 수행하기 위한 디지털 논리 구성요소를 고르는 것
* 필요한 논리 구성요소는 실제 사용되는 기술. 예를 들어 fixed-function 구성요소, 프로그래머블 장치, 칩의 개별 트랜지스터가 있음
* 설계 제약을 충족시키기 위해 설계를 최적화하고 변형함

### 1.3.3 논리 설계가 소프트웨어 설계와 다른 점

* 많은 일들이 병렬로 동시에 일어나기 때문에 소프트웨어 디자인과 다름.
* 논리 설계 때 사용하는 computing/storage resource처럼 알고리즘을 특화.

### 1.3.4 Digital Hardware란?

* and/or 같은 디지털 값을 전달하는 제어 회로 (control wires)를 감지 및 제어하는 장치 모음
  * 예를 들어 0 또는 1로 해석될 수 있는 물리양

* 원시적인 하드웨어 장치
  * 논리 연산 장치(Logic Computation Devices) (input:sense, output:drive)
    * sense & sense => and => drive
    * binary gate
      * 둘 다 1일 경우 : AND
      * 둘 중 하나만 1일 경우 : OR
    * unary gate
      * 1일 경우 : NOT

  * 메모리 장치 (저장)
    * write() : 값 저장
    * read() : 이전에 저장된 값 불러오기

## 1.4 Computation

* 논리값을 보여주는 전압을 사용해서 계산을 수행
* 기본 단위
  * representation : 0, 1 등의 값을 회로로 표현
  * assignment : `x = y`
  * data operations `x + y -5`
  * control
    * sequential statements `A; B; C;`
    * conditionals
    * loops
    * procedures(=function call)

  -> 하드웨어 어떻게 구현하는지 알아볼 것임.
  
### 1.4.1 Switches

(1) 물리적인 수행 요소

* 간단한 회로: A와 Z는 동일한 boolean 값
  * 스위치 (A)
    * closed : 1 (ON)
    * open: 0 (OFF)
  * 전구 (Z)
    * ON : 1
    * OFF : 0
* 복잡한 회로:
  * `Z  ≡ A and B`
  * `Z  ≡ A or B`

(2) Switching networks

* 스위치 설정 : 전구를 밝히기 위한 전선(전도 경로)이 있는지를 판단함
* 다른 스위치를 설치해서 더 큰 계산기를 만듦
* 여러개의 스위치 조합해서 더 복잡한 논리회로를 만듦
  * 스위치 직렬 연결 : AND 구현
  * 스위치 병렬 병렬 : OR 구현

### 1.4.2 Transistors

현실에서는 스위치가 아니라 트랜지스터를 사용한다.
트랜지스터는 전압으로 켜고 끄는 아주 작은 스위치다.

* 전압이 높을 때 : 닫힘
* 전압이 낮을 때 : 열림

(1) CMOS (Complementary Metal-Oxide Semiconductor) 기술

* C는 Complementary의 약자인데, 둘다 정상적으로 열려있는 스위치가 있고 둘다 정상적으로 닫혀있는 스위치가 있음.
  * nMOS : minus
  * pMOS : plus

(2) MOS transistors

(3) MOS networks

(4) Two input networks

(5) n-channel (or n-type) MOS (nMOS)

(6) p-channel (or p-type) MOS (pMOS)

## 1.5 Combinational vs Sequential Digital Circuits

### 1.5.1 Digital vs Analog

### 1.5.2 Combinational Circuit vs sequential digital circuits

(1) 조합회로(Combinational Circuit)

* 현재 입력에만 의존해서 결과가 나오는 회로
* 수학에서의 순수함수(pure function) 같은 것 `Output = f(input)`

(2) 순차회로(Sequential Digital Circuit)

* 이전의 입력이 미래의 결과에 영향을 주는 회로
* ex: vendor machine
* State 가 존재한다. `Output = f(input, previous_input)`

### 1.5.3 [Combinational logic symbols](https://en.wikipedia.org/wiki/Combinational_logic)

* 표준이 있고 논리 게이트(logic gates)라고 부름
  * Buffer
    * Regenerating
    * 아무것도 하지 않는다
    * 전압을 정규화할 때 쓰임. 예를 들어 입력 3.8V는 출력 5V
    * 논리회로 수업 때는 잘 안 씀. 현실세계에서는 고성능 회로 디자인할 때 사용
  * AND, OR
  * NOT, NAND, NOR
    * CMOS 트랜지스터로 구현하기 가장 쉽고 가장 많이 사용하는 것.

# Week 2, Mon
---

### 1.5.4 Examples

(1) Combinational digital circuit

* Calendar subsystem
  * 월별 일 수 계산기
  * 입력으로 월과 윤년 여부를 받아서 그 월에 있는 일 수를 출력

* Reference implementation in software

* Implementation as a combinational digital system

* Truth-table to logic to switches to gates

(2) Sequential digital circuit

* Door combination lock

* Reference implementation in software

* Implementation as a sequential digital system
* Abstract control : Finite-state diagram
* Internal structure : Data-path vs. control
* Finite-state machine(FSM)
* Finite-state machine(cont'd)
* Encoding: Encode state table
* Encode state table (cont'd)
* Implementation of the controller

# Week 2, Wed

Combinational Logic
---

## 2.1 Basic Logic

### 2.1.1 Boolean algebra

(1) An algebraic structure 구성

* 원소의 집합
* binary operations : `+, *`, (OR, AND)
* unary operation : `'` (NOT)
* Axioms로 구성된 수학적 구조
  * 셋 안에 최소 두 개 원소 존재
  * Closure : 연산에 대해 닫혀 있음
  * Commutativity : 교환법칙
  * Associativity : 결합법칙
  * Identity : 연산(덧셈/곱셈)에 대해 항등원이 존재
  * Distributivity : 분배법칙
  * Complementarity : 연산(덧셈/곱셈)에 대해 역원이 존재

(2) Logic functions and Boolean algebra

* 진리표로 표현되는 모든 임의의 논리 함수는 `'`, `+`, `*` 같은 연산자 조합으로 부울대수를 표현할 수 있다.

(3) 부울대수에서의 Axioms와 Theorems

* Identity(항등원)
  * X or 0 = X, X or False = X
  * X and 1 = X, X and True = x

* Null
  * X + 1 = 1, X or True = True
  * X * 0 = 0, X and False = False

* Idempotency(멱등성)
  * X + X = X, X or X = X
  * X * X = X, X and X = X
  * f(f(x)) = x

* Involution
  * (X')' = X, !(!X) = X

* Complementarity(역원)
  * X + X' = 1, X or !X = True
  * X * X' = 0, X and !X = False

* Commutativity(교환법칙)
  * X + Y = Y + X, X or Y = Y or X
  * X * Y = Y * X, X and Y = Y and X

* Associativity(연관법칙)
  * (X + Y) + Z = X + (Y + Z), (X or Y) or Z = X or (Y or Z)
  * (X * Y) * Z = X * (Y * Z), (X and Y) and Z = X and (Y and Z)

* Distributivity(분배법칙)
  * X and (Y or Z) = (X and Y) or (X and Z), X * (Y + Z) = (X * Y) + (X * Z)
  * X or (Y and Z) = (X or Y) and (X or Z), X + (Y * Z) = (X + Y) * (X + Z)

* Uniting
  * (X and Y) or (X and !Y) = X, X * Y + X * Y' = X
    * X * (Y + Y') = X * 1 = X
  * (X or Y) and (X or !Y) = X, (X + Y) * (X + Y') = X

* Absorption(흡수 법칙)
  * X or (X and Y) = X, X + (X * Y) = X
  * X and (X or Y) = X, X * (X + Y) = X
  * (X or !Y) and Y = X and Y, (X + Y') * Y = X * Y
  * (X and !Y) or Y = X or Y, (X * Y') + Y = X + Y

* Factoring
  * (X or Y) and (!X or Z) = (X and Z) or (!X or Y), (X + Y) * (X' + Z) = X * Z + X' * Y
  * (X and Y) or (!X or Z) = (X or Z) and (!X or Y), X * Y + (X' * Z) = (X + Z) * (X' + Y)

* Concensus

  * (X and Y) or (Y and Z) or (!X and Z) = (X and Y) or (!X and Z), (X + Y) * (X' + Z) = X * Z + X' * Y
  * (X or Y) and (Y or Z) and (!X or Z) = (X or Y) and (!X or Z), (X * Y) * (Y + Z) * (X' + Z) = (X + Y) * (X' + Z)

* de Morgan's Law

  * !(X or Y) = !X and !Y
  * !(X1 or X2 or ... Xn) = !X1 and !X2 and ... !Xn, (X + Y + ...)' = X' * Y' * ...
  * !(X and Y) = !X or !Y
  * !(X1 and X2 and ... Xn) = !X1 or !X2 or ... !Xn, (X * Y * ...)' = X' + Y' +

* Generalized de Morgan's Law

  * !f(X1, X2, ... Xn, 0, 1, or, and) = f(!X1, !X2, ... !Xn, 1, 0, and, or)

* Duality (Meta-theorem)

  * 한 Boolean expression 안에 있는 모든 and와 or를 맞바꾸고 true와 false를 맞바꿔서, 한 expression의 dual을 얻을 수 있다.
  * f(X1, X2, ... Xn, 0, 1, or, and) 의 Dual은 f(X1, X2, ... Xn, 1, 0, and, or)

### 2.1.2 Proofs by re-writing, proofs by perfect induction

Theorems을 증명하는데엔 크게 두가지 방법이 있다.

(1) Rewrite로 증명하기 - 부울대수 정리 사용

* (X and Y) or (X and !Y)
= X                         (Uniting)
= X and (Y or !Y)           (Distributivity)
= X and true                (Complementarity)
= X                         (Identity)

* X or (X and Y)
= X                          (Absorption)
= (X and true) or (X and Y)  (Identity)
= X and (true or Y)          (Distributivity)
= X and true                 (Null)
= X                          (Identity)

(2) Complete Truth table로 증명하기, Perfect induction(유도)

가능한 입력의 경우의 수를 모두 다 써서 수식이 맞다는걸 증명하면 증명되었다고 간주

* e.g de Morgan's

X  Y  X' Y' | (X+Y)' X'*Y'
------------|-------------
0  0  1  1  |   1     1
0  1  1  0  |   0     0
1  0  0  1  |   0     0
1  1  0  0  |   0     0

## 2.2 Realizing Boolean Formulas

Technology mapping으로 Boolean exponential로 표현해서 물리적인 회로로 만듦
논리 게이트를 표현하는 mapping 방법은 한 가지 이상이다.

### 2.2.1 Logic Functions

`n`개의 입력값이 있을 때 `2 ** (2 ** n)`개의 함수가 생김
예를 들어 2개 input 값이 있으면 16가지 function이 발생

 X  Y | F0| F1 | F2 | F3 | F4 | F5 |F6  |F7 | F8 | F9 | F10 | F11| F12 | F13| F14 | F15
------|---|----|----|----|----|----|----|---|----|----|-----|----|-----|---|-----|-----
 0  0 | 0 | 0  | 0  | 0  | 0  | 0  | 0  | 0 | 1  | 1  | 1   | 1  | 1   | 1 |  1  | 1
 0  1 | 0 | 0  | 0  | 0  | 1  | 1  | 1  | 1 | 0  | 0  | 0   | 0  | 1   | 1 |  1  | 1  
 1  0 | 0 | 0  | 1  | 1  | 0  | 0  | 1  | 1 | 0  | 0  | 1   | 1  | 0   | 0 |  1  | 1
 1  1 | 0 | 1  | 0  | 1  | 0  | 1  | 0  | 1 | 0  | 1  | 0   | 1  | 0   | 1 |  0  | 1
  \- |  - | 0 | and| -  | X  | -  | Y  | xor| or| nor| -  | not | -  | not | - |nand | 1

- 1-bit full adder

### 2.2.2 Cost of different logic functions

각각의 논리함수는 쉽게 구현되기도 어렵게 구현되기도 함. 그에 대한 비용도 마찬가지.
NOT, NOR, NAND가 싸기 때문에 이걸 구현하는 연습을 하자. AND, OR, NOT 보다 저렴함.

- 필요한 스위치 개수에 비례해서 비용이 증가한다.
- 단순 0(F0) 과 1(F15)이라는 아웃풋은 0개의 스위치가 필요. 직렬연결 시 low / high 로 아웃풋이 나옴풋
- X(F3)와 Y(F5)라는 아웃풋은 스위치가 필요 없고 input 중 하나가 output이 됨
- X'(F12)와 Y'(F10)는 **inverter**와 NOT-gate를 구현하기 위해 2개의 스위치가 필요함.
- X nor Y (F4) and X nand Y (F14)는 4개의 스위치가 필요함.
- X or Y (F7)와 X and Y (F1)은 6개의 스위치가 필요함.
- X = Y(F9) and X ⊕ Y (F6)은 16개의 스위치가 필요함.
  - 가장 비싼 비용이 든다.
  - X xor Y = X or Y but not both (inequality, difference)

### 2.2.3 Minimal set

모든 논리회로는 NAND 단 하나만으로, 혹은 NOR 단 하나만으로 구현이 가능하다. (NAND와 NOR은 듀얼 관계, waveform view of logic functions)
예를 들어 and 는 not nand로 표현 가능함.

* `nor` Truth Table
  
 X  Y  | X nor Y
-------|--------
 0  0  |   1
 1  1  |   0

* `nand` Truth Table

 X  Y  | X nand Y
-------|--------
 0  0  |   1
 1  1  |   0


### 2.2.4 Waveform view of logic functions

시간에 따라 다른 입력을 연속적으로 흘려줌으로써 진리표를 쉽게 뽑을 수 있음. Propagation Delay 때문에 출력이 약간 늦게 나옴.

# Week 3, Mon

### 2.2.5 Choosing different realizations of a function

부울대수적으로 동치되는 논리식을 진리표로 나타내, 논리게이트로 옮기는 방법이 여러가지 있음.

### 2.2.6 Which realization is best?

회로 크기가 커짐에 따라 지연이 발생하는 것에 대한 tradeoff가 발생한다. 논리회로를 잘 만들려면 어떻게 해야 할가?

(1) 비용에 영향을 주는 요인

1. 입력 (변수) 개수

* 입력 변수는 literal 하나당 2개의 트랜지스터에 대한 논리 게이트 비용에 준한다.
* 입력 변수가 적을 수록 트랜지스터도 적게 사용함
* input이 적을수록 게이트가 빨라진다.
* 기술에 따라서 fan-in(논리게이트가 감당할 수 있는 인풋 개수)은 제한적임
* 비용 ↓
* 구현도 ↓

2. 게이트 수

* 게이트 수와 게이트에 들어오는 packages가 적을수록 회로도 작아짐.
* 게이트 많아지면 비용 ↑ (가장 직접적인 요인)

3. 게이트 레벨 개수

* 게이트 레벨이 낮아질수록 신호 propagation delay가 줄어든다.
* 최소 지연 설정은 게이트를 더 많이 필요한다.
  * 더 크고 덜 깊은 회로가 필요하게 됨.
  * 구현도 ↑
* 게이트 레벨 높아지면 비용 ↑
* 예시
  * 단순하게 생긴 XOR은 내부 구현이 복잡
  * NAND는 AND와 구현이 비슷해보이지만 비용 ↓

(2) Solution

* 자동화된 툴(CAD 같은거)로 각각의 기준(지연을 최소화하자, 게이트 개수를 줄이자 등등)에 따른 솔루션을 만들 수 있다.

* logic minimization : 게이트 개수와 복잡도를 줄인다
* logic optimization : 트레이드 오프시 지연에 따라 축소시킴

## 2.3 Two-level logic

### 2.3.1 Canonical forms

동일한 진리표라도 게이트 구현 방법은 여러가지가 있음. 그 중 Canonical form(표준형)이 Boolean expression의 standard한 형태. 표준형이 반드시 Minimal form은 아님.

(1) Sum-of-products (S-o-P, 곱의 합) canonical forms

    * Truth table에서 결과가 1(True)인 경우를 모두 모아놓은 형태
    * Also known as Disjunctive(분리) normal form, Minterm expansion

(2) Product-of-sums (P-o-S, 합의 곱) canonical forms

    * Truth table에서 결과가 0(False)인 경우를 모두 모아놓은 형태
      * SoP form의 Dual
    * Also known as Conjunctive(결합) normal form, Maxterm expansion

(3) 변환

    Minterm form과 Maxterm form은 아래처럼 변환할 수 있음
        Σm(1, 3, 5, 6, 7) = ΠM(0, 2, 4)
    F의 minterm과 F'(not F)의 minterm
        F = Σm(1, 3, 5, 6, 7), F' = Σm(0, 2, 4)
    F의 maxterm과 F'(not F)의 maxterm도 간편하게 변환 가능함
        F = ΠM(0, 2, 4), F' = ΠM(1, 3, 5, 6, 7)

### 2.3.2 Incompletely specified functions

* BCD(Binary Coded Decimal)
  * 각 자리수의 수를 4비트 binary 값으로 나타냄.
  * 예를 들어 10은 00010000로 표현.

* Incompletely specified functions는 Two-level logic 에서 SoP / PoS canonical form 외에 잘못된 입력에 대한 output을 **Don't care** 로 표현하는 방법이다.

    이 함수를 쓸 때는 On-set와 Off-set, dc-set을 고려해야 함.
    예를 들어서 BCD increment by 1 function에서의
    * minterm expansion:
      * Z = ∑[m(0, 2, 4, 6, 8) + d(10, 11, 12, 13, 14, 15)]
    * maxterm expansion:
      * Z = Π[M(1, 3, 5, 7, 9) * D(10, 11, 12, 13, 14, 15)]

## 2.4 Motivation for two-level simplification

## 2.4.1 논리회로를 단순화 하는 방법

    Minimal S-o-P, P-o-S realization 찾기
        - Exploit "Don't care" information in the process
        - 게이트가 최소로 필요한 조합으로 dc-set을 만들 수 있으므로 비용을 줄일 수 있음.
    Algebraic simplification
        - Algorithmic/Systematic procedure가 아니여서, 지금의 표현이 minimum realization 인지 아닌진 알 수 없다.
    Computer-Aided Design (CAD)
        - NP문제여서 최적해 찾기가 아주 오래 걸림. 
        - 특히 입력이 10개 초과로 넘어가면 아주 느려짐
        - Educated guesses 휴리스틱으로 풀수는 있긴 한데 최적해는 아님
    Hand methods still relevant
        - 자동화 툴의 장단점을 익히는데에 좋음
        - 작은 예제에 대해선 직접 결과를 체크하는 능력을 키워줌

## 2.4.2 논리회로를 단순화하는 두 테크닉

Uniting Theorem에 기반한다.

    Uniting Theorem
    * XY+XY' = X(Y'+Y) = X
    * two-level logic 간소화에 필요한 핵심 개념.
    * 변수 X의 값이 어떤 것이든 Y값이 고정되어 결정되는 출력이 있을 때 적용할 수 있다.

다음 진리표에서 F가 1이 되는 경우에 고정된 값은 B의 0, 변하는 값은 A. A는 생략된다.
A B | F
----|---
0 0 | 1
0 1 | 0
1 0 | 1
1 1 | 0

(1) [Boolean Cubes](https://courses.cs.washington.edu/courses/cse370/97au/admin/Slides/Week3Lecture1/sld006.htm)
  
* Uniting Theorem을 적용시키기 쉽도록 입력이 N개일 때의 진리표를 N차원 큐브(N-dimensional Cube)에 시각화하는 방법.
  - Uniting theorem combines two 'faces' of a cube into a larger 'face'

* 구성요소
  * 방향을 나타내는 벡터
  * ON-set의 요소에 대응되면 Node를 까맣게 칠하고(solid nodes), OFF-set의 요소에 대응되면 빈 노드(empty nodes)로 둠.
  * DC-set은 X의 d nodes 로 둠.

* 종류
  * 1-cube
  * 2-cube
  * 4-cube

# Week 3, Wed

## 2.4.2 논리회로를 단순화하는 두 테크닉

(2) Karnaugh-maps (K-maps)

* input 수가 많아지면 구현하기 힘들어지는 Boolean Cube와 달리 **Karnaugh Maps**를 활용하면 편리하게 진리표를 시각화할 수 있다.

* Flat map of Boolean cube
  * Adjacencies를 잘 보여줌.
  * 값을 바꾸는 한 개의 변수에 해당하는 ON-set 요소가 인접함을 나타낸다.

* Numbering scheme based on Gray-code
  * 예를 들어, 00, 01, 11, 10이 있음
  * 서로 인접한 칸끼리는 입력이 1 bit씩만 변하기 때문에, map cell에서의 adjacent를 쉽게 파악할 수 있다.
  * 카너프맵의 양쪽 끝은 연결되어있다. (토폴로지가 도넛 모양임)

* 변수가 5개 넘어가면 카너프맵으로 시각화 하는 것도 어려움. 대신 컴퓨터가 해줌.

# Week 4, Mon

## 3.1 Working with combinational logic

Boolean minimization 과정을 배울 것이다.
Boolean cubes나 K-map로 논리식을 표현할 수도 있지만, 이번에는 시스템이나 알고리즘적으로 접근해볼 것임.

### 3.1.1 Simplification

(1) 2-level simplification

최적화한 결과가 2-level logic 이기 때문에 2-level simplification이라고 함.

(2) Exploiting don't cares

input의 범위는 0부터 3. 2bit-by-2bit multiplier that generates 4 bit output.

(3) Algorithm for simplification

### 3.1.2 Design example : two-bit comparator

two-bit comparator는 ~.

      * msb(most significant bit): 2진수의 여러비트들 중 가장 큰 값에 해당하는, 즉 가장 왼쪽에 있는 비트
      * lsb(least significant bit): 2진수의 여러비트들 중 가장 작은 값이자 가장 오른쪽의 비트

      * LT : Lesser Than
      * EQ : Equal
      * GT : Greater Than

3.1.2.1 Block diagram for two-bit comparator

* input: 2bits input  
  * 첫 번째 input : A1, A2
  * 두 번째 input : B1, B2

* output: 2bits output
  * 첫 번째 output : P1, P2
  * 두 번째 output : P4, P8

3.1.2.2 Truth table for two-bit comparator

A2 A1 B2 B1 | P8 P4 P2 P1
------------|------------
0   0  0  0 |  0  0  0  0
0   0  0  1 |  0  0  0  0
0   0  1  0 |  0  0  0  0
0   0  1  1 |  0  0  0  0
0   1  0  0 |  0  0  0  0
0   1  0  1 |  0  0  0  1
0   1  1  0 |  0  0  1  0
0   1  1  1 |  0  0  1  1
1   0  0  0 |  0  0  0  0
1   0  0  1 |  0  0  1  0
1   0  1  0 |  0  1  0  0
1   0  1  1 |  0  1  1  0
1   1  0  0 |  0  0  0  0
1   1  0  1 |  0  0  1  1
1   1  1  0 |  0  1  1  0
1   1  1  1 |  1  0  0  1

3.1.2.3 K-map for two-bit comparator

* LT = A'B'D + A'C + B'CD
* EQ
  * = A'B'C'D' + A'B'C'D + ABCD + AB'CD' 
  * =  (AC+A'C')BD + (AC+A'C')B'D' = (AC+A'C')(BD+B'D')
  * = `(Axnor C) * (B xnor D)`
* GT = BC'D' + AC' + ABD'

3.1.2.4 결론

XOR을 사용할 때와 사용하지 않을 때 모두 EQ 구현이 달라지게 되고 복잡도도 높지만, XNOR은 최소한 3개의 간단한 게이트로 구현이 가능하다. 

### 3.1.3 Design example: 2X2 bit multiplier

2X2 bit multiplier는 4비트짜리 출력을 발생시킨다. 이 때의 MSB는 P8, LSB는 P1이다. 입력 A2와 B2는 각각 MSB.

4개의 input으로 표현할 수 있는 number이 0~3까지라고 할 때, loss가 없는 전제 하에 two-bit comparator 로 표현할 수 있는 number 범위는 0~9까지다.

3.1.3.1 Block Diagram

3.1.3.2 Truth table

3.1.3.3 K-map


### 3.1.3 BCD increment by 1

3.1.3.1 Block diagram and turth table

input을 분명하게 넣어주는 특징이 있음.
(PPT 9페이지 예시 참고) +1 연산을 하는 다이어그램에 4비트짜리 BCD number에 해당하는 10개의 숫자를 0~9까지, A~F로 input과 output을 표현한다. 나머지 unused input에 대한 output은 DC-set.

이 식을 간소화할 수 있는 방법? Directly transform SoP, PoS 를 AND, OR 게이트로 만든다거나.

3.1.3.2 K-map

----

O8: 1의 자리를. If you can make bigger. simplify form of the boolean expression. This is the kind of biggest subcube that actually contains the 1. 
- I4I2I1 + I8I1'

O4: biggest subcube that acontains the 1, 
I3I2' + I4I1' + I4'I2I1


* 10개의 숫자

O8 
O4
O2
O1

P4

P2
원래는 각각의
Unification law 에 따라서 하나의 공통된 것이 있고.

P1
2 literals이 있고 인접한 2 min-term이 있음

* Example
  * Design example: bCD increment by 1
  
    * BCD
      * Binary Coded Decimal의 준말이고 Decimal number을 binary bit 로 표현하는 방법.
      * 0부터 9까지를 표현한다. 즉 A~F까지 표현하고 나머지는 Don't care.
      * 요즘 자주 쓰이는 것은 아니고 legacy support increment에 쓰임.


    * 1 ~ 0 까지는
    * 나머지는 unused고 Don't care.

이 function을 간소화시키는 방법
* Boolean expression으로 


* Design example: BCD increment by 1
  * O8 = I4 I2 I1 + I8 + I1'
  * O4 = minimal set 에 대한 subcube 를..

---

## 3.1.4 Definition of terms for 2-level simplification

### 3.1.4.1 Terms

* Implicant
  * On-set과 (input combination이 True가 되는 것들)과  DC-set으로만 이뤄진 subcube
  * 모든 implicant는 1 또는 0으로만 각각 구성되어야 함.
* Prime Implicant
  * 다른 Larger subcube에 합쳐질 수 없는 경우의 implicant.
* Essential Prime Implicant
  * Implicant은 Prime Implicant를, Prime Implicant 는 Essential Prime Implicant 을 포함
* Optimization Objective
  * Implicant들을 모두 Prime implicants 로 키우기
  * 전체 ON-set을 최소한의 Prime implicants로 덮기 (minimum cover)

### Algorithm for two-level simplification

  1. 카르노맵에 ON-set, OFF-set, DC-set 그리기
  2. 모든 Prime Implicants 를 찾는다.
    1. 카르노맵의 맨 윗줄과 맨 아랫줄, 맨 왼쪽줄과 맨 오른쪽줄, 각 코너들이 모두 연결되어 있음을 이용.
  3. Essential Prime Implicant 찾기
    - EPI는 무조건 결과에 포함되어야 함.
  4. EPI로 커버되지 않는 1들을 제일 적은 수의 Prime Implicant 로 덮어볼 것 (NP-hard)

### Algorithm for two-level simplification

### 3.4 Hardware Description Languages(HDL)

* Verilog
* schematic(회로도)

* 
HDL의 역사

    Abel, 약 1983
    ISP, 약 1977
    Verilog, 약 1985
        파스칼, C와 유사한 문법
        코드가 짧고 작성하기 쉬움
        IEEE 표준
    VHDL, 약 1987
        Ada와 유사한 문법
        Very general하지만 너무 verbose함
        IEEE 표준

Abel, ISP는 프로토타입이고 Verilog와 VHDL은 널리 쓰임. Verilog가 한국 미국 등지에선 더 많이 쓰이는데 VHDL은 유럽에서 많이 쓰임

하시설에서 안배운거

    $display: 콘솔에 글자 찍는 명령어
    $finish: 시뮬레이션 멈추는 명령어
    Assign에도 delay를 줄 수 있다. Propagation Delay를 묘사 가능

* synthesis

a process of compiling behavior of model into structure model.

highlevel chance to .

and/or/nand 같은 comblex operation이 break down 되었을 때,

lowering number of structure.
behavior model : xor
real hardware what can be implemented.

timing verification : sequential logic 을 아직 배우진 않았지만, 이건 motional clock에서 worst case delay between two, and three clock을 이 설계가 제대로 되었는지 확인하는 용도. 

cell phone, labtop 같은 2~4GHZ 같은 . clock speed.


Deisgn process : iterative process.

You're system is not disatisfied with certain input. You need to optimize the program to reduce the time. 

### HDLs vs programming languages(python, c++, c, java, ...)

기본적으로 HDLS는 multiple instantiation of multiple components of the same type
- specify interconnections between modules via schematic
- hierachy of modules
  
* Notable differencies
  * assignment
    * C 언어에서 `z=x^y` 같은 assignment 는 HDLs과 다른 점.
      * continuous assignment 는 조합논리
      * propagation delay 
      * timing of signals is important. It determins when does computation have its effect.
      * malloc?
      * new?

NAND gate가 AND gate보다 좀 더 싸다
  - NAND : 4개 transistor
  - AND : NAND(4개) + NOT (2개) = 6개


always는 continuous 가 아님.

트랜지스터의 동작원리

---
# Week5, Mon

## Time response in combinational networks

### Gate delays

Dynamic behavior:

Static behavior

### Timing Waveforms

* Waveforms

* Simulation tools
  * VIVADO
  * ISE

* Gatedelay : input change 부터 output change까지 걸린 시간


* rise time
  
* fall time

* pulse width : 출력 전압이 낮거나 높은채로 유지되는 시간

# Lecture 4

## Combinational Logic Technologies

[개요]

* Standard gates (random logic)
  * gate packages
  * cell libraries
* Regular logic : 진리표를 arbitrary functions로 dumping 하는 것과 비슷하다.
  * multiplexers
  * decoders
* Two-level programmable logic
  * PALs
  * PLAs
  * ROMs

## 4.1 Random logic

Week 7 : Mon
===

## Case1 : BCD to 7-segment display controller


