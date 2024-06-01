/* --------------------------------------------------------
    Nome:       Davide 
    Cognome:    Mancini 
    Matricola:  0001114441 
    Classe:     A
    Mail:       davide.mancini10@studio.unibo.it
----------------------------------------------------------- */

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>

#define NODE_UNDEF -1
#define DIRECTIONS 4

/* Invece di implementare il grafo con matrici di adiacenza, ho strutturato
 * un vettore di lunghezza 4 per ogni cella della matrice, dove ogni elemento
 * contiene l'altezza delle celle adiacenti nelle rispettive direzioni, indicate
 * dall'enum Direction qui sotto */
typedef enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
} Direction;

typedef struct Coord {
    int x, y;
} Coord;

typedef struct Edge {
    Coord src, dst;
    double h_src, h_dst;
} Edge;

typedef struct {
    int key;
    Coord cell;
    double prio;
} HeapElem;

typedef struct {
    HeapElem *heap;
    int *pos; /* Utilizzato per ottimizzare l'heap */
    int n; /* Numero di coppie (chiave, prio) presenti nell'heap */
    int size; /* Massimo numero di coppie (chiave, prio) che possono essere contenuti nell'heap */
} MinHeap;

typedef struct Cell {
    double height;
    double adj[DIRECTIONS];
} Cell;

typedef struct Graph {
    unsigned int n, m; /* Numero di righe e colonne della matrice */
    unsigned int c_cell; /* Costo di ogni cella */
    unsigned int c_height; /* Costo di ogni altezza */
    Cell **cells;
} Graph;

/* Funzioni per il minheap */
int valid(const MinHeap *h, int i) {
    assert(h != NULL);

    return ((i >= 0) && (i < h->n));
}

/* Funzione di supporto: scambia heap[i] con heap[j] */
void swap(MinHeap *h, int i, int j) {
    HeapElem tmp;

    assert(h != NULL);
    assert(valid(h, i));
    assert(valid(h, j));
    assert(h->pos[h->heap[i].key] == i);
    assert(h->pos[h->heap[j].key] == j);

    tmp = h->heap[i];
    h->heap[i] = h->heap[j];
    h->heap[j] = tmp;

    h->pos[h->heap[i].key] = i;
    h->pos[h->heap[j].key] = j;
}

/* Funzione di supporto: restituisce l'indice del padre del nodo i */
int parent(const MinHeap *h, int i) {
    assert(valid(h, i));

    return (i+1)/2 - 1;
}

/* Funzione di supporto: restituisce l'indice del figlio sinistro del
   nodo `i`. Ritorna un indice non valido se `i` non ha figlio
   sinistro. */
int lchild(const MinHeap *h, int i) {
    assert(valid(h, i));

    return 2*i + 1;
}

/* Funzione di supporto: restituisce l'indice del figlio destro del
   nodo `i`. Ritorna un indice non valido se `i` non ha figlio
   destro. */
int rchild(const MinHeap *h, int i) {
    assert(valid(h, i));

    return 2*i + 2;
}

/* Funzione di supporto: restituisce l'indice del figlio di `i` con
   priorità minima. Se `i` non ha figli, restituisce -1 */
int min_child(const MinHeap *h, int i) {
    int l, r, result = -1;

    assert(valid(h, i));

    l = lchild(h, i);
    r = rchild(h, i);
    if (valid(h, l)) {
        result = l;
        if (valid(h, r) && (h->heap[r].prio < h->heap[l].prio)) {
            result = r;
        }
    }
    return result;
}

/* Funzione di supporto: scambia l'elemento in posizione `i` con il
   padre fino a quando raggiunge la posizione corretta nello heap */
void move_up(MinHeap *h, int i) {
    int p;

    assert(valid(h, i));

    p = parent(h, i);
    while ( valid(h, p) && (h->heap[i].prio < h->heap[p].prio) ) {
        swap(h, i, p);
        i = p;
        p = parent(h, i);
    }
}

/* Funzione di supporto: scambia l'elemento in posizione `i` con il
   figlio avente priorità minima, fino a quando l'elemento raggiunge
   la posizione corretta. */
