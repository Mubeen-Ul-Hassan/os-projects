// Simple Shell

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h> // exit()

int main()
{
    char string[20];

    printf("Enter the string: ");
    fgets(string, 20, stdin);
    printf("\nThe string is: %s", string);

    char *token;
    char delimiter[] = " ";

    token = strtok(string, delimiter);

    while (token)
    {
        printf("%s\n", token);
        token = strtok(NULL, delimiter); // "Null" to resume tokenizing from the previously saved the position.
    }

    // Fork start
    int pid;
    pid = fork();

    if (pid == 0)
    {
        printf("I am the child process\n");
    }

    printf("Process ID: %d\n", getpid());
    // Fork end

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