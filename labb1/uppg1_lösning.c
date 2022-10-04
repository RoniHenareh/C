#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define IN 0
#define OUT 1

int main() {
    int p[2];
    if(pipe(p) == -1) {
        printf("Creating pipe failed!");
    }

    int pid = fork();    
    if(pid == 0) {     
        dup2(p[OUT], STDOUT_FILENO); 
        close(p[IN]);
        close(p[OUT]);
        char* args[] = {"ls", "/", NULL};
        execv("/bin/ls", args);
        
    } else {
        dup2(p[IN], STDIN_FILENO);
        close(p[IN]);
        close(p[OUT]);
        char* args[] = {"wc", "-l", NULL};
        execv("/bin/wc", args);     
    }

    return 0;
}