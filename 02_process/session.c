#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	int pid = fork();

	if (pid == 0) {
		int child = getpid();
		printf("child  (%d): session %d\n", child, getsid(child));
	} else {
		int parent = getpid();
		printf("parent (%d): session %d\n", parent, getsid(parent));    
	}
	
	return 0;
}

