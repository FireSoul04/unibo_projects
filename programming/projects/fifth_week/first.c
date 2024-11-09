#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX 200

#ifdef _WIN32
    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
    #endif

    #define FFLUSH fflush(stdin)
    #define CLEAR system("cls")
#else
    void _fflush() {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {}
    }

    #define FFLUSH _fflush()
    #define CLEAR system("clear")
#endif

#define BLUE printf("\033[94m")
#define WHITE printf("\033[39m")
#define RESET printf("\033[m")

#define HIDE_CURSOR printf("\033[?25l")
#define MOVE_CURSOR(x, y) printf("\033[%d;%dH", y, x)

/**
 * Funzione per generare un numero casuale in un range scelto
 * @param min Minimo numero che può essere generato
 * @param max Massimo numero che può essere generato
 * @returns Il valore casuale scelto
*/
int random(int min, int max) {
    return min + rand() % (max - min);
}

/**
 * Funzione per cifrare e decifrare una stringa
 * @param str Stringa da cifrare e decifrare
*/
void crypt(char str[]) {
    CLEAR; // Pulisce i contenuti della console
    HIDE_CURSOR; // Nasconde il cursore della console
    srand(clock());
    printf("Decifrazione in corso...");

    /* 
        Il ciclo for che decifra utilizza k per gestire quanti caratteri per giro del ciclo while può decifrare
        insieme in modo da arrivare ad un punto in cui li decifra tutti insieme 
    */

    int length = strlen(str);
    int k = 0; // Contatore per gestire la velocità in cui decifra
    char converted_str[length];

    // Esegue un ciclo finché la stringa non è stata decifrata
    while (strcmp(converted_str, str)) {
        MOVE_CURSOR(0, 2); // Resetta la posizione all'inizio dello schermo
        
        // Converte ogni char in un char random della tabella ASCII estesa
        for (int i = 0; str[i] != '\0'; i++) {
            converted_str[i] = (char)(random(33, 254));
        }

        // Decifra valori casuali partendo quando il while ha eseguito almeno un numero di cicli pari alla lunghezza della stringa
        for (int i = k; k > length && i > length; i--) {
            int index = random(0, length); // Cerca un indice della stringa casuale
        
            converted_str[index] = str[index]; // Decifra un valore in posizione casuale
        }
        converted_str[length] = '\0'; // Chiudo la stringa in modo da non andare in buffer overflow
        k++; // Aumento il contatore di velocità

        // Stampa i caratteri decifrati in blu e quelli non decifrati in bianco
        for (int i = 0; str[i] != '\0'; i++) {
            char ch = converted_str[i];
            if (ch == str[i]) {
                BLUE; // Pongo i caratteri decifrati in blu
            } else {
                WHITE; // Pongo i caratteri cifrati in bianco
            }
            putchar(ch); // Stampo il carattere con il rispettivo colore
            RESET; // Chiudo il colore dell'ANSI C
        }
        
        // Aspetta 50 millisecondi prima di andare in modo da non essere troppo veloce
        while (clock() % 50 != 0);
    }
    printf("\n");
}

int main() {
    CLEAR;
    char str[MAX] = "";

    printf("Scrivi una stringa da crittografare\n");
    gets(str);
    FFLUSH;

    crypt(str);
    printf("Stringa decriptata con successo");

    return 0;
}