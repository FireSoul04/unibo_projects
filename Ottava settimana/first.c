#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "first.h"

int main() {
    // Ipotesi generico
    const feedback_t empty_s = { EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY };
    feedback_t s = empty_s;
    queue_t dataset;
    init_queue(&dataset);

    int exit = 0;
    do {
        // Fase di training
        training_phase(&dataset, &s, &empty_s);

        // Fase di testing
        exit = testing_phase(&dataset, &s);
    } while(!exit);

    return 0;
}

void training_phase(queue_t *dataset, feedback_t *s, const feedback_t *empty_s) {
    node_t *current;
    int choice = 0;

    do {
        CLEAR;
        puts("ALGORITMO FIND-S");
        puts("Inserire un numero tra le scelte disponibili");
        puts("0: Stampo l'ipotesi generica");
        puts("1: Puoi aggiungere una recensione al dataset");
        puts("2: Stampo l'intero dataset");
        puts("3: Leggo dati da file");
        puts("4: Annullare l'allenamento eseguito");
        puts("5: Conclude la fase di allenamento");

        printf("Scelta: ");
        choice = getchar() - '0';
        FFLUSH;

        switch (choice) {
            case 0:
                // Stampo l'ipotesi generica
                print_data(s);
                break;

            case 1:
                // L'utente aggiunge un dato
                feedback_t new_feedback;
                read_data_from_user(&new_feedback);
                if (add_node(dataset, &new_feedback) == -1) {
                    puts("Memoria insufficente...");
                }
                find_s(&new_feedback, s);
                break;

            case 2:
                // Stampa tutto il dataset
                current = dataset->first;
                for (int i = 0; current != NULL; i++) {
                    printf("index: %d\n", i);
                    print_data(&current->feedback);
                    puts(""); // Va a capo
                    current = current->next;
                }
                break;

            case 3:
                // Leggo da file scelto dall'utente
                string_t file_path;
                puts("Inserire il percorso del file dove leggere i dati");
                gets(file_path);
                FFLUSH;

                if (read_data_from_file(dataset, file_path, DATASET_COLUMNS)) {
                    puts("I valori del file non sono validi");
                } else {
                    current = dataset->first;
                    while (current != NULL) {
                        find_s(&current->feedback, s);
                        current = current->next;
                    }
                    puts("Letti con successo");
                }
                break;

            case 4:
                // Cancella i dati dalla lista
                free_queue(dataset);
                *s = *empty_s;
                break;

            case 5:
                // Esce dal ciclo
                break;
            
            default:
                puts("Inserire un valore tra le scelte disponibii");
                break;
        }
        puts("Premere INVIO per andare avanti");
        getchar();
        FFLUSH;
    } while(choice != 5);
}

int testing_phase(queue_t *dataset, feedback_t *s) {
    int choice = 0;

    do {
        CLEAR;
        puts("ALGORITMO FIND-S");
        puts("Inserire un numero tra le scelte disponibili");
        puts("0: Provare l'algoritmo allenato con una nuova recensione");
        puts("1: Eseguire di nuovo l'allenamento");
        puts("2: Uscire dal programma");

        printf("Scelta: ");
        choice = getchar() - '0';
        FFLUSH;

        switch (choice) {
            case 0:
                // Provare l'algoritmo con un'ipotesi
                feedback_t h;
                read_data_from_user(&h);
                int do_we_wait = do_wait(&h, s, DATASET_COLUMNS);

                // Chiedo all'utente se data la sua ipotesi, il risultato è corretto
                char is_correct;
                do {
                    printf("Data l'ipotesi, il risultato e' %s\n", yes_no[do_we_wait + 1]);
                    puts("L'ipotesi e' corretta? (y/n)");
                    is_correct = tolower(getchar());
                } while(is_correct != 'y' && is_correct != 'n');

                // Aggiunge all'allenamento in caso sia corretto
                if (is_correct == 'y') {
                    find_s(&h, s);
                }
                break;

            case 1:
                // Esco dal ciclo
                break;

            case 2:
                // Conclude il programma
                free_queue(dataset);
                system("pause");
                return 1;
            
            default:
                puts("Inserire un valore tra le scelte disponibili");
                break;
        }
        puts("Premere INVIO per andare avanti");
        getchar();
        FFLUSH;
    } while(choice != 1);

    return 0;
}

// Funzione per inizializzare una coda
int init_queue(queue_t *head) {
    head->first = NULL;
    head->last = NULL;
    head->length = 0;

    return 0;
}

// Funzione per liberare una coda dalla memoria
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

// Funzione per aggiungere un nodo ad una coda
int add_node(queue_t *head, feedback_t *feedback) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    if (new_node == NULL) {
        return -1;
    }

    new_node->feedback = *feedback;
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

