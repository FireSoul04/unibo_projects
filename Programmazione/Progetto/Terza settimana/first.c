#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32 // valido sia per 32 che 64 bit
    #include <conio.h>

	#define CLEAR system("cls") // Definisco una funzione per pulire la console
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

    #define CLEAR system("clear") // Definisco una funzione per pulire la console
#endif

// Timer di un numero di secondi deciso in input
#define TIMER(seconds) (current_time) = time(NULL); while (time(NULL) - current_time < seconds)

// Numero per passare da ASCII a un numero (lo 0 in ASCII parte da 48)
#define ASCII_TO_NUMBER 48

// Tasti per muovere il cursore
#define KEY_UP 'w' // w
#define KEY_DOWN 's' // s
#define KEY_LEFT 'a' // a
#define KEY_RIGHT 'd' // d

// Trasforma il tasto da lettera minuscola a lettera maiuscola
#define KEY_TO_MAIUSC(key) ((key) - 32)

// Tasto spacebar
#define KEY_EXIT 32

// Associa un colore in ANSI C per la mappa
#define COLOR_OCEAN "\033[40m"
#define COLOR_AMERICA "\033[42m"
#define COLOR_AFRICA "\033[46m"
#define COLOR_ASIA "\033[43m"
#define COLOR_EUROPE "\033[44m"
#define COLOR_AUSTRALIA "\033[45m"

// Associa il rosso in ANSI C da mostrare nella mappa quando un giocatore perde
#define COLOR_WRONG "\033[41m"

// Associa il bianco in ANSI C per guardare il cursore nella mappa quando un giocatore perde
#define COLOR_CURSOR "\033[47m"

// Mette il colore di default come sfondo
#define RESET_COLOR printf("\033[49m");

// Lunghezza delle stringhe dei colori (5 + fine stringa)
#define COLOR_LENGTH 6

// Associa un numero ad ogni continente più l'oceano
#define OCEAN 0
#define AMERICA 1
#define AFRICA 2
#define AUSTRALIA 3
#define ASIA 4
#define EUROPE 5

#define MAX_CONTINENTS 6

/*La mappa è un array bidimensionale di numeri, ogni coordinate x e y corrisponde a un continente e a quanti punti restituisce,
è gestita in modo che ogni continente può dare minimo un punto e massimo tre e ogni continente nella mappa ha un valore che
è divisibile per tre e essendo una divisione tra interi restituirà il risultato del rapporto senza resto.
Esempio: una cella appartiene all'America se vale da 3 a 5, se eseguo la divisione 5/3 ottengo 1, che corrisponde al continente America nel gioco.
L'oceano restituisce sempre un punto.*/

// Dimensioni della mappa
#define MAP_HEIGHT 25 // Altezza della mappa
#define MAP_LENGTH 50 // Lunghezza della mappa

// Calcoli per ottenere un indice dell'array mappa partendo da x e y
#define GO_TO(x, y) (printf("\033[%d;%dH", (y), (x))) // Partendo da x e y in input, sposta il cursore in quella posizione nella console
#define POSITION_IN(x, y) (WOLRD_MAP[(y)][(x)]) // Partendo da x e y in input, restituisce la cella di mappa corrispondente
#define CONTINENT_IN(x, y) (POSITION_IN((x), (y)) / 3) // Partendo da x e y in input, restituisce il continente che si trova in quella posizione della mappa 

// Carattere per concludere una stringa
#define END_CHAR '\0'

