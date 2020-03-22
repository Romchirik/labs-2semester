#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#define SIZE 1000003

typedef struct node_s {
    uint64_t val;
    uint32_t position;
    struct node_s *next;
} Node;

Node *checkNode(Node *hash_table_node, uint32_t data) {
    Node *p = hash_table_node;
    while (p != NULL) {
        if (p->val == data)
            return p;
        p = p->next;
    }
    return NULL;
}

void addNode(Node **hash_tbale_node, uint32_t value, uint32_t posiition) {
    Node *head = (Node *) malloc(sizeof(Node));
    head->val = value;
    head->position = posiition;
    head->next = *hash_tbale_node;
    *hash_tbale_node = head;
}

uint64_t a, b, c, mod;

uint64_t getState(uint64_t state) {
    return (state * state * a + state * b + c) % mod;
}

Node *hash_table[SIZE] = {NULL};

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    uint64_t state = 1;
    uint32_t position = 0;
    scanf("%lld\n", &mod);
    scanf("%lld %lld %lld", &a, &b, &c);

    addNode(&hash_table[state % SIZE], state, position);
    position++;
    while (1){
        state = getState(state);
        Node* collision_found = checkNode(hash_table[state % SIZE], state);
        if(collision_found != NULL){
            printf("%d %d", collision_found->position, position);
            return 0;
        }
        addNode(&hash_table[state % SIZE], state, position);
        position++;
    }
}
