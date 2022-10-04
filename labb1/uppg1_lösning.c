#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

//#define IN 0
//#define OUT 1

int main() {
    
    int p[2];

    pid_t pid;
    //pid = fork();
    
    if(pipe(p) == -1) {
        printf("Creating pipe failed!");
    }

    pid = fork();   

    if(pid == 0) {     

        dup2(p[1], STDOUT_FILENO); 
        close(p[0]);
        close(p[0]);

        //char* args[] = {"ls", "/", NULL};
        //execv("/bin/ls", args);

        execl("/bin/ls", "/bin/ls", "/", NULL); // execute ls / 
        
    } else {
        dup2(p[0], STDIN_FILENO);
        close(p[0]);
        close(p[1]);

        //char* args[] = {"wc", "-l", NULL};
        //execv("/bin/wc", args);   

        execl("/bin/wc", "/bin/wc", "-l", NULL); // execute wc -l

    }

    return 0;
}