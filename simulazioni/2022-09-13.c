#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 13-09-2022

#define N_MEDICI 200
#define MAX_TURNI 8
#define N_GIORNI 7
#define MAX_PAZIENTI_PER_TURNO 5

#define USCITA_CON_SUCCESSO 0
#define ERRORE_ALLOCAZIONE -1
#define ERRORE_FILE -2
#define ERRORE_VETTORE_PIENO -3

// Nodo lista singolo turno
typedef struct singolo_turno {
    int id_turno; // Compreso tra 1 e 8
    int pazienti_per_turno; // Massimo 5
    struct singolo_turno *next;
} SingoloTurno;

typedef struct medico {
    char id_medico[13]; // Ordinato crescente per id_medico
    char reparto[31];
    SingoloTurno *turni[N_GIORNI]; // Massimo 8 turni, ogni turno lavora un solo medico
} Medico;

typedef struct esubero {
    SingoloTurno *turni[N_GIORNI];
} Esubero;

float *occupazione_medico(Medico *medici, int n_medici);
void stampa_esuberi(Esubero esuberi[], SingoloTurno *temp, int *medico, int *giorno, int *pazienti_in_esubero);
int aggiungi_a_turno(Medico *medici, Esubero esuberi[], int n_medici, char id_medico[12], int turno_richiesto, int giorno_richiesto);
int leggi_appuntamenti(const char *nome_file, Medico *medici, Esubero esuberi[], int n_medici);

int main() {
    Medico *medici = (Medico *)malloc(N_MEDICI * sizeof(Medico)); // Creo l'array di 200 medici
    if (medici == NULL) {
        puts("Errore durante l'allocazione di memoria");
        return ERRORE_ALLOCAZIONE;
    }
    // Inizializzo il vettore medici
    for (int i = 0; i < N_MEDICI; i++) {
        strcpy(medici[i].id_medico, ""); // Inizializzo l'id come vuoto
        strcpy(medici[i].reparto, ""); // Inizializzo il reparto come vuoto
        for (int j = 0; j < N_GIORNI; j++) {
            SingoloTurno *temp = medici[i].turni[j];
            while (temp != NULL) {
                temp->pazienti_per_turno = 0;
                temp = temp->next;
            }
        }
    }

    Esubero esuberi[N_MEDICI];
    // Inizializza il vettore esuberi
    for (int i = 0; i < N_MEDICI; i++) {
        for (int j = 0; j < N_GIORNI; j++) {
            SingoloTurno *temp = esuberi[i].turni[j];
            while (temp != NULL) {
                temp->pazienti_per_turno = 0;
                temp = temp->next;
            }
        }
    }
    const char *nome_file = "appuntamenti.txt"; // Nome del file dove leggere i dati

    if (leggi_appuntamenti(nome_file, medici, esuberi, N_MEDICI) == ERRORE_FILE) {
        puts("File non trovato");
        return ERRORE_FILE;
    }

    return 0;
}

// Legge il file e riempie il vettore medici in base ai dati del file
int leggi_appuntamenti(const char *nome_file, Medico *medici, Esubero esuberi[], int n_medici) {
    FILE *f = fopen(nome_file, "r");
    if (f == NULL) { // Se il file non lo trova esce dalla funzione
        return ERRORE_FILE;
    }

    char *token;
    char riga[500];
    char id_medico[12];
    int turno_richiesto, giorno_richiesto;

    while (fgets(riga, sizeof(riga), f) != NULL) {
        token = strtok(riga, " "); // Salta la prima colonna poiché salvare l'id del cliente non ci serve nella funzione
        token = strtok(NULL, " ");
        strcpy(id_medico, token); // Salvo l'id del medico al quale è richiesto l'appuntamento
        
        token = strtok(NULL, " ");
        turno_richiesto = atoi(token) - 1; // Salvo il turno richiesto, si presuppone il file sia formattato correttamente e turno sia compreso tra 1 e 8

        token = strtok(NULL, " ");
        giorno_richiesto = atoi(token) - 1; // Salvo il turno richiesto, si presuppone il file sia formattato correttamente e turno sia compreso tra 1 e 7
        int codice = aggiungi_a_turno(medici, esuberi, id_medico, turno_richiesto, giorno_richiesto, n_medici);
        if (codice == ERRORE_ALLOCAZIONE) {
            return ERRORE_ALLOCAZIONE;
        } else if (codice == ERRORE_VETTORE_PIENO) {
            printf("Non c'è abbastanza spazio per aggiungere il medico: %s", id_medico);
        }
    }

    fclose(f);
    return USCITA_CON_SUCCESSO;
}

