#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* read_from_file(char *filename);
void populate_sudoku_board(int *input_array, int target_array[9][9]);

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
    populate_sudoku_board(numbers, sudoku);

    for (int i = 0; i < 9; i++)
    {
        printf("%d ", sudoku[0][i]);
    }
    printf("\n");

    free(numbers);
    return 0;
}

void populate_sudoku_board(int *input_array, int target_array[9][9])
{
    int index = 0;

    for (int row = 0; row < 9; row++)
    {
        for (int column = 0; column < 9; column++)
        {
            target_array[row][column] = input_array[index++];
        }
    }
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