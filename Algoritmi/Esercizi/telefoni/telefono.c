/****************************************************************************
 *
 * telefono.c -- Numero di telefono ripetuto
 *
 * Copyright (C) 2021--2024 Moreno Marzolla
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
% LabASD - Numero di telefono ripetuto
% Moreno Marzolla <moreno.marzolla@unibo.it>
% Ultimo aggiornamento: 2024-01-23

![Tomasz Sienicki (Own work), CC BY 3.0, <https://commons.wikimedia.org/w/index.php?curid=10330603>](phone-book.jpg "Elenco telefonico")

Siete stati assunti come consulenti dalla IATM S.p.A. (Importante
Azienda di Telefonia Mobile) che è alle prese con il problema
seguente. L'azienda ha un file contenente $n$ numeri di telefono,
$200000 < n \leq \mathtt{MAXN}$. Tutti i numeri hanno sei cifre, la
prima delle quali può essere `3` oppure `5`; i numeri di telefono
hanno quindi la forma `3xxxxx` oppure `5xxxxx`, dove le `x` sono cifre
numeriche arbitrarie. Il contenuto del file non è necessariamente
ordinato.

Da quanto detto sopra si può dedurre che ci sia sicuramente almeno un
numero di telefono che compare più di una volta, perché il file
contiene più elementi di quanti siano i possibili numeri distinti. Il
vostro compito è di implementare un algoritmo efficiente che stampi a
video **il più piccolo numero di telefono che compare più di una
volta** nel file di input.

Il file di input ha $n$ righe, ciascuna delle quali contenente un
numero di telefono (si consideri [questo esempio](telefono.in)). Il
programma riceve il nome del file di input come unico parametro sulla
riga di comando, e deve stampare a video il minimo numero ripetuto
presente nel file.

Per compilare:

        gcc -std=c90 -Wall -Wpedantic telefono.c -o telefono

Per eseguire in ambiente Linux/MacOSX:

        ./telefono nome_file

Per eseguire in ambiente Windows:

        .\telefono nome_file

dove `nome_file` è il nome del file di input contenente l'elenco dei
numeri di telefono.

## Per approfondire

Un aspetto complicato di questo esercizio è la generazione dei file di
input (che non è richiesta, ma che ho dovuto fare io per preparare gli
input). Dato un intero $n > 200000$ e un numero di telefono $t$, come
fareste per generare un file di input composto da $n$ numeri di
telefono come sopra, non necessariamente in ordine, in cui il minimo
valore ripetuto sia esattamente $t$?

## File

- [telefono.c](telefono.c)
- [telefono.in](telefono.in) ([output atteso](telefono.out))
- [telefono1.in](telefono1.in)
- [telefono2.in](telefono2.in)
- [telefono3.in](telefono3.in)
- [telefono4.in](telefono4.in)

***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <sys/ioctl.h>

/* MAXN è il massimo numero di valori che possono essere presenti nel
   file. Questo parametro si può considerare fissato, ma il programma
   dovrebbe funzionare con qualsiasi valore di MAXN */
#define MAXN (size_t)250000
#define MAX_TELEFONO 100000

void loading_bar(int row, int n, int max);
void random_generate(const char *fout, int t);
int random_number(int max);
int random_range(int min, int max);
int compare(const void *pa, const void *pb);

int main( int argc, char *argv[] )
{
    /* [TODO] Il programma fornitosi limita a leggere e stampare il
       contenuto del file di input; lo si modifichi per risolvere il
       problema proposto, anche definendo ulteriori funzioni di
       supporto. */

    FILE *fin;
    int num_tel, i, l, *arr;
    const char *filename = "telefonX.in";

    srand(time(NULL));
    system("clear");
    printf("\033[?25l");

    if (argc == 1) {
        num_tel = random_number(MAX_TELEFONO);
        random_generate(filename, num_tel);
    } else if (argc != 2) {
        fprintf(stderr, "Usage: %s input_file_name\n", argv[0]);
        return EXIT_FAILURE;
    } else {
        filename = argv[1];
    }

    l = 0;
    arr = (int *)malloc(MAXN * sizeof(int));
    assert(arr != NULL);

    fin = fopen(filename, "r");
    if (fin == NULL) {
        fprintf(stderr, "Can not open \"%s\"\n", argv[1]);
        return EXIT_FAILURE;
    }

    i = 0;
    while (1 == fscanf(fin, "%d", &num_tel)) {
        arr[i] = num_tel;
        i++;
    }
    l = i;

    /* Ordino il vettore di elementi e cerco la prima occorrenza di due elementi consecutivi uguali */
    qsort(arr, l, sizeof(int), compare);
    for (i = 0; i < l - 1 && arr[i] != arr[i + 1]; i++);
    printf("First occurency: %d\n", arr[i]);
    printf("\033[?25h");

    fclose(fin);
    return EXIT_SUCCESS;
}

void random_generate(const char *filename, int t) {
    FILE *fout = fopen(filename, "w");
    int *a, i, j;

    a = (int *)malloc(MAXN * sizeof(int));
    if (a == NULL) {
        fprintf(stderr, "Memory error");
        exit(EXIT_FAILURE);
    }
    
    /* Genera numeri casuali in modo che t sia il primo ad essere ripetuto, 
    ordino l'array in modo da trovare le occorrenze prendendo direttamente il valore successivo
    e mischio gli elementi in modo da avere valori in ordine casuale */
    do {
        puts("Generating random numbers...");
        for (i = 0; i < MAXN; i++) {
            a[i] = random_number(MAX_TELEFONO);
            for (j = 0; j < MAXN; j++) {
                while (a[i] == a[j] && a[i] < t) {
                    a[i] = random_number(MAX_TELEFONO);
                }
            }
            loading_bar(2, i, MAXN);
        }
        qsort(a, MAXN, sizeof(int), compare);
        for (i = 0; i < MAXN - 1 && a[i] != a[i + 1]; i++);
    } while (a[i] != t);
    puts("\nNumbers generated, filling file...");

    for (i = 0; i < MAXN; i++) {
        fprintf(fout, "%d\n", a[i]);
        loading_bar(4, i, MAXN);
    }
    puts("\nFile filled successfully...");

    fclose(fout);
    free(a);
}

void loading_bar(int row, int n, int max) {
    int i, length, perc;
    struct winsize w;

    ioctl(0, TIOCGWINSZ, &w);
    length = w.ws_col - 2;
    perc = (int)(n * length / max);

    printf("\033[%d;0H", row);
    putchar('[');
    for (i = 0; i < length; i++) {
        if (i <= perc) {
            putchar('#');
        } else {
            putchar(' ');
        }
    }
    putchar(']');
}

/* Genera le cifre e il prefisso, che genero con un numero random 1 o 2 moltiplico per 2 e 
ottengo o 2 o 4 e aggiungo 1 per ottenere o 3 o 5 per poi sommarlo con le cifre che vanno da 0 a MAX_TELEFONO */
int random_number(int max) {
    return random_range(0, max) + (random_range(1, 3) * 2 + 1) * max;
}

int random_range(int min, int max) {
    return rand() % (max - min) + min;
}

int compare(const void *pa, const void *pb) {
    int a, b;
    a = *(int *)pa;
    b = *(int *)pb;
    return a - b;
}