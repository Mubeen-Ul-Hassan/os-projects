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
        printf("Parent: Waiting for child to finish...\n");
        wait(NULL);
        printf("Parent: Child is done, now I can finish too. \n");
    }

    return 0;
}