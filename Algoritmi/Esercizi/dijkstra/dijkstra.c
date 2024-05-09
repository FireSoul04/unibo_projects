/****************************************************************************
 *
 * dijkstra.c -- Algoritmo di Dijkstra
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
% LabASD - Algoritmo di Dijkstra
% Moreno Marzolla <moreno.marzolla@unibo.it>
% Ultimo aggiornamento: 2024-05-08

![Edsger W. Dijkstra (1930--2002) By Hamilton Richards - manuscripts of Edsger W. Dijkstra, University Texas at Austin, CC BY-SA 3.0, <https://commons.wikimedia.org/w/index.php?curid=4204157>](Dijkstra.jpg "Edsger W. Dijkstra")

Questo esercizio ha come sopo l'implementazione dell'algoritmo di
Dijkstra per il calcolo del cammini minimi da singola sorgente in un
grafo orientato pesato con pesi non negativi. L'algoritmo di Dijkstra
sfrutta una coda di priorità, che abbiamo già implementato nei
programmi [minheap.c](../solutions/minheap.c) e
[minheap.h](../solutions/minheap.h)).

Detta $d[v]$ è la distanza minima tra la sorgente e il nodo $v$, $v
\in \{0, \ldots, n-1\}$, l'algoritmo di Dijkstra inizializza tutte le
distanze a $+\infty$ per poi calcolare i valori corretti. Per i
dettagli dell'algoritmo si faccia riferimento al materiale delle
lezioni in aula. Per rappresentare $+\infty$ si può usare il simbolo
`HUGE_VAL` che è associato ad un valore di tipo `float` o `double`
definito in `<math.h>`[^1].  Questo simbolo è parte dello standard
C90, per cui deve essere presente in tutti i compilatori conformi.

[^1]: In realtà la documentazione afferma che

      > The macros `HUGE_VAL`, `HUGE_VALF`, `HUGE_VALL` expand to
      > constants of types `double`, `float` and `long double`,
      > respectively, that represent a large positive value, possibly
      > positive infinity.

      Il simbolo `INFINITY` rappresenta il valore "infinito" su
      processori che supportano lo standard
      [IEEE754](https://en.wikipedia.org/wiki/IEEE_754), ma purtroppo
      è definito solo da C99 in poi. `INFINITY` non è semplicemente
      "un valore grande": ad esempio, lo standard IEEE754 impone che
      se $x$ è un qualunque valore positivo finito, allora `INFINITY +
      x == INFINITY`, mentre `HUGE_VAL + x` potrebbe causare
      overflow. I compilatori che ho a disposizione _sembrano_
      definire `HUGE_VAL` come `INFINITY`, ma non è garantito che sia
      sempre così.

Questo programma memorizza l'albero dei cammini minimi in due modi:
come array di predecessori `p[]` di lunghezza $n$, e in un array di
puntatori ad archi `sp[]` sempre di lunghezza $n$. Specificamente,
`p[v]` è un intero e rappresenta l'identificativo (indice) del nodo
che precede $v$ lungo il cammino minimo dalla sorgente a $v$; se $v$
non ha predecessore (ad es., perché è il nodo sorgente o perché non è
raggiungibile dalla sorgente) si pone `p[v] = -1` oppure `p[v] =
NODE_UNDEF` (il simbolo `NODE_UNDEF` vale -1 ed è definito all'inizio
del programma). `sp[v]` è un puntatore all'arco entrante nel nodo $v$
lungo il cammino minimo dalla sorgente a $v$; se $v$ non è
raggiungibile dalla sorgente, oppure coincide con la sorgente, si pone
`sp[v] = NULL`; si faccia riferimento alla Figura 1.

![Figura 1: Esempio di grafo orientato pesato con l'albero dei cammini
minimi usando il nodo 0 come sorgente. `sp[v]` punta all'arco in
ingresso verso il nodo `v`, se `v` è raggiungibile dalla
sorgente.](shortest-paths.svg)

Poiché l'array `sp[]` non viene mai sfruttato da questo programma,
suggerisco di lasciarlo inizialmente indefinito.

Il programma riceve da uno a tre parametri sulla riga di comando:

- il primo parametro è il nome del file di input; il formato
  dell'input è quello utilizzato dal tipo [grafo](graph.html);

- il secondo parametro è un intero che indica il nodo sorgente (se
  manca, si assume 0 come sorgente);

- il terzo parametro è un intero che indica il nodo destinazione. Si
  noti che il programma calcola sempre le distanze di *tutti* i nodi
  dalla sorgente, per cui il nodo destinazione influenza solo ciò che
  viene stampato ma non il costo asintotico dell'algoritmo. Se la
  destinazione non viene specificata, stampa le distanze e i cammini
  minimi verso tutti i nodi del grafo.

Per sperimentare il proprio programma su grafi più grandi, si possono
usare gli input nella Tabella 1, che rappresentano porzioni delle reti
stradali di alcuni stati americani e della città di Roma. Viste le
dimensioni degli input, si suggerisce di disattivare la stampa dei
cammini minimi (commentare la chiamata alla funzione `print_path()`
dentro `print_dist()`).

:Tabella 1: Alcuni input di medio/grandi dimensioni

Dataset                     Nodi ($n$)   Archi ($m$)
------------------------- ------------ -------------
[Nevada](graph-NV.in)           261155        618175
[Maine](graph-ME.in)            194505        425708
[Vermont](graph-VT.in)           97975        212979
[Delaware](graph-DE.in)          49109        119744
[Roma](graph-rome.in)             3353          8859
------------------------- ------------ -------------

I dati in Tabella 1 facevano parte del [9th DIMACS implementation
challenge--Shortest
Paths](https://www.diag.uniroma1.it/challenge9/download.shtml), una
competizione internazionale in cui venivano confrontate
implementazioni efficienti di alcuni algoritmi su grafi, tra cui
quelli per cammini minimi.  Si presti attenzione al fatto che i grafi
in tabella non sono necessariamente fortemente connessi, quindi non
tutti i nodi sono raggiungibili da tutti gli altri.

Per compilare:

        gcc -std=c90 -Wall -Wpedantic minheap.c graph.c dijkstra.c -o dijkstra

Per stampare le distanze e i cammini minimi dal nodo 0:

        ./dijkstra graph10.in 0

su Windows:

        .\dijkstra graph10.in 0

Per stampare la distanza e il cammino minimo dal nodo 3 al nodo 4:

        ./dijkstra graph10.in 3 4

su Windows:

        .\dijkstra graph10.in 3 4

## File

- [dijkstra.c](dijkstra.c)
- [minheap.c](../solutions/minheap.c)
- [minheap.h](../solutions/minheap.h)
- [graph.c](../solutions/graph.c)
- [graph.h](../solutions/graph.h)
- [graph10.in](graph10.in) ([risultato atteso usando il nodo 0 come sorgente](graph10-dijkstra.out))
- [graph100.in](graph100.in)
- [graph1000.in](graph1000.in)

***/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include "minheap.h"
#include "graph.h"

