#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list {
    char data;
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
    char input_string[1000] = {0};
    char output_string[1000] = {0};

    Stack_s *Stack = stack_initialize();

    char *input_buffer_string = malloc(1000 * sizeof(char));
    memset(input_buffer_string, 0, 1000);
    gets(input_buffer_string);

    int input_length = 0;
    for (int i = 0; i < 1000; i++) {
        if ((input_buffer_string[i] == '\n') || (input_buffer_string[i] == '\0')) {
            break;
        } else {
            if (input_buffer_string[i] == ' ') continue;

            input_string[input_length] = input_buffer_string[i];
            input_length++;
        }
    }
    free(input_buffer_string);
    if (input_length == 0) return 0;

    int output_length = 0;
    for (int i = 0; i < input_length; i++) {
        switch (input_string[i]) {
            case '(':
                push('(', Stack);
                break;
            case ')':
                while (1) {
                    char tmp = pop(Stack);
                    if (tmp == '(') break;
                    else {
                        output_string[output_length] = tmp;
                        output_length++;
                    }
                }
                break;
            case '+':
                while (1) {
                    int tmp = get_top(Stack);
                    if (((tmp == '-') || (tmp == '+') || (tmp == '*') || (tmp == '/')) && (!is_empty(Stack))) {
                        output_string[output_length] = pop(Stack);
                        output_length++;
                    } else {
                        push('+', Stack);
                        break;
                    }
                }
                break;
            case '-':
                while (1) {
                    int tmp = get_top(Stack);
                    if (((tmp == '-') || (tmp == '+') || (tmp == '*') || (tmp == '/')) && (!is_empty(Stack))) {
                        output_string[output_length] = pop(Stack);
                        output_length++;
                    } else {
                        push('-', Stack);
                        break;
                    }
                }
                break;
            case '*':
                while (1) {
                    int tmp = get_top(Stack);
                    if (((tmp == '*') || (tmp == '/')) && (!is_empty(Stack))) {
                        output_string[output_length] = pop(Stack);
                        output_length++;
                    } else {
                        push('*', Stack);
                        break;
                    }
                }
                break;
            case '/':
                while (1) {
                    int tmp = get_top(Stack);
                    if (((tmp == '*') || (tmp == '/')) && (!is_empty(Stack))) {
                        output_string[output_length] = pop(Stack);
                        output_length++;
                    } else {
                        push('/', Stack);
                        break;
                    }
                }
                break;
            default:
                output_string[output_length] = input_string[i];
                output_length++;
                break;
        }
    }

    while (!is_empty(Stack)) {
        output_string[output_length] = pop(Stack);
        output_length++;
    }

    printf("%s", output_string);
    return 0;
}