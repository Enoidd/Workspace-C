#include <stdio.h>
#include <stdlib.h>

/* Per ogni nodo x dell’albero: 
 * tutti i nodi del sottoalbero sinistro di x hanno chiave minore di quella di x
 * tutti i nodi del sottoalbero destro di x hanno chiave maggiore di quella di x 
 * In un abr:
 * Il ramo più a sinistra termina con il valore minimo. Il nodo minimo non ha figlio sinistro. 
 * Il ramo più a destra termina con il valore massimo. Il nodo massimo non ha figlio destro. */

/* Struttura nodo albero binario di ricerca */
typedef struct abr{
    struct nodo* parent;
    int key;
    struct nodo* left;
    struct nodo* right; 
}nodo;

/* Funzione che crea un nuovo nodo */
nodo* new_tree_element(int k){
    nodo* x = (nodo*)malloc(sizeof(nodo)); // 'x' è un oggetto 'abr'
    x->parent = NULL;
    x->left = NULL;
    x->right = NULL;
    x->key = k;

    return x;
}

/* Funzione che inserisce un nuovo nodo nell'abr */
int bst_insert(nodo** pt, int k){
    int out = 0;    // per verificare se il nodo è stato inserito
    /* Se 'k' è minore del valore del suo genitore */
    if(k < pt->key){
        /* Inserisci il nodo a sinistra */
        pt->left = new_tree_element(k); // inseriscilo
        
    }
}

/* Funzione che aggiunge un nuovo nodo all'abr, se il nodo gia' esiste non viene aggiunto e la funzione ritorna false (0),
 * altrimenti ritorna true (1) */
int tree_insert(nodo* pt, int k){
    /* Se l'albero è vuoto */
    if((*pt)==NULL){
        (*pt) = new_tree_element(k);    // inserisco il primo nodo come radice
        return 1;
    }   // Altrimenti albero non vuoto
    return bst_insert(&(*pt), k);
}

int main(){

}