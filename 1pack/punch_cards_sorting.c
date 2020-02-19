/*
 * Solution from https://github.com/Nerozine
 * Modified by Romchririk
 */



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
    q->size = 0;
    q->first = 0;
    return q;
}


int QueueIsEmpty(queue *q) {
    return (q->leng == 0);
}


int QueueIsFilled(queue *q) {
    return (q->leng == q->size);
}


void fillDeck(queue *q, int multiplier, int num_cards_to_fill) {

    for (int i = 0; i < (q->size - 1) / 2; i++) {
        q->arr[i] = (i + 1) * multiplier;
    }
    q->leng = num_cards_to_fill;
}


int getCommand() {
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
        }
    } else {
        if (!QueueIsFilled(q2)) {
            if (flag_down) {
                putCardDown(q2, a);
                return;
            } else {
                putCardUp(q2, a);
                return;
            }

        }
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

    queue *left_queue, *right_queue;
    int num_cards, num_operations;
    scanf("%d%d\n", &num_cards, &num_operations);

    left_queue = createQueue();
    right_queue = createQueue();

    left_queue->size = num_cards * 2 + 1;
    right_queue->size = num_cards * 2 + 1;
    left_queue->arr = (int *) (malloc(sizeof(int) * left_queue->size));
    right_queue->arr = (int *) (malloc(sizeof(int) * right_queue->size));

    fillDeck(left_queue, -1, num_cards);
    fillDeck(right_queue, 1, num_cards);

    for (int i = 0; i < num_operations; i++) {
        int x;
        int card;
        char take_flag_right = 0;
        char take_flag_down = 0;
        char put_flag_right = 0;
        char put_flag_down = 0;
        x = getCommand();

        if (x == 0 || x == 5 || x == 10 || x == 15)
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
        card = takeCard(left_queue, right_queue, take_flag_down, take_flag_right);
        if (card != 10000000) {
            putCard(left_queue, right_queue, put_flag_down, put_flag_right, card);
        }
    }

    printQueue(right_queue);
    printf("\n");
    printQueue(left_queue);

    free(left_queue->arr);
    free(right_queue->arr);

    return 0;
}