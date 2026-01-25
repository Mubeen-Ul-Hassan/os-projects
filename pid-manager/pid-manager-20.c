#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define MIN_PID 300;
#define MAX_PID 5000;

typedef struct {
    uint64_t n_bytes; // Number of bytes in "bit" array
    uint64_t n_valid_bytes; // The actual number of bit used
    unsigned char *bits; // Array of bits
} bitmap_t;

bitmap_t allocate_map(uint64_t n_bits);
int allocate_pid(bitmap_t *bm);
int release_pid(bitmap_t *bm, int pid);
int append(int arr[], int arr_size, int val);
int remove_item(int arr[], int arr_size, int val);

int main(int argc, char *argv[]) {

    int initial_size = 1;
    int *allocated_pids = (int *)malloc(initial_size * sizeof(int));

    int size = MAX_PID - MIN_PID;
    bitmap_t bitm = allocate_map(size);
    
    for (int i = 0; i < 7; i++) 
    {
        int PID = allocate_pid(&bitm);
        append(allocated_pids, initial_size, PID);

        int new_size =  initial_size + 1;
        int *tmp = (int *)realloc(allocated_pids, new_size * sizeof(int));
        if (tmp == NULL)
        {
            printf("Memory Reallocation Failed\n");
            break;
        } else {
            allocated_pids = tmp;
            initial_size  = new_size;
        }
    }
    
    release_pid(&bitm, allocated_pids[1]); // Free the PID
    remove_item(allocated_pids, initial_size, allocated_pids[1]); // Flash the record from allocated PID list
    printf("Size: %d\n", initial_size);
    for (int i = 0; i < initial_size - 1; i++)
    {
        printf("PID: %d\n", allocated_pids[i]);
    }

    int busy_pids = 1;
    for (int i = 0; i < bitm.n_valid_bytes; i++) 
    {
        if (bitm.bits[i] == 1)
        {
            printf("Array PID: %d\n", bitm.bits[i]);
            busy_pids += 1;
        }
    }
    printf("Busy PIDs: %d\n", busy_pids);

    free(allocated_pids);
    free(bitm.bits);

    return 0;
}


/*
*   O means PID is free
*  1 means PID is in use
*/
bitmap_t allocate_map(uint64_t n_bits) {
    bitmap_t bm;
    bm.n_valid_bytes = n_bits;
    bm.n_bytes = (n_bits + 7) / 8;
    bm.bits = calloc(bm.n_bytes, 1);

    return bm;
}

int allocate_pid(bitmap_t *bm) {
    for (int i = 0; i < bm->n_valid_bytes; i++)
    {
        if (bm->bits[i] == 0)
        {
            bm->bits[i] = 1;
            return i + MIN_PID;
        }
    }
    return -1; // All PIDs are in used
}

int release_pid(bitmap_t *bm, int pid) {
    const int INDEX = pid - MIN_PID;
    if (bm->bits[INDEX] != 0)
    {
        bm->bits[INDEX] = 0;
        return 1;
    }
    return 0;
}


int append(int *arr, int arr_size, int val)
{   
    arr[arr_size - 1] = val;
    return 1;
}

int remove_item(int *arr, int arr_size, int val)
{
    const int INDEX = val - MIN_PID;
    if (arr[INDEX] == val)
    {
        arr[INDEX] = 0;
        for (int in = INDEX; in < INDEX; in++)
        {
            arr[in] = arr[in + 1];
            arr[in + 1] = 0;
        }
        return 1;
    }
    return 0;
}
