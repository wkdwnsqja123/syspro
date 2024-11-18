#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
    int data;
    struct node *next;
};

void addq(struct node **head, struct node **tail, int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    if (new_node == NULL) return;
    new_node->data = data;
    new_node->next = NULL;
    if (*tail) {
        (*tail)->next = new_node;
    } else {
        *head = new_node;
    }
    *tail = new_node;
}

int delete(struct node **head, struct node **tail) {
    if (*head == NULL) return -1;
    struct node *temp = *head;
    int value = temp->data;
    *head = (*head)->next;
    if (*head == NULL) *tail = NULL;
    free(temp);
    return value;
}

void print_queue(struct node *head) {
    struct node *temp = head;
    printf("Print queue\n");
    while (temp != NULL) {
        printf("%d\n", temp->data);
        temp = temp->next;
    }
}

int main() {
    struct node *head = NULL, *tail = NULL;
    char input[50];

    while (1) {
        if (scanf("%s", input) != 1) break;

        char *endptr;
        double value = strtod(input, &endptr);

        if (*endptr != '\0' || value <= 0 || value != (int)value) {
            print_queue(head);
            break;
        } else {
            addq(&head, &tail, (int)value);
        }
    }

    return 0;
}