// Mappa che viene utilizzata per associare in che posizione si trova ogni stato
const unsigned char WOLRD_MAP[MAP_HEIGHT][MAP_LENGTH] = { 
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5, 5, 0, 5, 5, 4, 4, 4, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 4, 4, 5, 0, 0, 0, 5, 4, 3, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 14, 14, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 5, 5, 5, 5, 4, 4, 4, 4, 4, 5, 5, 0, 0, 5, 4, 4, 5, 0, 0, 0, 0, 0, 0, 17, 17, 0, 0, 0, 0, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14, 0, 0, 0, },
    { 0, 0, 5, 5, 5, 4, 4, 4, 3, 3, 3, 4, 4, 5, 5, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 17, 17, 17, 14, 14, 14, 14, 14, 14, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 14, 14, 14, 0, 0, },
    { 0, 0, 0, 0, 5, 5, 5, 4, 4, 3, 3, 3, 4, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17, 17, 16, 17, 14, 13, 13, 13, 13, 13, 13, 13, 12, 12, 13, 13, 14, 14, 14, 14, 14, 14, 14, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 5, 4, 4, 3, 3, 3, 4, 4, 5, 5, 0, 0, 0, 0, 0, 0, 0, 17, 17, 16, 16, 17, 14, 14, 13, 13, 12, 12, 12, 12, 12, 12, 12, 13, 13, 14, 0, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 5, 4, 4, 3, 3, 4, 4, 5, 5, 0, 0, 0, 0, 0, 0, 0, 17, 16, 16, 16, 17, 17, 14, 14, 13, 12, 12, 12, 12, 12, 12, 12, 12, 13, 14, 14, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 5, 4, 4, 3, 3, 4, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 17, 16, 17, 17, 17, 17, 14, 14, 13, 13, 12, 12, 12, 12, 12, 12, 13, 13, 13, 14, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 5, 5, 4, 4, 3, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 17, 17, 17, 0, 17, 14, 14, 13, 13, 13, 12, 12, 12, 12, 12, 13, 13, 14, 14, 14, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 4, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 8, 8, 8, 0, 14, 14, 14, 13, 13, 13, 13, 13, 13, 13, 13, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 4, 4, 5, 0, 0, 0, 0, 0, 0, 0, 8, 8, 7, 7, 7, 8, 8, 8, 14, 14, 14, 14, 14, 14, 14, 14, 13, 13, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 4, 4, 5, 5, 0, 0, 0, 0, 0, 8, 7, 7, 6, 6, 7, 7, 8, 8, 8, 0, 0, 0, 14, 0, 14, 13, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 4, 4, 5, 0, 0, 0, 0, 0, 8, 8, 8, 7, 6, 6, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 14, 13, 14, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 4, 5, 5, 0, 0, 0, 0, 0, 0, 0, 8, 7, 6, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 14, 13, 13, 14, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 4, 4, 4, 5, 0, 0, 0, 0, 0, 0, 0, 8, 6, 7, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 14, 14, 0, 0, 0, 11, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 4, 3, 4, 5, 5, 0, 0, 0, 0, 0, 0, 8, 7, 8, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 11, 0, 11, 11, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 3, 4, 5, 0, 0, 0, 0, 0, 0, 0, 8, 7, 8, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 10, 11, 0, 11, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 10, 10, 10, 11, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 10, 10, 11, 11, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 11, 11, 11, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, }
};

// Array dei continenti disponibili più l'oceano
const unsigned short CONTINENTS[MAX_CONTINENTS] = { 
    OCEAN, AMERICA, AFRICA, 
    AUSTRALIA, ASIA, EUROPE
};

// Colori associati ad ogni stato e all'oceano utilizzando lo standard ANSI C
const char CONTINENT_COLORS[MAX_CONTINENTS][COLOR_LENGTH] = {
    COLOR_OCEAN, COLOR_AMERICA, COLOR_AFRICA,
    COLOR_AUSTRALIA, COLOR_ASIA, COLOR_EUROPE
};

int score; // Qui salvo il punteggio dell'utente

// Mappa del mondo che verrà stampata a colori
char render_map[10 * MAP_HEIGHT * MAP_LENGTH + MAP_HEIGHT * 13];

