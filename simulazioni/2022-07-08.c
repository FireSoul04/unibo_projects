#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 08-07-2022

#define LUNGHEZZA_LISTINO 50

// Struttura dati per salvare i prodotti che può possedere un supermercato nel listino
typedef struct PRODOTTO_LISTINO {
    int codice_prodotto, codice_fornitore, quantita_minima;
    float prezzo_unitario;
} ProdottoListino;

// Struttura dati per salvare la lista di prodotti disponibili in un supermercato
typedef struct PRODOTTO {
    int codice_prodotto, codice_fornitore, quantita_presente;
    struct PRODOTTO *next;
} Prodotto;

// Struttura dati per salvare la lista di supermercati identificati da codice e prodotti disponibili
typedef struct SUPERMERCATO {
    int codice_supermercato;
    Prodotto *prodotti; // Lista di prodotti
    struct SUPERMERCATO *next;
} Supermercato;

void bubble_sort(ProdottoListino *);
int aggiungi_supermercato(Supermercato **, int);
int aggiungi_prodotto(Supermercato **, int, int, int, int);

int chiudi_supermercato(Supermercato **, int, int);
void stampa_prodotti_in_esaurimento(Supermercato *, ProdottoListino *, int);
int miglior_supermercato(Supermercato *, ProdottoListino *);

int main() {
    srand(time(NULL));
    ProdottoListino listino[LUNGHEZZA_LISTINO];

    for (int i = 0; i < LUNGHEZZA_LISTINO; i++) {
        listino[i].quantita_minima = 6 + rand() % 12;
        listino[i].codice_fornitore = 32;
        listino[i].codice_prodotto = i;
        listino[i].prezzo_unitario = (float)(rand() % 14) + i * listino[i].quantita_minima;
    }
    bubble_sort(listino);

    Supermercato *supermercati = NULL;
    for (int i = 0; i < 5; i++) {
        aggiungi_supermercato(&supermercati, i);
        for (int j = 0; j < LUNGHEZZA_LISTINO; j++) {
            aggiungi_prodotto(&supermercati, j, 32, 6 + rand() % 12, i);
        }
        aggiungi_prodotto(&supermercati, 0, 35, 47, i); // Giusto per controllare se funziona la lista prioritaria
    }

    stampa_prodotti_in_esaurimento(supermercati, listino, 1);
    if (chiudi_supermercato(&supermercati, 3, 1) == 1) {
        puts("Non e' stato trovato uno dei due supermercati...");
    }
    int migliore = miglior_supermercato(supermercati, listino);
    if (migliore == 1) {
        puts("La lista e' vuota...");
    }
    printf("Il migliore supermercato e' il %d\n", migliore);

    system("pause");

    return 0;
}

// Bubble sort per il listino, ordino per codice prodotto
void bubble_sort(ProdottoListino listino[LUNGHEZZA_LISTINO]) {
    int sorted;
    do {
        sorted = 1;
        for (int i = 0; i < LUNGHEZZA_LISTINO; i++) {
            if (listino[i].codice_prodotto > listino[i + 1].codice_prodotto) {
                ProdottoListino prodotto = listino[i];
                listino[i] = listino[i + 1];
                listino[i + 1] = prodotto;
                sorted = 0;
            } else if (listino[i].codice_prodotto == listino[i + 1].codice_prodotto) {
                if (listino[i].codice_fornitore > listino[i + 1].codice_fornitore) {
                    ProdottoListino prodotto = listino[i];
                    listino[i] = listino[i + 1];
                    listino[i + 1] = prodotto;
                    sorted = 0;
                }
            }
        }
    } while(!sorted);
}

// Aggiunge il supermercato alla lista
int aggiungi_supermercato(Supermercato **supermercati, int codice_supermercato) {
    Supermercato *nuovo = (Supermercato *)malloc(sizeof(Supermercato));
    if (nuovo == NULL) {
        puts("Memoria insufficente..");
        exit(1);
    }

    nuovo->codice_supermercato = codice_supermercato;
    nuovo->prodotti = NULL;
    nuovo->next = NULL;

    if (*supermercati == NULL) { // Aggiungo la testa se la lista dei supermercati è vuota
        *supermercati = nuovo;
        (*supermercati)->next = NULL;
    } else { // Aggiungo alla coda il supermercato se la lista non è vuota
        Supermercato *temp = *supermercati;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nuovo;
    }
    return 0;
}

// Aggiunge alla lista dei prodotti per il supermercato scelto e li ordino per codice prodotto, in caso codice prodotto sia uguale si ordina per codice fornitore, ritorna 0 se il supermercato è presente nella lista e 1 se non è presente
int aggiungi_prodotto(Supermercato **supermercati, int codice_prodotto, int codice_fornitore, int quantita_presente, int codice_supermercato) {
    Supermercato *temp = *supermercati;
    Prodotto *nuovo = (Prodotto *)malloc(sizeof(Prodotto));
    if (nuovo == NULL) {
        puts("Memoria insufficente..");
        exit(1);
    }

    nuovo->codice_prodotto = codice_prodotto;
    nuovo->codice_fornitore = codice_fornitore;
    nuovo->quantita_presente = quantita_presente;
    nuovo->next = NULL;

    int trovato = 0;

    // Cerco il supermercato specifico
    while (temp != NULL) {
        trovato = 0;
        if (temp->codice_supermercato == codice_supermercato) {
            trovato = 1;
            // Aggiungo alla coda il prodotto se la lista non è vuota e aggiungo in ordine per codice prodotto
            Prodotto *temp_p = temp->prodotti, *prev = NULL;
            while (temp_p != NULL) {
                if (codice_prodotto < temp_p->codice_prodotto) {
                    break;
                } else if (codice_prodotto == temp_p->codice_prodotto && codice_fornitore < temp_p->codice_fornitore) {
                    break;
                }
                prev = temp_p;
                temp_p = temp_p->next;
            }

            if (temp->prodotti == NULL) { // Aggiungo la testa se la lista di prodotti è vuota
                temp->prodotti = nuovo;
            } else if (prev == NULL) { // Aggiungo davanti alla testa
                temp->prodotti->next = nuovo;
            } else { // Aggiungo partendo da temp
                nuovo->next = temp_p;
                prev->next = nuovo;
            }
        }
        temp = temp->next;
    }

    // Controlla se il supermercato è presente
    if (!trovato) {
        return 1;
    }
    return 0;
}

