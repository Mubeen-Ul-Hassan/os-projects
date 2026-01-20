#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {

    pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) { // Child process
        printf("Child: My parent PID is %d\n", getppid());
        sleep(5);
        printf("Child: Now my parent PID is %d\n (I might be orphaned)\n", getppid());
        exit(EXIT_SUCCESS);
    } else { // Parent process
        printf("Parent: PID %d, I will exit before the child.\n", getppid());
        sleep(1);
        printf("Parent: Exiting now!\n");
        exit(EXIT_SUCCESS);
    }

    return 0;
}