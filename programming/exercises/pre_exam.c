#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Giocatore {
    char nome[30];
    char cognome[30];
    int punteggio;
} G;

typedef struct Partita {
    G giocatore1;
    G giocatore2;
    struct Partita *next;
} P;

typedef struct Torneo {
    P *testa_torneo;
    char nome[30];
    struct Torneo *next;
} T;

typedef struct Giocatori {
    G giocatore;
    int vittorie;
    struct Giocatori *next;
} Gi;

G punteggioMax(T *tornei) {
    G gret = { "NULL", "NULL", -1 };
    if (tornei == NULL) {
        return gret;
    }

    T *current_torneo = tornei;
    while (current_torneo != NULL) {
        P *current_partita = tornei->testa_torneo;
        while (current_partita != NULL) {
            G g1 = current_partita->giocatore1;
            G g2 = current_partita->giocatore2;
            G *vincitore;

            if (g1.punteggio >= g2.punteggio) {
                vincitore = &g1;
            } else {
                vincitore = &g2;
            }

            if (vincitore->punteggio >= gret.punteggio) {
                gret = *vincitore;
            }

            current_partita = current_partita->next;
        }
        current_torneo = current_torneo->next;
    }

    return gret;
}

int numVittorie(T *tornei, char nome[30]) {
    if (tornei == NULL) {
        return 0;
    }

    int vittorie = 0;
    T *current_torneo = tornei;
    while (current_torneo != NULL) {
        P *current_partita = tornei->testa_torneo;
        while (current_partita != NULL) {
            G g1 = current_partita->giocatore1;
            G g2 = current_partita->giocatore2;
            G *vincitore;

            if (g1.punteggio >= g2.punteggio) {
                vincitore = &g1;
            } else {
                vincitore = &g2;
            }
            
            if (strcmp(vincitore->nome, nome) == 0) {
                vittorie++;
            }

            current_partita = current_partita->next;
        }
        current_torneo = current_torneo->next;
    }

    return vittorie;
}

int addNode(Gi **giocatori, G *giocatore, T *tornei) {
    Gi *newG = (Gi*)malloc(sizeof(Gi));
    if (newG == NULL) {
        return -1;
    }

    newG->giocatore = *giocatore;
    newG->vittorie = numVittorie(tornei, giocatore->nome);
    newG->next = NULL;

    if (*giocatori == NULL) {
        *giocatori = newG;
    } else {
        Gi *temp = *giocatori;
        while (temp != NULL) {
            // if (strcmp(giocatore->nome, temp->giocatore.nome) == 0) {
            //     break;
            // }
            if (temp->vittorie >= newG->vittorie) {
                Gi *tmp = temp->next;
                newG->next = tmp;
                temp = newG;
                break;
            }
            temp = temp->next;
        }
    }
}

int printList(Gi *list) {
    Gi *current = list;
    while (current != NULL) {
        printf("%d", current->giocatore.punteggio);
        current = current->next;
    }
}

int main() {
    G g1 = { "A", "", 5 };
    G g2 = { "B", "", 5 };
    G g3 = { "C", "", 2 };
    G g4 = { "D", "", 1 };

    P partita1 = { g1, g2, NULL };
    P partita2 = { g1, g3, NULL };
    P partita3 = { g2, g3, NULL };
    P partita4 = { g2, g4, NULL };

    partita1.next = &partita2;
    partita2.next = &partita3;
    partita3.next = &partita4;

    T tornei = { &partita1, "Wimbledon", NULL };

    Gi *list = NULL;
    addNode(&list, &g1, &tornei);
    addNode(&list, &g2, &tornei);
    addNode(&list, &g3, &tornei);
    addNode(&list, &g4, &tornei);

    printf("%s", punteggioMax(&tornei).nome);

    printList(list);
    system("pause");

    return 0;
}