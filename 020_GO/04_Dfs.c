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

/* Struttura nodo arco */
typedef struct nodo_arco{
    int id;
    nodo* from;
    nodo* to;
    elem_archi* pos;
    elem_archi* f_pos;
    elem_archi* t_pos;
}arco;

/* Struttura lista nodo */
typedef struct lista_nodi{
    nodo* info;
    struct lista_nodi* prev;
    struct lista_nodi* next;
}elem_nodi;

/* Struttura lista arco */
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

/* Costruttore grafo */
go* new_grafo(){
    go* nuovo_grafo = (go*)malloc(sizeof(go));

    nuovo_grafo->numero_nodi = 0;
    nuovo_grafo->numero_archi = 0;
    nuovo_grafo->nodi = NULL;
    nuovo_grafo->archi = NULL;

    return nuovo_grafo;
}

/* Aggiungi un nodo al grafo */
nodo* add_nodo(go* g, int value){
    nodo* new_nodo = (nodo*)malloc(sizeof(nodo));
    new_nodo->archi = NULL;
    new_nodo->id = value;
    new_nodo->color = 0;

    elem_nodi* ln = (elem_nodi*)malloc(sizeof(elem_nodi));
    ln->info = new_nodo;
    ln->prev = NULL;
    ln->next = g->nodi;

    if(g->nodi!=NULL){
        g->nodi->prev = ln;
    }

    g->nodi = ln;
    g->numero_nodi++;

    return new_nodo;
}

/* Aggiungi arco */
arco* add_arco(go* g, int id, nodo* from, nodo* to){

    arco* nuovo_arco = (arco*)malloc(sizeof(arco));
    nuovo_arco->id = id;
    nuovo_arco->from = from;
    nuovo_arco->to = to;

    // Aggiungo lista archi grafo
    elem_archi* lista_archi = (elem_archi*)malloc(sizeof(elem_archi));
    lista_archi->info = nuovo_arco;
    lista_archi->prev = NULL;
    lista_archi->next = g->archi;

    /* c'èra già un arco */
    if(g->archi!=NULL){ 
        g->archi->prev = lista_archi;
    }
    g->archi = lista_archi;
    g->numero_archi++;
    nuovo_arco->pos = g->archi;

    // From
    elem_archi* l_from = (elem_archi*)malloc(sizeof(elem_archi));
    l_from->info = nuovo_arco;
    l_from->prev = NULL;
    l_from->next = from->archi;

    if(from->archi!=NULL){
        from->archi->prev = l_from;
    }
    from->archi = l_from;
    nuovo_arco->f_pos = l_from;

    // To
    elem_archi* la_to = (elem_archi*)malloc(sizeof(elem_archi));
    la_to->info = nuovo_arco;
    la_to->prev = NULL;
    la_to->next = to->archi;

    if(to->archi!=NULL){
        to->archi->prev = la_to;
    }
    to->archi = la_to;
    nuovo_arco->t_pos = la_to;

    return nuovo_arco;
}

void stampa(go* g){

    printf("\n==== STAMPA GRAFO ====\n");
    printf("Nodi trovati: %d.\n", g->numero_nodi);
    printf("Archi trovati: %d.\n", g->numero_archi);

    elem_nodi* ln = g->nodi;
    while(ln!=NULL){
        printf("\nNodo trovato: [%d]", ln->info->id);
        printf("\n      colore: %d.\n", ln->info->color);
        ln = ln->next;
    }

    elem_archi* la = g->archi;
    while(la!=NULL){
        printf("\nArco trovato con id: %d", la->info->id);
        printf("\n          dal nodo [%d]", la->info->from->id);
        printf("\n           al nodo [%d].\n", la->info->to->id);

        la = la->next;
    }
}

/* Funzione che fa una visità in profondità a partire dal nodo 'n' per grafi non connessi */
void dfs_ricorsiva(nodo* n){
    
}

int main(){

    go* grafo_1 = new_grafo();

    nodo* nodo_1 = add_nodo(grafo_1, 2);
    nodo* nodo_2 = add_nodo(grafo_1, 3);
    nodo* nodo_3 = add_nodo(grafo_1, 5);
    nodo* nodo_4 = add_nodo(grafo_1, 7);

    arco* a_1 = add_arco(grafo_1, 3, nodo_1, nodo_2);

    stampa(grafo_1);


}