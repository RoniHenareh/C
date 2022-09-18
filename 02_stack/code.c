#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h> 

char global[] = "This is a global string";
const int read_only = 123456;

int main() {

	int pid = getpid(); // returns the process ID of the calling process

	foo: // foo is a term used by programmers as a placeholder for a value that can change
	printf("process id: %d\n", pid);

	// intressant skrivsätt, adresser:
	printf("global string: 0x%lx\n", (unsigned long)&global);
	printf("read only:  0x%lx\n", (unsigned long)&read_only);  
	printf("the code: 0x%lx\n", (unsigned long)&&foo); 

	// testa på linux sen
	printf("\n\n /proc/%d/maps \n\n", pid);

	char command[50];
	sprintf(command, "cat /proc/%d/maps", pid);
	system(command);  

	return 0;
}

