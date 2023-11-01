#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	
	printf("Name - Ujjawal Singh Tolia Section - J Class Rollno - 69\n\n");
    pid_t child_pid;

    child_pid = fork(); // Create a child process

    if (child_pid == -1) {
        perror("fork");
        exit(1);
    }

    if (child_pid == 0) { // This code is executed by the child process
        printf("Child process: Executing 'date' command\n");
        // Use execl() to replace the child process with the "date" command
        execl("/bin/date", "date", NULL);

        // If execl() fails, we reach this point
        perror("execl");
        exit(1);
    } else { // This code is executed by the parent process
        printf("Parent process: Executing 'ls' command\n");
        // Use execl() to replace the parent process with the "ls" command
        execl("/bin/ls", "ls", "-l", NULL);

        // If execl() fails, we reach this point
        perror("execl");
        exit(1);
    }

    // The following code is unreachable because execl() replaces the process
    printf("This code should not be reached.\n");

    return 0;
}

