/* --------------------------------------------------------
    Nome e cognome: Davide Mancini 
    Matricola:      0001114441 
    Classe:         A
    Mail:           davide.mancini10@studio.unibo.it
----------------------------------------------------------- */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/* Definisco le strutture Grafo e MinHeap */

typedef enum { GRAPH_UNDIRECTED, GRAPH_DIRECTED } Graph_type;

/* struttura arco */
typedef struct Edge {
    int src;            /* nodo sorgente        */
    int dst;            /* nodo destinazione    */
    double weight;      /* peso dell'arco       */
    struct Edge *next;
} Edge;

/* struttura grafo */
typedef struct {
    int n;              /* numero di nodi               */
    int m;              /* numero di archi              */
    Graph_type t;       /* tipo di grafo (orientato/non orientato) */
    Edge **edges;       /* array di liste di adiacenza  */
    int *in_deg;        /* grado entrante dei nodi      */
    int *out_deg;       /* grado uscente dei nodi       */
} Graph;

typedef struct {
    int key;
    double prio;
} HeapElem;

typedef struct {
    HeapElem *heap;
    int *pos;
    int n; /* quante coppie (chiave, prio) sono effettivamente presenti nello heap */
    int size; /* massimo numero di coppie (chiave, prio) che possono essere contenuti nello heap */
} MinHeap;

/* Codice inerente alla struttura grafo */

/* Crea un nuovo grafo con `n` nodi. Il numero di nodi deve essere
   strettamente positivo. Il tipo di grafo (orientato oppure non
   orientato) è specificato dal parametro `t`. */
Graph *graph_create(int n, Graph_type t);

/* Libera tutta la memoria occupata dal grafo e dalle liste di
   adiacenza */
void graph_destroy(Graph *g);

/* Restituisce il tipo di grafo */
Graph_type graph_type(const Graph *g);

/* Aggiunge un nuovo arco (src, dst) con peso "weight". Si può
   assumere che l'arco non esista già (si può omettere il controllo,
   anche se nella soluzione fornita viene fatto). Nel caso di grafo
   non orientato, occorre aggiungere l'arco sia nella lista di
   adiacenza di `src` che in quella di `dst`.

   Si presti attenzione a modificare correttamente gli array dei gradi
   entranti e uscenti, e il numero di archi. */
void graph_add_edge(Graph *g, int src, int dst, double weight);

/* Cancella l'arco (src, dst) dal grafo. Se l'arco non è presente, non
   fa nulla. Nel caso di grafo non orientato, occorre rimuovere l'arco
   sia dalla lista di adiacenza di `src` che da quella di `dst`.

   Si presti attenzione a modificare correttamente gli array dei gradi
   entranti e uscenti, e il numero di archi solo se l'arco è stato
   cancellato. */
void graph_del_edge(Graph *g, int src, int dst);

/* Restituisce un puntatore al primo arco della lista di adiacenza
   associata al nodo `v` (`NULL` se la lista è vuota) */
Edge *graph_adj(const Graph *g, int v);

/* Restituisce il numero di nodi del grafo */
int graph_n_nodes(const Graph *g);

/* Restituisce il numero di archi del grafo */
int graph_n_edges(const Graph *g);

/* Restituisce il grado uscente del nodo `v`. */
int graph_out_degree(const Graph *g, int v);

/* Restituisce il grado entrante nel nodo `v`. */
int graph_in_degree(const Graph *g, int v);

/* Stampa il grafo a video */
void graph_print(const Graph *g);

/* Crea un nuovo grafo leggendone il contenuto dal file `f`. Il file `f`
   deve essere già stato aperto in lettura. */
Graph *graph_read_from_file(FILE *f);

/* Salva il grafo `g` sul file `f`, con lo stesso formato usato dalla
   funzione `graph_read_from_file()`. Il file `f` deve essere già
   stato aperto in scrittura. */
void graph_write_to_file(FILE *f, const Graph *g);

/* Codice inerente alla struttura MinHeap */

/* Crea uno heap vuoto in grado di contenere al più `size` coppie
   (chiave, priorità); le chiavi possono essere esclusivamente gli
   interi 0 .. `size` - 1; ogni chiave può essere presente nello heap
   al più una volta. Inizialmente lo heap è vuoto.

   Precondizione: size > 0 */
MinHeap *minheap_create(int size);

void init_pos(MinHeap *h, int size);

/* Svuota lo heap */
void minheap_clear(MinHeap *h);

/* Dealloca la memoria occupata dallo heap h e dal suo contenuto */
void minheap_destroy(MinHeap *h);

