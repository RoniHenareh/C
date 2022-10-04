// Producer

#include <stdio.h>
#include <string.h> 
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h>     

#define MAX 100

struct  mq_attr attr;

char *my_mq = "/mymq";
mqd_t mqd, mqs;

int main() {

    struct  mq_attr attr = {

        .mq_flags=0,
        .mq_maxmsg=10,
        .mq_msgsize=MAX,
        .mq_curmsgs=0
    };

    // file pointer
    FILE *filePointer;
     
    // det vi skickar
    char message[MAX];

    // Open txt-file with fopen() and read
    filePointer = fopen("part2.txt", "r");
     
    // felhantera
    if (filePointer == NULL) {
        printf( "part2.txt file failed to open." );
    } else {
        printf("The file is now opened.\n") ;

        // Read the data from the file using fgets() method
        while( fgets(message, MAX, filePointer ) != NULL)
        {
            // Prints the data from the txt.file
            printf( "The data was: %s\n" , message);
        }
         
        // Closing the file using fclose()
        fclose(filePointer) ;

        printf("Data successfully read from part2.txt\n");
        printf("The file is now closed\n") ;
    }

   
    mqd = mq_open(my_mq, O_CREAT | O_WRONLY, 0644, &attr);
    printf("detta bör inte bli -1: %i\n", mqd);
    
    mqs = mq_send(mqd, message, strlen(message) + 1, 0);
    printf("detta bör inte bli -1: %i\n", mqs);

    mq_close(mqd);

	return 0;
}