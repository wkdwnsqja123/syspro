#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int data;
    struct node *next;
};

void push(struct node **top, int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL) return;
    new_node->data = data;
    new_node->next = *top;
    *top = new_node;
}

void print_stack(struct node *top) {
    struct node *temp = top;
    printf("Print stack\n");
    while (temp != NULL) {
        printf("%d\n", temp->data);
        temp = temp->next;
    }
}

int main() {
    struct node *top = NULL;
    char input[50];

    while (1) {
        if (scanf("%s", input) != 1) break;

        char *endptr;
        double value = strtod(input, &endptr);

        if (*endptr != '\0' || value <= 0 || value != (int)value) {
            print_stack(top);
            break;
        } else {
            push(&top, (int)value);
        }
    }

    return 0;
}

