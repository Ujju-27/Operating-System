//for Sending Process
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
int main()
{
    void *shared_memory;
    char buff[100];
    int shmid;
    shmid = shmget((key_t)1122, 1024, 0666 | IPC_CREAT);
    printf("key of shared memory is :: %d\n", shmid);
    shared_memory = shmat(shmid, NULL, 0);
    printf("process attached at :: %p\n", shared_memory);
    printf("enter some data to write to the shared memory\n");
    read(0, buff, 100);
    strcpy(shared_memory, buff);
    printf("you wrote :: %s\n", (char *)shared_memory);
}

// code for the reciever process
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <string.h>
int main()
{
    void *shared_memory;
    char buff[100];
    int shmid;
    shmid = shmget((key_t)1122, 1024, 0666);
    printf("key of shared memory is :: %d\n", shmid);
    shared_memory = shmat(shmid, NULL, 0);
    printf("process attached at:: %p\n", shared_memory);
    printf("data read from the memory is :: %s\n", (char *)shared_memory);
}
