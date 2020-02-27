#include <stdio.h>
#include <stdlib.h>

typedef struct Heap_s {
    int length;
    int *data_arr;
} Heap;

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

Heap *createHeap(int max_len) {
    Heap *tmp = malloc(sizeof(Heap *));
    tmp->data_arr = malloc(sizeof(int) * max_len);
    return tmp;
}

void heapify(int *target, int length, int finish_index) {
    int largest = finish_index;

    int left = 2 * finish_index + 1;
    int right = 2 * finish_index + 2;


    if (left < length && target[left] > target[largest])
        largest = left;

    if (right < length && target[right] > target[largest])
        largest = right;

    if (largest != finish_index) {
        swap(&target[finish_index], &target[largest]);
        heapify(target, length, largest);
    }
}

void heapSort(int *target, int length) {
    for (int i = length / 2 - 1; i >= 0; i--) {
        heapify(target, length, i);
    }

    for (int i = length - 1; i >= 0; i--) {
        swap(&target[0], &target[i]);
        heapify(target, i, 0);
    }
}

int main() {
    FILE *input = fopen("input.bin", "rb");
    FILE *output = fopen("output.bin", "wb");

    int mass_length;
    fread(&mass_length, sizeof(int), 1, input);
    char error_flag;

    Heap *data = createHeap(mass_length);
    data->length = mass_length;
    fread(data->data_arr, sizeof(int), mass_length, input);

    heapSort(data->data_arr, data->length);

    fwrite(data->data_arr, sizeof(int), data->length, output);

    fclose(input);
    fclose(output);

    free(data->data_arr);
    free(data);
    
}
