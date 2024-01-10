#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next;
} node_t;

int add_node(node_t **, int);
int free_list(node_t **);
int print_list(node_t *);

int main() {
    node_t *head = NULL;
    for (int i = 0; i < 20; i++) {
        add_node(&head, i);
    }

    print_list(head);
    free_list(&head);
    system("pause");
}

int print_list(node_t *head) {
    node_t *current = head;
    do {
        printf("%d ", current->val);
        current = current->next;
    } while (current != head);
    printf("\n");
}

int free_list(node_t **head) {
    do {
        node_t *temp = *head;
        *head = (*head)->next;
        free(temp);
    } while (*head != NULL);
    return 0;
}

int add_node(node_t **head, int val) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    if (new_node == NULL) {
        puts("Memoria insufficente...");
        exit(1);
    }
    new_node->val = val;
    new_node->next = *head;

    if (*head == NULL) {
        *head = new_node;
        (*head)->next = *head;
    } else {
        node_t *current = *head;
        int tmp = 0;
        while(current->next != *head) {
            tmp++;
            current = current->next;
        }
        current->next = new_node;
        //Collega new node al successivo!!!!
    }
}