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
    if(t->l!=NULL)
        
}


int main(){

    albero t1 = NULL;

    /* Aggiungi radice */
    add_root(&t1, 1);
}