#include <stdio.h>
#include <stdlib.h>

/* Sono strutture dati utilizzate per implementare dizionari, cioè coppie <chiave, valore>
 * nel caso in cui sulle chiavi (uniche) sia definita una relazione d'ordine totale.
 * Per ogni nodo x dell’albero:
 * Consultazione di un abr: Ricerca di un valore, calcolo del valore max o min
 * Creazione e manutenzione di un abr: inserimento e cancellazione di nodi
 * tutti i nodi del sottoalbero sinistro di x hanno chiave minore di quella di x
 * tutti i nodi del sottoalbero destro di x hanno chiave maggiore di quella di x 
 * In un abr:
 * Il ramo più a sinistra termina con il valore minimo. Il nodo minimo non ha figlio sinistro. 
 * Il ramo più a destra termina con il valore massimo. Il nodo massimo non ha figlio destro. */

/* Struttura nodo albero binario di ricerca */
typedef struct abr{
    struct abr* parent;
    int key;
    struct abr* left;
    struct abr* right; 
}nodo;

/* ============================================================= VERSIONE SLIDE ============================================================= */

/* Funzione che crea un nuovo nodo */
nodo* new_tree_element(int k){
    nodo* out = (nodo*)malloc(sizeof(nodo));
    out->parent = NULL;
    out->key = k;
    out->left = NULL;
    out->right = NULL;

    return out;
}

/* Funzione che inserisce un nodo sotto al sottoalbero radicato a sx o dx */
void bst_insert(nodo* pt, int k){
    /* Verifica le condizioni di inserimento: 
     * - Se l'oggetto da inserire è uguale al nodo corrente: rifiuta inserimento
     * - Se l'oggetto da inserire è < del nodo corrente: sottoalbero sinistro
     * - Altrimenti - Se l'oggetto da inserire è > del nodo corrente: sottoalbero destro */
    nodo* nuovoNodo = new_tree_element(k);
    
    /* Oggetto uguale a nodo corrente */
    if(pt->key == k){
        printf("\nInserimento fallito.\n");
        return;
    }
    /* Oggetto < nodo corrente */
    if(pt->key > k){
        /* Nodo ci sono nodi a sinistra */
        if(pt->left==NULL){
            nuovoNodo->parent = pt;
            pt->left = nuovoNodo;
            printf("\nInserimento sottoalbero sinistro.\n");
        }   // Altrimenti ci sono nodi a sinistra aggiungilo come figlio del nodo a sinistra già esistente
        else
            bst_insert(pt->left, k);
    }   // Altrimenti
    else if(pt->key < k){ // se oggetto > nodo corrente
        if(pt->right==NULL){
            nuovoNodo->parent = pt;
            pt->right = nuovoNodo;
            printf("\nInserimento sottoalbero destro.\n");
        }   // Altrimenti ci sono nodi a destra aggiungilo come figlio del nodo a destra già esistente
        else
            bst_insert(pt->right, k);
    }
}

/* Se l'abr è vuoto: Funzione che inserisce un nuovo nodo nell'abr */
void tree_insert(nodo** pt, int k){
    /* Se l'albero è vuoto */
    if((*pt)==NULL){
        (*pt) = new_tree_element(k);    // Inserisci il primo nodo come radice
        return;
    }
    else{   // Altrimenti è già presente un nodo
        bst_insert((*pt), k);
        return;
    }
}

/* ========================================================================================================================================== */

void parentetica_simmetrica(nodo* a) {

   if( a == NULL ) {
      printf("()");
      return;
   }

   printf("(");
   parentetica_simmetrica(a->left);
   printf("%d",a->key);
   parentetica_simmetrica(a->right);
   printf(")");
}

int main(){

    nodo* abr = NULL;

    tree_insert(&abr, 10);
    //tree_insert(&abr, 1);    // Debug di correzione. Stampa: Inserimento non valido.  - Corretto -

    tree_insert(&abr, 3);    // sx
    tree_insert(&abr, 5);    // sx
    tree_insert(&abr, 11);   // dx
    tree_insert(&abr, 12);   // dx
    tree_insert(&abr, 4);    // sx

    parentetica_simmetrica(abr);
    
}