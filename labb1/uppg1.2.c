#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

// version 2, saknar wait och switch men funkar

int main() {
    
    int fd[2];
    pid_t pid;

    if(pipe(fd) == -1) {
        printf("Creating pipe failed!");
    }

    pid = fork();   

    if(pid == 0) {     

        dup2(fd[1], STDOUT_FILENO); 
        close(fd[0]);
        close(fd[0]);

        execl("/bin/ls", "/bin/ls", "/", NULL); // execute ls / 
        
    } else {

        dup2(fd[0], STDIN_FILENO);
        close(fd[0]);
        close(fd[1]);

        execl("/bin/wc", "/bin/wc", "-l", NULL); // execute wc -l

    }

    return 0;
}