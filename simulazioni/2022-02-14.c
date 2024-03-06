#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N_MEDICI 200
#define MAX_TURNI 8
#define N_GIORNI 7
#define MAX_PAZIENTI_PER_TURNO 5

#define N_REPARTI 50 // Indefinito

#define USCITA_CON_SUCCESSO 0
#define ERRORE_ALLOCAZIONE -1
#define ERRORE_FILE -2
#define ERRORE_VETTORE_PIENO -3
#define ERRORE_MEDICO_NON_TROVATO -4
#define ERRORE_TROPPI_TURNI -5

typedef struct singolo_turno {
    int id_turno; // Tra 1 e 8
    int pazienti_per_turno; // Tra 1 e 5
    struct singolo_turno *next;
} SingoloTurno;

typedef struct medico {
    char id_medico[13]; // Ordinato per id_medico crescente
    char reparto[6];
    SingoloTurno *turni[N_GIORNI]; // In totale 8 turni
} Medico;

typedef struct esubero_reparto {
    char reparto[6];
    SingoloTurno *turni[N_GIORNI];
} EsuberoReparto;

int aggiungi_paziente(Medico *medici, EsuberoReparto *esuberi, char id_medico[13], char reparto[6], int giorno_richiesto, int turno_richiesto);
int aggiungi_medico(Medico *medici, EsuberoReparto *esuberi, char id_medico[13], char reparto[6]);
int aggiungi_turno(Medico *medici, EsuberoReparto *esuberi, char id_medico[13], int giorno_richiesto, int turno_richiesto);

void stampa_esuberi(EsuberoReparto *esuberi, SingoloTurno *temp, int medico, int giorno, int pazienti_in_esubero);

float *occupazione_reparti(Medico *medici, char *reparti_medici[]);

int leggi_appuntamenti(char *nome_file, Medico *medici, EsuberoReparto *esuberi, char *reparti_medici[]);

int main() {
    Medico *medici = (Medico *)malloc(N_MEDICI * sizeof(Medico));
    if (medici == NULL) { // Controllo eventuali errori di allocazione
        puts("Errore allocazione");
        return ERRORE_ALLOCAZIONE;
    }
    for (int i = 0; i < N_MEDICI; i++) { // Inizializzo tutti i medici con id nullo in modo da sapere quando posso riempire una certa cella del vettore
        strcpy(medici[i].id_medico, "");
    }
    EsuberoReparto *esuberi = (EsuberoReparto *)malloc(N_MEDICI * sizeof(EsuberoReparto));
    if (esuberi == NULL) { // Controllo eventuali errori di allocazione
        puts("Errore allocazione");
        return ERRORE_ALLOCAZIONE;
    }

    return USCITA_CON_SUCCESSO;
}

float *occupazione_reparti(Medico *medici, char *reparti_medici[]) {
    float *percentuale_occupazione = (float *)malloc(N_REPARTI * sizeof(float));
    if (percentuale_occupazione == NULL) {
        puts("Errore allocazione memoria");
        exit(1);
    }
    // Inizializzo il vettore
    for (int i = 0; i < N_REPARTI; i++) {
        percentuale_occupazione[i] = 0.0f;
    }
    char *token;
    int max_pazienti = N_GIORNI * MAX_TURNI * MAX_PAZIENTI_PER_TURNO;
    for (int i = 0; i < N_MEDICI; i++) {
        // Ottengo l'indice del reparto del medico
        token = strtok(medici[i].id_medico, "-");
        token = strtok(NULL, "-");
        int indice_reparto = atoi(token);

        // Calcolo il totale dei pazienti per quel medico
        float pazienti_totali = 0.0f;
        for (int j = 0; j < N_GIORNI; j++) {
            SingoloTurno *temp = medici[i].turni[j];
            while (temp != NULL) {
                pazienti_totali += temp->pazienti_per_turno;
            }
        }
        // Calcolo la percentuale dei pazienti in quel reparto e la aggiungo se era già presente la percentuale di un altro medico nello stesso reparto
        percentuale_occupazione[indice_reparto] += pazienti_totali * 100 / max_pazienti;
    }
}

void stampa_esuberi(EsuberoReparto *esuberi, SingoloTurno *temp, int reparto, int giorno, int pazienti_in_esubero) {
    pazienti_in_esubero += temp->pazienti_per_turno;
    if (temp == NULL) { // Se la lista turni è conclusa passo al turno successivo
        printf("Pazienti in esubero per il giorno %d sono %d", giorno + 1, pazienti_in_esubero);
        pazienti_in_esubero = 0;
        giorno++;
        if (giorno >= 7) { // Se ho finito di scorrere i giorni del medico passo al medico successivo
            reparto++;
            giorno = 0;
            if (reparto >= N_REPARTI) {
                return;
            }
        }
        temp = esuberi[reparto].turni[giorno]; // Passo al giorno successivo e/o medico successivo
    }
    stampa_esuberi(esuberi, temp->next, reparto, giorno, pazienti_in_esubero);
}

