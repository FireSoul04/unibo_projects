#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32 // valido sia per 32 che 64 bit
	#define CLEAR system("cls") // Definisco una funzione per pulire la console
#else
    #define CLEAR system("clear") // Definisco una funzione per pulire la console
#endif

// Timer di un numero di secondi deciso in input
#define TIMER(seconds) (current_time) = time(NULL); while (time(NULL) - current_time < seconds)

// Numero per passare da ASCII a un numero (lo 0 in ASCII parte da 48)
#define ASCII_TO_NUMBER 48

// Associa un colore in ANSI C per la mappa
#define COLOR_OCEAN "\033[40m"
#define COLOR_AMERICA "\033[42m"
#define COLOR_AFRICA "\033[46m"
#define COLOR_ASIA "\033[43m"
#define COLOR_EUROPE "\033[44m"
#define COLOR_AUSTRALIA "\033[45m"

// Associa il rosso in ANSI C da mostrare nella mappa quando un giocatore perde
#define COLOR_WRONG "\033[41m"

// Associa un numero ad ogni continente più l'oceano
#define OCEAN 0
#define AMERICA 1
#define AFRICA 2
#define AUSTRALIA 3
#define ASIA 4
#define EUROPE 5

/*La mappa è un array di numeri, ogni numero corrisponde a un continente e a quanti punti restituisce,
è gestita in modo che ogni continente può dare minimo un punto e massimo tre e ogni continente nella mappa ha un valore che
è divisibile per tre e essendo una divisione tra interi restituirà il risultato del rapporto senza resto.
Esempio: una cella appartiene all'America se vale da 3 a 5, se eseguo la divisione 5/3 ottengo 1, che corrisponde al continente America nel gioco.
L'oceano restituisce sempre un punto.*/

// Dimensioni della mappa
#define MAP_HEIGHT 25 // Altezza della mappa
#define MAP_LENGTH 50 // Lunghezza della mappa
#define MAP_AREA (MAP_HEIGHT * MAP_LENGTH) // Area della mappa

// Calcoli per ottenere un indice dell'array mappa partendo da x e y
#define AXES_TO_ARRAY_INDEX(x, y) ((MAP_LENGTH) * (y) + (x)) // Partendo da x e y in input, restituisce l'indice dell'array mappa corrispondente
#define POSITION_IN(x, y) (world_map[AXES_TO_ARRAY_INDEX((x), (y))]) // Partendo da x e y in input, restituisce la cella di mappa corrispondente
#define CONTINENT_IN(x, y) (POSITION_IN((x), (y)) / 3) // Partendo da x e y in input, restituisce il continente che si trova in quella posizione della mappa 

// Carattere per concludere una stringa
#define END_CHAR '\0'

// Array dei continenti disponibili più l'oceano
const unsigned int continents[6] = { 
    OCEAN, AMERICA, AFRICA,
    AUSTRALIA, ASIA, EUROPE
};

