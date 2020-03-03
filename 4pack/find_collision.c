#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#define TABLE_LEN 1000003
#define MOD 1000003


typedef struct Node_s {
    uint32_t hash;
    uint32_t data;
    struct Node_s *next;
} Node;


void addNode(Node **hash_table_node, uint32_t data, uint32_t hash) {
    Node *new_head = malloc(sizeof(Node));
    new_head->next = *hash_table_node;
    new_head->data = data;
    new_head->hash = hash;
    *hash_table_node = new_head;
}


Node *checkNode(Node *hash_table_node, uint32_t hash) {
    Node *tmp_node = hash_table_node;
    while (tmp_node != NULL) {
        if (tmp_node->hash == hash) {
            return tmp_node;
        }
    }
    return NULL;
}


Node *hash_table[TABLE_LEN] = {NULL};

int main(void) {
    uint32_t number = 1, hash;
    printf("eval %d\n", number);
    fflush(stdout);
    scanf("%u", &hash);
    addNode(&hash_table[hash % MOD], number, hash);
    while (1){
        number++;
        printf("eval %d\n", number);
        fflush(stdout);
        scanf("%u", &hash);
        Node *tmp_node = checkNode(hash_table[hash % MOD], hash);
        if (tmp_node != NULL){
            printf("answer %u %u\n", tmp_node->data, number);
            fflush(stdout);
            return 0;
        }
        addNode(&hash_table[hash % MOD], number, hash);
    }
    return 0;
}

