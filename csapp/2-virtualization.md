# CSAPP Virtualization

## 1. 가상화 (Virtualization)

컴퓨팅의 역사는 가상화의 역사라고도 볼 수 있다.

- 가상화(Virtualization)은 현실세계의 물리적인 한계를 뛰어넘는 기능이 실현 가능한 환경을 구축하는 기술을 뜻한다.
- logical duplication 라고도 한다. 메모리를 가상화하면 물리적인 실제 RAM에는 한번만 저장했던 데이터가 여러군데 있는 것처럼 보이게 할 수 있기 때문이다.
- 예시 : Simultaneous Multithreading(SMT), Process Abstraction, Virtual Machine, Cache Memory, Virtual Memory

### 1.1 Process Abstraction

하나의 물리적인 cpu(physical cpu)가 여러 논리 cpu가 있는 것처럼 작동하게 가상화하는 기술. 물리적인 cpu에 타이머회로/인터럽트를 사용하는 운영체제의 시분할다중화 기술을 더함으로써 가능해진다. 예를 들어 resource manager 역할을 하는 운영체제는 한 번에 한 스레드를 시간 차를 두고 차례대로 돌려, 운영체제가 여러 스레드를 동작하게금 한다.

### 1.2 Virtual Machine

하나의 OS를 구동하는 물리적인 컴퓨터를 여러 OS를 구동하는 것처럼 작동하게 전체 컴퓨터 시스템을 가상화하는 기술. 예를 들어 VMware, Virtualbox, Connectix Virtual PC가 있다. 컴퓨터 시스템 전체 상태를 백업하는 매커니즘이 필요하다.

### 1.3 Cache Memory

두 개의 DRAM, SRAM 이라는 메모리를 따로 마련함으로써 마치 하나의 빠르고 저렴한 메모리로 동작하게금 가상화하는 기술. CPU가 한정된 메모리 참조 속도를 캐시메모리(SRAM)에 메인메모리(DRAM)을 더하는 방식으로 이뤄진다. 자주 참조되는 데이터는 캐시메모리에 저장되어 있기 때문이다.

### 1.4 Virtual Memory

각각의 프로세서마다 하나의 메인메모리가 있는 것처럼 동작하도록 하는 가상화기술. 하드디스크를 공간분할다중화(Space Division Multiplexing) 기술을 적용한다. 메인메모리(DRAM)과 하드디스크를 접목하는 방식이다. 메인메모리(DRAM)에 로드될 데이터는 하드 디스크에 저장되고, 그 중 프로세스가 자주 참조하는 부분은 메인메모리로 로드된다.

## 2. 가상 메모리 기술

CPU가 메모리에 접근할 때는 가상주소가 물리주소로 변환된다. 가상주소는 MMU(Memory Management Unit)라는 하드웨어 장치로 넘겨진다. MMU로 넘어온 가상주소는 TLB(Translation Look-aside Buffer)라는 하드웨어 장치를 참조해 가상주소가 물리주소로 변환된다.

* Page fault : TLB가 물리주소를 계산하지 못하는 예외 현상(Exception)
  * 원인 : 가상주소공간의 페이지가 물리주소공간에 없기 때문에.
  * 결과 : CPU 제어가 OS로 넘어가고 OS가 exception을 해결하는 작업을 시작한다.
    * 하드디스크에 있는 참조할 페이지를 빈 메모리 공간에 적재한다.
    * 만일 메모리가 꽉 차 있다면, 메모리 내의 페이지 하나를 하드디스크로 이동시킨 후 그 자리에 새로운 페이지를 적재한다.
    * OS의 작업이 끝나면 interrupt mechanism을 이용해서 CPU에게 알림을 준 후 page fault 처리를 마무리 한다.

### 2.1 가상주소(Virtual address), 물리주소(Physical address)

* 가상주소
  * 컴파일된 싪행 파일 내에 표현되어 있는 메모리 주소
  * 실제 CPU가 프로그램 실행시 읽는 메모리 주소
  * 고정된 크기의 페이지(Page)로 나눠져있다.
    * 일부 페이지는 Physical space page에 대응, 나머지는 하드디스크에 저장된다.

* 물리주소
  * 실제 메모리 주소

### 2.2 가상메모리 기술의 두가지 측면

2.2.1 구현(Functionality)

* 하드웨어
  * MMU(Memory Management Unit)와 'page fault' 같은 exception mechanism를 처리하는 매커니즘으로 구현한다.

* 소프트웨어
  * 페이지테이블(page tables)에 근거해서 가상메모리를 관리하는 OS 루틴으로 구현한다. OS에는 각각의 프로세스가 있다.

2.2.2 최적화(Performance)

Temporal Locality와 Spatial Locality로 page table 참조를 최적화한다. Spatial locality는 자주 접근하는 페이지로 페이지 테이블을 구성하게금 하고, 이로 인해 page fault가 줄어든다. TLB(Translation Look-aside Buffer)이 그 예다. TLB는 MMU가 가상주소를 물리주소로 변환할 때 참조하는 고속 보조기억장치다.