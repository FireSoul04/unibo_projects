#include <stdlib.h>

#ifdef _WIN32
	#define FFLUSH fflush(stdin)
	#define CLEAR system("cls")
#else
    void _fflush() {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
    }

    #define FFLUSH _fflush()
	#define CLEAR system("clear")
#endif

#define STRING_LENGTH 200
#define DATASET_COLUMNS 11

#define ANY 0 //?
#define EMPTY -1 //phi

#define YES 2
#define NO 1

typedef char string_t[STRING_LENGTH + 1];

// Struttura contenente le recensioni
typedef struct Feedback {
    int how_crowded, price, restaurant_type, estimated_waiting_time, has_alternative, has_waiting_room, is_weekend, is_hungry, is_raining, is_reserved, do_wait;
} feedback_t;

// Nodo della coda
typedef struct Node {
    feedback_t feedback;
    struct Node *next; 
} node_t;

// Struttura coda
typedef struct Queue {
    node_t *first, *last;
    int length;
} queue_t;

// Stringhe per stampare in modo leggibile i dati del dataset che sono interamente numerici
char *yes_no[3] = { "?", "no", "yes" },
    *how_crowded[4] = { "?", "none", "someone", "full" },
    *price[4] = { "?", "economic", "average", "expensive" },
    *restaurant_type[5] = { "?", "italian", "french", "thai", "fast_food" },
    *estimated_waiting_time[5] = { "?", "<10", "10-29", "30-60", ">60" };

// Funzioni per gestire una coda
int init_queue(queue_t *);
int free_queue(queue_t *);
int add_node(queue_t *, feedback_t *);

void training_phase(queue_t *, feedback_t *, const feedback_t *);
int testing_phase(queue_t *, feedback_t *);

int compare_specific(int, int);
int compare_hypotesis(int, int);

int find_s(feedback_t *, feedback_t *);
int read_val(feedback_t *, char *, int);
int read_data_from_file(queue_t *, char *, int);
void read_data_from_user(feedback_t *);

int set_value(int *, char, const char *);
int print_data(feedback_t *);
int do_wait(feedback_t *, feedback_t *, int);

void wait_user_input(feedback_t *, int, string_t, char *);