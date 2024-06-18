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

typedef struct {
    int key;
    double prio;
} HeapElem;

typedef struct {
    HeapElem *heap;
    int *pos;
    int n;
    int size;
} MinHeap;

typedef struct Edge {
    int src;
    int dst;
    double weight;
    struct Edge *next;
} Edge;

typedef struct {
    unsigned int n;         /* Numero righe matrice */
    unsigned int m;         /* Numero colonne matrice */
    unsigned int c_cell;    /* Costo di una cella */
    unsigned int c_height;  /* Costo per ogni differenza di altezza */
    Edge **edges;
} Graph;

void minheap_clear( MinHeap *h ) {
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
    MinHeap *h = (MinHeap*)malloc(sizeof(*h));
    assert(h != NULL);
    assert(size > 0);

    h->size = size;
    h->heap = (HeapElem*)malloc(size * sizeof(*(h->heap)));
    assert(h->heap != NULL);
    h->pos = (int*)malloc(size * sizeof(*(h->pos)));
    assert(h->pos != NULL);
    minheap_clear(h);
    return h;
}

void minheap_destroy( MinHeap *h ) {
    assert(h != NULL);

    h->n = h->size = 0;
    free(h->heap);
    free(h->pos);
    free(h);
}

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

/* Restituisce true (nonzero) se lo heap è pieno, cioè è stata
   esaurita la capienza a disposizione */
int minheap_is_full(const MinHeap *h) {
    assert(h != NULL);

    return (h->n == h->size);
}

/* Restituisce il numero di elementi presenti nello heap */
int minheap_get_n(const MinHeap *h) {
    assert(h != NULL);

    return h->n;
}

/* Restituisce la chiave associata alla priorità minima */
int minheap_min(const MinHeap *h) {
    assert( !minheap_is_empty(h) );

    return h->heap[0].key;
}

/* Inserisce una nuova coppia (key, prio) nello heap. */
void minheap_insert(MinHeap *h, int key, double prio) {
    int i;

    assert( !minheap_is_full(h) );
    assert((key >= 0) && (key < h->size));
    assert(h->pos[key] == -1);

    i = h->n++;
    h->pos[key] = i;
    h->heap[i].key = key;
    h->heap[i].prio = prio;
    move_up(h, i);
}

/* Rimuove la coppia (chiave, priorità) con priorità minima;
   restituisce la chiave associata alla priorità minima. */
int minheap_delete_min(MinHeap *h) {
    int result;

    assert( !minheap_is_empty(h) );

    result = minheap_min(h);
    swap(h, 0, h->n-1);
    assert( h->heap[h->n - 1].key == result );
    h->pos[result] = -1;
    h->n--;
    if (!minheap_is_empty(h)) {
        move_down(h, 0);
    }
    return result;
}

/* Modifica la priorità associata alla chiave key. La nuova priorità
   può essere maggiore, minore o uguale alla precedente. */
