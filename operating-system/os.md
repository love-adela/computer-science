# 권한 분리
Read()), Write() 같은 권한이 필요한 일을 해야 할 경우에는 ecall을 사용(?)

Usercode 가 (권한이 필요한 )systemcall을 절대로 안 부른다. 따라서 무한루프만 도는 그런 일만 함. (while 문만 돌린다든지.)
OS가 돌아갈 chance 가 없는데 어떻게 하냐?
무한 roof 가 도는 동안 system이 100% 수행 안 하고 무엇을 하고 있나?

schedule 을 하면서 이런 저런 일을 해야 하는데 , systemcall을 안 부르면 OS가 안 돌아가는 문제가 발생함.
=> hang 된다.

CPU가 Usercode를 사용할 수 있도록 권한을 부여하는걸 빼앗는게 어렵다.
방법 : Timer라는 Hardware를 만들어서.

* Timer (Interrupt)의 기능?

- 죽을 때까지 주어진 주기로 (예를 들면 10ms당 한 번씩 깨어나서, 프로그래밍으로 조절 가능)interrupt 를 건다.
- 위에서 오는 System Call이 없다고 하더라도, interrupt 를 받으면 (하던 일을 그만두고, 설사 무한 루프를 돌고 있더라도) 주기적으로 얼마에 한 번씩은 OS가 권한을 부여 받음.
    * Halting Problem
    (앱 개발자가 잘못 개발해서) 앱이 이상하게 무한루프에 들어가는지 판단하는게 어렵다. 강제로 죽이는 방법 있냐?
    - 컴퓨터가 풀 수 없는 문제 중 하나: 어떤 프로그램이 끝날지 말지를 스스로 결정하는 것 (무한 루프에 들어가는지 안 들어가는지를 알아내는게 어려움.)

그래도 잠시 쉬게 하고 다른걸 돌리 수 있게 함.

* Non-cooperative approach: 프로세스의 협력을 기대하기 어려운 상황
* Coooperative approach: 간단한 일을 수행하는 로봇 청소기 등은 Timer가 없어도 버그가 없고 OS가 보기에 OS 위에서 돌아가는 일들을 신뢰할 수 있을 경우, 자기가 CPU를 쓸만큼 쓰고 특별한 Yield() (<- 스케쥴러를 돌린다가고?) 같은 Systemcall을 적절한 시점에 잘 불러주면 스케쥴링이 원활하게 된다.
  * OS가 User application을 Trust 할 수 있을 때 사용할 수 있음. (단 Bug가 있으면 안됨.)

Timer의 주기를 무한대로 설정하면 User가 나쁜 짓을 할 수 있겠지만 previliege opeation이기 때문에 User가 허튼 일을 할 수 없음.

* 요약
User가 하는 일을 제약하고, Curnel이 하는 일을 정해주고, User이 해야 하는 일이 있을 경우 OS 코드가 , OS코드가 중간 중간 돌아가게 하기 위해서 Timer를 마련함.

  * 문제점 : 다른 메모리 (user code, data, os code, os data, user code , user data 등이 들어있음)를 마구 쓸 수 있음. 문제는 CPU에서 메모리(하드웨어)로 접근하는게 Unpreivilieged. 따라서 메모리를 보호해야 함. Track handler의 내용을 바꿔버리면 무용지물이 되어버림.
  * CPU가 유저레벨에서 하드웨어 (I/O 장치, 네트워크 카드 등..)에 접근하는 걸 OS가 감시. OS에게 접근할 수 있는 기능을 요청했어야 하는데, 메모리를 그렇게 보호하면 (1000배, 10,000배) 너무 느려지기 때문에 그렇게 할 수가 없음.
  * 해결 : Memory에 접근하는데 OS가 끼어드는 순간, 너무 느려지기 때문에 성능을 위해서 HardWare가 끼어드는 수 밖에 없다.
    - 앗 그런데 지금 process에서 사용하고 있는 메모리 주소(?) 같은 정보는 OS가 정하기 때문에 CPU 혼자서는 판단할 수 없음. => CPU와 OS가 서로 협동해야 함.

### CPU & OS의 협동

* 과거: PRog에 Memory와 Data를 할당했다고 한다면. 하드웨어가 Prog, 잘못된 영역, 잘못된 메모리 참조하려고 하면 OS가 프로그램을 죽이면 됨. Common case에서는 하드웨어가 OS를 깨움.
즉, OS가 가지고 있는 정보를 하드웨어에 주고 그 정보를 하드웨어가 Runtime에 validation하고, 문제가 생기면 OS를 깨워서 나머지 처리를 함. 접근할 수 있는 메모리 영역이 연속되어 있기 때문에 조금 어려움. Embedded system에서 자주 사용. 