void move_down(MinHeap *h, int i) {
    int done = 0;

    assert(valid(h, i));

    /* L'operazione viene implementata iterativamente, sebbene sia
       possibile una implementazione ricorsiva probabilmente più
       leggibile. */
    do {
        const int dst = min_child(h, i);
        if (valid(h, dst) && (h->heap[dst].prio < h->heap[i].prio)) {
            swap(h, i, dst);
            i = dst;
        } else {
            done = 1;
        }
    } while (!done);
}

/* Restituisce true (nonzero) se lo heap è vuoto */
int minheap_is_empty(const MinHeap *h) {
    assert(h != NULL);

    return (h->n == 0);
}

/* Modifica la priorità associata alla chiave key. La nuova priorità
   può essere maggiore, minore o uguale alla precedente. */
void minheap_change_prio(MinHeap *h, int key, Coord cell, double newprio) {
    int j;
    double oldprio;

    assert(h != NULL);
    assert(key >= 0 && key < h->size);
    j = h->pos[key];
    assert( valid(h, j) );
    oldprio = h->heap[j].prio;
    h->heap[j].prio = newprio;
    if (newprio > oldprio) {
        move_down(h, j);
    } else {
        move_up(h, j);
    }
}

void minheap_clear(MinHeap *h) {
    int i;
    assert(h != NULL);
    for (i=0; i<h->size; i++) {
        h->pos[i] = -1;
    }
    h->n = 0;
}

/* Costruisce un min-heap vuoto che può contenere al massimo
   `size` elementi */
MinHeap *minheap_create(int size) {
    MinHeap *h = (MinHeap *)malloc(sizeof(MinHeap));
    assert(h != NULL);
    assert(size > 0);

    h->size = size;
    h->heap = (HeapElem *)malloc(size * sizeof(HeapElem));
    assert(h->heap != NULL);
    h->pos = (int *)malloc(size * sizeof(int));
    assert(h->pos != NULL);
    minheap_clear(h);
    return h;
}

/* Restituisce true (nonzero) se lo heap è pieno, cioè è stata
   esaurita la capienza a disposizione */
int minheap_is_full(const MinHeap *h) {
    assert(h != NULL);

    return (h->n == h->size);
}

/* Inserisce una nuova coppia (key, prio) nello heap. */
void minheap_insert(MinHeap *h, int key, Coord cell, double prio) {
    int i;

    assert( !minheap_is_full(h) );
    assert((key >= 0) && (key < h->size));
    assert(h->pos[key] == -1);

    i = h->n++;
    h->pos[key] = i;
    h->heap[i].key = key;
    h->heap[i].cell = cell;
    h->heap[i].prio = prio;
    move_up(h, i);
}

/* Restituisce l'elemento con priorità minima */
HeapElem minheap_min(const MinHeap *h) {
    assert( !minheap_is_empty(h) );

    return h->heap[0];
}

/* Rimuove la coppia (chiave, priorità) con priorità minima;
   restituisce l'elemento con priorità minima. */
HeapElem minheap_delete_min(MinHeap *h) {
    HeapElem result;
    int key;

    assert( !minheap_is_empty(h) );

    result = minheap_min(h);
    key = result.key;
    swap(h, 0, h->n-1);
    assert( h->heap[h->n - 1].key == key );
    h->pos[key] = -1;
    h->n--;
    if (!minheap_is_empty(h)) {
        move_down(h, 0);
    }
    return result;
}

void minheap_destroy(MinHeap *h) {
    assert(h != NULL);

    h->n = h->size = 0;
    free(h->heap);
    free(h->pos);
    free(h);
}

/* Libera dalla memoria tutti dati allocati all'interno del grafo */
void graph_destroy(Graph *g) {
    int i;
    for (i = 0; i < g->n; i++) {
        free(g->cells[i]);
    }
    free(g->cells);
    free(g);
}

/* Funzione per stampare i dati di un grafo */
void graph_print(Graph *g) {
    int i, j;

    for (i = 0; i < g->n; i++) {
        for (j = 0; j < g->m; j++) {
            int cell = g->cells[i][j].height;
            printf("%d ", cell);
        }
        printf("\n");
    }
}

/* Funzione per ottenere la cella adiacente nella direzione scelta */
double graph_adj(Graph *g, int x, int y, int dir) {
    return g->cells[y][x].adj[dir];
}

Cell *graph_at(Graph *g, int x, int y) {
    return &g->cells[y][x];
}

/* In base alla direzione cambio le coordinate della cella e ritorno
 * le coordinate della cella adiacente nella seguente direzione
 */
