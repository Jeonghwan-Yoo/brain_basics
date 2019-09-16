#include <stdio.h>

int __stdcall testfunc(int a, int b, ...) {
	return a + b;
}

int main(int argc, char* argv[]) {
	testfunc(10, 20, 30);
	return 1;
}