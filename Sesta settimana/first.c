#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Definisco le funzioni fflush e clear per tutte le piattaforme
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

// Funzione per aspettare tot millisecondi
#define TIMER(time) while (clock() % time != 0)

// Numero di stati totali
#define STATES 4
// Tutti gli stati possibili
#define BLANK_STATE 0
#define BOMB_STATE 1
#define BONUS_STATE 2
#define GOAL_STATE 3

// Numero identificativo del robot nella mappa
#define ROBOT 4

// Numero di passi massimo per sessione di allenamero onde evitare che le stesse azioni vengano eseguite all'infinito
#define MAX_TRAINING_STEP 15
// Numero massimo di sessioni di allenamento che il robot è disposto a fare
#define MAX_TRAINING_EXPERIMENT 2000

#define LEARNING_RATE 0.1
#define DISCOUNT_RATE 0.99

// Numero totale di premi disponibili nella mappa
#define REWARDS 4
// Premi disponibili
#define REWARD_BLANK -1
#define REWARD_BONUS 1
#define REWARD_BOMB -100
#define REWARD_GOAL 100

// Nasconde il cursore della console
#define HIDE_CURSOR printf("\033[?25l")
// Partendo da x e y in input, sposta il cursore in quella posizione nella console
#define MOVE_CURSOR(x, y) (printf("\033[%d;%dH", (y), (x)))

// Lunghezza delle stringhe dei colori dell'ANSI C
#define COLOR_LENGTH 6
// Colori in ANSI C delle celle della mappa
#define BLANK_COLOR "\033[40m"
#define BOMB_COLOR "\033[41m"
#define BONUS_COLOR "\033[42m"
#define GOAL_COLOR "\033[46m"
#define ROBOT_COLOR "\033[47m"

// Lunghezza dei nomi degli elementi degli stati
#define NAME_LENGTH 9
// Nomi degli stati
#define BLANK_NAME "Vuoto   "
#define BOMB_NAME "Mina    "
#define BONUS_NAME "Energia "
#define GOAL_NAME "Finale  "

// Numero di direzioni possibili per il robot
#define DIRECTIONS 4
// Stringhe con direzioni
#define UP_CHAR '^'
#define LEFT_CHAR '<'
#define RIGHT_CHAR '>'
#define DOWN_CHAR 'v'

// Dimensioni mappa
#define MAP_HEIGHT 4
#define MAP_LENGTH 4

// Righe della QTable
#define Q_HEIGHT MAP_LENGTH * MAP_HEIGHT

// Aggiunge una riga orizzontale
#define HORIZONTAL_LAYER(str, length) ({ strcat(str, "+"); for (int i = 1; i < length + 1; i++) { strcat(str, "-"); } })

// Aggiunge una riga dei contorni orizzontali della mappa
#define HORIZONTAL_MAP_LAYER(str, length) ({ HORIZONTAL_LAYER(str, length); strcat(str, "+"); })

// Aggiunge una riga dei contorni orizzontali della tabella
#define HORIZONTAL_QTABLE_LAYER(str, name_length, times, length) ({ HORIZONTAL_LAYER(str, name_length - 1); for (int i = 0; i < times; i++) { HORIZONTAL_LAYER(str, length); } strcat(str, "+"); })

// Aggiunge un numero di spazi scelti dall'utente
#define ADD_SPACES(str, length) ({ for (int i = 0; i < length; i++) { strcat(str, " "); } })

// Carattere finale di stringa
#define END_CHAR '\0'

// Spazio dedicato alle celle con le direzioni della QTable
#define DIRECTION_NAME_LENGTH 8
// Lunghezza di una riga della QTable + eventuale spazio
#define Q_TABLE_ROW_SIZE (2 + (NAME_LENGTH) + (DIRECTION_NAME_LENGTH * (MAP_LENGTH)) + 2)
// Lunghezza di una riga che separa ogni cella della QTable + eventuale spazio + lunghezza confine orizzontale della mappa
#define ROW_SEPARATOR_SIZE ((MAP_LENGTH * 4) + 2 + (Q_TABLE_ROW_SIZE))
// Lunghezza di una riga della stringa finale (lunghezza della mappa + lunghezza QTable + eventuale spazio)
#define ROW_SIZE ((MAP_LENGTH * 5 * 4) + 2 + (Q_TABLE_ROW_SIZE))
// Lunghezza stringa finale contenente la mappa e la QTable
#define MAP_SIZE ((ROW_SEPARATOR_SIZE) * (Q_HEIGHT - MAP_HEIGHT + 3) + (ROW_SIZE) * (MAP_HEIGHT))

