// Simple Shell

#include <stdio.h>
#include <string.h>
#include <unistd.h> // for fork() and getpid()
#include <stdlib.h> // exit()
#include <sys/wait.h>
#include <stdbool.h> // defines true and false

char **input_token(char *input)
{
    char **tokens = (char **)malloc(20 * sizeof(char *));
    char *token;

    token = strtok(input, " \n");
    int index = 0;

    while (token != NULL)
    {
        tokens[index] = (token);
        token = strtok(NULL, " \n");
        index++;
    }

    tokens[index] = NULL;
    return tokens;
}

int main()
{
    char string[100];

    printf("Enter the string: ");
    fgets(string, sizeof(string), stdin);

    char **input = input_token(string);

    /*
    -- Print the tokens --
    printf("Tokens are: \n");
    for (int i = 0; input[i] != NULL; i++)
    {
        printf("%s", input[i]);
        printf(" ");
    }
    */
    // Fork()

    pid_t pid = fork(); // Create a child process

    if (pid == 0) // Child process
    {
        execvp(input[0], input);
        printf("Child PID: %d\n", getpid());
        _exit(0);
    }
    else
    {
        wait(NULL); // wait for child to exit
    }

    free(input); // Release dynamically allocate memory
    return 0;
}

/*
        strtok(arg1, arg2)
        arg1 - original string to be passed.
        arg2 - seprator using which we tokenize the string.
*/

/*
        fgets(argument1, argument2, argument3);
        arg1 - name of the array which will store the value
        arg2 - size of the input you want to take
        arg3 - source of the input
*/
