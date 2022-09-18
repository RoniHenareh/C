/*
  This is an example of a stack overflow that will allow an intruder
  to change the secret password and get access. The example is of
  course far fetched and will not work if you're not trying to hack a
  machine from the eighties. 

  By a stroke of luck the real passwd aray is allocated above the
  given passwd on the stack and this is what we're going to
  exploit. The programmer also made an error that allows us to attac
  the system.

  In order for this to work you need to compile with 

  gcc -o overflow -fno-stack-protector overflow.c 

  This will turn of the stack smashing detection (which of course we
  should never do).

  When we insert the password we chose qqqqqqqq....... 

  Experiment as see how many you need before you actually start to
  overwrite the realPassword[20] array. If you feed in enough q:s the
  two buffers will both contain 20 q:s :-) 
*/

#include <signal.h>
#include <stdio.h>
#include <string.h>

int main(){
	char realPassword[20];
	char givenPassword[20];
                              
	strncpy(realPassword, "secret password", 20);

	/* this is where we error, we accept 60 chars (enough to
		overwrite the realPassword) */
	fgets(givenPassword, 60, stdin);

	if (0 == strncmp(givenPassword, realPassword, 20)) {
		printf("You have Root!\n");
	} else {
		printf("FAILURE!\n");
	}
	
	printf("given password: %s\n", givenPassword);
	printf(" real password: %s\n", realPassword);
	return 0;
}

