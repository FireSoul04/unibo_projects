typedef struct Data {
    int how_crowded, price, restaurant_type, estimated_waiting_time, has_alternative, has_waiting_room, is_weekend, is_hungry, is_raining, is_reserved, do_wait;
} data_t;

typedef struct Node {
    data_t data;
    struct Node *next; 
} node_t;

typedef struct Queue {
    node_t *first, *last;
    int length;
} queue_t;

int init_queue(queue_t *);
int free_queue(queue_t *);
int add_node(queue_t *, data_t *);

#include "queue.c"