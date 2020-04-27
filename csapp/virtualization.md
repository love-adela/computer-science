# CSAPP Virtualization

## 1. 운영체제 (Operating System)

1.1 부팅(Booting)

1.2 운영체제의 목적

1.3 운영체제의 기능

1.4 유저프로그램의 제어권이 CPU에서 OS로 넘어가는 경우

경우에 따라 유저프로그램을 사용하다 OS 코드를 실행하기도 한다. 

## 2. 가상화 (Virtualization)

컴퓨팅의 역사는 가상화의 역사라고도 볼 수 있다. 

- 가상화(Virtualization)은 현실세계의 물리적인 한계를 뛰어넘는 기능이 실현 가능한 환경을 구축하는 기술을 뜻한다.
- logical duplication 라고도 한다. 메모리를 가상화하면 물리적인 실제 RAM에는 한번만 저장했던 데이터가 여러군데 있는 것처럼 보이게 할 수 있기 때문이다. 
- 예시 : Simultaneous Multithreading(SMT), Process Abstraction, Virtual Machine, Cache Memory, Virtual Memory

2.1 Process Abstraction

하나의 물리적인 cpu(physical cpu)가 여러 논리 cpu가 있는 것처럼 작동하게 가상화하는 기술. 물리적인 cpu에 타이머회로/인터럽트를 사용하는 운영체제의 시분할다중화 기술을 더함으로써 가능해진다. 예를 들어 resource manager 역할을 하는 운영체제는 한 번에 한 스레드를 시간 차를 두고 차례대로 돌려, 운영체제가 여러 스레드를 동작하게금 한다.

2.2 Virtual Machine

하나의 OS를 구동하는 물리적인 컴퓨터를 여러 OS를 구동하는 것처럼 작동하게 전체 컴퓨터 시스템을 가상화하는 기술. 예를 들어 VMware, Virtualbox, Connectix Virtual PC가 있다. 컴퓨터 시스템 전체 상태를 백업하는 매커니즘이 필요하다.

2.3 Cache Memory

두 개의 DRAM, SRAM 이라는 메모리를 따로 마련함으로써 마치 하나의 빠르고 저렴한 메모리로 동작하게금 가상화하는 기술. CPU가 한정된 메모리 참조 속도를 캐시메모리(SRAM)에 메인메모리(DRAM)을 더하는 방식으로 이뤄진다. 자주 참조되는 데이터는 캐시메모리에 저장되어 있기 때문이다.

2.4 Virtual Memory

각각의 프로세서마다 하나의 메인메모리가 있는 것처럼 동작하도록 하는 가상화기술. 하드디스크를 공간분할다중화(Space Division Multiplexing) 기술을 적용한다. 메인메모리(DRAM)과 하드디스크를 접목하는 방식이다. 메인메모리(DRAM)에 로드될 데이터는 하드 디스크에 저장되고, 그 중 프로세스가 자주 참조하는 부분은 메인메모리로 로드된다.
