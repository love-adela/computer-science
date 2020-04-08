W1
---

## 1. Explain each of the instruments below

### 1.1 DC Power Supply (직류 전원 공급 장치)

1.1.1 DC : 시간에 따라 극성이 변하지 않는 전류

- 역할 : 부하에 일정한 DC 전압을 공급한다.
- 특징 : 설계에 따라 DC 전원 공급기는 DC 전원 또는 전원 주전원과 같은 AC 전원으로부터도 전원을 공급받을 수 있다.
- 분류
  
      1. AC-to-DC supply
      - DC 전원 공급기는 AC 주전원 전기를 에니저원으로 사용한다. 
      - 입력 전압을 더 높거나 더 낮은 AC 전압으로 변환하기 위해 변압기를 사용한다.
      - 정류기(Rectifier)는 변압기 출력 전압을 다양한 DC 전압으로 변환하기 위해 사용된다. 전자 필터를 통과하여 조절되지 않은 DC 전압으로 변환된다.
  
      2. Switched-mode-power supply (SMPS)
      작동원리
      - AC 주전원 입력을 직접 수리하고 필터링하여 DC 전압을 얻는다. 
      - 전자 개폐 회로가 고주파에서 DC전압을 키고 끈다. 
      - 고주파 변압기 또는 인덕터를 통과하는 AC 전류를 생성한다. 개폐는 매우 높은 주파수(10kHz-1MHz)에서 발생하므로 선형 전원 공급장치보다는 작고 가벼우며 저렴한 변압기와 필터를 사용한다.
      - 고주파 AC를 정류하고 필터링하여 DC 출력 전압을 생성한다.
- 특징
  - 절연된 고주파 변압기를 사용하면 출력이 전원에서 전기적으로 격리되기 때문에 안전에 필수적이다.
  - 일반적으로 제한되고 출력 전압을 일정하게 유지하기 위해 전원을 공급시키는 부하가 그리는 전류를 따라 피드백 컨트롤러를 사용한다.
  - 출력 요구사항이 증가하면 스위칭 듀티 사이클도 함께 증가한다. 출력 전압이 아닌 스위치 전류가 직접 제어하기 때문이다.

1.1.2. Linear regulator (선형 전압 조절기)
- 기능 
  - 다양한 DC 전압을 일정하고 종종 특정하며 낮은 DC 전압으로 변환하는 것

- 특징
  - 전원 공급과 부하를 과전류(과잉, 잠재적으로 파괴적인 전류)로부터 보호하기 위한 전류 제한 기능을 제공하는 경우가 많다.

### 1.2 Multimeter(=volt-ohm-milliammeter, 멀티미터)

- 요약 : 전압/전류/저항 등 많은 전기량을 측정하는 다목적 계기
- 기능
  - 전압 측정 : 프로브를 통해 외부에서 들어온 전압은 멀티미터 내부의 저항(고 임피던스)을 거쳐 전압을 내릴 때 흐르는 전류로부터 측정하거나, 내부저항에 걸린 전압을 ADC(Analog-to-Digital converter)을 통해 수치화한다.
  - 전류 측정 : 대상과 직렬로 측정기를 연결한다. 특정 노드에 연결된 전선에 전류를 측정하려면 해당 전선을 절단하고 두 프로브를 삽입해야 전류가 측정된다.
  - 저항 측정 : 멀티미터 내부의 전지를 이용하여 외부의 프로브에 연결된 저항에 전압을 인가해 전류를 측정한다.
- 특징 : 휴대장치로 측정 대상의 기본적인 결점을 찾기 위한 벤치 기구로 사용. 예를 들어, 전지, 모터 컨트롤, 전기 제품, 파워서플라이, 전신 체계와 같은 산업과 가구용 장치의 전기문제를 점검할 때 사용된다.
- 분류
  - 아날로그 방식: 무빙코일에 흐르는 전류에 따른 자장의 크기로 회전력을 얻는다.
  - 디지털 방식: 입력도딘 전압을 ADC를 통해 디지털화 한 후, LCD 숫자창에 표시한다. 아날로그에 비해 회로가 복잡하다.
  
### 1.3 Function Generator (함수 발생기)

- 요약 : 전자 시험 장비 혹은 소프트웨어의 한 종류로, 전자 신호인 파형을 발생시키기 위한 장치
- 기능 : 사인(sine)파, 방형(square)파, 삼각(triangular)파, 톱니파(sawtooth)파 같은 주기적 신호를 만든다. 각 신호는 AC 신호이므로 여기에 DC 성분을 추가하기도 한다.
- 원리 : 함수가 발생함에 다라 파형 종류, 전압, 주파수, 오프셋, 듀티비가 변경되기 때문에 요소를 적절히 설정함으로써 원하는 파형을 얻을 수 있다.

