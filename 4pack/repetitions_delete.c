#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define TABLE_LEN 1000003
#define MOD 1000003

typedef struct Node_s {
    unsigned int data;
    struct Node_s *next;
} Node;

unsigned int hash(unsigned int source) {
    return (unsigned int) source % MOD;
}

void addNode(Node **hash_table_node, unsigned int data) {
    Node *new_head = malloc(sizeof(Node));
    new_head->next = *hash_table_node;
    new_head->data = data;
    *hash_table_node = new_head;
}


int checkNode(Node **hash_table, unsigned int data) {
    unsigned int tmp_hash = hash(data);
    Node *tmp_chain_start = hash_table[tmp_hash];
    while (tmp_chain_start != NULL) {
        if (tmp_chain_start->data == data) {
            return 1;
        }
        tmp_chain_start = tmp_chain_start->next;
    }
    return 0;
}



Node *hash_table[TABLE_LEN] = {NULL};

int main(void) {
    FILE *input = fopen("input.bin", "rb");
    FILE *output = fopen("output.bin", "wb");

    unsigned int length, counter = 0;
    fread(&length, sizeof(unsigned int), 1, input);
    unsigned int *data = malloc(length * sizeof(unsigned int));
    fread(data, sizeof(unsigned int), length, input);

    fseek(output, 4, SEEK_CUR);
    for (int i = 0; i < length; i++) {
        if (checkNode(hash_table, data[i]) == 0) {
            addNode(&hash_table[hash(data[i])], data[i]);
            fwrite(&data[i], sizeof(unsigned int), 1, output);
            counter++;
        }
    }
    fseek(output, 0, SEEK_SET);
    fwrite(&counter, sizeof(unsigned int), 1, output);

    
    fclose(input);
    fclose(output);
}