// Funzione che restituisce un valore casuale da min a max
int random(int min, int max) {
    return min + rand() % (max - min);
}

// Porta la mappa allo stato di partenza
void reset_map(const int start_map[MAP_HEIGHT][MAP_LENGTH], int map[MAP_HEIGHT][MAP_LENGTH]) {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_LENGTH; j++) {
            map[i][j] = start_map[i][j];
        }
    }
}

// Mostra la QTable insieme alla mappa del robot e aggiorna i valori della QTable e muove il robot nella mappa
void render(double q_table[Q_HEIGHT][DIRECTIONS], int map[MAP_HEIGHT][MAP_LENGTH], int states[Q_HEIGHT], const char direction_names[DIRECTIONS]) {
    // Parto dall'inizio della console
    MOVE_CURSOR(0, 0);

    // Tutti i colori degli stati indicizzati
    // 0: Nulla (Nero)
    // 1: Bomba (Rosso)
    // 2: Bonus (Verde)
    // 3: Arrivo (Blu)
    // 4: Robot (Bianco)
    const char colors[][COLOR_LENGTH] = {
        BLANK_COLOR, BOMB_COLOR, BONUS_COLOR, GOAL_COLOR, ROBOT_COLOR
    };

    // Tutti i nomi degli stati indicizzati
    // 0: Nulla
    // 1: Bomba
    // 2: Bonus
    // 3: Arrivo
    // 4: Robot
    const char names[][NAME_LENGTH] = {
        BLANK_NAME, BOMB_NAME, BONUS_NAME, GOAL_NAME
    };

    // Creo la stringa che salva la mappa e la QTable da stampare
    char str_map[MAP_SIZE] = "";

    // Metto la scritta QTable in modo che sia al centro della tabella
    ADD_SPACES(str_map, (ROW_SEPARATOR_SIZE - MAP_HEIGHT) / 2 - NAME_LENGTH);
    strcat(str_map, "Q_TABLE");
    ADD_SPACES(str_map, (ROW_SEPARATOR_SIZE - MAP_HEIGHT) / 2 - NAME_LENGTH + 1);

    // Metto la scritta mappa in modo che sia al centro della mappa
    ADD_SPACES(str_map, MAP_LENGTH / 2 + 1);
    strcat(str_map, "MAPPA\n");

    // Aggiungo il separatore orizzontale alla QTable
    HORIZONTAL_QTABLE_LAYER(str_map, NAME_LENGTH, MAP_LENGTH, DIRECTION_NAME_LENGTH);

    // Aggiungo il separatore orizzontale alla mappa
    ADD_SPACES(str_map, 2);
    HORIZONTAL_MAP_LAYER(str_map, MAP_LENGTH * 4);
    strcat(str_map, "\n");

    // Preparo la stringa con la QTable e la mappa
    for (int i = 0; i < Q_HEIGHT + 2; i++) {
        // Aggiungo la legenda della QTable
        if (i == 0) {
            strcat(str_map, "|");
            ADD_SPACES(str_map, NAME_LENGTH - 1);
            strcat(str_map, "|");
            for (int j = 0; j < 4; j++) {
                ADD_SPACES(str_map, DIRECTION_NAME_LENGTH / 2 - 1);
                strncat(str_map, &direction_names[j], 1);
                ADD_SPACES(str_map, DIRECTION_NAME_LENGTH / 2);
                strcat(str_map, "|");
            }
        } else if (i == 1) {
            // Aggiungo la riga separatore per separare la legenda dalla tabella
            HORIZONTAL_QTABLE_LAYER(str_map, NAME_LENGTH, MAP_LENGTH, DIRECTION_NAME_LENGTH);
        } else {
            // Controllo che stato è presente in questa riga
            int index = states[i - 2];
            strcat(str_map, "|");

            // Aggiungo lo stato presente in quell'indice
            strcat(str_map, names[index]);

            // Aggiunge la QTable alla stringa della mappa
            for (int j = 0; j < MAP_LENGTH; j++) {
                // Ottengo il numero presente nella cella attuale della QTable
                strcat(str_map, "|");
                
                // Converto il valore contenuto nella cella della QTable in stringa per poi concatenarla
                char temp[DIRECTION_NAME_LENGTH] = "";
                int chars = sprintf(temp, "%.1f", q_table[i - 2][j]);
                strcat(str_map, temp);
                // Aggiungo gli spazi necessari ad occupare tutta la cella della QTable
                ADD_SPACES(str_map, DIRECTION_NAME_LENGTH - chars);
            }
            strcat(str_map, "|");
        }

        ADD_SPACES(str_map, 2);
        // Controllo se in questa riga è presente la mappa
        if (i < MAP_HEIGHT * 2) {
            // Aggiungo una riga della mappa alla volta
            strcat(str_map, "|");
            for (int j = 0; j < MAP_LENGTH; j++) {
                // Ottengo che stato è presente sulla cella della mappa
                int index = map[i / 2][j];

                // Aggiungo il colore della cella e due spazi in modo da avere una cella quadrata del colore corrispondente
                strcat(str_map, colors[index]);
                ADD_SPACES(str_map, 4);
                strcat(str_map, "\033[m");
            }
            strcat(str_map, "|");
        } else if (i == MAP_HEIGHT * 2) {
            // Chiude la mappa con il separatore orizzontale
            HORIZONTAL_MAP_LAYER(str_map, MAP_LENGTH * 4);
        }
        // Concateno la stringa contenente la riga alla stringa finale contenente la mappa
        strcat(str_map, "\n");
    }

    // Aggiungo il separatore orizzontale alla QTable
    HORIZONTAL_QTABLE_LAYER(str_map, NAME_LENGTH, MAP_LENGTH, DIRECTION_NAME_LENGTH);
    ADD_SPACES(str_map, MAP_LENGTH * 2 + 4);

    // Stampo la mappa e la QTable
    puts(str_map);
}