### 1.4 Oscilloscope(오실로스코프)

- 요약 : 오실로스코프는 특정 시간 간격(대역)의 전압 변화를 볼 수 있는 장치
- 기능 : 주기적으로 반복되는 전자 신호를 표시하는데 사용한다. 이 기기를 활용하면 시간에 따라 변화하는 신호를 주기적이고 반복적인 하나의 전압 형태로 파악할 수 있다.
- 활용 : 전압 측정, 시간 간격 측정, 주파수 측정, 위상차 측정
- 원리
  - 신호처리 방식: 프로브로 입력된 전자신호는 화면 표시를 위해 처리해야 한다.
    - 아날로그 방식: 입력부터 신호 표시 전과정을 아날로그 회로가 제어한다.
    - 디지털 방식: 디지털화하면서 신호의 미세한 부분에서 신호모양이 변형된다.

## 2. Explain how to read registor color coding

저항의 본체에는 3~6가지 색의 밴드가 칠해져 있다. 보통은 4개의 밴드를 사용한다.

### 2.1 밴드의 특징

1. 왼쪽 앞 부분에 있는 밴드는 항상 0부터 9까지를 표시하는 저항 값을 나타탠다.
2. 저항의 값을 표시하는 밴드 뒷부분에는 multiplier band가 있다.
      - 십진법을 오른쪽이나 왼쪽으로 움직이는걸 나타낸다. 
      - 각각 1옴, 10옴, 100옴, 1K옴, 10K옴, 100K옴, 1M옴 등으로 표시할 수 있다.
3. 마지막 밴드는 허용오차 및 온도 계수를 나타낸다.

[예시]
* 3~4개 밴드 저항인 경우
   - 2개 밴드는 저항 값의 처음 두 자리를 옴 단위로 표시한다.
   - 세번째 밴드가 multiplier를 뜻한다. 이 multiplier는 10진수 단위로 값을 변화시킨다.
   - 4번째 밴드는 저항력을 나타낸다. 이 밴드가 없는 상태에서 3-밴드 저항기를 볼 경우 기본 허용오차는 ±20%다.

* 5~6개 밴드 저항인 경우
   - 세번째 significant digit 을 나타내는 추가 색상 밴드가 있는 저항기는 정밀도가 높다.
   - 네번째 밴드는 multiplier을, 다섯번째 밴드는 저항력을 나타낸다. 
   - 6-밴드 저항기는 기본적으로 신뢰도를 나타내는 추가 링 또는 온도 계수(ppm/K) 사양을 가진 5-밴드 형식이다. 예를 들어 가장 일반적인 6번째 밴드 색상인 갈색은 10°C의 온도 변화마다 저항값이 0.1%씩 변화한다.

출처: https://www.arrow.com/en/research-and-events/articles/resistor-color-code

Week4, Wed
---

## 4.1 Multiplexer, Demultiplexer

* 4-to-1 MUX
  * input: 2 ** n개 → selecting one input
  * output: 1개
  * controll: 2개

* 1-to-4 DEMUX
  * input: 1개
  * output: 2 ** n 개 → selecting one output
  * controll: 2개

## 4.2 Encoder, Decoder

* 4-to-2 encoder
  * input: 2 ** n개
  * output: n개
    * 인풋값을 선택하고 그에 대한 binary value로 결과를 내보냄
    * No selection lines
  * ground
    * 1이면 enabling signal
    * 0이면 don't care

* 2-to-4 decoder
  * input: n개
  * output: 2 ** n개
    * 아웃풋값을 선택하고 그에 대한 binary value로 결과를 내보냄.
  * No selection lines

## 4.3 Verliog

### 4.3.1 HDL(Hardware Description Language)

4.3.1.1 HDL 종류

* Abel
  * circa 1983, developed by data-I/O
* ISP
  * circa 1977, research project at CMU
* **Verilog**
  * circa 1985, developed by Gateway (absorbed by Cadence)
* VHDL
  * circa 1987, DoD sponsored standard

4.3.1.2 HDLs 장점

* IEEE standard
* Common
* Flexible - Delay modeling, Matrices, ...
* Describe hardware at varying levels of abstraction

### 4.3.2 Types of programming (description)

4.3.2.1 Structural description

4.3.2.2 Data-flow style description

* Textual replacement of truth table
* Normally focuses.

4.3.2.3 Behavioral Description

* Describe hardware at varying levels of abstraction
* Structural description
  * Textual replacement for schematic
  * Hierarchical composition of modules from primitives(basic logic gates)
* Data-flow style description
  * Textual replacement of truth table
* Behavioral/functional description
  * Describe what module does, not how
  * Synthesis generates circuit for module

