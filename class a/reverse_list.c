#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Node {
    int val;
    struct Node *next; 
} node_t;

int free_list(node_t **);
int reverse_list(node_t **);
int add_node(node_t **, int);
int print_list(node_t *);

node_t* tail_of(node_t *);

int main() {
    node_t *head = NULL;
    for (int i = 0; i < 2000; i++) {
        add_node(&head, i);
    }

    //print_list(head);
    float start_time = (float)clock();
    reverse_list(&head);
    float end_time = ((float)clock() - start_time) / CLOCKS_PER_SEC;
    printf("Time spent: %f\n", end_time);

    //print_list(head);

    free_list(&head);
    system("pause");
}

int free_list(node_t **head) {
    node_t *current = *head;

    while (current != NULL) {
        node_t *temp = current;
        current = current->next;
        free(temp);
    }
    return 0;
}

int reverse_list(node_t ** head) {
    node_t *prev = NULL, *tail = tail_of(*head);

    while (prev != *head) {
        // Ottengo la coda e il nodo precedente
        node_t *current = *head;
        while (current->next != NULL) {
            prev = current;
            current = current->next;
        }
        current->next = prev;
        prev->next = NULL;
    }
    *head = tail;

    return 0;
}

int add_node(node_t **head, int val) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    if (new_node == NULL) {
        return -1;
    }

    new_node->val = val;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
    } else {
        node_t *current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    return 0;
}

int print_list(node_t *current) {
    while (current != NULL) {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
}

node_t* tail_of(node_t *head) {
    node_t *tail = head;
    while (tail->next != NULL) {
        tail = tail->next;
    }

    return tail;
}