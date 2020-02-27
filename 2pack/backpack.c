#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


typedef struct list {
    int weight;
    int cost;

} List;

List *items;
int *index;
int *answer;
int *totally_weight;
int *totally_cost;


void find_ans(int k, int s, int **D) {
    if (D[s][k] == 0)
        return;
    if (D[s][k - 1] == D[s][k])
        find_ans(k - 1, s, D);
    else {
        find_ans(k - 1, s - items[k].weight, D);
        answer[*index] = k;
        (*index)++;
        *totally_weight += items[k].weight;
        *totally_cost += items[k].cost;
    }


}


int main() {
    int N, W;
    totally_weight = (int *) malloc(sizeof(int));
    *totally_weight = 0;
    totally_cost = (int *) malloc(sizeof(int));
    *totally_cost = 0;
    scanf("%d %d", &N, &W);
    index = (int *) malloc(sizeof(int));
    *index = 0;
    answer = (int *) malloc(sizeof(int) * (N + 1));
    int **D = (int **) calloc(W + 1, sizeof(int *));
    items = (List *) calloc(N + 1, sizeof(List));
    for (int i = 1; i <= N; i++)
        scanf("%d %d", &items[i].weight, &items[i].cost);
    for (int i = 0; i <= W; i++)
        D[i] = (int *) calloc(N + 1, sizeof(int));
    for (int i = 0; i <= W; i++)
        D[i][0] = 0;
    for (int i = 0; i <= N; i++)
        D[0][i] = 0;
    for (int i = 1; i <= N; i++)
        for (int w = 1; w <= W; w++) {
            D[w][i] = D[w][i - 1];
            if (items[i].weight <= w)
                if ((D[w - items[i].weight][i - 1] + items[i].cost) >= D[w][i])
                    D[w][i] = D[w - items[i].weight][i - 1] + items[i].cost;

        }
    find_ans(N, W, D);
    printf("%d %d %d\n", *index, *totally_weight, *totally_cost);
    while (*index >= 1) {
        printf("%d ", answer[*index - 1]);
        (*index)--;
    }


}
