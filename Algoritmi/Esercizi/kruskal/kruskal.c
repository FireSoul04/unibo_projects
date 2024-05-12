/****************************************************************************
 *
 * kruskal.c -- Algoritmo di Kruskal
 *
 * Copyright (C) 2021, 2022, 2023 Moreno Marzolla
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
% LabASD - Algoritmo di Kruskal
% Moreno Marzolla <moreno.marzolla@unibo.it>
% Ultimo aggiornamento: 2023-05-02

![Joseph Bernard Kruskal, Jr. (1928--2010) <https://web.archive.org/web/20150707154900/http://www-groups.dcs.st-and.ac.uk/~history/Biographies/Kruskal_Joseph.html>](Joseph_Kruskal.jpg)

Scopo di questo esercizio è implementare l'algoritmo di Kruskal per il
calcolo di un _Minimum Spanning Tree_ (MST) di un grafo non orientato
pesato $G=(V, E, w)$. L'algoritmo di Kruskal opera come segue:

- Ordina gli archi per peso crescente;

- Sia $T$ la foresta di alberi costituita da $n$ nodi isolati
  (un nodo per ogni nodo del grafo).

- Per ogni arco $\{u, v\} \in E$, in ordine crescente di peso:

    * Se $u$ e $v$ appartengono ad alberi diversi $T_u$ e $T_v$,
      aggiungi l'arco $\{u, v\}$ al MST e fondi $T_u$ e $T_v$
      in un unico albero.

    * Altrimenti, salta l'arco e passa al successivo.

Per implementare l'algoritmo di Kruskal serve un modo efficiente per
verificare se due nodi appartengono allo stesso albero della
foresta. Per fare questo si usa una struttura _merge-find_ oggetto di
[un'altra esercitazione](mfset.html).

Per ordinare gli archi si può usare un algoritmo di ordinamento
efficiente tra quelli visti a lezione, oppure usare la funzione
`qsort()` dichiarata in `<stdlib.h>`. L'interfaccia della funzione è
la seguente:

```C
#include <stdlib.h>

void qsort(void *base, size_t nmemb, size_t size,
           int (*compare)(const void *, const void *));
```

dove:

- `base` è un puntatore all'inizio dell'array da ordinare;

- `nmemb` è il numero di elementi dell'array da ordinare (attenzione,
  **non** il numero di byte!)

- `size` è la dimensione in byte di ciascuno degli elementi dell'array

- `compare` è un puntatore ad una funzione del tipo
  `int cmp(const void *a, const void *b)` che restituisce:

    + un valore negativo, se `a` viene prima di `b` nell'ordinamento;

    + zero, se `a` e `b` sono considerati uguali;

    + un valore positivo, se `a` viene dopo `b` nell'ordinamento

Esempio di esecuzione dell'algoritmo di Kruskal:

---

![Grafo iniziale](kruskal0.svg)

---

![Aggiunta dell'arco $\{2, 3\}$](kruskal1.svg)

---

![Aggiunta dell'arco $\{1, 2\}$](kruskal2.svg)

---

![Aggiunta dell'arco $\{3, 5\}$](kruskal3.svg)

---

![Aggiunta dell'arco $\{3, 4\}$](kruskal4.svg)

---

![L'arco $\{1, 3\}$ non viene inserito](kruskal5.svg)

---

![L'arco $\{2, 4\}$ non viene inserito](kruskal6.svg)

---

![Aggiunta dell'arco $\{0, 1\}$](kruskal7.svg)

---

![L'arco $\{4, 5\}$ non viene inserito](kruskal8.svg)

---

![L'arco $\{0, 2\}$ non viene inserito](kruskal9.svg)

---

Il programma deve leggere il grafo da un file il cui nome viene
passato come unico parametro sulla riga di comando, e deve stampare a
video l'elenco degli archi che fanno parte del MST. L'ordine con cui
vengono stampati gli archi del MST non è importante. Il formato
dell'input è [quello della struttura Graph](graph.html). L'algoritmo
di Kruskal opera su grafi non orientati.

Il programma stampa l'elenco degli archi che fanno parte del MST nello
stesso formato dell'input. È quindi possibile usare l'output come
input al programma stesso.

Lo scheletro di programma fornito non fa uso della struttura
`Graph`. Infatti, per l'algoritmo di Kruskal è sufficiente
rappresentare il grafo mediante un elenco di archi. Nel nostro caso
usiamo un array `E[]` di strutture `Edge`. Gli archi che fanno parte
del MST vengono memorizzati in un array di puntatori `mst[]` (Figura
1) di lunghezza $n-1$. I primi `nmst` elementi di `mst[]` puntano agli
archi che fanno parte del MST, mentre i rimanenti devono puntare a
`NULL`. Si avrà sempre $\texttt{nmst} \leq n-1$ (perché?).

![Figura 1: Grafo orientato e rappresentazione di un suo MST](kruskal.svg)

Per compilare da riga di comando:

        gcc -std=c90 -Wall -Wpedantic kruskal.c mfset.c -o kruskal

Per eseguire in ambiente Linux/MacOSX:

        ./kruskal graph10.in

Per eseguire in ambiente Windows:

        .\kruskal graph10.in

## Domande

- Cosa succede applicando l'algoritmo di Kruskal ad un grafo non
  connesso?

- Che risultato ci aspettiamo se usiamo l'output di una esecuzione di
  questo programma come input per una successiva esecuzione?  In altre
  parole, cosa ci aspettiamo che succeda se calcoliamo il MST di un
  MST?

## File

- [kruskal.c](kruskal.c)
- [mfset.c](mfset.c)
- [mfset.h](mfset.h)
- [mst10.in](mst10.in) ([output atteso](mst10-kruskal.out))
- [mst100.in](mst100.in) ([output atteso](mst100-kruskal.out))
- [mst1000.in](mst1000.in)
- [mst1500.in](mst1500.in)
- [mst2000.in](mst2000.in)

***/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "mfset.h"