// Funzione per controllare se data l'ipotesi e dato il risultato allenato conviene aspettare
int do_wait(feedback_t *h, feedback_t *s, int columns) {
    // Controllo se sono tutte vere, se si conf sarà pari al numero di colonne dei dati
    int conf = 0;
    conf += compare_hypotesis(s->has_alternative, h->has_alternative);
    conf += compare_hypotesis(s->has_waiting_room, h->has_waiting_room);
    conf += compare_hypotesis(s->is_weekend, h->is_weekend);
    conf += compare_hypotesis(s->is_hungry, h->is_hungry);
    conf += compare_hypotesis(s->how_crowded, h->how_crowded);
    conf += compare_hypotesis(s->price, h->price);
    conf += compare_hypotesis(s->is_raining, h->is_raining);
    conf += compare_hypotesis(s->is_reserved, h->is_reserved);
    conf += compare_hypotesis(s->restaurant_type, h->restaurant_type);
    conf += compare_hypotesis(s->estimated_waiting_time, h->estimated_waiting_time);

    return conf == columns;
}

// Funzione per considerare ogni riga del dataset prendendo i dati più generali, ritorna se il dato è un esempio positivo
int find_s(feedback_t *h, feedback_t *s) {
    // Controllo se la classe è positiva
    if (h->do_wait == YES) {
        s->estimated_waiting_time = compare_specific(s->estimated_waiting_time, h->estimated_waiting_time);
        s->has_alternative = compare_specific(s->has_alternative, h->has_alternative);
        s->has_waiting_room = compare_specific(s->has_waiting_room, h->has_waiting_room);
        s->how_crowded = compare_specific(s->how_crowded, h->how_crowded);
        s->is_hungry = compare_specific(s->is_hungry, h->is_hungry);
        s->is_raining = compare_specific(s->is_raining, h->is_raining);
        s->is_reserved = compare_specific(s->is_reserved, h->is_reserved);
        s->is_weekend = compare_specific(s->is_weekend, h->is_weekend);
        s->price = compare_specific(s->price, h->price);
        s->restaurant_type = compare_specific(s->restaurant_type, h->restaurant_type);
        s->do_wait = YES;
        return 1;
    }
    return 0;
}

/**
 * Funzione per distinguere che tipo di valore è presente nel dataset
 * @param possible_values è un array di caratteri, ogni carattere viene confrontato con il valore passato nella funzione
 * @returns 0 se il dato è valido e -1 se non lo è
*/
int set_value(int *value, char check, const char *possible_values) {
    int str_length = strlen(possible_values);
    for (int i = 0; i < str_length; i++) {
        if (check == possible_values[i]) {
            *value = i + 1; // +1 perché il valore 0 è dedicato a ANY
            return 0;
        }
    }
    return -1;
}

// Funzione per comparare un feedback con l'ipotesi allenata per controllare se conviene aspettare
int compare_hypotesis(int s_val, int h_val) {
    return s_val == ANY || s_val == h_val;
}

// Funzione per comparare un feedback da allenare per cercare l'ipotesi specifica
int compare_specific(int s_val, int h_val) {
    if (s_val == EMPTY) {
        s_val = h_val;
    } else if (h_val != s_val) {
        s_val = ANY;
    }
    return s_val;
}

// Funzione per inserire i dati di un nuovo nodo, ritorna -1 se il valore è invalido
int read_val(feedback_t *new_feedback, char *str, int index) {
    switch (index) {
        case 0:
            return set_value(&new_feedback->has_alternative, str[0], "ny");
        case 1:
            return set_value(&new_feedback->has_waiting_room, str[0], "ny");
        case 2:
            return set_value(&new_feedback->is_weekend, str[0], "ny");
        case 3:
            return set_value(&new_feedback->is_hungry, str[0], "ny");
        case 4:
            // 0=?, 1=none, 2=someone, 3=full
            return set_value(&new_feedback->how_crowded, str[0], "nsf");
        case 5:
            // 0=?, 1=$, 2=$$, 3=$$$
            int length = strlen(str);
            for (int i = 0; i < length; i++) {
                if (str[i] != '$') {
                    return -1;
                }
            }
            if (length < 0 || length > 3) {
                return -1;
            } else {
                new_feedback->price = length;
                return 0;
            }
        case 6:
            return set_value(&new_feedback->is_raining, str[0], "ny");
        case 7:
            return set_value(&new_feedback->is_reserved, str[0], "ny");
        case 8:
            // 0=?, 1=italian, 2=french, 3=thai, 4=fast_food
            return set_value(&new_feedback->restaurant_type, str[1], "trha");
        case 9:
            // 0=?, 1=<10, 2=10-29, 3=30-60, 4=>60
            return set_value(&new_feedback->estimated_waiting_time, str[0], "<13>");
        case 10:
            return set_value(&new_feedback->do_wait, str[0], "ny");
        default:
            return -1;
    }
}

