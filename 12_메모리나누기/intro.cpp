/*
물리적으로 하나의 메모리를 논리적인 단위로 몇가지 구분을 하는데 대표적인 것들?
프로그램의 인스트럭션 코드가 위치하는 코드 세그먼트, 전역 변수들이 위치하는 데이터 세그먼트,
지역 변수들을 위한 스택 세그먼트, 동적인 메모리 할당을 위한 힙 세그먼트 등으로 나뉜다.
논리적인 구분일 뿐 메모리 상의 어느 위치에 어느 세그먼트가 위치해도 문제는 없다.
다만, 코드 및 데이터 세그먼트는 최초에 프로그램이 시작될 때 그 크기가 결정되고 변하지 않지만,
스택과 힙 세그먼트는 프로그램 실행 도중 동적으로 크기가 변하므로 효율성을 위해 서로 이웃하게끔 자리잡음.

전역 변수와 지역변수의 차이점이 뭘까요?
액세스 범위와 라이프 사이클.
전역 변수는 프로그램 어디서나 참조할 수 있으며, 프로그램 시작과 함께 종료될 때 한 개체로서 유효.
지역 변수는 선언된 함수 내부에서만 유효하며 함수가 호출될 때마다 새로운 개체로 생성.
전역 변수는 데이터 세그먼트에 자리잡고 절대 주소로 액세스되지만 지역변수는 스택세그먼트에 자리잡어
그때그때 생성 주소가 틀려 스택포인터를 이용해 상대적인 주소로 액세스합니다.

01 코드 및 데이터 세그먼트
변수 선언은 메모리의 특정 부분을 컴파일러가 기억했다가 그 곳을 다른 용도로 사용치 않게 하는 것.
그리고 해당 변수 이름이 코드상에 나올 때마다 기억된 메모리로의 액세스 하는 것.
변수의 초기값은 컴파일러나 혹은 개발자가 결정하는 것.
초기화를 하지 않으면 그곳에 어떤 값이 있는지 아무도 모릅니다.
그래서 변수를 선언하면 무엇이 있는지 확실하게 하기 위해 초기화를 같이 한다.
어셈블리어는 
mov byte ptr [ebp-4],2Ch
C언어는
int global = 1;
int main() {
	int local = 2;
	return 0;
}
	int global = 1;
	int local = 2;
00311708 C7 45 F8 02 00 00 00 mov         dword ptr [ebp-8],2
local은 잘 되었지만 global은 초기화 했지만 코드가 없습니다.
int global = 1;
int main() {
	int local = global;
	return 0;
}
	int local = global;
012B1708 A1 00 90 2B 01       mov         eax,dword ptr ds:[012B9000h]
012B170D 89 45 F8             mov         dword ptr [ebp-8],eax
global이라는 변수는 ebp라는 레지스터를 매개로 하지 않고 직접 012B9000h주소로 맵핑되어 있다.
그리고 이 주소값을 eax레지스터로 옮겼다가 다시 local변수에 해당하는 메모리 공간에 저장했습니다.
012B9000h번지에는 01 00 00 00으로 채워져 있습니다. 처음 초기화한 1이라는 값.
리틀엔디안 방식이기 때문에 앞에서부터 채워졌다.

우리가 해야하는 건 CPU의 전원을 켰을 때 최초 시작 어드레스가 어딘지 파악해야 하고,
어셈블리로 만든 프로그램이 그 시작 어드레스에 정확히 위치하도록 메모리에 기록해 주는 것.
코드가 있는 메모리 영역을 데이터 영역으로 사용하면 문제가 생깁니다.
CPU는 그저 PC레지스터가 가리키는 메모리 값을 읽어와 인스트럭션으로 취급하여 실행할 뿐이고
그 값이 데이터인지 인스트럭션인지는 프로그래머가 결정해야 함.
그러므로 인스트럭션이 차지하는 메모리 영역과 변수로서 사용할 영역을 구분해서 써야 한다.
일반적으로 대부분의 프로그래머나 컴파일러가 실제 인스트럭션이 들어가는 코드 부분과 데이터 영역을 구분.
이는 물리적으로 딱 정해진 것이 아니라, 사용자가 코드영역과 데이터 영역을 구분해 사용할 뿐입니다.
영역구분을 세그먼테이션(Segmentation)이라고 하는데 코드 세그먼트, 데이터 세그먼트라 부릅니다.
global변수는 데이터 세그먼트에 해당되는 변수이기 때문에 코드가 없었다.
CPU에서는 전혀 구분하지 않고 최초의 시작주소부터 차례대로 값을 읽어 '코드'로 해석하고 실행하는 것뿐.
그 과정에서 프로그램은 어느 메모리 영역을 데이터로 읽기도하고 쓰기도 하는 것.
그리고 이런 코드와 데이터를 포함한 메모리의 구성은 프로그램 수행 전에 개발자가 결정해 기록해야 합니다.
이 결정에는 코드 세그먼트뿐아니라 데이터 세그먼트에 대한 초기값 결정도 포함.
즉, 데이터 세그먼트에 맵핑된 변수들의 초기값이 이미 결정나 있다는 얘기.
일반적인 메모리는 램(RAM)으로 전원이 꺼졌다 들어오면 어떤 값인지 몰라 초기화해주는 과정이 필요.
이를 위해 일반적으로 CPU가 가장 먼저 코드를 읽어 들이는 주소를 ROM으로 구성합니다.
ROM부분에 간단한 부트(Boot)프로그램을 작성해서 기록해두는 것.
ROM은 한번 기록을 하면 전원을 끄더라도 지워지지 않는다.
따라서 전원이 켜지면 CPU는 가장 먼저 롬의 부트 프로그램을 실행하게 됩니다.
부트 프로그램은 하드 디스크나 플래시 메모리와 같은 반영구 기록장치에서 이미지를 읽어들여 램에 복사.
이미지라는 것이 CPU가 시작되었을 때의 메모리 상태값을 지닌 것.
    어드레스
|CPU| -> |      ROM       |ㄱ1. 최초 프로그램 시작위치(0x100)
|   | -> | (부트프로그램)  | -> 2. 하드 디스크에서 이미지 읽고 |하드디스크|
|   | ┌> |      RAM       | <- 3. 램으로 복사                |         |
|   | -> |                |
      └ 4. 실제 프로그램으로 점프
최초에 하드웨어저긍로 CPU전원이 들어오자마 0x100으로 PC가 셋팅됐다고 가정.
0x100부터 CPU가 인스트럭션 파치를 하며 수행합니다.
해당 롬 프로그램이 수행되면서 하드 디스크에서 램 영역에 복사할 이미지를 찾아 읽어오고,
이를 램으로 복사해서 원하는 초기 상태를 만들게 됩니다.
램에는 원하는 프로그램의 코드와 데이터들의 초기값이 들어있게 되고,
마지막으로 부트 프로그램은 램상의 코드 세그먼트 중 한 곳으로 점프합니다.
그리고 본격적인 프로그램이 시작.
작성한 코드만 램으로 복사하는 것이 아니라 데이터 세그먼트의 내용도 함께 복사합니다.
데이터 세그먼트는 사용할 변수에 해당하는 영역이고 변수의 초기값이 됩니다.
즉, 데이터 세그먼트에 맵핑된 변수는 프로글매 이미지가 메모리로 로드되는 순간 같이 초기화되는 것.

PC역시 처음 전원이 들어오면 CPU는 롬 바이오스 영역을 실행하기 시작합니다.
(PC레지스터 초기값에 해당하는 주소에 롬 바이오스를 배치하게 설계한 것)
그리고 롬 바이오스는 여러 가지 주변 장치를 체크하고 하드디스크나 CD-ROM 등의 부트 섹터에서
이미지를 읽어 메모리로 복사합니다.
그리고 그 복사한 영역으로 점프함으로써 실제 프로그램이 기동되는 것.
복사된 이미지는 윈도우즈나 리눅스 같은 OS프로그램.
애플리케이션도 마찬가지로 윈도우즈에서 탐색기를 띄어 exe파일을 실행하면 실제로는 LoadLibrary라는
윈도우즈 API함수가 불리면서 하드디스크에서 해당 exe의 이미지를 읽어 메모리상에 로드합니다.
이 과정에서 데이터 세그먼트에 해당하는 값도 같이 로드되므로 이미 초기화되어 있음.
exe파일에는 이런 데이터 세그먼트를 초기화할 수 있도록 데이터 세그먼트의 메모리 내용을 가지고 있어야 한다.
만약 데이터 세그먼트가 2GB라면 exe파일 안에도 이에 해당하는 2GB크기의 데이터가 있어야 합니다.
하지만 실제로 전체 데이터 세그먼트 영역이 모두 변수로 맵핑되는 것도 아니고, 초기화가 필요한 변수는
적으므로 실제 exe파일 안에는 메모리 값을 그대로 저장하지 않고, 데이터 세그먼트의 어느 부분을 어떤
값으로 초기화하라는 메타 데이터 형태로 값이 저장되어 있습니다.
그리고 이를 메모리에 로드하는 과정에서 메타 데이터를 해석해서 메모리상의 데이터 세그먼트 부분을
적절히 초기화하는 것입니다.
(하지만 큰 OS가아니라 펌웨어나 OS가 없으면 바이너리 이미지가 실제 데이터 및 코드 세그먼트 전체를
그대로 나타내게 됩니다. 코드와 데이터 세그먼트 크기가 실제 이미지 크기가 됨.)
결론적으로 global변수는 데이터 세그먼트로 맵핑된 변수이고, 이미지가 메모리로 로드되는 순간
이미 global이라는 변수에 해당하는 메모리도 같이 초기화되는 것.

02 스택 세그먼트
데이터 세그먼트는 코드 세그먼트와 함께 프로그램 이미지가 메모리로 넘어올 때 같이 로드되고 초기화됨.
전역변수란 함수 바깥에 선언된 변수로서 프로그램이 실행되는 내내 그 값을 유지하고 모든 곳에서 접근이 가능.
진역변수는 함수 안에 선언되고 해당 함수 안에서만 접근할 수 있음.
변수 없이 프로그램을 만드는 것은 불가능하고, 코드 전체에 접근 가능한 형태인 전역 변수가 필수적.
지역변수를 이용하는 이유는 함수마다 독립성을 높이기 위함.
프로그램에서 함수는 어떤 동작 자체에 대한 정의만 기억하고 내부 동작은 잊어서
함수의 독립성을 높일 수 있도록 전역 변수를 쓰지 않고 일회성이면서 함수 내부에 국한되는 지역 변수를 쓰는 것.
데이터 세그먼트의 각 변수들은 메모리상에 그대로 맵핑되므로 고정된 메모리 주소를 얻습니다.
지역 변수도 데이터 세그먼트가 아닌 각 함수만의 고유 영역에 배치되도록 하는 것이 좋다.
각 함수마다, 고유한 데이터 세그먼트를 따로 만들어 여기에 할당할 수 있다.
함수라는 것은 어떤 주어진 입력에 대해 적절한 처리를 해서 출력을 내보내는 단위.
내부 동작에 대해선 외부에선 관여하지 않고 입력갑소가 함께 호출될 때만 수행하는 독립적인 형태의 모듈.
따라서 함수가 내부적으로 사용하는 변수들은 함수가 호출되는 동안만 필요. 리턴 후에는 불필요.
그래서 함수가 호출되는 시점에서 이들 변수를 위한 메모리 공간을 할당해주고, 함수가 리턴하는 시점에서
다시 회수하는 방식을 사용하면 많은 메모리 공간을 절약.
모든 함수가 항상 동시에 불리는 것이 아니므로, 현재 수행 중인 함수 변수에 대해서만 확보하면 됨.
그러므로 공간 하나만 확보하면 되는데 가장 많은 변수를 사용하는 함수를 기준으로 메모리 공간을
확보하고, 해당 공간에 함수가 불릴 때마다 해당 함수의 변수들을 맵핑해서 사용.

프로그램을 만들 때 사용하는 방식을 탑다운 방식이라고 합니다.
제일 위에 엔트리 포인트(Entry Point)의 하나의 함수가 있고 여기서 시작하여 점점 다른 함수를 불러가며
프로그램이 구동된다는 것.
C에서는 main이라는 엔트리 포인트가 있고 여기서 시작하여 다른 함수들이 순차적으로 불리며 진행.
이 시점은 이미 동시에 두 개 이상의 함수가 불린 셈.
main이라는 함수 역시 OS에서 호출된 상태.
main함수를 비롯해 이어서 불린 함수 역시 아직 실행 중이므로 각각 변수 공간을 필요로 하게 됨.
그래서 스택(Stack) 저장 방식이 나옴.
스택은 변수를 메모리 공간에 점점 쌓아 올리는 것.
우선 메모리 상에 지역 변수를 위한 공간을 할당합니다.
하지만 최초에는 어떤 함수의 변수도 이 공간에 맵핑되지 않습니다.
이 공간의 시작 어드레스는 스택포인터라 불리는 특정한 레지스터에 기억하도록 합니다.
그리고 함수가 호출되면 스택 포인터를 기준으로 함수에 필요한 변수만큼 맵핑하는 것.
맵핑에 사용된 크기로 스택 포인터를 조정합니다.
같은 공간상에 변수를 맵핑하는 것이 아닌 맵핑이 끝난 이후 지점에서 새로 맵핑하는 것.
					|코드 세그먼트 |
함수1이 불리기전 SP_/|             |<-함수1호출(변수 맵핑)    함수1─────┐
함수1이 불린 후  SP_/|    스택     |<-함수2호출(변수 맵핑)      | 함수2 |
함수2이 불린 후  SP_/	|             |<-스택의 남은 공간         └───────┘
					|             |
					|데이터세그먼트|
					|             |
우선 코드 세그먼트와 데이터 세그먼트는 정확하게 그 크기가 정해지는 부분이므로 먼저 메모리상에 할당.
그리고 남은 공간에 스택을 사용.
아무 함수도 불리지 않은 상태에서는 SP는 스택의 시작 부분을 가리키고 있습니다.
함수1이 호출되자 함수1에 필요한 변수 크기만큼 스택에 맵핑되고 SP가 그 크기만큼 조절.
함수1이 끝나기 전에 이 안에서 함수2를 호출하자 이후 영역에 함수2의 변수를 맵핑하고 SP를 증가시켜 조절.
함수 안에서 다른 함수를 부른 경우 다른 함수를 호출한 함수를 Caller, 받은 함수를 Callee라고 함.
이 관계는 상대적인 것.
중요한 것은 콜러는 콜리가 리턴하기 전에는 절대로 끝나지 않는다.
함수1은 함수2가 리턴하기 전까지는 리턴하지 않습니다.
항상 호출받은 콜리 함수가 호출한 콜러보다 뒤 쪽에 맵핑됩니다.
그리고 콜리 함수가 콜러보다 먼저 리턴.
따라서 콜리 함수가 리턴하면 SP를 해당 콜리 함수에 해당되어 있던 만큼 감소시키면 됨.
					|코드 세그먼트 |
4. 함수1 리턴 후 SP_/|             |->3. 함수1리턴           함수1─────┐
2. 함수2 리턴 후 SP_/|    스택     |->1. 함수2리턴             | 함수2 |
                    |             |                          └───────┘
					|             |
					|데이터세그먼트|
					|             |

스택구조를 사용해 지역 변수를 맵핑하면 좋은점
1)동시에 여러 함수가 호출되는 상황이 발생하더라도 서로의 변수 영역을 침범하지 않습니다.
항상 함수가 호출될 때마다 새로 스택에 공간을 할당해 변수를 맵핑하므로 넘치지않는이상 좋다.
2)모든 함수에 미리 변수 할당을 하지 않음으로서 상당한 메모리를 절약할 수 있습니다.
동시에 불리는 함수(Calling Depth)는 많아야 몇개 안됩니다.
3)함수의 재귀호출(Recursive Call)을 사용할 수 있습니다.
재귀호출이란 호출된 함수가 내부에서 다른 함수를 호출하는 것이 아닌 자기 자신을 다시 호출하는 경우.

스택 오버플로우는 스택사이즈가 동시에 호출되는 함수들이 다 이용하지 못할 만큼 작아서 생기는 에러.
전체 지역변수 크기가 남은 스택공간보다 클 경우 스택 오버플로우(Stack Overflow)발생.
이럴 경우 아무 대책없이 프로그램을 계속 실행하면 데이터 세그먼트 영역을 초과해 전역변수가 영향받음.
그래서 일반적으로 버그를 방지하기 위해 CPU나 OS차원에서 스택 오버플로우를 감지할 수 있는 기능을 제공.
같은 이름의 함수가 불리어도 스택포인터는 증가하고 지역변수가 맵핑됨.
실제로 컴파일 옵션을 통해 스택사이즈크기를 변경할 수 있는데 변경하더라도 횟수만 늘지 에러 발생.
따라서 재귀호출을 하는 프로그램은 반드시 끝을 맺을 수 있는 조건문이 있어야 합니다.
int RefCall(int nVal, int nUtil) {
	int nSum;
	if (nUtil == nVal)
		nSum = nVal;
	else
		nSum = nVal + RefCall(nVal + 1, nUtil);
	return nSum;
}
int main() {
	int nSum = RefCall(0,5);
	getch();
	return 0;
}
도스 창이 닫혀 버리는 것을 방지하기 위해 getch(). 사용자가 임의의 키를 눌러야 종료.
nUtil 인자가 추가되었고, 조건문추가.
RefCall함수 안에서 다시 RefCall을 호출하는 코드 이전에는 순서대로 값을 출력하고 리턴된 이후에는
역순으로 반복되어 출력.
재귀호출을 이용하면 종종 굉장히 효율적으로 코드를 작성할 수 있습니다.
for문을 쓰지 않고 재귀호출을 통해 원하는 프로그램을 만들 수 있는 것.
트리 탐색같은 경우에는 재귀호출 방식을 이용해 이루어집니다.

장기같은 프로그램에서는 주어진 국면을 수치적으로 판단해 점수를 낼 수 있는 함수를 작성해야 합니다.
이런 함수를 평가함수라고 부르는데 가장 쉽게 만드려면 현재 국면에 있는 기물의 개수와 종류를 보고 판단하는 것.
자신의 것은 중요도가 높은 순으로 장군은 무한대, 5, 1이런식으로 점수를 부여하고 상대편 기물에는
같은 크기를 가지되 마이너스 점수를 부여하여 현재 국면상의 모든 기물의 점수를 더한 값이 평가 함수의 리턴값.
시작할 때 평가함수는 0이지만 진행되면서 바뀜.
평가함수가 준비되면 트리를 구성해야 합니다.
구성하려면 현재의 국면에서 말을 한 번 움직였을 때 가능한 모든 국면에 대해 평가 함수를 통해 점수를 매긴다.
그리고 예산한 수 뒤의 국면에서 상대 편 말을 움직였을 때 가능한 모든 국면을 생성해 다시 평가함수로 점수를 매긴다.
이를 반복하면 트리가 완성이 될 것이다.
한 수 후의 각 상태에서 다시 사람이 둘 수 있는 모든 국면을 생각해보는 것.
만일 충분한 시간과 메모리 자원이 허락한다면 가장 유리한 루트를 따라 다음 국면을 전개.
평가함수가 가장 자신에게 유리한 경우를 선택하여 컴퓨터는 자신이 수를 둘 때는 점수가 가장 높은 경우,
사람이 수를 두는 경우는 가장 나쁜 경우를 선택해 경로를 선택하면됩니다.
이러한 방식의 선택을 MinMax게임.
한 국면 당 가능한 국면이 평균 30~40개 이상이고, 한 수를 내다볼 때마다 이 숫자만큼 곱해져
트리의 노드 수가 증가하므로, 40수씩 4수만 대나봐도 2560000이라는 수의 국면에 대해 평가해야 합니다.
이런 기본 아이디어가지고는 시간적으로나 메모리 사이즈적으로나 거의 불가능.
그래서 사실 알파베타 가지치기 같은 효율적인 탐색 방법이 알려져 있습니다.
여기선 재귀호출을 이용하면 훨씬 간단하게 프로그램을 만들 수 있습니다.
각 국면에서 다음 수를 내다보기 위해 해야 하는 동작이 항상 똑같기 때문.
함수를 이런 형태로 구성하여 계속 자기 자신을 호출하는 재귀호출 방식을 이용하면 쉬운 탐색이 가능.

동시에 불리는 함수의 최대 개수와 이 때 함수의 지역 변수 크기를 알면 최대로 필요한
스택 사이즈를 계산할 수 있을 것이다.
컴파일러에서는 알 방법이 없어 경험적이고 막연한 값으로 결정해야 합니다.
만일 코드 세그먼트,데이터세그먼트,스택만 있으면 코드세그먼트와 데이터세그먼트는 컴파일러가 쉽게
알 수 있으므로 나머지를 스택으로 사용할 수도 있을 것이다. 단순한 임베디드 시스템에서는 가능.
하지만, 복잡한 OS에서 돌아가는 프로그램은 힙(Heap)이라는 영역도 고려해야하고, 가상메모리라는 것을 통해
실제 시스템에 있는 물리메모리와는 다른 영역에서 프로그램이 실행되는 등 여러 다른 요인이 있어 힘들다.
특별히 옵션을 주지않는 이상 1MB정도 영역.
링커 옵션에서 /STACK을 통해 조절할 수 있지만 충분한 크기.

정리해보면 전역 변수들은 데이터 세그먼트에 맵핑되어 실행 이미지 안에 그 정보가 포함되는 반면,
함수 안에서 사용되는 지역변수들은 스택이라는 메모리 공간에 동적으로 할당됩니다.
전역 변수는 프로그램이 종료되지 않는 이상 같은 메모리 공간에 맵핑되어 있으므로, 직접 액세스가 가능.
지역변수는 ebp라는 레지스터를 매개로 지정됩니다.
ebp레지스터가 SP 스택포인터입니다.
프로그램이 수행되는 동안 스택에 동적으로 할당된 변수들은 프로그램이 작성되고 컴파일되는 시점에서는 
정확히 그 주소가 나올 수가 없습니다. 그때그떄 할당되는 것이므로.
하지만 함수 내의 변수들은 순서가 정해져 있으므로 변수가 맵핑된 시작 주소만 알면 상대적인 순서로 계산가능.
그 시작 주소가 SP가 가리키는 주소.
80x86 CPU에서는 ebp라는 레지스터를 스택포인터로 삼았고 이 값을 기준으로 지역변수들이 순서대로 맵핑되는 것.
ebp-4, ebp-8, ebp-12 ...
int변수는 4바이트의 크기이므로 간격이 4바이트.
스택포인터를 기준으로 주소가 음의 방향으로 증가합니다.
윈도우즈를 만든 사람이 스택을 하위주소(큰주소값)에서 상위주소(작은주소값)로 증가되도록 만들었기 때문.

폰노이만 vs 하버드 아키텍처
하나의 메모리가 아닌 물리적으로 메모리를 다르게 할당하면 어떨까 -> 하버드 아키텍처

03 힙 세그먼트
코드는 코드가 있는 메모리, 데이터 메모리는 프로그램이 수행되는 동안 사라지지 않는 전역변수를 위한 공간,
스택 세그먼트는 함수 호출 등을 할 때마다 지역변수를 위해 동적으로 할당하는 메모리였습니다.
전역 변수들은 프로그램의 수행 라이프 사이클동안 항상 유지되므로 그 주소가 일정하게 고정,
스택은 주소를 고정할 수 없고, SP레지스터를 사용해 상대적인 거리를 이용해 변수를 액세스 했다.
결론적으로 전역 변수는 컴파일 시점에서 결정되는 정적 메모리, 스택은 실행하는 동안 결정되는 동적메모리.
만약 OS가 없는 임베디드 시스템에서 간단한 프로그램을 만든다면 굳이 세그먼트를 만들 필요가 없다.
도스 시절에는 com이라는 실행파일이 있어 명시적으로 데이터 세그먼트나 코드 세그먼트 구분없이 작성되는
실행파일로 주로 어셈블리로 가볍고 빠른, 시스템 접근이 용이한 형태의 실행 파일을 만드는 데 이용함.
C언어에서 프로그램을 만들면 컴파일러가 자동으로 세그맨테이션함.

어떠한 프로그램을 작성하기 위해선 그 프로그램의 특성에 대해 분석하는 작업이 필요합니다.
워드 프로세서의 가장 기본이 글자를 입력해 문장을 만들고 또 편집하는 기능.
편집 기능을 위해 글자 하나를 나타내는 구조체가 필요합니다.
typedef struct {
	char character; //글자
	int LineNo; //몇 번째 줄?
	int ColNo; //몇 번째 칸?
} OneCharacter;
편집하려면 커서를 표시해야 하고 커서가 옮겨다니거나 추가하는 등의 편집하려면 각 글자마다 위치정보가 필요.
지역변수로 선언하면 다른 함수에서 액세스할 수 없으므로 일단 전역변수로 선언.
1)키보드로부터 글자를 입력 받고
2)입력된 키에 따라 글자를 추가하거나 삭제하며 라인을 정렬하고
3)정렬된 글자를 화면에 출력
프로그램이 종료될 때까지 무한히 반복해야 함.
OneCharacter g_chars[1000];
int g_nCursorPos = 0; //커서가 위치할 인덱스
int main() {
	while(bQuit == false) {
		//키보드 입력을 처리한다.
		inputChar = ProcessKeyboardInput();
		//입력된 키에 따라 새롭게 라인과 글자들을 정렬한다.
		Alignment(inputChar);
		//정렬된 라인에 따라 글자를 화면에 출력한다.
		Draw();
	}
	return 0;
}
ProcessKeyboardInput은 키보드로부터 입력을 받는 부분으로 getch같은 함수를 써서 처리하던가
OS가 없는 시스템이라면 직접 키보드에서 데이터 값을 스캔해서 가져와야 합니다.
Alignment함수에서는 입력받은 키 값에 따라, 글자라면 추가시키고 화살표키라면 커서이동 하는 등의 작업.
Draw함수에서는 현재 화면에 보여야 할 부분이 몇페이지인가를 고려해 적절히 글자나 커서 등을 화면에.
추가되거나 삭제된 글자들은 메모리에 어떤 형태로든 저장되어야 합니다.
이 글자를 저장할 변수가 g_chars.
글자가 입력되면 현재 커서가 가리키는 위치에 글자를 추가해야 하는데 커서 변수가 g_nCursorPos.
최초에 프로그램이 시작되면 g_nCursorPos는 0으로 초기화되고 입력받으면 g_chars[0]에 글자가 저장.
그리고 g_nCursorPos는 증가되어 1이 될 것.
배열 크기를 늘리는 것에는 한계가 있다.
그리고 중간에 있는 값을 삭제 후 타입하면 덮어쓰기가 될 것입니다.
그렇다고 뒤로 복사하면 프로그램이 너무 느려짐.

문제의 근본 원인은 g_chars가 데이터 세그먼트에 정적으로 할당되어 있는 것.
컴퓨터의 메모리를 원하는 곳에서 원하는 만큼 마음대로 할 수 있다면 문제는 해결될 것.
힙은 프로그램이 실행되면서 필요할 때마다 동적으로 메모리를 할당할 수 있는 공간.
스택도 사실 함수 하나로 국한한다면 지역변수도 이미 결정나는 정적 변수의 하나이다.
main역시 다른 함수와 같고 호출할 수도 있다.
그렇기 때문에 프로그램 전체에서 보더라도 main함수의 지역변수는 정적인 변수일 뿐.
프로그램 전체 관점에서 본다면야 각 함수의 지역 변수들이 동적으로 할당되는 것이지만,
함수 내부에서는 여전히 변수를 동적으로 할당할 수 없다는 것.
ebp레지스터는 함수가 호출되면 한번 값이 설정되고 리턴하기 전까지는 바뀌지 않습니다.
함수 내부에서는 ebp레지스터 값이 바뀌지 않으므로 각 변수의 상대적인 오프셋 값들이 마치 전역 변수의
절대 주소와 같은 역할을 합니다.
SP는 다음 함수 호출을 대비해 항상 스택이 증가하는 방향의 끝 부분을 가리킵니다.
ebp는 모든 지역 변수를 고려한 스택 제일 마지막을 가리키고, 각 변수의 오프셋이 모두 마이너스가 되는 것.
이런 상황에서 중간에 변수가 필요해 메모리를 스택에 할당하면 할당된 만큼 SP도 증가.
이미 결정난 지역 변수들을 기존과 같은 오프셋 값으로 액세스하면 엉뚱한 메모리를 건드리는 결과.
|C|\_ebp-12 동적으로 할당 |C|
|B|\_ebp-8      --->     |B|\_ebp-12
|A|\_ebp-4               |A|\_ebp-8
| |\_ebp                 |*|\_ebp-4
                            \_ebp
스택에 동적할당을 하고 나면 ebp를 그만큼 증가시켜야 하는데 기존의 지역변수를 액세스하면 다른 곳 액세스.

힘을 관리하는 법은 OS나 컴파일러 등에 따라서 얼마든지 바뀔 수는 있다.
우선 메모리상에 힙으로 사용될 공간을 확보합니다. 힙 세그먼트(Heap Segment) 혹은 힙.
힙은 한 프로그램당 하나만 있을 수 있고, 시스템에 따라서는 여러 개의 힙 공간도 있을 수 있다.
대부분의 경우는 디폴트로 하나의 힙만으로 작업.
마련된 힙 공간에서 프로그램에서 필요한 시점에 메모리를 할당하도록 적절한 함수를 불러주어야 한다.
malloc같은 함수가 불리면 내부에서는 우선 해당 힙 공간을 들여다 봅니다.
앞에서 이미 사용되고 남은 힙 공간 중에 malloc함수를 부를 때 인자로 넘어오는 크기만큼 
연속된 공간이 존재하는지 탐색합니다.
그리고 발견되면 이 공간의 시작주소를 리턴하는 것.
리턴된 주소를 포인터로 선언된 변수에 저장하고 그 뒤에 유용하게 사용하는 것.
만일 프로그램이 처음 시작된 상태라면 힘 공간은 전부 비어 있을 것이고 차례대로 메워져 내려갈 것.
힙의 가장 큰 특징은 동적인 할당입니다. 
프로그램을 작성하는 시점이 아니라 실행되는 동안 입력이나 조건에 의해 동적으로 메모리가 할당되는 것.
사실 이러면 데이터 세그먼트에 맵핑해 두는 전역변수와 같아보이지만 메모리의 동적인 해제도 가능하다.
한번 할당된 메모리가 사용이 끝나면 다시 해제되어 힙의 빈공간이 되는 것.
워드프로세서에서 계속 글자를 입력할 때마다 글자에 해당하는 메모리 공간을 할당해 나가면 글자가 늘어날수록
힙의 크기도 늘어나게 될 것이다.
그리고 지우는 경우에는 메모리 공간을 해제하여 공간을 마련해야 한다.
따라서 동적할당된 힙을 다시 동적으로 해제하는 것 역시 중요한 작업.
C에서는 free라는 함수가 있습니다.
free함수는 동적으로 할당된 메모리의 시작주소를 넘겨 받아 그 공간을 다시 빈 공간으로 표시.

malloc함수가 리턴하는 메모리 공간의 시작 주소를 가지고 사용하고, 메모리 사용이 끝나면 free 함수에 다시
이 시작 주소를 넘겨주기만 하면 알아서 할당된 크기만큼 해제가 됩니다.
주소만으로 free하는 것은 이는 어딘가에 할당된 메모리의 정보가 저장되고 있다는 의미.
실제로 플랫폼이나 컴파일러 OS 등 여러 환경에 따라 서로 다른 형태로 관리됩니다.
대표적인 형태가 할당된 메모리자체에 필요한 정보를 보관하는 방법.
malloc(100)을 하면 실제로는 100바이트보다 좀 더 큰 공간을 찾습니다.
확보된 공간의 가장 첫 부분에 할당된 메모리의 관리에 필요한 모든 정보를 저장. 메모리 헤더(Memory Header)
그리고 실제론 이 헤더 바로 다음 주소를 리턴하는 것.
그러므로 malloc이 확보하는 공간은 요청한 공간에 헤더 정보를 더한 만큼.

필요한 정보 중 가장 기본이 되는 정보는 할당된 블록의 크기.
나중에 빈 공간을 계산할 수 있고, 애플리케이션도 이 정보를 활용할 수 있다.
할당받은 블록 크기가 얼마인지를 알아내느 함수도 존재.
빈 공간을 찾기 위해선 힙 세그먼트의 시작 주소를 알고 있어야 합니다.
보통 하나의 기본 힙을 가지고 시작주소는 프로그램 내부에 저장합니다.
빈 공간 탐색은 이 힙의 시작주소를 살펴봄으로 시작됩니다.
시작 주소에는 항상 헤더가 존재해야 합니다.
그 헤더에는 다음 할당된 공간의 헤더 주소가 기록되어 있습니다.
그러면 malloc은 다음 할당된 주소까지의 공간에 자신의 할당된 크기를 뺀 값(빈공간크기)을 할당하려는 크기와 비교.
충분히 공간이 확보가 되면 빈 공간에 새로 헤더를 작성하고 주소를 리턴합니다.
공간이 모자라면, 다음 헤더 안에 적혀 있는 그 다음 할당된 공간의 주소를 찾습니다.
결국 헤더 안에는 다음 헤더를 가리키는 포인터가 있어야하고 포인터를 따라가면 전체 할당된 블록을 다 탐색 가능.
중간에 메모리가 해제된다면 단순히 해제될 메모리 바로 전 헤더의 포인터를 수정해주는 것만으로도 가능.
메모리를 할당하는 작어버도 새로 할당된 메모리의 헤더 정보를 기록하고 바로 앞에 할당된 메모리 헤더의
포인터를 새로 할당된 헤더를 가리키도록 조정해 주는 작업이 필요하다.
새로 할당된 헤더의 포인터는 다음 할당 공간의 헤더를 가리키도록 설정해야 한다.
이런 자료구조는 서로 연결되어 있다하여 링크드 리스트(Linked List)라 불립니다.
실제로는 앞뒤로 탐색가능하도록 이전헤더도 가리켜 양방향 링크드 리스트(Double Linked List) 형태.

워드프로세서에서 구조체형태로 배열을 만들었는데 정적인 변수 였다. 그리고 비효율적이었다.
배열 대신 힙을 사용하여 글자가 입력될 때마다 메모리를 할당하고 지워지면 해제하면 좋겠지만
새로운 메모리가 할당될 때마다 어떻게 관리할까가 문제.
Draw함수로 모든 글자에 대해 루프를 돌려면 모든 할당된 메모리에 대한 포인터를 가지고 있어야 하는데,
이 포인터 역시 변수이므로 글자 개수에 따라 가변합니다.
생각할 수 있는 방법은 링크드 리스트(Linked List).
typedef struct {
	char character; //글자
	int LineNo; //몇 번째 줄?
	int ColNo; //몇 번째 칸?
	
	OneCharacter* pNext; //다음 글자에 대한 포인터
} OneCharacter;
이 구조체변수는 하나의 글자를 나타내고 다음 글자에 대한 포인터를 가지도록 포인터를 추가했다.
메인 프로그램은 가장 첫 번째 글자에 대한 포인터만 있으면 pNext를 차례대로 따라가면 마지막까지 탐색 가능.
마지막 글자에서 다음 글자가 없으므로 pNext는 NULL;
링크드리스트 형태로 글자를 관리하면 중간에 글자가 삽입이나 제거되도 포인터만 수정해주면 됩니다.
그래서 이 수정은 글자가 얼마나 많이 있던 상관없이 항상 일정.
시작 포인터만 알고 있으면 모든 글자도 탐색 가능.
그래서 링크드 리스트같은 자료구조는 힙과 찰떡 궁합.

동적 메모리 할당 함수
C++에선 new라는 연산자가 malloc과 같이 동적으로 메모리를 할당.
윈도우즈 프로그래밍에는 GlobalAlloc이나 HeapAlloc도 있다. 동적으로 메모리를 할당하는 API.
일단 HeapAlloc,new,malloc같은 함수들은 사실 같은 함수라고 볼 수 있다.
new나 malloc은 C++에서 완전히 동일하게 사용하는데 상위 수준 힙 할당 함수입니다. 일반애플리케이션 프로그래머들.
new나 malloc함수와 HeapAlloc의 차이는 어느 힙을 사용하는가에서 기인.
HeapAlloc은 Heap핸들이 인자로 넘어가는데, malloc같은 함수는 핸들 인자가 없습니다.
즉, malloc이나 new는 어딘가 미리 정해진 힙 공간에서 메모리를 할당하지만 HeapAlloc은 힙공간을 지정할 수 있다.
힙 공간은 HeapCreate라는 API를 통해 새로 만들 수도 있고 기본적으로 윈도우즈 프로그램 실행하면서
하나의 힙 공간을 할당받기도 합니다.
반면 C,C++라이브러리 함수인 malloc이나 new는 자체적으로 생성한 힙 공간을 활용.
힙 관련 할당 함수들은 단편화(Fragmentation)이라는 문제가 있다.
메모리의 할당과 해제를 반복하면 듬성듬성 빈공간이 발생하는 것을 단편화라고 함.
단편화 현상이 심해지면 연속된 공간의 크기가 줄어들어 점점 큰 메모리 할당이 힘들어집니다.
매번 메모리를 할당할 때마다 단편화된 많은 수의 공간을 뒤져야 하므로 할당 속도도 떨어짐.
이런 문제를 해결하기 위한 함수들이 GlobalAlloc이나 LocalAlloc이라는 API.
HeapAlloc과는 달리 프로그램이 실행되면서 할당받는 기본힘에서만 메모리 할당을 하는데 new와 malloc과 비슷.
결정적인 차이는 바로 이 API들은 단편화 문제를 해결할 수 있다는 것.
HeapAlloc은 포인터를 리턴하는 반면 GlobalAlloc이나 LocalAlloc은 핸들을 리턴.
HeapAlloc은 이미 고정된 메모리 주소인 반면 GlobalAlloc같은 함수는 일단 OS의 관리를 한번 받습니다.
GlobalAlloc에서 할당받은 핸들은 그 자체로는 사용할 수 없고, GlobalLock같은 함수를 사용해 메모리를 고정해야함.
그렇지 않으면 OS에서는 단편화를 방지하기 위해 할당된 메모리 블록들을 이리저리 옮기기 때문.
따라서 GlobalAlloc이 곧바로 고정된 메모리 주소값을 리턴하면 OS가 단편화 작업을 하고 나선
엉뚱한 곳을 가리키고 있는 셈.
그러므로 메모리를 실제로 사용할 때만 GlobalLock함수로 OS가 이런 단편화를 못하도록 막고 작업하고
사용이 끝나면 GlobalUnlock함수를 불러 다시 OS가 단편화 작업을 할 수 있게 하는 것.
LocalAlloc은 예전 16비트 환경과의 호환을 위해 남아 있는 API로 GlobalAlloc과 동일.

VirtualAlloc
실제 윈도우즈에서 돌아가는 각 프로그램은 모두 실제 램보다 많은 양의 메모리를 할당받습니다.(4GB라고하자)
가상 메모리라는 개념을 통해서 이루어지는데, 프로그램이 사용하는 4GB메모리는 실제 메모리가 아니라,
중간에 OS가 적절히 이 메모리를 하드 디스크나 실제 메모리로 맵핑해가면서 눈속임하는 것.
아무리 프로그램마다 4GB공간이 주어져도 최대치를 얘기하는 거지 항상 다쓰는 건 아니다.
필요할 때마다 메모리 할당 함수들을 사용해서 적절한 양만큼 할당하는 것이 일반적.
그런 용도로 힙이라는 메모리 공간을 확보하고 그 힙 공간 안에 적절히 메모리를 할당해 주는 것.
힙 공간 자체가 크지 않고 단편화 문제까지 겹쳐 큰 용량의 메모리 할당이 힘들다.
힙은 앞으로 할당받을 메모리지만 OS입장에서는 이미 그 공간만큼 확보되어 있어야 하는 메모리.
힙공간이 너무 크면 OS가 실제 메모리랑 하드디스크를 오가면 눈속임하는데 부담이 커짐.
그래서 힙 공간은 일반적으로 수MB정도, 기본적으로 할당하는 힙공간은 1MB. 링크옵션으로 변경가능.
여전히 4GB메모리 공간이 주어져 있고 VirtualAlloc을 사용한다.
VirtualAlloc은 특정 힙에서 메모리를 할당받는 것이 아니라, 4GB가상 메모리 중에서 확보합니다.
일반적으로 가상메모리는 OS의 관리하에 있게 됩니다.
오랜 시간 사용이 없는 부분은 하드디스크로 들어가고(스와핑) 다시 사용되면 메모리로 로드.
만일 커다란 크기의 메모리를 애플리케이션에 요청해 확보하고 있으면 스와핑이 빈번하게 일어나
전체적인 시스템 속도가 무척 느려질 수 있습니다.
이런 책임을 프로그래머에게 넘기고자 만들어진 함수가 VirtualAlloc.
VirtualAlloc을 호출하면 실제 메모리 상에 공간을 확보하지는 않습니다.
대신 논리적으로 해당 크기만큼 주소 공간을 예약(확보)합니다.
다른 곳에서 메모리를 할당받아서 예약된 주소 공간은 이미 사용된 것으로 간주해, 피하는 것입니다.
예약된 메모리를 이후 실제로 액세스하게 될 때에는 다시 VirtualAlloc을 호출하여 Commit이라는 동작.
Commit은 예약한 메모리 영역 중 액세스하고자 하는 크기만큼을 실제 메모리상에 확보하라는 뜻.
그리고 사용이 끝난 메모리는 다시 Decommit으로 해지한 후 다른 곳에서 사용할 수 있습니다.
이 방식은 논리적으로 큰 메모리가 필요하지만 실제 액세스는 좁은 영역에서 일어나는 경우 유용.
예로 액셀 프로그램은 논리적으로는 무한대의 행과 열을 지니므로 매우 큰 메모리 공간이 필요하지만
실제 액세스하는 영역은 아주 일부에 국한.
따라서 이런 경우 큰 메모리 영역을 VirtualAlloc으로 예약만하고 실제 액세스되는 행과 열에 해당하는
메모리 영역만 Commit하여 사용하면 효율적으로 메모리를 활용할 수 있습니다.
OS가 획일된 정책(사용 빈도)로 스와핑하는 것보다 효율이 높습니다.

결론적으로 메모리 할당 함수들은 계층 구조로 되어 있습니다.
하위 계층의 저수준 함수가 VirtualAlloc이고 VirtualAlloc함수를 이용해 HeapAlloc같은 함수가 구현되고,
애플리케이션에 가장 가까운 상위 계층에 new나 malloc같은 함수가 있는 것.
정말 대용량의 메모리를 다루는 서버나 이미지프로세싱, 가상 메모리와 물리메모리를 같이 활용하는
드라이버 개발자가 아니라면 new, malloc으로 충분하고 플랫폼 호환을 위해서도 좋다.

*/