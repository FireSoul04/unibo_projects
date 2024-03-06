#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 17-01-2022

#define N_STUDENTI 120 // Non identificato
#define N_MAX_ESAMI 25

// Struttura esame
typedef struct ESAME {
    char id_esame[16];
    char esito[4]; // R se ritirato, I se respinto, 30L se 30 e lode, >18 e <=30 se passato
} Esame;

typedef struct PIANO_STUDIO {
    int matricola; // Ordinato crescente per matricola
    Esame esami[N_MAX_ESAMI]; // Elenco dettagli esame per ogni studente
} PianoStudio;

typedef struct NODO_STUDENTI {
    int matricola;
    char nome_e_cognome[101];
    Esame esami[N_MAX_ESAMI];
    struct NODO_STUDENTI *next;
} NodoStudenti;

NodoStudenti* aggiungi_a_lista(NodoStudenti *testa, int matricola, char nome_e_cognome[101], Esame esami[N_MAX_ESAMI]);
NodoStudenti* leggi_carriera(const char *nome_file);
void pulisci_lista(NodoStudenti **testa, NodoStudenti *temp, int matricola);
int statistiche_esame(NodoStudenti *testa, char id_esame[16], float *percentuale_passati, float *percentuale_lodi);

int main() {
    PianoStudio *piano_di_studi = (PianoStudio *)malloc(N_STUDENTI * sizeof(PianoStudio));
    // Controllo eventuali errori di allocazione
    if (piano_di_studi == NULL) {
        puts("Errore allocazione di memoria");
        exit(1);
    }
    const char *nome_file = "carriera.txt";

    NodoStudenti *testa = leggi_carriera(nome_file);
    pulisci_lista(&testa, testa, 101010);

    float percentuale_passati = 0.0f, percentuale_lodi = 0.0f;
    int studenti_passati = statistiche_esame(testa, "INF200", &percentuale_passati, &percentuale_lodi);

    printf("Studenti passati: %d, percentuale studenti passati: %f, percentuale studenti con lode: %f", studenti_passati, percentuale_passati, percentuale_lodi);

    return 0;
}

NodoStudenti* aggiungi_a_lista(NodoStudenti *testa, int matricola, char nome_e_cognome[101], Esame esami[N_MAX_ESAMI]) {
    NodoStudenti *nuovo = (NodoStudenti *)malloc(sizeof(NodoStudenti));
    // Controllo eventuali errori di allocazione
    if (nuovo == NULL) {
        puts("Errore allocazione di memoria");
        exit(1);
    }
    // Salvo nel nuovo nodo i dati passati nella funzione
    nuovo->next = NULL;
    nuovo->matricola = matricola;
    strcpy(nuovo->nome_e_cognome, nome_e_cognome);
    for (int i = 0; i < N_MAX_ESAMI; i++) {
        nuovo->esami[i] = esami[i];
    }

    // Se la lista è vuota aggiungo il nuovo nodo alla testa
    if (testa == NULL) {
        testa = nuovo;
    } else { // Aggiungo alla testa della lista
        nuovo->next = testa;
        testa = nuovo;
    }

    return testa;
}

// Crea una lista in base ai parametri del file
NodoStudenti* leggi_carriera(const char *nome_file) {
    NodoStudenti *testa = (NodoStudenti *)malloc(sizeof(NodoStudenti));
    // Controllo eventuali errori di allocazione
    if (testa == NULL) {
        puts("Errore allocazione di memoria");
        exit(1);
    }
    // Apro il file in lettura
    FILE *f = fopen(nome_file, "r");
    if (f == NULL) {
        puts("File non trovato");
        exit(1);
    }
    
    char *token;
    char riga[500];
    int matricola;
    char nome_e_cognome[101];
    Esame esami[N_MAX_ESAMI];

    // Scorro ogni riga del file
    while (fgets(riga, 500, f) != NULL) {
        // Salvo matricola e nome e cognome
        token = strtok(riga, " ");
        matricola = atoi(token);

        token = strtok(NULL, " ");
        strcpy(nome_e_cognome, token);

        // Scorro ogni esame nel file
        int colonna_esame = 0;
        do {
            token = strtok(NULL, " ");
            strcpy(esami[colonna_esame].id_esame, token);

            token = strtok(NULL, " ");
            strcpy(esami[colonna_esame].esito, token);
            
            colonna_esame++;
        } while (token != NULL);
        testa = aggiungi_a_lista(testa, matricola, nome_e_cognome, esami);
    }

    // Chiudo il file
    fclose(f);
    return testa;
}

// Funzione ricorsiva per rimuovere un certo studente dalla lista
void pulisci_lista(NodoStudenti **testa, NodoStudenti *temp, int matricola) {
    if (temp == NULL) { // La lista non contiente quello studente
        puts("Studente non trovato");
        return;
    } else if ((*testa)->matricola == matricola) { // Rimuove lo studente in testa
        *testa = (*testa)->next;
        free(temp);
        return;
    } else if (temp->matricola == matricola) { // Rimuove uno studente in mezzo alla lista
        NodoStudenti *aux = temp;
        temp = temp->next;
        free(aux);
        return;
    }
    // Scorre al prossimo nodo
    pulisci_lista(testa, temp, matricola);
}

// Ritorna quanti studenti si sono ritirati
int statistiche_esame(NodoStudenti *testa, char id_esame[16], float *percentuale_passati, float *percentuale_lodi) {
    int studenti_ritirati = 0, studenti_passati = 0, studenti_con_lode = 0, studenti_totali = 0;

    // Scorro tutta la lista degli studenti e calcolo il numero totale di studenti
    NodoStudenti *temp = testa;
    while (temp != NULL) {
        for (int i = 0; i < N_MAX_ESAMI; i++) {
            // Cerco nella lista degli esami dello studente l'esame specifico
            if (strcmp(temp->esami[i].id_esame, id_esame) == 0) {
                // Conta quanti studenti si sono ritirati
                if (strcmp(temp->esami[i].esito, "R") == 0) {
                    studenti_ritirati++;
                } else if (strcmp(temp->esami[i].esito, "I") != 0) {
                    // Controlla quanti studenti hanno passato e quanti con la lode
                    studenti_passati++;
                    if (strcmp(temp->esami[i].esito, "30L") == 0) {
                        studenti_con_lode++;
                    }
                }
                break;
            }
        }
        studenti_totali++;
    }

    // Salvo la percentuale
    *percentuale_lodi = studenti_con_lode * 100 / studenti_totali;
    *percentuale_passati = studenti_passati * 100 / studenti_totali;

    return studenti_ritirati;
}