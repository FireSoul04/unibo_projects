#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SOGLIA_PESO 1000.0f // Soglia per dividere un pacco pesante da uno leggero

typedef struct pacchi {
    int id_pacco;
    float peso_kg;
    float valore;
    struct pacchi *next;
} Pacchi;

typedef Pacchi PilaPacchi;
typedef Pacchi PacchiInDogana;

typedef struct camion {
    int id_camion;
    PilaPacchi *pacchi;
} Camion;

typedef struct coda_camion {
    Camion *camion;
    int lunghezza;
    int coda;
} CodaCamion;

PacchiInDogana *aggiungi_pacco(PacchiInDogana *pacchi, int id_pacco, float peso_kg, float valore);
int statistica_pacchi_pesanti(CodaCamion *coda_camion);
void unisci_pacchi(PacchiInDogana **pacchi, PacchiInDogana *pacchi_leggeri, PacchiInDogana *pacchi_pesanti);

// Funzioni per gestire la coda di camion
int aggiungi_a_coda(CodaCamion *coda_camion, PilaPacchi *pacchi, int id_camion);

// Funzioni per gestire la pila di pacchi
int pila_vuota(PilaPacchi *pila_pacchi);
PilaPacchi *push(PilaPacchi *pila_pacchi, int id_pacco, float peso_kg, float valore);
PilaPacchi *pop(PilaPacchi **pila_pacchi);

CodaCamion *arrivo_in_dogana(CodaCamion *coda_camion, Camion *camion, PilaPacchi **pacchi_pesanti, PilaPacchi **pacchi_leggeri);

int main() {
    

    return 0;
}

void unisci_pacchi(PacchiInDogana **pacchi, PacchiInDogana *pacchi_leggeri, PacchiInDogana *pacchi_pesanti) {
    if (pacchi_leggeri == NULL && pacchi_pesanti == NULL) { // Quando sono entrambe vuote chiudo
        return;
    }

    if (pacchi_leggeri != NULL) { // Aggiungo in testa il pacco leggero
        pacchi = aggiungi_pacco(pacchi, pacchi_leggeri->id_pacco, pacchi_leggeri->peso_kg, pacchi_leggeri->valore);
        if (pacchi == NULL) { // Controllo eventuali errori di memoria
            puts("Errore di allocazione di memoria");
            exit(1);
        }
        unisci_pacchi(pacchi, pacchi_leggeri->next, pacchi_pesanti); // Scorro la lista dei pacchi leggeri
    } else if (pacchi_pesanti != NULL) { // Aggiungo in testa il pacco pesante
        pacchi = aggiungi_pacco(pacchi, pacchi_pesanti->id_pacco, pacchi_pesanti->peso_kg, pacchi_pesanti->valore);
        if (pacchi == NULL) { // Controllo eventuali errori di memoria
            puts("Errore di allocazione di memoria");
            exit(1);
        }
        unisci_pacchi(pacchi, pacchi_leggeri, pacchi_pesanti->next); // Scorro la lista dei pacchi pesanti
    }
}

int statistica_pacchi_pesanti(CodaCamion *coda_camion) {
    int id_camion = -1; // Se la coda è vuota ritorna -1
    int max_pacchi = 0;

    for (int i = 0; i < coda_camion->lunghezza; i++) {
        int pacchi_pesanti = 0;
        PilaPacchi *temp = coda_camion[i].camion->pacchi;
        PilaPacchi *pila_aux = NULL;
        while (temp != NULL) {
            temp = pop(&temp);
            if (temp->peso_kg >= SOGLIA_PESO) {
                pacchi_pesanti++;
            }
            pila_aux = push(pila_aux, temp->id_pacco, temp->peso_kg, temp->valore);
            if (pila_aux == NULL) { // Controllo eventuali errori di memoria
                puts("Errore di allocazione di memoria");
                exit(1);
            }
        }

        while (pila_aux != NULL) {
            pila_aux = pop(&pila_aux);
            temp = push(temp, pila_aux->id_pacco, pila_aux->peso_kg, pila_aux->valore);
            if (temp == NULL) { // Controllo eventuali errori di memoria
                puts("Errore di allocazione di memoria");
                exit(1);
            }
        }

        if (pacchi_pesanti > max_pacchi) { // Salvo il numero maggiore di pacchi pesanti
            max_pacchi = pacchi_pesanti;
            id_camion = coda_camion[i].camion->id_camion;
        }
    }

    return id_camion;
}

