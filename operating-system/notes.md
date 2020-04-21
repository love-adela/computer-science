수업 : http://csl.snu.ac.kr/courses/4190.307/2020-1/

---

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

Program과 Process

바이너리 넘버로 변환이 되어서 그 이미지를 . 
C에서의 global variable 에 대한 초기값을 묶어서 Disk에 있는 데이터에 바이너리 형태로 저장. 
Code 이미지와 Data의 초기값을 가지고 있는게 프로그램.

부가적인 메모리가 더 필요하다. Stack이라는 영역과 Heap이라는 영역. Local variable 등을 저장해야 하는 Stack이 필요함. malloc 같은 런타임을 지원하는 영역이 Heap. 
두 개 영역을 할당해줘야 하고. 

할당해준 스택의 제일 밑에 Stack Pointer 가 자라게 해서 CPU에게 Process 를 실행하게 함.

Process : an instance of a program in execution (실행 중에 있는 인스턴스)

Running a Process
- CPU의 지루한 일생 (Fetch/ Decode / Execute / Update)
- CPU는 32비트(4바이트)를 가지고 가서 : Fetch, 
- 무슨 명령어인지 Decode
- Execute : ALU / LD.ST / Branch 
- Update PC

<OS의 역사>

* CPU가 하나고 Process 가 하나면 문제될게 없다. 초창기 2세대, 한 번에 하나의 프로그램만 사용하는 MS DOS 시절.
  - 비효율적임. CPU가 항상 바쁜게 아니기 때문에. 
  - 키보드, 디스크, 네트워크로부터 중간 중간 자주 IO를 해야 한다.
  - IO가 끝날 때까지 CPU가 놀아야 하기 때문에.. 
  - 효율성이 낮음.

* 여러개의 Process를 돌리고 싶다면.. -> 메모리는 여러개 있을 필요는 없고 여러개의 CPU 를 써서 동시에 여러개의 프로세스를 돌릴 수 있음.

* Interleaving Multiple Process

  - I/O를 타겟으로 했었음.
  - Multiprogrammed OS -> Time sharing I/O
  - Yield() 라는 시스템 콜을 만들어서 다른 IO를 쓰라고 말할 수는 있지만, 그걸 Process 가 일일이 처리해야 한다. 
  - 따라서 OS의 스케쥴러(scheduler)의 역할이 중요.
  - hat (hardware thread) 초기화 할 때까지 기다리고 있따가 초기화 끝나면 실행을 개시. 모든 CPU가 Scheduler routine 에 들어간다.
  - CPU를 던져준다 (CPU가 어떤 프로세스를 실행시키도록 하는 것)
    - Kernel 모드에서 User 레벨로 바꿔주려면 (Exception, Interrupt)
  
Physical CPU는 하나인데, OS가 각각의 프로세스가 있는 것처럼 Virtualize
  - OS creates the illusion that each process has its own CPU and memory. 
  
epc : sepc,... 

Example: Creating a Process
```C
#include <sys/types.h>
#include <unistd.h>

int main() {
  int pid;
  
  if ((pid==fork()) == 0)
    printf ("Child of %d is %d\n", getppid(), getpid()); /*child*/
  else
  printf("I am %d. My child is %d\n", getpid(), pid); /*parent */
}
```

rsv6에서 userinit() 함수 부분에 init, pid:1d

Process Hierachy
* Parent-child relationship
  * One process can create another process
  * Unix calls the hierachy a "process group"
  * Windows has no concept of process hierarchy
    `$ cat file | wc`

  우리가 아는 전체 CPU 중에 Intel CPU가 2,3%. OS 없이 돌아가는 것도 있음.
  Linux 계열의 OS가 대부분. Windows NT는 거의 미비. 
  RealtimeOS, Embedded OS, Linux 의 변종. => Unix 계열의 OS가 대부분

Process Creation
  fork(), exec()를 분리하면?
  - IO Redirection
    `$ ls > a.txt`


Time Slice = Scheduling Quantumn

Timer interrupt 의 배수로 결정된다.
Process를 OS가 어떻게 구현?

Process 그룹에서 .
  - Accounting information:

Context Switch

서로 다른 프로세서끼리 OS를 실행히셬  스케쥴링을 할 때 정보를 공유


서로 다른 프로세스끼리 OS를 실행? 동일한 정보 공유? -> 말도 안되는 소리임
프로세스 : 시스템 콜, 
프로세스가 돌다가 중간에 인터럽트가 걸리고, 중간에 스케쥴러를 불러야 하는 일 있으면 커널이 부른다.

타이머 인터럽트: 주기적으로 있는 것. 
타이머 인터럽트 핸들러에서 지금 현재 돌아가고 있는 프로세서가 남아있는지 호가인.
컨텍스트스위치가 되는 건 커널 안에서만 되는거고, 컨텍스트로 다시 돌아오는 경우엔 컨텍스트스위치가 없었던 것처럼.. 을 구현

