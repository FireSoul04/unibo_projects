/****************************************************************************
 *
 * shooting-stars.c - Shooting Stars
 *
 * Copyright (C) 2018--2024 Moreno Marzolla
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 ****************************************************************************/

/***
% LabASD - Shooting Stars
% Moreno Marzolla <moreno.marzolla@unibo.it>
% Ultimo aggiornamento: 2024-02-26

![](shooting-stars.jpg "Copertina del numero 9, maggio 1976 di BYTE Magazine dedicata a shooting stars")

"Shooting stars" è un gioco di strategia descritto nella rivista [BYTE
Magazine n. 9, p. 42, maggio
1976](https://archive.org/details/byte-magazine-1976-05/page/n43/mode/1up).

Il gioco si svolge su una griglia $3 \times 3$ le cui celle sono
numerate da 0 a 8 come segue:

```
012
345
678
```

Ogni cella può contenere una stella (`*`) oppure un buco nero
(`.`). La configurazione iniziale contiene un'unica stella nella cella
4:

```
...
.*.
...
```

Ad ogni turno il giocatore può far "esplodere" una stella digitando il
numero della cella corrispondente. Una stella esplosa si trasforma in
un buco nero; inoltre, i frammenti della stella vanno a finire in
alcune delle celle adiacenti, trasformando i buchi neri in stelle, e
le stelle in buchi neri. Il vicinato è definito in modo differente per
ogni cella, ed è rappresentato con un `#` dalle figure seguenti:

```
0#.  #1#  .#2
##.  ...  .##
...  ...  ...

#..  .#.  ..#
3..  #4#  ..5
#..  .#.  ..#

...  ...  ...
##.  ...  .##
6#.  #7#  .#8
```

quindi il vicinato della cella 0 è costituita da (1, 3, 4); il
vicinato della cella 1 è costituito da (0, 2); il vicinato della cella
2 è costituito da (1, 4, 5), e così via. In pratica, fare esplodere la
stella in posizione $k$ significa trasformare stelle in buchi neri (e
viceversa) nella cella $k$ e in quelle "vicine" secondo le figure
sopra.

Ad esempio, partendo dalla configurazione iniziale (per facilitare la
lettura, le celle contenenti una stella sono indicate con il
rispettivo numero):

```
...
.4.
...
```

il giocatore può solo fare esplodere la stella 4, ottenendo la nuova
configurazione

```
.1.
3.5
.7.
```

Se ora decide di fare esplodere la stella 3, la nuova configurazione
sarà

```
01.
..5
67.
```

e così via.

Si vince se si ottiene la configurazione

```
012
3.5
678
```

mentre si perde se si ottiene la configurazione contenente solo buchi neri

```
...
...
...
```

(infatti, a questo punto non sarebbe possibile far esplodere alcuna
stella).

Compilare il programma con

        gcc -std=c90 -Wall -Wpedantic shooting-stars.c -o shooting-stars

In ambiente Linux/MacOSX eseguire con

        ./shooting-stars

In ambiente Windows eseguire con

        .\shooting-stars

## Per approfondire

Alla fine del corso sarete in grado di scrivere un programma
efficiente in grado di rispondere a queste domande:

- Qual è il numero minimo di mosse necessarie per vincere? Qual è la
  sequenza minima di mosse che porta alla vittoria?

- Qual è il numero minimo di mosse necessarie a perdere (cioè
  a raggiungere la configurazione vuota)?

- Esiste una configurazione di stelle/buchi neri che non può essere
  generata dallo stato iniziale effettuando solo mosse valide?

Per il momento si richiede di completare il programma in modo da
consentire all'utente di giocare una partita.

## File

- [shooting-stars.c](shooting-stars.c)

***/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define SIZE 9

#define NO_END 0
#define LOSE -1
#define WIN 1

int minimum_moves_to_win(int *map, int **parse_maps);

int parse_win(int *map);
void parse_map(int *map, int *zone);
void print_map(int *map);

int main( void )
{
  /* Mappa 3x3 di stati 0/1 dove 0 sono buchi neri e 1 stelle 
  inizializzato con tutti buchi neri tranne la cella centrale */
  int num = 0, win = 0;
  int map[SIZE] = {
    0, 0, 0,
    0, 1, 0,
    0, 0, 0
  };
  int parse_maps[9][SIZE] = { {
      1, 1, 0,
      1, 1, 0,
      0, 0, 0
    }, {
      1, 1, 1,
      0, 0, 0,
      0, 0, 0
    }, {
      0, 1, 1,
      0, 1, 1,
      0, 0, 0
    }, {
      1, 0, 0,
      1, 0, 0,
      1, 0, 0
    }, {
      0, 1, 0,
      1, 1, 1,
      0, 1, 0
    }, {
      0, 0, 1,
      0, 0, 1,
      0, 0, 1
    }, {
      0, 0, 0,
      1, 1, 0,
      1, 1, 0
    }, {
      0, 0, 0,
      0, 0, 0,
      1, 1, 1
    }, {
      0, 0, 0,
      0, 1, 1,
      0, 1, 1
    }
  };

  printf("\033[2J");

  /* Main loop, esce quando l'utente scrive un numero negativo */
  while (num >= 0 && win == 0) {
    print_map(map);
    printf("Dove si vuole sparare? (se negativo chiude il programma): ");
    scanf("%d", &num);

    /* Controllo se il numero della posizione è valida e
    se in quella posizione è presente una stella */
    if (num > SIZE) {
      puts("Posizione non presente nella mappa");
    } else if (map[num] == 0) {
      puts("Non e' presente una stella nella posizione scelta");
    } else {
      parse_map(map, parse_maps[num]);

      /* Controllo se sono tutti buchi neri contando quanti ne sono presenti, se si win sarà -1 */
      win = parse_win(map);
    }
  }
  print_map(map);

  if (win == WIN) {
    puts("Hai vinto!");
  } else if (win == LOSE) {
    puts("Hai perso...");
  }
  return EXIT_SUCCESS;
}

int parse_win(int *map) {
  int lose_con[SIZE] = {
    0, 0, 0,
    0, 0, 0,
    0, 0, 0
  };
  int win_con[SIZE] = {
    1, 1, 1,
    1, 0, 1,
    1, 1, 1
  };
  int i, cont_w = 0, cont_l = 0;
  for (i = 0; i < SIZE; i++) {
    if (map[i] == lose_con[i]) {
      cont_l++;
    }
    if (map[i] == win_con[i]) {
      cont_w++;
    }
  }

  if (cont_l == SIZE) {
    return LOSE;
  } else if (cont_w == SIZE) {
    return WIN;
  } else {
    return NO_END;
  }
}

void parse_map(int *map, int *zone) {
  int i;
  for (i = 0; i < SIZE; i++) {
    map[i] ^= zone[i];
  }
}

/* stampa la mappa dove le stelle sono la posizione e i buchi neri dei punti */
void print_map(int *map) {
  int i;
  char ch;
  printf("\033[0;0H");
  for (i = 0; i < SIZE; i++) {
    if (i % 3 == 0 && i != 0) {
      puts("");
    }
    if (map[i] == 0) {
      ch = '.';
    } else {
      ch = i + '0'; /* Per convertire da int a char velocemente parto dal carattere 0 e aumento del numero richiesto */
    }
    printf(" %c ", ch);
  }
  printf("\n");
}

int minimum_moves_to_win(int *map, int **parse_maps) {
  int win = 0, moves = 0;
  while (win == 0) {
    win = parse_win(map);
  }

  return moves;
}
