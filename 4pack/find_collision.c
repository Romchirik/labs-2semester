#define SIZE 100000

#include<stdlib.h>
#include<stdio.h>
#include<inttypes.h>

typedef struct node_s {
    uint32_t val;
    uint32_t key;
    struct node_s *next;
} Node;

uint32_t *check(Node *hash_table_node, uint32_t data) {
    Node *p = hash_table_node;
    while (p != NULL) {
        if (p->key == data)
            return &p->val;
        p = p->next;
    }
    return NULL;
}

void add(Node **hash_tbale_node, uint32_t key, uint32_t value) {
    Node *head = (Node *) malloc(sizeof(Node));
    head->val = value;
    head->key = key;
    head->next = *hash_tbale_node;
    *hash_tbale_node = head;
}

Node *hash_table[SIZE] = {NULL};

int main() {
    uint32_t number = 1, hash;
    printf("eval %u\n", number);
    fflush(stdout);
    scanf("%u", &hash);
    add(&hash_table[hash % SIZE], hash, number);
    while (1) {
        number++;
        printf("eval %u\n", number);
        fflush(stdout);
        scanf("%u", &hash);
        uint32_t *collision_found = check(hash_table[hash % SIZE], hash);
        if (collision_found != NULL) {
            printf("answer %u %u\n", *collision_found, number);
            fflush(stdout);
            return 0;
        }
        add(&hash_table[hash % SIZE], hash, number);
    }
    return 0;
}
