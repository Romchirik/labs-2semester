#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

#define ARRAY_EL_SIZE 32

typedef unsigned int bitword;


bitword *bitsetCreate() {
    return calloc((UINT32_MAX / ARRAY_EL_SIZE) + 1, sizeof(bitword));
}


int bitsetGet(const bitword *arr, int idx) {
    return (arr[idx / ARRAY_EL_SIZE] >> (ARRAY_EL_SIZE - 1 - (idx % ARRAY_EL_SIZE))) & 1;
}

void bitsetSet(bitword *arr, unsigned int idx, unsigned int newval) {
    if (newval)
        arr[idx / ARRAY_EL_SIZE] = arr[idx / ARRAY_EL_SIZE] | (1 << (ARRAY_EL_SIZE - 1 - idx));
    else
        arr[idx / ARRAY_EL_SIZE] = arr[idx / ARRAY_EL_SIZE] & ~(1 << (ARRAY_EL_SIZE - 1 - idx));
}


int main() {
    FILE *input = fopen("input.bin", "r");
    FILE *output = fopen("output.bin", "w");

    unsigned int length;
    fread(&length, sizeof(unsigned int), 1, input);
    uint32_t *data = calloc(length, sizeof(unsigned int));
    bitword *hash_table = bitsetCreate();
    fread(data, sizeof(unsigned int), length, input);

    bitsetSet(hash_table, 1, 1);



    fclose(input);
    fclose(output);
}
