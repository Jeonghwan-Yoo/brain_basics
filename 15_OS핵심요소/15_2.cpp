#include <stdio.h>
#include <Windows.h>

int g_idx = 0;

unsigned int NewThread(void* pParam) {
	while (1) {
		g_idx++;
	}
}

int main(int argc, char* argv[]) {
	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)NewThread, 0, 0, NULL);
	while (1) {
		printf("g_idx:%d\n", g_idx++);
	}
	return 1;
}