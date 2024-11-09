/****************************************************************************
 *
 * mfset.c -- Strutture Merge-Find
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
% LabASD - Strutture Merge-Find
% Moreno Marzolla <moreno.marzolla@unibo.it>
% Ultimo aggiornamento: 2024-05-02

In questo esercizio implementiamo una struttura dati per insiemi
disgiunti, detta _struttura Merge-Find_ o _Union-Find_ o
_Up-Tree_. L'interfaccia è descritta nel file [mfset.h](mfset.h) e
viene implementata in [nfset.c](mfset.c).

Una struttura merge-find è inizialmente costituita da $n$ insiemi
disgiunti $\{0\}, \{1\}, \ldots, \{n-1\}$. In questo esercizio
implementiamo la versione _QuickUnion_, che supporta in modo
efficiente l'operazione di unione. Nelle strutture QuickUnion, ogni
insieme è rappresentato da un albero i cui nodi sono gli elementi
dell'insieme. La foresta di alberi è realizzata con un _vettore di
padri_ `p[]`. Dato un elemento $x \in \{0, \ldots, n-1\}$, `p[x]`
denota il padre di $x$. Nel caso in cui $x$ sia la radice di un
albero, e quindi non abbia padre, poniamo `p[x] = x`.

![Figura 1: Esempio di foresta merge-find che rappresenta gli insiemi $\{0, 2, 3, 5, 7, 9, 10\}$, $\{1, 4, 8\}$, $\{6\}$](mfset.svg)

Nella Figura 1 riportiamo un esempio di struttura merge-find con
$n=11$ elementi organizzati in tre insiemi disgiunti. I tre alberi
merge-find sono codificati dall'array di padri `p[]` mostrato. Ad
esempio $p[0] = 7$ in quanto il nodo 7 è il padre del nodo 0 nella
foresta merge-find, mentre $p[7] = 7$ perché il nodo 7 è la radice
dell'albero di cui fa parte.

L'operazione di unione è realizzata dalla funzione `mfset_merge(s, x,
y)` che, data una struttura merge-find `s` e due interi $x, y$ che
rappresentano due valori nell'insieme $\{0, \ldots, n-1\}$, modifica
`s` in modo che gli insiemi contenenti $x$ e $y$ vengano uniti (se già
non lo sono). Per fare ciò, si identificano le radici $x_R$ e $y_R$
degli insiemi contenenti $x$ e $y$, e si rende una delle due (ad
esempio $y_R$) figlia dell'altra (ad esempio, $x_R$).

![Figura 2: Struttura dati risultante dopo l'operzione `merge(s, 5, 1)`](mfset-after-union.svg)

In Figura 2 mostriamo come cambia la struttura dati dopo l'operazione
`merge(s, 5, 1)`. Prima dell'unione, la radice dell'albero contenente
$x=5$ è $x_R = 7$; la radice dell'albero contenente $y = 1$ è $y_R =
4$. Per unire i due insiemi rendiamo $4$ figlio del nodo $7$ ponendo
$p[4] \leftarrow 7$ (sarebbe stato anche possibile rendere $7$ figlio
di $4$).

Il programma [mfset-main.c](mfset-main.c) contiene una funzione
`main()` che legge da un file una sequenza di comandi che manipolano
una struttura merge-find. I comandi validi sono elencati nella Tabella
1 (le lettere _in corsivo_ indicano valori numerici).

: Tabella 1: Comandi nel file di input

------------------------------------------------------------------
Comando       Significato
-----------   ----------------------------------------------------
_n_           Crea una struttura MF con _n_ nodi; questo comando
              è sempre il primo e compare una sola volta

`m` _x y_     Fonde gli insiemi contenenti _x_ e _y_

`q` _x y_     Determina se _x_ e _y_ appartengono allo
              stesso insieme
------------------------------------------------------------------

dove $n$ è un intero positivo, e $x, y$ sono interi compresi tra 0 e
$n-1$ (inclusi).

Per compilare il programma dalla riga di comando:

        gcc -std=c90 -Wall -Wpedantic mfset.c mfset-main.c -o mfset

Per eseguire in ambiente Linux/MacOSX:

        ./mfset-main mfset.in

Per eseguire in ambiente Windows:

        .\mfset-main mfset.in

## Per approfondire

Chi lo desidera può implementare qualche euristica tra quelle viste a
lezione. L'euristica di _compressione dei cammini_ consente di
limitare l'altezza degli alberi, e si realizza con una modifica della
funzione `mfset_find()` vista a lezione. L'idea è che, ogni volta in
cui si effettua una operazsione _find(x)_, tutti i nodi che si
incontrano nel cammino da $x$ alla radice vengono resi figli della
radice.

Un'altra possibilità per migliorare le prestazioni di una struttura
merge-find è l'euristica _union by rank_, che consiste nel tenere
traccia dell'altezza di ciascun albero, in modo che `mfset_merge()`
renda la radice dell'albero più basso figlia di quella dell'albero più
alto. L'altezza degli alberi può essere mantenuta nell'array
ausiliario `h[]` definito nella struttura `MFSet`:

```C
typedef struct {
    int n;
    int *p;
    int *h;
} MFSet;
```

`h[]` ha lunghezza $n$, e `h[x]` deve rappresentare l'altezza
dell'albero che ha $x$ come radice; se $x$ non è la radice di un
albero, il valore `h[x]` non viene utilizzato ed è quindi
ininfluente.

Inizialmente tutte le altezze valgono zero (un albero composto da un
singolo nodo ha altezza zero). Quando si effettua l'unione di due
alberi con radice $x_R, y_R$ si possono verificare i casi seguenti:

- $h[x_R] < h[y_R]$: l'albero con radice $x_R$ diventa figlio della
  radice $y_R$; l'altezza di $y_R$ non cambia (perché?);

- $h[x_R] > h[y_R]$: l'albero radicato in $y_R$ diventa figlio della
  radice $x_R$; l'altezza di $x_R$ non cambia

- $h[x_R] = h[y_R]$: in questo caso si sceglie arbitrariamente la
  nuova radice (ad esempio, scegliamo $x_R$), e si rende l'altro
  albero figlio della radice scelta. Si noti che l'altezza del nuovo
  albero è maggiore di 1 rispetto alla vecchia altezza, cioè se $x_R$
  è la nuova radice, occorre porre $h[x_R] \leftarrow h[x_R] + 1$.

L'euristica _union by rank_ è più laboriosa da implementare rispetto
alla compressione dei cammini, ed è anche un po' meno efficiente, ma
costituisce comunque un utile esercizio per chi vuole provare.

## File

- [mfset.c](mfset.c)
- [mfset.h](mfset.h)
- [mfset-main.c](mfset-main.c)
- [mfset.in](mfset.in) ([output atteso](mfset.out))
- [mfset1.in](mfset1.in)
- [mfset2.in](mfset2.in)
- [mfset3.in](mfset3.in)

***/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "mfset.h"

