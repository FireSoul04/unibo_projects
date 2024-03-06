#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 09-06-2021

#define N_ORDINI_MAX 15
#define N_PRODOTTI 150

typedef struct PRODOTTO {
    int id_prodotto; // Ordine crescente per id_prodotto
    char descrizione[101];
    float prezzo;
    int disponibilita_residua;
    int codice_errore;
} Prodotto;

typedef struct ORDINE {
    int id_prodotto;
    int quantita;
} Ordine;

typedef struct NODO_ORDINE {
    char nome_e_cognome[71];
    char indirizzo[71];
    int n_ordini;
    Ordine *ordini;
    struct NODO_ORDINE *next;
} NodoOrdine;

typedef struct CODA_ORDINI {
    NodoOrdine *testa;
    NodoOrdine *coda;
    int n_clienti;
} CodaOrdini;

void shift_sinistra(Ordine *ordini, int lunghezza, int inizio);
float* calcola_scontrino_clienti(CodaOrdini coda_ordini, Prodotto prodotti[N_PRODOTTI]);
void stampa_lista(CodaOrdini coda_ordini);
int prodotto_disponibile(Ordine *ordine, Prodotto prodotti[N_PRODOTTI]);
void aggiungi_a_coda(CodaOrdini *coda_ordini, char nome_e_cognome[71], char indirizzo[71], Ordine *ordini, Prodotto prodotti[N_PRODOTTI], int colonna_ordini);
CodaOrdini leggi_ordini(const char *nome_file, Prodotto prodotti[N_PRODOTTI]);

int main() {
    Prodotto prodotti[N_PRODOTTI]; // Si presuppone già riempito e ordinato per id_prodotto crescente
    const char *nome_file = "ordini.txt";

    CodaOrdini coda_ordini = leggi_ordini(nome_file, prodotti);
    stampa_lista(coda_ordini);
    float *scontrino_client = calcola_scontrino_clienti(coda_ordini, prodotti);

    return 0;
}

CodaOrdini leggi_ordini(const char *nome_file, Prodotto prodotti[N_PRODOTTI]) {
    CodaOrdini coda_ordini;
    NodoOrdine *testa = (NodoOrdine *)malloc(sizeof(NodoOrdine));
    if (testa == NULL) { // Controllo eventuali problemi di allocazione di memoria
        puts("Errore di allocazione di memoria");
        exit(1);
    }

    // Controllo se il file è presente e lo leggo
    FILE *f = fopen(nome_file, "r");
    if (f == NULL) {
        puts("File non trovato");
        exit(1);
    }

    // Inizzializzo il numero dei clienti della coda a 0
    coda_ordini.n_clienti = 0;

    char *token;
    char riga[500];
    char nome_e_cognome[71];
    char indirizzo[71];
    Ordine *ordini = (Ordine *)malloc(N_ORDINI_MAX * sizeof(Ordine));

    // Scorro ogni riga del file
    while (fgets(riga, 500, f) != NULL) {
        // Scorro ogni colonna del file
        // Leggo i primi due parametri della riga
        token = strtok(riga, " ");
        strcpy(nome_e_cognome, token);

        token = strtok(NULL, " ");
        strcpy(indirizzo, token);

        // Si presuppone il file sia formattato correttamente
        // Leggo ogni coppia di ordini
        int colonna_ordini = 0;
        do {
            token = strtok(NULL, " ");
            ordini[colonna_ordini].id_prodotto = atoi(token);

            token = strtok(NULL, " ");
            ordini[colonna_ordini].quantita = atoi(token);
            colonna_ordini++; // Passo al prossimo ordine
        } while (token != NULL);
        aggiungi_a_coda(&coda_ordini, nome_e_cognome, indirizzo, ordini, prodotti, colonna_ordini);
    }

    fclose(f);
    return coda_ordini;
}

// Controllo se il prodotto è disponibile
int prodotto_disponibile(Ordine *ordine, Prodotto prodotti[N_PRODOTTI]) {
    for (int i = 0; i < N_PRODOTTI; i++) {
        if (prodotti[i].id_prodotto == ordine->id_prodotto) {
            if (prodotti[i].disponibilita_residua >= ordine->quantita) {
                prodotti[i].disponibilita_residua -= ordine->quantita;
                return 1;
            } else {
                puts("Prodotto non piu' disponibile");
                prodotti[i].codice_errore = 1;
                return 0;
            }
        }
    }
    return 0;
}

