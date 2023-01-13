#include <stdio.h>
#include <stdlib.h>

/* Struttura nodo albero */
typedef struct nodo{
    struct nodo* p;
    struct nodo* l;
    struct nodo* r;
    int info;
}nodo;
typedef nodo* albero;


/* Funzione aggiungi radice */
void add_root(albero* t, int v){
    if(*t!=NULL){
        printf("\nInserimento radice fallito. Radice gia' esistente\n");
        return;
    }
    nodo* root = (nodo*)malloc(sizeof(nodo));
    root->p = NULL;
    root->l = NULL;
    root->r = NULL;
    root->info = v;
    (*t) = root;
}

albero add_left(albero t, int v){
    if(t->l!=NULL){
        printf("\nNodo a sinistra gia' esistente.\n");
    }
    t->l = (nodo*)malloc(sizeof(nodo));
    t->l->p = t;
    t->l->l = NULL;
    t->l->r = NULL,
    t->l->info = v;

    return t->l;
}

albero add_right(albero t, int v){
    if(t->r!=NULL){
        printf("\nNodo a destra gia' esistente.\n");
    }
    t->r = (nodo*)malloc(sizeof(nodo));
    t->r->p = t;
    t->r->l = NULL;
    t->r->r = NULL;
    t->l->info = v;

    return t->r;
}

int is_empty(nodo* t){
    return t==NULL;
}

/* PREORDINE */
/* Funzione che cerca nell'albero se esiste un nodo con valore 'n', ritorna TRUE, FALSE altrimenti */
/* VERSIONE PROFESSORE */
nodo* search_pre(nodo* t, int n){
    if(t==NULL)
        return NULL;

    if(t->info==n)   
        return t;

    nodo* l = search_pre(t->l, n);
    if(l!=NULL){
        return l;
    }
    return search_pre(t->r, n);
}

int main(){

    albero t1 = NULL;

    /* Is empty */
    printf("\nis empty: %d.\n", is_empty(t1)); // atteso 1

    /* Aggiungi radice */
    add_root(&t1, 1);

    /* Aggiungi nodo a sinistra */
    nodo* l = add_left(t1, 2);
    /* Aggiungi nodo a destra */
    nodo* r = add_right(t1, 3);

    /* Is empty */
    printf("\nis empty: %d.\n", is_empty(t1));  // atteso 0

    /* Search pre */
    printf("\nNodo con valore 4 trovato ris: %d.\n", search_pre(t1, 4)!=NULL);    // atteso: 0
    printf("\nNodo con valore 2 trovato ris: %d.\n", search_pre(t1, 2)!=NULL);    // atteso: 1
}