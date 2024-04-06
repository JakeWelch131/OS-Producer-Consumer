# OS-Producer-Consumer
The producer generates items and puts items onto the table. The consumer will pick up items. The table can only hold two items at the same time. When the table is complete, the producer will wait. When there are no items, the consumer will wait. We use semaphores to synchronize producer and consumer.  Mutual exclusion should be considered. Shared memory is used for the “table”.

# Summary of files
struct.h defines the struct "buffer" which will be used in shared memory in order for both producer and consumer to interact with.\
producer.c creates and initializes the semaphores that are used to synchronize the access of the critical section. Producer also is responsible for filling the "table" with integers when the table is empty.\
consumer.c selects the current item on the table and takes it off. It is then output to the terminal.\

# Extra notes
Project required for this program to be developed in a Linux environment. You may need to be within this environment to run this code.

# Compilation
To compile both files, type the commands below:\
$ gcc producer.c -pthread -lrt -o producer\
$ gcc consumer.c -pthread -lrt -o consumer\
$ ./producer & ./consumer &\
