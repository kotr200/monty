#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100

typedef struct {
    int stack[100];
    int top;
} Stack;

void push(Stack *stack, int value) {
    if (stack->top == 100 - 1) {
        fprintf(stderr, "Error: Stack overflow\n");
        exit(EXIT_FAILURE);
    }
    stack->top++;
    stack->stack[stack->top] = value;
}

void pall(Stack *stack) {
    int i;
    for (i = stack->top; i >= 0; i--) {
        printf("%d\n", stack->stack[i]);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    Stack stack;
    stack.top = -1;

    char opcode[256];
    int value;

    while (fscanf(file, "%s", opcode) != EOF) {
        if (strcmp(opcode, "push") == 0) {
            if (fscanf(file, "%d", &value) != 1) {
                fprintf(stderr, "Error: usage: push integer\n");
                exit(EXIT_FAILURE);
            }
            push(&stack, value);
        } else if (strcmp(opcode, "pall") == 0) {
            pall(&stack);
        } else {
            fprintf(stderr, "Error: Unknown opcode %s\n", opcode);
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);

    return 0;
}
