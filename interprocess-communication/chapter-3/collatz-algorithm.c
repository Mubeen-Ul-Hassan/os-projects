#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <limits.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>

#define SHM_NAME "/sequence_shm"
#define CHUNK_SIZE 4096

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
    printf("-- Number: %d\n", number);

    pid_t child_pid = fork();

    if (child_pid < 0)
    {
        perror("Fork Failed");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0)
    {
        int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
        ftruncate(fd, CHUNK_SIZE);
        char *write_ptr = mmap(NULL, CHUNK_SIZE, PROT_WRITE, MAP_SHARED, fd, 0);

        if (write_ptr == MAP_FAILED)
        {
            perror("mmap failed\n");
            close(fd);
            exit(EXIT_FAILURE);
        }
        
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
            write_ptr += sprintf(write_ptr, "%d ", n);
        }
        printf("-- Child process have computed the sequence.\n");
        close(fd);
        exit(EXIT_SUCCESS);
    } else
    {
        wait(NULL);
        int fd = shm_open(SHM_NAME, O_RDONLY, 0666);
        char *read_ptr = mmap(NULL, CHUNK_SIZE, PROT_READ, MAP_SHARED, fd, 0);

        if (read_ptr == MAP_FAILED)
        {
            perror("mmap failed\n");
            close(fd);
            exit(EXIT_FAILURE);
        }
        printf("-- Parent process reading the sequence.\n");
        printf("-- Sequence: %s\n", (char *)read_ptr);
        close(fd);
    }
    shm_unlink(SHM_NAME);

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