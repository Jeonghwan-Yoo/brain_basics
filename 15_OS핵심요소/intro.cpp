/*
프로세스와 스레드의 차이점은 무엇일까요?
프로세스란 프로그램이 실행되기 위해 필요한 자원 소유의 단위.
프로그램이 실행되기 위해선 메모리나 프로그램 이미지, I/O핸들 등 여러 요소가 있다.
자원이 소속되는 단위가 바로 프로세스.
스레드란 프로세스의 코드를 수행하는 단위를 일컫습니다.
CPU는 문맥 전환이 일어나는 단위로도 볼 수 있다.
현대 OS에서는 프로세스당 복수개의 스레드를 허용함으로써 분리된 개념.
스레드를 프로세스에 속하는 자원의 일종으로 생각할 수 있다.

Blocked I/O와 Non-Blocked I/O의 차이점은 무엇일까요?
Blocked I/O는 I/O 작업이 끝나는 동안 CPU 대기 상태에 머무르는 I/O작업을 일컫습니다.
예를 들어 파일을 오픈하고 ReadFile함수를 호출하였을 때 이 함수가 원하는 데이터를 다 읽을 때까지 리턴하지 않는다면
Blocked I/O함수라 할 수 있다.
Non-Blocked I/O는 I/O 작업이 완료되기 전에 바로 리턴하고 CPU가 다른 일을 할 수 있게 되는 경우.
실제 I/O작업의 완료는 인터럽트 형태로 전달되며 프로그램상에서는 콜백 함수나 이벤트 객체의 시그널링(신호) 형태.

01 프로세서 vs 스레드
현대적인 OS의 가장 필수적인 요소 중 하나가 멀티태스킹(Multi Tasking)의 지원.
하나의 CPU상에서 동시에 여러 개의 프로그램이 실행되는 기술.
하지만 사용자가 느끼기에 '동시'인 것이고 엄밀하게는 매우 빠르게 여러 프로그램이 조금씩 실행되도록 OS가
실행 전환(문맥전환, Context Switching) 해주는 것.
하지만 일반적인 응용 프로그램 개발자 입장에선 다른 프로그램과 상관없이 하나의 프로그램만 실행되는 환경과 동일.
OS는 멀티태스킹을 구현하기 위해 단순히 수행 코드만 전환하는 것이 아니라 여러 다른 인프라를 구현.
이런 인프라를 통해 개발자는 다른 프로그램에 대해 고려하지 않고 독립적으로 돌아가는 프로그램을 개발하는 것 같은
환경을 제공받는다.
가장 대표적인 요소가 프로세스(Process)입니다.
프로세스는 윈도우즈에서 실행 중인 파워포인터 같은 개개의 프로그램을 일컫습니다..
프로세스가 하드디스크상에 있는 이러한 프로그램 이미지가 아니라 '실행 중'인 프로그램을 일컫는 것.
프로세스는 하나의 프로그램이 실행되는 단위로 생각할 수 있습니다.
하나의 프로그램이 돌아가기 위해선 여러 가지 요소가 필요합니다.
우선 실행되고자 하는 프로그램의 코드와 데이터가 있는 이미지가 있어야 합니다.
이 이미지는 보조기억장치에 있는데, 프로그램이 실행되기 위해선 메모리로 로드되어야 합니다.
만일 똑같은 파워포인트 이미지를 두 번 실행하면, 하드디스크 상에 있는 파워포인트라는 이미지는 하나뿐이지만,
실제 메모리상에는 두 개의 파워 포인트 이미지가 로드되어 있고, 각각의 이미지는 독립적으로 다른 내용을 작성.
즉, 파워포인트라는 이미지로부터 두 개의 독립적인 프로세스가 생성된 것.
각각의 프로세스는 비록 같은 이미지에서 실행되었다고 하더라도, 서로 독립적인 로드 과정을 거쳐서 메모리에
적재되고 또 서로 다른 메모리 공간에 배치되어 독립적으로 자신만의 메모리를 할당받아 사용합니다.
프로세스란 프로그램이 수행되기 위한 자원(Resource) 소유의 단위로 생각할 수 있습니다.
자원이라 부를 수 있는 가장 큰 요소는 메모리.
각 프로세스는 하나의 독립된 프로그램으로서 동작하기 위해 자신만의 메모리를 확보합니다.
이 외에도 프로그램이 수행되면서 필요로 하는 자원은 여러 가지가 있습니다.
제한된 하드웨어를 다수의 프로그램(프로세스)이 동시에 사용하기 위해서는 각 프로그램이 임의로 하드웨어를
제어하는 것이 아니라, OS한테 제어를 요청하고 OS가 일괄적으로 묶어서 이를 처리해줍니다.
OS는 대기 번호표같은 핸들이라는 고유 값을 프로그램에게 넘겨주게 됩니다.
가령 프로그램이 어떤 파일을 열거나, 네트워크 장치를 사용하고자 요청하면 OS는 특정 번호표 같은 핸들 값을 넘겨줍니다.
그리고 해당파일이나 장치에 데이터를 쓰거나 읽거나 할 때도 항상 해당 핸들을 가지고 OS에 요청해야 됩니다.
핸들 값도 결국 프로그램(프로세스)마다 할당되는 것으로 해당 프로그램이 종료되면 같이 폐기처분됩니다.
즉, 하나의 프로세스에 할당된 자원인 것.
프로세스의 중요한 요소는 실행(Dispatching) 단위라는 점.
프로세스는 메모리상에서 CPU에 의해 수행되고 있는 프로그램.
프로세스는 메모리와 같은 자원을 독립적으로 소유하고 실행되기 위해서는 CPU를 사용할 권한을 얻어야 합니다.
프로그램 수가 늘어날수록 그 수에 비례해서 CPU 수행 시간이 공평하게 분배될 것입니다.
결국 하나의 수행되는 프로그램이 프로세스이므로 프로세스는 이러한 CPU 수행시간을 분배받는 단위인 것.
CPU가 모든 프로세스를 순회하면 차례대로 실행합니다.

일반적으로 과거에는 하나의 프로세스는 하나의 실행 단위로 생각되던 것이 효율성의 문제로 인해 프로세스와
실행 단위를 구별해서 생각하게 된 것.
일반적인 응용 프로그램에서는 대부분 하나의 수행 단위로도 프로그램을 만들 수 있습니다.
간혹 논리적으로 두 개의 수행단위가 편한 경우가 발생하거나 네트워크 서버처럼 많은 수의 IO처리를 해야하는 경우
서버 프로그램 자체는 하나의 프로세스지만 CPU로부터 여러 개의 수행 단위를 얻어 작업하는 것이 효율적.
워드 프로세서 프로그램에서 타이핑을 하면 자동으로 맞춤법 검사를 합니다.
이런 경우 워드 프로세서라는 하나의 프로세서 안에 사용자의 타이핑을 대기하고 화면에 글자를 뿌리는 등의
루틴과는 별도로 다른 수행 단위를 만들어 타이핑되어 있는 글자들을 항상 모니터링 하는 것.
만약 다른 프로세서로 만들면 루틴이 별도의 프로세스가 되어버려 워드 프로세스에 할당된 메모리와는 다른 공간을
할당받고 별도의 독립적인 프로세스가 되므로 서로의 메모리 공간에 접근하기가 힘듭니다.
이런 경우는 하나의 프로세스로 동일한 자원 등을 사용하되 수행단위만 별도로 두는 경우가 편리.
그래서 프로세스에서 수행단위를 분리하여 스레드(Thread)라는 개념을 도입.

스레드라는 개념이 도입되면서 프로세스는 더 이상 수행의 단위가 아닌 자원 소유의 단위로 바뀌게 됨.
대신 수행단위인 CPU시간을 할애받는 것도 하나의 자원으로 인식되어 스레드라는 이름으로 다른 여러 자원과
함께 프로세스에 종속된 형태가 되었습니다.
하나의 프로세스는 여러 개의 핸들을 가질 수 있듯이 여러 개의 스레드를 가질 수 있고 여러 개의 수행 단위를 갖게됨.
프로세스에서 실행단위라는 개념이 사라지면서 프로세스는 기본적으로 최소 하나의 스레드는 소유해야 합니다.
따라서 모든 프로세스는 생성될 때 기본적으로 하나의 기본 스레드가 함께 생성됩니다.
이 후 생성되는 스레드는 프로그램이 능동적으로 생성 여부를 결정하게 되는 것.
수행단위인 스레드 역시 하나의 자원으로서 프로세스에 종속된다.
메모리
프로세스1|파워포인트 스레드1|<-실행 |CPU|                    
	  	|       ...       |       
프로세스2|파워포인트 스레드1|<-실행 |CPU|              
		|       ...       |
프로세스3|   스타 스레드1   |<-실행 |CPU|
		|   스타 스레드2   |<-실행 |CPU|
		|       ...       |
프로세스4|      OS 코드    |<-실행 |CPU|
스타는 한 프로세스 안에 두 개의 스레드를 보유해 마치 두 개의 프로그램이 동시에 메모리를 공유하고 독립적으로
실행되는 것 같은 효과를 나타냄.

15_1.cpp
코드는 컴파일되고 나면, 실행 이미지인 exe파일이 하나 생성될 겁니다. 실행하면 탐색기 프로그램이 선택된 파일의
이름을 인자로 넘기면서 윈도우즈에서 제공하는 CreateProcess라는 API함수를 호출합니다.
OS는 응용 프로그램에게 시스템 함수라고 불리는 함수 라이브러리를 제공함으로써 응용 프로그램이 해당 OS
기반에서 돌아갈 수 있게 해줍니다.
CreateProcess라는 함수는 윈도우즈에서 제공하는 라이브러리로 Kernel32.lib라는 라이브러리 파일에 포함되어
있습니다. 실제로는 Kernel32.dll라고 하는 동적 링크 라이브러리 형태.
탐색기가 호출한 CreateProcess는 작성한 코드의 실행 파일 경로를 인자로 넘겨받고 해당 코드를 하드디스크에서
읽어 메모리로 로드합니다.
OS내부에서는 필요한 메모리뿐 아니라 실행할 프로그램에 필요한 여러 정보를 저장할 변수들을 준비합니다.
즉, 작성한 실행 파일 이미지로부터 새로운 '프로세스'가 생성되어 OS는 이를 위해 필요한 '자원'을 확보한 것.
OS도 프로그램이므로 내부적으로 해당 프로세스에 필요한 핸들엔트리, 코드, 메모리 등을 준비하는 것.
프로세스를 생성하면서 윈도우즈는 프로세스의 코드를 수행시키기 위한 자원 '스레드'를 생성합니다.
그리고 이 스레드 역시 하나의 프로세스 자원으로서 종속시킵니다.
정리해보면
탐색기 프로그램이 내부적으로 윈도우즈가 제공한 API함수인 CreateProcess호출
CreateProcess(...) {
	메모리 할당;
	핸들 엔트리 할당;
	실행 이미지 로드;
	스레드 생성;
}
생성된 스레드는 소속된 프로세스의 코드 수행을 시작하면서 프로그램 수행이 시작됨.

스레드는 결국 멀티태스킹 OS상에서 프로그램간의 실행 전환이 일어날 때 전환의 대상이 되는 주체.
하나의 프로그램은 인스트럭션이 연속적으로 실행되어 하나의 의미 있는 동작으 할 수 있게 문맥을 형성하는 상태.
하나의 인스트럭션이 글자 하나에 해당한다면 프로그램은 글자를 의미있게 나열한 문장이나 글.
사실 CPU는 한번에 하나의 인스트럭션 밖에 수행할 수 없습니다.
글자가 의미를 이루려면 순차적으로 읽으면서 앞에서 읽은 내용을 기억하고 있어야 합니다.
프로그램이란 앞의 수행 결과를 레지스터에 보관해가면서 순차적으로 수행되도록 나열된 인스트럭션.
하나의 프로세스 안에서도 여러 단위의 문맥이 존재해서 그 문맥들을 동시에 실행해 나갈 수 있는데,
이 문맥의 실행 단위를 스레드라고 부릅니다.
스레드가 의미 있는 글을 읽어나가는 단위이므로 한 스레드가 실행되는 동안은 연속적으로 인스트럭션이
실행되며 레지스터에 실행 결과가 축적될 것입니다.
중간에 다른 스레드로 문맥 전환이 일어나면 이 레지스터 값을 어딘가 저장해두고 새로 전환되는 문맥에서
축적된 레지스터 값을 복원해와야 할 것.
결국 CPU가 한 스레드의 코드를 일부 수행하고 잠시 후 다른 스레드의 코드를 수행하려고 할 때마다
CPU의 모든 레지스터 정보는 해당 스레드와 연계된 메모리상에 보관되어야 하고 다시 그 스레드가 실행될 때는
보관했던 레지스터 값으로 레지스터를 셋팅.
이런 동작은 LOAD, STORE로 수행하게 되는데 상당한 부담이 됩니다.
스레드간의 문맥 전환이 자주 일어나면 정작 필요한 코드를 수행하는 것보다 문맥 전환을 위해 레지스터 값을
저장하고 복원하는데 대부분의 CPU파워를 소비하게 됩니다.

탐색기가 CreateProcess라는 API함수를 통해 새로운 프로세스를 생성하고 윈도우즈는 CreateThread API함수를 제공.
탐색기가 CreateProcess를 불러 생성한 새로운 프로세스는 별도의 프로세스입니다. 서로 독립적으로 실행.
스레드는 분명 하나의 연속적이고 일관성있는 코드 덩어리를 실행하지만, 코드 덩어리가 하나의 프로세스가 아니어도 된다.
한 프로그램 안에서도 얼마든지 서로 독립적인 함수들이 존재하는데 스레드는 이런 독립적인 실행 주체를 생성하는 것.
따라서 생성된 스레드는 최초에 프로세스가 생성될 때 OS가 생성해서 main함수부터 실행해가는 메인 스레드와는
별도로 새로운 코드를 수행하지만, 메인 스레드와 동일한 프로세스 안에 존재하기 때문에, 두 스레드는 같은 자원을 사용.
또한 두 스레드가 같은 코드를 실행할 수도 있는데 메인 스레드보다 늦게 시작해도 새로 생성한 스레드가 main함수부터
시작하도록 지정할 수도 있습니다.

15_2.cpp
CreateThread라는 스레드 생성 API함수가 호출되고 있다.
CreateThread API는 새로운 스레드를 생성하는데, 새로운 스레드가 실행할 코드의 주소를 반드시 넘겨야 한다.
NewThread가 그 주소이고 나머지 인자들은 우선순위나 속성 등 다른 필요한 정보들.
NewThread라는 함수 주소를 넘겨줌으로써 새로 생성된 스레드는 메인 스레드와는 별개로 NewThread함수를 수행합니다.
프로그램이 실행되면(프로세스) OS가 새로운 스레드를 만들고, 스레드의 수행 코드 주소를 main으로 주는 것과 마찬가지.
(실제로는 main이 아니라 다른 곳에서 시작해서 이후 main함수를 호출하는 것)
main함수가 리턴하면 메인 스레드가 종료되고 프로세스도 종료되듯 새로 생성된 스레드 역시 지정받은 함수가
리턴하면 자동적으로 종료되는 것.
하지만 main과 NewThread 모두 무한루프여서 강제 종료를 하지 않는 이상 두 스레드는 모두 무한히 존재.
새로 생성된 스레드가 없다면 1씩만 증가되는 g_idx변수값이 출력되야 하지만 NewThead코드를 메인 스레드와 별도로
수행하고 있으므로 g_idx는 main함수뿐아니라 NewThrad함수 내에서도 증가가 일어납니다.
printf로 출력은 main함수 내에서만 하고 있습니다.
main함수는 1씩 증가시켜 값을 출력하지만 새로 생성된 스레드가 g_idx값을 계속 증가시키기 때문.
즉, main함수 내에서 1증가하고 printf함수가 수행되어 출력하는 동안 NewThread는 수없이 g_idx값을 증가시키는 것.
컴파일해서 실행하면 하나의 프로세스가 생성되고 기본적으로 OS가 하나의 메인 스레드를 통해 main함수를 수행하지만
메인스레드가 코드를 수행하다가 CreateThread함수를 호출해 별도의 스레드를 생성합니다.
별도의 스레드는 CreateProcess로 다른 프로세스를 만들 때와는 다르게 같은 프로세스 내에서 수행되면서 자원공유.
작업관리자에서 열선택에 스레드 수를 체크해 스레드 수를 확인해볼 수도 있다.

좀 더 효율성 높은 프로그램을 작성하려다 보면 메인스레드 외에 별도의 스레드를 만들어 사용하고,
이렇게 복수의 스레드가 존재하게끔 프로그램을 작성하는 것을 '멀티스레딩(Multi Threading)'.
별도의 스레드 없이도 만들 수 있다면 그게 더 좋다.
스레드가 많아지고 스레드 간에 문맥 전환이 자주 일어나면 그만큼 CPU가 레지스터를 저장하고 복구하는데
시간을 허비하게 되므로 시스템 성능이 떨어질 수 밖에 없습니다.
특히 한 프로세스 안에서 두 개 이상의 스레드가 동작하게 될 경우 문제가 되는 것이 동기화(Synchronization).
프로세스가 다르면 사용하는 메모리 공간을 포함해 할당된 모든 자원이 달라집니다.
상호간에 같은 자원을 사용하지 않기 때문에 스레드가 달라져도 서로 문제 되지 않진 않습니다.
같은 프로세스 안에서 스레드가 두 개 이상이 되면 같은 메모리 공간 안에서 같은 변수를 사용할 수 있고,
모든 프로세스의 자원을 공유합니다.
각 스레드는 서로 독립적으로 실행하다 보니 서로 같은 자원이나 변수를 사용할 때 동기화 문제가 발생.
예제도 동기화 문제를 내포하고 있습니다.
메인 스레드의 의지와는 상관없이 별도의 스레드가 g_idx변수를 가지고 조작하니 메인스레드는 예측불가.
그래서 이런 경우 스레드간에는 g_idx변수를 놓고 서로 동기화하는 작업이 필요합니다.
동기화된 규칙을 만드는 것.
이런 작업을 하기 위해 윈도우즈에서는 동기화 객체라는 것이 있습니다.
동기화가 코드가 길어지고 프로그램이 복잡해짐에 따라 버그가 쉽게 발생.
따라서 단일 스레드로 프로그램을 작성하되 멀티스레딩이 꼭 필요한 경우 동기화 원칙을 유념하며 간결하게 작성.

02 동기화
멀티스레딩이란 하나의 프로세스에서 메인 스레드 하나 외에 다른 스레드를 만들어 복수의 스레드가 동시에
돌아가는 프로그램 기법.
CPU는 하나라도 동시에 여러 개의 코드가 수행될 수 있다는 것.
(실제론 단일 CPU에선 불가능. 인스트럭션단위까지 내려가면 결국 한 번에 한 인스트럭션이 수행되고 
논리적인 단위로만 마치 동시에 코드가 수행되는 것처럼 보임)
따라서 동시에 수행되는 코드들이 같이 변수를 액세스한다거나 했을 경우 발생할 수 있는 문제점을 방지해야 한다.
15_3
g_idx변수를 증가시키는 일은 NewThread에서만 하고, main스레드에서는 2를 곱한 값을 출력.
너무빨리 증가하고 빠르게 출력되는 것을 막기위해 Sleep API호출 코드를 추가했다.
Sleep함수는 인자로 전달받은 숫자 크기만큼 실행을 중지한다고 생각하면 된다. ms.
g_idx : 0 g_idx*2 = 2 이런식으로 들쑥날쑥하게 출력되는데 메인스레드와 NewThread가 독립적으로 실행되기 때문.
문제는 논리적인 동시의 단위가 실제로 CPU가 코드를 수행하는 단위인 인스트럭션과 다르다는 것.
g_idx++하는 코드를 어셈블리로 보면
mov ecx,dword ptr [_g_idx(00427c48)]
add ecx,1
mov dword ptr [_g_idx(00427c48)],ecx
반면 printf함수는 긴 인스트럭션으로 이루어져 있습니다.
printf함수가 두 번 수행되면서 그 사이에 g_idx값이 NewThread에 의해 바뀌고 만 것.
g_idx를 동시에 액세스해서 동기화가 이루어지지 않고 있다.
main         NewThread
|printf|     |g_idx++|
|      |     | Sleep |
|      |     |g_idx++| 
|      |     | Sleep |
|      |     |g_idx++|
|      |     | Sleep |
|printf|     |g_idx++|
|      |     | Sleep |
|      |     |g_idx++|
|      |     | Sleep |
|      |     |g_idx++|
|      |     | Sleep |
| Sleep|     |g_idx++|
...
실제로는 g_idx가 참조되는 동안에도 NewThread스레드는 계속 수행하면서 g_idx를 증가시키고 있는 것.
두번째 printf는 이미 앞에서 참조된 g_idx값이 아닌 것.
이런 경우가 동기화가 필요한 경우.
printf코드는 서로 다르지만 사실은 동일한 g_idx를 참조해야 하므로 논리적으로 한 단위로 이루어져 있어야 합니다.
따라서 두 번의 printf가 수행되는 동안에는 NewThread가 g_idx값을 변경하지 못하게 해야 합니다.
이를 위해 멀티태스킹 OS에서는 동기화 객체(Synchronization Object)를 제공.
대표적으로 크리티컬 섹션(Critical Section)이나 뮤텍스(Mutex) 등이 있는데 근본적으로 기능은 같다.
크리티컬 섹션은 크리티컬 섹션을 만들어 놓고 한 스레드가 이 섹션을 사용하고 있고(Lock) 다른 스레드가 다시
그 섹션을 사용하려고 하면 앞의 스레드가 사용을 마칠 때까지(Unlock) 기다리게 됩니다.
스레드가 대기모드로 전환되면서 더 이상 코드를 수행되지 않는 것(Blocking).
그리고 앞의 스레드가 Unlock하면 대기하고 있던 스레드가 해당 섹션을 Lock하게 되면서 수행이 계속되는 것.
스레드1                       스레드2
   |                            |1. 진입성공. 크리티컬 섹션 락.
   |2. 대기(락 실패.블로킹됨.)    |
   |   스레드 정지 후 대기상태    |
   |4. 크리티컬 섹션 락           |3. 사용완료. 크리티컬 섹션 언락
   |                             |
...
두 개의 스레드가 공용으로 사용하는 변수 등의 자원이 있을 경우, 프로그램상에서 공용의 크리티컬 섹션을 만듭니다.
각 스레드는 공용 자원을 사용하기 전에 반드시 크리티컬 섹션을 락하고 사용합니다.
그리고 자원의 사용이 끝난 시점에서 다시 언락을 해주면 됩니다.
이러면 공용 자원은 한 시점에 한 스레드에 의해서만 액세스가 가능.
15_4.cpp
공용변수인 g_idx를 보호하기 위해 크리티컬 섹션 객체 g_csFor_g_idx를 선언.
그리고 이를 사용하기 위해 최초에 한 번 초기화해야하는데 API함수가 InitializeCriticalSection.
제일 마지막에서 사용이 끝난 크리티컬 섹션을 삭제해주는 DeleteCriticalSection.
g_idx를 액세스하기 전에 EnterCriticalSection API로 락하게 됩니다.
끝난 시점에서는 다시 LeaveCriticalSection으로 언락해줍니다.
그러면 메인 스레드에서 printf를 부르기 전에 크리티컬 섹션을 락한다. 그래서 언락할 때까지 대기.
그래서 메인 스레드 내에서 두 번의 printf가 불리는 중간에 g_idx++코드가 수행되지 않습니다.
메인 스레드                         NewThread
|C/S락 실패|                         |C/S락 성공|
|  (대기)  |							 | g_idx++ |
|  (대기)  |	   <-----------------	 | C/S언락 |
|  printf  |  NewThread가 C/S를      |  Sleep  |
|          |  언락함에 따라 메인      |C/S락 실패|
|          |  스레드의 블로킹해제     | (대기)  |
|          |                         | (대기)  |
|          |                         | (대기)  |
|          |                         | (대기)  |
|  printf  |                         | (대기)  |
|          |                         | (대기)  |
|          |                         | (대기)  |
|          |  메인스레드가 C/S를      | (대기)  |
|          |  언락함에 따라 NewThread | (대기)  |
|          |  블래킹해제              | (대기)  |
| C/S 언락 |    ----------------->   | (대기)  |
|  Sleep   |                         |C/S락 성공|
|          |                         | g_idx++ |
...
g_idx부분이 서로 겹치지 않고 있다.

동기화 객체에는 크리티컬 섹션 외에도 뮤텍스(Mutex)나 세머포어(Semaphore) 등이 있다.
뮤텍스는 크리티컬 섹션과 거의 동일
(C/S는 같은 프로세스 안에서만 사용할 수 있지만 뮤텍스는 서로 다른 프로세스에 속한 스레드끼리 동기화할 때도 가능)
세모포어는 락을 한 번이 아니라 지정된 횟수만큼 여러 번에 걸쳐 할 수 있다는 차이.
원칙을 정리해보면
1)2개 이상의 복수의 스레드에서 함께 사용하는 자원마다 동기화 객체를 생성해 둔다.
2)각 공용 자원이 사용되는 논리적 단위마다 해당 동기화 객체로 묶는다.
예로 printf를 두번 호출하는 동안 g_idx가 변하면 안되기 때문에, 이 구간을 논리적 단위로 보고 전후로 락과 언락.
NewThread에서는 g_idx++가 논리적 단위이므로 전후로 동기화 객체의 락과 언락을 해준다.
3)가능한 동기화 객체로 보호되는 논리적 단위(임계 영역)를 작게 잡는다.
만약 Sleep까지 포함해 논리적단위로 잡으면 동작은 하지만 성능이 훨씬 떨어진다.
15_5.cpp

실제 멀티스레딩 환경이 되어야 할만큼 복잡한 환경에서는 논리적 단위를 어디까지 끊을 것인가는 어렵다.
아예 무식하게 공용자원을 사용하는 코드가 있는 함수 전체를 하나의 단위로 묶어 시작부터 끝까지 락/언락하면
편할지모르나 성능면에서는 상당한 손해를 보게 된다.
단 한 군데에서만 실수가 있어도 그 구간에서 얼마든지 공용자원을 액세스하므로 말짱 도루묵.

멀티스레딩으로 인해 발생하는 가장 골치 아픈 상황은 데드락(DeadLock). 교착상태.
꼭 멀티스레딩에 의해서만 아니라 여러 프로세스간에서도 발생할 수 있는 것이지만 대부분 멀티스레딩프로그램 개발에서.
프로세스간에 데드락이 발생하는 경우는 대부분 OS로서도 대책이없어 컴퓨터 재부팅해야 한다.
하지만 멀티스레딩 프로그램에서 발생하는 데드락은 대부분 프로그램을 수정해서 해결가능.
데드락의 필수조건은 '두 스레드가 각각 서로 다른 자원을 하나씩 소유한 채 서로 쌍방이 소유한 자원을 요청
하고 기다리는 것'
물론 여러 개의 스레드 간에도 일어날 수 있고, 각각의 스레드가 하나씩의 자원을 소유한 채 서로 다른
스레드가 소유한 자원을 요청하고 이 관계가 순환관계가 되면 데드락이 발생합니다.
스레드1(A자원소유) -> 스레드2(B자원소유) -> 스레드3(C자원소유) -> 스레드1(A자원소유)
          B자원 요청. 블로킹    C자원 요청. 블로킹    A자원 요청. 블로킹
자원을 소유한 채 서로 소유한 자원을 요청하고 순환 관계가 되는 경우 데드락이 발생.
15_6.cpp
변수를 증가시키는 부분이랑 출력하는 부분을 각각 하나의 논리적 단위로 묶어 크리티컬 섹션으로 보호하고 있기
때문에 A와 B는 항상 같은 숫자가 나올 것.
그런데 결과가 나오다가 프로그램이 멈출 것이다. 교착상태.
메인 스레드             NewThread
    |                      |
	|                    g_csA락 성공
  g_csB락 성공              |
    |                    g_csB락 실패
  g_csA락 실패              |
NewThread에서 이미     메인 스레드가 이미
g_csA를 락한 상태여서   g_csB를 락한 상태여서
블로킹되어 대기모드     블로킹되어 대기모드
=>두 스레드 모두 상대방이 락한 변수를 요청하며 대기하여 더이상 프로그램이 진전되지못하고 데드락상태.
main스레드에서 두 크리티컬 섹션을 락하는 순서가 g_csB,g_csA순입니다.
NewThread스레드에선 g_csA, g_csB로 메인 스레드와 반대로 락을 시도하고 있습니다.
메인 스레드와 NewThread에서 각각 g_csB와 g_csA를 성공적으로 락하게 됩니다.
NewThread쪽에서 g_csB를 락하려하지만 메인 스레드에 의해 락된 상태이므로 실패하고 NewThread함수는 블로킹.
메인 스레드 역시 g_csB를 성공적으로 락한 후에 g_csA의 락을 시도할 때 실패.
만약 이 상태에서 어느 한쪽이 자기가 락한 CS를 언락해준다면 아무문제 없이 프로그램은 재개되겠지만
서로간에 하나씩 자원을 락한 상태로 상대방의 자원을 대기하므로 누군가 강제적으로 어느 한쪽의 CS를
언락해주지 않는 이상 해결될 수 없습니다.
이런 데드락은 멀티스레딩 환경이 아니라, 프로세스간에서도 발생할 수 있습니다.
프로세스들은 변수의 공유보다는 IO장치 등을 놓고 경쟁을 벌일 수 있는데 데드락 상황이 발생.
프로세스 간의 데드락은 일반적으로 해결 방법이 없습니다.
각 프로세스들은 정말 서로 완벽히 독립적으로 움직이기 때문에 프로토콜을 만들어 조정하기도 힘듬.
만든 프로그램인 경우 얼마든지 조정해서 데드락을 예방할 수 있다.
두 변수의 CS를 락하는 순서를 동일하게 잡음으로써 데드락을 예방할 수 있었습니다.
메인 스레드             NewThread
	|                      |
	|                    g_csB락 성공
  g_csB락 실패              |
	|                    g_csA락 성공
  g_csB기다림(대기)         |
    |                    g_csB언락
  g_csB락 성공(스레드재개)   |
    |                      |
  g_csA락 실패              |
    |                      |
  g_csA기다림(대기)       g_csA언락
    |                      |
  g_csA락 성공(스레드재개)   |

데드락 조건이 만족하기 위해서는 서로 다른 자원을 우선 소유, CS을 락해서 성공해야 하는데 동일한 순서로 자원을
요청하면 결코 각 스레드가 다른 자원을 소유한 상태가 될 수 없습니다.
하지만 이는 직접 자원을 요청하는 순서를 조정할 수 있는 경우지만 서로 다른 프로그램, 다른 프로세스끼리는 불가능.
프로세스끼리는 완전히 독립적인 프로그램이고 언제 어떤 자원을 소유하고 요청하게 될 지 예측불가.
멀티스레딩이 가장 유용하게 쓰이는 것이 바로 I/O처리를 할 때

03 Blocked I/O vs Non-blocked I/O
I/O라는 것은 Input/Output의 약자이고 입력과 출력을 의미하는데 컴퓨터의 가장 큰 요소 두 가지 중 하나.
CPU의 본질적인 특징은 Calculation 및 Control를 할 수 있다는 것.
그런데 CPU가 아무리 뛰어나도 대상이 되는 입력값(Input)이 없으면 능력을 활용할 수 없습니다.
또한 보여주든 보내주는 출력 기능(Output)이 없어도 아무 쓸모가 없습니다.
어떤 CPU라도 입출력 기능은 반드시 가지고 있는데 가장 기본적인 입출력이 메모리.
CPU는 기본적으로 메모리에서 인스트럭션을 읽어와서 수행하고 그 결과를 다시 메모리에 저장합니다.
또한 CPU는 I/O포트라는 것을 별도로 가지고 있어 외부 장치와 통신할 수 있도록 준비되어 있다.
디스크,프린터 등을 연결할 수 있고 어떤 경우는 Memory Mapped I/O라 해서 메모리 연결 라인을 통해
데이터를 주고 받게 연결하는 장치도 있습니다.
프로그램을 만들 때는 대표적인 I/O가 파일 입출력.
파일에 데이터를 읽고 쓰기 위해 우리는 OS나 C컴파일러가 제공하는 함수를 호출하는 일만 하지만 결과적으로
그 함수를 통해 하드디스크 같은 외부 장치의 데이터를 읽고 쓸 수 있습니다.
(보통 내부적으로 OS의 도움을 받습니다)
문제는 외부 장치는 대체로 CPU의 처리 속도에 비해서 무지막지하게 느립니다.
메모리도 느려서 CPU 속에 캐쉬 메모리를 이용한다.
따라서 CPU가 외부 장치에서 데이터를 읽어 오려면 그 동안 CPU는 다른 인스트럭션을 수행할 수도 없고,
데이터가 읽혀오기까지 대기하는 수밖에 없습니다.
이렇게 대기하는 CPU를 블로킹(Blocking)되었다고 하며 이런 방식의 I/O를 Blocked I/O라고 합니다.
CPU                   I/O장치(하드디스크)
 |실행   데이터 읽기/쓰기     .유휴(IDLE)상태
        ---------------->
 .대기   작업완료(CPU재개)    |I/O작업
        <----------------
 |실행                       .유휴(IDLE)상태

극복하고자 하드웨어와 소프트웨어 두 가지 모두의 개선이 필요합니다.
하드웨어의 개선은 CPU는 I/O장치랑 직접 통신하지 않고 중간에 컨트롤러라는 것을 두고 이 컨트롤러와 통신.
CPU는 컨트롤러에게 데이터를 읽기 위해 요청하거나 혹은 쓰기 위해 보내주기만 하고 그 이후에
실제 장치랑 통신하면서 데이터의 읽고 쓰기가 완료될 때까지 기다리는 책임은 컨트롤러가 하는 것.
그리고 컨트롤러는 요청한 작업이 끝나고 나면 CPU에서 인터럽트(interrupt)를 통해 작업이 끝났음을 알림.
따라서 필요한 작업의 요청만할 뿐 더 이상 작업이 끝날 때까지 기다릴 필요가 없습니다.
즉, 읽기/쓰기 요청 후에는 해당 작업이 끝나는 동안 다른 인스트럭션을 수행할 수 있는 것.

인터럽트란 CPU에 마련된 특별한 핀에 시그널이 들어오면 CPU가 기존의 작업을 중단하고 지정된 주소로
점프하여 작업을 수행하고 돌아오는 특별한 메커니즘.
인터럽트 핀으로 신호가 들어오면 CPU는 현재 수행 중이던 주소 PC레지스터의 값을 어딘가에 저장하고 미리 지정된
주소로 점프합니다.
그리고 이 지정된 주소에서부터 다시 인스트럭션을 수행하다가 iret라는 특별한 인스트럭션을 만나면 앞에서 저장한
PC레지스터의 값으로 다시 점프하는 것.
CPU는 해당 인터럽트 종류에 맞춰 지정된 주소로 점프하는데 점프할 주소는 통상적으로 프로그래머가 지정할
수 있도록 약속된 메모리나 레지스터에 저장.(점프 주소를 저장해두는 곳을 인터럽트 벡터 테이블이라고한다.)
인터럽트 루틴에서는 일반적으로 해당 I/O작업에 대한 완료 처리를 합니다.
더 보낼 데이터가 있으면 다시 컨트롤러에 데이터 전송 요청을 하고, 전송이 완료되었음을 사용자에게 알려야 한다면
완료 메세지를 출력하도록 할 수도 있을 것.
그리고 해당 인터럽트 루틴에서는 iret같은 복귀 인스트럭션을 통해 기존에 수행하던 곳으로 다시 점프해서 
아무 일도 없었다는 듯이 하던 일을 계속하는 것.
이런 방식을 블로킹되지 않는다 하여 Non-Blocked I/O 혹은 비동기 I/O(Asynchronous I/O)라고 합니다.
CPU                                       I/O장치(하드디스크)
 |실행   I/O 요청                I/O 명령       .유휴(IDLE)상태
		---------> |  컨트롤러  | --------->
 |실행   인터럽트   |           |  작업완료      |I/O작업
		<--------- |  컨트롤러  | <---------
    |인터럽트벡터로 점프                         .유휴(IDLE)상태
    | 
    |인터럽트 서비스 루틴 실행
	|
   iret
 |이전 실행 계속

아무리 하드웨어적으로 CPU가 I/O작업을 요청만 하고 다음 코드를 수행할 수 있다해도 실제 프로그래머가 작성하게
되는 코드는 I/O를 요청하고 나면 그 결과를 알아야 다음 작업을 할 수 있는 경우가 많습니다.
만약 ReadFile이 만일 비동기I/O로 동작한다면 호출되자마자 실제로 데이터가 읽히기도 전에 바로 리턴.
그리고 실제 읽기 작업이 끝나는 것은 인터럽트를 통해 알립니다.
이는 특정 함수로 맵핑되거나 메시지나 이벤트 방식으로 전달될 수 있습니다.
읽기가 완료되면 특정 함수가 호출된다든가 OS의 이벤트 객체가 깨어나 이 이벤트 객체에 대해 대기하던 스레드가
살아난다든지 할 수도 있습니다.
그리고 복사를 위해 WriteFile을 부르려면 데이터가 다 읽힌 다음이어야 한다.
아무리 ReadFile 이후 실제 I/O작업이 끝나기도 전에 바로 다음 코드를 수행할 수 있다해도 WriteFile을
호출하려면 어쩔 수 없이 I/O작업이 끝나고 데이터가 다 읽힌 이후여야 한다.
하지만 ReadFile과 WriteFile이 연속적으로 작성되어 있지 않고, 비동기적으로 ReadFIle호출 따로 WriteFile호출
따로인 방식으로 작성되어 있을 것이고 이런 I/O방식을 비동기I/O라고 부르는 것.
이런 코드는 결과적으로는 Blocked I/O일 때와 별다른 성능 차이를 보이진 않는다.
오히려 Blocked I/O에서는 ReadFile함수가 데이터를 실제로 다 읽을 때까지 리턴하지 않으므로 ReadFile 이후
곧바로 WriteFile을 부를 수 있어 훨씬 직관적이고 단순하게 만들 수 있는 반면 Non-Blocked I/O에서는 어차피
ReadFile의 결과가 넘어올 때까지 기다려야 하고 완료가 인터럽트 방식으로 비동기적이므로 프로그램 구조만 복잡.
하지만 실제 데이터가 I/O장치로부터 읽히는 동안 화면에 무언가를 표시하는 작업을 하려면 Blocked I/O로는 불가능.
반대로 Non-Blocked I/O에서는 복잡할 수 있지만 ReadFile을 호출하자마자 바로 리턴하므로 다른 코드 수행 가능.
사실 일반적으로 단일 응용 프로그램에서는 Non-Blocked I/O가 그다지 큰 의미가 없습니다.
파일이 복사되는 동안 할만한게 없다.
게다가 Non-Blocked I/O프로그램을 작성하는 것은 무척 까다롭다.
따라서 실제로 하드웨어적으로는 I/O컨트롤러를 통해 Non-Blocked I/O방식으로 동작하긴 하지만,
ReadFile/WriteFile같은 I/O용 API함수들은 내부적으로 컨트롤러로부터 작업이 완료되었다는 인터럽트가 
들어올 때까지 리턴하지 않고 블로킹하도록 만들기도 합니다. getch.

단일 응용 프로그램에서는 의미가 없었지만 멀티스레딩 OS에서는 매우 중요합니다.
한 스레드가 I/O작업을 하려하는데 이 I/O가 끝날 때까지 CPU가 기다려야 한다면 다른 스레드 모두 같이 대기해야
하는 상황이 벌어집니다.
반면 I/O요청만 하고 이 작업이 끝날 동안 CPU가 다른 일을 할 수 있다면 그 시간동안 나머지 스레드들의
코드를 수행할 수 있으므로 CPU는 쉬지 않고 일을 할 수 있고 전체적인 시스템 성능은 크게 향상되는 것.
하드웨어에서 아예 Blocked I/O밖에 지원하지 않아서 어쩔 수 없이 I/O함수가 블로킹하고 있는 것과 내부적으로
OS차원에서 대기하도록 하는 것과는 큰 차이가 있습니다.
내부적으로 대기하고 있는 동안은 OS가 다른 스레드를 실행할 수 있지만 하드웨어 차원에서 블로킹되면 CPU자체가
멈추므로 모든 스레드가 같이 멈추기 때문.
즉, I/O를 요청한 스레드 입장에서는 하드웨어가 Non-Blocked I/O를 지원하나 안하나 어차피 I/O함수가
Blocked I/O모드로 동작하므로 별다른 성능 향상은 없겠지만 시스템 전체로 그 시간 동안 다른 스레드를
실행할 수 있어 훨씬 이득인 셈.
따라서 많은 경우 실제 하드웨어에선 Non-Blocked I/O를 지원하면서도 OS가 제공하는 I/O함수들은 대부분
Blocked I/O모드로 동작하는 경우가 일반적.
이러면 프로그램에서는 Blocked I/O의 편리성을 누릴 수 있고 OS입장에서는 한 스레드가 I/O함수 안에서
블로킹하고 있는 동안 다른 스레드를 실행하게 스케쥴링할 수 있으므로 시스템 전체적으로 CPU를 놀리지 않고
가동해 성능을 높일 수 있다는 장점.
실제로 많은 OS에서는 특수한 경우를 빼고는 대부분 I/O함수들이 Blocked I/O방식으로 동작하고 있습니다.
대부분의 경우 이는 큰 문제가 되지 않습니다.
ReadFile하는 동안 화면에 출력하고 싶으면 별도로 스레드를 만들어 그 안에서 ReadFile함수를 호출하면 되기 때문.
그리고 메인 스레드는 이와 동기를 맞추어 화면에 표시하면 되기 때문.
결국 멀티스레딩은 다중 I/O작업에 있어서 보다 효율적인 면을 제공.

04 멀티스레딩과 서버
스레드가 분리된 이유는
1)자연스러운 논리적 흐름이 멀티스레딩과 부합하는 경우가 존재했기 때문입니다.
프로그램에서 논리적으로 두 가지 작업이 동시에 일어나야 하는 경우 실제로 작업의 개수만큼 스레드를 만들어
각 작업에 할당하는 것이 하나의 스레드에서 흉내내는 것보다 이상적.
게임을 만들면서 인공지능으로 5개의 적이 화면에서 움직이는 경우, 각각의 적마다 스레드를 만들어 서로
독립적인 알고리즘으로 개별적인 수행을 하여 움직이는 것이 좋아보입니다.
하지만 적들은 완벽하게 독립적일 수는 없고(충돌, 지형 등) 공유 자원 때문에 실질적으로 멀티스레딩이 그 
효용성에 비해 구현이 어려워집니다.
특히 게임의 특성상 한 번의 루프 안에서 모든 적과 아군의 이동 계산과 장면의 구성(Rendering)이 이루어지므로
별도의 스레드를 분리하여 생각하는 작업이 생각보다 만만치 않습니다.
따라서 실제로는 대부분의 게임이 단일 스레드로 동작.
논리적으로는 멀티 스레딩이 더 이상적인 매칭이 되는 경우가 있으므로 충분히 프로세스와 스레드 분리 사유가 된다.
2)실질적인 성능 향상을 위해서입니다.
CPU가 하나일 경우 멀티스레딩은 무조건 성능적인 손해를 봅니다.
각 스레드 사이에 전환이 일어나기 위해서는 모든 레지스터를 저장하고 복구해야 하는 등의 쓸데없는 오버헤드.
변면에 두 개의 스레드가 존재하고 실제로도 두 개의 CPU가 있으면 두 스레드는 어차피 논리적으로 독립된 수행을
해야 하므로 각각이 하나씩의 CPU에 할당되어 수행될 수 있기 때문.
이럴 경우 한 CPU가 복수의 스레드를 수행하면서 겪어야 하는 문맥전환이 필요없어지고 또한 한 CPU가 두 스레드에서
하는 작업을 처리할 때보다 이론적으로는 절반만큼 수행 시간이 단축될 수 있습니다.
그래서 CPU의 속도를 올리기보다 복수의 CPU를 사용하여 성능을 향상하는 방법을 연구하게 됨.
문제는 CPU마다 '어떻게 작업을 분배해 줄 것인가'하는 부분.
대부분의 경우는 한 프로그램이 하나의 흐름을 따라 진행되는 단일 스레드 방식이 적합하다.
이런 경우에는 어쩔 수 없이 한 CPU에 몰아서 작업을 줘야하고 복수의 독립된 프로그램이 있어야 CPU마다 
작업을 분배할 수 있습니다.
이런 경우도 사실 메모리와 같은 하드웨어 자원을 공유하기 때문에 완벽하게 작업을 분리하기는 힘듭니다.

멀티스레딩은 대용량 I/O처리를 하는 경우 큰 역할을 하게 됩니다.
파일에 작업을 하기 위해서는 C에서 제공하는 fopen이나 윈도우즈의 API함수인 CreateFile 함수 등을 이용해
파일을 열고 핸들을 얻어야 합니다.
그리고 그 핸들을 통해 C의 fread/fwrite나 ReadFile/WriteFile 같은 API함수를 호출하면서 작업.
핸들이 필요한 이유는 I/O의 대상이 되는 장치(파일)가 프로그램만 사용하는 것이 아니기 때문.
이러한 공용 장치(파일도 장치)로 하는 I/O하는 과정은 항상 OS가 제공하는 I/O API함수를 통해 실행.
그리고 이 함수들은 번호표를 뽑듯 핸들이라는 것을 리턴하여 이후 작업을 그 핸들을 통해 하는 것.
네트워크 카드는 하나지만 그 하나의 네트워크를 통해 많은 PC와 장치들과 통신합니다.
일반적으로 이러한 네트워크 통신을 위해서 핸들과 유사한 소켓이라는 개념이 사용되고 있습니다.
소켓이 파일과 다른 점은 파일은 여는 주체가 항상 프로그램이며 그 사용자의 의지에 따라 읽히고 쓰이는 수동적이지만
소켓은 일방적으로 사용자가 연다라는 개념이 아니라 상대방에게 접속을 하거나 접속을 당하는 두 가지 입장을 
둘 다 갖는다는 점.
그리고 데이터를 쓰는 것은 파일처럼 사용자의 의지대로 하지만 읽는 것은 통신 상대방의 의지라는 점.
(상대방이 데이터를 보내줘야만 읽을 수 있습니다)
파일을 다루는 프로그램에서는 파일에 데이터를 읽을지 쓸지 분명한 목적을 가지고 오픈한 다음 읽기 위해 연 경우면
데이터를 읽어 그 값에 따라 주어진 행동을 하고 쓰기 위해 연 경우 주어진 데이터를 쓰는 것으로 완료.
네트워크 프로그래밍에서는 내가 상대방에 접속을 하든지 상대방이 접속을 하든지 간에 일단 접속이 이루어지고나면
상대방과 데이터를 받으면서 그 데이터 내용에 따라 다음 행동이 결정되는 프로토콜(Protocol)이 있다.
가령 'Hello'를 보내면 'World'를 보낸다는 규칙이 있어야 하는 것.
네트워크 통신에서는 보통 접속을 당하는 쪽은 접속할 상대방이 누가 될지 모르므로 불특정 다수에 대해 연결을 대기.
그리고 상대방이 접속하고 나면 필요한 정보를 주고 '제공'하는 역할을 담당하게 됩니다.
접속을 당하는 쪽을 '서버(Server)'라고 합니다.
접속을 하는 쪽은 접속할 상대방인 서버의 주소를 명확히 알고 있어야만 하고, 접속하고 난 뒤에 데이터를 
주로 요청하는 입장에 있게 됩니다. 클라이언트(Client).

그런데 1:1로 통신을 하는 경우, 클라이언트를 만드는 경우는 단일 스레드만으로 충분합니다.
int main(int argc, char* argv[]) {
	char data[100];
	//소켓을 생성한다
	SOCKET s = socket(..);
	//접속을 한다
	connect(s, 접속주소);
	//Hello라는 문자를 보낸다
	send(s, "Hello");
	//응답을 기다린다. 답이 올 때까지 블로킹함.
	data = recv(s);
	//Hello에 대한 응답이 기대한대로 World라면
	//"Correct Server"를 출력하고 아니면
	//"Wrong Server"를 출력
	if(data == "world") {
		printf("Correct Server");
	}
	else {
		pirntf("Wrong Server");
	}
	//"123"을 보낸다.
	send(s, "123");
	//응답을 기다린다. 답이 올 때까지 블로킹
	data = recv(s);
	//응답이 기대한 123의 두 배인 246인지 확인
	if(data == "246") {
		printf("Correct Server");
	}
	else {
		printf("Wrong Server");
	}
	return 1;
}
우선 소켓을 생성하여(socket) 주어진 서버 주소로 접속하고(connect) 'Hello'라는 문자를 보내(send)
서버가 약속한대로 답을 보내는지(recv) 확인합니다.
connect, send, recv라는 함수들은 모두 BSD(Berkeley System Distribution)라는 버클리 대학의 변종 Unix
시스템에서 제안한 네트워크 프로그래밍 라이브러리에서 정의된 함수입니다.
소위 버클리 소켓이라 불리는데 미 국방성에서 BSD시스템을 채용하게 되면서 거의 표준 인터페이스로 자리잡음.
그래서 네트워크 프로그래밍 라이브러리를 제공하는 플랫폼에서는 버클리 소켓의 인터페이스는 기본으로 제공.
그리고 거기에 추가적으로 해당 플랫폼에서 특화된 형식의 코드를 제공.
윈도우즈에서도 버클리 소켓인터페이스를 제공하면서 동시에 자신들이 만든 WinSock이라는 라이브러리로 
WSAConnect, WSA 등의 새로운 함수들을 제공하기도 합니다.
위 함수들 모두 결국 CPU입장에서 보면 네트워크 카드와 I/O를 하는 것이므로 I/O함수입니다.
따라서 기본적으로 CPU와 네트워크 카드는 Non-Blocked I/O방식으로 동작하지만 위 함수들은 Blocked I/O형태로 동작.
가령 send함수를 호출하고 나면 데이터가 전송될 때까지나 실패될 때까지 리턴하지 않습니다.
(물론 소켓 설정에 따라 Non-Blocked방식으로 변경 가능)
중요한 건 일반적으로 클라이언트 프로그램에서는 Blocked I/O로 동작을 하는 소켓함수들을 통해 단일 스레드로도
충분히 하고자 하는 일을 할 수 있다는 점.
주어진 요청을 하고 그 요청에 대한 응답이 오기를 기다렸다가 그 응답에 따라 다시 다음 일을 진행하는 방식.

서버는 언제 클라이언트가 접속할지 모르므로 항상 대기하고 있어야 합니다.
이 때 클라이언트의 접속을 대기하는 함수가 바로 accept라는 함수.
이 accept함수도 기본적으로 Blocked I/O방식으로 동작하는 함수.
(소켓 생성 옵션을 통해 바꿀 수 있습니다)
문제는 서버가 단순히 접속을 기다리기만하면 안됩니다.
서버가 기다리기 위해 accept함수를 호출하면 이 함수는 클라이언트의 접속이 있을 때까지 계속 리턴하지 않고
블로킹 상태로 있게 됩니다.
첫번째 클라이언트가 접속할 때까지는 문제가 없지만 접속한 이후에 accept 함수는 접속한 소켓과 함께 리턴하고
그 때부터 접속한 소켓을 가지고 서버는 데이터를 주고 받는 작업을 해야합니다.
데이터를 수신하고 수신한 데이터에 대해 다시 적절한 응답을 해야 하는 것.
int main(int argc, char* argv[]) {
	char data[100];
	//접속을 기다릴 소켓을 생성
	SOCKET server_sock = socket(..);
	//클라이언트를 위한 소켓
	SOCKET client_sock;
	//접속을 기다리게 한다.
	listen(server_sock, ..);
	while(1) {
		//클라이언트가 접속할 때까지 대기
		//클라이언트가 접속하면 소켓 리턴
		client_sock = accept(server_sock);
		//접속한 클라이언트 소켓으로 데이터를 주고 받는다.
		//클라이언트가 bye를 보낼 때까지 반복
		do {
			//데이터가 올 때까지 대기
			recv(client_sock, data, ...);
			//Hello를 받으면 World를 보내주고
			//숫자를 받으면 두배해서 보내준다.
			if(data == "Hello") {
				send(client_sock, "World",..);
			}
			else if(data == 숫자) {
				send(client_sock, data*2, ...);
			}
		} while(data != "bye");
		close(clinet_sock);
	}
	return 1;
}
우선 서버용 소켓을 생성해서(socket) 이 소켓을 접속 대기용 소켓으로 만든다. (listen)
그리고 accept 함수를 호출해 접속이 있을 때까지 대기합니다.(accept)
accept함수는 접속이 이루어지면 접속된 클라이언트용 소켓과 함께 리턴하고 이제부터는 그 소켓을 통해
클라이언트와 데이터를 주고 받기 시작합니다.
그리고 클라이언트로부터 "bye"를 받으면 클라이언트의 접속을 끊고 다시 accept함수를 부르고
다음 클라이언트의 접속을 기다린다는 것.
루프 안에선 다시 accept함수를 부르지 않으므로 다른 클라이언트의 접속을 받을 수 없습니다.
만일 중간에 접속이 끊기면 단절을 알 방법이 있어야합니다.
접속이 끊기면 이를 감지하고 다시 accept를 불러 다른 클라이언트의 접속을 대기해야 하니까.
강제로 끊기지 않아도 누군가 다른 사람이 접속을 이미 해버렸다면 "bye"로 접속을 종료하지 않으면 접속 불가.
이런 경우는 일반적으로 기존에 접속되어 있는 사람이 있더라도 뒤에 접속하는 사람을 대비해 접속은 항상 가능하게
만들고, 대신 인증 문자 등을 통해 뒤에 접속하는 사람이 우선권을 가지게 해야 합니다.
이러한 문제를 해결하기 위해 표준 소켓 라이브러리에는 accept, send, recv 등의 소켓 함수들을
Non-Blocked모드로 동작하도록 설정하는 옵션이 있습니다.
그러면 accept함수를 부르더라도 곧바로 리턴하죠.
대신 select라는 함수만이 블로킹을 하고 클라이언트가 접속하거나 이미 접속한 클라이언트로부터 데이터를
수신하거나 하면 리턴합니다.
그리고 어떤 이벤트가 발생했는지에 따라 accept함수나 recv 등을 불러서 처리할 수 있는 것.
select는 하나의 소켓이 아니라 여러 클라이언트를 동시에 핸들링할 수도 있게 해줍니다.
만약 멀티스레딩을 이용하면 직관적이고 간단한 형태로 서버를 제작할 수 있습니다.
unsigned int ClientThread(void* pClientSock) {
	SOCKET client_sock = (SOCKET)pClientSock;
	//접속한 클라이언트 소켓으로 데이터를 주고 받는다.
	//클라이언트가 bye를 보낼 때까지 반복
	do {
		//데이터가 올 때까지 대기
		recv(client_sock,data, ...);
		//Hello를 받으면 World를 보내주고
		//숫자를 받으면 두배해서 보내준다.
		if(data == "Hello") {
			send(client_sock, "World",..);
		}
		else if(data == 숫자) {
			send(client_sock, data*2, ...);
		}
	} while(data != "bye");
	close(client_sock);
	//스레드 종료
}
int main(int argc, char* argv[]) {
	char data[100];
	//접속을 기다릴 소켓을 생성
	SOCKET server_sock = socket(..);
	//클라이언트를 위한 소켓
	SOCKET client_sock;
	//접속을 기다리게 한다.
	listen(server_sock,..);
	while(1) {
		//클라이언트가 접속할 때까지 대기
		//클라이언트가 접속하면 소켓 리턴
		client_sock = accept(server_sock);
		//새로운 스레드를 만들어 접속한 클라이언트 소켓을 인자로 넘겨준다.
		//이후 클라이언트와의 통신은 새 스레드에서 행해진다.
		CreateProcess(...,ClientThread,...,client_sock,...);
	}
	return 1;
}
메인스레드가 accept함수에서 블로킹 되어 클라이언트가 접속할 때까지 실행이 멈춰 있습니다.
accept가 되고 나서 접속한 클라이언트 소켓과 통신하며 요청한 응답에 대응하는 작업을 메인스레드가 하는 대신
새로운 스레드를 생성해서 한다.
새 스레드는 ClientThread함수를 실행하며 인자는 접속한 클라이언트의 소켓이 넘어갑니다.
전달받은 소켓을 통해 같은 작업을 합니다.
결국 메인 스레드는 클라이언트가 접속하면 접속된 클라이언트에 매달려 있는 대신 새로운 스레드를 생성해서
해당 스레드가 일 처리를 하게 하고 자신은 다시금 accept함수를 불러 다음 클라이언트의 접속을 대기하는 것.
아무리 많은 클라이언트가 접속하더라도 OS가 허락하는 한 계속 새로운 스레드가 만들어지며 해당 클라이언트와의
통신을 전담할 수 있습니다.
이렇게 되면 코드도 심플해지고, 직관적인 코드를 제작할 수 있습니다.
이 방식 역시 유닉스에서 전통적으로 사용되던 멀티스레딩 서버 제작 방식.

하지만 연구 결과, 멀티스레딩이 생각보다 성능이 좋지 않다는 점.
실제로는 접속한 클라이언트 수가 많아질수록 select를 사용한 단일 스레드 방식 서버에 비해 성능이 점점 떨어짐.
멀티스레딩 방식에서는 접속되어 있는 클라이언트 수만큼 스레드가 만들어지고 이 스레드들은 결국 CPU가
스레드 개수만큼 있지 않은 이상 OS가 스케쥴링을 통해 계속 Context Switching해야 하기 때문.
CPU는 기존에 실행 상태에 있는 스레드를 다시 재개할 때를 대비해 현재의 레지스터 정보를 전부 메모리에 저장.
그리고 새로 실행 상태가 되는 스레드가 과거에 저장하였던 값을 읽어와 다시 각 레지스터에 써줍니다.
이렇게 접속한 클라이언트 수가 많아질수록 활성화된 스레드 개수가 많아질 것이고 그만큼 문맥전환도 자주.
그만큼 CPU가 문맥전환을 위해 작업에 시간을 많이 할애해야 한다는 것.
결국 클라이언트 수가 증가할수록 CPU는 정작 해야할 일을 하는 것보다 문맥전환하는데 시간이 더 많이 뺏김.
그래서 소켓 함수들을 Non-Blocked모드로 동작하게하고 select함수를 사용해 단일 스레드로 처리하는 방식이
멀티스레드보다 좋다는 결론이 나있습니다.
실제 클라이언트와의 I/O작업 패턴이나 양에 따라 어느 경우엔 멀티스레드가 더 효율적이거나 비슷한 퍼포먼스하에서
사용하기 편리한 경우도 있어 멀티스레드도 쓰인다.
최종선택은 서버 제작자의 경험이나 성향에 따라 결정되는 것.
하지만 윈도우즈 세계에서는 최강자 타이틀을 거머쥔 방식이 IOCP(I/O Completion Port)라고 하는 것.

05 윈도우즈의 최강자 서버 - IOCP
Overlapped I/O는 윈도우즈 NT에서 처음 도입된 방식.
유닉스 계열의 OS에서는 I/O장치를 포함한 모든 것이 파일 형태로 존재하고 결국 외부 장치와의 I/O역시
파일 입출력과 마찬가지 형태로 이루어집니다.
윈도우즈에서도 어느 정도 비슷하지만 ReadFile/WriteFile이라는 API함수를 통해 파일 뿐 아니라
RS-232C로 대표되는 시리얼 통신장치(UART)나 네트워크 소켓까지도 데이터를 주고 받을 수 있습니다.
그리고 Overlapped I/O라는 것은 이 두 API함수가 Non-Blocked I/O형태로 동작하는 것을 일컫는다.
기존에서는 두 함수는 Blocked I/O로 동작하기 때문에 실제 데이터가 써지거나 읽히는 작업이 완료될 때까지
함수가 리턴하지 않습니다.
NT버전부터는 파일을 오픈할 때 어떤 옵션을 주느냐에 따라 ReadFile/WriteFile이 Non-Blocked I/O형태로.
이를 윈도우즈에서는 Overlapped I/O라고 부르는데 Non-Blocked로 동작하는 것 뿐만아니라,
내부적으로 실제 디바이스와 응용 프로그램간에 주고 받는 데이터도 같은 메모리를 사용함으로써
데이터 복사 시간을 줄였다는 장점도 있습니다.
(보통은 응용 프로그램에서 요청한 I/O작업을 디바이스 드라이버에서 다시 별도의 메모리에 복사해서 요청)
중요한 점은 Overlapped I/O가 Non-Blocked 모드로 동작하면서 I/O 작업을 요청하고 다른일을 할 수 있게된 점.
이 방식이 서버 프로그램의 성능을 개선시킬 수 있을 거라 생각했지만 결국 멀티스레딩과 똑같았다.
왜냐하면 Overlapped I/O방식으로 파일이나 장치가 오픈되면 ReadFile이나 WriteFile함수가 바로 리턴하기는 하지만
결국은 요청한 I/O작업이 끝났다는 사실을 프로그램이 전달 받으려면 ReadFile이나 WriteFile을 호출한 스레드가
Sleep함수 등을 호출해서 대기 모드(Waiting Mode)로 들어가야 하기 때문.
거의 대부분의 경우 데이터를 읽거나 쓰고나면 그 작업이 끝났다는 것을 알아야 다음 작업을 진행할 수 있는데,
Blocked I/O방식에서는 아예 ReadFile/WriteFile 함수 자체가 작업이 완료되기 전까지는 리턴하지 않기 때문에
별도의 작업 완료에 대한 통지가 없습니다.
하지만 Overlapped I/O방식에서는 이 함수들이 Non-Blocked 방식으로 동작하다보니 곧바로 리턴하는데,
요청한 작업이 끝났다는 것을 알려주는 방식이 콜백 함수나 이벤트 객체를 통해서 이루어집니다.
콜백 함수는 함수의 주소를 넘겨주면 후에 그 함수가 호출되어 실행되는 방식을 일컫고
이벤트 객체 방식은 해당 이벤트 객체를 시그널링(Signaling)하여 알려주는 방법.
unsigned int OnComplete(void* pOverlapped) {
	//ReadFile의 읽기 요청 작업이 끝났다.
	//전달받은 인자를 통해 읽힌 데이터를 액세스할 수 있다.
}
int main(int argc, char* argv[]) {
	...
	//데이터 읽기를 요청
	//곧바로 리턴하고 읽기 작업이 완료되면 OnComplete함수를 호출하도록 한다.
	ReadFileEx(..., OnComplete);
	...
	//OnComplete 콜백 함수가 불리게 하기 위해서는 자발적으로 Sleep함수 등을 불러
	//대기 모드로 스레드를 전환시켜 두어야 한다.
	Sleep(..);

	return 1;
}
ReadFileEx는 ReadFile이랑 비슷한 함수인데 단지 작업 완료를 콜백 함수를 통해 해 준다.
사용자가 ReadFileEx함수를 호출하여 데이터를 읽어오라고 명령합니다.
그러면 ReadFileEx는 이 요청을 디바이스 드라이버를 통해 I/O장치로 전달하고 곧바로 리턴합니다.
그리고 이제 데이터가 다 읽히고 나면 인터럽트가 걸리고 이 인터럽트를 처리하는 루틴에서
ReadFileEx를 호출할 때 인자로 넘겨받은 OnComplete함수를 불러줍니다.
Overlapped I/O방식에서는 바로 ReadFileEx를 호출한 스레드를 통해 OnComplete을 수행시켜 줍니다.
main함수 내에서 ReadFileEx를 호출하였으므로 메인 스레드가 OnComplete함수를 실행해야 하지만
메인 스레드가 다른 코드를 실행 중일 수도 있다.
스레드에도 대기 큐(Queue)라는 것이 있어 해당 스레드가 실행시키고자 하는 루틴의 시작 주소를 대기시켜 둔다.
이 큐의 루틴을 실행하려면 기존에 실행하던 루틴에서 Sleep같은 API함수를 호출해 스레드를 대기모드로 전환해야 합니다.
결국 메인 스레드를 통해 OnComplete콜백함수가 호출되려면 메인스레드가 ReadFileEx를 부른 후에
어느 시점에선가 Sleep 함수 등을 불러 자발적으로 대기 모드로 들어가 있어야 한다.
이렇게 되면 결국 유닉스의 멀티스레딩 방식 서버와 달리지는 점이 없습니다.
멀티스레딩 방식에서는 기본적으로 recv, accept 등의 I/O 함수들이 Blocked I/O방식으로 동작하므로
작업이 끝나기 전까지 함수 내부에서 자발적으로 대기 모드로 전환하고 있다가 I/O작업이 끝나면 
리턴하였지만 Overlapped I/O방식에서도 결국 ReadFileEx안에서 직접 대기모드로 전환하지 않았을 뿐
결국엔 Sleep 등의 함수를 써서 ReadFileEx를 호출한 다음에 스레드를 대기 모드로 전환해야 하기 때문.
결국 I/O함수가 내부적으로하느냐 응용 프로그램 코드가 해주냐의 차이뿐.

ReadFileEx대신 ReadFile을 쓰면 OVERLAPPED라고 하는 구조체 안에 이벤트 객체의 핸들을 지정해 두고
이 이벤트 객체를 시그널링해서 작업 완료를 알려준다는 점만 다를 뿐 마찬가지.
int main(int argc, char* argv[]) {
	HANDLE hComplete = CreateEvent(...);
	OVERLAPPED ov;
	ov.hEvent = hComplete;
	//데이터 읽기를 요청
	//곧바로 리턴하고 읽기 작업이 완료되면 hComplete 이벤트 객체를 시그널링 해준다.
	ReadFile(..., &ov);
	//hComplete 이벤트 객체가 시그널링될 때까지 스레드를 대기모드로 만들어 준다.
	//즉, 코드 실행이 멈추게 된다.
	WaitForSingleObject(hComplete,..);
	//hComplete 이벤트 객체가 시그널링 되었다.
	//ov 구조체의 다른 인자들을 통해 데이터를 액세스할 수 있다.
	...
	return 1;
}
ReadFileEx대신 ReadFile을 사용해 이벤트 객체의 시그널링을 통해 작업 완료를 전달 받는 방식.
결국 OnComplete 함수를 부르는 대신 이벤트 객체라는 것을 만들고 WaitForSingleObjet같은 API함수를 호출해
해당 이벤트가 시그널링될 때까지 스레드를 대기 모드로 전환해 둡니다.
그리고 ReadFile에서 요청한 읽기 작업이 완료되면 그 이벤트가 시그널링되어 WaitForSingleObject함수가 리턴.
그리고 그 이후에 비로소 OnComplete 함수에서 한 것처럼 읽힌 데이터를 이용해 다음 처리를 하면 됨.
결국 OnComplete 함수 안의 코드를 ReadFile을 호출한 main함수 안으로 옮겨놓은것 뿐.
Overlapped I/O 방식에서도 I/O 작업을 요청한 스레드를 통해 다음 일을 진행할 수 밖에 없으므로 소켓 작업을
할 경우 접속한 클라이언트당 하나의 스레드를 만들어야 하고, 클라이언트 수가 많아질수록 유닉스 스타일의
멀티스레딩 방식과 마찬가지로 문맥 전환에 CPU파워를 소비해버리는 비효율적인 운영이 됩니다.
이런 단점을 개선해 놓은 것이 IOCP(I/O Completion Port).

IOCP는 '가장 이상적인 케이스는 문맥전환의 오버헤드를 없애고 모든 CPU파워를 실제 필요한 일에 집중시키는 것'.
IOCP의 핵심은 I/O 작업 스레드간의 문맥 전환을 없앴다는 것.
select를 사용한 방식에서는 CPU가 무조건 단일 스레드만으로 동작하는데, 결국 한 개의 CPU만 사용하고
나머지 CPU는 작동하지 않는 셈.
멀티스레딩 방식에서는 클라이언트가 접속할 때마다 스레드를 생성하므로 불필요하게 CPU개수 이상으로
스레드 개수가 많아져 비효율적.
IOCP방식에서는 기본적으로 딱 CPU개수만큼만 스레드를 미리 생성해두는 것.
시스템에 세 개의 CPU가 있으면 세 개의 스레드를 미리 생성합니다.(실제로는 조금 다름).
그리고 미리 생성된 세 개의 스레드를 스레드 풀(Thread Pool)이라고 부르고 각각의 스레드들을
워커 스레드(Worker Thread)라고 부릅니다.
이러한 스레드 풀과 함께 필요한 것이 IOCP라고 불리는 객체.
IOCP도 Overlapped I/O처럼 Non-Blocked I/O로 동작합니다.
Overlapped I/O에서는 I/O작업의 완료를 호출한 스레드를 통해 콜백함수를 실행함으로써 통지하는데,
IOCP방식에서는 IOCP 객체를 I/O장치와 연동하면 해당 I/O에 대한 작업 완료 통지가 IOCP객체로 전달됩니다.
그러면 IOCP객체는 스레드 풀에 있는 워커 스레드 중 현재 대기 모드에 있는 것을 하나 선택해
해당 스레드를 통해 작업 완료를 알려줍니다.
임의의 스레드          I/O장치(파일,소켓)               IOCP객체
     |      읽기 요청
 Read 파일    ----->        |실제 읽기    완료 통지    (완료된 작업 리스트)
     |계속 실행          작업 완료          ----->     완료목록n
													  ...
							스레드풀에서  			  완료목록1
							┌────────────────────────────┘
							|  대기 상태의 스레드 선택
                        |스레드1|
						|스레드2|
						|...   |
						|스레드m|
						   | 선택된 스레드로 주어진 완료 목록에 대해 콜백 함수 실행
						   | 

IOCP객체가 생성되었고 파일을 하나 열었다고 가정해보자.
또 열린 파일 핸들은 IOCP객체와 연동되어 있습니다.
어떤 스레드에서 열린 파일로 ReadFile함수를 호출했습니다.
이 때 ReadFile을 호출할 때 파라미터 변수를 하나 넘기는데, OVERLAPPED 구조체라 불리는 이 변수가
작업이 완료되었을 때 어떤 I/O작업이 완료되었는지를 파악할 수 있게 해줌.
ReadFile함수는 Non-Blocked 모드로 동작하고 I/O 장치로 데이터를 읽으라고 요청만하고 바로 리턴합니다.
I/O장치에서 데이터가 다 읽히고 나면 이 사실이 IOCP객체에 전달됩니다.
이 때 어떤 작업이 완료되었는지 알 수 있도록 처음 ReadFile을 호출할 때 넘겼던 OVERLAPPED구조체 변수가 같이 넘어옴.
IOCP객체는 내부적으로 큐를 가지고 있어 완료된 작업에 대한 목록을 OVERLAPPED구조체 변수와 함께 저장합니다.
그리고 스레드 풀에 있는 스레드 중 현재 대기 모드에 있는 스레드가 하나 선택되어 미리 주어진 함수가 실행.
이 때 함수의 인자로 넘어가는 것이 바로 주어진 OVERLAPPED 구조체 변수.
결국 ReadFile 때 인자로 준 OVERLAPPED 구조체 변수는 데이터가 다 읽히고 나면 스레드 풀에 있는
스레드 중 하나가 실행되면서 인자로 넘어가는 것.
IOCP의 장점은 스레드 풀을 유지하고 있다는 것.
CPU개수만큼 스레드를 미리 생성해서 유지하면서 IOCP객체와 연동된 I/O작업이 끝나면 스레드 중 쉬고 있는
스레드를 통해 완료 작업을 하는 것.
모두 작업을 수행 중이라면 쉬는 스레드가 나올 때까지 기다림.
우선 딱 CPU개수만큼 스레드를 생성하고 이 스레드만으로 모든 I/O작업을 하므로 스레드간 쓸데 없는 문맥전환이
일어나지 않습니다.
CPU개수만큼 스레드가 있으므로 단일 스레드 때와 다르게 쉬는 CPU가 발생하지 않습니다.
단일 쓰레드는 아무리 많은 I/O작업이 밀려 있어도 하나의 스레드로 작업하므로 CPU도 하나만 사용했다.
스레드 풀을 사용하게 되어서 스레드를 생성하는 수고도 덜게 됩니다.
매번 I/O작업이 발생할 때마다 스레드를 만들어 처리하면 그만큼 스레드를 만드는데 시간을 빼앗깁니다.
결국 IOCP는 단일 스레드와 멀티스레드의 장점만을 모아 만든 방식.

typedef enum {
	IO_ACCEPT, IO_READ, IO_WRITE
} IOTYPE;
typedef struct {
	OVERLAPPED ov;
	IOTYPE IOKind;
	SOCKET sock;
	char readbuf[1000];
} OVERLAPPED_EX;
HANDLE g_hIOCP;
SOCKET g_listen_sock;
OVERLAPPED_EX g_OV;
unsigned int OnIoCompletion(OVERLAPPED_EX* pOV) {
	//접속이 끊겼을 경우 다시 클라이언트 접속을 기다린다.
	if(접속이 끊겠냐?) {
		close(pOV->sock);
		pOV->sock = socket(..);
		pOV->IOKind = IO_ACCEPT;
		AcceptEx(g_listen_sock, pOV->sock, ..., pOV);
	}
	else {
		//어떤 I/O가 완료되었는지에 따라 다음 할 일을 결정한다.
		switch(pOV->IOKind) {
		case IO_ACCEPT:
			//소켓을 IOCP객체와 연동시킨다.
			//이후 이 소켓으로 이루어지는 작업완료는 연동된 IOCP객체로 통보된다.
			BindIoCompletionCallback((HANDLE)pOV->sock, OnIOCompletion, ...);
			//클라이언트가 접속한 경우 곧바로 데이터 수신을 기다린다.
			pOV->IOKind = IO_READ;
			ReadFile(pOV->sock,...,pOV->readbuf,...);
			break;
		case IO_READ:
			//데이터 수신이 완료된 경우 해당 데이터에 따라 적절한 응답 메시지를 보내준다.
			//그리고 다시금 수신 데이터를 기다린다.
			if(pOV->readbuf == "Hello") {
				pOV->IOKind = IO_WRITE;
				WriteFile("World",...,&ov);
			}
			else if(pOV->readbuf == 숫자) {
				pOV->IOKind = IO_WRITE;
				WriteFile(pOV->readbuf*2,...,&ov);
			}
			else if(pOV->readbuf == "bye") {
				close(pOV->sock);
				pOV->sock = socket(...);
				pOV->IOKind = IO_ACCEPT;
				AcceptEx(g_listen_sock, pOV->sock, ..., pOV);
			}
			break;
		case IO_WRITE:
			pOV->IOKind = IO_READ;
			ReadFile(pOV->sock,...,pOV->readbuf,...);
		}
	}
}
int main(int argc, char* argv[]) {
	//IOCP객체의 핸들을 만든다.
	g_hIOCP = CreateIoCompletionPort(...);
	g_listen_sock = sock(...);
	BindIoCompletionCallback((HANDLE)listen_sock, OnIOCompletion,...);
	listen(listen_sock);
	for(int i = 0; i < MAX_CLIENT_COUT; i++) {
		g_OV[i].IOKind = IO_ACCEPT;
		g_OV[i].sock = socket(...);
		AcceptEx(g_listen_sock,g_OV[i].sock, ..., &g_OV[i]);
	}
	return 1;
}
CreateIoCompletionPort라는 API함수를 통해 IOCP객체를 생성합니다.
기존과 같이 서버용 소켓을 생성해 listen.
여기서는 서버 소켓을 방금 생성한 IOCP객체와 연동시켜(BindIoCompletionCallBack) 이 소켓에서 일어나는
모든 I/O 완료 작업을 IOCP객체에 통보하도록 합니다.
다음으로 accept함수를 부르는데 접속할 클라이언트 수만큼 accept함수를 호출해 두면 클라이언트가 접속할 
때마다 IOCP로 그 사실이 통보되고 IOCP는 스레드 풀에서 현재 대기 모드에 있는 스레드를 찾아 이후 일을 맡기게 됨.
accept함수를 호출하는 것은 main함수이므로 메인 스레드가 되겠지만 실제 클라이언트가 접속된 경우 이를
처리하는 것은 다른 스레드이므로 accept함수를 호출할 때 g_OV[i]라는 구조체를 함께 넘기게 됩니다.
구조체가 작업지시서 같은 것으로 이번 작업이 accept함수의 호출에 의해 생긴 작업이라는 것을 알기 위해
IO_ACCEPT라는 값을 저장해서 넘깁니다.
클라이언트가 접속하면 IOCP가 이를 통보 받고 다시 대기 중인 스레드를 찾아서 일을 맡깁니다.
앞에서 서버 소켓을 IOCP와 연동하는 함수인 BindIoCompletionCallBack를 호출할 때 인자로 넘긴
콜백 함수의 주소 OnIOCompletion이 있습니다.
IOCP가 스레드에게 일을 맡기면 바로 해당 스레드를 통해 OnIOCompletion가 실행되는 것.
그러면 함수의 인자로 어떤 일로 인해 실행되는지에 대한 정보를 같이 보냅니다.
그 정보가 바로 accept함수를 호출할 때 인자로 넘겼던 g_OV[i]라는 구조체.
따라서 함수 안에서는 이 구조체의 정보를 보고 다음에 무슨 일을 진행해야 하는지를 판단.
accept함수를 호출할 때 IO_ACCEPT라는 값을 구조체에 저장하고 호출합니다.
클라이언트가 접고하여 OnIOCompletion이라는 함수가 임의의 워크스레드를 통해 실행이 되면,
OnIOCompletion안에서는 인자로 넘어온 pOV구조체의 IOKind라는 값이 IO_ACCPET라는 것을 보고
accept함수를 호출하고 그 결과 클라이언트가 접속한것을 알게 된 후 접속한 클라이언트의 소켓을 다시
IOCP 객체와 연동합니다(BindIOCompletionPort호출)
그 다음 할일은 ReadFile을 호출하는 것.
BindIoCompletionPort를 부른 후에 해당 클라이언트 소켓으로 ReadFile을 함으로써 클라이언트로부터 데이터를
기다리게 되는 것.
ReadFile은 곧바로 리턴하고 OnIOCompletion함수도 리턴하여 해당 스레드가 다시 대기 모드로 들어갑니다.
ReadFile을 호출할 때 자신이 받은 pOV작업 지시서에 다시 이번에는 IO_READ라는 기록을 해둡니다.
ReadFile의 결과 데이터가 수신되면, IOCP객체에서는 다시 스레드를 찾아 pOV와 함께 전달.
OnIOCompletion함수가 대기 중인 스레드에 의해 실행되고, ReadFile을 호출할 때 넘겼던 pOV값이
그대로 인자로 다시 넘어옵니다.
pOV는 원래는 accept를 호출할 때 사용했던 g_OV[i]객체였고, 지금은 IO_READ라는 값이 기록되어져 있습니다.
따라서 OnIOCompletion함수 안에서는 switch 문에서 IO_READ의 루틴을 수행하는 것.
그리고 넘겨 받은 물건은 작업 지시서와 함께 있는 readbuf라는 버퍼.
이 버퍼의 값을 보고 이전의 서버와 마찬가지로 Hello인가 숫자인가에 따라 적절한 응답을 해주는 것.
응답이라는 것은 WriteFile로 데이터를 클라이언트에게 보내주는 것.
그리고 WriteFile안에는 다시 IO_WRITE를 기록한 pOV를 넘겨주어 다음 스레드가 일을 계속할 수 있게 해줌.
만일 수신한 데이터가 bye라는 문자열이라면 스레드는 해당 소켓을 close하고 다시 새로운 소켓을 생성해
IO_ACCEPT를 작업지시서에 기록하고 accept함수를 불러 다음 일을 요청.
WriteFile로 요청한 전송 작업이 끝나면 다시 IOCP로 통보가 오고 작업 지시서엔 IO_WRITE라고 되어 있을 것이므로
이를 처리하는 스레드는 다시 ReadFile을 불러 클라이언트로부터의 다음 메세지를 요청하고 이런과정이 계속 반복.
결국 중요한 것은 accept나 ReadFile(recv), WriteFile(send) 등은 모두 I/O에 작업을 요청하는 함수들인데
함수를 호출하는 스레드가 어떤 스레드였는지 상관없이 요청된 작업이 끝나면 그 시점에서 대기 모드에 있는
스레드로 다음 작업이 이어지게 된다는 것.
물론 모든 과정이 우연히 하나의 스레드로 이루어질 수도 있습니다.
IOCP서버에서는 훨씬 더 빈번하게 일어나는데 항상 마지막에 일을 끝낸 스레드로 다시 일을 시키기 때문.
개념들은 단순해 보일 수있지만 구현하려면 무척 힘듭니다.
가장 핵심은 BindIOCompletion라는 함수인데 이 함수가 워커 스레드에 대한 관리라든지 대부분의 위에서
얘기한 작업을 도맡아 해줍니다.
직접 워커 스레드를 원하는 개수만큼 만들어 GetQueuedCompletionStatus라는 함수를 이용해 구현할 수도 있다.
IOCP는 대용량 서버 프로그래밍입니다.

스레드의 CPU점유율
스레드가 많아지면 많아질수록 한 프로그램이 사용하는 CPU의 사용률은 떨어지게 될 것입니다.
하지만 작업관리자를 띄워보면 대다수 프로그램은 CPU사용률이 0이고, 샘플프로그램이 거의 대부분의 CPU사용률.
작업관리자에서도 보면 한 프로그램에 16개의 스레드가 있는 경우도 있고, 시스템 전체로 따지면
100개가 넘을 정도로 많은 스레드가 존재합니다.
만일 CPU가 스레드 모두를 공평하게 수행하고 있다면 스레드가 늘어날 때마다 모든 나머지 프로그램의 수행속도는
점점 느려질 것이고, CPU사용률 역시 100을 전체로 보았을 때 모든 프로그램이 공정하게 나누어 점유해야 합니다.
하지만 실제로 대부분 프로그램 CPU사용률은 0이며 프로그램을 더 많이 실행해도 수행속도가 크게 느려지진 않습니다.
프로그램을 많이 띄워 느려지는 경우 대체로 메모리 부족으로 인한 현상.
이는 비록 시스템에 있는 전체 스레드 개수는 많아도 현재 활성화 되어 있는 스레드가 거의 없기 때문.
스레드는 내부적으로 여러가지 상태값을 가지고 있는데 대푲거인 것이 Waiting Mode와 Running Mode.
대기모드란 스레드가 어떤 일도 하지 않고 대기하고 있는 상태.
이 상태에서는 스레드는 존재하지만 CPU는 해당 스레드로 문맥전환을 하지 않기 때문에
실제로는 CPU의 성능에 영향을 주지 않습니다.
그리고 실제 대다수의 스레드는 거의 대부분의 시간을 이 대기모드에서 지내게 됩니다.
반면 활성화되어 CPU가 해당 스레드로 문맥전환하여 수행하는 상태가 실행모드.
스레드가 늘어날 때마다 다른 스레드들의 CPU사용률이 줄어들게 됩니다.
(엄밀하게는 OS가 강제적으로 다른 스레드로 전환을 하는 동안은 실행모드가 아닙니다)
도스에서는 단일 프로그램만 동작할 수 있었고, 스레드라는 개념조차 없습니다.
따라서 CPU는 항상 실행 중인 프로그램 코드를 수행하고 있게 됩니다.
모든 프로그램은 main이나 WinMain함수에서 프로그램이 시작하면 어디선가 항상 무한 루프를 돌면서
프로그램이 종료될 때까지 그 루프를 벗어나지 않습니다.
왜냐하면 코드가 진행되어 main이나 WinMain에서 리턴하게 되면 프로그램이 종료되니까.
프로그램에 따라 무한루프에서 하는 일이 다른데 게임인 경우 비디오 화면을 갱신할 수 있습니다.
따라서 초당 몇 번이나 루프를 돌 수 있는지가 게임에서 몇 프레임이 나온다는 얘기.
워드 프로세서라면 대부분의 시간을 키입력을 기다리며 getch같은 함수에서 보내고 있을 것.
getch함수는 굳이 다른 일을 안해도 내부적으로 계속 루프를 돌면서 키보드를 모니터링해도 문제 없다.
즉 CPU가 계속 getch안의 루프 코드를 수행하고 있는것 (실제론 조금 다르다)
반면, 윈도우즈와 같은 멀티태스킹 OS에서는 getch 같이 혼자서 CPU를 계속 독점하게 되면 다른 프로그램이
수행할 기회를 잡지못합니다.
따라서 비선점형OS에서는 한 프로그램에서 계속 무한 루프를 돌게 되면 다른 프로그램이 작동되지 않았습니다.
지금의 선점형 OS에서는 일정 시간이 지나면 인터럽트라는 것을 통해 OS가 다시 제어권을 다른 프로그램(스레드)로
전환해주므로 다른 프로그램도 실행이 되지만 문제가 있다.
왜냐하면 CPU는 계속해서 무한 루프를 돌고 있는 프로그램에 할당되어 루프 코드를 수행해야하므로
전체적인 시스템 성능이 떨어질 것.
윈도우즈에서는 이벤트 드리븐(Event Driven)방식을 사용합니다.
각 프로그램이 직접 getch같은 함수를 부르면 무한 루프를 도는 대신 GetMessage API를 부르면 무한 루프를 도는 것.
그리고 GetMessage는 내부적으로 어떤 이벤트가 발생할 때까지 해당 스레드를 대기모드로 전환시킵니다.
만일 키보드 같은 입력이 발생하면 해당 프로그램은 대기 모드에서 깨어나 실행모드가 되면서 멈춰있던 GetMessage가
다시 실행되며 그 메시지를 OS로부터 받아오는 것.
그 이후의 코드는 그 메시지에 따라 적절한 처리를 하고 다시 GetMessage로 되돌아가는 형태.
따라서 많은 프로그램이 대부분의 시간을 사용자의 입력을 기다리면서 보내고, 입력이 발생하지 않는 한 CPU를
사용하지 않는 대기 모드에 있는 것.
키보드 타이핑은 아무리 빨라도 CPU속도에 미치지 못하지만 MP3데이터를 처리하는 것은 많은 CPU파워를 요구.
그래서 CPU가 MP3데이터를 디코딩하는 속도가 재생속도보다 느리거나 같다면 MP3플레이어의 스레드는 대기모드에 있는
시간보다 실행모드에서 보내는 시간이 많을 것.
그러면 CPU사용률이 높아져 100%에 가까운 점유율.
무한루프를 도는 대부분은 키보드 등의 외부 입력을 받기 위한 I/O작업을 요청하거나 윈도우즈의 메시지를
기다리기 위해 OS의 API함수를 호출합니다.
그러면 API함수는 내부적으로 스레드를 대기모드로 전환하고, I/O작업이 끝나게되면 Blocked I/O인 경우
다시 실행모드로 되돌아옵니다.
따라서 무한정 CPU를 사용하는 일은 드물고 사용하는 경우가 발생해도 중간에 Sleep같이 강제적으로 스레드를
대기모드로 전환해주는 함수를 삽입해서 CPU를 너무 독점적을 사용하지 않게 해주는 것이 일반적.
결론적으로 시스템에 많은 스레드가 존재해도 실제로 대부분의 스레드는 아주 잠깐 실행모드에서 돌아가고
대부분의 시간은 대기모드에서 존재하기 때문에 시스템 전체 성능을 크게 떨어뜨리지 않는 것.

*/