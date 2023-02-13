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

typedef struct arco_grafo{
    int id;
    nodo* from;
    nodo* to;
    elem_archi* pos;
    elem_archi* from_pos;
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

/* Struttura grafo */
typedef struct grafo_oggetti{

    int numero_nodi;
    int numero_archi;
    elem_nodi* nodi;
    elem_archi* archi;
}go;

go* new_grafo(){

    go* nuovo = (go*)malloc(sizeof(go));
    nuovo->numero_archi = 0;
    nuovo->numero_nodi = 0;
    nuovo->archi = NULL;
    nuovo->nodi = NULL;

    return nuovo;
}

nodo* aggiungi_nodo(go* g, int value){

    nodo* nuovo = (nodo*)malloc(sizeof(nodo));
    nuovo->id = value;
    nuovo->archi = NULL;
    nuovo->color = 0;
    
    elem_nodi* ln = (elem_nodi*)malloc(sizeof(elem_nodi));
    ln->info = nuovo;
    ln->prev = NULL;
    ln->next = g->nodi;

    if(g->nodi!=NULL){
        g->nodi->prev = ln;
    }

    g->nodi = ln;
    g->numero_nodi++;

    return nuovo;
}

arco* aggiungi_arco(go* g, int id, nodo* from, nodo* to){

    arco* a = (arco*)malloc(sizeof(arco));
    a->id = id;
    a->from = from;
    a->to= to;

    // Aggiungo arco nella lista del grafo
    elem_archi* la = (elem_archi*)malloc(sizeof(elem_archi));
    la->prev = NULL;
    la->info = a;
    la->next = g->archi;

    if(g->archi!=NULL){ // c'èra già un arco
        g->archi->prev = la;
    }
    g->archi = la;
    g->numero_archi++;

    // from
    elem_archi* la_from = (elem_archi*)malloc(sizeof(elem_archi));
    la_from->info = a;
    la_from->prev = NULL;
    la_from->next = from->archi;

    if(from->archi!=NULL){
        from->archi->prev = la_from;
    }

    from->archi = la_from;
    a->from_pos = la_from;

    // to
    elem_archi* la_to = (elem_archi*)malloc(sizeof(elem_archi));
    la_to->info = a;
    la_to->prev = NULL;
    la_to->next = to->archi;

    if(to->archi!=NULL){
        to->archi->prev = la_to;
    }
    
    to->archi = la_to;
    a->to_pos = la_to;

    return a;
}
void rimuovi_arco(go* g, arco* a);

// Rimuovi nodo
void rimuovi_nodo(go* g, nodo* n){

    // rimuovi tutti gli archi dal nodo
    elem_archi* archi_da_cancellare = n->archi;
    while(archi_da_cancellare!=NULL){
        elem_archi* prossimo_arco = archi_da_cancellare->next;
        rimuovi_arco(g, archi_da_cancellare->info);
        archi_da_cancellare = prossimo_arco;
    }
    // non ci sono archi
    if(n->pos->next!=NULL){
        n->pos->next->prev = n->pos->prev;
    }else{
        g->nodi = n->pos->next;
    }
    free(n->pos);
    free(n);

    g->numero_nodi--;

}

void rimuovi_arco(go* g, arco* a){
    
    // rimuovi arco dalla lista degli archi del grafo
    if(a->pos->next!=NULL){
        
    }
}

void stampa(go* g){

    printf("\n==== STAMPA GRAFO ====\n");
    printf("Nodi trovati: %d.\n");
    printf("Archi trovati: %d.\n");

    elem_nodi* ln = g->nodi;
    while(ln!=NULL){
        printf("\nNodo trovato: [%d]", ln->info->id);
        printf("\n      colore: %d.\n", ln->info->color);
        ln = ln->next;
    }
    elem_archi* la = g->archi;
    while(la!=NULL){
        printf("\nArco trovato con id: %d.\n", la->info->id);
        printf("\n Dal nodo %d\n", la->info->from->id);
        printf("\n       al %d.\n", la->info->to->id);

        la = la->next;
    }
}

int main(){

    go* grafo_1 = new_grafo();

    nodo* nodo_1 = aggiungi_nodo(grafo_1, 3);

    arco* a_1 = aggiungi_arco(grafo_1, 1, nodo_1, nodo_1);

    stampa(grafo_1);
}