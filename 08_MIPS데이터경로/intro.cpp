/*
CPU가 인스트럭션을 수행하는 대표적인 과정
CPU는 몇 가지 주요 동작으로 나뉘어 클럭 신호에 맞추어 순서대로 진행합니다.
1)인스트럭션을 읽어오는 패치(Fetch)
2)읽어온 인스트럭션 종류에 따라 각 유닛으로 보낼 적절한 제어 신호를 생성하는 디코딩(Decoding)
3)연산결과, ALU의 출력값이 저장되는 실행(Execution)
4)실행 결과값을 최종적으로 타겟 레지스터에 저장하는 라이트-백(Write Back)
이러한 과정은 클럭에 의해 구분 지을 수도 있고 한 클럭 내에 다 몰아 넣을 수도 있습니다.
하지만 파이프라이닝 기법을 사용하기 위해선 대부분 여러 클럭으로 나눕니다.

01 R-타입 인스트럭션의 CPU수행
CPU는 기본적으로 '프로그램 저장방식'을 채택하고 있습니다.
이 방식은 수행하고자 하는 프로그램(인스트럭션의 집합)이 주기억장치(메모리)에 존재하고
CPU가 이를 순차적으로 읽어와 수행하는 방식.
이렇게 인스트럭션을 메모리에서 읽어오는 과정을 패치라고 부릅니다.
패치가 된 인스트럭션들은 연산을 수행함에 있어서 필요한 정보를 제공해야 합니다.
인스트럭션상에 필드별로 나누어져 있으며 필드들은 필요한 모듈로 전달되 다음 단계에서 필요한 값을 도출.
addi 인스트럭션에서는 인스트럭션의 rs필드는 레지스터 파일로 전달되어 레지스터를 선택하게 하고,
16비트의 상수 필드는 ALU 입력에 대비하여 부호를 고려한 32비트로 확장합니다.
이렇게 연산을 위한 준비단계, 즉 레지스터를 선택하고 상수 필드를 확장하는 등의 과정을 디코딩(Decoding)
디코딩 과정까지 거치면 연산에 필요한 모든 레지스터나 상수값이 준비되고, 이 값이 ALU의 입력으로 들어감.
그리고 인스트럭션의 op코드 필드가 ALU의 컨트롤 입력에 인가되어 두 입력에 대해 어떤 연산을 할 지 정함.
이렇게 CPU의 가장 핵심적 역할인 ALU연산을 하게 되는 과정을 바로 실행(Execution).
실행 후에는 이 실행 결과를 반영하는 것입니다.
add이면 ALU의 연산 결과를 다시 타겟 레지스터에 저장해야 하고, Load면 실행단계에서 ALU를 통해 액세스할 
메모리 어드레스를 계산하고 그 계산 결과를 메모리 어드레스로 보내 데이터를 읽거나 쓸 것입니다.
이렇게 최종적으로 결과를 반영하는 과정을 '라이트백'이라고 합니다.
모든 인스트럭션에서 실행이나 라이트백에서 차이는 있을 수 있지만, 패치와 디코딩은 필수적이며
실행 과정에서도 대부분 ALU를 활용합니다.
각 과정은 클럭에 의해서 구분짓는데 매 클럭이 인가될 때마다 각 단계의 결과물은 다음 단계의
입력이 될 수 있도록 저장해야 하고, 이 때 필요한 것이 레지스터입니다.

인스트럭션 패치(Instruction Fetch)
인스트럭션을 수행하기 위해 가장 먼저 해야할 일이 바로 인스트럭션을 메모리에서 읽어오는 일입니다.
곧 메모리 유닛에 어드레스 신호를 주고 해당 어드레스의 값을 읽어온다는 것.
데이터를 읽어오는 경우에는 해당 어드레스가 전적으로 프로그래머의 의지에 의해 결정됩니다.
C에선 구체적으로 메모리 어드레스를 주고 데이터를 엑세스하진 않지만, 변수를 선언하고 해당 변수를 참조하면
결과적으로 컴파일러는 해당 변수가 저장된 메모리의 어드레스를 결정해 그 어드레스를 액세스하는 인스트럭션으로 바뀜.
패치과정에서 메모리 어드레스는 하드웨어, CPU제작자의 의도에 따라 결정됩니다.
CPU는 전원이 들어오면 자동으로 미리 정해진 메모리 어드레스의 값을 읽어와 이를 인스트럭션으로 이해하고 수행.
그리고 하나의 인스트럭션이 끝나면 다음 인스트럭션을 읽고 계속 반복됩니다.
데이터를 읽는 방식의 차이는 일반적인 데이터 액세스가 매 번 읽을 때마다 프로그램에 의해 단절적으로
어드레스를 주고 읽는 반면 인스트럭션은 시작 어드레스부터 순차적으로 읽어가며 수행.
그래서 인스트럭션은 CPU가 마지막에 읽은 인스트럭션의 어드레스를 기억하고 있어야 하며,
다음 인스트럭션을 읽기 위해 이 어드레스 값을 순차적으로 증가시켜야 하는데 PC레지스터.
PC레지스터는 전원이 들어오는 순간 특정 값으로 초기화되고, 자동으로 PC값이 인스트럭션이 저장된
메모리의 어드레스로 들어가 해당 인스트럭션을 읽어옵니다.
그리고 인스트럭션이 읽히는 것과 동시에 자동으로 PC레지스터의 입력값이 다음 인스트럭션을 가리키게 증가.
PC레지스터의 값이 인스트럭션 메모리의 어드레스 값으로 들어가서 해당 어드레스의 인스트럭션이 출력되는데
이 인스트럭션은 이후 디코딩 단계에서 사용될 수 있도록 인스트럭션 레지스터라고 불리는 특별한 레지스터에 저장.
PC의 입력단에는 다음 인스트럭션을 가리킬 수 있도록 한 인스트럭션의 크기인 4만큼 더해진 값이 인가.
PC는 플립플롭으로 이루어진 순차회로이므로 클럭이 인가되는 순간에만 입력값이 출력으로 반영.
반면 Adder는 ALU와 마찬가지로 입력이 바뀌면 바로 출력도 바뀌는 조합회로.
메모리 유닛도 조합회로라고 간주해보자.
모든 이벤트가 발생하는 시작점은 유일한 순차회로인 PC레지스터에서 클럭이 인가되는 순간.
회로가 안정된 상태에 있다면 현재 PC레지스터의 값이 그대로 메모리의 어드레스 값으로 전달되어
해당 어드레스의 인스트럭션이 데이터 라인을 통해 출력된 후 인스트럭션 레지스터의 입력단에 연결.
또한 Adder 역시 입력이 바뀜과 함께 바로 출력이 바뀌는 조합회로이므로 현재 PC레지스터의 출력값에
4를 더한 값이 항상 출력.
이 값은 PC레지스터의 입력에 다시 연결되어 있지만 PC 및 인스트럭션 레지스터는 순차회로이므로 클럭이
인가되기 전까지 입력값이 출력값에 반영되지 않습니다. 댐같은 역할을 한다.
이 상태에서 인스트럭션 레지스터와 PC레지스터에 각각 클럭이 인가되면
인스트럭션 레지스터의 입력단에 이미 인가되어 있던 값이 레지스터에 저장됨과 동시에 출력단에 반영.
동시에 PC레지스터 역시 인가된 입력값이 출력단에 반영.
┌─────────┐
|     4┐  |3-1
|3   ┌>add┘
|    |2               1
└PC──┴>메모리──>인스트럭션레지스터──>
  1         3-2                2-1
1:클럭 인가
2:PC의 변한 출력값이 각 모듈의 입력에도 반영
2-1:디코딩 과정 시작
3:다음 인스트럭션의 값이 PC의 입력에서 대기하고, 다음 클럭에서 다시 1~3과정을 거친다.
3-1:새로운 PC값에 4를 더한 값. 다음 인스트럭션의 주소값이 계산되어 나옴.
3-2:새로운 PC값에 맞춰 다음 인스트럭션이 나오게 된다.

인스트럭션 디코딩(Instruction Decoding)
패치 과정을 거치게 되면 인스트럭션 메모리에서 다음 실행 어드레스의 인스트럭션이 나옵니다.
인스트럭션은 원하는 연산을 위해 필요한 레지스터를 선택하고, ALU의 연산도 결정해야 합니다.
이런 결정은 인스트럭션의 각 필드별로 분해하여 적절한 모듈에 그 값을 인가하는데 인스트럭션 디코딩이라 한다.
인스트럭션 레지스터(IR)에 저장된 인스트럭션이 R-타입이라고 하면 연산의 종류는 op와 funct필드 조합으로 결정.
IR의 비트 32개가 각각의 필드로 나뉘어 레지스터파일(Register File)에 들어가고 여기서 선택된
두 오퍼랜드 값이 출력으로 나와 다음 단계(Execution)을 위해 각각 오퍼랜드1과2 레지스터 입력에 연결.
또한, op와 funct필드의 조합으로 ALU의 컨트롤 입력값이 나옵니다.
디코딩 과정은 사실 IR에 클럭이 인가되자마자 시작합니다.
이미 이전 패치 과정에서 인스트럭션이 읽힌 후 입력단엔 연결된 상태이고,
클럭이 인가되자마자 곧바로 출력단으로 해당 인스트럭션을 보내는 것.
적절히 디코딩한 데이터는 최종적으로는 다음 단계로 들어가는 댐에 해당하는 오퍼랜드 레지스터의 입력단에 
연결된 채로 다음 클럭이 오는 것을 대기.
┌─────────┐
|     4┐  |3
|    ┌>add┘
|    |2         1                               2-1        4            5
└PC──┴>메모리──>IR┬─>레지스터 파일(rs,rt,rd,데이터)┬─>오퍼랜드1레지스터──>실행(Execution)
  1         3-1  |                            3-2└─>오퍼랜드2레지스터──>실행(Execution)
                 └─>ALU컨트롤입력생성(op,funct)──>
1:첫번째 클럭 인가
2:새로운 PC값이 각 모듈의 입력에 반영
2-1:IR의 입력이 출력으로 반영되고 새로운 인스트럭션이 필드별로 레지스터 파일과 컨트롤 입력 생성 모듈에 반영.
3:PC의 입력에 PC+4 값이 인가
3-1:새로운 인스트럭션이 출력되어 IR입력에 인가
3-2:선택된 레지스터 값과 ALU컨트롤 값이 출력됨.
4:두 번째 클럭 인가
5:실행
PC와 IR은 댐역할을 합니다.
마지막에 오퍼랜드 레지스터 역시 디코딩 과정이 끝난 데이터를 다음 사이클 동안 실행단계로 흘려주는 댐 역할.

실행(Execution)
디코딩 과정이 끝나고 나면 두 개의 오퍼랜드 레지스터의 입력단에는 연산의 대상이 되는 두 값이 인가된 상태.
클럭이 인가되기 전까지는 입력이 바뀌어도 출력이 바로 바뀌지 않습니다.
두 번째 클럭이 이 두 오퍼랜드 레지스터에 인가되고 나면 출력단도 입력에 맞춰 변하고, 새로운 값들도
ALU에 직접 연결되어 원하는 연산을 할 수 있다.
ALU연산의 종류를 결정짓는 컨트롤 입력도 디코딩 단에서 넘어와, 이름대로 ALU의 컨트롤 입력부분에 연결.
두 오퍼랜드의 값이 ALU의 입력에 연결되어 있고 컨트롤 입력은 연산의 종류를 결정.
ALU는 조합회로이므로 오퍼랜드 레지스터의 출력이 변하는 즉시 ALU출력단으로 연산의 결과가 반영.
이 연산 결과는 다음 단계(라이트백)를 위해 ALU Output레지스터의 입력에 연결됩니다.
ALU Output레지스터가 댐의 역할.
┌─────────┐
|     4┐  |3
|    ┌>add┘
|    |2         1                               2-1       4         5 
└PC──┴>메모리──>IR┬─>레지스터 파일(rs,rt,rd,데이터)┬─>오퍼랜드1레지스터─>|    6       7
  1         3-1  |                            3-2└─>오퍼랜드2레지스터─>|ALU──>ALU Output레지스터──>라이트백
				 └─>ALU컨트롤입력생성(op,funct)───────────────────────>|
1:첫 번째 클럭 인가
2:새로운 PC값이 각 모듈의 입력에 반영
2-1:IR의 입력이 출력으로 반영되고 새로운 인스트럭션이 필드별로 레지스터 파일과 컨트롤 입력 생성 모듈에 반영.
3:PC의 입력에 PC+4 값이 인가
3-1:새로운 인스트럭션이 출력되어 IR입력에 인가
3-2:선택된 레지스터 값과 ALU컨트롤 값이 출력됨.
4:두 번째 클럭 인가
5:새로운 오퍼랜드 값이 ALU입력에 인가
6:곧이어 연산된 결과가 출력
7:세 번째 클럭 인가

라이트백(Write Back)
연산한 결과를 타겟 레지스터에 저장하는 과정.
우선 앞의 싱행 단계의 결과를 받아들이기 위해 ALU Output레지스터에 세 번째 클럭이 인가되면서 시작.
ALU Output레지스터의 출력이 변하면서 입력값이 반영되고, 레지스터 파일의 데이터 입력 라인으로 연결.
타겟 레지스터는 디코딩 과정에서 rd필드(11~15비트)가 레지스터 파일에 연결되었으므로,
실제 타겟 레지스터에 값을 쓰기 위해 해당 레지스터에 네 번째 클럭을 줍니다.
레지스터 파일의 모든 레지스터도 댐역할을 합니다.
┌─────────┐
|     4┐  |3                                                            8
|    ┌>add┘                                 ┌─────────────────────────────────────────────────┐
|    |2         1               9           |    2-1       4        5                         |
└PC──┴>메모리──>IR┬─>레지스터 파일(rs,rt,rd,데이터)┬─>오퍼랜드1레지스터─>|    6       7           |
  1         3-1  |                            3-2└─>오퍼랜드2레지스터─>|ALU──>ALU Output레지스터─┘
				 └─>ALU컨트롤입력생성(op,funct)───────────────────────>|
1:첫 번째 클럭 인가
2:새로운 PC값이 각 모듈의 입력에 반영
2-1:IR의 입력이 출력으로 반영되고 새로운 인스트럭션이 필드별로 레지스터 파일과 컨트롤 입력 생성 모듈에 반영.
3:PC의 입력에 PC+4 값이 인가
3-1:새로운 인스트럭션이 출력되어 IR입력에 인가
3-2:선택된 레지스터 값과 ALU컨트롤 값이 출력됨.
4:두 번째 클럭 인가
5:새로운 오퍼랜드 값이 ALU입력에 인가
6:곧이어 연산된 결과가 출력
7:세 번째 클럭 인가
8:ALU의 결과 값이 레지스터 파일의 데이터 입력으로 인가됨
9:네 번째 클럭을 인가하여 ALU Output레지스터의 출력을 타겟 레지스터에 저장토록 함.
결국 ALU Output레지스터의 값을 원하는 타겟 레지스터로 옮기는 과정일 뿐.

02 I-타입 인스트럭션의 CPU 수행
연산할 두 개의 오퍼랜드 중 하나는 R-타입처럼 레지스터에서 읽어오는 반면 다른 하나는 자체에 16비트 값.
rs필드가 지정하는 레지스터 값과 인스트럭션의 Constant필드의 값으로 op필드가 지정하는 연산을 합니다.
1)산술 또는 논리 연산
Constant필드를 하나의 오퍼랜드로 취급하여 연산
2)Load/Store 처럼 메모리 관련 연산
3)bne같은 조건부 분기 인스트럭션
Constant필드가 rs레지스터와 함께 메모리의 어드레스를 가리키는 역할.
3가지 모두 ALU가 필요하고 오퍼랜드 중 하나가 인스트럭션 자체에서 온다는 것.
R-타입의 데이터 경로에서 바뀌어야 할 부분은 인스트럭션에서 온 상수값이 될 수 있도록 MUX등을
사용하여 임의로 선택할 수 있어야 합니다.
또한, 인스트럭션의 Constant필드를 그대로 MUX로 연결하지 않고 중간에 16비트를 32비트로 변환하는 회로를 구성.
왜냐하면, 16비트와 32비트로 나타낸 수는 음수 표현에서 차이가 나기 때문(2의 보수)
부호를 고려하여 비트를 확장하는 것을 부호확장.
IR 21~25|──>오퍼랜드1레지스터─────────────>|ALU──>ALU Output레지스터
   16~20|──>오퍼랜드2레지스터────>|1 MUX──>|
    0~15|──>32비트 확장─────────>|2

Load/Store은 최종 메모리 어드레스를 계산하기 위해 rs필드가 가리키는 레지스터값과 constant필드의 두 값을 더함.
그리고 이 때 실행 단계에서 ALU를 사용합니다.
차이점은 라이트백단계.
Store인 경우 ALU Output레지스터의 값을 레지스터가 아닌 메모리에 저장합니다.
이 때 저장할 데이터는 ALU Output레지스터의 값이 아니라 rt필드가 가리키는 레지스터에 저장한 값.
그리고 ALU Output레지스터는 실행단계에서 Reg[rs]+Constant값으로 저장할 메모리의 어드레스로 활용.
                                           4         5       6        7                   6-1
IR 21~25|──>|rs read 레지스터 파일|──>오퍼랜드1레지스터──>|add|──>ALU Output레지스터──>|어드레스 메모리|
   16~20|──>|rt read             |──>오퍼랜드2레지스터──────────────────────────────>|데이터        |
    0~15|──────────────────32비트 부호 확장─────────────>|   |           Reg[RT]
4:두 번째 클럭 인가
5:새로운 오퍼랜드 값이 ALU입력에 인가됨
6:곧이어 연산된 결과가 출력
6-1:네 번째 클럭 동안 메모리에 데이터 기록 라이트 시그널
7:세 번째 클럭 인가

한편 Load인 경우 메모리에서 데이터를 읽어온 후 이를 다시 레지스터에 저장해야 합니다.
실행 단계에서 계산된 어드레스 값으로 4번째 단계에서 메모리에 어드레스를 인가하지만
이 때 데이터를 인가하여 쓰도록 하는 것이 아니라 읽도록 신호를 주는 것.
메모리에서 나온 데이터는 메모리 데이터 레지스터(MDR)에 저장되고 5번째 클럭에서 최종적으로
MDR값이 rt필드로 지정된 레지스터에 저장됩니다.
					11					   4         5       6        7                   7-1
IR 21~25|──>|rs read 레지스터 파일|──>오퍼랜드1레지스터──>|add|──>ALU Output레지스터──>|어드레스 메모리|
   16~20|──>|rt read             |                      |   |                       |데이터        |─┐
         ┌─>|라이트데이터         |                      |   |                                        |
    0~15|──────────────────32비트 부호 확장─────────────>|   |                                        |
	     └─────────────────────────────────────MDR───────────────────────────────────────────────────┘                                  
	                      10                    9                      8
4:두 번째 클럭 인가
5:새로운 오퍼랜드 값이 ALU입력에 인가됨
6:곧이어 연산된 결과가 출력
7:세 번째 클럭 인가
7-1:라이트 시그널
8:메모리에서 데이터가 나오기 시작함
9:네 번째 출력
10:MDR데이터가 나오기 시작
11:다섯 번째 클럭. MDR데이터를 레지스터에 라이트백

조건부 분기 인스트럭션은 rs,rt필드의 두 레지스터 값을 비교하여 그 여부에 따라 지정된 어드레스로 분기.
분기 어드레스를 결정하기 위해 constant필드를 사용.
constant필드는 PC레지스터의 값에서 떨어진 정도를 나타내는 offset값.
MIPS의 인스트럭션은 항상 4바이트므로 constant필드가 나타내는 어드레스 단위도 4바이트 단위로 나태내어
실제로는 [다음 인스트럭션 어드레스] = PC + (32비트 부호확장[Constant] << 2)
두 개의 레지스터 값을 비교해 결과에 따라 분기 여부를 결정해야 하는데 비교가 실행단계에서 이루어집니다.
이 구조를 활용하려면 비교할 두 레지스터끼리 뺄셈하여 그 결과가 0인지 살펴보는 것.
이를 위해 ALU에 간단한 회로를 첨부하여 결과가 0인지를 나타내는 1비트 출력을 하나 만듭니다. Zero Output.
Zero Output을 통해 실행 단계에서 분기 여부를 결정합니다.
즉, 분기 어드레스만 미리 결정나 있으면 분기 인스트럭션은 실행단계에서 완료될 수 있다는 것.
실제로도 분기 어드레스 계산을 실행 단계 이전에 완료하도록 설계했다.
지금까지라면 패치나 디코딩단계에서 ALU는 유휴 상태인데 미리 분기 어드레스를 계산하도록 설계했습니다.
디코딩 단계에서 계산하게 했는데 별도의 Adder를 둘 것이 아니라 이미 있는 ALU를 패치 단계에서 활용해
다음 어드레스를 계산하면 비용을 절감할 수 있습니다.
따라서 실제로는 별도 Adder없이 두 개의 ALU입력단에 MUX를 활용해 각각 PC와 상수 4입력을 추가하고,
이 둘을 패치 단계에서 더해 다음 인스트럭션의 어드레스 값으로 활용하는 것.
하지만 계산을 위한 소스가 패치 단계에선 아직 없습니다.
[다음 인스트럭션 어드레스] = PC + (32비트 부호확장[Constant] << 2)
분기 어드레스를 계산하려면 인스트럭션의 constant필드를 읽어와 좌측으로 두번 쉬프트하여 PC값에 더해야 합니다.
PC는 괜찮지만 constant부분은 인스트럭션의 일부분이므로 패치되기 전까지는 알 수 없습니다.
constant값을 알 수 있는 최초 시점이 바로 디코딩 단계입니다.
계산된 어드레스는 디코딩 단계가 끝나면 ALU Output레지스터에 저장되고 실행 단계에서
두 레지스터의 값을 비교해 그 결과에 따라 이미 계산되어 있는 ALU Output 레지스터 값을
PC레지스터로 사용해 분기가 일어납니다.

03 J-타입 인스트럭션의 CPU 수행
기본적으로 무조건 분기를 합니다.
MIPS는 인스트럭션을 패치하고 디코딩하여 이 인스트럭션이 j인스트럭션으로 판단되는 시점에서 바로 PC값을
타겟 어드레스로 업데이트 합니다.
J-타입은 PC값과의 산술적 합이 아닌 단순히 비트 조합으로 최종 타겟 어드레스를 생성하므로 미리
어드레스를 계산해 둘 필요가 없습니다.
즉, 최종 분기 어드레스는 PC레지스터의 최상위 4비트와 어드레스 비트 26비트를 그대로 조합하여 생성하므로
Adder 같은 장치 없이 그대로 각 비트에서 선만 끌어오면 되는 것.
PC의 최상위 4비트와 어드레스 필드 26비트, 그리고 00값 2비트를 제일 하위에 넣어 최종적으로
32비트 메모리 어드레스를 생성합니다.
디코딩이 끝나고 J-타입을 알아내면 필요한 비트를 끌어와 PC레지스터의 입력값으로 주면 됩니다.

정리해보면
1)패치
IR = Mem[PC]
PC = PC + 4
IR에 현재 PC가 가리키는 메모리상의 인스트럭션 로드와 함께 다음 인스트럭션을 가리키도록 PC값을 4증가
2)디코딩
오퍼랜드 Reg1 = Reg[RS]
오퍼랜드 Reg2 = Reg[RT]
ALU Output Reg = PC + (32비트부호확장[constant] << 2)
두 개의 오퍼랜드 레지스터에 각각 인스트럭션의 RS,RT필드가 가리키는 레지스터 값을 저장한다.
또한 조건부 분기 인스트럭션의 타겟 어드레스를 미리 계산해둔다.
3)실행
<R-타입 인스트럭션>
ALU Output Reg = 오퍼랜드 Reg1 ⊙ 오퍼랜드 Reg2
<Load/Store>
ALU Output Reg = 오퍼랜드 Reg1 + 32비트부호확장[constant]
<조건부 분기>
if (Zero Output) then PC = ALU Output Reg
<J-타입 인스트럭션>
PC = PC[31-28]||IR[25-0]||00
R-타입인 경우 두 오퍼랜드로 ALU연산을 하고, 메모리 엑세스 인스트럭션은 타겟 어드레스를 계산한다.
조건부 분기 인스트럭션은 두 비교값에 따라 디코딩 단계에서 미리 계산된 타겟 어드레스로 PC를 업데이트하고,
무조건 분기문은 PC와 인스트럭션 레지스터의 값을 조합하여 최종 타겟 어드레스를 만들어 PC를 업데이트한다.
모든 분기 인스트럭션은 여기서 동작이 끝난다.
4)라이트백
<R-타입 인스트럭션>
Reg[rd] = ALU Output Reg
<Load>
MDR = Mem[ALU Output Reg]
<Store>
Mem[ALU Output Reg] = 오퍼랜드 Reg 2
R-타입 인스트럭션은 최종적으로 계산될 결과를 타겟 레지스터에 저장한다.
Load나 Store인스트럭션은 메모리에 타겟 어드레스를 주고 각각에 맞는 Read/Write신호를 준다.
Store인 경우는 데이터도 함께 준다.
5)Load인스트럭션 Completion
<Load>
Reg[rt] = MDR
Load는 이 단계에서 메모리에서 읽은 데이터를 타겟 레지스터에 저장하는 동작.

유휴 하드웨어의 활용
결론은 MIPS는 인스트럭션 종류에 상관없이 항상 디코딩 단계에서 PC + (32비트 부호확장[Constant] << 2)를
이용해서 ALU Output 레지스터에 저장합니다.
만일 전혀다른 인스트럭션이라면 그 인스트럭션 용도에 맞게 실행 단계에서 ALU를 사용하고 
그 결과는 다시 ALU Output 레지스터에 저장해 미리 계산해두었던 값을 덮어 씌어버리는 것.
그리고 조건부 분기 인스트럭션이라면 ALU Output레지스터에 있는 값으로 실행단계에 PC를 업데이트하면 됨.
추가적인 하드웨어는 전혀 없이 복잡성만 조금 높아지는 것으로 미리 타겟 어드레스를 계산하여 속도를 높이는
방식의 행동을 'Optimistic Prediction'이라 하며 다음 인스트럭션은 필시 조건부 분기문이라고 예상하고 준비.
RISC방식의 모든 인스트럭션이 같은 형태로 구성되어 있고 일정한 단계를 거쳐 수행되기 때문에 가능.
또한, 컴파일러에서도 자주 사용됩니다.

*/