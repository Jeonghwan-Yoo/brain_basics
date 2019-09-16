/*
MIPS란 무엇일까?
컴퓨터의 성능을 나타내는 지표인 Million Instruction Per Second의 약자.
하지만 여기서는 여러 전자 제품에서 활용되는 CPU의 이름.
전형적인 RISC스타일의 CPU로 비교적 인스트럭션 셋이 간단하고 깔끔하게 구성되어있다.

R-타입, I-타입, J-타입 인스트럭션 같이 인스트럭션을 몇 가지 종류로 나누는데,
왜 이런 식으로 인스트럭션을 구분 짓는 것일까요?
RISC특성상 가능한 모든 인스트럭션을 CPU의 처리 단위인 1워드씩 동일한 크기로 만들다 보니.
각 인스트럭션마다 필요한 필드의 종류나 크기가 다른데 이를 주어진 크기 안에 맞추다보니
인스트럭션 종류를 구분 가능하게 만들어야 했던 것.
구분없이 같은 크기의 필드를 지니게 된다면 무척이나 비효율적인 구성이 될 것.

가장 흔하게 접할 수 있고 또 디버깅하기도 쉬운 CPU는 Intel의 펜티엄 프로세서입니다.
하지만 RISC방식을 일부만 도입해 CISC의 잔재가 많이 남아있습니다.
그래서 수많은 복합 기술과 복잡한 인스트럭션 셋을 보유하고 있기 때문에 어렵습니다.
MIPS는 전형적인 RISC방식으로 간결한 인스트럭션셋을 이뤄 데이터경로까지 쉽게 공부할 수 있습니다.

01 MIPS의 레지스터
MIPS는 32개의 범용 32비트 레지스터를 가지는 전형적인 RISC방식 CPU.
모든 인스트럭션이 같은 길이를 가지며, 기준이 되는 것이 CPU의 처리단위(ALU)로 여기서는 32비트.
처리단위를 일반적으로 1워드라고 부르고 MIPS에서는 1워드가 32비트입니다.
32개의 레지스터는 0~31까지의 값으로 인스트럭션상에 맵핑되며, 32개의 레지스터들은
레지스터 파일이라고 부르는 그룹을 형성하며 일반적으로 어드레스 값에 의해 선택합니다.
레지스터를 지정하기 위해서는 5비트 크기의 어드레스 값이 필요합니다.(2^5=32)
하지만 일반적으로 CPU의 어셈블러에서 각 레지스터는 고유의 이름을 보유하는 것이 일반적.
메모리가 단순히 어드레스만으로 표현하는 것에 반해 레스터는 개별적으로 용도가 나뉘어져 있고,
CPU연산에 아주 밀접하게 사용되는데다가 그 숫자가 적어, 구분이 쉽도록 이름을 붙이는 것.
MIPS에서는 32개의 레지스터가 모두 두 개씩 이름을 소유하고 있는데
첫 번째는 단순히 레지스터 파일의 어드레스인 0~31을 그대로 따와서 상수와 구분하기위해 
앞에 $을 붙힘. $0, $31...
두 번째는 레지스터를 그 활용도에 맞추어 몇 가지 그룹으로 나누어 그룹 내에서 다시 
첫 번째 이름과 유사하게 인덱싱하는 방법입니다.
MIPS에서는 효율적인 함수 호출을 지원하기 위해 레지스터를 Saved레지스터, Temporary레지스터,
Argument레지스터 등으로 나누어 각 그룹별로 이름을 부여합니다.
예를 들어 Saved레지스터 그룹이면 $s0~$s7이런 식으로.
이렇게 이름을 별도로 나누는 것은 어셈블리 코드를 작성하는 사람의 편의를 위한 것으로
단순히 인덱스의 불과한 숫자보다는 사용 용도에 맞추어 별명을 하나 더 준 것.
즉, 어셈블리 코드에서 레지스터를 지정할 때 $09로 하든 $t1로 하든 같은 인스트럭션 값.

한편, MIPS에서 한 레지스터를 지정하기 위해서는 5비트가 필요하며 인스트럭션의 각 오퍼랜드 중 
레지스터를 지정하는 5비트 필드가 디코딩이라는 과정을 거쳐 레지스터 파일에 입력으로 들어가 
해당 레지스터를 액세스하게 해줍니다.
MIPS뿐 아니라 모든 CPU는 기본적으로 Program Counter(PC)라는 레지스터를 가지고 있습니다.
메모리상에 현재 수행할 인스트럭션의 주소를 저장하는 레지스터가 있어야하고, 이 레지스터가 PC레지스터.
PC레지스터는 32개의 레지스터와는 별도로 존재합니다.
PC레지스터는 인스트럭션을 수행하는데 아주 중요한 기준이어서 직접 바꿀 수 없고, 인스트럭션이
수행될 때마다 자동으로 그 값이 증가하여 다음 인스트럭션의 주소를 가리키도록 설계합니다.
PC레지스터는 메모리상에서 다음 수행할 인스트럭션이 있는 곳을 가리키고 있어야하므로 
분기문이 발생하면 PC값이 분기 후 수행할 위치로 바뀌어야 합니다.
이를 위해 Jump라는 인스트럭션이 존재하고, MIPS에서도 jr이나 jal같은 점프 명령어가 있습니다.
이 인스트럭션은 다음 수행위치를 임의로 바꿀 수 있게 해주지만 실제로 하는 일은 단순히
PC레지스터에 점프하고자 하는 주소를 저장하는 것에 불과합니다.
그러면 CPU는 그 메커니즘에 의해 자동으로 PC가 가리키는 주소의 인스트럭션을 읽어와
수행하고 나서 다시 다음 인스트럭션을 가리키도록 PC값을 증가합니다.

MIPS의 모든 인스트럭션은 32비트 길이를 지니고 있어 이 인스트럭션의 길이만큼 PC값을 증가시킴.
또한 메모리의 엑세스 단위를 고려해야 합니다.
같은 메모리라 하더라도 메모리의 최소 액세스 단위에 따라 이를 액세스하는 주소의 단위가 달라지게 되므로
한 인스트럭션을 수행 후 다음 인스트럭션을 가리키기 위해 증가해야 하는 PC 레지스터의 값도 달라집니다.
그런데 대부분 CPU는 바이트(8비트) 단위의 액세스를 합니다.
32비트 CPU인 경우 인스트럭션 길이 역시 32비트이므로 32/8=4만큼 증가시켜야 합니다.

PC레지스터를 통한 인스트럭션 패치 과정
매 인스트럭션이 PC가 가리키는 메모리 주소에서 패치되고 자동적으로 PC레지스터가 
다음 인스트럭션을 가리킬 수 있도록 증가하는 모습.
 ┌──────┐
PC──┬──ADD
    |  4┘
	|
메모리 유닛───인스트럭션

MIPS에서는 FLAG레지스터 등 몇 가지 레지스터가 더 있습니다.

02 레지스터의 활용
MIPS에서는 크게 3가지 타입의 인스트럭션이 있습니다.
R-타입 인스트럭션 중 대표적인 것은 ADD나 SUB 같은 산술연산이며 두 오퍼랜드를 모두 레지스터로 지정.
그리고 그 연산의 결과는 RISC 방식의 특성상 특정 AC레지스터 없이 임의의 레지스터를 지정하여 저장할 수 있다.
add $r12, $r10, $r11 #$r12 = $r10 + $r11
sub $r16, $r17, $r18 #$r16 = $r17 + $r18
타겟 레지스터가 가장 앞에 지정되었고, 연산을 할 두 오퍼랜드 역시 레지스터 형태.
C컴파이러로 다음과 같은 수식을 작성했다고 하자.
A = (B - C) + (D - E)
우선 순위가 있는 연산의 경우 따로따로 우선 계산하여 그 결과를 임시로 저장해두고
두 임시 결과를 다시 합하여 최종 결과를 얻어야 합니다.
sub $r8,$r17,$r18 #$r8(temp1) = $r17(B) - $r18(C)
sub $r9,$r19,$r20 #$r9(temp2) = $r19(D) - $r20(E)
add $r16,$r8,$r9  #$r16(A) = $r8(temp1) + $r9(temp2)
계산의 중간 결과로 임시로 사용되는 변수들은 Temporary 레지스터 그룹에 속하는 $tx레지스터로 맵핑.
실제 C구문상에서 변수로 맵핑되는 부분은 모두 Saved레지스터 그룹의 $sx레지스터에 맵핑.
타당한 이유가 있어서 컴파일러가 이렇게 맵핑한 것.
이런 레지스터의 구분은 함수 호출을 효율적으로 하기 위한 방법으로 반드시 이를 따라야 하는 제약은 없습니다.
직접 어셈블리 코드를 작성할 경우 일부 레지스터를 제외하고 상관없습니다.
$0레지스터 같은경우는 $zero라는 이름으로 불리는데 읽으면 항상 0값이 들어있기 때문.
일단 Temporary레지스터와 Saved레지스터 위주로 사용하되 Saved레지스터는 실제 변수에,
Temporary레지스터는 계산의 중간 결과를 저장하기 위한 임시 변수로 사용.

03 R-타입 인스트럭션
R-타입 인스트럭션에서는 오퍼랜드를 위한 두 개의 소스 레지스터와 한 개의 타겟 레지스터, 총 3개의 레지스터.
또한 인스트럭션의 연산 종류를 나타내는 필드 OP코드 부분이 있어야 합니다.
각 레지스터 필드마다 5비트씩을 사용해야 합니다.
OP코드는 MIPS가 지원하는 총 인스트럭션 개수에 따라 달라집니다.
그런데 MIPS에서는 OP코드를 한 필드에 나타내지 않고, 두가지 필드에 나누어 사용합니다.
op(6) rs(5) rt(5) rd(5) shamt(5) fuct(6) = 32
op:OP코드 부분. func필드와 함께 인스트럭션의 종류를 나타낸다.
rs:두 개의 오퍼랜드 중 첫 번째 오퍼랜드 레지스터
rt:두 개의 오퍼랜드 중 두 번째 오퍼랜드 레지스터
rd:연산 결과를 저장할 타겟 레지스터
shamt:Shift인스트럭션에서 shift양을 나타내는 필드. 다른 인스트럭션에서는 무의하므로 항상 zero값.
funct:op필드와 함께 인스트럭션의 종류를 선택하는 필드. op필드의 연장필드.
add $r16,$r8,$r9 #$r16 = $r8 + $r9
$r8과 $r9의 인덱스 값이 각각 rs,rt 필드에 저장됩니다.
그리고 연산 결과를 저장하는 $r16레지스터는 rd필드에 기록됩니다.
MIPS에서의 R-타입 인스트럭션은 op필드뿐 아니라 funct필드까지 합쳐야 비로소 정확한 인스트럭션종류를 파악.
R-타입을 제외한 나머지 인스트럭션들은 모두 op필드만으로 구분되는데,
R-타입 인스트럭션의 경우에는 op필드 값이 0으로 채워져 있고 funct필드를 확인해야 파악할 수 있다.
MIPS는 모든 인스트럭션이 동일한 길이로 나타내고자 하다 보니 모자란 것도 있고 남는 것도 있습니다.
이런 부분을 극복하고자 인스트럭션 종류를 크게 3가지 정도로 나눠 각 인스트럭션마다 필드 구성을 다르게했다.
R-타입인스트럭션은 비교적 여유가 있지만 I-타입이나 J-타입은 모자라고 R-타입은 인스트럭션개수가 많기 때문.
op필드를 가능한 짧게 만들어 R-타입 인스트럭션을 하나의 인스트럭션으로 취급하여 다른 인스트럭션과
구분하게 한 뒤, R-타입 인스트럭션인 경우에는 여유 있는 인스트럭션 길이를 감안해 다시 funct라는
필드를 구성하여, 구체적인 종류는 funct필드를 보고 판단하게 한 것.
이렇게 R-타입 이외의 인스트럭션은 funct필드를 없애고 다른용도로 활용하여 효율적인 사용도 가능.
op(0) rs(8) rt(9) rd(126) shamt(0) funct(32)
00000 01000 01001 10000 00000 100000
op필드는 R-타입 인스트럭션을 하나의 인스트럭션처럼 취급하여 모든 R-타입 인스트럽션은 같은 op필드이며 0.
정확한 구분은 funct필드를 보고 하며, add는 32라는 값을 가집니다. (다른 타입은 op필드만으로 구분)
shamt필드는 shift인스트럭션이 아닌 이상 항상 0입니다.
레지스터 필드에는 인덱스값이 저장됩니다.

04 I-타입 인스트럭션
오퍼랜드 중 하나로 레지스터 대신 상수값을 직접 인스트럭션에 지정하는 방식.
rt필드를 없대고 대신 직접 상수값이 들어가는 것.
addi $r16,$r8,32 #$r16 = $r8 + 32
$r8레지스터에 저장된 값과 32라는 상수를 더하여 $r16레지스터에 저장하라는 뜻.
32라는 상수는 MIPS에서 처리 단위인 1워드, 32비트가 좋겠지만 전체가 32비트여야 하므로
최소한의 필드만 남겨놓고 나머지만 상수 필드로 돌립니다.
op(6) rs(5) rt(5) Constant(16) = 32
op:OP코드 부분. 모든 I-타입 인스트럭션은 op필드만으로 구분된다.
rs:두 개의 오퍼랜드 중 첫 번째 오퍼랜드 레지스터
rt:연산 결과를 저장할 타겟 레지스터
constant:두 개의 오퍼랜드 중 하나가 될 상수값
rd나 shamt, funct필드가 모두 사라지고 대신 Constant가 대신.
16비트를 확보하고 2의보수 방식을 채택하기 때문에 -32768~32767의 범위.
메모리에서 직접 상수값을 읽어와서 레지스터에 저장하고 레지스터간의 연산으로 같은 결과를 얻을 수 있긴하다.
하지만 그러려면 메모리를 액세스해야 하는데 메모리 액세스는 무척 느리다.
연산과정에서 다시 메모리를 액세스를 해야하기 때문에 R-타입 인스트럭션보다 훨씬 긴시간이 필요.
I-타입 인스트럭션이 꼭 필요한 이유는 메모리에서 데이터를 가져오는 Load/Store연산 등.
데이터를 메모리에서 읽거나 저장하기 위해서는 메모리 어드레스를 지정해야 합니다.
이 어드레스는 상수형태로 됩니다.
연속적인 주소에서 읽어오는 경우는 레지스터를 통해 어드레스를 결정할 수 있지만
최초 어드레스는 상수에 의해 결정될 수 밖에 없습니다.
따라서 Load/Store인스트럭션을 위해 I-타입 인스트럭션이 존재해야 합니다.
16비트로는 최대 메모리가 64킬로바이트밖에 되질 않습니다.
이를 해결하기 위해선 레지스터 활용.
I-타입 인스트럭션에는 한 개의 소스 오퍼랜드를 지정할 수 있는 레지스터필드 rs가 있으며
MIPS에서는 이 rs필드의 레지스터 값에 상수 필드값을 더해 메모리 어드레스를 결정하는 Displacement Addressing방식.
기준점을 잡고 그 기준점에서 위치변경을 주면서 Addressing하는 방식.
기준점이 되는 레지스터가 바로 rs필드의 레지스터이며 32비트이므로 4기가 바이트의 어드레스를 나타낼 수 있다.
따라서 레지스터에 원하는 기준 주소를 저장하고 다시 offset값을 16비트(+-32KB)만큼 더 저장할 수 있으므로
32비트 레지스터로 표현 가능한 4GB 메모리 전체를 액세스할 수 있습니다.
따라서 4GB+-32KB

arrMoney[3] = nPrice + arrMoney[5];
nPrice는 $r16으로 맵핑되어 있고 arrMoney의 Base어드레스([0]의 주소)는 $r18로 맵핑되어 있다고 가정하면
lw $r8,20($r18) #$r8 = Mem[$r18 + 20] = arrMoney[5]
add $r8,$r16,$r8 #$r8 = $r16 + $r8 = nPrice + arrMoney[5]
sw $r8,12($r18) #Mem[$r18 + 12] = $r8
lw는 Load에 해당하는 오퍼레이션으로 메모리에서 1워드(4바이트)를 읽어서 레지스터에 저장하는 명령어.
$r8이 메모리에서 가져온 데이터를 저장할 타겟 레지스터고, $r18이 메모리 액세스의 기준이 되는
Base레지스터로 배열의 Base어드레스라고 생각할 수 있다.
그리고 Offset을 나타내는 부분이 바로 상수 20입니다.
'메모리의 $r18+20번지에서 한 워드를 읽어서 $r8레지스터에 저장하라'
읽힌 값은 임시로 $r8에 저장되고 nPrice변수는 $r16에 맵핑되어 있으므로 두 레지스터를 더해 $r8에 저장.
원하는 계산 결과가 $r8에 저장되었으므로 다시 arrMoney[3]에 해당하는 메모리에 저장해야 합니다.
이를 위한 인스트럭션이 sw이고 '$r18+12번지의 메모리에 $r8레지스터의 값을 저장하라'
20과 12로바뀌어 있는데 arrMoney와 nPrice변수는 int형태의 변수이고 4바이트여야 합니다.
CPU는 메모리 액세스를 바이트 단위로 하고 배열의 한 데이터는 4바이트를 차지하는 int이므로 12(3x4),20(5x4).
lw $r8,20($r18) #op(35) rs(18) rt(8) Constant(20)
add $r8,$r16,$r8 #op(0) rs(16) rt(8) rd(8) shamt(0) funct(32)
sw $r8,12($r18) #op(43) rs(18) rt(8) Constant(12)

프로그램 저장 방식의 CPU가 지원해야 할 일을 크게 3가지로 나누어보면,
기본적인 산술논리연산, 메모리 액세스, 프로그램의 순서를 바꿀 수 있는 조건부 혹은 분기문.
조건부 분기문에 해당하는 인스트럭션은 MIPS에서 I-타입 형태롤 구현합니다.
Equal이나 Not Equal체크가 대표적.
MIPS에선 beq와 bne인스트럭션으로 구현.
i = 50;
Again:
i = i - 1;
if (i! = 0) goto Again;
MIPS로는
addi $r16,$zero,50 #$r16 = 50
Again:
sub $r16,$r16,1 #$r16 = $r16 - 1
bne $r16,$zero,Again #if($r16 != 0) goto Again
x86계열이라면 addi대신
mov ax,50 #ax = 50
addi는 원하는 레지스터로 50이라는 상수를 옮겨오는 I-타입 인스트럭션.
addi로도 mov인스트럭션의 기능을 흉내낼 수 있어 굳이 RISC에 인스트럭션 숫자를 증가시키지 않음.
addi $r16,$r0,125에서
#r0은 무조건 0이라고 했으므로
$r16 = 125가 된다.
$r0레지스터도 $zero라는 별도의 이름을 가지고 있습니다.
그리고 1을 줄이기 위해 sub라는 인스트럭션을 사용했습니다.
bne인스트럭션을 사용해 $r16이 0이 되었는지 판단하여 아니면 Again으로 점프하여 0일 때까지 루프.
beq인스트럭션은 두 레지스터의 값이 같다면 지정된 어드레스로 분기하는 명령.

05 J-타입 인스트럭션
I-타입과 같이 상수 필드를 필요로 하되, rs필드와 같이 참조되는 레지스터가 없는 인스트럭션을 위한 포맷.
레지스터 필드를 없앤 대시 op필드를 제외한 나머지 모든 필드를 상수필드로 활요해 더 큰 범위의 상수값.
op(6) Address(26)
op:OP코드 부분. 모든 J-타입 인스트럭션은 op필드만으로 구분이 된다.
Address:모두 분기 명령어로 이 필드가 분기할 주소가 된다.
전형적인 인스트럭션이 바로 'Unconditional Branch'. 무조건 분기 명령.
bne나 beq가 특정 조건이 만족해야 타겟 주소로 점프하는 반면 무조건 어드레스에 지정된 주소로 점프.
bne $r16,$zero,Again #if($r16 != 0) goto Again이었던 코드를 J-타입으로 수정하면
beq $r16,$zero,Quit #if($r16 == 0) goto Go
j Again #goto Again
Go:
두 값이 같으면 아래의 Go부분으로 점프하여 j문장을 건너 뛰게 하였습니다.
beq에서 분기가 일어나지 않으면 j가 실행되어 Again으로 점프합니다.
J-타입이 따로 있는 이유는 조금이라도 많은 어드레스 필드를 확보하여 더 멀리 점프하려고.
26비트를 어드레스로 사용할 수 있으므로 1024배 늘어난 32MB까지 점프할 수 있습니다.
실제 모든 인스트럭션은 4바이트로 이루어져 있으므로 4바이트 단위로 점프하게 되고,
그 경우 점프할 수 있는 크기도 4배늘어난 128MB까지 입니다.
또한 J-타입을 위해 새로 추가되는 하드웨어가 상대적으로 미미합니다.
만약 많은 비용이들어가고 복잡해지면 포기했겠지만 별차이가 없어 도입.
RISC의 모토는 자주 쓰는 것을 빠르게, 구성은 단순화해 전체 퍼포먼스를 높이는 것.
하지만 여전히 32비트 CPU가 액세스하는 메모리 공간 4GB를 넘나들기엔 부족합니다.
그렇지만 대부분의 분기문은 현재 수행 중인 위치에서 가까운 곳으로 한정되어 있고 아주 먼곳은 드물다.
그래도 4GB영역 전체를 커버하는 점프명령을 위해 레지스터를 이용해 간접 주소 지정을 통해 점프하게 합니다.
인스트럭션 자체에 점프할 곳의 주소를 넣지않고, R-타입 인스트럭션 같이 레지스터를 지정해 해당
레지스터의 값을 타겟 어드레스로 삼아 점프하는 것입니다.
그래서 MIPS에서는 jr이라는 R-타입 인스트럭션을 준비합니다.
jr $r16
op(0) rs(0) rt(16) rd(0) shamt(0) funct(8)
jr은 R-타입 인스트럭션으로 구성되어 있고 op필드값도 0입니다. funct필드는 고유의 값으로 8을 가집니다.
jr은 점프하고자 하는 주소를 담고 있는 레지스터 하나만 지정하면 되므로 rt필드 하나만 타겟 주소.
$r16레지스터를 목적지 주소가 담긴 포인터 값으로 삼고 CPU가 수행하고 나면 점프합니다.
하드웨어적 구현은 PC레지스터 값에 점프하고자 하는 주소 값을 쓰면 자동으로 
다음 인스트럭션이 'PC가 가리키는 곳'에서부터 패치되어 실행.

MIPS에는 이 외에도 많은 인스트럭션이 있으며 3가지 유형 중 하나에 속할 것입니다.
정리해보면
1)R-타입 인스트럭션
add rd,rs,rt
0(6) rs(5) rt(5) rd(5) 0(5) 0x20(6)
rd = rs + rt
sub rd,rs,rt
0(6) rs(5) rt(5) rd(5) 0(5) 0x22(6)
rd = rs - rt
and rd,rs,rt
0(6) rs(5) rt(5) rd(5) 0(5) 0x24(6)
rd = rs & rt
or rd,rs,rt
0(6) rs(5) rt(5) rd(5) 0(5) 0x25(6)
rd = rs | rt
slt rd,rs,rt
0(6) rs(5) rt(5) rd(5) 0(5) 0x2a(6)
if(rs < rt) rd = 1; else rd = 0. 부등호 beq문과 함께 사용해 부등호 조건문을 이룰 때 사용.
jr rs
0(6) rs(5) 0(5) 0(5) 0(5) 8(6)
goto rs. 무조건 분기문. rs레지스터가 가리키는 주소로 분기한다.
2)I-타입 인스트럭션
addi rs,rs,constant
8(6) rs(5) rt(5) constant(16)
rt = rs + constant. 레지스터와 상수 간의 덧셈. Constant를 음수로 지정해 뺄셈 대용도 가능.
lw rt,address
0x23(6) 0(5) rt(5) address(16)
rt = (int)Memory[address]. 메모리의 address주소에 있는 값을 4바이트 읽어 rt레지스터에 저장
sw rt,address
0x2b(6) 0(5) rt(5) address(16)
Memory[address] = (int)rt. lw와 반대로 rt레지스터의 값 4바이트를 메모리의 address주소에 저장.
lb rt,address
0x20(6) 0(5) rt(5) address(16)
rt = (바이트*)Memory[address]. 메모리의 address주소에 있는 값을 1바이트 읽어 rt레지스터에 저장.
부호를 고려하여 rt레지스터의 값이 결정됨(sign extended).
sb rt,address
0x28(6) 0(5) rt(5) address(16)
Memory[address] = (바이트)(rt & 0xFF). lb와 반대로 rt레지스터의 하위 1바이트 값을 메모리의 address주소에 저장.
lui rt,constant
0x0f(6) 0(5) rt(5) constant(16)
rt = (constant << 16). constant를 rt레지스터의 상위 16비트에 로드한다.
addi인스트럭션과 함께 사용되어 32비트 상수를 로드할 수 있게 한다.
beq rs,rt,offset
4(6) rs(5) rt(5) offset(16)
if (rs == rt) goto $PC + 4 + offset. 조건부 분기문으로 rs와 rt레지스터의 값이 같다면
다음 인스트럭션 수행위치($PC+4)에서 offset만큼 떨어진 곳으로 점프한다.
bne rs,rt,offset
5(6) rs(5) rt(5) offset(16)
if (rs != rt) goto $PC + 4 + offset. 조건부 분기문으로 rs와 rt레지스터의 값이 다르다면
다음 인스트럭션 수행위치($PC+4)에서 offset만큼 떨어진 곳으로 점프한다.
slti rd,rs,constant
0x0a(6) rd(5) rs(5) constant(16)
if (rs < constant) rd = 1; else rd = 0. slt와 마찬가지로 beq와 함께 부등호 조건부 분기문에 사용.
3)J-타입 인스트럭션
j address
2(6) address(26)
goto address. 무조건 분기문
jal address
3(6) address(26)
goto address. $ra = $pc + 4. j와 마찬가지로 무조건 분기를 하나 $ra레지스터에 복귀할 주소를 저장.
함수 호출 등에 사용된다.

I-타입 인스트럭션의 한계
상수는 16비트밖에 못하였는데 32비트상수를 로드할 수 있는 방법이 있습니다.
lui $r16,0x1234 #$r16 = 0x12340000
0x1234라는 상수를 $r16레지스터의 상위 16비트에 로드하라는 것.
상수 16비트를 타겟 레지스터의 상위 16비트로 로드하는 것.
나머지 하위16비트는 addi를 사용합니다.
addi $r16,0x5678 #$r16 = $r16 + 0x5678
그러면 0x12345678.
모든 인스트럭션이 32비트의 제한된 크기를 가지며 이 안에서 레지스터와 상수를 동시에 지정할 수 있는
포맷은 I-타입이 유일합니다.
결국 기본 틀을 깨뜨리지 않는 범위내에서 인스트럭션에 32비트 상수를 지정할 수가 없었습니다.
(CISC라면 mov로 32비트 상수도 로드가능)
대부분의 상수로드는 16비트 범위 이내에서 이루어지고 일부 경우에 한해서 16비트를 넘어갑니다.
16비트 이상의 상수 로드의 경우에도 컴파일러가 두 번의 인스트럭션으로 나누도록 코드를 생성하면 됩니다.
프로그래머 입장에선 똑같이 작성하면 되므로 불편한 게 없습니다.
모든 인스트럭션이 동일한 크기를 가진다는 룰을 깨지 않고 두번의 계산이 전체적인 효율로보면 더 좋은 것.

*/