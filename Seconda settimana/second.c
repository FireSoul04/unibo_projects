#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Funzione che restituisce un numero casuale con un minimo e un massimo scelto
int random(int min, int max){
    srand(time(NULL));
    return min + rand() % (max - min + 1);
}

int main() {
    int min = 1, max = 0, // Definisco minimo, massimo
        tries = 0, maxTries, scelta, // Definisco i tentativi e la scelta dell'utente
        number, lastNumber; // Definisco il numero generato attualmente e il numero generato il tentativo precedente

    // Controllo che l'utente inserisca un massimo più grande del minimo di almeno 1 e che siano diversi da 0
    while(max < min) {
        printf("Inserisci il massimo dell'intervallo: ");
        scanf("%d", &max);
        fflush(stdin);
        printf("Inserisci il minimo dell'intervallo: ");
        scanf("%d", &min);
        fflush(stdin);
        if (max < min) {
            printf("Il massimo deve essere piu' grande del minimo\n");
        }
        if (max < 0 || min < 0) {
            printf("I valori negativi non sono ammessi\n");
            max = 0;
            min = 0;
        }
    }

    // Controllo che l'utente inserisca un numero di tentativi maggiore di 0
    while(tries < 1) {
        printf("Inserisci quanti tentativi ho a disposizione: ");
        scanf("%d", &tries);
        maxTries = tries;
        if (tries < 1) {
            printf("Deve essere più grande di 0\n");
        }
    }

    // scelta:
    // 0 = numero da indovinare è più piccolo
    // 1 = numero da indovinare è più grande
    // 2 = numero è uguale
    while(!(scelta == 2 || tries <= 0)) { // Eseguo il gioco finché il numero sia quello scelto dall'utente oppure i tentativi siano esauriti
        number = random(min, max); // Genero un numero random

        printf("Tentativi rimasti: %d\n", tries);
        printf("Numero proposto: %d\n", number);
        printf("0 = il numero e' piu' grande\n1 = il numero e' piu' piccolo\n2 = il numero e' quello che stavo pensando\nScelta: ");
        scanf("%d", &scelta);
        fflush(stdin);

        // Controllo che la scelta sia compresa tra 0 e 2
        do {
            switch(scelta) {
                case 0:
                    printf("Riprovo con un numero piu' grande\n");
                    lastNumber = number; // Salva il numero per il prossimo tentativo
                    min = number;
                    tries--; // Riduce i tentativi
                    break;
                case 1:
                    printf("Riprovo con un numero piu' piccolo\n");
                    lastNumber = number; // Salva il numero per il prossimo tentativo
                    max = number;
                    tries--; // Riduce i tentativi
                    break;
                case 2:
                    printf("Ho indovinato!\n");
                    break;
                default:
                    printf("La scelta deve essere un numero compreso tra 0 e 2\n");
                    break;
            }
        } while(!(scelta >= 0 || scelta <= 2));

        if (max == min) { // Controllo che l'utente non abbia inserito che il numero scelto da lui sia più grande del massimo
            printf("Hai provato a fregarmi eh? Ho vinto!\n");
            tries++;
            break; // Conclude il gioco
        }
    }

    if (tries <= 0) {
        printf("Tentativi esauriti!");
    } else {
        printf("Tentativi utilizzati: %d", maxTries - tries);
    }

    return 0;
}