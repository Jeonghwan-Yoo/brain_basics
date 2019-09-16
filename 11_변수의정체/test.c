#include <stdlib.h>
#include <conio.h>
#include <stdio.h>

int compare_ints(const void* a, const void* b) {
	int* arg1 = (int*)a;
	int* arg2 = (int*)b;

	if (*arg1 < *arg2)
		return -1;
	else if (*arg1 == *arg2)
		return 0;
	else
		return 1;
}

int main(int argc, char* argv[]) {
	int array[] = { -2,99,0,-743,2,3,4 };
	int array_size = 7;
	int i;

	printf("Before sorting:");
	for (i = 0;i < array_size;i++) {
		printf("%d ", array[i]);
	}
	printf("\n");

	qsort(array, array_size, sizeof(int), compare_ints);

	printf("After sorting:");
	for (i = 0;i < array_size;i++) {
		printf("%d ", array[i]);
	}
	printf("\n");

	getch();

	return 0;
}