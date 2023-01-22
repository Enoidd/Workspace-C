#include <stdio.h>
#include <stdlib.h>

// Forward declaration
typedef struct elem_lista_archi elem_archi;
typedef struct elem_lista_nodi elem_nodi;


typedef struct struct_nodo{ // Struttura nodo del grafo
    int id;
    elem_archi* archi;  // puntatore ad una lista di archi
    elem_nodi* pos; // puntatore ad una lista dei nodi del grafo
}nodo;

typedef struct struct_arco{ // Struttura nodo arco
    int id;
    nodo* from; // l'arco arriva dal nodo from
    nodo* to;   // l'arco va al nodo to
    elem_archi* pos;    // posizione nella lista degli archi
    elem_archi* from_pos;   // posizione nella lista degli archi del nodo from
    elem_archi* to_pos; // posizione nella lista degli archi del nodo to
}arco;

typedef struct elem_lista_nodi{ // struttura lista nodi
    nodo* info; // puntatore al nodo
    struct elem_lista_nodi* prev;
    struct elem_lista_nodi* next;
}elem_nodi;

typedef struct elem_lista_archi{    // struttura lista archi
    arco* info; // puntatore al nodo
    struct elem_lista_archi* prev;
    struct elem_lista_archi* next;
}elem_archi;


typedef struct go{  // Struttura grafo oggetti
    int numero_archi;
    int numero_nodi;
    elem_nodi* nodi;
    elem_archi* archi;
}grafo_oggetti;


grafo_oggetti* new_grafo(){
    grafo_oggetti* out = (grafo_oggetti*)malloc(sizeof(grafo_oggetti));
    out->numero_nodi = 0;
    out->numero_archi = 0;

    out->nodi = NULL;
    out->archi = NULL;
    
    return out;
}

nodo* aggiungi_nodo(grafo_oggetti* go, int id){
    nodo* nuovo_nodo = (nodo*)malloc(sizeof(nodo));
    nuovo_nodo->id = id;
    nuovo_nodo->archi = NULL;

    elem_nodi* lista_nodi = (elem_nodi*)malloc(sizeof(elem_nodi));
    lista_nodi->info = nuovo_nodo;
    lista_nodi->prev = NULL;
    lista_nodi->next = go->nodi;

    if(go->nodi!=NULL){
        go->nodi->prev = lista_nodi;
    }
    go->nodi = lista_nodi;
    go->numero_nodi++;

    nuovo_nodo->pos = lista_nodi;
}

arco* aggiungi_arco(grafo_oggetti* go, int id, nodo* from, nodo* to){
    arco* nuovo_arco = (arco*)malloc(sizeof(arco));
    nuovo_arco->id = id;
    nuovo_arco->from = from;
    nuovo_arco->to = to;

    elem_archi* lista_archi = (elem_archi*)malloc(sizeof(elem_archi));
    lista_archi->info = nuovo_arco;
    lista_archi->prev = NULL;
    lista_archi->next = go->archi;

    if(go->archi!=NULL){
        go->archi->prev = lista_archi;
    }

    go->archi = lista_archi;
    go->numero_archi++;
    nuovo_arco->pos = lista_archi;
}

void stamp_grafo(grafo_oggetti* go){
    printf("\n===== STAMPO GRAFO =====.\n");
    printf("\nIl grafo ha %d nodi.\n", go->numero_nodi);
    printf("\nIl grafo ha %d archi.\n", go->numero_archi);

    /* per scorrere la lista dei nodi */
    elem_nodi* lista_nodi = go->nodi;
    while(lista_nodi!=NULL){
        printf("\nNodo trovato: %d.\n", lista_nodi->info->id);
        lista_nodi = lista_nodi->next;
    }
    /* per scorrere la lista di archi */
    elem_archi* lista_archi = go->archi;
    while(lista_archi!=NULL){
        printf("\nArco da nodo %d a nodo %d.\n", lista_archi->info->from->id, lista_archi->info->to->id);
        lista_archi = lista_archi->next;
    }

}

void rimuovi_arco(grafo_oggetti* go, arco* arco_da_rimuovere){
    
    if(arco_da_rimuovere->pos->next!=NULL){
        arco_da_rimuovere->pos->next->prev = 
    }
}

int main(){

    grafo_oggetti* go = new_grafo();

    nodo* n1 = aggiungi_nodo(go, 2);
    nodo* n2 = aggiungi_nodo(go, 3);

    stamp_grafo(go);

    arco* a1 = aggiungi_arco(go, 1, n1, n2);
    arco* a2 = aggiungi_arco(go, 2, n2, n1);

    stamp_grafo(go);
}