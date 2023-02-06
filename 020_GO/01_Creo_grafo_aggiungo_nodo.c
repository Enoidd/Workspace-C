#include <stdio.h>
#include <stdlib.h>

typedef struct lista_nodi elem_nodi;

typedef struct lista_archi elem_archi;

/* Struttura nodo */
typedef struct nodo{
    int id;
    elem_archi* archi;
    elem_nodi* nodi;
    int color;
}nodo;

/* Struttura nodo arco */
typedef struct arco{
    int id;
    nodo* from;
    nodo* to;
    elem_archi* pos;
    elem_archi* from_pos;
    elem_archi* to_pos;
}arco;

/* Struttura lista archi */
typedef struct lista_nodi{
    nodo* info;
    struct lista_nodi* prev;
    struct lista_nodi* next;
}elem_nodi;

/* Struttura lista nodi */
typedef struct lista_archi{
    arco* info;
    struct lista_archi* prev;
    struct lista_archi* next;
}elem_archi;

/* Struttura grafo oggetti */
typedef struct grafo_oggetti{
    int numero_nodi;    // numero nodi del grafo
    int numero_archi;   // numero archi del grafo
    elem_nodi* nodi;
    elem_archi* archi;
}go;

/* Costruisce un grafo oggetti */
go* new_go(){
    go* nuovo_go = (go*)malloc(sizeof(go));
    nuovo_go->numero_nodi = 0;
    nuovo_go->numero_archi = 0;
    nuovo_go->nodi = NULL;
    nuovo_go->archi = NULL;

    return nuovo_go;
}

/* Aggiungo un nodo */
nodo* nuovo_nodo(go* g_oggetti, int id){

    nodo* new_nodo = (nodo*)malloc(sizeof(nodo));   // creo un nodo
    new_nodo->archi = NULL; // il nuovo nodo non ha archi
    new_nodo->id = id;
    new_nodo->color = 0;

    elem_nodi* lista_nodi = (elem_nodi*)malloc(sizeof(elem_nodi));  // creo l'elemento lista nodi che collego al nuovo nodo creato
    lista_nodi->info = new_nodo;
    lista_nodi->prev = NULL;    // lo metto in testa
    lista_nodi->next = g_oggetti->nodi;

    if(g_oggetti->nodi!=NULL){
        g_oggetti->nodi->prev = lista_nodi;
    }
    g_oggetti->nodi = lista_nodi;
    g_oggetti->numero_nodi++;

    return new_nodo;
}

/* Funzione che stampa il grafo oggetti */
void print_go(go* grafo_oggetti){
    printf("\n===== STAMPO GRAFO =====\n");
    printf("----- Il grafo ha %d nodi.\n", grafo_oggetti->numero_nodi);
    printf("----- Il grafo ha %d archi.\n\n", grafo_oggetti->numero_archi);

    elem_nodi* scorri_nodi = grafo_oggetti->nodi;
    while(scorri_nodi!=NULL){
        printf("Nodo trovato: [%d]\n", scorri_nodi->info->id);
        printf("      colore: %d\n", grafo_oggetti->nodi->info->color);
        scorri_nodi = scorri_nodi->next;
    }
}

int main(){

    go* grafo_oggetti_1 = new_go(); // creo un grafo oggetti chiamato 'grafo_oggetti_1'

    nodo* nodo_1 = nuovo_nodo(grafo_oggetti_1, 2);
    nodo* nodo_2 = nuovo_nodo(grafo_oggetti_1, 3);
    nodo* nodo_3 = nuovo_nodo(grafo_oggetti_1, 4);
    nodo* nodo_4 = nuovo_nodo(grafo_oggetti_1, 6);

    print_go(grafo_oggetti_1);  
}