/* Restituisce 1 se e solo se lo heap è vuoto */
int minheap_is_empty(const MinHeap *h);

/* Restituisce 1 se e solo se lo heap è pieno */
int minheap_is_full(const MinHeap *h);

/* Ritorna il numero di elementi effettivamente presenti nello heap */
int minheap_get_n(const MinHeap *h);

/* Restituisce la chiave associata alla minima priorità; non modifica
   lo heap */
int minheap_min(const MinHeap *h);

/* Inserisce una nuova chiave `key` con priorità `prio`.

   Precondizioni:
   - `key` deve essere una chiave valida;
   - `key` non deve essere già presente nello heap;
   - Lo heap non deve essere pieno. */
void minheap_insert(MinHeap *h, int key, double prio);

/* Rimuove dallo heap la coppia (chiave, prio) con priorità minima, e
   restituisce la chiave di tale coppia.

   Precondizione: lo heap non deve essere vuoto. */
int minheap_delete_min(MinHeap *h);

/* Modifica la priorità associata alla chiave `key`.

   Precondizione: la chiave `key` deve essere presente nello heap. */
void minheap_change_prio(MinHeap *h, int key, double new_prio);

/* Stampa il contenuto dello heap */
void minheap_print(const MinHeap *h);

Graph *graph_create( int n, Graph_type t ) {
    int i;
    Graph *g = (Graph*)malloc(sizeof(*g));
    assert(g != NULL);
    assert(n > 0);

    g->n = n;
    g->m = 0;
    g->t = t;
    g->edges = (Edge**)malloc(n * sizeof(Edge*));
    assert(g->edges != NULL);
    g->in_deg = (int*)malloc(n * sizeof(*(g->in_deg)));
    assert(g->in_deg != NULL);
    g->out_deg = (int*)malloc(n * sizeof(*(g->out_deg)));
    assert(g->out_deg != NULL);
    for (i=0; i<n; i++) {
        g->edges[i] = NULL;
        g->in_deg[i] = g->out_deg[i] = 0;
    }
    return g;
}

void graph_destroy(Graph *g) {
    int i;

    assert(g != NULL);

    for (i = 0; i < g->n; i++) {
        Edge *edge = g->edges[i];
        while (edge != NULL) {
            Edge *next = edge->next;
            free(edge);
            edge = next;
        }
        g->edges[i] = NULL;
    }
    free(g->edges);
    free(g->in_deg);
    free(g->out_deg);
    g->n = 0;
    g->edges = NULL;
    free(g);
}

Graph_type graph_type(const Graph *g) {
    return g->t;
}

Edge *create_edge(int src, int dst, double weight) {
    Edge *edge = (Edge *)malloc(sizeof(*edge));
    assert(edge != NULL);

    edge->src = src;
    edge->dst = dst;
    edge->weight = weight;

    return edge;
}

void graph_directed_add_edge(Graph *g, int src, int dst, double weight) {
    Edge *new_edge = create_edge(src, dst, weight);
    new_edge->next = g->edges[src];
    g->edges[src] = new_edge;

    g->in_deg[dst]++;
    g->out_deg[src]++;

    g->m++;
}

void graph_undirected_add_edge(Graph *g, int src, int dst, double weight) {
    Edge *new_edge = create_edge(src, dst, weight);
    new_edge->next = g->edges[src];
    g->edges[src]->next = new_edge;
    
    new_edge = create_edge(dst, src, weight);
    new_edge->next = g->edges[dst];
    g->edges[dst]->next = new_edge;

    g->in_deg[src]++;
    g->out_deg[src]++;
    g->in_deg[dst]++;
    g->out_deg[dst]++;

    g->m++;
}

void graph_add_edge(Graph *g, int src, int dst, double weight) {
    assert((src >= 0) && (src < graph_n_nodes(g)));
    assert((dst >= 0) && (dst < graph_n_nodes(g)));

    if (graph_type(g) == GRAPH_DIRECTED) {
        graph_directed_add_edge(g, src, dst, weight);
    } else {
        graph_undirected_add_edge(g, src, dst, weight);
    }
}

/* Funzione ricorsiva ausiliaria che rimuove l'arco che porta al nodo
   `dst` dalla lista di adiacenza `adj`. Se tale arco non è presente,
   non fa nulla. Ritorna la testa della lista modificata. Al termine
   pone `*deleted = 1` se l'arco è stato rimosso. */
