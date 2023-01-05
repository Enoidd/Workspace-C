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

/* Funzione che calcola il valore minimo contenuto nell'abr */
int tree_minimum(nodo* pt){
    if(pt==NULL){
        return 0;
    }
    while(pt->left!=NULL){
        pt = pt->left;
    }
    return pt->key;
}

/* Funzione che calcola il valore massimo contenuto nell'abr */
int tree_maximum(nodo* pt){
    if(pt==NULL){
        return 0;
    }
    while(pt->right!=NULL){
        pt = pt->right;
    }
    return pt->key;
}

/* Funzione che cancella un nodo dall'abr */

// Forward declaration
void tree_bypass(nodo** t, nodo* x);

void tree_delete(nodo* t, nodo* x){ // 'x' è il nodo che si vuole cancellare
    
    /* Metti in 'y' il minimo trovato a destra */
    nodo* y = (nodo*)malloc(sizeof(nodo));
    /* Se il nodo da cancellare (x) ha entrambi i figli */
    if(x->left!=NULL && x->right!=NULL){
        y = tree_minimum(x->right);
        x->key =y->key; // memorizza anche il valore
    }
    else    // Altrimenti non ha entrambi i figli
        y = x;
    tree_bypass(&t, y);
}

void tree_bypass(nodo** t, nodo* x){    // Complessità Theta(1)
    /* Il nodo 'x' ha un nodo figlio a sinistra */
    nodo* figlio = (nodo*)malloc(sizeof(nodo));
    if(x->left!=NULL){
        figlio = x->left;   // il figlio del nodo da cancellare è a sinistra
    }
    else    // Altrimenti il figlio del nodo da cancellare è a destra
        figlio = x->right;
    /* Il figlio è != NULL */
    if(figlio!=NULL)
        figlio->parent = x->parent; // il parent del figlio diventa il parent del nodo da cancellare, cioè il parent del figlio non è il genitore ma il nonno
    /* Se il parent è != NULL */
    if(figlio->parent!=NULL){
        /* Il nodo da cancellare è un figlio a sinistra */
        if(x == x->parent->left)
            x->parent->left = figlio;   // il campo left del nonno punta al nuovo nodo (salta quello cancellato)
        else    // il nodo da cancellare è un figlio a destra
            x->parent->right = figlio;
    }
    else    // Altrimenti il nodo figlio non ha parent, dunque è la radice
        (*t) = figlio;
}

/* Funzione che ricerca un nodo con chiave k - ITERATIVA */
nodo* iterative_tree_search(nodo* pt, int k){

    while(pt!=NULL && k!=pt->key){
        /* chiave minore della key corrente */
        if(pt->key > k)
            pt = pt->left;
        else
            pt = pt->right;
    }
    return pt;  // ritorna il riferimento al nodo
}

/* Funzione che ricerca un nodo con chiave k - RICORSIVA */
nodo* recursive_tree_search(nodo* pt, int k){
    if(pt==NULL)
        return NULL;
    if(pt->key==k)
        return pt;
    if(pt->key > k)
        return recursive_tree_search(pt->left, k);
    else
        return recursive_tree_search(pt->right, k);
}

/* =========== Funzione che verifica se un albero è un abr =========== */

/* NB. E'un abr se questo produce tutti elementi in ordine crescente. */
int conta_nodi_albero(nodo* pt){
    if(pt==NULL) return 0;
    /* Contatore nodi sotto albero radicato a sinistra */
    int l = conta_nodi_albero(pt->left);
    int r = conta_nodi_albero(pt->right);

    return 1 + l + r;
}

int tree_to_array(int* A, nodo* pt, int i){
    if(pt!=NULL){
        i = tree_to_array(A, pt->left, i);
        A[i] = pt->key;
        i = tree_to_array(A, pt->right, i+1);
    }
    return i;   // 'i' è la prossima posizione libera nell'array 'A'
}


int is_sorted(nodo* pt, int* A){ // Theta(n)
    int numNodi = conta_nodi_albero(pt);
    for(int i=0; i<numNodi-1; i++) {
        for(int j=i+1; j<numNodi; j++) {
            if(A[i]>A[j])
                return 0;
        }
    }
    return 1;
}

/* Funzione che visita l'albero e crea l'array, verifica se questo è un abr */
int abr_sym(nodo* pt){ // Theta(n)
    int count = conta_nodi_albero(pt);
    //int* A[count];
    int* A = malloc(conta_nodi_albero(pt)*sizeof(int));

    tree_to_array(A, pt, 0);    // Riverso l'albero nell'array 'A'

    printf("\nArray:\n");
    for(int i=0; i<count; i++){
        printf("[%d]", A[i]);
    }
    printf("\n");

    return is_sorted(pt, A);
}


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

/* Funzione che verifica se un albero è un abr con visita in preordine */


/* Funzione che verifica se un albero è un abr con visita in postordine */

int main(){

    nodo* abr = NULL;

    tree_insert(&abr, 10);
    //tree_insert(&abr, 1);    // Debug di correzione. Stampa: Inserimento non valido.  - Corretto -

    tree_insert(&abr, 29);
    tree_insert(&abr, 16);
    tree_insert(&abr, 7);
    tree_insert(&abr, 45);

    parentetica_simmetrica(abr);

    /* Tree_minimum */
    printf("\nTree_minimum: %d.\n", tree_minimum(abr)); // Atteso 3
    
    /* Tree_maximum */
    printf("\nTree_maximum: %d.\n", tree_maximum(abr)); // ATteso 12

    /* Iterative_tree_search */
    if(iterative_tree_search(abr, 12)!=NULL)
        printf("\nIterative_tree_search: trovato.\n");
    else
        printf("\nIterative_tree_search: non trovato.\n");

    /* Recursive_tree_search */
    if(recursive_tree_search(abr, 12)!=NULL)
        printf("\nRecursive_tree_search: trovato.\n");
    else
        printf("\nRecursive_tree_search: non trovato.\n");

    /* Verifica se un albero è un abr */
    /* NB. Un albero se lo si trasforma in un array, se l'array ha tutti elementi posti in ordine crescente allora l'albero è un abr, no altrimenti */
    if(abr_sym(abr))
        printf("\nE' un abr.\n");
    else
        printf("\nNon e' un abr.\n");
}