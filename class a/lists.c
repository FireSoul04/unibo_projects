#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char letter;
    struct Node *next; 
} node_t;

int free_list(node_t **);
int add_letter(node_t **, char);
int remove_letter(node_t **, char);
int print_list(node_t *);

int main() {
    node_t *head = NULL;
    char letter = 'g';

    add_letter(&head, letter);
    for (int i = 0; i < 50; i++) {
        add_letter(&head, 40 + (rand() % 87));
    }
    print_list(head);
    printf("\n");
    remove_letter(&head, letter);
    print_list(head);

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

int remove_letter(node_t **head, char letter) {
    node_t *current, *prev = *head;
    
    // Elimino tutti i nodi che partono dalla testa
    while (*head != NULL && (*head)->letter == letter) {
        node_t *temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    current = *head;
    
    // Elimino i nodi che non sono nella testa
    while (current != NULL) {
        if (current->letter == letter) {
            node_t *temp = current;
            current = current->next;
            prev->next = current;
            free(temp);
        } else {
            prev = current;
            current = current->next;
        }
    }
    return 0;
}

int add_letter(node_t **head, char letter) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    if (new_node == NULL) {
        return -1;
    }

    new_node->letter = letter;
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
        printf("%c ", current->letter);
        current = current->next;
    }
    printf("\n");
}