static Edge *graph_adj_remove(Edge *adj, int dst, int *deleted) {
    /* Questo è l'algoritmo ricorsivo standard per la rimozione da una
       lista concatenata singola. */
    if (adj == NULL) { /* caso base 1: lista vuota */
        *deleted = 0;
        return adj;
    } else if (adj->dst == dst) { /* caso base 2: il nodo da cancellare è il primo della lista. */
        Edge *result = adj->next;
        free(adj);
        *deleted = 1;
        return result;
    } else { /* caso ricorsivo */
        adj->next = graph_adj_remove(adj->next, dst, deleted);
        return adj;
    }
}

void graph_del_edge(Graph *g, int src, int dst) {
    int del_srcdst, del_dstsrc;

    assert((src >= 0) && (src < graph_n_nodes(g)));
    assert((dst >= 0) && (dst < graph_n_nodes(g)));

    /* Rimuovi l'arco src -> dst. */
    g->edges[src] = graph_adj_remove(g->edges[src], dst, &del_srcdst);
    if (del_srcdst) {
        g->out_deg[src]--;
        g->in_deg[dst]--;
        g->m--;
    }
    if (g->t == GRAPH_UNDIRECTED) {
        /* Rimuovi l'arco dst -> src. */
        g->edges[dst] = graph_adj_remove(g->edges[dst], src, &del_dstsrc);
        /* L'asserzione seguente serve per assicurarsi che l'arco
           dst->src venga cancellato se e solo se src->dst lo è.
           Infatti, in un grafo non orientato ogni arco viene
           rappresentato dalla coppia src->dst e dst->src. Pertanto,
           se esiste l'arco "di andata" ma non quello "di ritorno" (o
           viceversa), il grafo non è stato costruito correttamente e
           il programma deve essere abortito. */
        assert(del_srcdst == del_dstsrc);
        if (del_dstsrc) {
            g->out_deg[dst]--;
            g->in_deg[src]--;
            /* Non bisogna decrementare g->m due volte. */
        }
    }
}

int graph_n_nodes(const Graph *g) {
    assert(g != NULL);

    return g->n;
}

int graph_n_edges(const Graph *g) {
    assert(g != NULL);

    return g->m;
}

int graph_out_degree(const Graph *g, int v) {
    assert(g != NULL);
    assert((v >= 0) && (v < graph_n_nodes(g)));
    return g->out_deg[v];
}

int graph_in_degree(const Graph *g, int v) {
    assert(g != NULL);
    assert((v >= 0) && (v < graph_n_nodes(g)));
    return g->in_deg[v];
}

Edge *graph_adj(const Graph *g, int v) {
    assert(g != NULL);
    assert((v >= 0) && (v < graph_n_nodes(g)));

    return g->edges[v];
}

void graph_print(const Graph *g) {
    int i;

    assert(g != NULL);

    if (graph_type(g) == GRAPH_UNDIRECTED) {
        printf("UNDIRECTED\n");
    } else {
        printf("DIRECTED\n");
    }

    for (i=0; i<g->n; i++) {
        const Edge *e;
        int out_deg = 0; /* ne approfittiamo per controllare la
                            correttezza dei gradi uscenti */
        printf("[%2d] -> ", i);
        for (e = graph_adj(g, i); e != NULL; e = e->next) {
            printf("(%d, %d, %f) -> ", e->src, e->dst, e->weight);
            out_deg++;
        }
        assert(out_deg == graph_out_degree(g, i));
        printf("NULL\n");
    }
}

Graph *graph_read_from_file(FILE *f) {
    int n, m, t;
    int src, dst;
    int i; /* numero archi letti dal file */
    double weight;
    Graph *g;

    assert(f != NULL);

    if (3 != fscanf(f, "%d %d %d", &n, &m, &t)) {
        fprintf(stderr, "ERRORE durante la lettura dell'intestazione del grafo\n");
        abort();
    };
    assert( n > 0 );
    assert( m >= 0 );
    assert( (t == GRAPH_UNDIRECTED) || (t == GRAPH_DIRECTED) );

    g = graph_create(n, t);
    /* Ciclo di lettura degli archi. Per rendere il programma più
       robusto, meglio non fidarsi del valore `m` nell'intestazione
       dell'input. Leggiamo informazioni sugli archi fino a quando ne
       troviamo, e poi controlliamo che il numero di archi letti (i)
       sia uguale a quello dichiarato (m) */
    i = 0;
    while (3 == fscanf(f, "%d %d %lf", &src, &dst, &weight)) {
        graph_add_edge(g, src, dst, weight);
        i++;
    }
    if (i != m) {
        fprintf(stderr, "WARNING: ho letto %d archi, ma l'intestazione ne dichiara %d\n", i, m);
    }
    /*
    fprintf(stderr, "INFO: Letto grafo %s con %d nodi e %d archi\n",
            (t == GRAPH_UNDIRECTED) ? "non orientato" : "orientato",
            n,
            m);
    */
    return g;
}

