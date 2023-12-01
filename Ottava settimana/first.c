#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LENGTH 200
#define DATASET_LENGTH 3

#define NO 0
#define YES 1

#define NONE 0
#define SOMEONE 1
#define FULL 2

#define ITALIAN 0
#define FRENCH 1
#define THAI 2
#define FAST_FOOD 3

#define ECONOMIC 0
#define AVERAGE 1
#define EXPENSIVE 2

#define LESSTHAN10 0
#define BETWEEN10AND29 1
#define BETWEEN30AND60 2
#define MORETHAN60 3

#define ANY 0 //?
#define EMPTY -1 //ø

typedef char string_t[STRING_LENGTH + 1];
typedef struct Data {
    int how_crowded, price, restaurant_type, estimated_waiting_time, has_alternative, has_waiting_room, is_weekend, is_hungry, is_raining, is_reserved;
} data_t;

void set_bool(int *, char);
int generalize(data_t *, data_t *);
data_t* read_data(int);

int main() {
    int n = 0;
    data_t h = { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY };
    data_t *dataset = read_data(DATASET_LENGTH);

    int do_wait[n];

    for (int i = 0; i < n; i++) {
        do_wait[i] = generalize(dataset, &h);
    }

    free(dataset);
    system("pause");

    return 0;
}

// Funzione per considerare ogni riga del dataset prendendo i dati più generali
int generalize(data_t *dataset, data_t *h) {

}

data_t* read_data(int length) {
    const char separator[2] = ",";
    
    // Apro il file in lettura
    FILE *data_sheet = fopen("./dataset.csv", "r");
    if (data_sheet == NULL) {
        puts("Il dataset non è stato trovato...");
        exit(1);
    }

    data_t *dataset = (data_t *) malloc(sizeof(data_t) * length);
    if (dataset == NULL) {
        puts("Memoria insufficente...");
        exit(1);
    }

    char *token;
    string_t data;
    
    // Salto la prima riga
    fgets(data, STRING_LENGTH + 1, data_sheet);

    for (int i = 0; i < length && fgets(data, STRING_LENGTH + 1, data_sheet) != NULL; i++) {
        // Gestisco ogni dato singolarmente
        token = strtok(data, separator);
        for (int j = 0; j < 10 && token != NULL; j++) {
            switch (j) {
                case 0:
                    set_bool(&dataset[i].has_alternative, token[0]);
                    break;
                case 1:
                    set_bool(&dataset[i].has_waiting_room, token[0]);
                    break;
                case 2:
                    set_bool(&dataset[i].is_weekend, token[0]);
                    break;
                case 3:
                    set_bool(&dataset[i].is_hungry, token[0]);
                    break;
                case 6:
                    set_bool(&dataset[i].is_raining, token[0]);
                    break;
                case 7:
                    set_bool(&dataset[i].is_reserved, token[0]);
                    break;
                case 4:
                    // 0=none, 1=someone, 2=full
                    switch (token[0]) {
                        case 'n':
                            dataset[i].how_crowded = NONE;
                            break;
                        case 's':
                            dataset[i].how_crowded = SOMEONE;
                            break;
                        case 'f':
                            dataset[i].how_crowded = FULL;
                            break;
                        default:
                            dataset[i].how_crowded = EMPTY;
                            break;
                        }
                    break;
                case 5:
                    // 0=$, 1=$$, 2=$$$
                    dataset[i].price = strlen(token) - 1;
                    break;
                case 8:
                    // 0=italian, 1=french, 2=thai, 3=fast_food
                    switch (token[1]) {
                        case 't':
                            dataset[i].restaurant_type = ITALIAN;
                            break;
                        case 'r':
                            dataset[i].restaurant_type = FRENCH;
                            break;
                        case 'h':
                            dataset[i].restaurant_type = THAI;
                            break;
                        case 'a':
                            dataset[i].restaurant_type = FAST_FOOD;
                            break;
                        default:
                            dataset[i].restaurant_type = EMPTY;
                            break;
                    }
                    break;
                case 9:
                    // 0=<10, 1=10-29, 2=30-60, 3=>60
                    switch (token[0]) {
                        case '<':
                            dataset[i].estimated_waiting_time = LESSTHAN10;
                            break;
                        case '1':
                            dataset[i].estimated_waiting_time = BETWEEN10AND29;
                            break;
                        case '3':
                            dataset[i].estimated_waiting_time = BETWEEN30AND60;
                            break;
                        case '>':
                            dataset[i].estimated_waiting_time = MORETHAN60;
                            break;
                        default:
                            dataset[i].estimated_waiting_time = EMPTY;
                            break;
                    }
                    break;
            }
            token = strtok(NULL, separator);
        }
    }
    fclose(data_sheet);
    return dataset;
}

void set_bool(int *h_value, char new_value) {
    if (new_value == 'y') {
        *h_value = YES;
    } else if (new_value == 'n') {
        *h_value = NO;
    } else {
        *h_value = EMPTY;
    }
}