// Aggiunge alla coda dei clienti
void aggiungi_a_coda(CodaOrdini *coda_ordini, char nome_e_cognome[71], char indirizzo[71], Ordine *ordini, Prodotto prodotti[N_PRODOTTI], int colonna_ordini) {
    // Controllo se l'ordine del cliente è già presente e in caso positivo rimuovo la quantità ordinata dall'array di prodotti
    int cliente_trovato = 0;
    NodoOrdine *temp = coda_ordini->testa;
    while (temp != NULL) {
        // Cerco il cliente nella lista
        if (strcmp(temp->nome_e_cognome, nome_e_cognome) == 0) {
            temp->n_ordini += colonna_ordini;
            // Rialloco il vettore in modo da avere la lunghezza attuale
            temp->ordini = (Ordine *)realloc(temp->ordini, temp->n_ordini * sizeof(Ordine));
            for (int i = 0; i < N_ORDINI_MAX; i++) {
                for (int j = 0; j < temp->n_ordini; j++) {
                    // Controllo se il prodotto nella lista è già presente
                    if (ordini[i].id_prodotto == temp->ordini[j].id_prodotto) {
                        // Controllo se è disponibile il prodotto
                        if (prodotto_disponibile(&ordini[i], prodotti)) {
                            temp->ordini[j].quantita += ordini[i].quantita;
                        } else {
                            temp->n_ordini--;
                            // Eventuale shift a sinistra e scorro l'array finché non colmo la cella vuota
                            shift_sinistra(temp->ordini, temp->n_ordini, j);
                        }
                    } else {
                        temp->ordini[j] = ordini[i];
                    }
                }
            }
            cliente_trovato = 1;
            // Rialloco il vettore in modo da avere la lunghezza attuale
            temp->ordini = (Ordine *)realloc(temp->ordini, temp->n_ordini * sizeof(Ordine));
            break;
        }
        temp = temp->next;
    }

    if (!cliente_trovato) {
        NodoOrdine *nuovo = (NodoOrdine *)malloc(sizeof(NodoOrdine));
        if (nuovo == NULL) { // Controllo eventuali problemi di allocazione di memoria
            puts("Errore allocazione memoria");
            exit(1);
        }

        // Inserisco i dati del nuovo nodo da aggiungere alla coda
        nuovo->next = NULL;
        strcpy(nuovo->nome_e_cognome, nome_e_cognome);
        strcpy(nuovo->indirizzo, indirizzo);
        nuovo->n_ordini = colonna_ordini;
        for (int i = 0; i < N_ORDINI_MAX; i++) {
            for (int j = 0; j < nuovo->n_ordini; j++) {
                // Controllo se è disponibile il prodotto
                if (prodotto_disponibile(&ordini[i], prodotti)) {
                    nuovo->ordini[j] = ordini[i];
                } else {
                    nuovo->n_ordini--;
                    // Eventuale shift a sinistra e scorro l'array finché non colmo la cella vuota
                    shift_sinistra(nuovo->ordini, nuovo->n_ordini, j);
                }
            }
        }
        // Rialloco il vettore in modo da avere la lunghezza attuale
        nuovo->ordini = (Ordine *)realloc(nuovo->ordini, nuovo->n_ordini * sizeof(Ordine));
        // Aggiungo la testa e la coda se la coda risulta vuota
        if (coda_ordini->testa == NULL) {
            coda_ordini->testa = nuovo;
        } else {
            nuovo->next = coda_ordini->coda;
        }
        coda_ordini->coda = nuovo;
        coda_ordini->n_clienti++;
    }
}

// Passo la coda per valore in modo da scorrere senza modificare la testa nel main
void stampa_lista(CodaOrdini coda_ordini) {
    if (coda_ordini.testa == NULL) {
        return;
    }

    // Stampo i dati degli ordini di uno specifico cliente
    printf("Nome: %s", coda_ordini.testa->nome_e_cognome);
    for (int i = 0; i < N_ORDINI_MAX; i++) {
        printf("Ordine n. %d, id_prodotto: %d, quantita: %d", i, coda_ordini.testa->ordini[i].id_prodotto, coda_ordini.testa->ordini[i].quantita);
    }
    printf("Indirizzo: %s", coda_ordini.testa->indirizzo);

    // Vado avanti con la lista
    coda_ordini.testa = coda_ordini.testa->next;
    stampa_lista(coda_ordini);
}

// Ritorna un array dinamico di scontrini di ogni cliente
float* calcola_scontrino_clienti(CodaOrdini coda_ordini, Prodotto prodotti[N_PRODOTTI]) {
    float *scontrino_clienti = (float *)malloc(coda_ordini.n_clienti * sizeof(float));

    int cliente = 0;
    // Calcolo il conto di ogni cliente
    NodoOrdine *temp = coda_ordini.testa;
    while (temp != NULL) {
        for (int i = 0; i < N_ORDINI_MAX; i++) {
            for (int j = 0; j < N_PRODOTTI; j++) {
                // Controllo quale prodotti ha ordinato il cliente
                if (temp->ordini[i].id_prodotto == prodotti[j].id_prodotto) {
                    // Aggiungo allo scontrino del cliente il prezzo e la quantita dell'ordine
                    scontrino_clienti[cliente] += prodotti[j].prezzo * temp->ordini->quantita;
                }
            }
        }
        // Passo al cliente successivo
        cliente++;
        temp = temp->next;
    }

    return scontrino_clienti;
}

// Sposto la cella verso sinistra di uno
void shift_sinistra(Ordine *ordini, int lunghezza, int inizio) {
    for (int i = inizio; i < lunghezza - 1; i++) {
        ordini[i] = ordini[i + 1];
    }
}