### 4.3.3 Verilog Basics

4.3.3.1 Verilog Notation

* Verilog
  * Case sensitive
  * Based on the programming language C

* Comments
  * `// this is a comment`
    * single line
  * `/* this is a comment */`
    * multiple line

* List element separator: `,`
* Statement terminator : `;`

* Binary Values for Constants and Variables
  * 0 : logic 0 or a false condition
  * 1 : logic 1 or a true condition
  * X, x : unknown logic value
  * Z, z : High impedance, floating state (open circuit)
* Constants
  * `n'b[integer]` : 1'b1=1, 8'b1=000000001, 4'b0101=0101, 8'bxxxx=0000xxxx
  * `n'h[integer]` : 8'hA9 = 10101001, 16'hf1 = 0000000011110001

* Scalar vs Vector
  * Scalar
    * 1bit wide, (ex: wire scalar_wire)
  * Vector
    * n bit wide, (ex: wire[3:0] vector_wire)
    * Each bit can be individually selected. (ex: vector_wire[2])

4.3.3.2 Verliog Operators

* Bitwise operators
  * `~` : NOT
  * `&` : AND
  * `|` : OR
  * `^` : XOR

* Example

```
input[3:0] A, B;
output[3:0] C;

assign C = A | ~B;

// if A = 0001, B = 1010
// C = 0001 | ~ (1010) = 0001 | 0101 = 0101
```

* Logical & Relational Operators
  * `!`, `&&`, `||`, `==`, `!=`, `>=`, `<=`, `>`, `<`, etc

* Arithmetic Operators
  * `+`, `-`, etc

* Concatenation & Replication Operators
  * `{identifier_1, identifier_2, ...}`
  * `{n{identifier3}}` : replicate identifier3 in n times

* Example

```
assign A = {REG_IN[6:0], Serial_in} // total of 8 bits
assign B = {8{1'b0}} // equal to 8'b00000000
```

* Ternary Operator(삼항연산자)
`(A?B:C)`

4.3.3.3 Verilog Keywords & constructs

* Input Declaration
  * Scalar
    * Input list of input identifiers
    * Example: input A, B, c_in; // 3*1 bit inputs
  * Vector
    * Input[range] lst of input identifiers;
    * Example: input[15:0] A, B, data; // 3 * 16 bit inputs

* Output Declaration
  * Scalar Example
    * `output c_out, 0V;` // 2 * 1 bit outputs
  * Vector Example
    * `output[7:0] ACC, data_out;` // 2 * 8bit outputs

* Wire Declaration
  * Scalar Example : `wire t1, t2; // 2 * 1bit wires`
  * Vector Example : `wire[7:0] t1, t2; // 2*8bit wires`
  
* keywords are lower case
  * `input`, `assign` etc.

* Module - fundamental building block for Verilog designs
  * Used to construct design hierarchy
  * Cannot be nested
  * One can be used within another module

* Module Declaration
  * Start with `module`, end with `endmodule`

* example

```
module ex1(
  input ex_in1_scalar,
  input ex_in2_scalar,
  output ex_out_scalar,
  input [3:0] ex_in1_vector,
  input [3:0] ex_in2_vector,
  output [3:0] ex_out_vector
  );

  wire ex_wire1;
  wire [3:0] ex_wire2;

  assign ex_wire1 = ex_in1_scalar & ex_in2_scalar;
  assign ex_wire2 = ex_in1_vector & ex_in2_vector;

  assign ex_out_scalar = ~ex_wire1;
  assign ex_out_vector = ~ex_wire2;

endmodule
```

* Primitive Gates
  * `buf`, `not`, `and`, `or`, `nand`, `nor`, `xor`, `xnor`

* Syntax
  * [gate_operator][instance_identifier][(output, input_1, input_2,...)]

* Code

```
module ex2(
  input A,
  input B,
  input C, 
  output Output
  );

  wire tmp;
  and and1(tmp, A, B);
  and and2(Output, tmp, C);

endmodule
```

* Primitive Gates
  * `buf`, `not`, `and`, `or`, `nand`, `nor`, `xor`, `xnor`

* Syntax
  * `[gate_operator][instance_identifier][(output, input_1, input_2, ...)]`

* Code
```
module ex2(
  input A,
  input B,
  input C,
  output Output
  );
  
  wire tmp;
  and and1(tmp1, A, B);
  and and2(Output, tmp, C);

endmodule
```

* Process
  * The body of a process consists of procedural statement to make desired outputs from inputs as like a common programming.
  * Processes run in **parallel**.
  * **initial**
    * executes only once at t =  0
    * syntax
      `initial statement`;
      Example1> initial clock = 0
      Example2> 
        initial begin
            clock = 0;
            en = 1;
            ...
        end
  
      * 