#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>

int main(void)
{

    bool running = true;
    while (running)
    {
        char args[50];
        char *words[10];

        printf("myshell > ");
        fgets(args, sizeof(args), stdin);

        // Remove trailing newline character
        args[strcspn(args, "\n")] = 0;

        // Split string by spaces
        char *token = strtok(args, " ");

        char index = 0;
        while (token != NULL) {
            words[index++] = token;
            token = strtok(NULL, " ");
        }
        words[index] = NULL;

        // Check for exit command
        if (strcmp(words[0], "exit") == 0) {
            running = false;
            break;
        }

        pid_t pid = fork();

        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
            execvp(words[0], words);
            perror("Error: ");
            exit(EXIT_FAILURE);
        }
        else {
            int status;
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}