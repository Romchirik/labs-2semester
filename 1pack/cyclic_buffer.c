//Solution from https://github.com/Nerozine



#include <stdio.h>
#include <stdlib.h>

typedef struct _Queue {
    int size; // размер массива
    int first; // номер первого элемента очереди
    int leng; // длина очереди
    int *arr; // указатель на начало массива
} queue;

queue *createQueue() {
    queue *q = (queue *) malloc(sizeof(queue));
    q->leng = 0;
    q->size = 1;
    q->arr = (int *) malloc(sizeof(int) * q->size);

    return q;
}


int QueueIsEmpty(queue *q) {
    return (q->leng == 0);
}

int QueueIsFilled(queue *q) {
    return (q->leng == q->size);
}

void addQueue(queue *q, int a) {
    q->arr[(q->leng + q->first) % q->size] = a;
    q->leng++;
}


int deQueue(queue *q) {
    int a = q->arr[q->first];
    //q->arr[q->first] = 0;
    q->first++;
    q->first %= q->size;
    q->leng--;
    return a;
}


void printQueue(queue *q) {
    printf("---\nfirst:%d\nleng:%d\n0 1 2 3 4\n", q->first, q->leng);
    printf("%d %d %d %d %d\n---\n", q->arr[0], q->arr[1], q->arr[2], q->arr[3], q->arr[4]);
}

void ringb() {
    int n, m;
    scanf("%d%d", &n, &m);
    queue *q = createQueue();
    q->arr = (int *) malloc(sizeof(int) * n);
    q->size = n;
    q->first = 0;
    //for (int i = 0; i < n; i++)
    //	q->arr[i] = 0;
    for (int i = 0; i < m; i++) {
        int r, j;
        scanf("%d", &r);
        //printQueue(q);
        if (r > 0) {
            char flag_overflow = 0;
            for (j = 0; j < r; j++) {
                if (!flag_overflow) {
                    if (!QueueIsFilled(q)) {
                        int a;
                        scanf("%d", &a);
                        addQueue(q, a);
                        //printQueue(q);
                    } else {
                        flag_overflow = 1;
                        //printQueue(q);
                        printf("Memory overflow\n");
                        int k = 0;
                        for (k = j; k < r; k++) {
                            int g;
                            scanf("%d", &g);
                        }
                        j = r - 1;
                    }
                } else {
                    int a;
                    scanf("%d", &a);
                    //printQueue(q);
                }

            }
            i += j;
        } else if (r < 0) {
            r = -r;
            char flag_empty = 0;
            int sum = 0;
            for (j = 0; j < r; j++) {
                if (!flag_empty) {
                    if (!QueueIsEmpty(q)) {
                        sum += deQueue(q);
                        //printQueue(q);
                    } else {
                        if (j == 0) {
                            printf("Empty queue\n");
                            flag_empty = 1;
                            break;
                        }

                        printf("%d\n", sum / j);
                        //	printQueue(q);
                        printf("Empty queue\n");
                        flag_empty = 1;
                    }
                }
            }
            if (!flag_empty)
                printf("%d\n", sum / r);
            //printQueue(q);
        } else {
            continue;
        }
    }
}


int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    ringb();
    return 0;
}