PacchiInDogana *aggiungi_pacco(PacchiInDogana *pacchi, int id_pacco, float peso_kg, float valore) {
    PacchiInDogana *nuovo = (PacchiInDogana *)malloc(sizeof(PacchiInDogana));
    if (nuovo == NULL) {
        return NULL;
    }
    // Aggiungo in testa
    nuovo->next = pacchi;
    pacchi = nuovo;
    return pacchi;
}

CodaCamion *arrivo_in_dogana(CodaCamion *coda_camion, Camion *camion, PilaPacchi **pacchi_pesanti, PilaPacchi **pacchi_leggeri) {
    if (aggiungi_a_coda(coda_camion, camion->pacchi, camion->id_camion) == -1) { // Controllo eventuali errori di memoria
        puts("Errore di allocazione di memoria");
        exit(1);
    }

    PilaPacchi *temp = camion->pacchi;
    PilaPacchi *pila_aux = NULL;
    while (temp != NULL) { // Scorro la pila dei pacchi
        temp = pop(&temp);
        if (temp->peso_kg >= SOGLIA_PESO) { // Suddivido i pacchi in base al peso
            *pacchi_pesanti = aggiungi_pacco(*pacchi_pesanti, temp->id_pacco, temp->peso_kg, temp->valore);
            if (*pacchi_pesanti == NULL) { // Controllo eventuali errori di memoria
                puts("Errore di allocazione di memoria");
                exit(1);
            }
        } else {
            *pacchi_leggeri = aggiungi_pacco(*pacchi_leggeri, temp->id_pacco, temp->peso_kg, temp->valore);
            if (*pacchi_leggeri == NULL) { // Controllo eventuali errori di memoria
                puts("Errore di allocazione di memoria");
                exit(1);
            }
        }
        pila_aux = push(pila_aux, temp->id_pacco, temp->peso_kg, temp->valore);
        if (pila_aux == NULL) { // Controllo eventuali errori di memoria
            puts("Errore di allocazione di memoria");
            exit(1);
        }
    }

    // Prendo la pila ausiliaria e inserisco nella vecchia pila seguendo lo stesso ordine di partenza dei nodi
    while (pila_aux != NULL) { // Scorro la pila dei pacchi
        pila_aux = pop(&pila_aux);
        temp = push(temp, pila_aux->id_pacco, pila_aux->peso_kg, pila_aux->valore);
        if (temp == NULL) { // Controllo eventuali errori di memoria
            puts("Errore di allocazione di memoria");
            exit(1);
        }
    }
}

int aggiungi_a_coda(CodaCamion *coda_camion, PilaPacchi *pacchi, int id_camion) {
    if (coda_camion == NULL) {
        coda_camion->lunghezza = 1; // Inizializzo a 1 la lunghezza
        coda_camion->coda = 0; // Inizializzo la coda a 0
        coda_camion->camion = (CodaCamion *)malloc(sizeof(CodaCamion));
        if (coda_camion->camion == NULL) {
            return -1;
        }
        coda_camion->camion[0].pacchi = pacchi;
        coda_camion->camion[0].id_camion = id_camion;
    } else {
        coda_camion->lunghezza++; // Aumento la lunghezza del vettore
        coda_camion->camion = (CodaCamion *)realloc(coda_camion->camion, coda_camion->lunghezza * sizeof(CodaCamion));
        if (coda_camion->camion == NULL) {
            return -1;
        }
        coda_camion->coda++; // Aumento l'indice della coda
        coda_camion->camion[coda_camion->coda].pacchi = pacchi;
        coda_camion->camion[coda_camion->coda].id_camion = id_camion;
    }
}

int pila_vuota(PilaPacchi *pila_pacchi) {
    return pila_pacchi == NULL; // Ritorna 1 quando la pila è vuota, 0 altrimenti
}

PilaPacchi *push(PilaPacchi *pila_pacchi, int id_pacco, float peso_kg, float valore) {
    PilaPacchi *nuovo = (PilaPacchi *)malloc(sizeof(PilaPacchi));
    if (nuovo == NULL) { // Controllo eventuali errori di memoria
        return NULL;
    }
    nuovo->id_pacco = id_pacco;
    nuovo->peso_kg = peso_kg;
    nuovo->valore = valore;

    nuovo->next = pila_pacchi; // Aggiungo alla pila
    pila_pacchi = nuovo;

    return pila_pacchi; // Ritorno la nuova testa della pila
}

PilaPacchi *pop(PilaPacchi **pila_pacchi) {
    if (pila_vuota(*pila_pacchi)) {
        return NULL; // La pila è vuota
    } else {
        PilaPacchi *temp = *pila_pacchi;
        *pila_pacchi = (*pila_pacchi)->next; // Muovo la testa della pila al nodo successivo
        return temp; // Ritorno la testa della pila
    }
}