Coord graph_adj_coord(Coord cell, int dir) {
    switch (dir) {
    case UP:
        cell.y--;
        break;
    case DOWN:
        cell.y++;
        break;
    case LEFT:
        cell.x--;
        break;
    case RIGHT:
        cell.x++;
        break;
    }
    return cell;
}

void relax(Graph *g, MinHeap *h, Edge *e, double *d, Coord *p) {
    unsigned int n = g->n;

    /* Ottengo il peso di entrambe le celle e calcolo la distanza */
    int u = e->src.y * n + e->src.x;
    int v = e->dst.y * n + e->dst.x;
    double height = (e->h_src - e->h_dst) * (e->h_src - e->h_dst);

    if (d[u] + height < d[v]) {
        d[v] = d[u] + height;
        p[v].x = e->src.x;
        p[v].y = e->src.y;

        minheap_change_prio(h, v, e->dst, d[v]);
    }
}

void dijkstra(Graph *g, double *d, Coord *p) {
    int x, y, v, dir;
    unsigned int n, m, size;
    MinHeap *h;
    n = g->n;
    m = g->m;
    size = n * m;
    h = minheap_create(size);

    /* Inizializzo i vettori distanza e predecessore, la distanza
       dalla sorgente, che sarà sempre il primo nodo, è 0 */
    for (v = 0; v < size; v++) {
        d[v] = HUGE_VAL;
        p[v].x = NODE_UNDEF;
        p[v].y = NODE_UNDEF;
    }
    d[0] = 0.0;

    /* Riempio l'heap con tutti i nodi */
    for (y = 0; y < n; y++) {
        for (x = 0; x < m; x++) {
            int key = y * n + x;
            Coord cell;
            cell.x = x;
            cell.y = y;
            minheap_insert(h, key, cell, d[key]);
        }
    }

    /* Scorro l'heap finché non è vuoto, estraggo ogni volta l'arco più 
       piccolo del nodo attuale e lo rilasso */
    while (!minheap_is_empty(h)) {
        HeapElem min = minheap_delete_min(h);
        Coord src_coord = min.cell;

        for (dir = 0; dir < DIRECTIONS; dir++) {
            /* Ottengo le celle della sorgente e della destinazione
               tramite le adiacenza della sorgente nella direzione passata */
            double src = graph_at(g, src_coord.x, src_coord.y)->height;
            double dst = graph_adj(g, src_coord.x, src_coord.y, dir);

            /* Se in questa direzione la cella è fuori dalla matrice
               non rilassa nulla */
            if (dst != NODE_UNDEF) {
                Coord dst_coord = graph_adj_coord(src_coord, dir);
                Edge e;
                e.h_src = src;
                e.h_dst = dst;
                e.src = src_coord;
                e.dst = dst_coord;
                
                relax(g, h, &e, d, p);
            }
        }
    }

    minheap_destroy(h);
}

/* Prende le celle degli estremi della matrice e assegna
 * un valore invalido poiché non ha adiacenze oltre i contorni 
 */
void border_adj(Graph *g, int x, int y) {
    Cell *cell = graph_at(g, x, y);

    if (y == 0) { /* Prima riga */
        cell->adj[UP] = NODE_UNDEF;
    } else if (y == g->n - 1) { /* Ultima riga */
        cell->adj[DOWN] = NODE_UNDEF;
    }

    if (x == 0) { /* Prima colonna */
        cell->adj[LEFT] = NODE_UNDEF;
    } else if (x == g->m - 1) { /* Ultima colonna */
        cell->adj[RIGHT] = NODE_UNDEF;
    }
}

/* Prende come input il grafo e crea i vettori dove sono
 * contenuti i dettagli sulle celle adiacenti, gestendo anche
 * i contorni della matrice dove non ci sono adiacenze
 */
void create_adj(Graph *g) {
    int x, y;
    Cell *cell;

    for (y = 0; y < g->n; y++) {
        for (x = 0; x < g->m; x++) {
            border_adj(g, x, y);

            /* Gestisce i casi in cui le adiacenze esistono e salvo il valore
               delle celle adiacenti in un array e l'indice indica la direzione
               della cella adiacente */
            cell = graph_at(g, x, y);
            if (y > 0) {
                cell->adj[UP] = graph_at(g, x, y - 1)->height;
            }
            if (y < g->n - 1) {
                cell->adj[DOWN] = graph_at(g, x, y + 1)->height;
            }
            if (x > 0) {
                cell->adj[LEFT] = graph_at(g, x - 1, y)->height;
            }
            if (x < g->m - 1) {
                cell->adj[RIGHT] = graph_at(g, x + 1, y)->height;
            }
        }
    }
}