* 현재: Virtual Memory라는 기법으로 (Phasing, Table 생성, 컴퓨터구조시간에 배움.) 지원. Common Case가 없으면 하드웨어가 처리함.

=> Memory Protection을 위해 Hardware의 역할이 필요함.


### Synchronization

Thread 처럼 실행흐름들이(systemcall, interrupt) 커널 안에서 concurrent 하게 발생. (시스템 프로그래밍에서 thread programming을 했음.) 실행을 할 때 같은 메모리를 건드리면 concurrent 하게 실행되던 중에 수행이 되다 동일한 메모리를 참조하게 되는 문제가 있음.

해결 :Synchronization

* CPU가 하나밖에 없을 때 (Single CPU), interrupt 를 꺼버려서 원하지 않는 시점에 간단하게 막을 수 있음.
* 여러개(Multi core) 있으면 로컬 CPU만 꺼지고 다른 CPU는 계속 돌아가고 있기 때문에 문제가 생김. 따라서 별도의 lock이 필요함. => `spin lock`


#### Atomic Instructions

* OS Architecture에서 지원되는 Requires special atomic instructions
  * Read-Modify-Write (잘리지 않고 다 수행되게게
  *  Test-and-Set
  *  Comare-and-Swap
  *  LOCK prefix in IA-32
...

* 참고: concurrency를 다룰 때 더 자세하게 다룰 예정.

## Summary
* General Purpose 위해서 반드시 필요한 것들
* 없어도 되는 것 : Interrupt, DMA...
  * 80년대에 CPU를 만드는 회사(Sun, IBM 등)들이 OS를 동시에 보유하고 있었다. 그런식으로 다른 회사와 차별화시켰음
  * Linux 의 등장 이후로 단독적인 Chip을 만드는 회사는 Intel, AMD), 정도 밖에 안 남았고, 회사에서 만드는 것보다 Linux처럼 대규모의 사람들이 검증, 개선 등을 하는게 훨씬 효율적이기 때문에 자체적인 OS를 가지고 있는게 뭐.. 그렇게 장점이 없어짐.


## Homework

* 간단한 systemcall 발생
  
* 지난 번에 process 한 번씩 만져봤으니.. 유닉스계열에 있는 process group (여러개의 process를 묶고, ) Userlevel program인 setpgid()(): pgid로 바뀐다. / 쓰기), getpgid(): (/ 읽기) 라는 systemcall 사용
* parent process가 생성되기 때문에 parent group id 를 상속 받아서 쓸 수 있음.
* Initial Process : pgid 1번, setpgid를 부르지 않는 이상 모든 프로세스의 group id가 1이 된다.

ctrl + P 누르면 당시 돌아가고 있는 프로세스 리스특 나옴. 
1 (아이디) 1 sleep (상태) init(이름)-> 문서보고 다시 확인.


# OS Internals

What is a Process?
* An instance of program in execution (시스템 프로그래밍에서 공부함) 여러개의 프로세스가 돌아가게 됨.
  * Program : file 형태로 저장되어 있는 static한 프로그램 코드 / 프로그램을 돌린다, 프로그램을 카피한다. 그러나 프로그램을 죽인다<-는 잘못된 말. 프로그램을 지울 수는 있음.
    * code와 data의 초기값이 중요함. 
  * Process : 프로그램으로부터 만들어져서 실제로 수행되고 있는 프로그램. 프로세스 죽이고 살리는게 가능
  * Processor : CPU 의미

* The basic unit of protection : 기본적으로 메모리가 다 분리되어 있음
* A process is identified using a process ID (PID) -> PGID 를 만드는게 숙제
* A process includes : CPU context(resisters), OS resources(만든 사람, 상태, 온갖 정보)

From Program to Process 

Memory Disk

- Program: 실행 파일 형태로 되어 있는 것
- Process: Shell이 받아서 OS에 요청하는 것 ->  Code, data 를 읽어서 Heap(malloc등을 수행할 때 필요한 것), Stack

* Stack pointer : Stack의 탑
* PC : ?


Process 구현 방법 : 

OS가 실제로 어떻게 구현되어 있는지 알아보다 보면, Process 의 상태, 실제 구현은 어떻게 하는지를 알게됨.

Default PGID 초기값은 parent의 PID를 쓰면 됨. Parent 상속 받아서. 