/* Rappresentiamo il grafo come array di archi. Per questo programma
   non è conveniente usare la struttura Grafo (vista in una lezione
   precedente), perché sarebbe più laborioso (anche se certamente
   possibile) ordinare gli archi. */
typedef struct {
    int src, dst;
    double weight;
} Edge;

/* Anche se non è una buona pratica di programmazione, utilizziamo
   variabili globali per memorizzare l'input del programma e il
   risultato calcolato. Questo semplifica il codice, e puo' essere
   considerato accettabile vista la dimensione ridotta di questo
   programma. Chi vuole può eliminare le variabili globali e
   modificare le funzioni aggiungendo opportuni parametri. */

int n = 0;        /* numero di nodi del grafo   */
int m = 0;        /* numero di archi del grafo  */
Edge *E = NULL;   /* Array di archi del grafo   */
int nmst = 0;     /* numero archi del MST       */

/* `mst[]` è l'array dei puntatori agli archi che fanno parte del
   MST. L'array avrà al massimo (n-1) elementi, di cui i primi `nmst`
   sono puntatori agli archi che fanno parte del MST (i restanti
   elementi, se presenti, verranno ignorati). L'array `mst[]` deve
   essere allocato nella funzione Kruskal(). */
const Edge **mst = NULL;


/* Leggi li grafo dal file `filein`, che deve essere già stato aperto
   in lettura dal chiamante, e alloca l'array `E[]` di archi. Il
   formato dell'input è quello usato dalla struttura dati Graph;
   ricordiamo che, per i grafi non orientati, gli archi sono salvati
   su file una sola volta, anche se in fase di lettura la struttura
   Graph li memorizza _due_ volte nelle liste di adiacenza. Siccome
   non usiamo liste di adiacenza, possiamo leggere gli archi e
   salvarli direttamente nell'array `E[]`. */
void readGraph( FILE* filein )
{
    int i, t;
    int nread;

    nread = fscanf(filein, "%d %d %d", &n, &m, &t);
    /* Assicuriamoci di avere letto correttamente tutti e tre i campi
       della fscanf() */
    assert(nread == 3);
    if (t != 0) {
        fprintf(stderr, "ERRORE: questo programma richiede grafi non orientati\n");
        exit(EXIT_FAILURE);
    }
    E = (Edge*)malloc(m * sizeof(*E)); assert(E != NULL);
    for (i=0; i<m; i++) {
        nread = fscanf(filein, "%d %d %lf", &(E[i].src), &(E[i].dst), &(E[i].weight));
        assert(nread == 3);
    }
}

int cmp(const void *a, const void *b) {
    if (((Edge *)a)->weight > ((Edge *)b)->weight) {
        return 1;
    } else if (((Edge *)a)->weight < ((Edge *)b)->weight) {
        return -1;
    } else {
        return 0;
    }
}

/* Calcola il MST usando l'algoritmo di Kruskal e ritorna il peso
   totale dell'albero; alloca l'array `mst[]` e ne definisce i valori
   (l'array `mst[]` contiene puntatori ad archi). Al termine, la
   variabile globale `nmst` deve contenere il numero di archi che
   fanno parte del MST. È consentito allocare più spazio di quello
   strettamente necessario per l'array `mst[]`. */
double Kruskal( void )
{
    /* [TODO] */
    MFSet *mfset;
    double total_weight = 0.0;
    int i;

    mst = (const Edge **)malloc((n - 1) * sizeof(Edge *));
    assert(mst != NULL);

    for (i = 0; i < n - 1; i++) {
        mst[i] = NULL;
    }

    mfset = mfset_create(m);
    qsort(E, m, sizeof(Edge), cmp);

    /* Scorro tutti gli archi e controllo se non fanno
        parte dello stesso gruppo li aggiungo al gruppo aggiungendo 
        l'arco nell'mst e aumentanto il peso totale dell'mst*/
    for (i = 0; i < m; i++) {
        int src, dst;
        src = mfset_find(mfset, E[i].src);
        dst = mfset_find(mfset, E[i].dst);
        if (src != dst) {
            mfset_merge(mfset, src, dst);
            mst[nmst] = &E[i];
            total_weight += mst[nmst]->weight;
            nmst++;
        }
    }

    mfset_destroy(mfset);

    return total_weight;
}

/* Stampa a video l'elenco degli archi del MST nello stesso formato
   usato per il grafo di input. */
void print_mst( void )
{
    int i;

    printf("%d %d 0\n", n, nmst);
    for (i=0; i<nmst; i++) {
        printf("%d %d %f\n", mst[i]->src, mst[i]->dst, mst[i]->weight);
    }
}

int main( int argc, char *argv[] )
{
    double wtot; /* peso totale del MST */
    FILE* filein = stdin;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-") != 0) {
        filein = fopen(argv[1], "r");
        if (filein == NULL) {
            fprintf(stderr, "Can not open %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    readGraph(filein);
    wtot = Kruskal();
    print_mst();
    printf("# MST weight = %f\n", wtot);
    free(E);
    free(mst);
    if (filein != stdin) fclose(filein);

    return EXIT_SUCCESS;
}