MFSet *mfset_create(int n)
{
    int i;
    MFSet *s = (MFSet*)malloc(sizeof(*s));
    assert(s != NULL);

    s->n = n;
    s->p = (int*)malloc(n * sizeof(*(s->p)));
    assert(s->p != NULL);
    s->h = (int *)malloc(n * sizeof(int));
    assert(s->h != NULL);
    for (i=0; i<n; i++) {
        s->p[i] = i;
        s->h[i] = 0;
    }
    return s;
}

void mfset_destroy(MFSet *s)
{
    assert(s != NULL);

    s->n = 0;
    free(s->p);
    free(s->h);
    free(s);
}

void mfset_merge(MFSet *s, int x, int y)
{
    /* [TODO] */
    int px, py;

    assert(s != NULL);
    assert((x >= 0) && (x < s->n));
    assert((y >= 0) && (y < s->n));

    px = mfset_find(s, x);
    py = mfset_find(s, y);

    if (px == py) {
        return;
    }

    if (s->h[px] > s->h[py]) {
        s->p[py] = x;
    } else {
        s->p[px] = y;
        if (s->h[px] == s->h[py]) {
            s->h[py]++;
        }
    }
}

int mfset_find(MFSet *s, int x)
{
    /* [TODO] */
    
    assert(s != NULL);
    assert(x >= 0);
    assert(x < s->n);
    
    while (s->p[x] != x) {
        x = s->p[x];
        assert(x >= 0);
        assert(x < s->n);
    }
    return x;
}
