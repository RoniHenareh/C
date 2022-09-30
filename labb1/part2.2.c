// Consumer

#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <mqueue.h> 

#define MAX_SIZE 100
#define MAX_NUM_MESSAGE 100
#define MQ_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

char *my_mq = "/mymq";
char buf[MAX_SIZE];
mqd_t mqd;

struct mq_attr attr; 

int main() {

    // queue attributes
    attr.mq_maxmsg = MAX_NUM_MESSAGE;
    attr.mq_msgsize = MAX_SIZE;

    // create message queue
    mqd = mq_open(my_mq, O_RDONLY | O_CREAT, MQ_MODE, &attr);

    // read from the queue
    mq_receive(mqd, buf, sizeof(buf), NULL);
    printf("The message is: %s\n", buf);

    int count = 0;
    for (int i = 0; buf[i] != '\0'; i++) {

        if (buf[i] == ' ' && buf[i+1] != ' ')

            count++;    

    }

    printf("Number of words in given string are: %d\n", count + 1);
    
    // close 
    mq_close(mqd);
    
    return 0;	
}

