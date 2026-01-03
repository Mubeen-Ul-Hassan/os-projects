#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>

int find_token(char **words, const char *token)
{
    int pipe_index = -1;
    for (int i = 0; words[i] != NULL; i++) {
        if (strcmp(words[i], token) == 0) {
            pipe_index = i;
            break;
        }
    }
    return pipe_index;
}

void handle_redirection(char **args) 
{
    int token_index;

    token_index = find_token(args, ">"); // Output redirection '>'
    if (token_index != -1) {
        int fd = open(args[token_index + 1],
            O_WRONLY | O_CREAT | O_TRUNC, 
            0644);
        if ( fd < 0) {
            perror("Open: ");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDOUT_FILENO);
        close(fd);
        args[token_index] = NULL;
    }

    token_index = find_token(args, "<"); // Input redirection '<'
    if (token_index != -1) {
        int fd = open(args[token_index + 1], O_RDONLY);
        if ( fd < 0 ) {
            perror("Open: ");
            exit(EXIT_FAILURE);
        }
        dup2(fd, STDIN_FILENO);
        close(fd);
        args[token_index] = NULL;
    }

}

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
            break;
        }

        int p_index = find_token(words, "|");

        if (p_index == -1) {
            pid_t pid = fork();
            if (pid == 0) {
                handle_redirection(words);
                execvp(words[0], words);
                perror("Error: ");
                exit(EXIT_FAILURE);
            }
            waitpid(pid, NULL, 0);
        } else {
            char **cmd1 = &words[0];
            char **cmd2 = &words[p_index + 1];
            words[p_index] = NULL;

            int fd[2];
            pipe(fd);

            pid_t child_pid1 = fork();
            if (child_pid1 == 0) {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]); close(fd[1]);
                handle_redirection(cmd1);
                execvp(cmd1[0], cmd1);
                perror("Error: ");
                exit(EXIT_FAILURE);
            }

            pid_t child_pid2 = fork();
            if (child_pid2 == 0) {
                dup2(fd[0], STDIN_FILENO);
                close(fd[0]); close(fd[1]);
                handle_redirection(cmd2);
                execvp(cmd2[0], cmd2);
                perror("Error: ");
                exit(EXIT_FAILURE);
            }
            close(fd[0]); close(fd[1]);

            waitpid(child_pid1, NULL, 0);
            waitpid(child_pid2, NULL, 0);
        }
    }

    return 0;
}