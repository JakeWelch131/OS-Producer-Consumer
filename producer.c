#include "struct.h"
int main(){

    struct buffer *shmp;
    

    const char* shmPtr = "/sharedMemObject";                                            // used as the name identifier for shared memory object


    shm_unlink(shmPtr);                                                                 // ensures any shared mem obj is removed before new creation
    int fd = shm_open(shmPtr, O_CREAT | O_EXCL | O_RDWR, S_IRUSR | S_IWUSR);            // opens a shared memory object (named the value of shmPtr) that is able to read or write

    if (fd == -1){
        printf("Producer: failed to open shared memory\n");                                                         // error checking
        exit(0);
    }
      

    if(ftruncate(fd, sizeof(struct buffer)) == -1){                                     // sets size of the shared mem obj
        printf("Producer: failed to truncate shared mem\n");
        exit(0);
    }


    shmp = mmap(NULL, sizeof(*shmp), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);        // maps a shared mem obj into the address space of the consumer process. allows consumer to access shared mem


    if(shmp == MAP_FAILED){
        perror("Producer: ");
        printf("Producer: mapping failed\n");
        exit(0);
    }  

    //Initializes semaphores shared between producer and consumer through shared memory

    if (sem_init(&shmp->semFull, 1, 0) == -1){                                          // semFull initialized to 0 because we want 0 full slots to begin with
        printf("Producer: semFull did not initialize\n");
        exit(0);
    } 
    if (sem_init(&shmp->semEmpty, 1, 2) == -1){                                         // semEmpty initialized to 2 because we want 2 empty slots to begin with
        printf("Producer: semEmpty did not initialize\n");
        exit(0);
    } 
    
    
        
    srand(time(NULL)); //random seed


    for(int i = 0; i < 10; ++i){                                                        // runs 10 times so terminal is easier to read

        sem_wait(&shmp->semEmpty);                                                      // blocks if semEmpty's value is 0 (table is full). once item is consumed sumEmpty will decrement (shows item will be put on table)

        int X = rand() % 100;                                                           // generate random number

        // Critical section
        shmp->data[shmp->count] = X;                                                    // sets random number to the slot in shared buffer
        printf("Produced: %d\n", shmp->data[shmp->count]);                              // outputs number produced to the terminal
        
        shmp->count++;                                                                  // increment count 
        
                                                                     
        sem_post(&shmp->semFull);                                                       // increments semFull to signal that item has been produced

    }

    exit(EXIT_SUCCESS);
}