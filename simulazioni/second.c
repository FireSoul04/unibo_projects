#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_PIATTI 150
#define LUNGHEZZA_STRINGA 200
#define LUNGHEZZA_DESCRIZIONE 100
#define LUNGHEZZA_NOME_E_COGNOME 70
#define MAX_ORDINI 15

typedef struct PIATTO {
    int id_piatto;
    char descrizione[LUNGHEZZA_DESCRIZIONE];
    float prezzo;
} Piatto;

typedef struct ORDINE {
    int id_piatto, numero_porzioni;
} Ordine;

typedef struct NODO_ORDINE {
    char nome_e_cognome[LUNGHEZZA_NOME_E_COGNOME];
    Ordine *ordini_cliente;
    int numero_ordini;
    struct NODO_ORDINE *next;
} NodoOrdine;

int bubble_sort(Piatto *, int);
int leggi_ordini(char *, NodoOrdine **);
int aggiungi_a_ordini(NodoOrdine **, Ordine *, char *, int);
void dividi_lista(NodoOrdine *, NodoOrdine **, NodoOrdine **, int *);
float calcola_scontrino_cliente(Piatto *, NodoOrdine *, char *);

int main() {
    Piatto piatti[NUM_PIATTI];
    for (int i = 0; i < NUM_PIATTI; i++) {
        piatti[i].id_piatto = i;
        piatti[i].prezzo = (14.0f * (float)(rand() % 14)) / 10.0f;
        strcpy(piatti[i].descrizione, "Si");
    }
    // Ordino per id_piatto in ordine crescente
    bubble_sort(piatti, NUM_PIATTI);

    NodoOrdine *lista_ordini = NULL;
    char *nome_file = "ordini.txt";
    if (leggi_ordini(nome_file, &lista_ordini) == -1) {
        puts("Stack overflow");
        return -1;
    }

    int i = 1;
    NodoOrdine *lp = NULL, *ld = NULL;
    dividi_lista(lista_ordini, &lp, &ld, &i);

    printf("Totale %f", calcola_scontrino_cliente(piatti, lista_ordini, "cioa_ciao"));
    printf("Totale %f", calcola_scontrino_cliente(piatti, lista_ordini, "ciao_ci"));

    system("pause");

    return 0;
}

// Calcola il totale da pagare di un certo cliente
float calcola_scontrino_cliente(Piatto piatti[NUM_PIATTI], NodoOrdine *lista_ordini, char nome_e_cognome[LUNGHEZZA_NOME_E_COGNOME]) {
    NodoOrdine *temp = lista_ordini;
    float totale = 0.0f;

    while (temp != NULL) {
        // Cerco il cliente dal nome e cognome
        if (strcmp(temp->nome_e_cognome, nome_e_cognome) == 0) {
            for (int i = 0; i < NUM_PIATTI; i++) {
                // Controllo tutti gli ordini del cliente
                for (int j = 0; j < temp->numero_ordini; j++) {
                    // Cerco il prezzo di ogni piatto del cliente e lo aggiungo al totale in base alle porzioni richieste
                    if (temp->ordini_cliente[j].id_piatto == piatti[i].id_piatto) {
                        totale += piatti[i].prezzo * temp->ordini_cliente[j].numero_porzioni;
                    }
                }
            }
        }
        temp = temp->next;
    }

    return totale;
}

// Divide la lista in due liste dove lp contiente tutti gli ordini con indice pari e ld tutti gli ordini con indice dispari
void dividi_lista(NodoOrdine *lo, NodoOrdine **lp, NodoOrdine **ld, int *i) {
    if (lo != NULL) {
        // Salvo i dati dentro la lista in base all'ordine pari o dispari degli ordini
        if (*i % 2 == 0) {
            aggiungi_a_ordini(lp, lo->ordini_cliente, lo->nome_e_cognome, lo->numero_ordini);
            *i++;
            dividi_lista(lo->next, &(*lp)->next, ld, i);
        } else {
            aggiungi_a_ordini(ld, lo->ordini_cliente, lo->nome_e_cognome, lo->numero_ordini);
            *i++;
            dividi_lista(lo->next, lp, &(*ld)->next, i);
        }
    }

    return;
}

