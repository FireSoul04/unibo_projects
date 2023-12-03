#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int val;
    struct Node *next; 
} node_t;

int free_list(node_t **);
int add_node(node_t **, int);
int print_list(node_t *);

int main() {
    node_t *head = NULL;
    int nums[10] = {
        1, 6, 2, 9, 8, 9, 4, 0, 2, 2
    };

    for (int i = 0; i < 10; i++) {
        add_node(&head, nums[i]);
    }
    print_list(head);

    free_list(&head);
    system("pause");
    return 0;
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

int add_node(node_t **head, int val) {
    // Creo il nuovo nodo
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    if (new_node == NULL) {
        return -1;
    }
    new_node->val = val;
    new_node->next = NULL;

    // Aggiungo alla testa
    if (*head == NULL) {
        *head = new_node;
    } else {
        // Prendo la posizione dove finisce l'ultimo valore più piccolo o uguale e lo aggiungo da lì
        node_t *current = *head, *prev = NULL;
        while (current != NULL && val > current->val) {
            prev = current;
            current = current->next;
        }
        // Se il valore è da aggiungere alla testa
        if (prev == NULL) {
            new_node->next = *head;
            *head = new_node;
        } else {
            new_node->next = current;
            prev->next = new_node;
        }
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