#include <stdio.h>
#include <stdlib.h>

typedef struct lista_nodi elem_nodi;
typedef struct lista_archi elem_archi;

/* Struttura nodo */
typedef struct nodo{
    int id;
    elem_archi* archi;
    elem_nodi* pos;
    int color;
}nodo;

/* Struttura nodo che rappresenta l'arco */
typedef struct nodo_arco{
    int id;
    nodo* from;
    nodo* to;
    elem_archi* pos;
    elem_archi* f_pos;
    elem_archi* to_pos;
}arco;

/* Lista nodi */
typedef struct lista_nodi{
    nodo* info;
    struct lista_nodi* prev;
    struct lista_nodi* next;
}elem_nodi;

/* Lista archi */
typedef struct lista_archi{
    arco* info;
    struct lista_archi* prev;
    struct lista_archi* next;
}elem_archi;

/* Struttura grafo oggetti */
typedef struct grafo_oggetti{
    int numero_nodi;
    int numero_archi;
    elem_nodi* nodi;
    elem_archi* archi;
}go;

/* Funzione che crea un nuovo grafo */
go* new_grafo(){

    go* nuovo_grafo = (go*)malloc(sizeof(go));
    nuovo_grafo->numero_nodi = 0;
    nuovo_grafo->numero_archi = 0;
    nuovo_grafo->nodi = NULL;
    nuovo_grafo->archi = NULL;

    return nuovo_grafo;
}

/* Funzione aggiungi nodo al grafo di valore 'value' */
nodo* aggiungi_nodo(go* g, int value){

    nodo* new_nodo = (nodo*)malloc(sizeof(nodo));
    new_nodo->archi = NULL; // nessun arco32
    new_nodo->id = value;
    new_nodo->color = 0;

    elem_nodi* lista_nodi = (elem_nodi*)malloc(sizeof(elem_nodi));
    lista_nodi->info = new_nodo;    // adesso punta al nuovo nodo creato
    lista_nodi->prev = NULL;    // è il primo
    lista_nodi->next = g->nodi;

    if(g->nodi!=NULL){
        g->nodi->prev = lista_nodi;
    }

    g->nodi = lista_nodi;
    g->numero_nodi++;

    return new_nodo;
}

/* Funzione che aggiunge arco */
void aggiungi_arco(go* g){
    
}


/* Funzione stampa grafo */
void print_grafo(go* g){
    printf("\n===== STAMPA GRAFO =====\n");
    printf("----- Il grafo ha %d nodi.\n", g->numero_nodi);
    printf("----- Il grafo ha %d archi.\n", g->numero_archi);

    elem_nodi* n = g->nodi;
    while(n!=NULL){
        printf("\nNodo trovato: %d.\n", n->info->id);
        printf("\n      colore: %d.\n", n->info->color);

        n = n->next;
    }

    elem_archi* a = g->archi;
    while(a!=NULL){
        printf("\nArco trovato: %d.\n", a->info->id);
        printf("\n     da nodo: [%d].\n", a->info->from->id);
        printf("\n      a nodo: [%d].\n", a->info->to->id);

        a = a->next;
    }
}


int main(){

    go* grafo_oggetti_1 = new_grafo();

    nodo* nodo_1 = aggiungi_nodo(grafo_oggetti_1, 2);
    nodo* nodo_2 = aggiungi_nodo(grafo_oggetti_1, 3);
    nodo* nodo_3 = aggiungi_nodo(grafo_oggetti_1, 4);
    nodo* nodo_4 = aggiungi_nodo(grafo_oggetti_1, 5);

    arco* arco_1 = aggiungi_arco(grafo_oggetti_1, 5, nodo_1, nodo_2);

    print_grafo(grafo_oggetti_1);
}

