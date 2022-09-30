#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFFER_SIZE 100

int fd[2];
char read_message[BUFFER_SIZE];
char write_message[BUFFER_SIZE] = "Hello World";

// pipe: fd[0] för att läsa, fd[1] för att skriva

int main() {

    pipe(fd); // skapar pipe

    int test = fork();
    printf("test: %d\n", test);

    switch(test) {

        case -1: // fel
            break;

        case 0: // child

            close(fd[1]); // ska bara läsa så vi stänger skriva
            read(fd[0], read_message, BUFFER_SIZE);
            printf("The message is: %s\n", read_message);

            // fixa
            execl("/bin/ls", "/bin/ls", "/", "|", NULL); // execute ls / |

            break;

        default: // parent
            close(fd[0]); // ska bara skriva så vi stänger läsa
            write(fd[1], write_message, strlen(write_message) + 1);
            
            // fixa
            execl("/bin/ls", "/bin/ls", "wc -l", NULL); // execute wc -l

            break;
    }

    return 0;
}