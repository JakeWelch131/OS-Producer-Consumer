#ifndef STRUCTURE_HPP
#define STRUCTURE_HPP

#include <unistd.h>
#include <time.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>


struct buffer{                         // structure to be accessed by pointer and to be shared between the two processes
    int data[2];                       // our table in producer-consumer
    int count;                         // counter for location in table
    sem_t semFull;                     // semaphore to represent how many slots are full in table
    sem_t semEmpty;                    // semaphore to represent how many slots are empty in table
};

#endif