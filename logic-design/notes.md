Week 1, Mon
---

* 학습목표
  - Digital Logic Design에 대해서 배운다.
  - Digital Abstraction

1. Digital Systems
  1. 기반 : Digital Logic Design
  2. 특징 : Digital Abstraction - 모든 값(전선의 전압, 진동수, 질량의 위치...)을 살펴보는게 아니라 이산적인 부분집합의 값만 고려하는 것
  3. 활용 : 계산, 데이터 가공, 제어, 통신, 측정 -> 신뢰성, 통합성
  4. 참고
    * Analog: Continuous
    * Digital: Discrete, Discontinuous, Quantized, Binary Values (1's and 0's / True and False / High and Low / On and Off), Bit(Binary Digits)
  5. Three design level
    * System Design : 전체시스템을 서브시스템으로 분리
    * Logic Design : 특정 기능을 수행하기 위해 기본 논리 블록을 연결시키는 방법을 결정함
    * Circuit Design : 전기전자회로에서 특정한 부품을 연결시키는 방법을 특화함

2. Switching Circuits (회선교환)
    1. Digital Circuit : 1과 0을 나타내기 위해 주로 특정 전압 레벨에 의존한다.
      1. Logic Levels은 1과 0을 나타내기 위해 이산적이고 물리적인 전압을 정의한다.
        - 예를 들어, 0는 ground와 0v로, 1는 Vdd와 5v로 정의.
        - 4.99v, 3.2v는 **Error** 또는 **Noise**라고 함.
      2. Noise : Anything that degrades the signal (resistance, power, supply noise, coupling to neighboring wires, etc)
        - 아날로그와 달리 repeater나 regenerator로 noise를 제거할 수 있으므로 robust 하다.
    2. 종류
       1. Combinational Circuit(조합회로): 출력이 현재 입력에만 의존
       2. Sequential Circuit(순차회로): 출력이 현재와 과거 입력에 의존 (Memory 기능이 있음)
  