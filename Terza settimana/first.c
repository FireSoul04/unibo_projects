#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32 // valido sia per 32 che 64 bit
	#define clear() system("cls");
#else
    #define clear() system("clear");
#endif

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
    #define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
#endif

// Timer di tot secondi
#define timer(seconds) (current_time) = time(NULL); while (time(NULL) - current_time < seconds);

// Numero per passare da ASCII a un numero (lo 0 in ASCII parte da 48)
#define ASCII_TO_NUMBER 48

// Associa un colore in ANSI C per la mappa
#define COLOR_OCEAN "\033[40m"
#define COLOR_AMERICA "\033[42m"
#define COLOR_AFRICA "\033[46m"
#define COLOR_ASIA "\033[43m"
#define COLOR_EUROPE "\033[44m"
#define COLOR_AUSTRALIA "\033[45m"

#define COLOR_WRONG "\033[41m"

// Associa un numero ad ogni continente più l'oceano
#define OCEAN 0
#define AMERICA 1
#define AFRICA 2
#define AUSTRALIA 3
#define ASIA 4
#define EUROPE 5

// Dimensioni della mappa
#define MAP_HEIGHT 25
#define MAP_LENGTH 50
#define MAP_AREA (MAP_HEIGHT * MAP_LENGTH)

// End char of an array
#define END_CHAR '\0'

unsigned int continents[6] = { // Array dei continenti disponibili più l'oceano
    OCEAN, AMERICA, AFRICA, 
    AUSTRALIA, ASIA, EUROPE
};
unsigned char world_map[MAP_AREA] = { // Mappa che viene utilizzata per associare in che posizione si trova ogni stato
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

char fg_colors[6][7] = { // Colori associati ad ogni stato e all'oceano utilizzando lo standard ANSI C
    COLOR_OCEAN, COLOR_AMERICA, COLOR_AFRICA,
    COLOR_AUSTRALIA, COLOR_ASIA, COLOR_EUROPE
};

char render_map[8 * MAP_AREA + MAP_HEIGHT]; // Mappa del mondo che verrà stampata a colori

/**
 * Funzione che permette di mostrare la mappa del mondo mostrando ogni stato con un determinato colore colore
 * @param cell In caso si voglia mostrare una casella dove si ha sbagliato viene evidenziata in un altro colore (-1 se non bisogna mostrarla)
*/
int render(int cell) {
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

    return 0;
}

/**
 * Funzione per generare un numero casuale in un range scelto
 * @param min Minimo numero che può essere generato
 * @param max Massimo numero che può essere generato
*/
int random(int min, int max) {
    srand(clock());
    return min + rand() % (max - min) + 1;
}

int main() {
    bool game_over, // Controllo per concludere il ciclo quando l'utente perde
        retry = false;
    int x, // Coordinata x (lunghezza) generata dal computer
        y, // Coordinata y (altezza) generata dal computer
        actual_continent, // Continente che è situato nelle coordinate generate dal computer
        score_modifier, // Modificatore del punteggio in base a quanto è entroterra le coordinate indovinate
        choice, // Qui salvo la scelta dell'utente ogni turno
        current_time, // Qui salvo il tempo per il timer in cui mostro la mappa
        score; // Qui salvo il punteggio dell'utente

    do {
        game_over = false;
        score = 0;
        choice = 0;
        clear()
        printf("MAPPA MONDO\n");

        render(-1); // Renderizziamo la mappa e rimaniamo in attesa dell'input dell'utente per iniziare il gioco

        getchar();
        do {
            // Pulisco la console e nascondo la mappa
            clear()
    
            // Ottengo le coordinate casuali e le stampo
            x = random(0, MAP_LENGTH - 1);
            y = random(0, MAP_HEIGHT - 1);
            printf("Coordinate (%d, %d)\n", x, y);

            timer(2);

            // Pulisco la console e nascondo la mappa
            clear()

            current_time = time(NULL);

            printf("Score: %d\n", score);
            // Salvo che continente è (in un numero identificativo)
            actual_continent = world_map[MAP_HEIGHT * y + x] / 3;

            // In base al continente situato nelle coordinate appena generate, i punti saranno influenzati se sono più all'interno del continente
            switch (actual_continent)
            {
            case OCEAN: // Restituirà sempre un punto
                score_modifier = 1;
                break;

            case AMERICA: // Restituirà da uno a tre punti
                score_modifier = -2;
                break;

            case AFRICA: // Restituirà da uno a tre punti
                score_modifier = -5;
                break;

            case AUSTRALIA: // Restituirà da uno a due punti
                score_modifier = -8;
                break;

            case ASIA: // Restituirà da uno a tre punti
                score_modifier = -11;
                break;

            case EUROPE: // Restituirà da uno a due punti
                score_modifier = -14;
                break;
            }

            printf("Selezionare un numero tra questi in base al tuo stato\n");
            printf("0: Oceano\n1: America\n2: Africa\n3: Australia\n4: Asia\n5: Europa\n");

            // Ciclo per controllare se la scelta è un numero compreso tra 0 e 5
            do {
                printf("Scelta: ");
                choice = getchar() - ASCII_TO_NUMBER; // Converto un numero da ASCII a numero (in ASCII lo zero corrisponde al 48)
                fflush(stdin);

                if (choice < 0 || choice > 5) { // Controllo se la scelta è compreso tra 0 e 5
                    printf("Deve essere compreso tra 0 e 5\n");
                    choice = -1;
                } else if (continents[actual_continent] == choice) { // Controllo se la scelta dell'utente è corretta e aumento i punti in base al modificatore scelto in precedenza e in base al tempo di risposta
                    int time_elapsed = time(NULL) - current_time;

                    // In base al tempo dà un punteggio diverso (più di 4 secondi non aggiunge punti sul tempo)
                    if (time_elapsed <= 1) {
                        score_modifier += 3;
                    } else if (time_elapsed <= 3) {
                        score_modifier += 2;
                    } else if (time_elapsed <= 4) {
                        score_modifier++;
                    }
                    
                    score += world_map[MAP_HEIGHT * y + x] + score_modifier;
                    printf("Corretto!\n");
                    timer(1);
                } else { // L'utente ha sbagliato, quindi perde e il programma si chiude
                    printf("Hai perso...\nIn quel punto e' presente: \n");
                    render(MAP_HEIGHT * y + x); // Mostra la casella che era giusta
                    timer(1);
                    game_over = true;
                }
            } while (choice == -1);
        } while (!game_over);
        // Chiede all'utente se vuole rigiocare
        printf("\033[0BVuoi rigiocare? s/n: ");
        
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