/* Si può usare il simbolo NODE_UNDEF per indicare che il predecessore
   della lista dei padri non esiste. */
const int NODE_UNDEF = -1;

/* Calcola l'albero dei cammini minimi dalla sorgente s usando
   l'algoritmo di Dijkstra.

   Parametri:

   - g: grafo di input con n nodi

   - s: nodo sorgente (0 <= s < n)

   - d[v]: distanza di v dalla sorgente; d[] è un array di n elementi
     allocato dal chiamante che viene riempito da questa funzione

   - p[v]: predecessore di v lungo il cammino dalla sorgente a v; p[]
     è un array di n elementi allocato dal chiamante e viene riempito
     da questa funzione. Se `v` non ha predecessore, ad esempio perché
     è la sorgente o perché non è raggiungibile dalla sorgente, si
     deve porre `p[v] = -1` oppure `p[v] = NODE_UNDEF`

   - sp[v]: puntatore all'arco di g in ingresso a v lungo il cammino
     dalla sorgente a v; sp[] è un array di n puntatori ad arco
     allocato dal chiamante e viene riempito da questa
     funzione. Questo array viene usato dalla funzione `print_sp()`
     che però non viene usata da questo programma, per cui il
     contenuto si può lasciare indefinito.
*/
void dijkstra( const Graph *g, int s, double *d, int *p, const Edge **sp )
{
    /* [TODO] */
}

