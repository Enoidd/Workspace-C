#include <stdio.h>
#include <stdlib.h>

/* Struttura nodo albero */
typedef struct nodo{
    struct nodo* parent;
    struct nodo* left;
    struct nodo* right;
    int info;
}nodo;

typedef nodo* albero;   // albero è un puntatore a nodo

/* Funzione che crea un nodo */
nodo* new_node(int v){
    nodo* n = (nodo*)malloc(sizeof(nodo));
    n->parent = NULL;
    n->left = NULL;
    n->right = NULL;
    n->info = v;
}

/* Funzione che aggiunge il nodo radice all'albero binario */
void add_root(nodo** root, int v){
    /* Esiste gia' una radice */
    if(*root==NULL)
}

int main(){
    
    albero t1 = NULL;
    /*
        struct nodo* t1 = NULL;
        nodo* t1 = NULL;
        albero t1 = NULL;
    */
}