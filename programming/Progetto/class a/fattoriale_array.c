#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct BIGINT {
    int n;
    struct BIGINT *next;
} big_int_t;

big_int_t *factorial(int);

int add_cypher_to_big_int(big_int_t **, int);
void multiply_big_int(big_int_t **, int);
int free_big_int(big_int_t **);
void print_big_int(big_int_t *);

int main() {
    int n;
    big_int_t *fact;

    // printf("Inserisci un numero intero positivo: ");
    // scanf("%d", &n);

    // printf("Fattoriale di %d e' ", n);
    add_cypher_to_big_int(&fact, 10);
    print_big_int(fact);
    //free_big_int(&fact);
}

int add_cypher_to_big_int(big_int_t **big_int, int n) {
    big_int_t *new = (big_int_t *)malloc(sizeof(big_int_t));
    if (new == NULL) {
        puts("Stack overflow...");
        exit(1);
    }
    new->n = n;
    new->next = NULL;

    if (*big_int == NULL) {
        *big_int = new;
    } else {
        big_int_t *temp = *big_int;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new;
    }
}

void multiply_big_int(big_int_t **big_int, int n) {
    int resto = 0;
}

void print_big_int(big_int_t *big_int) {
    big_int_t *temp = big_int;
    while (temp != NULL) {
        printf("%d", big_int->n);
    }
}

big_int_t *factorial(int n) {
    if (n <= 1) {   
        //return 1;
    }

    

    //return n * factorial(n - 1);
}