/* Funzione di supporto per leggere un parametro intero del file */
void read_double(FILE *f, double *ptr) {
    if (fscanf(f, "%lf", ptr) != 1) {
        fprintf(stderr, "Errore durante la lettura del file\n");
        exit(EXIT_FAILURE);
    }
}

/* Funzione di supporto per leggere un parametro intero senza segno del file */
void read_uint(FILE *f, unsigned int *ptr) {
    if (fscanf(f, "%u", ptr) != 1) {
        fprintf(stderr, "Errore durante la lettura del file\n");
        exit(EXIT_FAILURE);
    }
}

/* Prende il file in input e salva il contenuto nella
 * matrice contenuta nella struttura grafo, restituendola
 */
Graph *graph_read_from_file(FILE *f) {
    Graph *g;
    int i, j;
    unsigned int c_cell, c_height;
    unsigned int n, m;

    /* Legge le prime 4 */
    read_uint(f, &c_cell);
    read_uint(f, &c_height);
    read_uint(f, &n);
    read_uint(f, &m);

    assert(n >= 5 || n <= 250);
    assert(m >= 5 || m <= 250);

    g = (Graph *)malloc(sizeof(Graph));
    assert(g != NULL);
    g->n = n;
    g->m = m;
    g->c_cell = c_cell;
    g->c_height = c_height;

    /* Creo una matrice di celle dinamicamente allocando
     * in ogni riga un array di dimensione m
     */
    g->cells = (Cell **)malloc(sizeof(Cell *) * n);
    assert(g->cells != NULL);
    for (i = 0; i < n; i++) {
        g->cells[i] = (Cell *)malloc(sizeof(Cell) * m);
        assert(g->cells[i] != NULL);
    }

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            read_double(f, &(g->cells[i][j].height));
        }
    }

    return g;
}

void print_path(const Coord *p, Coord dst, unsigned int n, unsigned int size)
{
    int key = dst.y * n + dst.x;
    if (key < 0) {
        printf("Non raggiungibile");
    } else if (key == 0) {
        printf("0 0\n");
    } else {
        print_path(p, p[key], n, size);

        printf("%d %d\n", dst.x, dst.y);

        if (key == size - 1) {
            printf("-1 -1\n");
        } 
    }
}

double road_total_cost(Graph *g, double *d, Coord *p, int k) {
    int i;
    double init_cost;
    double total_distance;
    int key = 0;

    init_cost = g->c_cell * k;
    total_distance = 0;
    for (i = 0; i < k - 1; i++) {
        /*int key = p[i].y * g->n + p[i].x;
        total_distance += d[key];*/
    }
    total_distance *= g->c_height;

    return init_cost + total_distance;
}

int main(int argc, char **argv) {
    Graph *g;
    double *d;       /* d[v] è la distanza minima dalla sorgente al
                        nodo v */
    Coord *p;          /* p[v] è il predecessore di v lungo il cammino
                        minimo dalla sorgente a v */
    unsigned int size;
    double road_cost;
    Coord dst;
    FILE *filein;
    
    if (argc != 2) {
        fprintf(stderr, "Usage: %s filename\n", argv[0]);
        return EXIT_FAILURE;
    }

    filein = fopen(argv[1], "r");
    if (filein == NULL) {
        fprintf(stderr, "Can not open %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    g = graph_read_from_file(filein);
    create_adj(g);

    size = g->n * g->m;
    d = (double *)malloc(size * sizeof(double)); assert(d != NULL);
    p = (Coord *)malloc(size * sizeof(Coord)); assert(p != NULL);

    dijkstra(g, d, p);
    /*graph_print(g);*/
    dst.x = g->n - 1;
    dst.y = g->m - 1;
    print_path(p, dst, g->n, size);

    road_cost = road_total_cost(g, d, p, size);
    printf("%.f\n", road_cost);

    free(p);
    free(d);
    graph_destroy(g);
    fclose(filein);

    return EXIT_SUCCESS;
}