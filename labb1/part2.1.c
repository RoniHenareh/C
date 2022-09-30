// Producer

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h> 

#define MAX 100

struct  mq_attr attr;

char *my_mq = "/mymq";
mqd_t mqd;

int main() {

    attr.mq_flags=0;
    attr.mq_maxmsg=MAX;
    attr.mq_msgsize=8192;
    attr.mq_curmsgs=0;

    // file pointer
    FILE *filePointer ;
     
    // det vi skickar
    char message[MAX];

    // Open txt-file with fopen() and read
    filePointer = fopen("part2.txt", "r") ;
     
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

    // O_WRONLY (write only)
    mqd = mq_open("/mymq", O_CREAT|O_RDWR,0744,&attr);
    printf("detta ska inte bli -1: %i\n", mqd);

    mq_send(mqd, message, strlen(message) + 1, 0);
    
    mq_close(mqd);

	return 0;
}
