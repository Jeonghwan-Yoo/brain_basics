#include <stdio.h>
#include <Windows.h>

int g_idx = 0;
CRITICAL_SECTION g_csFor_g_idx;

unsigned int NewThread(void* pParam) {
	while (1) {
		EnterCriticalSection(&g_csFor_g_idx); //
		g_idx++;
		LeaveCriticalSection(&g_csFor_g_idx); //
		Sleep(50);
	}
}

int main(int argc, char* argv[]) {
	InitializeCriticalSection(&g_csFor_g_idx); //
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)NewThread, 0, 0, NULL);
	while (1) {
		EnterCriticalSection(&g_csFor_g_idx); //
		printf("g_idx:%d ", g_idx);
		printf("g_idx*2 = %d\n", g_idx * 2);
		Sleep(500);
		LeaveCriticalSection(&g_csFor_g_idx); //
	}
	DeleteCriticalSection(&g_csFor_g_idx); //
	return 1;
}