void minheap_change_prio(MinHeap *h, int key, double newprio) {
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

Graph *graph_create( unsigned int n, unsigned int m ) {
    int i;
    Graph *g = (Graph*)malloc(sizeof(*g));
    assert(g != NULL);

    g->n = n;
    g->m = m;
    g->edges = (Edge**)malloc(n * m * sizeof(Edge*));
    assert(g->edges != NULL);
    for (i = 0; i < n * m; i++) {
        g->edges[i] = NULL;
    }
    return g;
}

void graph_destroy(Graph *g) {
    int i;

    assert(g != NULL);

    for (i = 0; i < g->n * g->m; i++) {
        Edge *edge = g->edges[i];
        while (edge != NULL) {
            Edge *next = edge->next;
            free(edge);
            edge = next;
        }
    }
    free(g->edges);
    g->n = 0;
    g->m = 0;
    g->edges = NULL;
    free(g);
}

int graph_nodes(const Graph *g) {
    assert(g != NULL);

    return g->n * g->m;
}

Edge *graph_adj(const Graph *g, int v) {
    assert(g != NULL);
    assert((v >= 0) && (v < graph_nodes(g)));

    return g->edges[v];
}

Edge *create_edge(int src, int dst, double weight) {
    Edge *edge = (Edge *)malloc(sizeof(*edge));
    assert(edge != NULL);

    edge->src = src;
    edge->dst = dst;
    edge->weight = weight;

    return edge;
}

void graph_add_edge(Graph *g, int src, int dst, double h_src, double h_dst) {
    double weight = (h_src - h_dst) * (h_src - h_dst);
    Edge *new_edge = create_edge(src, dst, weight);
    new_edge->next = g->edges[src];
    g->edges[src] = new_edge;
}

void relax( const Graph *g, const Edge *e, MinHeap *h, double *d, int *p ) {
    const int u = e->src;
    const int v = e->dst;
    const double w = g->c_cell + g->c_height * e->weight;
    
    if (d[u] + w < d[v]) {
        d[v] = d[u] + w;
        p[v] = u;

        minheap_change_prio(h, v, d[v]);
    }
}

void dijkstra( const Graph *g, double *d, int *p ) {
    int v, n = graph_nodes(g);
    MinHeap *h = minheap_create(n);
    const Edge *e;

    for (v = 0; v < n; v++) {
        d[v] = HUGE_VAL;
        p[v] = NODE_UNDEF;
    }
    d[0] = 0.0;

    /* Riempio l'heap con tutti i nodi */
    for (v = 0; v < n; v++) {
        minheap_insert(h, v, d[v]);
    }
    
    /* Scorro l'heap finché non è vuoto, estraggo ogni volta l'arco più 
        piccolo del nodo attuale e lo rilasso */
    while (!minheap_is_empty(h)) {
        v = minheap_delete_min(h);

        for (e = graph_adj(g, v); e != NULL; e = e->next) {
            relax(g, e, h, d, p);
        }
    }

    minheap_destroy(h);
}

/* Calcolo il costo totale del percorso prendendo l'ultimo peso
   dell'array dei pesi e aggiungo il costo dell'ultima cella */
double road_total_cost(Graph *g, double *d, int *p) {
    int key = g->n * g->m - 1;
    return d[key] + g->c_cell;
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

/* Funzione per aggiungere gli archi calcolando il peso in base al quadrato della differenza
   dell'altezza della cella sorgente con la cella destinazione trovata nella
   formula per calcolare il costo totale */
void graph_add_all_edges(Graph *g, double *h) {
    int x, y;
    unsigned int n = g->n;
    unsigned int m = g->m;

    for (y = 0; y < n; y++) {
        for (x = 0; x < m; x++) {
            int dst;
            int src = y * m + x;

            if (y > 0) {
                dst = (y - 1) * m + x;
                graph_add_edge(g, src, dst, h[src], h[dst]);
            }
            if (y < n - 1) {
                dst = (y + 1) * m + x;
                graph_add_edge(g, src, dst, h[src], h[dst]);
            }
            if (x > 0) {
                dst = y * m + x - 1;
                graph_add_edge(g, src, dst, h[src], h[dst]);
            }
            if (x < m - 1) {
                dst = y * m + x + 1;
                graph_add_edge(g, src, dst, h[src], h[dst]);
            }
        }
    }
}

/* Prende il file in input e salva il contenuto nella
 * matrice contenuta nella struttura grafo, restituendola
 */
Graph *graph_read_from_file(FILE *f) {
    Graph *g;
    double *heights;
    int i;
    unsigned int c_cell, c_height;
    unsigned int n, m;

    /* Legge le prime 4 righe del file */
    read_uint(f, &c_cell);
    read_uint(f, &c_height);
    read_uint(f, &n);
    read_uint(f, &m);

    assert(n >= 5 || n <= 250);
    assert(m >= 5 || m <= 250);

    g = graph_create(n, m);
    g->c_cell = c_cell;
    g->c_height = c_height;
    
    /* Creo una matrice dove salvo le altezze di ogni cella */
    heights = (double *)malloc(sizeof(double) * n * m);
    assert(heights != NULL);
    for (i = 0; i < n * m; i++) {
        read_double(f, &heights[i]);
    }

    graph_add_all_edges(g, heights);

    free(heights);
    return g;
}

/* Funzione che stampa il percorso con costo minore */
void print_path(const int *p, int dst_x, int dst_y, unsigned int m, unsigned int n) {
    int key = dst_y * m + dst_x;
    if (key < 0) {
        printf("Non raggiungibile");
    } else if (key == 0) {
        printf("0 0\n");
    } else {
        int x = p[key] % m;
        int y = p[key] / m;
        print_path(p, x, y, m, n);

        printf("%d %d\n", dst_y, dst_x);
        if (key == n * m - 1) {
            printf("-1 -1\n");
        } 
    }
}

int main(int argc, char **argv) {
    Graph *g;
    double *d; /* Array dei pesi */
    int *p;    /* Array di chiavi delle celle che formano il percorso migliore */
    unsigned int size;
    double road_cost;
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

    size = g->n * g->m;
    d = (double *)malloc(size * sizeof(double)); assert(d != NULL);
    p = (int *)malloc(size * sizeof(int)); assert(p != NULL);

    dijkstra(g, d, p);
    print_path(p, g->m - 1, g->n - 1, g->m, g->n);

    road_cost = road_total_cost(g, d, p);
    printf("%.f\n", road_cost);

    free(p);
    free(d);
    graph_destroy(g);
    fclose(filein);

    return EXIT_SUCCESS;
}