int aggiungi_paziente(Medico *medici, EsuberoReparto *esuberi, char id_medico[13], char reparto[6], int giorno_richiesto, int turno_richiesto) {
    // Scorro i medici finché non trovo il medico richiesto
    for (int i = 0; i < N_MEDICI; i++) {
        if (strcmp(medici[i].id_medico, id_medico) == 0) {
            // Prendo la lista dei turni nel giorno richiesto
            SingoloTurno *temp = medici[i].turni[giorno_richiesto];
            SingoloTurno *temp_esub = esuberi[i].turni[giorno_richiesto];
            // Scorro la lista dei turni finché non trovo il turno richiesto
            while (temp != NULL) {
                if (temp->id_turno == turno_richiesto) {
                    if (temp->pazienti_per_turno < MAX_PAZIENTI_PER_TURNO) {
                        temp->pazienti_per_turno++;
                    } else {
                        temp_esub->pazienti_per_turno++;
                    }
                }
                temp = temp->next;
            }
        }
    }
}

// Funzione per aggiungere un turno ad un certo medico
int aggiungi_turno(Medico *medici, EsuberoReparto *esuberi, char id_medico[13], int giorno_richiesto, int turno_richiesto) {
    for (int i = 0; i < N_MEDICI; i++) {
        if (strcmp(medici[i].id_medico, id_medico) == 0) {
            // Controllo se i turni sono già 8
            int turni = 0;
            SingoloTurno *temp = medici[i].turni[giorno_richiesto];
            while (temp != NULL) {
                if (temp->id_turno = turno_richiesto) {
                    return USCITA_CON_SUCCESSO; // Il turno è già presente
                }
                temp = temp->next;
                turni++;
            }
            if (turni > 8) { // I turni sono già occupati e restituisco un codice di errore
                return ERRORE_TROPPI_TURNI;
            }

            SingoloTurno *nuovo_turno = (SingoloTurno *)malloc(sizeof(SingoloTurno));
            if (nuovo_turno == NULL) { // Controllo eventuali errori di allocazione
                return ERRORE_ALLOCAZIONE;
            }
            nuovo_turno->id_turno = turno_richiesto;
            nuovo_turno->pazienti_per_turno = 0;

            // Inserisco in testa il nuovo turno
            nuovo_turno->next = medici[i].turni[giorno_richiesto]; 
            medici[i].turni[giorno_richiesto] = nuovo_turno;
            esuberi[i].turni[giorno_richiesto] = nuovo_turno; // Se è presente in medici è presente anche in esuberi, quindi non controllo le ripetizioni di esuberi
            return USCITA_CON_SUCCESSO; // Una volta trovato il medico e aggiunto il turno esco dalla funzione
        }
    }
    return ERRORE_MEDICO_NON_TROVATO;
}

// Funzione per aggiungere un medico al vettore di medici
int aggiungi_medico(Medico *medici, EsuberoReparto *esuberi, char id_medico[13], char reparto[6]) {
    for (int i = 0; i < N_MEDICI; i++) {
        if (strcmp(medici[i].id_medico, id_medico) == 0) {
            return USCITA_CON_SUCCESSO; // Il medico è già presente
        }
        if (strcmp(medici[i].id_medico, "") == 0) { // Controllo quali celle medico sono vuote
            strcpy(medici[i].id_medico, id_medico);
            strcpy(medici[i].reparto, reparto);
            strcpy(esuberi[i].reparto, reparto);
            return USCITA_CON_SUCCESSO; // Appena trovata la cella vuota esce dalla funzione
        }
    }
    return ERRORE_VETTORE_PIENO; // Se il vettore medici è pieno restituisco un codice di errore
}

// Reparti medici è un vettore di stringhe già presente è inizializzato
int leggi_appuntamenti(char *nome_file, Medico *medici, EsuberoReparto *esuberi, char *reparti_medici[]) {
    FILE *f = fopen(nome_file, "r");
    if (f == NULL) { // Se non riesce ad aprire il file ritorno un codice di errore
        return ERRORE_FILE;
    }
    
    char *token;
    char riga[500];
    char id_paziente[13], id_medico[13], codice_richiesta_prestazione[26], reparto[6];
    int giorno_richiesto, turno_richiesto;
    while (fgets(riga, sizeof(riga), f) != NULL) { // Si presuppone il file sia formattato correttamente
        token = strtok(riga, " ");
        strcpy(id_paziente, token);
        token = strtok(NULL, " ");
        strcpy(id_medico, token);
        token = strtok(NULL, " ");
        strcpy(codice_richiesta_prestazione, token);
        token = strtok(NULL, " ");
        turno_richiesto = atoi(token);
        token = strtok(NULL, " ");
        giorno_richiesto = atoi(token);

        // Ottengo l'indice del reparto del medico
        token = strtok(id_medico, "-");
        token = strtok(NULL, "-");
        int indice_reparto = atoi(token);
        strcpy(reparto, reparti_medici[indice_reparto]);
        // Inizializzo anche gli esuberi
        if (aggiungi_medico(medici, esuberi, id_medico, reparto) != USCITA_CON_SUCCESSO) {
            exit(EXIT_FAILURE);
        }
        if (aggiungi_turno(medici, esuberi, id_medico, giorno_richiesto, turno_richiesto) != USCITA_CON_SUCCESSO) {
            exit(EXIT_FAILURE);
        }
        aggiungi_paziente(medici, esuberi, id_medico, reparto, giorno_richiesto, turno_richiesto);
    }


    return USCITA_CON_SUCCESSO;
}