#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list {
    long long int data;
    struct list *next;
};

typedef struct stack {
    struct list *top;
} Stack_s;

void clear_stack(Stack_s *S) {
    struct list *p;
    while (S->top) {
        p = S->top;
        S->top = p->next;
        free(p);
    }
}

Stack_s *stack_initialize() {
    Stack_s *S;
    S = (Stack_s *) malloc(sizeof(Stack_s));
    S->top = NULL;
    return S;
}

int get_top(Stack_s *S) {
    if (S->top)
        return (S->top->data);
    else
        return 0;
}

int pop(Stack_s *S) {
    int data;
    struct list *tmp_top;

    tmp_top = S->top;
    data = tmp_top->data;
    S->top = tmp_top->next;
    free(tmp_top);

    return data;
}

void push(int a, Stack_s *S) {
    struct list *p;
    p = (struct list *) malloc(sizeof(struct list));
    p->data = a;
    p->next = S->top;
    S->top = p;
}

int is_empty(Stack_s *S) {
    return (S->top == NULL);
}


int main(void) {
    char input_string[2000] = {0};
    char output_string[2000] = {0};

    int operand1, operand2;
    Stack_s *Stack = stack_initialize();

    char *input_buffer_string = malloc(2000 * sizeof(char));
    memset(input_buffer_string, 0, 2000);

    gets(input_buffer_string);

    int output_length = 0;
    for (int i = 0; (i < 2000) && (input_buffer_string[i] != '\0'); i++) {
        switch (input_buffer_string[i]) {
            case '+':
                operand2 = pop(Stack);
                operand1 = pop(Stack);
                push(operand1 + operand2, Stack);
                break;
            case '-':
                operand2 = pop(Stack);
                operand1 = pop(Stack);
                push(operand1 - operand2, Stack);
                break;
            case '*':
                operand2 = pop(Stack);
                operand1 = pop(Stack);
                push(operand1 * operand2, Stack);
                break;
            case '/':
                operand2 = pop(Stack);
                operand1 = pop(Stack);
                if (operand2 == 0) {
                    printf("Division by zero, terminating...");
                    return 0;
                }
                push(operand1 / operand2, Stack);
                break;
            case ' ':
                continue;
            default: {
                short int number_len = 0;
                int tmp_number = 0;
                int power = 1;
                char number_to_translate[15];

                number_to_translate[number_len] = input_buffer_string[i];
                number_len++;
                i++;

                while ((input_buffer_string[i] != ' ') && (input_buffer_string[i] != '\0')) {
                    number_to_translate[number_len] = input_buffer_string[i];
                    i++;
                    number_len++;
                }

                for (int j = number_len - 1; j >= 0; j--) {
                    tmp_number += (number_to_translate[j] - 48) * power;
                    power *= 10;
                }

                push(tmp_number, Stack);
                memset(number_to_translate, 0, 15);
            }


        }
    }

    printf("%d", pop(Stack));

    clear_stack(Stack);
    free(Stack);
    free(input_buffer_string);

}