void graph_write_to_file( FILE *f, const Graph* g ) {
    int v;
    int n, m, t;

    assert(g != NULL);
    assert(f != NULL);

    n = graph_n_nodes(g);
    m = graph_n_edges(g);
    t = graph_type(g);

    fprintf(f, "%d %d %d\n", n, m, t);
    for (v=0; v<n; v++) {
        const Edge *e;
        for (e = graph_adj(g, v); e != NULL; e = e->next) {
            assert(e->src == v);
            /* Se il grafo è non orientato, dobbiamo ricordarci che
               gli archi compaiono due volte nelle liste di
               adiacenza. Nel file pero' dobbiamo riportare ogni arco
               una sola volta, dato che sarà la procedura di lettura a
               creare le liste di adiacenza in modo corretto. Quindi,
               ogni coppia di archi (u,v), (v,u) deve comparire una
               sola volta nel file. Per comodità, salviamo nel file la
               versione di ciascun arco in cui il nodo sorgente è
               minore del nodo destinazione. */
            if ((graph_type(g) == GRAPH_DIRECTED) || (e->src < e->dst)) {
                fprintf(f, "%d %d %f\n", e->src, e->dst, e->weight);
            }
        }
    }
}

void minheap_print(const MinHeap *h) {
    int i, j, width = 1;

    assert(h != NULL);

    printf("\n** Contenuto dello heap:\n\n");
    printf("n=%d size=%d\n", h->n, h->size);
    printf("Contenuto dell'array heap[] (stampato a livelli):\n");
    i = 0;
    while (i < h->n) {
        j = 0;
        while (j<width && i < h->n) {
            printf("h[%2d]=(%2d, %6.2f) ", i, h->heap[i].key, h->heap[i].prio);
            i++;
            j++;
        }
        printf("\n");
        width *= 2;
    }
    printf("\nContenuto dell'array pos[]:\n");
    for (i=0; i<h->size; i++) {
        printf("pos[%d]=%d ", i, h->pos[i]);
    }
    printf("\n\n** Fine contenuto dello heap\n\n");
}

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

/* Funzione di supporto: restituisce 1 sse l'indice `i` appartiene
   all'intervallo degli indici validi degli elementi validi nell'array
   che rappresenta lo heap. */
static int valid(const MinHeap *h, int i) {
    assert(h != NULL);

    return ((i >= 0) && (i < h->n));
}

/* Funzione di supporto: scambia heap[i] con heap[j] */
static void swap(MinHeap *h, int i, int j) {
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
static int parent(const MinHeap *h, int i) {
    assert(valid(h, i));

    return (i+1)/2 - 1;
}

/* Funzione di supporto: restituisce l'indice del figlio sinistro del
   nodo `i`. Ritorna un indice non valido se `i` non ha figlio
   sinistro. */
static int lchild(const MinHeap *h, int i) {
    assert(valid(h, i));

    return 2*i + 1;
}

/* Funzione di supporto: restituisce l'indice del figlio destro del
   nodo `i`. Ritorna un indice non valido se `i` non ha figlio
   destro. */
static int rchild(const MinHeap *h, int i) {
    assert(valid(h, i));

    return 2*i + 2;
}

/* Funzione di supporto: restituisce l'indice del figlio di `i` con
   priorità minima. Se `i` non ha figli, restituisce -1 */
static int min_child(const MinHeap *h, int i) {
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
static void move_up(MinHeap *h, int i) {
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
static void move_down(MinHeap *h, int i) {
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

/* Come minheap_min(), ma restituisce la coppia (chiave, prio); questa
   funzione verrà utilizzata in future edizioni del corso al posto di
   minheap_min(). */
HeapElem minheap_min2( const MinHeap *h) {
    assert( !minheap_is_empty(h) );

    return h->heap[0];
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

/* Come minheap_delete_min(), ma restituisce la coppia (chiave, prio);
   questa funzione verrà utilizzata al posto di minheap_delete_min()
   in future edizioni del corso. */
HeapElem minheap_delete_min2(MinHeap *h) {
    HeapElem result;

    assert( !minheap_is_empty(h) );

    result = minheap_min2(h);
    swap(h, 0, h->n-1);
    assert( h->heap[h->n - 1].key == result.key );
    h->pos[result.key] = -1;
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

int main(int argc, char **argv) {


    return EXIT_SUCCESS;
}