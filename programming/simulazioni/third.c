#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LUNGHEZZA_MEDICI 200
#define LUNGHEZZA_STRINGA 100
#define LUNGHEZZA_ID 12

typedef struct SINGOLO_TURNO {
    int id_turno; // Compreso tra 1 e 8
    int pazienti_per_turno; // Compreso tra 0 e 5 
    struct SINGOLO_TURNO *next;
} SingoloTurno;

typedef struct MEDICO {
    char id_medico[12];
    char reparto[30];
    SingoloTurno *turni[7];
} Medico;

typedef struct ESUBERO {
    SingoloTurno *turni[7];
} Esubero;

int bubble_sort(Medico *, int);
int aggiungi_a_lista(SingoloTurno **, int, int);
int leggi_appuntamenti(char *, Medico *, Esubero *);

int main() {
    Medico *medici = (Medico *)malloc(sizeof(Medico) * LUNGHEZZA_MEDICI);
    Esubero esuberi[10];
    leggi_appuntamenti("appuntamenti.txt", medici, esuberi);
    bubble_sort(medici, LUNGHEZZA_MEDICI);

    return 0;
}

// Ordina per id_medico
int bubble_sort(Medico *medici, int lunghezza_medici) {
    int sort = 0;
    // Quando ha finito di ordinare esce
    while (!sort) {
        sort = 1;
        for (int i = 0; i < lunghezza_medici - 1; i++) {
            // Scorro la stringa
            for (int j = 0; j < LUNGHEZZA_ID; i++) {
                // Appena trova un carattere più grande scambia l'ordine dei medici
                if (medici[i].id_medico[j] > medici[i - 1].id_medico[j]) {
                    sort = 0;
                    Medico tmp = medici[i];
                    medici[i] = medici[i - 1];
                    medici[i - 1] = tmp;
                    break;
                }
            }
        }
    }
}

// Aggiunge il nodo alla lista dei turni
int aggiungi_a_lista(SingoloTurno **testa, int id_turno, int pazienti_per_turno) {
    SingoloTurno *nuovo = (SingoloTurno *)malloc(sizeof(SingoloTurno));
    if (nuovo == NULL) {
        puts("Stack overflow...");
        exit(1);
    }
    // Crea un nuovo nodo
    nuovo->id_turno = id_turno;
    nuovo->pazienti_per_turno = pazienti_per_turno;
    nuovo->next = NULL;

    // Aggiunge alla testa se la lista è vuota
    if (*testa == NULL) {
        *testa = nuovo;
    } else {
        // Scorre la lista fino alla coda e aggiunge alla coda
        SingoloTurno *temp = *testa;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nuovo;
    }

    return 0;
}

// Legge il file
int leggi_appuntamenti(char nome_file[], Medico *medici, Esubero esuberi[10]) {
    static int num_esuberi = 0;
    FILE *appuntamenti = fopen(nome_file, "r");
    if (appuntamenti == NULL) {
        puts("File non trovato...");
        exit(1);
    }

    char *token;
    char riga[LUNGHEZZA_STRINGA];
    for (int i = 0; fgets(riga, LUNGHEZZA_STRINGA - 1, appuntamenti) != NULL; i++) {
        token = strtok(riga, " ");
        for (int j = 0; token != NULL; j++) {
            switch (j) {
                case 0:
                    break;
                case 1:
                    strcpy(medici[i].id_medico, token); break;
                case 2:
                    SingoloTurno *temp = medici[i].turni;
                    int id_turno = atoi(token);
                    while (temp != NULL) {
                        if (id_turno > 8 || id_turno < 1) {
                            puts("Id turno invalido");
                            break;
                        }
                        if (temp->id_turno == id_turno) {
                            
                        }
                    }
                    break;
            }
            token = strtok(NULL, " ");
        }
    }
}