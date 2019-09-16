/*
논리회로가 주어진 입력에 따라 출력이 결정되는 회로라면 CPU역시 입력에 따라 출력이 결정되는 논리회로다.
CPU는 원하는 용도에 맞는 입력외에 회로의 동작을 결정하는 컨트롤 입력이 별도로 있다는 것이 차이점.
콘트롤입력에 따라 여러가지 연산을 할 수 있도록 회로를 구성할 수 있다.
초창기CPU는 컨트롤 입력을 사람이 손으로 진공관을 뽑았다 꽂았다 하면서 조정하였는데
현재는 메모리에서 자동적으로 이 입력값을 읽어가는 형태로 바뀌었습니다.
이 입력값을 '인스트럭션'이라고 부릅니다.

01 CPU(Central Processing Unit)의 탄생 비화
논리회로는 주어진 입력에 대해 적절한 출력을 내어주는 절차적 자동화 장치.
CPU는 사실 논리회로의 조합에 불과합니다.
CPU의 특징은 유연성과 범용성.
이전 시스템
입력->논리회로->출력
추가 시스템
입력->논리회로->출력
추가입력┘
추가입력으로 CPU의 특징인 유연성과 범용성을 갖출 수 있게 됩니다.
추가의 입력만 충분히 확보되고 또 그 입력이 적절하게 기존 입력과 조합이 되도록 회로를 꾸민다면
추가 입력을 조정함으로써 기존 입력에 대한 출력 결과를 얼마든지 조절할 수 있다.
특정 목적을 위해서 설계한 논리회로는 다른 용도로 사용할 수 없고 다시 설계해야 합니다.
하지만 입출력 관계를 한가지 동작형태로 고정시키지 않고, 아주 일반적인 형태의 연산으로 나누어 설계하고
이런 연산 자체를 선택할 수 있도록 추가 입력선을 구성하면 재설계할 필요가 없습니다.
우리가 필요로 하고 필요로 할 것 같은 여러 연산을 정의하고 입력값은 그 연산의 대상이 되도록, 추가입력은
그 연산의 종류를 지목하는 값이 되도록 설계하면 어떠한 형태의 로직이 되더라도 원하는 목적을 이룰 수 있다.
입력값들은 그때그때 외부 입력에 따라 결정되는 값입니다.
추가 입력은 자판기가 동작하기 전에 이미 결정이 나 있어야 하는 것이고,
입력값은 자판기가 동작하면서 동적으로 외부에서 받는 입력이라는 것.
추가 입력은 프로그램을 짜는 과정이고, 입력은 프로그램 수행 과정입니다.

02 범용 논리회로
처음 입력 부분을 데이터 입력, 추가 입력 부분을 컨트롤 입력.
컨트롤 입력은 데이터 입력을 잘 조합하여 원하는 형태로 가공하게 하는 입력.
같은 형태의 데이터 입력이 들어가더라도 컨트롤 입력을 바꾸는 것만으로 출력이 얼마든지 바뀔 수 있는 것.
데이터입력1->|         |->출력
데이터입력2->| 논리회로 |->출력
                ^ ^
			    | |
	     컨트롤 입력(2비트)
1 2 컨트롤입력 의미 출력
0 0    00     AND  0X
0 0    01     OR   0X
0 0    10     XOR  0X
0 0    11     PASS 00
0 1    00     AND  0X
0 1    01     OR   1X
0 1    10     XOR  1X
0 1    11     PASS 01
1 0    00     AND  0X
1 0    01     OR   1X
1 0    10     XOR  1X
1 0    11     PASS 10
1 1    00     AND  1X
1 1    01     OR   1X
1 1    10     XOR  0X
1 1    11     PASS 11
PASS는 입력을 그대로 출력으로 내보내는 것.
X표시는 '묻지마 조건'의 표시. 논리 연산에서는 두 개의 입력이 들어가면 출력은 하나이기 때문에.
두 번째 라인은 어떤 결과가 나와도 신경 안 쓰겠다는 뜻. 'Don't Care Condition'
카르노맵을 그려 단순화해서 배치하면
출력 1           출력 2
   00 01 11 10      00 01 11 10
00 0  0  1  0    00 X  X  X  X
01 0  1  1  1    01 X  X  X  X
11 0  0  1  1    11 0  1  1  0
10 0  1  0  1    10 X  X  X  X
출력 1 = D1C2 + D1D2'C1 + D1D2C1' + D2C1'C2 + D1'D2C1C2'
출력 2 = D2
카르노 맵에서 공통 분모가 되는 부분을 찾아 그룹핑하여 수식을 간소화합니다.
얻을 결과 수식을 가지고 그대로 게이트로 표현하면 됩니다.
실제 논리회로를 설계하진 않더라도 어떤 형태로 논리회로가 이루어져 있으면 동작을 어떻게하는지 정도에 대한 개념은 파악.
CPU를 이루는 기본 단위가 바로 논리회로이기 때문이다.
ALU는 논리 연산을 하는 조합 논리회로(Combinational Logic Circuit)을 의미합니다.

03 산술 연산 장치 - Adder의 구현
자리 올림 값을 캐리(Carry)
덧셈과 같은 산술 연산에서는 캐리가 발생하므로 출력 라인이 하나 더 있어야 합니다.
ADD라는 연산을 추가하기 위해선 3비트로 확장해야 하지만 여기선 그냥 PASS를 삭제하고 ADD를 넣음.
1 2 컨트롤입력 의미 출력
0 0    11     ADD  00
0 1    11     ADD  01
1 0    11     ADD  01
1 1    11     ADD  10
자주 쓰이는 용도의 회로를 구성하여 모듈화하고 블록을 연결해 점점 큰 회로를 구성해나가는 방식을 이용하자.
각각의 연산 모듈은 두 개의 데이터 입력 a,b를 받아들여 출력 r을 생성합니다.
MUX는 여러 개의 입력 중 하나를 선택하여 그 값을 출력으로 내보내는 논리회로.
4가지 연산 중 하나를 선택할 것이므로 2비트의 동작입력이 필요합니다.
각각의 연산 모듈에 공통적으로 a,b의 입력을 가하고 각 모듈의 출력을 MUX에 연결한 후 이를 동작입력을 통해
선택한 MUX의 출력을 전체 회로의 최종 출력값으로 사용하면 되는 것.
동작입력이 컨트롤 입력.
a->| AND  0 |
b->| OR   1 |->r
   | XOR  2 |
   | ADD  3 |
      ^   ^
	  |   |(2)
	carry operation
덧셈포함된 ALU를 설계했다. 카르노 맵을 그려서 일일이 게이트를 나열하여 설계한 경우보다 심플하고 ADD도 추가됨.
C프로그램을 main안에 처음부터 끝까지 코드를 나열하여 작성해도 되지만 대부분의 경우는 기능별로 함수를 만들고 함수를 호출.

04 32비트 ALU의 구현(팬티엄)
앞서 작성한 1비트용 ALU를 이제 내부를 신경 쓰지 않기 위해 전체 덩어리를 하나로 모듈화.
a->|ALU|->r
b->|   |->Carry
     ^(2)
	 └Operation
a,b 두 입력 데이터를 받아 동작입력값으로 선택된 연산을 행하여 그 결과를 r로 출력합니다. 
ADD연산인 경우 캐리출력으로 자리 올림 결과가 출력됩니다.
단순하게는 1비트 ALU32개를 나란히 나열하여 사용하는 것.
ADD인 경우 각 1비트 ALU들이 서로 독립적으로 계산하므로 틀린 답이 나오게 됩니다.
자리 올림을 고려하지 않았기 때문이다.
따라서 각 1비트 ALU들이 발생한 캐리를 다시 상위비트에 반영할 수 있도록 회로가 수정되어야 합니다.
a->|ALU|->r
b->|   |->Carry Out
	^ ^(2)
	| └Operation
	└Carry In
각 인접 비트끼리 캐리 입출력을 연결합니다.
하위 비트에서 발생한 캐리 출력은 상위 비트의 캐리 입력으로 연결해야 합니다.
하지만 1비트 ALU에 비해 속도가 느리다는 단점.
게이트의 전기적 특성에 의해 입력에서 출력까지 어느 정도 시간이 걸립니다.
계산량은 32배가 되었지만 시간도 32배가되어 큰 의미가 없습니다. 리플캐리(Ripple Carry)라고 합니다.
리플캐리 방식은 속도상의 문제로 실제로는 잘 사용되지 않습니다.
대신 발생할 캐리를 미리 입력값에서 한꺼번에 계산하는 캐리 룩 어헤드(Carry Look Ahead)방식을 사용합니다.

05 ALU에서의 뺄셈 구현
뺄셈 연산은 덧셈 연산을 살짝 수정하는 것만으로 구현할 수 있습니다.
뺄셈 대신 음수의 덧셈으로 바꾸는 것.
음수는 보수라는 개념을 사용합니다.
두 개의 자연수가 합이 N이 되는 관계에 있을 때 두 수를 'N의 보수관계에 있다'라고 부릅니다.
음수라고 정해진 수는 쌍을 이루는 양수와 더하면 0이 되는 성질을 가져야만 합니다.
1111(2)을 0으로 삼고 모든 숫자들에 대해 1111(2)의 보수를 취하는 경우는 더해진 합이 1111(2)이고 각 비트가 1이되므로 1의 보수.
0000(2)를 기준으로 하는 경우에는 그 합이 각각 0이므로 2의 보수가 됩니다.(1+1=0)
1의 보수에서는 0이 0000(2), 1111(2) 2개가 존재하게 된다.
2의 보수에서는 0이 0000(2) 하나가 존재.
양수인 경우 최상위 비트는 모두 0이고 음수는 모두 최상위 비트가 1로 세팅되어 있다.
그래서 1000(2)은 8이아닌 -8로 취급하는 것이 일반적.
1의 보수는 부호가 다른 숫자들의 모든 비트가 서로 반전되어 있습니다.
하지만 ADD연산결과 최상위 비트에서 캐리가 발생하면 결과값에 1을 더해줘야만 합니다.
반면 2의보수는 모든 비트를 반전한 뒤 1을 더하면 2의 보수가 됩니다.
이 말은 b를 반전하여 입력으로 주고 똑같이 ADD연산을 하는데 이때 캐리 입력을 1로 주는 것과 같습니다.
어차피 캐리 입력은 사용하기 위한 것이고, 최하위 캐리입력은 0으로 입력해야 하지만,
뺄셈연산일 경우에는 최하위 캐리 입력에 1을 입력하고 ADD를 하면 결국 다른 추가없이 쉽게 뺄셈이 가능.
4비트로 나타낼 수 있는 숫자는 16가지이고, 1의 보수인 경우는 -7 ~ 7인 반면에 2의 보수는 -8 ~ 7로 더 효율적.
SUB연산은 별도로 모듈이 추가되는 것이 아니라 2의보수를 사용해 단순히 b입력을 반전시키고 ADD연산을 하면 됩니다.
SUB연산을 할 경우엔 동작입력을 ADD에 해당하는 10(2)을 넣어주고 반전해 주면 되는데
b입력을 이등분하여 하나엔 NOT게이트를 추가해서 선택할 수 있도록 2입력 MUX를 사용합니다.

06 인스트럭션(Instruction) 맛보기
C언어는 B언어를 개량한 고급언어입니다. 그리고 C언어로 작성된 소스는 컴파일러를 통해 어셈블리어로 바꿉니다.
그리고 어셈블러라는 것을 사용하면 어셈블리어는 인스트럭션의 집합인 바이너리(Binary)코드로 바뀌게 됩니다.
인스트럭션은 CPU가 이해하는 유일한 언어이며 2진수로 구성되어 있습니다.
이러한 인스트럭션에 1:1로 대응시켜 2진수를 사람들이 알아보기 쉬운 단어 형태로 바꾼 것을 어셈블리(Assembly)코드.
입력값이 다름 아닌 인스트럭션입니다.
ALU로 행하고자 하는 연산을 선택하는 동작입력의 값이 바로 인스트럭션.
MUX의 동작입력을 최상위 비트로 본다면 AND(0 00), OR(0 01), XOR(0 10), ADD(0 11), SUB(1 11) 이렇게 5종류 인스트럭션.
실제로는 인스트럭션을 구성하는 요소는 세가지로 컨트롤 명령어와 실제로 연산을 하기 위한 두 값(Operand)로 이루어져 있습니다.

ALU의 NOT연산 설계
NOT기능을 추가해서 설계해도 상관은 없지만 기존 ALU에서 데이터 입력 중 한 곳에는 반전하고자 하는 데이터를 연결하고
나머지 한 쪽에는 상수 1을 주고 XOR연산을 하면 결과는 반전된 비트가 됩니다.

*/