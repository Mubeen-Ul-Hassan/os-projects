#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* read_from_file(char *filename);
void populate_sudoku_board(int input_array, int target_array);

int sudoku[9][9]; // sudoku board

typedef struct {
    int row;
    int column;
    int thread_index;
} parameters;

// 1 --> valid 
// 0 --> invalid
int results[27];

// row check thread
// column check thread
// subgrid-check thread
int main(int argc, char *argv[])
{

    char *file_path = "./puzzle.txt";
    int *numbers = read_from_file(file_path); 

    for (int i = 0; i < 81; i++)
    {
        printf("%d ", numbers[i]);
    }

    free(numbers);
    return 0;
}

int* read_from_file(char *file_path)
{
    FILE *fptr;
    char line[255];

    int capacity = 81;
    int *num_array = malloc(capacity * sizeof(int));
    int index = 0;

    fptr = fopen(file_path, "r");

    while (fgets(line, sizeof(line), fptr) != NULL)
    {
        for (int i = 0; line[i] != '\0'; i+=2)
        {
            int num = atoi(&line[i]);
            num_array[index] = num;
            index++;
        }
    }

    fclose(fptr);
    return num_array;
}