#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

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

void heapifyUp(Heap *target, int start_index) {
    while (target->data_arr[start_index] < target->data_arr[(start_index - 1) / 2]) {
        swap(&target->data_arr[start_index], &target->data_arr[(start_index - 1) / 2]);
        start_index = (start_index - 1) / 2;
    }
}

void heapifyDown(Heap *target, int start_index) {
    while (2 * start_index + 1 < target->length) {
        int left = 2 * start_index + 1;
        int right = 2 * start_index + 2;
        int tmp = left;

        if (right < target->length && (target->data_arr[right] < target->data_arr[left])) tmp = right;
        if (target->data_arr[start_index] <= target->data_arr[tmp]) break;

        swap(&target->data_arr[start_index], &target->data_arr[tmp]);
        start_index = tmp;
    }
}

int getMinHeap(Heap *target) {
    if (target->length == 0) return INT32_MIN; //errors handler
    int tmp = target->data_arr[0];
    target->data_arr[0] = target->data_arr[target->length - 1];
    target->length--;
    heapifyDown(target, 0);
    return tmp;
}

void insertCellHeap(Heap *target, int data) {
    target->data_arr[target->length] = data;
    target->length++;
    heapifyUp(target, target->length - 1);
}


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int num_operations;
    scanf("%d", &num_operations);

    Heap *heap = createHeap(num_operations);
    heap->length = 0;

    for (int i = 0; i < num_operations; i++) {
        char command[5];
        scanf("%s ", command);
        switch (command[1]) {
            case 'u': {
                int tmp;
                scanf("%d\n", &tmp);
                insertCellHeap(heap, tmp);
                break;
            }
            case 'o': {
                int tmp = getMinHeap(heap);
                if (tmp == INT32_MIN) printf("Heap is empty\n");
                else printf("%d\n", tmp);
                break;
            }
        }
    }
}
