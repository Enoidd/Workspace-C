#include <stdio.h>
#include <stdlib.h>

/* Struttura nodo albero */
typedef struct na{
	struct na* parent;
	struct na* left;
	struct na* right;
	int info;
}nodo;
typedef nodo* albero;

/*	Funzione che crea un nuovo albero */
albero newTree(){
	albero new = (albero)malloc(sizeof(albero));	// alloca memoria per un nuovo albero
	return new;
}

/* Funzione che verifica se l'albero è vuoto */
int is_empty(albero t){
	return t==NULL;
}

/* Funzione che aggiunge la radice all'albero di valore 'v' */
void add_root(nodo** punta_albero, int v){
	/* Se l'albro ha già la radice */
	if(*punta_albero!=NULL)
		printf("\nError. Radice gia' esistente.\n");
	// Altrimenti radice non esistente
	nodo* root = malloc(sizeof(nodo));	// allocazione memoria per il nuovo nodo che rappresenta la radice dell'albero
	root->parent = NULL;	// la radice non ha parent
	root->left = NULL;		// la radice inizialmente non ha nodi figli a sinistra
	root->right = NULL;		// la radice inizialmente non ha nodi figli a destra
	root->info = v;			// inizializzazione valore radice a 'v'
	(*punta_albero) = root;	// aggiorna la radice dell'albero con la nuova radice
}

/* Funzione che inserisce un nodo "figlio" a sinistra */
nodo* add_left(albero t, int x){
	/* Se il nodo è gia' esistente */
	if(t->left!=NULL)
		printf("\nError overflow, add_left fallito.\n");
	// Altrimenti 
	t->left = malloc(sizeof(nodo));	// allocazione memoria per il nuovo nodo a sinistra
	t->left->parent = t;	// il nuovo nodo ha come parent il vecchio nodo 't'
	t->left->left = NULL;	// inizialmente il nuovo nodo non ha nodi figli a sinistra
	t->left->right = NULL;	// inizialmente il nuovo nodo non ha nodi figli a destra
	t->left->info = x;	// inizializzazione valore nuovo nodo creato
	
	return t->left;
}

/* Funzione che inserisci un nodo "figlio" a destra */
nodo* add_right(albero t, int x){
	/* Se il nodo è gia' esistente */
	if(t->right!=NULL)
		printf("\nError overflow, add_right fallito.\n");
	// Altrimenti
	t->right = malloc(sizeof(nodo));	// allocazione memoria per il nuovo nodo a destra
	t->right->parent = t;	// il nuovo nodo ha come parent il vecchio nodo 't'
	t->right->left = NULL;	// inizialmente il nuovo nodo non ha nodi figli a sinistra
	t->right->right = NULL;	// inizialmente il nuovo nodo non ha nodi figli a destra
	t->right->info = x;	// inizializzazione valore nuovo nodo creato
	
	return t->right;
}

/* ====================================================================================================================== */

// DA QUI ESERCIZI

/* PREORDINE */
/* Funzione che cerca nell'albero se esiste un nodo con valore 'n', ritorna TRUE, FALSE altrimenti */
int search(albero tree, int n){
    /* Albero vuoto */
    if(is_empty(tree)){
        printf("\nRicerca nodo con valore: %d fallita.\n", n);
        return;
    }   // Altrimenti albero non vuoto, devo cercare il valore nel sotto-albero a sinistra e nel sotto-albero a destra
    int trovato = 0;
    /* caso base */
    if(tree->info==n)
        trovato = 1;
    else
        trovato = search(tree->left, n) && search(tree->right, n);
    
    return trovato;
}


int main(){

    /* 
    Es. Di albero binario 

                          Radice (root)
                            __
                   --------|__|--------
                   |                 |
            -----|__|-----    -----|__|-----
            |            |    |             |

    */


    /* Creazione nuovo albero */
    albero alberello = newTree();

    /* Aggiunta di una radice all'albero */
    add_root(&alberello, 1);    // radice di valore '1' 

    /* Aggiungi nodo a sinistra */
    add_left()
}