Trapframe?
  - 트램펄린
  - User 프로세스의 상태 (<- User Thread)
  - 커널 (<- Kernel Thread 에서) 에서 가지고 있는 레지스터의 state : xv6에서는 context라고 함.
  - User 모드에서 걸리다가 systemcall 로 돌아가면 trapframe 에 그 순간 레지스터의 상태를 저장. 
  - 돌아왔을 때의 레지스터 상태를 복구해야 돌아왔을 때 아무일도 없었던 것처럼 함. 
  - Trapframe: User 프로세스에 있던 걸 interrupt, exception 직전의 상태를 저장. 의미 있게 쓰는건 stack counter, pointer 정도 밖에 없고 나머지는 큰 의미가 없게 되는 것.
  - CPU가 자동으로 저장하는건 하드웨어가 하지 않고 프로그램 카운터 같은 OS가 하도록. CPU는 미니멀한 일만 하도록. PC만 바꿈. 

# 3주차 금요일
---

## Implementing Processes(Process 구현방법)

PCB (Process Control Block or Process Descriptor)
- OS마다 이름이 다름 (Linux : Task Structure)
- OS 입장에서는 프로세스를 하나 만드는게 엄청난 부담. (시간이 많이 걸리고, 초기화해야 하기 때문에.)
- 포인터에 연결된 자료구조가 줄줄이 달려 나옴 (?)

## Context Switch

Process A가 실행되고 있을 때 IO나 Timer Interrupt가 발동되어서 Process B가 작동되어야 한다고 할 때 CPU가 끊고 B를 실행시키는 것.

* Process : CPU state 가 별거 없고 가지고 있는 레지스터의 값들. (?)

Register의 종류

- User
- System Register