// Funzione per trovare il valore da aggiungere alla QTable con lo stato e l'azione attuale
double q_function(double q_table[Q_HEIGHT][DIRECTIONS], int map[MAP_HEIGHT][MAP_LENGTH], int directions[DIRECTIONS][2], int x, int y, int next_x, int next_y, int state, int new_state, int action, double learning_rate, double discount_rate) {
    // Tutti i premi indicizzati
    // 0: Nulla (-1)
    // 1: Bomba (-100)
    // 2: Bonus (1)
    // 3: Arrivo (100)
    int rewards[REWARDS] = {
        REWARD_BLANK, REWARD_BOMB, REWARD_BONUS, REWARD_GOAL
    };

    // Ottengo il premio della mappa nelle coordinate del robot
    int index = map[y][x];
    int reward = rewards[index];

    // Ottengo il valore della QTable attuale
    double q_value = q_table[state][action];
    // Pongo il prossimo valore della QTable come un numero più piccolo di tutti i valori possibili della QTable in modo da entrare sempre nella prima iterazione del ciclo
    double next_q_value = -1000;

    // Controllo la direzione che restituisce il premio più grande
    for (int i = 0; i < DIRECTIONS; i++) {
        next_x = x + directions[i][0];
        next_y = y + directions[i][1];
        // Controllo che le coordinate non vadano fuori dalla mappa
        if (next_x >= 0 && next_x < MAP_LENGTH && next_y >= 0 && next_y < MAP_HEIGHT) {
            if (q_table[new_state][i] > next_q_value) {
                next_q_value = q_table[new_state][i];
            }
        }
    }

    // Salvo il nuovo valore della QTable utilizzando la formula di Bellman
    double new_q_value = q_value + learning_rate * (reward + discount_rate * next_q_value - q_value);
    return new_q_value;
}