// Mappa che viene utilizzata per associare in che posizione si trova ogni stato
const unsigned char world_map[MAP_AREA] = { 
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 0, 3, 3, 4, 4, 4, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 4, 4, 3, 0, 0, 0, 3, 4, 5, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 3, 3, 3, 3, 4, 4, 4, 4, 4, 3, 3, 0, 0, 3, 4, 4, 3, 0, 0, 0, 0, 0, 0, 15, 15, 0, 0, 0, 0, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0,
    0, 0, 3, 3, 3, 4, 4, 4, 5, 5, 5, 4, 4, 3, 3, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 15, 15, 15, 12, 12, 12, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 12, 12, 12, 0, 0,
    0, 0, 0, 0, 3, 3, 3, 4, 4, 5, 5, 5, 4, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 16, 15, 12, 13, 13, 13, 13, 13, 13, 13, 14, 14, 13, 13, 12, 12, 12, 12, 12, 12, 12, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 3, 4, 4, 5, 5, 5, 4, 4, 3, 3, 0, 0, 0, 0, 0, 0, 0, 15, 15, 16, 16, 15, 12, 12, 13, 13, 14, 14, 14, 14, 14, 14, 14, 13, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 3, 4, 4, 5, 5, 4, 4, 3, 3, 0, 0, 0, 0, 0, 0, 0, 15, 16, 16, 16, 15, 15, 12, 12, 13, 14, 14, 14, 14, 14, 14, 14, 14, 13, 12, 12, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 3, 4, 4, 5, 5, 4, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 15, 16, 15, 15, 15, 15, 12, 12, 13, 13, 14, 14, 14, 14, 14, 14, 13, 13, 13, 12, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 3, 3, 4, 4, 5, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 15, 15, 0, 15, 12, 12, 13, 13, 13, 14, 14, 14, 14, 14, 13, 13, 12, 12, 12, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 4, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 6, 0, 12, 12, 12, 13, 13, 13, 13, 13, 13, 13, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 4, 4, 3, 0, 0, 0, 0, 0, 0, 0, 6, 6, 7, 7, 7, 6, 6, 6, 12, 12, 12, 12, 12, 12, 12, 12, 13, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 4, 3, 3, 0, 0, 0, 0, 0, 6, 7, 7, 8, 8, 7, 7, 6, 6, 6, 0, 0, 0, 12, 0, 12, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 4, 3, 0, 0, 0, 0, 0, 6, 6, 6, 7, 8, 8, 8, 7, 6, 0, 0, 0, 0, 0, 0, 0, 12, 13, 12, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 3, 3, 0, 0, 0, 0, 0, 0, 0, 6, 7, 8, 8, 7, 6, 0, 0, 0, 0, 0, 0, 0, 12, 13, 13, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 4, 4, 3, 0, 0, 0, 0, 0, 0, 0, 6, 8, 7, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 12, 12, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 5, 4, 3, 3, 0, 0, 0, 0, 0, 0, 6, 7, 6, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 0, 9, 9, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 5, 4, 3, 0, 0, 0, 0, 0, 0, 0, 6, 7, 6, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 10, 9, 0, 9, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 10, 10, 10, 9, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 4, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 10, 10, 9, 9, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 9, 9, 9, 9, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
};

// Colori associati ad ogni stato e all'oceano utilizzando lo standard ANSI C
const char fg_colors[6][7] = {
    COLOR_OCEAN, COLOR_AMERICA, COLOR_AFRICA,
    COLOR_AUSTRALIA, COLOR_ASIA, COLOR_EUROPE
};

// Mappa del mondo che verrà stampata a colori
char render_map[10 * MAP_AREA];

/**
 * Funzione che permette di mostrare la mappa del mondo mostrando ogni continente con un determinato colore
 * @param cell In caso si voglia mostrare una casella dove si ha sbagliato viene evidenziata in rosso (-1 se non la si vuole mostrare)
*/
void render(int cell) {
    // Pulisco il contenuto della stringa della mappa per ricostruirla
    render_map[0] = END_CHAR;

    // Ciclo per renderizzare ogni carattere (2 per la precisione) per costruire la mappa che verra visualizzata a schermo
    for (int i = 0; i < MAP_AREA; i++) {
        // Ogni riga va a capo
        if (i % MAP_LENGTH == 0 && i > 0) {
            strcat(render_map, "\n");
        }
        // Concatena i colori a 2 caratteri utilizzando lo standard ANSI C
        strcat(render_map, "\033[");

        // Mostra la casella giusta in caso di sconfitta
        if (i == cell) {
            strcat(render_map, COLOR_WRONG);
        } else {
            strcat(render_map, fg_colors[world_map[i] / 3]);
        }
        strcat(render_map, "  \033[");
    }

    // Mostra la mappa renderizzata
    puts(render_map);
}

/**
 * Funzione per calcolare il modificatore di punti in base alla zona del continente e tempo investito nella scelta
 * @param continent Continente situato nelle coordinate generate dal computer
 * @param choice_time Tempo che l'utente ha dedicato alla scelta
 * @returns Il modificatore di punti
*/
int score_modifier(int continent, int choice_time) {
    // Salvo quanto tempo ci mette l'utente a trovare la soluzione
    int time_elapsed = time(NULL) - choice_time;

    // In base al continente situato nelle coordinate appena generate, i punti saranno influenzati se sono più all'interno del continente
    int score_bonus = -1 * continent + 1;

    // In base al tempo dà un punteggio diverso (più di 4 secondi non aggiunge punti sul tempo)
    if (time_elapsed <= 1) {
        score_bonus += 3;
    } else if (time_elapsed <= 3) {
        score_bonus += 2;
    } else if (time_elapsed <= 4) {
        score_bonus++;
    }

    return score_bonus;
}