* Context Switch를 자주 쓰면 Overhead 가 발생
  - 1초에 수십?수백번? 정도 (CPU 발전 속도는 엄청 빨라졌음에도 불구하고 70, 80년대의 횟수와 다름 없음횟
    - 사람 감각으로 '동시에 하고 있구나' 느낄 정도만?
  - Cache의 TLB miss? Datastructure가 계속 바뀜

```
$ cat /proc/uptime # 10738129.85
$ grep ctxt /proc/stat # 6770575dfadsf
$ echo "10738129.85 / 6770575dfasdf"
```

## Performing Context Switch in xv6

두 개의 프로세스가 있고 현재 프로세스 A를 실행하고 있따고 할 때.. 
  - 보통은 Interrupt 를 처리하고 돌아가는건데.. (하던 일을 중단하고 kernel이 처리해야 할 걸 처리하고..)
  - Context Switch가 다른 점은 Interrupt 처럼 들어오긴 했는데 Process A에서 와서 Process B로 나감. (프로세스 입장에서는 다른 걸 돌리고 다시 오는 느낌)
  - CPU 레지스터를 아무 일 없었던 것처럼 복구
(1) Timer Interrupt 가 시작 : Timer Interrupt의 주기와 Timeslice의 주기와 같음
* CPU(RISC-V)가 하는 역할 - H/w적으로 한 번에 일어나는 일
  (2) 현재 갖고 있는 프로그램 카운터의 값을 Set sepc(supervisore..)에 넘기고
    - sepc 는 한개 밖에 없음
    - sepc를 가지고 돌아갈 곳을 결정
    - 그러나 메모리가 바뀌었기 때문에 User page table 에서 바꿈
    - 바꿔준 메모리에서 어디로 돌아갈지는 sepc 에서 저장이 되어 있음
    - program counter 가 ...? 뭐?
    - sepc를 변조하는건 OS가 하고, sepc를 PC로 업데이트하는건 하드웨어적으로
  (3) Disable interrupt
  (4) Change to kernel mode
  (5) stvec에 있는 값으로 PC를 업데이트하면 트랩핸들러에 있는 것(?)이 실행될 준비가 됨
  * (1) ~ (5)는 atomic 하게 진행. 아주 빠름.
* Kernel이 하는 역할 - S/W적으로 일어나는 일
  (6) Trap handler 
  (7) Trapframe 에 있는 user regs 에 저장/백업함
  (8) User가 사용하는 메모리와 Kernel이 사용하는 메모리를 분리
  (9) A의 상태를 running -> runnable 상태로 바꿈
  (10) 커널로 들어와서 레지스터를 썻을 때 프로세스 A가 switch 되기 전의 상태를 보관해야할 필요가 있음. -> 깨어났을 때 나가야 하기 때문에.
    - 커널이 쓰는 모든 주소도 virtualize. 
  (11) 
  (12) sret (s return)을 하면 다시 User 모드로 바뀌면서 interrupt 가 걸리고 그 당시 명령어를 가져오게 됨.

* xv6- book을 10번 정도 읽어보면 도움이 된다. 그 책에 있는 내용을 이해할 정도 되면 이 코스 다 끝난 것.
  * trap, schedule, lock 같은거 ... 
  
## Process State Queues

* 지금 프로세스가 running 상태에 있는 것들, runnable 상태에 있는 것들
* 예를 들어 시스템에 100개의 프로세스가 있을 때 몇 개만 Runnable이고 나머지는 다 block인데 그 중에서 돌아갈 수 있는걸 다 뒤지는게 비효율적이기 때문에 queue로 만들어두면 됨. (runnable 하는 애들을 묶어놓는 것 : run queue나 ready queue라고 함)
 * OS의 (보통 리스트로 구현)
 * Proc이라는 Datastructure가 array로 되어 있음. PID 3번에 해당하는 proc들.. 
   * 단점1 : array에 할당된 것 이상으로 proc을 만들 수 없음. xv6에는 NPROC이 64로 설정되어 있음 -> 이렇게 static 하게 쓰는 방식은 요즘 쓰지 않음
      * 리눅스 같은데서는 linked list 같은걸 사용
   * 단점2: load를 다 돌면서 찾기 때문에 비효율적. 빈 엔트리를 다 돌 필요가 없음. 돌아가고 있는 process 만 찾으면 되기 때문에.
      * 어느 프로세스가 뒤지고 있냐를 알고 있는건 또 말이 안됨.
      *  DISK IO에서 interrupt 되는 걸로

* PCB는 리눅스에서 task_struct와 같은 것


## Implementing fork()

* fork: A에 해당하는 proc structure 은 이미 만들어져 있고.. (PID, PGID 같은..), 메모리에 해당하는 정보도 있기 때문에 fork는 A와 똑같은걸 만들어줌
* Track frame 에 저장.
* xv6에 비어있는 structure에 . 비어 있는 PID 설정, 나머지는 copy.
* 포크 했을 때 포크된 당시의 state를 정확하게 만들어주는 것 (메모리를 카피해서 가지고 있음). parent가 쓰는 걸
* Track frame 에서도 나가야 하니까 copy
* return value (Track frame의 레지스터에 해당하는 부분을 넣고 runnable 한 상태로 만들고)
* parent 와 다른 것 ? 레지스터의 return value 가 변경되었기 때문에 다른 .  table 등은 그대로 카피된다.

## Implementing exec()

* Proc structure 같은건 그대로 있고 pid 등 그대로 있는데, 메모리만 바뀜. 
* DISK에서 bin의 ls에 해당하는 실행파일을 찾고 그것의 code와 data를 복사해서 . exec() 부르는 것 : duxoRkwl rkwlrh dlTsmsrj rmeofh skfflrh zhemdhk epdlxjfmf . heap과 stack을 초기화. 새로운 실행파일의 이미지를 초기화. 
* 나갈 때 trapframe에 예전 state가 저장되어 있긴 하지만 글루 돌아갈게 아니기 때문에 그 trapframe 을 사용하지 않음. 변조된 trapframe을 사용. loading 한 entry point로 초기화, stack 을 top을 가리키도록 하고 trapframe에 있는 레지스터를 수정한 다음 exec() 로 돌아가면 프로그램 처음으로 돌아가게 되는 것.

* fork와 exec 맘만 먹으면 구현.... ;;

## Policy vs Mechanism
- 구분 이유 : 규모가 큰 OS 디자인 시, 이를 구분해서 구분하는게 좋다.;

* Policy(정책) :
  * OS에서 구분해서 쓰는 용어.
  * 예를 들면 다음 프로세스에서 어떤 걸 선택할거냐. 
  * resource allocation 어디로? scheduling problems는 누구에게?
  * process 마다 priority가 제일 높은 애
  * 그때그때 바뀔 수 있도록 권장. 다음 OS 업데이트 때는 바뀐다거나..
  
* Mechanism(매커니즘) :
  * 어떤 policy를 구현하기 위해서 어떤 datastructure, algorithm이 있어야 하느냐.
  * 예를 들어 process 마다 policy를 가지고 있어야 하는데 
    * 트리 같은걸로 미리 소팅을 해둘 수 있고.. 
  * Policy가 바뀐다고 해서 새로운 자료구조를 만드는건 굉장히 부담이 되고 개발 때도 안 좋으니, policy와 분리해서 general하고 다양하게 policy를 서포트할 수 있도록 함.

## CPU Scheduling

* Mechanism
  * context switching
  * priority를 어디에 저장?
  
* Policy
  * scheduling policy

## Scheduling Basic Approaches
* Non-preemptive scheduling (=cooperate scheduling)
  * ~ 때까지 .
  * timer interrupt 같은거 필요 없고 프로세스가 돌아가다가 스스로 yield()함.
  * 상호협조적으로 돌아가는 스케쥴링 방법
  * 돌아가는 프로세스들이 서로 믿을 수 있는 관계, 나만 손해인 환경에서는 강제로 timer interrupt 할 필요 없는 경우가 많음. OS를 간단하게 만들기 위해서. 
  
  
* Preemptive scheduling
  * preemption: 원래 Process 의지와 상관 없이 다시 회수에 가는 것. 
  * General purpose OS에서는 이 방식. timer interrupt 가 항상 필요.식

## Terminologies
* workload: 각각 실행할 job의 묶음
  * e.g., arrival time, run time, etc
* scheduler
  * a logic that decides when jobs run
* metric
  * measurement of scheduing quality
  * e.g. turnaround time, response tiem, fairness, ..

## Workload Assumptions

1. 모든 job은 항상 동일한 시간을 돌고
2. 모든 job은 동시에 도착
3. 한 번 실행되면 IO 방해 없이 돌아가고
4. 모든 job의 실행시간이 알려져있고 

Turn arround time : 제출해서 arrival time 까지의 시간

## FIFO

1. First-Come, First-Served , 온 순서대로 처리
  * 언뜻 공평해보이는 방법
  * Non-preemptive (마트에서 우유 하나 집었는데 앞에 한 카트 계산할 때까지 기다리고 있는 상황)
  * Problems: Convoy Effect - 빨리 끝나는 애들한테 불리
  * 장점 : 기다리면 내 순서는 옴

## SJF (Shortest Job First)

* assumption이 틀어진다. 어떤 실행시간은 너무 길고 어떤건 너무 짧을 때
* Non-preemptive - 같이 도착하기 때문에...
* Problems: 
  * 동시에 도착했을 때 turn around time이 최소화시킬 수 있는 방법이긴 하지만 뒤늦게 빨리 끝나는 친구 오면 optimal (x)
  * Starvation 
  
## FIFO vs SJF 
  * FIFO : A는 0에 도착해서 10애 끝나고 B는 10에 끝나서 20에 끝나고, C는 30에 끝나고...
    * 동일한 runtime이라는 assumption 풀면 turnaround 많이 걸림
    * preemption 하지 않음

  * SJF
    * average turnaround tinme이 훨씬 적게 만들 수 있는 여지가 있다.
    * arrival time이 다르면. 긴 job이 0에 들어오면 실행시켜주고. A가 다 끝나야 B, C를 할 수 밖에 없는.. 
    * preemption을 하지 않는다고 하면, 긴 job인 A가 왔을 때 일단 B를 기다려봄. 문제는 언제 도착할지 알 수 없는게 문제. 

* Scheduler
  * work-conserving scheduler
    * 대부분 이 방식을 쓴다.
  * Non work-conserving scheduler
    * 할 작업이 있는데 일부러 놀고 있는 것
    * 전체적으로는 좀 기다렸다가 하는게 더 좋을 수도 있다.


preemtion 하기 좋은 
* CPU : 가지고 있는 state 양이 적기 때문에 preemption이 쉬움.


## STCF (Shortest Time-to-Completion First)

* 런타임 전체는 보지 않고 남아있는 시간이 작은 애만.
* preemption 대기 때문에.
* Job이 동시에 도착하지 않아도 쓸 수 있는 방법. 
* turnaround time이 엄청 줄 수 있음.

* SJF의 preemption 하는 버젼
* Time sharing 이 나온 이후로 새로운 metric이 나옴.

* Response time : shell에서 커맨드를 친 순간 스마트폰에서 터치를 했을 때가 arrival time. firstrun은 프로세스가 실제로 개시된 시점
  * 빨리 반응해줘야 함. 반응시간을 보는 것

## RR(Round Robinn)

* time slice(scheduling quantum)만큼 실행하고 간격을 두는 것.
  * timer interrupt period or timer **tick**
  * starvation 없고
  * preemption
  
* FIFO 로 얼마 이상 실행.
* Overhead가 증가되기도. respose time이 증가해서. 
  * 터치할 때 너무 늘어지면 반응성이 떨어짐. 
  * 10 ~ 100ms 정도로만 써야. 

* Time sharing 하겠다고 하는게 왜 좋음?
* Problem?
  * 너무 공평하다는 것. 프로세스가 급하든 안 급하든 다 똑같이 실행.

---
CPU scheduling

Time sharing
  - IO 없이 CPU를 계속 쓰고 싶다고 할 때 Time sharing을 씀

- Round Robin
  - Time slice (= scheduling quantum)

Timer Tick의 배수


Policy : Process 마다 Timeslice 를 배정

Priority Scheduling

- RR을 포함
- 필요하면 몇 몇 프로세스에는 priority를 높게 줘서.. 
- Static priority
  - 타고난 priority.
  - 계속 갖고 있는
  - run time 에 올라갈 수도 있고 내려갈 수도 있고.
  - 프로세스마다 priority
    - systemcall을 활용해서 priority를 조절할 수 있음.  
      - 예를 들어 유닉스 계열에서 가장 유명한 nice() -> nice값이 priority가 됨. 
      - -20 ~ 19 까지(40단계) 일 때 , nice value 가 0일 때 default.
        - nice가 음수값이 되면 priority가 높은 것
        - nice 가 점점 커지면 low priority
          - 자신이 priority를 떨어뜨릴 수는 있지만, 높일 수는 없음. root 권한이 있는 관리자만 높일 수 있음. 아무나 다 높이면 안되니까. 
  - priority가 같은게 있으면
    - round robin을 쓸 때 preemptive priority scheduling (돌아가는걸 그 즉시 중단시키는 것), non preemptive priority scheduling 할 수도 있음. 
  - round robin은 timeslice 를 줘서 스케쥴링하고. 
  - FIFO면 A 다 끝나면 B를 시키는. 
  - 보통은 RR를 쓰고 FIFO는 잘 안 씀. FIFO는 ~ 문제가 있으니까. 
  - 보통은 preemptive scheduling 을 함.
  - Prirority의 단점 : starvation (계속 높은 priority만 처리해서 낮은 priority의 애들은 CPU를 못 받아서 굶어 죽음)
- Dynamic priority


incorporating I/O
* I/O - aware scheduling

* CPU bound process
  * 높은 priority를 주려고 함.
* IO bound process
  - Disk, Keyboard, network acess
  - Interactive한 process
    - IO를 할 때 User를 상대하고 계속 interaction하는 것
    - CPU bound process 랑 구분해서 쓰려고 함.
    - 
  - Non-interactive process
    - 크게 신경 안 써도 됨.


CPU burst, I/O Burst
* CPU burst : time slice 가 다 되어서, 또는 IO를 해서 빼앗긴 상황에서 
* IO Burst

Scheduler Goal
* CPU의 Utilization을 올림
* Cache algorithm...LRU algorithm, branch prediction
  

MLFQ (Multi-level Feedback Queue)

* 같은 priority에 있으면 걔네들 끼리 RR.

Changing Priority
* 누가 CPU를 쓰는지 모름
* 주어진 Time slice보다 빨리 하는 애면.. 떨어뜨리고. 

Priority Boost

* malicious user(악의적인 user)
  * Time slice가 되기 전에 일부러 CPU를 둔다.

## Summary : Unix Scheduler
* MLFQ
* Favor interactive processes over CPU-bound processes
* Use aging : no starvation
  * priority가 낮아도 wait time이 자꾸 증가하면 (IO를 포함해서) 
  * 기다리면 어느 순간 priority가 높아지는 방법 (온갖 주술적인 constants를 가지고 휴리스틱을 가지고 복잡하게 사용)
    * OS 마다 원칙은 동일하지만 방식은 조금씩 다름.

Priority : 
Timeslice : 스케쥴이 되었을 때 얼마동안 할거냐.

## Linux CFS (Completely Fair Scheduler)

리눅스는 몇 가지 버젼의 스케쥴러가 있었다. 

여러가지 클래스가 있는데 별로 안 중요.

### Linux Task Priority
* Total 140 levels : [0, 140)


Nice to Weight

Priority와 Share 간의 연관성을 만들어줘야 함

floating point 를 가급적 안 
스려고 함
  * weight의 값을 변환하고
  * ₩
  * 

Virtual Runtime : normalize 해두고 . 상대적으로 다 비교해둔 것이기 때문에 
최소의 virtual runtime : 
  스케쥴링할 때 누굴 선택해야 하는지 알아봐야 할 때, Tree 같은데 소팅을 함. R-B 트리를 사용. 어느정도 밸런스된.. 소팅을 해서 왼쪽에 있는 가장 최소값을 찾음. 
  Timer interrupt가 v runtime 을 갱신하고 

CFS에서 time slice 를

MLFQ 방식으로 모든 스케쥴러마다 각각 다른 방법을 씀. 

CFS는 간단해졌다. 어쨌든 내가 Wait에 따라서 Share를 마치겠다. -19~20 사이에 있는 연동 값을. 

Block 되어 있다가 CPU를 못 쓰고 있는 애들한테 보상을 어떻게 해줄 것인지. 

- Block되어 있다가 깨어날 때
  - interactive 할 가능성이 높기 때문에.
  - 어떤 방법으로든 priority를 높이는 방법
  - 보상은 어떻게 해줄 것인가?
    - 과거의 linux scheduler?
      - 아무리 오래 기달려도 원래 자기 time slice의 2배를 넘어가지 않게. 

vruntime이 계속 증가하는데, 나중에 overflow가 나지 않겠냐. Linux에서 예전에 쓰던 트릭이 있다. vruntime이 unsigned integer 계산을 Vruntime에 해주는 것. 


Runqueue

`a-b`를 signed integer로 type casting을 해서 overflow가 나도 괜찮음.

minimum은 1/8 정도일 때 time slice가 기본적으로 많지 않으면 특정 주기 안에서 돌린다. 내가 쓸 수 있는 시간이 몇 개인지에 따라서 달라짐. Default로 p라는 주기가 6ms 로 정해짐. 

=> CPU virtualize

Process 만들면 OS가 알아서 해줄게.
Process 위에 각각의 virtual CPU가 있는 것처럼 동작.

# Virtual Memory

## GOals

1. Transparency
프로그래머에게 쓰기 쉬운 abstraction을 제공
  - 프로그램에는 메모리가 프로세스마다 충분히 제공하는 것처럼 실제 Process에 share 하는 것이기 때문에. (16G, 32G, 8G) 
  - 아주 큰 memory space가 연속되어 있는 것처럼 process에 virtualize. 현실과의 간극은 OS가 알아서 해주셈.

2. Efficiency

- Physical memory가 8GB로 제한되어 있을 때, 연속되어 있는 메모리 공간이 지워지고 할당되는 과정을 반복하다보면, 짜투리(External fregmentation)가 남게 된다. 짜투리를 연속되게 해주는 것이 필요함. -> virtual memory를 쓰면 효과적으로 바뀔 수 있다. 

3. Protection
허용되지 않은 메모리에 접근하는 걸 막아야 한다. 접근하는 과정에서 OS 가 매번 끼어들 수 없기 때문에, 문제가 없는 경우에는 하드웨어가 서포트가 필요함.

### Accessing Memory

0x08804x1 <- virtual memory address

### Virtual Address Space

32bit: 2**32바이트
64bit: 2**64바이트

- 코드영역 (instruction을 compile하면 C언어가 assembly언어로, assembly언어가 Binary Number로..)


초기화를 시킨 `int g = 1;` 명령ㅇ어는 data에 저장하지만.
- Bss 영역
초기화가 안된 `int x;` 변수는 필요한 사이즈가(int, char, pointer) 몇 byte 필요하냐. 알아보기 때문에 실행파일(execute file, 즉 program)에 매번 저장할 필요는 없음. 

- heap

PC를 가리키게 되면 다시 프로세스가 돌아감.

32bit 머신에서는 1bit를 꽁쳐놓고
64bit 머신에서는 32bit넝도를 꽁쳐놓아서 
커널이 메모리가 필요할 때마다 커널이 쓰는 메모리 영역을 . User는 접근을 못하게 하고, systemcall()를 해야지 접근이 가능하도록 함. 

meltdown attack? pipeline이 out of order 등의 상황이 발생할 때 cache에 permission이 안되게 exception을 체크해야 하는데.. 얘가 죽더라도 cache 내용을 잘 뒤져보다 보면 어떤 데이터가 커널에 있는지 훔쳐볼 수 있었음.

이후 커널의 address에 있는 영역을 따로 지정. xv6도 그 방법을 사용함. User가 사용하는 address space가 따로 있음. systemcall()을 하면 바뀌자마자 .

현재는 User용 address space, 커널이 사용하는 address space를 따로 배정함.


## Virtual Memoery

idea

* 실제 메모리에 접근할 때 진짜 물리적인 주소로 변환시켜서 쓰게하자.
  * 매번 address translation을 해야 하기 때문에... time, space overhead 가 많은 방법이지만.. virtual memory가 제공하는 기능이 워낙 유용하기 때문에 CPU가 이 방법을 택함.
 * 예를 들어 택배 안심번호. Virtual 전화번호. 진짜 전화번호는 Physical 전화번호.
   * 실제 physical한 주소와 다른사람에게 알려주는 주소를 분리시키면 다음의 이점이 있다. 
     * 실제의 자료와 이어주는 것만 하면 바뀐 전화번호를 실제의 것처럼 사용할 수 있음.

  * Mac address : Network마다 하나씩 붙어있는 고유 번호. 걔와 관계 없는 logic address는 IP address. IP address 와 Mac address 를 연결해주는 protocol이 있는.. 아이디어와 유사. 

* lazy allocation 
  * 실제 access 되지 않은데.. 
 * 누가 전화를 하면 그때 할당해주는 방법. 
 * memory가 제한되어 있을 때, 
   * disk로 백업. virtual address로 접근하는데 어느 곳에 . access 하도록. Virtual memory의 여러 테크닉 중 하나. 

* Virtual Memory
  * P1's address space

  * P2's address space

address translation mechanism으로 VA(Virtual Address)가 PA(Physical Address)로 translation되는데 그 과정을 address translation라고 함.

OS가 메모리를 보고 CPU


Process마다 따로 번지가 있으니까 CPU가 information을 Code/data/Heap/Stack...으로 바꿈. 

Pros:
Cons: 
- User가 자기에게 할당된 이상의 메모리를 써도 어떻게 할 방법이 없음. Protection이 안됨. 
- 한 번 조절했으면 옮길 방도가 없다.

## Dynamic Relocation

따라서 대부분은 하드웨어의 도움을 받아서 빠르고 protected된 방법을 쓰게 됨. 

* Implementation
  * Physical Memory
  * Fixed Partitions
    * Virtual address에서 loadstore() 명령어가 나올 때마다, Base register에 저장. Context 
    * Degree of Multiprogramming : Fixed partition에서 partition 1 개는 프로세스 1개다. 


## Fixed Partitions(2)

* Cons
  * Internal framentation : External framentation과 달리 이를 막는 방법은 고정된 크기(의 배수)로 할당. 고정된 공간 내에 1바이트 당 낭비되는 공간..

## Fixed Partitions (3)

파티션 사이즈를 픽스시키는게 아니라 개수를 정해놓고 함. 그것이 설사 variable이라고 하더라도.
IBM OS (60?70s)에서 파티션을 여러개 만들고 그 사이즈를 동일하게 두진 않게 됨. 

* Cons
  * partition에 들어갈 job들이 queue에 대기하고 있을 때 (메모리 요구량은 확인할 수 있음.)

- Job scheduling (policy)
큐를 하나만 만들고 : first fit
큐에 기다리고 있는 것 중에 하나를 정하는 것 : bbest fit

## Variable Partitions (1)
* Used in IBM OS/MVI

이제는 파티션의 크기가 완전하게 랜덤하게 바뀔 수 있으니까 Limit register를 하나 두고 길이가 늘어나면 fault(exception)을 내고, 아니면 virtual access에 냄. 

* Cons
  * Variable 사이즈로 할당되면 External fregmentation으로. 
  * 하드웨어는 레지스터 하나 추가되는 것 정도는 문제가 없지만.. 
  * No partial sharing : can't share parts of address space.

## Segmentation

여태까지는 하나의 프로세스에 큰 address 공간 하나를 보여주고 (포인터가 0에서 n-1을 할당해서) Code, data, heap, stack을 저장했다면.. <- 그 안에서 나눠 갖게 하는

- 여러개의 segment를 나눠서 쓸 수 있게 프로세스에 지원함
  - segment?
    - 코드만 저장하는 segment
    - data segment (필요에 다라 data1,data2, data3, ...)
    - stack만 
    - heap
    
* Pros
  * Protection을 segment 단위로 할 수 있음
  * kernel만 접근할 수 있게 설정할 수도 있음
  * Code(fixed), Data(fixed), Heap(자라는), Stack(자라는) 속성을 부여할 수도 있음. 
    * OS가 결정해주면 되고. 
  * system 관리는 이들을 저장해서 사용할 수 있도록 함. 

필요하면 compaction을 해줘야 할지도 모르고. 프로세스 입장에서는 좋을 수 있는..

Segement 안에서의 offset
- Virtual address : <Segment#, Offset>
  - intel CPU에는 Sementation의 잔재가 남아있음 
    - 직므은 별 의미 없이 쓰임. 

Segmentation : Addressing

00번 segment의 offset
01번 segment의 offset
...
연속할 필요 없이 별도로 만들 수 있음. 

Stack: intel에는 push(), pop() 같은 명령어는 stack에 있음. implicit하게 


## Segmentation: Implementation

* Segmentation table
  - Base는 어디, limit 크기는 얼마, Dir 방향이 어떻게 되는지 protection은 어떻게 되는지를 표로 나타냄. 
    - protection 검사에서 RO를 해야 하는데 write를 하려고 하면 exception을 발생시킨다거나. 

* Pros
  * 

* Cons
  * Variable 사이즈로 만들어두는게 어려움. Compaction을 하면 되긴 하는데 그게 어려움. 자바에서 오브젝트가 죽으면 리젝션을 만들긴 하는데 그 자체가 엄청난 오버헤드. 
  - User 입장에선 좋을 수 있지만 Process 입장에서는 메모리 관리가 굉장히 어려움.

  * sement address가 링크드리스트로 포인터를 만들게 되면 이 주소에 segment 번호를 담고 있을 때, 5...로 시작하게 된다면
  Process2가 6번 segment를 맵핑했다. 5번 segment로 가게되면. 

  * 가변적인 메모리를 사용하는게 OS입장에서는 부담이 되는게 Segment의 단점이 됨. 

---

- 프로그래머에게 연속되어있는 것처럼 보여주는게 virtual memory 


## Segmentation

* virtual memory를 구현하는 옛날 방법 중 하나.
  * Process 에 가변적인 크기 (segment 단위) 몇 개 
    * segment: process가 진짜 사용하는 영역
    * `segmentation violation` ? : (1024 B 같은 segment의 바깥을 사용하는 영역을 쓰고 있다.
  * 가상메모리가 크다고 해서 모든 가상적인 공간에서 마음대로 쓸 수 있는건 아니다. 실제로 사용하고 있는걸 OS가 tracking하고 있고 나머지는 Error로 판명.

* 요즘 : Paging 기법
  * linear한 space를 프로세스 하나당 던져줌.

smartphone에 들어가는 ARM CPU
- Cortex-A : Virtual memory를 무리 없이 다 사용할 수 있음.
- Cortex-R : Memory protection Unit이라는 것이 segmentation 역할을 한다.
- Cortex-M : Embedded system용. 모든 address가 physical address. Memory protection 안됨.

** 어디까지가 CPU 어디까지가 

## Paging

4K boundary로 동일하게 자른 것.
보통 paging 크기 : 512B ~ 8KB.

* (Page) Frame : Physical memory의 한 조각
* Page : Virtual memory의 한 조각

Physical memory와 달리 가변적인 것들에 대한 요구를 들어주는게 굉장히 힘들다. 

**No external fragmentation** 
- 대신 다른 형태의 fragmentation이 있음. 대신 internal fragmentation이라는게 있다. 만일 4바이트가 필요하면 4kb를 할당해야 함. 4kb 안에 있는건 연속되어 있음.

* Page table : 정보를 유지하는게 page table.
  * Process 별로 따로 있음.
  * OS가 관리함. (Cpu는 page table을 참조하는 역할만 한다.)
* Page table Entry : Frame 9에 가있다.

virtual address를 physical address로 바꿔줘야 함. 

트램플린에 들어가는 내용은 트랩 핸들러의 위치가 들어감.문제는 커널 모드로 바뀌면, paging table 이 바뀌기 전 상황이 오기 때문에. 

Trap frame은 레지스터 별로 하나씩 따로 있어야 함.

### Address Translation

보통 |VA(Virtual Address)| >= |PA(Physical Address)|

Physical memory의 사이즈는 architecture 일부는 아님.

## Protection

### Separate page table for each process

Virtual space가 process 별로 하나씩 나오기 때문에 page table을 변조한다. Page table은 커널이 관리하고 유저가 함부로 read/write 할 수 없음.

* e.g CR# in x86, satp in RISC-V

### Page-level protection

* Finer level of protection is possible for valid pages

  * execute-only protections : instruct를 fetch할 때만 쓸 수 있음

## PTE (Page Table Entry)

## Demand Paging

## Handling Page Faults

* malloc (1024 x 1024)
  * virtual memory space 영역만 잡고 physical memory space에는 할당되지 않음.
  * header, footer를 찍어야 함. 즉 메모리에 직접 할당해야 함.(?)

## Page Fault

invalid PTE를 접근할 때 CPU에 발생하는 예외

### Invalid page faults

* e.g : core dumped

### Major page faults

Valid한 것인데 아직 physical로 올리지 않는 경우도 있음.

### Minor page faults

디스크 IO로 없이 해결할 수 있는 Page faults. Heap, Stack이 그 예다.

---
# 6주차 화요일

## Paging : Pros

* No external fragmentation
* Fast to allocate and free
* 디스크로 보내기 쉬움. (요즘은 4KB로 확장되어서 4KB 배수로 보낼 수 있음.)
* Protect와 Sharing이 용이

## Paging : Cons

* 요즘은 크게 문제는 안되지만 Internal fragmentation이 발생

* Time - Memory reference overhead
  * 안 그래도 느린데..

* Space - Storage needed for page table
  * Page table 크기가 꽤 된다.
  * solution : store valid PTEs only or page the page table

## Paging with Segmentation

### Paging with Segmentation Example

* Multics (Unix 이전에 야심찬 프로젝트) 에서 address translation
  * segment를 page별로 나눠서 흩어놓겠다
  * segmentation을 안 쓰면 위치에 따른 사용 여부를 확인할 수 없다. 

### Paging with Segmentation: Pros and Cons

* Pros
  - 물리적으로 연속되어 있을 필요가 없기 때문에 편하다. (page table는 segment 의 최대크기만큼 만들면 안된다는)
  - page나 segment를 공유할 수 있게 flexible 한 형태다. 
    - 문제
    - 1. segment 자체는 유동적이지만, page table이 segment에 비해 (entry 개수가) 가변적인 메모리를 할당해야 함.
    - 2. 큰 Hash table 같은 자료 구조가 있을 때...

### Linear vs Multi-level Page Table

## Multi-level Page Table

* PDBR()

** Page directory의 physical address가 있음.  크기가 한 page 크기를 넘어가면?
커널이 켜지면 Virtual Address를 슴. 



## Multi-level Page Table: RISC-V

* Sv32
* Sv39
* Sv48
  * Intel 것과 비슷
  * 48-bit virtual address -> 56-bit physical address
  * 더 쓰면 57-bit를 쓰긴함

## Multi-level Page Table

* Pros
  * sparse-address space를 지원하는게 콤팩트함
  * 물리적인 메모리를 매니징 하는게 쉬움
  * "walk" : Cpu가 page table을 뒤지는 과정

* Cons
  * 'TLB'라는 메모리 접근을 사용함

## Inverted Page Table

* Forward mapping: VA -> PA
* Backward mapping: PA-> VA
* VA는 공간도 크고 프로세스 양 때문에 맵핑 정보의 양도 엄청 많음.
* 장점: PA에 필요한 만큼만 맵핑
* VA로 PA를 찾는게 필요한데, PA-> VA 맵핑이 되어 있으면...

대부분의 invalid한 page table은 굳이 저장하지 않기 때문에 무엇이 invalid한지 알아봐야 함. -> h/w적으로 순서대로 뒤져서 원하는 page table entry를 찾는 방법 : Multi-level Page Table

- 물리적인 memory 관리 하기 위해서
  - Page table 을 연속된 16k로 저장하기 위해 연속된 4K 조각(PFN, Page Frame Number)을 찾는게 어려워질 가능성이 있다.


항상 page table은 physical memory를 점유하고 있음. 
그러면 안 쓰는 page table은 disk에서 빼면 안될까? 즉 page table을 paging하는 것(=page table이 다른 page table을 가르키는 것 조차 virtual address로 만드는 것)

## TLB

* 시간적인 overhead와 그에 대한 해결 방법을 알아보자
  * page table을 줄이면 시간적인 overhead가 늘어남

### Problem

* Address translation is too slow
  * TLB (컴퓨터구조 시간에 나왔었음. Translation Look-aside Buffer)

* TLB exploits locality
  * Code : Sequential Access, Loop을 다루기 때문에 spatial locality가 높음.
  * Data : Hash table 같은 것 때문에 Spatial locality가 낮음.

Software Managed TLB vs Hardware Managed TLB
- 요즘은 H/w managed tlb가 대부분
- MIPS 같은 CPU는 (복잡한건 S/W, 간단한건 H/W가 다룬다는 철학으로) S/W managed tlb

page table format 을 CPU가 담당

### TLB on Context Switches

* Flush TLB on each context switch
* Process 가 Switching 될 때 완전히 비우고(=flush)..

자주 사용하는 pid 를 asid에 대응시키고 asid 를 다 사용하면 해당 asid를 가지는 tlb entry를 flush 시킨다.

### TLB on Multi-core
(참고: MMU마다 Tlb가 하나씩 있음.)

* TLB coherence

TLB는 CPU마다 하나씩 있음.
Process의 context가 필요하기 때문에 address space id 가 같은 프로세스라는 보장이 없기 때문에 일반 캐시와 달리 coherence protocol을 만들어놓지 않음.

* TLB shootdown
  * 어떤 코어의 entry에서 수정하면 다른 코어에 있을지 없을지 모르기 때문에, IPI(Inter-Processor Interrupt)를 이용해서 다른 코어에게 긴급한 메세지를 알려준다.
  * 메세지를 받은 애들은 해당한 엔트리를 invalid시킨다든지 등의 조치를 취해 TLB가 가장 최근의 업데이트된 내용을 보이게 함.

### TLB Performance

* TLB miss가 많아지면 page table을 뒤져야 하니까 느려짐. 
* 가끔 shootdown을 해줘야 해서 TLB performance가 떨어짐. 
* 특히 memory를 많이 쓰는 application의 경우 TLB 오버헤드가 늘어남.
* 요즘 많이 사용하는 건 모든 데이터를 메모리에 다 올려놓으면 빠르게 처리할 수 있게 됨 -> TLB performance의 중요성이 올라감.

* Increase TLB reacher / TLB coverage

* 늘리는 방법
  * entry를 많이 만들어서 늘릴 수 있음
  * superpage를 사용
    * 단점 : memory fragmentation이 심해진다. (4kb, 2mb를 섞어 쓰기 때문에..)