// Aggiunge i dati ad un turno del medico
int aggiungi_a_turno(Medico *medici, Esubero esuberi[], int n_medici, char id_medico[12], int turno_richiesto, int giorno_richiesto) {
    int medico_presente = 0;
    int totale_medici = 0;
    // Controllo se il medico esiste nel vettore o bisogna aggiungerlo ad esso
    for (int i = 0; i < n_medici; i++) {
        if (strcmp(medici[i].id_medico, id_medico) == 0) {
            medico_presente = 1;
            break;
        }
        totale_medici++;
    }
    if (totale_medici == n_medici) {
        return ERRORE_VETTORE_PIENO;
    }
    // Se l'id del medico non è presente nella
    if (!medico_presente) {
        for (int i = 0; i < n_medici; i++) {
            if (strcmp(medici[i].id_medico, "") == 0) {
                strcpy(medici[i].id_medico, id_medico); // Alla prima cella vuota del vettore aggiungo l'id_medico
                break;
            }
        }
    }

    // Aggiungo il paziente al turno del medico
    for (int i = 0; i < n_medici; i++) {
        if (strcmp(medici[i].id_medico, id_medico) == 0) { // Cerco il medico
            int turno_presente = 0;
            SingoloTurno *temp = medici[i].turni[giorno_richiesto]; // Puntatore ausiliare della lista turni
            // Controllo se la lista turni è già stata inizializzata
            while (temp != NULL) {
                if (temp->id_turno == turno_richiesto) { // Cerco il turno richiesto dal cliente
                    turno_presente = 1;
                    if (temp->pazienti_per_turno < 5) {
                        medici[i].turni[giorno_richiesto]->pazienti_per_turno++; // Aggiungo un paziente al turno del medico
                    } else {
                        esuberi[i].turni[giorno_richiesto]->pazienti_per_turno++; // Aggiungo l'appuntamento nel vettore esuberi se i pazienti in quel turno sono più di 5
                    }
                    break;
                }
                temp = temp->next;
            }

            if (!turno_presente) {
                // Inizializzo la lista turni per quel giorno specifico
                SingoloTurno *nuovo = (SingoloTurno *)malloc(sizeof(SingoloTurno));
                if (nuovo == NULL) {
                    return ERRORE_ALLOCAZIONE;
                }
                nuovo->id_turno = turno_richiesto;
                nuovo->pazienti_per_turno = 0;
                SingoloTurno *testa = medici[i].turni[giorno_richiesto]; // Mi salvo la testa della lista turni
                // Inserisco in testa alla lista
                nuovo->next = testa;
                testa = nuovo;
            }
        }
    }

    return USCITA_CON_SUCCESSO;
}

// Ricorsiva per stampare i pazienti in esubero
void stampa_esuberi(Esubero esuberi[], SingoloTurno *temp, int *medico, int *giorno, int *pazienti_in_esubero) {
    static int primo = 1;
    if (primo) {
        primo = 0;
        temp = esuberi[0].turni[0];
    }
    if (temp == NULL) { // Se la lista turni è conclusa passo al turno successivo
        printf("Pazienti in esubero per il giorno %d sono %d", *giorno, *pazienti_in_esubero);
        *pazienti_in_esubero = 0;
        *giorno++;
        if (*giorno >= 7) { // Se ho finito di scorrere i giorni del medico passo al medico successivo
            *medico++;
            *giorno = 0;
        }
        temp = esuberi[*medico].turni[*giorno]; // Passo al giorno successivo e/o medico successivo
    }
    *pazienti_in_esubero += temp->pazienti_per_turno;

    stampa_esuberi(esuberi, temp->next, medico, giorno, pazienti_in_esubero);
}

float *occupazione_medico(Medico *medici, int n_medici) {
    float *occupazione_percentuale = (float *)malloc(n_medici * sizeof(float));
    for (int i = 0; i < n_medici; i++) {
        for (int j = 0; j < N_GIORNI; j++) {
            occupazione_percentuale[i] = medici[i].turni[j]->pazienti_per_turno * 100 / MAX_PAZIENTI_PER_TURNO;
        }
    }

    return occupazione_percentuale;
}