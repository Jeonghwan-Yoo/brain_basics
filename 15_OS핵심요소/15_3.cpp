#include <stdio.h>
#include <Windows.h>

int g_idx = 0;

unsigned int NewThread(void* pParam) {
	while (1) {
		g_idx++;
		Sleep(50);
	}
}

int main(int argc, char* argv[]) {
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)NewThread, 0, 0, NULL);
	while (1) {
		printf("g_idx:%d ", g_idx);
		printf("g_idx*2 = %d\n", g_idx * 2);
		Sleep(500);
	}
	return 1;
}