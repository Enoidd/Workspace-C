#include <stdio.h>
#include <stdlib.h>

/* Struttura nodo albero */
typedef struct na{
	struct na* parent;	// puntatore a parent del nodo
	struct na* primo_figlio;	// puntatore a nodo "figlio" sinistro
	struct na* fratello_destro;	// puntatore a nodo "figlio" destro
	int info;	// campo info del nodo
}nodo;
typedef nodo* albero;

/* Funzione che crea un nuovo albero */
albero new_tree(){
	/* Alloca memoria per il nuovo albero */
	albero new_albero = malloc(sizeof(albero));
	new_albero = NULL;	// inizialmente l'albero è vuoto
	
	return new_albero;
}

/* Funzione che verifica se l'albero è vuoto */
int is_empty(albero tree){
	return tree==NULL;
}

/* Funzione che aggiunge la radice all'albero */
void add_root(nodo** puntatore_albero, int v){
	/* Se la radice gia' esiste */
	if(*puntatore_albero!=NULL){
		printf("\nError. Radice gia' esistente.\n");
		return;
	}	// Altrimenti la radice non esiste
	nodo* root = malloc(sizeof(nodo));	// Allocazione memoria per la radice
	root->parent = NULL;	// la radice non ha parent
	root->primo_figlio = NULL;	// inizialmente la radice non ha nodi "figli" a sinistra
	root->fratello_destro = NULL;	// inizialmente la radice non ha nodi "figli" a destra
	root->info = v;	// inizializzazione campo info della radice
	*puntatore_albero = root;	// il nuovo nodo è la testa della lista
}

/* Funzione che aggiunge un figlio al all'albero */
nodo* add_child(albero tree,int v){
	nodo* new_child = malloc(sizeof(nodo));	// Alloca memoria per il nuovo nodo 
	new_child->parent = tree;	// il parent del nuovo nodo è il vecchio nodo 'tree'
	tree->primo_figlio = NULL;	// inizialmente il nuovo nodo non ha altri figli
	new_child->info = v;	// inizializzazione valore nuovo nodo
	new_child->fratello_destro = tree->primo_figlio;	// il nuovo nodo punta al primo figlio del vecchio nodo
	tree->primo_figlio = new_child;	// il vecchio nodo ha come primo figlio il nuovo nodo
	
	return new_child;
}

/* Funzione che aggiunge al nodo 'n' un figlio di valore 'z' */
nodo* add_sibling(albero tree, nodo* n, int z){
	/* Se l'albero è vuoto */
	if(tree==NULL)
		printf("\nError underflow. Albero vuoto.\n");
	// Altrimenti albero non vuoto
	nodo* temp = malloc(sizeof(nodo));	// Alloca memoria per il nuovo nodo
	temp->parent = n;	// il parent del nuovo nodo è il vecchio nodo 'n'
	temp->primo_figlio = NULL;	// inizialmente il nuovo nodo non ha altri figli
	temp->info = z;	// inizializzazione valore nuovo nodo
	temp->fratello_destro = n->primo_figlio;	// il nuovo nodo punta al primo figlio del vecchio nodo
	n->primo_figlio = temp;	// il vecchio nodo ha come primo figlio il nuovo nodo
	
	return temp;
}

int main(int argc, char **argv)
{
	/* Creazione nuovo albero */
	albero tree1 = new_tree();
	
	/* IS_EMPTY -> Verifica albero vuoto */
	if(is_empty(tree1))
		printf("\n -IS_EMPTY: Albero vuoto.\n");	// Atteso
	else
		printf("\n -IS_EMPTY: Albero non vuoto.\n");
	
	/* Inserimento radice */
	add_root(&tree1, 1);	// radice di valore 10
	
	/* Inserimento nodi nell'albero */
	nodo* n0 = add_child(tree1, 2);
	nodo* n1 = add_child(tree1, 2);
	nodo* n2 = add_child(tree1, 2);
	nodo* n3 = add_sibling(tree1, n2, 2);
}