// Funzione per chiedere i dati all'utente da aggiungere al training set
void read_data_from_user(feedback_t *new_feedback) {
    string_t new_data;
    char ch;

    // Aspetto l'input dell'utente finché i dati non sono come desidera
    do {
        CLEAR;
        wait_user_input(new_feedback, 0, new_data, "Il ristorante ha alternative? (yes o no)");
        wait_user_input(new_feedback, 1, new_data, "Il ristorante ha una sala d'attesa/bar? (yes o no)");
        wait_user_input(new_feedback, 2, new_data, "Il giorno in cui si vuole andare e' weekend (venerdi' e sabato, scrivere yes o no)");
        wait_user_input(new_feedback, 3, new_data, "Si e' affamati? (yes o no)");
        wait_user_input(new_feedback, 4, new_data, "Quanto e' affollato? (none, someone o full)");
        wait_user_input(new_feedback, 5, new_data, "Quanto costa? (inserire il carattere $ da una a tre volte in base a quanto si pensa sia costoso)");
        wait_user_input(new_feedback, 6, new_data, "Sta piovendo? (yes o no)");
        wait_user_input(new_feedback, 7, new_data, "Si ha prenotato? (yes o no)");
        wait_user_input(new_feedback, 8, new_data, "Che tipo di ristorante e'? (italian, french, fast_food, thai)");
        wait_user_input(new_feedback, 9, new_data, "Attesa stimata in minuti? (<10, 10-29, 30-60, >60)");
        wait_user_input(new_feedback, 10, new_data, "Conviene aspettare? (yes o no)");
        CLEAR;

        print_data(new_feedback);
        puts("I seguenti dati vanno bene? (y/n)");
        do {
            ch = getchar();
            FFLUSH;
            if (ch != 'y' && ch != 'n') {
                puts("Inserire un valore tra y e n");
            }
        } while (ch != 'y' && ch != 'n');
    } while(ch != 'y');
}

// Funzione per leggere i dati dal dataset
int read_data_from_file(queue_t *dataset, char *file_path, int columns) {
    const char separator[2] = ",";
    
    // Apro il file in lettura
    FILE *data_sheet = fopen(file_path, "r");
    if (data_sheet == NULL) {
        puts("Il dataset non e' stato trovato...");
        return -1;
    }

    char *token;
    string_t data;
    feedback_t new_feedback;
    
    // Salto la prima riga
    fgets(data, STRING_LENGTH + 1, data_sheet);

    // Eseguo un ciclo finché non leggo completamente il file
    for (int i = 0; fgets(data, STRING_LENGTH + 1, data_sheet) != NULL; i++) {
        // Gestisco ogni dato singolarmente
        token = strtok(data, separator);
        for (int j = 0; j < columns; j++) {
            // Se anche solo un valore è invalido creo una coda nuova
            if (read_val(&new_feedback, token, j) == -1 || token == NULL) {
                free_queue(dataset);
                return -1;
            }
            token = strtok(NULL, separator);
        }
        if (add_node(dataset, &new_feedback) == -1) {
            puts("Memoria insufficente");
        }
    }
    // Chiudo il file e ritorno la coda di strutture
    fclose(data_sheet);
    return 0;
}

// Funzione per stampare tutti i dati di una recensione
int print_data(feedback_t *feedback) {
    // Controllo se i campi sono vuoti
    if (feedback->has_alternative == EMPTY) {
        puts("Non e' stato possibile allenare abbastanza...");
        return -1;
    }

    printf("has_alternative: %s\n", yes_no[feedback->has_alternative]);
    printf("has_waiting_room: %s\n", yes_no[feedback->has_waiting_room]);
    printf("is_weekend: %s\n", yes_no[feedback->is_weekend]);
    printf("is_hungry: %s\n", yes_no[feedback->is_hungry]);
    printf("how_crowded: %s\n", how_crowded[feedback->how_crowded]);
    printf("price: %s\n", price[feedback->price]);
    printf("is_raining: %s\n", yes_no[feedback->is_raining]);
    printf("is_reserved: %s\n", yes_no[feedback->is_reserved]);
    printf("restaurant_type: %s\n", restaurant_type[feedback->restaurant_type]);
    printf("estimated_waiting_time: %s\n", estimated_waiting_time[feedback->estimated_waiting_time]);
    printf("do_wait: %s\n", yes_no[feedback->do_wait]);

    return 0;
}

// Funzione per attendere l'input dell'utente
void wait_user_input(feedback_t *new_feedback, int index, string_t new_data, char *output) {
    int is_valid = 0;
    do {
        puts(output);
        gets(new_data);

        int length = strlen(new_data);
        for (int i = 0; i < length; i++) {
            new_data[i] = tolower(new_data[i]);
        }

        is_valid = read_val(new_feedback, new_data, index);
        if (is_valid == -1) {
            puts("Inserire un valore valido");
        }
    } while(is_valid == -1);
}