// Funzione per ottenere l'azione del robot
int get_action(double q_table[Q_HEIGHT][DIRECTIONS], int directions[DIRECTIONS][2], int state, double eps, int x, int y, int next_x, int next_y) {
    int action = 0;
    // Ottengo un numero da 1 a 100 per sfruttare il metodo epsilon greedy
    int random_value = random(1, 100);
    // Pongo il prossimo valore della QTable come un numero più piccolo di tutti i valori possibili della QTable in modo da entrare sempre nella prima iterazione del ciclo
    double q_value = -1000;

    // Controllo la direzione che restituisce il premio più grande
    if (random_value <= (100 - eps)) {
        for (int i = 0; i < DIRECTIONS; i++) {
            next_x = x + directions[i][0];
            next_y = y + directions[i][1];
            // Controllo che le coordinate non vadano fuori dalla mappa
            if (next_x >= 0 && next_x < MAP_LENGTH && next_y >= 0 && next_y < MAP_HEIGHT) {
                if (q_table[state][i] > q_value) {
                    q_value = q_table[state][i];
                    action = i;
                }
            }
        }
    } else {
        // Azione casuale, controllo che le coordinate non vadano fuori dalla mappa
        do {
            action = random(0, 4);
            next_x = x + directions[action][0];
            next_y = y + directions[action][1];
        } while (next_x < 0 || next_x > MAP_LENGTH - 1
            || next_y < 0 || next_y > MAP_HEIGHT - 1);
    }
    printf("\n");

    return action;
}

// Funzione per mostrare il percorso che il robot ha imparato dopo la sua sessione di allenamento
void show_final_path(const int start_map[MAP_HEIGHT][MAP_LENGTH], double q_table[Q_HEIGHT][DIRECTIONS], int directions[DIRECTIONS][2], int states[STATES], const char direction_names[DIRECTIONS], int start_x, int start_y) {
    // Porto la mappa allo stato iniziale
    int map[MAP_HEIGHT][MAP_LENGTH];
    reset_map(start_map, map);
    CLEAR;

    // Variabile per salvare le direzioni che fa il robot durante il percorso
    char path[15 * MAP_LENGTH * MAP_HEIGHT] = "";

    // Il robot parte dalla sua posizione iniziale
    int x = start_x;
    int y = start_y;

    int next_x, next_y;
    int current_state = 0;
    int count_training_step = 0;
    int previous_state = BLANK_STATE;

    // Ciclo che esegue ogni azione finché non trova la destinazione se durante l'allenamento è riuscito a trovarla o in caso contrario si ferma quando ha finito i passi disponibili
    do {
        map[y][x] = ROBOT;
        render(q_table, map, states, direction_names);
        
        // In caso il robot trova energie le rimuovo dalla mappa
        map[y][x] = BLANK_STATE;

        srand(time(NULL) + clock());
        
        int action;
        // Pongo il prossimo valore della QTable come un numero più piccolo di tutti i valori possibili della QTable in modo da entrare sempre nella prima iterazione del ciclo
        double q_value = -1000;
        // Controllo la direzione migliore in base ai valori della QTable
        for (int i = 0; i < DIRECTIONS; i++) {
            next_x = x + directions[i][0];
            next_y = y + directions[i][1];
            // Controllo che le coordinate non vadano fuori dalla mappa
            if ((q_table[current_state][i] > q_value) && (next_x >= 0 && next_x < MAP_LENGTH && next_y >= 0 && next_y < MAP_HEIGHT)) {
                q_value = q_table[current_state][i];
                action = i;
            }
        }
        // Sposta il robot in base all'azione migliore
        x += directions[action][0];
        y += directions[action][1];

        // Aggiorna lo stato
        current_state = y * MAP_HEIGHT + x;
        count_training_step++;

        // Salvo tutte le direzioni del giocatore
        char char_direction[15];
        sprintf(char_direction, "Direzione: %c\n", direction_names[action]);
        strcat(path, char_direction);
        puts(path);

        // Timer di un secondo
        TIMER(1000);
    } while(map[y][x] != GOAL_STATE && count_training_step < MAX_TRAINING_STEP);

    // Stampo un messaggio in base al risultato dell'allenamento
    char* final_message;
    if (map[y][x] == GOAL_STATE) {
        final_message = "Il robot e' arrivato a destinazione!";
    } else {
        final_message = "Il robot non e' arrivato a destinazione...";
    }
    // Aggiorno la mappa una volta finito il percorso
    map[y][x] = ROBOT;
    render(q_table, map, states, direction_names);

    // Stampo le direzioni prese dal robot, il messaggio finale e quanti passi ha dedicato per il percorso finale
    printf(path);
    printf("%s\n", final_message);
    printf("Passi eseguiti: %d\n", count_training_step);
}

