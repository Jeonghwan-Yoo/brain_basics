#include <stdio.h>

int g_idx = 0;

int main(int argc, char* argv[]) {
	while (1) {
		printf("g_idx : %d\n", g_idx);
		g_idx++;
	}
	return 1;
}