// Rimuove il supermercato passato nella funzione come parametro e ritorna 0 se l'operazione ha avuto successo e 1 se non ha avuto successo
int chiudi_supermercato(Supermercato **supermercati, int codice_supermercato_aquisto, int codice_supermercato) {
    Supermercato *temp = *supermercati, *prev = NULL;

    // Se trovo il supermercato da rimuovere eseguo l'algoritmo per rimuovere un nodo dalla lista
    // In caso non trovato restituisce un messaggio di errore
    while (temp != NULL) {
        if (temp->codice_supermercato == codice_supermercato) {
            Supermercato *rimuovi = temp;

            // Cerco il supermercato dove spostare i dettagli dei prodotti del negozio chiuso
            Supermercato *temp_aq = *supermercati;
            int trova = 0;
            while (temp_aq != NULL && !trova) {
                if (temp_aq->codice_supermercato == codice_supermercato_aquisto) {
                    trova = 1;
                }
                temp_aq = temp_aq->next;
            }

            // Se il supermercato non è stato trovato
            if (!trova) {
                return 1;
            }

            // Aggiungo al supermercato che acquista tutti i prodotti del supermercato chiuso
            Prodotto *temp_p = temp->prodotti;
            while (temp_p != NULL) {
                int codice_prodotto = temp->prodotti->codice_prodotto;
                int codice_fornitore = temp->prodotti->codice_fornitore;
                int quantita_presente = temp->prodotti->quantita_presente;
                aggiungi_prodotto(&temp_aq, codice_prodotto, codice_fornitore, quantita_presente, codice_supermercato_aquisto);
                temp_p = temp_p->next;
            }

            temp = temp->next;
            if (prev == NULL) { // Sposto alla testa
                *supermercati = temp;
            } else { // Sposto verso il precedente
                prev->next = temp;
            }

            free(rimuovi); // Libero il supermercato dalla memoria
            return 0;
        }
        prev = temp;
        temp = temp->next;
    }
    return 1;
}

// Stampa i prodotti in esaurimento di un certo supermercato se sono presenti
void stampa_prodotti_in_esaurimento(Supermercato *supermercati, ProdottoListino listino[LUNGHEZZA_LISTINO], int codice_supermercato) {
    Supermercato *temp = supermercati;

    // Se trova il supermercato stampa la lista dei prodotti in esaurimento e ritorna 0, altrimenti 1
    while (temp != NULL) {
        if (temp->codice_supermercato == codice_supermercato) {
            Prodotto *temp_p = supermercati->prodotti;

            // Cerco tutti i prodotti del supermercato e controllo se la quantita presente non supera la quantita minima, se li trova stampa i dettagli del prodotto individuato
            while (temp_p != NULL) {
                for (int i = 0; i < LUNGHEZZA_LISTINO; i++) {
                    if (temp_p->codice_prodotto == listino[i].codice_prodotto) {
                        if (temp_p->quantita_presente < listino[i].quantita_minima) {
                            printf("Codice prodotto: %d\n", temp_p->codice_prodotto);
                            printf("Codice fornitore: %d\n", temp_p->codice_fornitore);
                            printf("Quantita' presente nel supermercato: %d\n", temp_p->quantita_presente);
                            printf("Quantita' necessaria: %d\n\n", listino[i].quantita_minima);
                        }
                    }
                }
                temp_p = temp_p->next;
            }
        }
        temp = temp->next;
    }
}

// Funzione per trovare il codice sel supermercato con i prodotti di valore maggiore, se la lista è vuota ritorna 1
int miglior_supermercato(Supermercato *supermercati, ProdottoListino listino[LUNGHEZZA_LISTINO]) {
    Supermercato *temp = supermercati;
    if (temp == NULL) {
        return 1;
    }

    int ret = 0, max = 0; // Ret salva il codice del supermercato migliore e max il valore totale dei prodotti del supermercato con il valore maggiore
    while (temp != NULL) {
        Prodotto *temp_p = temp->prodotti;

        // Appena trovo un supermercato con la somma dei valori dei prodotti maggiore salvo il codice del supermercato
        int temp_max = 0;
        while (temp_p != NULL) {
            for (int i = 0; i < LUNGHEZZA_LISTINO; i++) {
                if (temp_p->codice_prodotto == listino[i].codice_prodotto) {
                    temp_max += listino[i].prezzo_unitario * temp_p->quantita_presente;
                    break;
                }
            }
            temp_p = temp_p->next;
        }
        if (temp_max > max) {
            max = temp_max;
            ret = temp->codice_supermercato;
        }
        temp = temp->next;
    }

    return ret;
}