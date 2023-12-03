#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LENGTH 200
#define DATASET_LENGTH 4
#define DATASET_COLUMNS 11

#define ANY 0 //?
#define EMPTY -1 //ø

#define YES 2
#define NO 1

typedef char string_t[STRING_LENGTH + 1];
typedef char* dynamic_string_t;
typedef struct Data {
    int how_crowded, price, restaurant_type, estimated_waiting_time, has_alternative, has_waiting_room, is_weekend, is_hungry, is_raining, is_reserved, do_wait;
} data_t;

dynamic_string_t yes_no[3] = { "?", "no", "yes" },
    how_crowded[4] = { "?", "none", "someone", "full" },
    price[4] = { "?", "economic", "average", "expensive" },
    restaurant_type[5] = { "?", "italian", "french", "thai", "fast_food" },
    estimated_waiting_time[5] = { "?", "<10", "10-29", "30-60", ">60" };


void print_data(data_t *);
void set_value(int *, char, const dynamic_string_t);
int generalize(data_t *, data_t *);

data_t* read_data(int, int);

int main() {
    // Ipotesi generico
    data_t h = { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY };
    data_t *dataset = read_data(DATASET_LENGTH, DATASET_COLUMNS);

    int training_steps = 0;
    
    // Stampa tutto il dataset
    // for (int i = 0; i < DATASET_LENGTH; i++) {
    //     printf("index: %d\n", i);
    //     print_data(dataset);
    //     puts("");
    // }

    for (int i = 0; i < DATASET_LENGTH; i++) {
        training_steps += generalize(&dataset[i], &h);
    }

    // Stampo l'ipotesi generica
    print_data(&h);
    printf("Valori positivi: %d\n", training_steps);
    free(dataset);
    system("pause");

    return 0;
}

// Funzione per considerare ogni riga del dataset prendendo i dati più generali
int generalize(data_t *data, data_t *h) {
    // Controllo se la classe è positiva
    if (data->do_wait == YES) {
        if (h->estimated_waiting_time == EMPTY) {
            h->estimated_waiting_time = data->estimated_waiting_time;
        } else if (data->estimated_waiting_time != h->estimated_waiting_time) {
            h->estimated_waiting_time = ANY;
        }

        if (h->has_alternative == EMPTY) {
            h->has_alternative = data->has_alternative;
        } else if (data->has_alternative != h->has_alternative) {
            h->has_alternative = ANY;
        }

        if (h->has_waiting_room == EMPTY) {
            h->has_waiting_room = data->has_waiting_room;
        } else if (data->has_waiting_room != h->has_waiting_room) {
            h->has_waiting_room = ANY;
        }

        if (h->how_crowded == EMPTY) {
            h->how_crowded = data->how_crowded;
        } else if (data->how_crowded != h->price) {
            h->how_crowded = ANY;
        }

        if (h->is_hungry == EMPTY) {
            h->is_hungry = data->is_hungry;
        } else if (data->is_hungry != h->is_hungry) {
            h->is_hungry = ANY;
        }

        if (h->is_raining == EMPTY) {
            h->is_raining = data->is_raining;
        } else if (data->is_raining != h->is_raining) {
            h->is_raining = ANY;
        }

        if (h->is_reserved == EMPTY) {
            h->is_reserved = data->is_reserved;
        } else if (data->is_reserved != h->is_reserved) {
            h->is_reserved = ANY;
        }

        if (h->is_weekend == EMPTY) {
            h->is_weekend = data->is_weekend;
        } else if (data->is_weekend != h->is_weekend) {
            h->is_weekend = ANY;
        }

        if (h->price == EMPTY) {
            h->price = data->price;
        } else if (data->price != h->price) {
            h->price = ANY;
        }
        
        if (h->restaurant_type == EMPTY) {
            h->restaurant_type = data->restaurant_type;
        } else if (data->restaurant_type != h->restaurant_type) {
            h->restaurant_type = ANY;
        }
        h->do_wait = YES;
        return 1;
    }
    return 0;
}

