#include<stdlib.h>
#include<stdio.h>
#include<inttypes.h>
#include <memory.h>
#include <string.h>

#define SIZE 1000003

typedef struct node_s {
    int born_year;
    char name[31];
    char country[11];
    struct node_s *next;
} Node;

uint32_t hash(const char *source_string, int length) {
    int p = 31;
    uint32_t hash = 0, p_pow = 1;

    for (int i = 0; i < 30; i++) {
        hash += (source_string[i] + 1) * p_pow;
        p_pow *= p;
    }
    return hash;
}

Node *checkNode(Node *hash_table_node, char *name) {
    Node *p = hash_table_node;
    while (p != NULL) {
        if (strcmp(p->name, name) == 0)
            return p;
        p = p->next;
    }
    return NULL;
}

void addNode(Node **hash_table_node, int born_date, char *name, char *country) {
    Node *head = (Node *) malloc(sizeof(Node));
    head->born_year = born_date;
    memcpy(head->name, name, 31);
    memcpy(head->country, country, 11);
    head->next = *hash_table_node;
    *hash_table_node = head;
}

Node *hash_table[SIZE];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int num_actors;
    int num_movies;

    scanf("%d\n", &num_actors);
    for (int i = 0; i < num_actors; i++) {
        char tmp_name[31] = {0}, tmp_country[11] = {0};
        int tmp_year;
        scanf("\n%*c%[^\"]%*c %d %*c%[^\"]%*c", tmp_name, &tmp_year, tmp_country);

        uint32_t tmp_hash = hash(tmp_name, 31) % SIZE;
        addNode(&hash_table[tmp_hash], tmp_year, tmp_name, tmp_country);
    }

    scanf("%d\n", &num_movies);

    for (int i = 0; i < num_movies; i++) {
        char tmp_name[31] = {0}, movie_name[20] = {0};
        scanf("\n%*c%[^\"]%*c %*c%[^\"]%*c", tmp_name, movie_name);

        uint32_t tmp_hash = hash(tmp_name, 31) % SIZE;

        Node *tmp_node = hash_table[tmp_hash];
        while (tmp_node != NULL) {
            if (strcmp(tmp_node->name, tmp_name) == 0){
                printf("\"%s\" %d \"%s\" \"%s\" \"%s\"\n", \
                    tmp_name, tmp_node->born_year, tmp_node->country, tmp_name, movie_name);
            }
            tmp_node = tmp_node->next;
        }
    }

    return 0;
}
