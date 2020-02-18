#define _CRT_SECURE_NO_WARNINGS

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


void fillDeck(queue *q, int multiplier) {
    int i;
    for (i = 0; i < (q->size - 1) / 2; i++) {
        q->arr[i] = (i + 1) * multiplier;
    }
    q->leng = i;
}


int readx() {
    char a;
    scanf("%c", &a);
    int x;
    if (a >= '0' && a <= '9') {
        x = a - '0';
    } else {
        x = a - 'A' + 10;
    }
    return x;
}


int takeCardUp(queue *q) {
    int a = q->arr[q->first];
    q->first++;
    q->first = q->first % q->size;
    q->leng--;
    return a;
}


int takeCardDown(queue *q) {
    int a = q->arr[(q->first + q->leng - 1 + q->size) % q->size];
    q->leng--;
    return a;
}


void putCardDown(queue *q, int a) {
    q->arr[(q->leng + q->first + q->size) % q->size] = a;
    q->leng++;
}


void putCardUp(queue *q, int a) {
    q->arr[(q->first - 1 + q->size) % q->size] = a;
    q->leng++;
    q->first--;
    q->first = (q->first + q->size) % q->size;
}


int takeCard(queue *q1, queue *q2, char flag_down, char flag_right) {
    if (flag_right) {
        if (!QueueIsEmpty(q1)) {
            if (flag_down) {
                return takeCardDown(q1);
            } else {
                return takeCardUp(q1);
            }
        } else
            return 10000000; //error: queue is empty
    } else {
        if (!QueueIsEmpty(q2)) {
            if (flag_down) {
                return takeCardDown(q2);
            } else {
                return takeCardUp(q2);
            }
        } else
            return 10000000; //error: queue is empty
    }
}


void putCard(queue *q1, queue *q2, char flag_down, char flag_right, int a) {
    if (flag_right) {
        if (!QueueIsFilled(q1)) {
            if (flag_down) {
                putCardDown(q1, a);
                return;
            } else {
                putCardUp(q1, a);
                return;
            }
        } else
            return 10000000; // error: queue is filled
    } else {
        if (!QueueIsFilled(q2)) {
            if (flag_down) {
                putCardDown(q2, a);
                return;
            } else {
                putCardUp(q2, a);
                return;
            }
        } else
            return 10000000; // error: queue is filled
    }
}


void printQueue(queue *q) {
    printf("%d ", q->leng);
    for (int i = 0; i < q->leng; i++) {
        printf("%d ", q->arr[(q->first + i) % q->size]);
    }
    q->leng = 0;
    q->first = 0;
}


int main() {

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    queue *q1, *q2; //q1 - right deck "-" , q2 - left deck "+"
    int n, m;
    scanf("%d%d\n", &n, &m);

    q1 = createQueue();
    q2 = createQueue();

    q1->size = n * 2 + 1;
    q2->size = n * 2 + 1;
    q1->arr = (int *) (malloc(sizeof(int) * q1->size));
    q2->arr = (int *) (malloc(sizeof(int) * q2->size));
    q1->first = 0;
    q2->first = 0;

    fillDeck(q1, -1);
    fillDeck(q2, 1);

    for (int i = 0; i < m; i++) {
        int x;
        int a;
        char take_flag_right = 0;
        char take_flag_down = 0;
        char put_flag_right = 0;
        char put_flag_down = 0;
        x = readx();

        if (x == '0' || x == '5' || x == 'A' || x == 'F')
            continue;

        if ((x & 8) == 8) {
            take_flag_right = 1;
        }

        if ((x & 4) == 4) {
            take_flag_down = 1;
        }

        if ((x & 2) == 2) {
            put_flag_right = 1;
        }

        if ((x & 1) == 1) {
            put_flag_down = 1;
        }
        a = takeCard(q1, q2, take_flag_down, take_flag_right);
        if (a != 10000000) {
            putCard(q1, q2, put_flag_down, put_flag_right, a);
        }
    }

    printQueue(q2);
    printf("\n");
    printQueue(q1);

    free(q1->arr);
    free(q2->arr);

    return 0;
}