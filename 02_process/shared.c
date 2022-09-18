#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
	int x = 0;
	int pid = fork();

	if (pid == 0) {
		x = 42;
		sleep(1);
		printf("\n  Hello, I'm the child and x is  %d\n", x);
	} else {
		x = 13;
		sleep(1);
		printf("\n  Hello, I'm the parent and x is  %d\n", x);
	}

	return 0;
}

