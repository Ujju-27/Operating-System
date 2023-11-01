#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<sys/wait.h>
#include <unistd.h>

int main() {

	printf("Name - Ujjawal Singh Tolia Section - J Class Rollno - 69\n\n");
    key_t key;
    int shmid;
    char *shmaddr;

    // Generate a unique key for the shared memory segment
    key = ftok("/tmp", 'A');

    // Create a shared memory segment with the given key
    shmid = shmget(key, 1024, 0666 | IPC_CREAT);

    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Attach the shared memory segment to this process
    shmaddr = (char *)shmat(shmid, (void *)0, 0);

    if (shmaddr == (char *)(-1)) {
        perror("shmat");
        exit(1);
    }

    // Parent process writes to shared memory
    strcpy(shmaddr, "Hello from the parent process!");

    // Fork a child process
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(1);
    }

    if (pid == 0) {
        // Child process reads from shared memory
        printf("Child process read: %s\n", shmaddr);

        // Detach from the shared memory segment
        shmdt(shmaddr);
    } else {
        // Parent process waits for the child to finish
        wait(NULL);

        // Detach from the shared memory segment
        shmdt(shmaddr);

        // Remove the shared memory segment
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}


//hello