int main() {
    // Tutte le direzioni indicizzate
    // 0: Sopra
    // 1: Sinistra
    // 2: Destra
    // 3: Sotto
    int directions[DIRECTIONS][2] = {
        { 0, -1 }, { -1, 0 }, { 1, 0 }, { 0, 1 }
    };

    // Tutti i caratteri delle direzioni indicizzati
    // 0: Sopra
    // 1: Sinistra
    // 2: Destra
    // 3: Sotto
    const char direction_names[DIRECTIONS] = {
        UP_CHAR, LEFT_CHAR, RIGHT_CHAR, DOWN_CHAR
    };

    // Inizializzo la mappa degli stati
    const int start_map[MAP_HEIGHT][MAP_LENGTH] = {
        {BLANK_STATE, BLANK_STATE, BLANK_STATE, BOMB_STATE},
        {BONUS_STATE, BLANK_STATE, BONUS_STATE, BLANK_STATE},
        {BOMB_STATE, BOMB_STATE, BLANK_STATE, BLANK_STATE},
        {GOAL_STATE, BLANK_STATE, BLANK_STATE, BONUS_STATE},
    };

    // Inizializzo la QTable con tutti valori a 0
    double q_table[Q_HEIGHT][DIRECTIONS];
    for (int i = 0; i < Q_HEIGHT; i++) {
        for (int j = 0; j < MAP_LENGTH; j++) {
            q_table[i][j] = 0;
        }
    }
    
    // Scrivo gli stati della mappa in un array ad una dimensione
    int states[Q_HEIGHT];
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_LENGTH; j++) {
            states[i * MAP_HEIGHT + j] = start_map[i][j];
        }
    }

    CLEAR;
    HIDE_CURSOR;

    int map[MAP_HEIGHT][MAP_LENGTH];
    
    double eps = 100;
    int count_training_experiment = 0;
    // Posizione iniziale del robot
    int start_x = 0, start_y = 0;
    while (count_training_experiment < MAX_TRAINING_EXPERIMENT) {
        // Pongo la mappa iniziale
        reset_map(start_map, map);

        // Il robot parte dalla posizione iniziale
        int x = start_x;
        int y = start_y;

        int next_x, next_y;
        int current_state = 0;
        int count_training_step = 0;
        int previous_state = BLANK_STATE;

        // Ciclo che esegue ogni azione finché non trova la destinazione o una mina oppure finisce i passi disponibili
        do {
            // Mostro il movimento del robot
            previous_state = map[y][x];
            map[y][x] = ROBOT;
            render(q_table, map, states, direction_names);
            map[y][x] = previous_state;
            
            srand(time(NULL) + clock());

            // Sposto il robot nella direzione ottenuta dall'azione
            int action = get_action(q_table, directions, current_state, eps, x, y, next_x, next_y);
            x += directions[action][0];
            y += directions[action][1];

            // Ottengo lo stato presente nelle coordinate del robot
            int new_state = y * MAP_HEIGHT + x;
            
            // Aggiorno la QTable
            q_table[current_state][action] = q_function(q_table, map, directions, x, y, next_x, next_y, current_state, new_state, action, LEARNING_RATE, DISCOUNT_RATE);

            // Aggiorno lo stato
            current_state = new_state;
            count_training_step++;
        } while(map[y][x] != BOMB_STATE && map[y][x] != GOAL_STATE && count_training_step < MAX_TRAINING_STEP);

        printf("Iterazione n: %d", count_training_experiment);

        map[y][x] = ROBOT;
        render(q_table, map, states, direction_names);

        // Diminuisco l'epsilon per sfruttare l'epsilon greedy
        eps -= 100.0 / MAX_TRAINING_EXPERIMENT;

        count_training_experiment++;
    }
    
    // Mostro il percorso che ha finalizzato durante l'allenamento
    show_final_path(start_map, q_table, directions, states, direction_names, start_x, start_y);

    return 0;
}