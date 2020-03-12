#include <stdio.h>
#include <stdlib.h>


typedef struct Item_s {
    int data;
    int heap_index;
} Item;

typedef struct Heap_item_s {
    int data;
    int source_idx;
} Heap_item;

typedef struct Heap_s {
    int length;
    Heap_item *data_arr;
} Heap;

void swapHeapItems(Heap_item *a, Heap_item *b) {
    Heap_item tmp = *a;
    *a = *b;
    *b = tmp;
}

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

Heap *createHeap(int max_len) {
    Heap *tmp = malloc(sizeof(Heap *));
    tmp->data_arr = malloc(sizeof(Heap_item) * max_len);
    return tmp;
}

void heapifyUp(Heap *target, int start_index, Item *template) {
    while (target->data_arr[start_index].data > target->data_arr[(start_index - 1) / 2].data) {

        int source_idx1 = target->data_arr[start_index].source_idx;
        int source_idx2 = target->data_arr[(start_index - 1) / 2].source_idx;

        swap(&template[source_idx1].heap_index, &template[source_idx2].heap_index);
        swapHeapItems(&target->data_arr[start_index], &target->data_arr[(start_index - 1) / 2]);

        start_index = (start_index - 1) / 2;
    }
}

void heapifyDown(Heap *target, int start_index, Item *template) {
    while (2 * start_index + 1 < target->length) {
        int left = 2 * start_index + 1;
        int right = 2 * start_index + 2;
        int tmp = right;

        if (left <= target->length && (target->data_arr[right].data < target->data_arr[left].data))
            tmp = left;
        if (target->data_arr[start_index].data >= target->data_arr[tmp].data)
            break;

        int source_idx1 = target->data_arr[start_index].source_idx;
        int source_idx2 = target->data_arr[tmp].source_idx;

        swap(&template[source_idx1].heap_index, &template[source_idx2].heap_index);
        swapHeapItems(&target->data_arr[start_index], &target->data_arr[tmp]);
        start_index = tmp;
    }
}


void insertCellHeap(Heap *target, Item *template, int idx) {
    target->data_arr[target->length].data = template[idx].data;
    target->data_arr[target->length].source_idx = idx;
    template[idx].heap_index = target->length;
    heapifyUp(target, target->length, template);
    target->length++;
}

void removeCell(Heap *target, Item *template, int idx) {
    int rm_idx = template[idx].heap_index;
    int tmp = target->data_arr[rm_idx].data;

    if(rm_idx + 1 >= target->length){
        target->length--;
        return;
    }
    target->data_arr[rm_idx] = target->data_arr[target->length - 1];
    template[target->data_arr[rm_idx].source_idx].heap_index = rm_idx;

    target->length--;

    if (target->data_arr[rm_idx].data == tmp) {
        return;
    }
    if (target->data_arr[rm_idx].data > tmp)
        heapifyUp(target, rm_idx, template);
    else
        heapifyDown(target, rm_idx, template);

}

int main(int num, char **args) {
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);

    int length, left = 0, right = 0;
    scanf("%d", &length);
    Item *template = malloc(sizeof(Item) * length);

    for (int i = 0; i < length; i++) {
        scanf("%d", &template[i].data);
        template[i].heap_index = -1;
    }

    Heap *heap = createHeap(length);
    heap->length = 0;

    for (int i = 0; i < 2 * length; i++) {
        char command;
        scanf("%c ", &command);
        switch (command) {
            case 'R': {
                right++;
                insertCellHeap(heap, template, right - 1);
                printf("%d\n", heap->data_arr[0].data);
                break;
            }
            case 'L': {
                left++;
                removeCell(heap, template, left - 1);
                printf("%d\n", heap->data_arr[0].data);
                break;

            }
        }
    }
}
