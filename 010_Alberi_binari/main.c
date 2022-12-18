#include <stdio.h>
#include <stdlib.h>

/* Struttura nodo dell'albero */
typedef struct nodo_albero{
	struct nodo_albero* parent;	// genitore del nodo
	struct nodo_albero* left;		// puntatore a figlio sinistro del nodo
	struct nodo_albero* right;	// puntatore a figlio destro del nodo
	int info;			// campo informazione del nodo
}nodo;
typedef nodo* albero;	// ridefinizione nodo* in 'albero'

/* Funzione che crea un albero */
albero new_tree(){
	albero new_albero = malloc(sizeof(albero));	// alloca memoria per un nuovo nodo
	new_albero = NULL;	// inizialmente albero vuoto
	
	return new_albero;
}

/* Funzione che verifica se l'albero è vuoto */
int is_empty(albero tree){
	return tree==NULL;	// ritorna TRUE(1) se l'albero è vuoto, FALSE(0) altrimenti 
}

/* Funzione che aggiunge la radice all'albero - IMPLEMENTA:  */
void add_root(nodo** puntatore_albero, int v){
	/* Se la radice già esiste */
	if(*puntatore_albero!=NULL){
		printf("\nError. Radice già esistente.\n");
		return;
	}	// Altrimenti
	nodo* root = malloc(sizeof(nodo));	// Alloca memoria per un nuovo nodo
	root->parent = NULL;	// La radice non ha parent
	root->left = NULL;	// inizialmente non ha nodi "figli" a sinistra
	root->right = NULL;	// inizialmente non ha nodi "figli" a destra
	root->info = v;	// inizializzazione al valore
	(*puntatore_albero) = root;	// il nuovo nodo è la testa della lista
}

/* Funzione che verifica se un nodo 'n' ha due figli, ritorna TRUE, FALSE altrimenti */
int twoChildren(nodo* n){
	int two = 0;	// HP. il nodo non ha due figli
	/* Se il nodo corrente ha due figli */
	if(n->left!=NULL && n->right!=NULL)
		two = 1;
	
	return two;
}

/* Funzione che aggiunge un nodo figlio a sinistra */
nodo* add_left(albero tree, int v){
	/* Se esiste un nodo a sinistra */
	if(tree->left!=NULL)
		printf("\nError overflow. Nodo a sinistra gia' esistente.\n");
	// Altrimenti non esiste
	tree->left = malloc(sizeof(nodo));	// alloca memoria per il nuovo nodo a sinistra
	tree->left->parent = tree;	// il parent è il vecchio primo nodo (tree rappresenta la testa)
	tree->left->left = NULL;	// inizialmente il nuovo nodo non ha nodi figli a sinistra
	tree->left->right = NULL;	// inizialmente il nuovo nodo non ha nodi figli a destra
	tree->left->info = v;	// inizializzazione nodo a valore 'v'
	
	return tree->left;
}

/* Funzione che aggiunge un nodo figlio a destra */
nodo* add_right(albero tree, int v){
	/* Se esiste un nodo a destra */
	if(tree->right!=NULL)
		printf("\nError overflow. Nodo a destra gia' esistente.\n");
	// Altrimenti
	tree->right = malloc(sizeof(nodo));	// alloca memoria per il nuovo nodo a destra
	tree->right->parent = tree; 	// il parent è il vecchio primo nodo (tree rappresenta la testa)
	tree->right->left = NULL;	// inizialmente il nuovo nodo non ha nodi figli a sinistra
	tree->right->right = NULL;	// inizialmente il nuovo nodo non ha nodi figli a destra
	tree->right->info = v;	// inizializzazione nodo a valore 'v'
	
	return tree->right;
}

/* Funzione che verifica se l'albero è costituito solo da nodi "figli" a sinistra -
 * IMPLEMENTA verifica universale */
int onlyLeft(albero tree){
	int onlyleft = 1;	// HP. Si ipotizza che l'albero ha tutti nodi "figli" a sinistra
	/* Se l'albero è vuoto */
	if(tree==NULL)
		printf("\nError underflow. Albero vuoto.\n");
	// Altrimenti albero non vuoto
	/* Scorri l'albero fintanto che non ci sono nodi "figli" a destra */
	while(tree!=NULL && onlyleft==1){
		/* Se il nodo corrente ha un figlio a destra */
		if(tree->right!=NULL)
			onlyleft = 0;
		// Altrimenti passa al prossimo
		tree = tree->left;
	}
	return onlyleft;
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
		add_root(&tree1, 10);	// radice di valore 10
		
		/* Inserimento nodi nell'albero */
		nodo* l = add_left(tree1, 2);
		nodo* r = add_right(tree1, 3);
		nodo* ll = add_left(l, 4);
		nodo* lr = add_right(l, 8);
		nodo* rl = add_left(r, 6);
		nodo* rr = add_right(r, 12);
		
		/* Stampa nodi albero dell'albero */
		printf("\n					Root\n");
		printf("				--------[%d]--------", tree1->info);
		printf("\n				|                 |\n");
		printf("			   ----[%d]----", l->info);
		printf("	     ----[%d]----\n", r->info);
		printf("			   |	     |	     |         |");
		printf("\n			  [%d]", ll->info);
		printf("	    [%d]", lr->info);
		printf("	    [%d]", rl->info);
		printf("	     [%d]", rr->info);
		printf("\n");
		
		/* IS_EMPTY -> Verifica albero vuoto */
		if(is_empty(tree1))
			printf("\n -IS_EMPTY: Albero vuoto.\n");
		else
			printf("\n -IS_EMPTY: Albero non vuoto.\n");	// Atteso
		
		/* ONLY_LEFT */
		printf("\n=== OnlyLeft === \n");
		if(onlyLeft(tree1))
			printf("\nTutti i nodi hanno solamente un nodo figlio a sinistra.\n");
		else
			printf("\nAlmeno un nodo dell'albero ha un figlio a destra.\n");
		printf("\n=================\n");
		
		/* TWO_CHILDREN */
		printf("\n= TWO CHILDREN ==\n");
		if(twoChildren(rr))
			printf("\nIl nodo ha due nodi figli.\n");
		else
			printf("\nIl nodo non ha due nodi figli.\n");	// Atteso
		
		
		printf("\n= TWO CHILDREN ==\n");
		if(twoChildren(l))
			printf("\nIl nodo ha due nodi figli.\n");	// Atteso
		else
			printf("\nIl nodo non ha due nodi figli.\n");
		
		
}