/* Stampa l'elenco degli archi dell'albero dei cammini minimi nello
   stesso formato usato per il grafo di input. Questa funzione non
   viene usata in questo programma. */
void print_sp( const Graph *g, const Edge **sp )
{
    const int n = graph_n_nodes(g);
    int v;
    int nsp = 0;

    assert(sp != NULL);

    /* Contiamo gli archi che fanno parte dell'albero dei cammini minimi */
    for (v=0; v<n; v++) {
        if (sp[v] != NULL) nsp++;
    }

    printf("%d %d 1\n", n, nsp);
    for (v=0; v<n; v++) {
        const Edge *e = sp[v];
        if (e != NULL) {
            printf("%d %d %f\n", e->src, e->dst, e->weight);
        }
    }
}

/* Questa funzione deve stampare la sequenza di nodi del cammino
   minimo da src a dst, se esiste, oppure "Non raggiungibile" se la
   destinazione non è raggiungibile.  Il formato deve essere:

   src->v0->v1->...->dst

   dove src, vi, dst sono interi che rappresentano i nodi del
   cammino minimo. Non bisogna andare a capo alla fine della
   stampa.

   L'array p[] è l'array dei predecessori, calcolato dall'algoritmo di
   Dijkstra.

   Suggerimento: suggerisco una implementazione ricorsiva, che è molto
   semplice. */
void print_path(const int *p, int src, int dst)
{
    printf("TODO");
    /* [TODO] */
}

/* Stampa la distanza e il cammino minimo da src a dst; se dst < 0,
   stampa le distanze e i cammini minimi da src a tutti i nodi del
   grafo. */
void print_dist( const Graph *g, int src, int dst, const int *p, const double *d )
{
    const int n = graph_n_nodes(g);
    int v, from_idx = 0, to_idx = n-1;

    assert(p != NULL);
    assert(d != NULL);

    if (dst >= 0) {
        from_idx = to_idx = dst;
    }

    printf(" src  dst            d path\n");
    printf("---- ---- ------------ -------------------------\n");
    for (v=from_idx; v<=to_idx; v++) {
        printf("%4d %4d %12.4f ", src, v, d[v]);
        print_path(p, src, v);
        printf("\n");
    }
}

int main( int argc, char *argv[] )
{
    Graph *G;
    const Edge **sp; /* sp[v] è il puntatore all'arco che collega v
                        con il suo predecessore nell'albero dei
                        cammini minimi */
    double *d;       /* d[v] è la distanza minima dalla sorgente al
                        nodo v */
    int *p;          /* p[v] è il predecessore di v lungo il cammino
                        minimo dalla sorgente a v */
    FILE *filein = stdin;
    int n, src = 0, dst = NODE_UNDEF;

    if ( (argc < 2) || (argc > 4) ) {
        fprintf(stderr, "Usage: %s filename [src [dst]]\n", argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-") != 0) {
        filein = fopen(argv[1], "r");
        if (filein == NULL) {
            fprintf(stderr, "Can not open %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    if (argc > 2)
        src = atoi(argv[2]);

    if (argc > 3)
        dst = atoi(argv[3]);

    G = graph_read_from_file(filein);

    n = graph_n_nodes(G);
    assert((src >= 0) && (src < n));
    assert((dst < 0) || ( (dst >= 0) && (dst < n) ));

    d = (double*)malloc(n * sizeof(*d)); assert(d != NULL);
    p = (int*)malloc(n * sizeof(*p)); assert(p != NULL);
    sp = (const Edge**)malloc(n * sizeof(*sp)); assert(sp != NULL);

    dijkstra(G, src, d, p, sp);
    /* print_sp(G, sp); */
    print_dist(G, src, dst, p, d);
    graph_destroy(G);

    free(d);
    free(p);
    free(sp);
    if (filein != stdin) fclose(filein);

    return EXIT_SUCCESS;
}
