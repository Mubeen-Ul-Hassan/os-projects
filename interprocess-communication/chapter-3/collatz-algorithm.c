#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>

int integer(char *num);
void print_sequence(int *arr, int arr_size);

int main(int argc, char *argv[])
{
    int number = integer(argv[1]);

    if ( number < 0) 
    {
        printf("ERROR: PositiveIntegerOnly\n");
        exit(EXIT_FAILURE);
    }
    printf("Number: %d\n", number);

    pid_t child_pid = fork();
    
    if (child_pid < 0)
    {
        perror("Fork Failed");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0)
    {
        int sequence_arr[number + 1];
        sequence_arr[0] = number;
        
        int index = 1;
        int n = number;
        while(n != 1)
        {
            if (n % 2 == 0)
            {
                n = n / 2;
            } else {
                n = (3 * n) + 1;
            }
            sequence_arr[index] = n;
            index++;
        }
        print_sequence(sequence_arr, index);
    } else
    {
        wait(NULL);
    }

    return 0;
}

int integer(char *num)
{
    char *endptr;
    errno = 0;

    long number = strtol(num, &endptr, 10);

    if (endptr == num || *endptr != '\0' || errno != 0) 
    {
        printf("Invalid input or conversion error occured. \n");
        return 1;
    }

    if (number > INT_MAX || number < INT_MIN) {
        printf("Number out of the integer ranger. \n");
        return 1;
    }

    return (int) number;
}

void print_sequence(int *arr, int arr_size)
{
    for (int i = 0; i < arr_size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}