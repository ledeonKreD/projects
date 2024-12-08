#include <stdio.h>

int main() {
	// 1 0 1 0 1 0 1 0 -> 170
	// 0 1 0 1 0 1 0 1 -> 85
	int a = 170, b = 85;
	printf("a = %u\t b = %u\n", a, b);
	//should be 255
	printf("a & b = %u\n", a ^ b);
	return 0;
}
