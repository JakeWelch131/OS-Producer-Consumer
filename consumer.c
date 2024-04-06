#include "struct.h"


int main(){

    struct buffer *shmp;                                                            // declare buffer pointer

    sleep(1);                                                                       //to allow producer to producer before consumer runs

    const char* shmPtr = "/sharedMemObject";                                        // used as the name identifier for shared memory object

    
    int fd = shm_open(shmPtr, O_RDWR, S_IRUSR | S_IWUSR);                           // opens a shared memory object (named the value of shmPtr) that is able to read or write
    if (fd == -1){
        perror("Consumer");
        printf("Consumer: failed to open shared memory\n");                         // error checking
        exit(0);    
    }

    shmp = mmap(NULL, sizeof(*shmp), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);    // maps a shared mem obj into the address space of the consumer process. allows consumer to access shared mem
    if(shmp == MAP_FAILED){
        printf("Consumer: map failed\n");
        exit(0);
    } 

    

    for(int i = 0; i < 10; ++i){                                                    // runs 10 times so terminal is easier to read

        sem_wait(&shmp->semFull);                                                   // blocks if semFull's value is 0 (no items on table). once item become's available semFull will decrement (shows item will be taken off table)
        

        // Critical section
        shmp->count--;                                                              // represents consumption 
        int Y = shmp->data[shmp->count];                                            // accesses item to be consumed in shared memory

        /*
        printf("Consumer: Buffer content is ");
        for(int j = 0; j < 2; ++j){                                                 // used for debugging
            printf("%d %s", shmp->data[j], " ");
        }*/

        shmp->data[shmp->count] = 0;                                                // sets item that was consumed to 0 to represent it being taken off table
        
        printf("%s %d\n", "Consumed: ", Y);                                         // prints item consumed


        sem_post(&shmp->semEmpty);                                                  // increments semEmpty to signal that item has been consumed
    }

    shm_unlink(shmPtr);
    exit(EXIT_SUCCESS);
}