#include <stdio.h>

int readable(char* inputPath);

int main(void) {
	char* path = "test";//"/Users/Spencer/Desktop/testDir1";

	printf("readable files = %d\n", readable(path));

	return 0;
}