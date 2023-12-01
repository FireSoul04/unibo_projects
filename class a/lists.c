#include <stdio.h>
#include <stdlib.h>

typedef struct Cell {
    char letter;
    struct Cell *next; 
} cell_t;

int free_list(cell_t **);
int add_letter(cell_t **, char);
int remove_letter(cell_t **, char);

int main() {
    cell_t *head = NULL;
    char letter = 'g';

    for (int i = 0; i < 4; i++) {
        add_letter(&head, letter + i);
    }
    add_letter(&head, letter);

    cell_t *current = head;
    while (current != NULL) {
        printf("%c ", current->letter);
        current = current->next;
    }

    remove_letter(&head, letter);

    current = head;
    while (current != NULL) {
        printf("%c ", current->letter);
        current = current->next;
    }

    free_list(&head);
    system("pause");
}

int free_list(cell_t **head) {
    cell_t *current = *head;

    while (current != NULL) {
        cell_t *temp = current->next;
        current = current->next;
        free(temp);
    }
}

int remove_letter(cell_t **head, char letter) {
    cell_t *current = *head;

    while (current != NULL) {
        if (current->letter == letter) {
            cell_t *temp = current->next;
            current->next = current->next->next;
            free(temp);
        }
        current = current->next;
    }
}

int add_letter(cell_t **head, char letter) {
    cell_t *current = *head;
    cell_t *new_node = (cell_t *) malloc(sizeof(cell_t));

    while (current != NULL) {
        current = current->next;
    }
    
    new_node->letter = letter;
    current = new_node;
    current->next = NULL;
}