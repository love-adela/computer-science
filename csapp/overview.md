# CSAPP Overview

## 1. Instruction Set Architecture(ISA)

1.1 Interface

[인터페이스](https://en.wikipedia.org/wiki/Interface_(computing))는 독립적이고 종종 관련이 없는 시스템이 서로 만나고 작용하거나 소통하는 공간을 뜻한다.
따라서 필요한 정보만 두개 이상의 시스템에 최소한으로 드러내고 나머지는 숨김으로써 각 컴포넌트가 효율적으로 통신할 수 있게 해야 한다. 이 역할은 추상자료형(ADT, Abstract Data Type)이 수행한다. ADT는 특정 구현 방식까지 정의하진 않지만 데이터 값과 그와 관련된 연산의 집합을 정의한다. ADT는 데이터값의 집합(상태, state)이나 연산이 내부적으로 어떻게 구현되었는지 드러내지 않는다. 스택(Stack)이 추상자료형의 예다. 스택에 연산(`push()`, `pop()`, `is_empty()`, `create_stack()`, `destroy_stack()`)을 수행할 때 메모리에 어떤 변화가 일어나는지 사람이 몰라도 되기 때문이다.

* 참고
  * Levels of Abstraction (Computer)
    * Devices → Circuits → Microarchitecture → Instruction Set Architecture → Language → Algorithms → Problems

1.2 Instruction Set Architecture (ISA)

ISA는 하드웨어와 소프트웨어 간의 인터페이스다. 인간이 해당 CPU의 ISA 체계에 맞는 소프트웨어 코드를 작성하면 해당 ISA를 따르는 CPU가 코드를 읽고 명령된 동작들을 수행한다.

**x86-64**는 Intel CPU의 ISA로 ARM의 ISA와 함께 세계적으로 가장 많이 사용된다고 한다.

1.3 Instruction Set Architecture as an ADT

앞서 ADT 정의에 따라 ISA는 ADT의 적절한 예시다. CPU의 내부 구현 방식까지 정의하진 않고 있지만, 레지스터와 메모리 값을 조작하는데 필요한 연산과 명령어를 정의한다.

또한 추상자료형으로서의 ISA는 여러개의 레지스터와 CPU를 구현한다.

## 2. 디자인 기법(Design Technique)

**디자인기법**

디자인기법이 사용되는 영역은 공학방법론(Engineering methodology), 정확성 기준(Correctness criteria), 평가 방법(Evaluation methods), 기술 경향(Technology trends)이 있다.

**메모리/IO 시스템의 동작방식**

프로그램은 선형으로 실행되기 때문에 앞으로 읽을 거리가 뻔하게 정해져 있다. 한정된 캐시 안에 instruction(code), data 에 접근하는 패턴이 각각 다르기 때문에 원치 않는 캐시가 지워지는 문제를 막기 위해 캐시를 분리해둔다.

캐시는 코어 하나당 있어야 하는데 멀티코어 컴퓨터가 나타나면서, 데이터를 변경했을 때 갱신되지 않는 문제가 있다. 이 문제를 해결하기 위해서 Unified cache를 마련한다. I-cache, D-cache에 원하는 코드나 데이터를 찾지 못하면 Unified cache에서 찾는다.

### 2.1 프로세서 (Processor)

2.1.1 프로세서(CPU) 구현 방식

명령어 실행 방식의 측면에서 다음으로 구분할 수 있다. (1)~(4)의 순서대로 구현하기 복잡하진 않지만, CPU 성능은 떨어지는 차이가 있다.

(1) Sequential Implementation

* 한 Instruction이 완전히 끝나면 다음 Insturction을 수행한다.
* 단순하지만 Trade-off의 측면에서 성능이 떨어진다.
  
(2) Pipelined Implementation

* 한 Instruction이 완전히 끝나기 전에 다음 Instruction을 수행한다.

(3) Out of order execution

* 바로 Instruction을 시작한다.
  
(4) Speculative execution

* Branch를 통해 Instruction으로 바로 이동한다.

### 2.2 캐시 메모리 (Cache Memory)

2.2.1 메모리의 종류

* DRAM(Dynamic RAM) : 메인 메모리
  * 상대적으로 속도가 느리다.
  * 단위 용량 가격이 저렴하다.
  * 용량이 큰 메인 메모리를 만들 때 사용된다.

* SRAM(Static RAM) : 캐시 메모리
  * 속도가 빠르다.
  * 상대적으로 가격이 비싸다.
  * 용량이 작은 캐시 메모리를 만들 때 사용된다.

2.2.2 [캐시](https://en.wikipedia.org/wiki/Cache_(computing) 메모리

* 역할 : 자주 참조될 것으로 예상되는 데이터가 저장된다. CPU가 메인 메모리에서 모든 데이터를 찾으면 상대적으로 시간이 많이 걸리기 때문이다.

* 용어 
  * Cache Hit : 찾고자 하는 데이터가 캐시 메모리에서 발견되는 것
    * [현대 CPU는 캐시 Hit 확률이 95.1% 정도다.](https://www.cloudflare.com/learning/cdn/what-is-a-cache-hit-ratio/)
  * Cache Miss : 찾고자 하는 데이터가 캐시 메모리에서 발견되지 않는 것

2.2.3 Cache Hit Concept: Locality (지역성)

* Locality(지역성)
  * Temporal Locality : 어떤 데이터를 참조하면 가까운 미래에 그 데이터를 다시 참조할 확률이 높다.
    * 예를 들어 for loop 의 변수 i는 반복적으로 참조되므로 i를 캐시메모리에 두면 처리 속도가 빠르다.
    * Cache memory 관점 - 캐시 메모리 내 블록을 최근에 참조된 순서대로 정렬한다. 또한 메모리가 꽉 차서 특정 블록을 버려야 하면 가장 예전에 참조되었던 블록을 버리도록 한다.
  * Spatial Locality : 어떤 데이터를 참조하면 가까운 미래에 그 주변의 데이터를 참조할 확률이 높다.
    * list 요소를 순차적으로 접근하는 성질을 따라, list 요소를 뭉치로 캐시 메모리에 저장해두면 처리 속도가 빠르다.
    * Cache memory 관점 - 어떤 데이터의 참조에 Cache Miss가 발생하면 그 데이터를 포함하는 메모리 뭉치를 캐시 메모리에 저장한다.

### 2.3 공학 방법론 (Enginerring Methodology)

Rule1 : 자주 수행되는 작업에 속도를 향상시키자.

- Identify & Optimize

Rule2 : 미리 모든 경우를 파악해서 버그가 발생하지 않게 디자인하자.

- Plain in advance on how to enumerate them systematically

### 2.4 정확성의 기준(Correctness Criteria) - as if(~인 것처럼)'s

- pipeline을 실행할 때의 instruction은 sequential하게 실행되는지 확인할 것.
- cache 메모리를 만드는 시스템을 구현했다면 메모리가 없는 동일한 시스템에서 실행될 때와 같은지 확인할 것.

### 2.5 성능 평가 방법(Performance Evaluation Method)

2.5.1 성능 척도

- 처리시간(Time) : 요청한 작업이 처리될 때까지 걸리는 시간
  - 응답시간(response time)
  - 실행시간(execution time)
  
- 처리속도(Rate) : 단위 시간 동안 처리하는 데이터의 양
  - 처리량(throughput) : MIPS, MFLOPS 같은 단위
  - 대역폭(bandwidth) : Mbps 같은 단위

- Ratio : time & rate를 고려하여 상대적인 퍼포먼스

### 2.6 기술 경향(Technology Trends)

2.6.1 Processor Trends

용량(density)이 로그스케일로 늘어나고 있다. 

2.6.2 DRAM Trends

용량이 2배씩 로그스케일로 늘어난다.

2.6.3 NAND Flash Trends

SSD 용량도 마찬가지로 늘어나고 있다. 자세한 내용은 market revenue 참고.

2.6.4 Hard Disk Drive (HDD) Trends

HDD 용량도 늘어나고 있다. 반면 단위가격이 점점 싸지고 있다.