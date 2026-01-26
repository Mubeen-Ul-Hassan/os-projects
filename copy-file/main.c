#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>


int main(int argc, char *argv[]) 
{
    char *src_path = argv[1];
    char *dest_path = argv[2];

    if (src_path == NULL || dest_path == NULL) {
        perror("Invalid parameters");
        exit(EXIT_FAILURE);
    }

    int src_fd = open(src_path, O_RDONLY);
    if (src_fd == -1) {
        perror("Error opening source file.");
        exit(EXIT_FAILURE);
    }

    int dest_fd = open(dest_path, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("Error opening destination file.");
        close(src_fd);
        exit(EXIT_FAILURE);
    }

    char buffer[1024];
    ssize_t bytes_read = 0;
    ssize_t bytes_written = 0;

    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0 ) {
        int bytes_written = write(dest_fd, buffer, bytes_read);    
    }

    if (bytes_read == -1) {
        perror("Error reading from source file.");
        close(src_fd);
        close(dest_fd);
        exit(EXIT_FAILURE);
    }

    if (bytes_written == -1) {
        perror("Error writing to destination file.");
        close(src_fd);
        close(dest_fd);
        exit(EXIT_FAILURE);
    }

    printf("File copied successfully.\n");
    close(src_fd);
    close(dest_fd);
    return 0;
}