// Aggiungo un nodo alla lista ordini
int aggiungi_a_ordini(NodoOrdine **lista, Ordine *ordini_cliente, char nome_e_cognome[], int numero_ordini) {
    NodoOrdine *nuovo_nodo = (NodoOrdine *)malloc(sizeof(NodoOrdine));
    // Stack overflow e restituisco un codice di errore
    if (nuovo_nodo == NULL) { 
        return -1;
    }
    strcpy(nuovo_nodo->nome_e_cognome, nome_e_cognome);
    nuovo_nodo->ordini_cliente = ordini_cliente;
    nuovo_nodo->next = NULL;

    // Se la lista è vuota aggiungo il nodo alla testa
    if (*lista == NULL) {
        nuovo_nodo->numero_ordini = numero_ordini;
        *lista = nuovo_nodo;
    } else if (strcmp((*lista)->nome_e_cognome, nome_e_cognome) == 0) {
        // Controllo se il cliente alla testa ha già altri ordini
        if ((*lista)->numero_ordini > 15) {
            puts("Impossibile aggiungere altri ordini!");
            return 1;
        }
        // Aggiorno i dati degli ordini nella lista
        (*lista)->numero_ordini += numero_ordini;
    } else {
        // Aggiungo il nodo alla coda scorrendo tutta la lista
        NodoOrdine *temp = *lista;
        while (temp->next != NULL) {
            // Controllo se il cliente ha già altri ordini e se sono meno di 15
            if (strcmp(temp->nome_e_cognome, nome_e_cognome) == 0) {
                if (temp->numero_ordini > 15) {
                    puts("Impossibile aggiungere altri ordini!");
                    return 1;
                }
                // Aumento il numero di ordini del cliente
                nuovo_nodo->numero_ordini += numero_ordini;
                break;
            } else {
                // Inizializzo il numero di ordini del cliente
                nuovo_nodo->numero_ordini = numero_ordini;
            }
            temp = temp->next;
        }
        nuovo_nodo->numero_ordini = numero_ordini;
        temp->next = nuovo_nodo;
    }

    return 0;
}

int leggi_ordini(char *nome_file, NodoOrdine **lista_ordini) {
    FILE *leggi_ordini = fopen(nome_file, "r");
    
    char riga[LUNGHEZZA_STRINGA];
    char *token;
    while (fgets(riga, LUNGHEZZA_STRINGA, leggi_ordini)) {
        token = strtok(riga, ",");

        Ordine *ordini_cliente = (Ordine *)malloc(sizeof(Ordine));
        if (ordini_cliente == NULL) {
            return -1;
        }

        // Salvo il nome del cliente
        char nome_e_cognome[LUNGHEZZA_NOME_E_COGNOME];
        strcpy(nome_e_cognome, token);

        // Scorro tutti gli ordini
        token = strtok(NULL, ",");
        int numero_ordini;
        for (numero_ordini = 0; token != NULL; numero_ordini++) {
            // Salva i dati dell'ordine nella struttura apposita
            ordini_cliente[numero_ordini].id_piatto = atoi(token);
            token = strtok(NULL, ",");
            ordini_cliente[numero_ordini].numero_porzioni = atoi(token);

            // Passa al prossimo ordine
            token = strtok(NULL, ",");
        }
        if (aggiungi_a_ordini(lista_ordini, ordini_cliente, nome_e_cognome, numero_ordini) == -1) {
            return -1;
        }
    }

    fclose(leggi_ordini);
    return 0;
}

int bubble_sort(Piatto *piatti, int lunghezza) {
    int ordinato;
    do {
        ordinato = 1;
        for (int i = 0; i < lunghezza - 1; i++) {
            if (piatti[i].id_piatto > piatti[i + 1].id_piatto) {
                Piatto tmp = piatti[i];
                piatti[i] = piatti[i + 1];
                piatti[i + 1] = tmp;
                ordinato = 0;
            }
        }
    } while (!ordinato);

    return 0;
}