/**
 * Funzione per generare un numero casuale in un range scelto
 * @param min Minimo numero che può essere generato
 * @param max Massimo numero che può essere generato
 * @returns Il valore casuale scelto
*/
int random(int min, int max) {
    srand(clock());
    return min + rand() % (max - min) + 1;
}

int main() {
    bool game_over, // Controllo per concludere il ciclo quando l'utente perde
        retry; // Controllo se l'utente vuole rigiocare
    int x, // Coordinata x (lunghezza) generata dal computer
        y, // Coordinata y (altezza) generata dal computer
        actual_continent, // Continente che è situato nelle coordinate generate dal computer
        choice, // Qui salvo la scelta dell'utente ogni turno
        current_time, // Qui salvo il tempo per il timer in cui mostro la mappa
        score; // Qui salvo il punteggio dell'utente

    do {
        game_over = false; // Pongo la condizione di game over falsa
        retry = false;
        score = 0; // Azzero il punteggio
        choice = 0;

        // Pulisco la console per mostrare la mappa
        CLEAR;
        printf("MAPPA MONDO | Premi invio per iniziare\n");
        render(-1); // Renderizziamo la mappa e rimaniamo in attesa dell'input dell'utente per iniziare il gioco
        getchar();

        // Ciclo del gioco, si conclude quando il giocatore sbaglia
        do {
            // Pulisco la console e nascondo la mappa
            CLEAR;

            // Ottengo le coordinate casuali e le stampo
            x = random(0, MAP_LENGTH - 1);
            y = random(0, MAP_HEIGHT - 1);
            printf("Coordinate (%d, %d)\n", x, y);

            TIMER(2);
            // Pulisco la console e nascondo le coordinate
            CLEAR;

            // Salvo il tempo per controllare quanto ci mette l'utente per rispondere, in base al tempo vengono assegnati punti bonus
            current_time = time(NULL);

            printf("Score: %d\n", score);
            // Salvo che continente è (numero identificativo)
            actual_continent = CONTINENT_IN(x, y);
            printf("%d\n", AXES_TO_ARRAY_INDEX(x, y));

            printf("Selezionare un numero tra questi in base al tuo stato\n");
            printf("0: Oceano\n1: America\n2: Africa\n3: Australia\n4: Asia\n5: Europa\n");

            // Ciclo per controllare se la scelta è un numero compreso tra 0 e 5
            do {
                printf("Scelta: ");
                choice = getchar() - ASCII_TO_NUMBER; // Converto un numero da ASCII a numero (in ASCII lo zero corrisponde al 48)
                fflush(stdin); // Pulisco il buffer della console

                if (choice < 0 || choice > 5) { // Controllo se la scelta è compreso tra 0 e 5
                    printf("Deve essere compreso tra 0 e 5\n");

                    // Pongo la condizione di uscita del while in modo da continuare il ciclo finché non sceglie un numero valido
                    choice = -1;
                } else if (continents[actual_continent] == choice) { // Controllo se la scelta dell'utente è corretta
                    printf("Corretto!\n");

                    // Aumento i punti in base alla cella scelta e in base al tempo di risposta
                    score += POSITION_IN(x, y) + score_modifier(actual_continent, current_time);
                } else { // L'utente ha sbagliato, quindi perde e il programma si chiude
                    printf("Hai perso...\nIn quel punto e' presente: \n");
                    render(AXES_TO_ARRAY_INDEX(x, y)); // Mostra la casella che era giusta

                    // Pongo la condizione game over in modo da uscire dal ciclo del gioco
                    game_over = true;
                }
            } while (choice == -1);
        } while (!game_over);

        // Chiede all'utente se vuole rigiocare
        printf("\033[0BVuoi rigiocare? s/n: ");

        // Ciclo per controllare che l'utente inserisca si o no, se si torna all'inizio del gioco
        char ch;
        do {
            ch = getchar();
            fflush(stdin);
            if  (ch != 's' && ch != 'n') {
                printf("Inserisci s o n (si o no): ");
            }
        } while (ch != 's' && ch != 'n');

        retry = ch == 's';
    } while (retry);

    return 0;
}
