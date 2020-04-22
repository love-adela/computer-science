# CSAPP Overview

## 1. Instruction Set Architecture(ISA)

### 1.1 Interface

[인터페이스](https://en.wikipedia.org/wiki/Interface_(computing))는 독립적이고 종종 관련이 없는 시스템이 서로 만나고 작용하거나 소통하는 공간을 뜻한다.
따라서 필요한 정보만 두개 이상의 시스템에 최소한으로 드러내고 나머지는 숨김으로써 각 컴포넌트가 효율적으로 통신할 수 있게 해야 한다. 이 역할은 추상자료형(ADT, Abstract Data Type)이 수행한다. ADT는 특정 구현과 무관하게 정확하게 지정된 데이터 값과 그와 관련된 연산의 집합이다. ADT는 데이터값의 집합(상태, state)이나 연산이 내부적으로 어떻게 구현되었는지 드러내지 않는다. 스택(Stack)이 추상자료형의 예다. 스택에 연산(`push()`, `pop()`, `is_empty()`, `create_stack()`, `destroy_stack()`)을 수행할 때 메모리에 어떤 변화가 일어나는지 사람이 몰라도 되기 때문이다.

* 참고
  * Levels of Abstraction (Computer)
    * Devices → Circuits → Microarchitecture → Instruction Set Architecture → Language → Algorithms → Problems

### 1.2 Instruction Set Architecture (ISA)

ISA는 하드웨어와 소프트웨어 간의 인터페이스다. 