/**
 * Funzione per distinguere che tipo di valore è presente nel dataset
 * @param possible_values è un array di caratteri, ogni carattere viene confrontato con il valore passato nella funzione
*/
void set_value(int *value, char check, const dynamic_string_t possible_values) {
    int str_length = strlen(possible_values);
    for (int i = 0; i < str_length; i++) {
        if (check == possible_values[i]) {
            *value = i + 1; // +1 perché il valore 0 è dedicato a ANY
        }
    }
}

// Funzione per leggere i dati dal dataset
data_t* read_data(int length, int columns) {
    const char separator[2] = ",";
    
    // Apro il file in lettura
    FILE *data_sheet = fopen("./dataset.csv", "r");
    if (data_sheet == NULL) {
        puts("Il dataset non è stato trovato...");
        exit(1);
    }

    // Creo un array di strutture per salvare i dati del dataset in memoria
    data_t *dataset = (data_t *) malloc(sizeof(data_t) * length);
    if (dataset == NULL) {
        puts("Memoria insufficente...");
        exit(1);
    }

    dynamic_string_t token;
    string_t data;
    
    // Salto la prima riga
    fgets(data, STRING_LENGTH + 1, data_sheet);

    // Eseguo un ciclo finché non leggo completamente il file
    for (int i = 0; i < length && fgets(data, STRING_LENGTH + 1, data_sheet) != NULL; i++) {
        // Gestisco ogni dato singolarmente
        token = strtok(data, separator);
        for (int j = 0; j < columns && token != NULL; j++) {
            switch (j) {
                case 0:
                    set_value(&dataset[i].has_alternative, token[0], "ny");
                    break;
                case 1:
                    set_value(&dataset[i].has_waiting_room, token[0], "ny");
                    break;
                case 2:
                    set_value(&dataset[i].is_weekend, token[0], "ny");
                    break;
                case 3:
                    set_value(&dataset[i].is_hungry, token[0], "ny");
                    break;
                case 4:
                    // 0=$, 1=none, 2=someone, 3=full
                    set_value(&dataset[i].how_crowded, token[0], "nsf");
                    break;
                case 5:
                    // 0=$, 1=$, 2=$$, 3=$$$
                    dataset[i].price = strlen(token);
                    break;
                case 6:
                    set_value(&dataset[i].is_raining, token[0], "ny");
                    break;
                case 7:
                    set_value(&dataset[i].is_reserved, token[0], "ny");
                    break;
                case 8:
                    // 0=$, 1=italian, 2=french, 3=thai, 4=fast_food
                    set_value(&dataset[i].restaurant_type, token[1], "trha");
                    break;
                case 9:
                    // 0=$, 1=<10, 2=10-29, 3=30-60, 4=>60
                    set_value(&dataset[i].estimated_waiting_time, token[0], "<13>");
                    break;
                case 10:
                    set_value(&dataset[i].do_wait, token[0], "ny");
                    break;
            }
            token = strtok(NULL, separator);
        }
    }
    // Chiudo il file e ritorno l'array di strutture
    fclose(data_sheet);
    return dataset;
}

void print_data(data_t *dataset) {
    // Controllo se i campi sono vuoti
    if (dataset->has_alternative == EMPTY) {
        puts("Non e' stato possibile allenare abbastanza...");
        return;
    }
    printf("has_alternative: %s\n", yes_no[dataset->has_alternative]);
    printf("has_waiting_room: %s\n", yes_no[dataset->has_waiting_room]);
    printf("is_weekend: %s\n", yes_no[dataset->is_weekend]);
    printf("is_hungry: %s\n", yes_no[dataset->is_hungry]);
    printf("how_crowded: %s\n", how_crowded[dataset->how_crowded]);
    printf("price: %s\n", price[dataset->price]);
    printf("is_raining: %s\n", yes_no[dataset->is_raining]);
    printf("is_reserved: %s\n", yes_no[dataset->is_reserved]);
    printf("restaurant_type: %s\n", restaurant_type[dataset->restaurant_type]);
    printf("estimated_waiting_time: %s\n", estimated_waiting_time[dataset->estimated_waiting_time]);
    printf("do_wait: %s\n", yes_no[dataset->do_wait]);
}