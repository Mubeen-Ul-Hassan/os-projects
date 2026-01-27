#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>

void reverse_string(char *str);
void toggle_case(char *str);

int main(int argc, char *argv[])
{
    int forward_propagation[2]; // fd[0] is read end, fd[1] is write end
    int backward_propagation[2];

    char message[] = "Mubeen Ul Hassan";
    char buffer[100];

    if (pipe(forward_propagation) == -1 || pipe(backward_propagation) == -1)
    {
        perror("Pipe failed");
        exit(EXIT_FAILURE);
    }

    pid_t child_pid = fork();
    if (child_pid < 0)
    {
        perror("Fork Failed");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0)
    {
        close(forward_propagation[0]);
        write(forward_propagation[1], message, sizeof(message));
        printf("Child sent message: %s\n", message);
        close(forward_propagation[1]);

        // Read the message from parent
        close(backward_propagation[1]);
        read(backward_propagation[0], buffer, sizeof(buffer));
        printf("Child received: %s\n", buffer);
        close(backward_propagation[0]);

        exit(EXIT_SUCCESS);
    } else
    {
        // wait(NULL);

        close(forward_propagation[1]);
        read(forward_propagation[0], buffer, sizeof(buffer));
        reverse_string(buffer);
        toggle_case(buffer);
        printf("Parent received: %s\n", buffer);
        close(forward_propagation[0]);

        close(backward_propagation[0]);
        write(backward_propagation[1], buffer, sizeof(buffer));
        printf("Parent sent: %s\n", buffer);
        close(backward_propagation[1]);
    }   

    return 0;
}

void reverse_string(char *str)
{
    if (str == NULL)
    {
        return;
    }

    int start = 0;
    int end = strlen(str) - 1;
    char temp;

    while (start < end)
    {
        // swap characters
        temp = str[start];
        str[start] = str[end];
        str[end] = temp;

        // Move towards center
        start++;
        end--;
    }
}

void toggle_case(char *str)
{
    while(*str)
    {
        if (isupper(*str))
        {
            *str = tolower(*str);
        } else if (islower(*str))
        {
            *str = toupper(*str);
        }
        str++;
    }
}