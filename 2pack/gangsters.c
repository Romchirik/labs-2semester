#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    int time;
    int money;
    int width;

} List;

void sort_by_time(List *a, int n) {
    List tmp;
    int j, i;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (a[j].time > a[j + 1].time) {
                tmp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = tmp;
            }
        }
    }
}


int main() {
    int N, K, T;
    scanf("%d %d %d", &N, &K, &T);
    List *gangsters = (List *) calloc(N, sizeof(List));

    for (int i = 0; i < N; i++)
        scanf("%d", &gangsters[i].time);
    for (int i = 0; i < N; i++)
        scanf("%d", &gangsters[i].money);
    for (int i = 0; i < N; i++)
        scanf("%d", &gangsters[i].width);

    sort_by_time(gangsters, N);

    int max, p;
    int answer[100] = {0};

    for (int i = 0; i < N; i++) {
        if ((gangsters[i].width > gangsters[i].time) || (gangsters[i].width > K))
            continue;
        if (gangsters[i].time > T)
            continue;
        else {
            max = gangsters[i].money;
            p = max;
            for (int prev = 0; prev < i; prev++) {
                if (abs(gangsters[prev].width - gangsters[i].width) <= (gangsters[i].time - gangsters[prev].time))
                    p = answer[prev] + gangsters[i].money;
                if (p > max)
                    max = p;
            }
            answer[i] = max;


        }
    }
    max = 0;

    for (int i = 0; i < N; i++) {
        if (answer[i] > max)
            max = answer[i];

    }
    printf("%d", max);

}
