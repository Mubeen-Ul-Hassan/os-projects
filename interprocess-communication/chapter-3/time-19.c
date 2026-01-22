#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define SHM_NAME "/time_shm"
#define SIZE 4096

struct shm_time {
    time_t tv_sec;
    suseconds_t tv_usec;
};

int main(int argc, char *argv[]) {
    struct timeval start, end;
    char *words[10];
    
    int index = 0;
    while (index < argc) {
        words[index] = argv[index + 1];
        index++;
    }
    
    pid_t child_pid = fork();
    if (child_pid < 0) {
        perror("Fork Failed");
        exit(EXIT_FAILURE);
    } else if (child_pid == 0) {
        int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
        ftruncate(fd, SIZE);
        struct shm_time *ptr_write = mmap(NULL, SIZE, PROT_WRITE, MAP_SHARED, fd, 0);

        gettimeofday(&start, NULL);

        ptr_write->tv_sec = start.tv_sec;
        ptr_write->tv_usec = start.tv_usec;

        execvp(words[0], words);

        munmap(ptr_write, SIZE);
        close(fd);
        exit(EXIT_SUCCESS);
    } else {
        wait(NULL);
        gettimeofday(&end, NULL);
        int fd = shm_open(SHM_NAME, O_RDONLY, 0666);
        struct shm_time *ptr_read = mmap(NULL, SIZE, PROT_READ, MAP_SHARED, fd, 0);

        double time_taken = (end.tv_sec - ptr_read->tv_sec) + (end.tv_usec - ptr_read->tv_usec) / 1e6;
        printf("Elapsed time: %f\n", time_taken);

        munmap(ptr_read, SIZE);
        close(fd);
    }
    shm_unlink(SHM_NAME);

    return 0;
}