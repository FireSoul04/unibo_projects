#include <stdlib.h>

int init_queue(queue_t *head) {
    head->first = NULL;
    head->last = NULL;
    head->length = 0;

    return 0;
}

int free_queue(queue_t *head) {
    node_t *current = head->first;

    while (current != NULL) {
        node_t *temp = current;
        current = current->next;
        free(temp);
    }
    init_queue(head);
    return 0;
}

int reverse_queue(queue_t *head) {
    node_t *prev = NULL;

    while (prev != head->first) {
        // Ottengo la coda e il nodo precedente
        node_t *current = head->first;
        while (current->next != NULL) {
            prev = current;
            current = current->next;
        }
        current->next = prev;
        prev->next = NULL;
    }
    head->first = head->last;

    return 0;
}

int add_node(queue_t *head, data_t *data) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    if (new_node == NULL) {
        return -1;
    }

    new_node->data = *data;
    new_node->next = NULL;
    
    if (head->first == NULL) {
        head->first = new_node;
    } else {
        node_t *current = head->first;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    head->last = new_node;
    head->length++;

    return 0;
}