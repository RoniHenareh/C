#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// pipe: fd[0] för att läsa, fd[1] för att skriva

int main() {

    int status;
    pid_t pid;
    int fd[2];

    pipe(fd); // skapar pipe

    pid = fork();
    //printf("test: %d\n", pid);

    switch(pid) {

        case -1: // felhantering
            break;

        case 0: // child

            dup2(fd[1], STDOUT_FILENO); // agerar |
            close(fd[1]); 
            close(fd[0]);
           
            // fixa
            execl("/bin/ls", "/bin/ls", "/", NULL); // execute ls / 

            //char* args1[] = {"ls", "/", NULL};
            //execv("/bin/ls", args1);

            break;

        default: // parent

            pid = wait(&status); // wait for child process

            dup2(fd[0], STDOUT_FILENO);
            close(fd[0]);
            close (fd[1]);
           
            // fixa
            execl("/bin/wc", "/bin/wc", "-l", NULL); // execute wc -l

            //char* args2[] = {"wc", "-l", NULL};
            //execv("/bin/wc", args2);  

            break;
    }

    return 0;
}