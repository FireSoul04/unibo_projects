#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32 // valido sia per 32 che 64 bit
    #include <conio.h>
#else
    #include <termios.h>
    #include <unistd.h>

    int getch(void) {
        struct termios oldattr, newattr;
        int ch;
        tcgetattr( STDIN_FILENO, &oldattr );
        newattr = oldattr;
        newattr.c_lflag &= ~( ICANON | ECHO );
        tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
        ch = getchar();
        tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
        return ch;
    }

    int getche(void) {
        struct termios oldattr, newattr;
        int ch;
        tcgetattr( STDIN_FILENO, &oldattr );
        newattr = oldattr;
        newattr.c_lflag &= ~( ICANON );
        tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
        ch = getchar();
        tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
        return ch;
    }
#endif

// Timer di tot secondi
#define TIMER(seconds) (current_time) = time(NULL); while (time(NULL) - current_time < seconds);

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

// Definisco una macro per pulire la console utilizzando lo standard ANSI C
#define CLEAR printf("\033[H\033[J")
#define HIDE_CURSOR printf("\033[?25l")

// Definisco le dimensioni della mappa
#define MAP_LENGTH 10
#define MAP_HEIGHT 10
#define MAP_AREA 2 * MAP_HEIGHT * MAP_LENGTH + MAP_HEIGHT

// Definisco una funzione per spostare il cursone nella mappa utilizzando lo standard ANSI C
#define GO_TO(x,y) printf("\033[%d;%dH", (y + 1), (x * 2 + 1))

// Definisco il valore della prima lettera dell'alfabeto in modo da ottenere l'alfabeto intero incrementando il valore per ogni casella riempita
#define FIRST_LETTER 'A'

/**
 * Funzione per mostrare una mappa di char a schermo
 * @param map Mappa da mostrare a schermo
*/
void render(char map[MAP_HEIGHT][MAP_LENGTH]) {
    CLEAR;
    // Creo una stringa di dimensione 2 volte l'area giocabile + lo spazio per \n ogni riga
    char string_map[MAP_AREA] = "";
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_LENGTH; j++) {
            strncat(string_map, &map[i][j], 1);
            strcat(string_map, " ");
        }
        strcat(string_map, "\n");
    }
    // Stampo la stringa
    puts(string_map);
}

/**
 * Funzione per generare un numero casuale in un range scelto
 * @param min Minimo numero che può essere generato
 * @param max Massimo numero che può essere generato
*/
int random(int min, int max) {
    srand(time(NULL) / clock());
    return min + rand() % (max - min) + 1;
}

int main() { 
    int current_letter = 0, // Contatore che tiene conto di quale lettera si trova il computer
        current_time,
        x = 0, // Posizione x del computer
        y = 0; // Posizione y del computer

    // Definisco una mappa di caratteri come un array bidimensionale di char
    char map[MAP_HEIGHT][MAP_LENGTH];

    // Controllo se il computer non è più in grado di muoversi
    bool is_stuck = false;

    // Riempio la mappa con dei punti che indicano le caselle dove il computer non è passato
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_LENGTH; j++) {
            map[i][j] = '.';
        }
    }
    
    HIDE_CURSOR;
    // Ciclo principale del gioco, si conclude quando il computer è bloccato oppure riesce a riempire le caselle fino ad arrivare alla Z
    while ((FIRST_LETTER + current_letter) <= 'Z' && !is_stuck) {
        // Controllo se il computer può riempire la casella con una lettera
        if (map[y][x] == '.') {
            render(map); // Mostro la mappa

            GO_TO(x, y);
            TIMER(1);
            map[y][x] = FIRST_LETTER + current_letter; // Aggiungo la lettera nella mappa nella posizione attuale
            current_letter++; // Passo alla lettera dell'alfabeto successiva
        }

        // Controllo se il computer è bloccato in tutte le quattro direzioni o da lettere o dai confini, se sì il programma si conclude
        is_stuck = ((map[y][x + 1] != '.' || x == MAP_LENGTH - 1) 
            && (map[y][x - 1] != '.' || x == 0) 
            && (map[y + 1][x] != '.' || y == MAP_HEIGHT - 1) 
            && (map[y - 1][x] != '.' || y == 0));

        // Controllo se il tasto premuto dall'utente corrisponde a una delle 4 direzioni
        switch(random(0, 4) - 1) {
            case UP:
                if (map[y - 1][x] == '.') {
                    y--;                    
                }
                break;

            case DOWN:
                if (map[y + 1][x] == '.') {
                    y++;                    
                }
                break;

            case LEFT:
                if (map[y][x - 1] == '.') {
                    x--;                    
                }
                break;

            case RIGHT:
                if (map[y][x + 1] == '.') {
                    x++;                    
                }
                break;
        }

        // Controllo se il computer va oltre i limiti dell'array nelle x
        if (x > MAP_LENGTH - 1) {
            x = MAP_LENGTH - 1;
        } else if (x < 0) {
            x = 0;
        }

        // Controllo se il computer va oltre i limiti dell'array nelle y
        if (y > MAP_HEIGHT - 1) {
            y = MAP_HEIGHT - 1;
        } else if (y < 0) {
            y = 0;
        }
    }

    if (FIRST_LETTER + current_letter == 'Z') {
        printf("Hai vinto!\n");
    } else {
        printf("Hai perso...\n");
    }

    // Mostro la mappa aggiornata
    render(map);

    return 0;
}