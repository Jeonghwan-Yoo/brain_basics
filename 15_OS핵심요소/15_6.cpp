#include <stdio.h>
#include <Windows.h>

int g_A = 0;
int g_B = 0;
CRITICAL_SECTION g_csA;
CRITICAL_SECTION g_csB;

unsigned int NewThread(void* pParam) {
	while (1) {
		EnterCriticalSection(&g_csA);
		EnterCriticalSection(&g_csB);

		g_A++;
		g_B++;

		LeaveCriticalSection(&g_csB);
		LeaveCriticalSection(&g_csA);

		Sleep(50);
	}
}

int main(int argc, char* argv[]) {
	InitializeCriticalSection(&g_csB);
	InitializeCriticalSection(&g_csA);

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)NewThread, 0, 0, NULL);

	while (1) {
		EnterCriticalSection(&g_csB);
		EnterCriticalSection(&g_csA);

		printf("A : %d\n", g_A);
		printf("B : %d\n", g_B);

		LeaveCriticalSection(&g_csA);
		LeaveCriticalSection(&g_csB);

		Sleep(50);
	}
	DeleteCriticalSection(&g_csA);
	DeleteCriticalSection(&g_csB);

	return 1;
}