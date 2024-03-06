#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 21-06-2022

#define N_AGENTI 100

typedef struct APPUNTAMENTO {
    char id_cliente[11];
    char codice_richiesta_prestazione[16];
    struct APPUNTAMENTO *next;
} Appuntamento;

typedef struct AGENTE {
    char nome_cognome_agente[71];
    char id_agente[11];
    int n_clienti_agente;
    Appuntamento *testa_appuntamenti;
    struct AGENTE *next;
} Agente;

typedef struct AGENTE_NOMI {
    char nome_cognome_agente[71];
    char id_agente[11]; // Ordinato crescente per id_agente
} AgenteNomi;

void premio_agente_anno(Agente *testa);
void stampa_agenti(Agente *temp);
Agente* aggiungi_appuntamento(Agente *testa, AgenteNomi id_nomi_agenti[N_AGENTI], char id_cliente[11], char id_agente[11], char codice_richiesta_prestazione[16]);
Agente* leggi_appuntamenti(const char *nome_file, AgenteNomi id_nomi_agenti[N_AGENTI]);

int main() {
    Agente *lista_agenti = (Agente *)malloc(sizeof(Agente));
    if (lista_agenti == NULL) { // Controllo eventuali errori di memoria
        puts("Errore allocazione di memoria");
        exit(1);
    }
    const char *nome_file = "appuntamenti.txt";

    AgenteNomi id_nomi_agenti[N_AGENTI]; // Si presume già riempito e ordinato per id_agente
    Agente *testa = leggi_appuntamenti(nome_file, id_nomi_agenti);

    return 0;
}

// Crea la lista degli agenti in base alla lettura del file
Agente* leggi_appuntamenti(const char *nome_file, AgenteNomi id_nomi_agenti[N_AGENTI]) {
    Agente *testa = NULL;

    FILE *f = fopen(nome_file, "r");
    if (f == NULL) { // Controllo se il file è presente
        puts("File non trovato");
        exit(1);
    }
    
    char *token;
    char riga[500];
    char id_cliente[11], id_agente[11], codice_richiesta_prestazione[16];

    // Scorro ogni riga del file
    while (fgets(riga, 500, f) != NULL) {
        token = strtok(riga, " ");

        // Scorro ogni colonna del file
        int colonna = 0;
        while (token != NULL) {
            switch (colonna) {
                case 0:
                    strcpy(id_cliente, token);
                    break;
                case 1:
                    strcpy(id_agente, token);
                    break;
                case 2:
                    strcpy(codice_richiesta_prestazione, token);
                    break;
            }
            colonna++;
        }
        testa = aggiungi_appuntamento(testa, id_nomi_agenti, id_cliente, id_agente, codice_richiesta_prestazione);
    }

    fclose(f);
    return testa;
}

Agente* aggiungi_appuntamento(Agente *testa, AgenteNomi id_nomi_agenti[N_AGENTI], char id_cliente[11], char id_agente[11], char codice_richiesta_prestazione[16]) {
    // Cerco se l'agente è già presente nella lista
    int agente_presente = 0;
    Agente *agente = testa;
    while (agente != NULL) {
        if (strcmp(agente->id_agente, id_agente) == 0) {
            agente_presente = 1;
            break;
        }
        agente = agente->next;
    }

    // Creo il prossimo appuntamento
    Appuntamento *nuovo_app = (Appuntamento *)malloc(sizeof(Appuntamento));
    if (nuovo_app == NULL) { // Controllo eventuali errori di memoria
        puts("Errore allocazione di memoria");
        exit(1);
    }
    nuovo_app->next = NULL;
    strcpy(nuovo_app->id_cliente, id_cliente);
    strcpy(nuovo_app->codice_richiesta_prestazione, codice_richiesta_prestazione);

    if (!agente_presente) {
        // Creo il prossimo agente
        Agente *nuovo = (Agente *)malloc(sizeof(Agente));
        if (nuovo == NULL) { // Controllo eventuali errori di memoria
            puts("Errore allocazione di memoria");
            exit(1);
        }
        nuovo->next = NULL;
        nuovo->n_clienti_agente = 0;
        strcpy(nuovo->id_agente, id_agente);

        // Salva il nome dell'agente in base all'id
        Agente *temp = testa;
        while (temp != NULL) {
            // Scorro tutto l'array id_nomi_agenti e quando trovo il nome dell'agente corrispondente lo salvo nel nuovo nodo
            for (int i = 0; i < N_AGENTI; i++) {
                if (strcmp(id_agente, id_nomi_agenti[i].id_agente) == 0) {
                    strcpy(nuovo->nome_cognome_agente, id_nomi_agenti[i].nome_cognome_agente);
                    break;
                }
            }
            temp = temp->next;
        }

        // Il primo cliente sarà sempre la testa
        nuovo->testa_appuntamenti = nuovo_app;

        // Se la lista è vuota aggiungo alla testa
        if (testa == NULL) {
            testa = nuovo;
        } else { // Caso contrario aggiungo alla coda o alla prima occorrenza già presente
            temp = testa;
            // Scorro finchè la lista non è conclusa oppure quando trovo l'agente corrispondente
            while (temp->next != NULL && strcmp(id_agente, temp->next->id_agente) != 0) {
                temp = temp->next;
            }
            temp->next = nuovo;
        }
    } else { // Se è già presente nella lista aggiungo un appuntamento
        nuovo_app->next = agente->testa_appuntamenti;
        agente->testa_appuntamenti = nuovo_app;
        agente->n_clienti_agente++;
    }

    return testa;
}

void stampa_agenti(Agente *temp) {
    // Scorro la lista finché non arriva alla coda
    if (temp != NULL) {
        return;
    }

    printf("Id agente: %s, Nome: %s\n", temp->id_agente, temp->nome_cognome_agente);
    printf("Appuntamenti:\n");
    // Scorro la lista degli appuntamenti
    Appuntamento *temp_app = temp->testa_appuntamenti;
    while (temp_app != NULL) {
        printf("Id cliente: %s, codice richiesta: %s", temp_app->id_cliente, temp_app->codice_richiesta_prestazione);
        temp_app = temp_app->next;
    }
    stampa_agenti(temp->next);
}

void premio_agente_anno(Agente *testa) {
    // Salvo i tre valori più grandi in un vettore di 3 int
    int max[3] = { 0, 0, 0 };
    char *nomi[3];
    Agente *temp = testa;
    while (temp != NULL) {
        for (int i = 0; i < 3; i++) {
            // Controllo in quale posizione trova il massimo
            // Se non trova il massimo nella prima posizione controlla la seconda e così anche la terza
            if (temp->n_clienti_agente > max[i]) {
                max[i] = temp->n_clienti_agente;
                strcpy(nomi[i], temp->nome_cognome_agente);
                break;
            }
        }
        temp = temp->next;
    }
    // Stampo i risultati
    printf("Primo posto: %d\n", nomi[0]);
    printf("Secondo posto: %d\n", nomi[1]);
    printf("Terzo posto: %d\n", nomi[2]);
}