#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {

    pid_t child_pid = fork();

    if (child_pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        printf("Child: Starting working...\n");
        sleep(2);
        printf("Child: Work finished!\n");
        exit(EXIT_SUCCESS);
    } else {
        // int status;
        printf("Parent: Waiting for child to finish...\n");
        // wait(&status);
        sleep(10); // Parent sleeps so child can become zombie.
        printf("Parent: Child is done, now I can finish too. \n");
    }

    return 0;
}