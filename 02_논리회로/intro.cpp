/*
게이트는 논리회로(Logic Circuit)를 설계함에 있어 가장 기본이 되는 단위.

01 기본 연산 게이트
내부 구조를 블랙박스로 하고 단순히 입출력 관계 그리고 내부 동작방식만 기억해도
아주 복잡한 형태의 프로그램을 만들 수 있다.
이런 형태의 프로그래밍을 바로 구조적 프로그래밍(Structual Programming)이라고 한다.
하드웨어에서도 아주 기본이 되는 함수가 있고 이 함수들의 조합으로 좀 더 복잡한 형태의 모듈을 만들고
계속 모듈을 연결해 하나의 디지털 하드웨어를 제작할 수 있는 것이다.
가장 기본이 되는 함수를 '게이트'라고 한다.
NOT:입력값을 반전하여 출력으로 내보냄.
AND:두 개의 입력값을 논리곱하여 출력으로 내보냄.
OR:두 개의 입력값을 논리합하여 출력으로 내보냄.
디지털 설계에서는 일반적으로 진리표라 부르는 형태의 테이블을 사용해 기능을 정의한다.
NOT 0 -> 1
    1 -> 0
AND 0 0 -> 0
	0 1 -> 0
	1 0 -> 0
	1 1 -> 1
OR  0 0 -> 0
	0 1 -> 1
	1 0 -> 1
	1 1 -> 1
아무리 복잡한 디지털 회로도 이 세가지 연산으로 모두 구현할 수 있다.

bool NOT(bool A) {
	if (A == true)
		return false;
	else
		return true;
}
bool AND(bool A, bool B) {
	if(A == true && B == true)
		return true;
	else
		return false;
}
bool OR(bool A, bool B) {
	if(A == true || B == true)
		return true;
	else
		return false;
}

02 BOOL 대수
대수는 덧셈, 뺄셈 등의 아주 기본적인 연산에서부터 연산들간의 결합법칙같은 규칙을 일컫는 것.
논리회로에서는 2진수를 기본으로 사용하므로 2진수에 대한 대수를 알고 있어야 한다.
AND는 곱셈으로 OR는 덧셈으로 표시한다.
NOT은 앞에 따옴표(')를 붙이고, AND는 사이에 가운데점(·), OR은 덧셈(+)기호.
실제+기호는 덧셈이아니라 BOOL대수의 OR연산을 나타내는 것입니다.
또한 연산자 간의 우선순위가 있습니다. ' > · > +
결합법칙, 교환법칙, 분배법칙도 성립.
드모르간(De Morgan)의 정리라는 법칙.
(x + y)' = x' · y'
(x · y)' = x' + y'
if문에서 많이 사용된다.
NOT(!)이 괄호 안으로 들어가면 AND(&&)는 OR(||)로 OR(||)는 AND(&&)로 바뀐다.
x + x'y = x(x + y) + x'y = xx + xy + x'y = x + (x + x')y = x + y

03 BOOL 대수의 응용
CPU안에는 논리 연산을 하는 ALU(Arithmetic Logic Unit)모듈이 존재.
어떤 회로를 설계하려면 해당 모듈의 기능을 정의를 가장 먼저 해야 한다. 함수도 입출력 관계로 결정.
덧셈 회로를 Adder라고 칭하고 Adder의 기능을 1비트의 두 입력을 더해서 그 결과를 리턴하는 것이라고 해보자.
bool Adder(bool A, bool B) : 2진 논리로 A와 B를 더한 결과를 리턴하는 함수.
1 + 1은 10이 되어야 한다. 따라서 출력값이 단순히 한 비트로는 안되고 자리올림까지 포함해 두 비트여야 합니다.
자리 올림 값을 캐리(Carry)라고 한다.
그리고 캐리를 상위 비트의 덧셈에 같이 더해줘야 합니다.
다시 바꾸면 void Adder(bool A, bool B, bool InCarry, bool* pSum, bool* pOutCarry);
A,B 두개의 비트 입력과 아랫자리에서 발생한 자리 올림, 즉 아랫자리의 캐리 값을 받아 더한 후 그결과를 pSum에,
그리고 자리 올림값을 pOutCarry에 리턴하는 것.
실제 어떤 함수를 구현하기 전에 그 입출력을 함수의 프로토타입을 선언하고 구현 후에도 이 원형을 사용해 호출합니다.
디지털 회로도 블랙박스 형태로 모듈을 나타내고 그 입출력을 선으로 표현한다.
Carry In ->|       |-> Carry Out
       A ->| Adder |-> Sum
       B ->|       |
A B CarryIn CarryOut Sum
0 0    0        0     0
0 0    1        0     1
0 1    0        0     1
0 1    1        1     0
1 0    0        0     1
1 0    1        1     0
1 1    0        1     0
1 1    1        1     1
Sum이 1이 되는 경우 (0 0 1), (0 1 0), (1 0 0), (1 1 1) 중 어떤 것이라도 발생하면 출력값 Sum이 1이 되야한다.
Sum = (0 0 1) + (0 1 0) + (1 0 0) + (1 1 1)
그리고 각 괄호항이 언제 1이 되느냐 하는 것. 세 입력값이 괄호 값과 같을 때만 1이되어야 합니다. NOT을 이용.
Sum = A'B'C + A'BC' + AB'C' + ABC
Carry Out = A'BC + AB'C + ABC' + ABC = AB + BC + AC
간략화하려면 카르노 맵이라는 기계적인 방법이 있다.
값들을 게이트를 이용해 회로를 그릴 수 있다.
1비트 Adder를 사용해 32비트 덧셈회로를 꾸밀 수 있고 다른 용도로 사용할 수도 있다. 함수가 완성된 것.
CPU를 구성하는데 자주쓰이는 MUX(Multiplexer)는 여러 개의 입력 중에 특정 입력을 선택해 출력으로 내보내는 '데이터 선택기'.
S(선택신호) ->|        |
  	  A(0) ->| 2x1MUX |-> Output
	  B(1) ->|        | 
선택신호의 개수는 전적으로 입력신호의 개수에 달려 있다. 2가지입력이 있을 수 있으므로 1개의 선택신호로 모두 표현.
S A B Output
0 0 0   0
0 0 1   0
0 1 0   1
0 1 1   1
1 0 0   0
1 0 1   1
1 1 0   0
1 1 1   1
Output = S'AB' + S'AB + SA'B + SAB = S'A + SB
따라서 2입력 OR게이트와 두 개의 2입력 AND게이트 그리고 NOT게이트 하나가 필요합니다.

카르노 맵
모든 입력에 대해 가능한 조합을 만들어 진리표를 만들면 입력 부분이 마치 인덱스처럼 순차적으로 증가합니다.
A\BC 00 01 11 10
 0   0  1  ⑶  2
 1   4  ⑸ ⑺  ⑹
어둡게 칠해진 부분을 최대한 많이 그룹을 묶어야 합니다.
3,7은 BC. 5,7은 AC. 7,6은 AB.
Carry Out = AB + AC + BC.

*/