/**
 * Funzione che permette di mostrare la mappa del mondo mostrando ogni continente con un determinato colore
 * @param cell_x Le coordinate x di una casella dove si ha sbagliato viene evidenziata in rosso (-1 se non la si vuole mostrare)
 * @param cell_y Le coordinate y di una casella dove si ha sbagliato viene evidenziata in rosso (-1 se non la si vuole mostrare)
*/
void render(int cell_x, int cell_y) {
    // Pulisco il contenuto della stringa della mappa per ricostruirla
    render_map[0] = END_CHAR;

    // Ciclo per renderizzare ogni carattere (2 per la precisione) per costruire la mappa che verra visualizzata a schermo
    for (int y = 0; y < MAP_HEIGHT; y++) {
        for (int x = 0; x < MAP_LENGTH; x++) {
            // Concatena i colori a 2 caratteri utilizzando lo standard ANSI C
            strcat(render_map, "\033[");

            // Mostra la casella giusta in caso di sconfitta
            if (x == cell_x && y == cell_y) {
                strcat(render_map, COLOR_WRONG);
            } else {
                strcat(render_map, CONTINENT_COLORS[CONTINENT_IN(x, y)]);
            }
            strcat(render_map, "  \033[");
        }
        strcat(render_map, COLOR_OCEAN);
        // Ogni riga va a capo
        strcat(render_map, "     \033[\n");
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

    // In base al continente situato nelle coordinate appena generate, i punti saranno influenzati se sono più ai confini del continente
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
int random_range(int min, int max) {
    srand(clock());
    return min + rand() % (max - min) + 1;
}

/**
 * Una volta che l'utente perde può controllare le coordinate di ogni cella e può visualizzare dove situava la cella del turno in cui ha perso
 * @param cell_x Le coordinate x di una casella dove si ha sbagliato viene evidenziata in rosso
 * @param cell_y Le coordinate y di una casella dove si ha sbagliato viene evidenziata in rosso
*/
void game_over(int cell_x, int cell_y) {
    int cursor_x = 0, // Coordinate x usate per muovere il cursore
        cursor_y = 0; // Coordinate y usate per muovere il cursore
    char ch;
    
    CLEAR;
    printf("Hai perso... Muoviti con W sopra, A sinistra, D destra, S sotto per visualizzare le coordinate della mappa, premi SPAZIO per concludere.\nIn quel punto e' presente: \n");
    render(cell_x, cell_y);

    // Nasconde il cursore della console
    printf("\e[?25l");
    do {
        // Controlla che tasto sta premendo l'utente
        ch = getch();

        GO_TO(0, 0);
        printf("Hai perso... Muoviti con W sopra, A sinistra, D destra, S sotto per visualizzare le coordinate della mappa, premi SPAZIO per concludere.\nIn quel punto e' presente: \n");
        render(cell_x, cell_y);

        // Muove il cursore in base ai tasti premuti dall'utente
        switch (ch) {
        case KEY_UP:
        case KEY_TO_MAIUSC(KEY_UP):
            cursor_y--;
            break;

        case KEY_DOWN:
        case KEY_TO_MAIUSC(KEY_DOWN):
            cursor_y++;
            break;

        case KEY_LEFT:
        case KEY_TO_MAIUSC(KEY_LEFT):
            cursor_x--;
            break;

        case KEY_RIGHT:
        case KEY_TO_MAIUSC(KEY_RIGHT):
            cursor_x++;
            break;
        }

        // Controlla se va oltre i limiti della matrice
        if (cursor_x < 0) {
            cursor_x = 0;
        } else if (cursor_x >= MAP_LENGTH) {
            cursor_x = MAP_LENGTH - 1;
        }

        // Controlla se va oltre i limiti della matrice
        if (cursor_y < 0) {
            cursor_y = 0;
        } else if (cursor_y >= MAP_HEIGHT) {
            cursor_y = MAP_HEIGHT - 1;
        }
        
        // Muove il cursore in base al movimento dell'utente e lo mostra con una casella bianca
        GO_TO(cursor_x * 2 + 1, cursor_y + 4);
        printf("%s  ", COLOR_CURSOR);

        // Mette il colore default della console
        RESET_COLOR; 

        // Sopra il cursore mostra le coordinate della cella selezionata
        GO_TO(cursor_x * 2 + 1, cursor_y + 3);
        printf("(%d;%d)", cursor_x + 1, cursor_y + 1);
    } while (ch != KEY_EXIT); // Quando l'utente preme spacebar esce da questa visualizzazione della mappa

    // Nasconde il cursore della console
    printf("\e[?25h");

    CLEAR;
}

/**
 * Funzione del gioco effettivo
 * @returns Torna vero (1) se il gioco continua e false (0) se l'utente ha perso
*/
bool game() {
    int choice, // Qui salvo la scelta dell'utente ogni turno
        x, // Coordinata x (lunghezza) generata dal computer
        y, // Coordinata y (altezza) generata dal computer
        current_time, // Qui salvo il tempo per il timer in cui mostro la mappa
        current_continent; // Qui salvo il continente del turno attuale

    // Pulisco la console e nascondo la mappa
    CLEAR;

    // Ottengo le coordinate casuali e le stampo
    x = random_range(0, MAP_LENGTH - 1);
    y = random_range(0, MAP_HEIGHT - 1);
    // Stampo ogni coordinata + 1 perché gli array partono da 0
    printf("Coordinate (%d, %d)\n", x + 1, y + 1);

    TIMER(2);
    // Pulisco la console e nascondo le coordinate
    CLEAR;

    // Salvo il tempo per controllare quanto ci mette l'utente per rispondere, in base al tempo vengono assegnati punti bonus
    current_time = time(NULL);

    printf("Punteggio: %d\n", score);
    // Salvo che continente è (numero identificativo)
    current_continent = CONTINENT_IN(x, y);

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
        } else if (CONTINENTS[current_continent] == choice) { // Controllo se la scelta dell'utente è corretta
            printf("Corretto!\n");

            // Aumento i punti in base alla cella scelta e in base al tempo di risposta
            score += POSITION_IN(x, y) + score_modifier(current_continent, current_time);
        } else { // L'utente ha sbagliato, quindi perde e il programma si chiude
            game_over(x, y);
            // Pongo la condizione game over in modo da uscire dal ciclo del gioco
            return false;
        }
    } while (choice == -1);
    
    // Prima di andare avanti aspetto un secondo
    TIMER(1);

    // Ritorno true in modo da eseguire il ciclo finché non perde il giocatore
    return true;
}

int main() {
    bool retry; // Controllo se l'utente vuole rigiocare

    // Ciclo per controllare che l'utente inserisca si o no, se si torna all'inizio del gioco
    char ch;
    do {
        score = 0; // Azzero il punteggio

        // Pulisco la console per mostrare la mappa
        CLEAR;
        printf("MAPPA MONDO | Premi invio per iniziare\n");
        render(-1, -1); // Renderizziamo la mappa e rimaniamo in attesa dell'input dell'utente per iniziare il gioco
        getchar();

        // Ciclo del gioco, si conclude quando il giocatore sbaglia
        while (game());

        // Chiede all'utente se vuole rigiocare
        printf("Vuoi rigiocare? s/n: ");
        do {
            ch = getchar();
            fflush(stdin);
            if  (ch != 's' && ch != 'n') {
                printf("Inserisci s o n (si o no): ");
            }
        } while (ch != 's' && ch != 'n');
    } while (ch == 's');

    return 0;
}
