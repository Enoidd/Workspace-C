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
	albero new = malloc(sizeof(albero));	// alloca memoria per un nuovo albero
	new = NULL;	// inizialmente l'albero è vuoto
	
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

/* PREORDINE */
/* Funzione che cerca nell'albero se esiste un nodo con valore 'n', ritorna TRUE, FALSE altrimenti */
/* VERSIONE PROFESSORE */
nodo* cerca_preordine(nodo* t, int n){
	
	/* Entro nel nodo 't' */
	if(t==NULL)
		return NULL;
	/* Eseguo la computazione su 't' */
	if(t->info==n)	// il nodo ha valore 'n'
		return t;
	/* Lancio la procedura su figlio sx e figlio dx */
	nodo* l = cerca_preordine(t->left, n);
	/* Fintanto che il nodo cercato è diverso da NULL */
	if(l!=NULL){
		return l;
	}
	return cerca_preordine(t->right, n);
}

/* PREORDINE---- VERSIONE RICHIESTA NELLA SLIDE -> MI SONO BASATO SUGLI ESERCIZI DELLA RICORSIONE DEL 1° ANNO */
int cerca(nodo* t, int v){
	int trovato;
	
	/* Albero vuoto */
	/* Passo base */
	if(t==NULL)
		trovato = 0;
	else{	// Altrimenti albero non vuoto
		/* Eseguo la computazione su 't' */
		if(t->info==v)
			trovato = 1;
		else{	// Altrimenti non lo hai trovato
			printf("Visito: %d.\n", t->info);
			/* Lancio della procedura su sotto albero radicato a sx e su sotto albero radicato a destra */
			trovato = cerca(t->left, v);	// cercalo a sinistra
			if(trovato==0)	// Non lo hai trovato nel sotto albero radicato a sinistra
				trovato = cerca(t->right, v);	// cercalo a destra
		}
	}
	return trovato;
}

/* POSTORDINE */
/* VERSIONE PROFESSORE */
nodo* cerca_postordine(nodo* t, int v){
	
	/* ALbero vuoto */
	if(t==NULL)
		return NULL;
	else{	// Altrimenti albero non vuoto
		/* Lancio la procedura su sotto albero radicato a sx e su sotto albero radicato a dx */
		nodo* l = cerca_postordine(t->left, v);
		nodo* r = cerca_postordine(t->right, v);
		/* Se lo hai trovato a sinistra */
		if(l!=NULL){
			return l;
		}
		/* Se lo hai trovato a destra */
		if(r!=NULL){
			return r;
		}
		/* Altrimenti non lo hai ancora trovato */
		/* Eseguo la computazione su 't' */
		if(t->info==v){
			return t;
		}
	}
	return NULL;
}

/* POSTORDINE---- VERSIONE RICHIESTA NELLA SLIDE -> MI SONO BASATO SUGLI ESERCIZI DELLA RICORSIONE DEL 1° ANNO */ 
int cercaPost(albero t, int v){
	int trovato;
	
	/* Albero vuoto */
	if(t==NULL)
		trovato = 0;
	else{	// Altrimenti albero non vuoto
		/* Lancio la procedura su sotto albero radicato a sx e su sotto albero radicato a dx */
		trovato = cercaPost(t->left, v);	// cercalo a sinistra
		if(trovato==0)	// se non lo hai trovato a sinistra
			trovato = cercaPost(t->right, v);	// cercalo a destra
		/* Eseguo la computazione su 't' */
		if(t->info==v)
			trovato = 1;
	}
	return trovato;
}

/* CERCA_SIMMETRICA */
/* VERSIONE PROFESSORE */
nodo* cerca_simmetrica(nodo* t, int v){
	
	/* Albero vuoto */
	if(t==NULL)
		return NULL;
	else{	// Altrimenti albero non vuoto
		/* Lancio la procedura sul sotto albero radicato a sx */
		nodo* l = cerca_simmetrica(t->left, v);
		if(l!=NULL){
			return l;
		}
		/* Eseguo la computazione su 't' */
		if(t->info==v){
			return t;
		}
		/* Lancio la procedura sul sotto albero radicato a dx */
		nodo* r = cerca_simmetrica(t->right, v);
		if(r!=NULL){
			return r;
		}
	}
	return NULL;
}

/* POSTORDINE---- VERSIONE RICHIESTA NELLA SLIDE -> MI SONO BASATO SUGLI ESERCIZI DELLA RICORSIONE DEL 1° ANNO */ 
int cercaSim(albero t, int v){
	int trovato; 
	
	/* Albero vuoto */
	if(t==NULL)
		trovato = 0;
	else{	// Altrimenti albero non vuoto
		/* Lancio la procedura sul sotto albero radicato a sx */
		trovato = cercaSim(t->left, v);
		/* Non lo hai trovato a sx */
		if(trovato==0){
			trovato = 
		}
		/* Eseguo la computazione su 't' */
		else if(t->info==v){
			trovato = 1;
		}
		/* Lancio la procedura sul sotto albero radicato a dx */
		trovato = cercaSim(t->right, v);
		/* Non lo hai trovato a dx */
		if(trovato!=0){
			trovato = 1;
		}
	}
	return trovato;
}


/* Funzione che verifica se l'albero è un cammino oppure no */
/* Quando un albero è un cammino?
 * Sequenza di nodi tali che uno è genitore del successivo è detta cammino, dove il numero di archi del cammino
 * è la sua lunghezza. */

/* Funzione che ritorna il numero di nodi dell'albero */
int contaNodi(albero t){
	/* Albero vuoto */
	if(t==NULL){
		return 0;
	}
	return 1 + contaNodi(t->left) + contaNodi(t->left);
}

int main(int argc, char **argv)
{
	/* Creazione albero */
	albero t = newTree();
	
	/*  IS_EMPTY */
	printf("\n===== IS_EMPTY =====\n");
	if(is_empty(t))
		printf("\nAlbero vuoto.\n");	// Atteso
	else
		printf("\nAlbero non vuoto.\n");
	printf("\n===================\n");
	
	/* Inserimento radice */
	add_root(&t, 10);
	/* Inserimento nodi */
	nodo* tleft = add_left(t, 2);
	nodo* tright = add_right(t, 3);
	nodo* ltleft = add_left(tleft, 4);

	/*  IS_EMPTY */
	printf("\n===== IS_EMPTY =====\n");
	if(is_empty(t))
		printf("\nAlbero vuoto.\n");
	else
		printf("\nAlbero non vuoto.\n");	// Atteso
	printf("\n===================\n");
	
	/* CERCA_NODO_PREORDINE */
	printf("\n=============================");
	printf("\n=== cerca_nodo_preordine ===\n");
	printf("\ncerca_preordine valore 3, esito: %d.\n",cerca_preordine(t, 3)!=NULL);	// Atteso: 1
	
	/* CERCA */
	if(cerca(t, 2))
		printf("\nValore 2, trovato nell'albero.\n");	// Atteso
	else
		printf("\nValore 2, non trovato nell'albero.\n");
		
	/* CERCA_NODO_POSTORDINE */
	printf("\n=============================");
	printf("\n=== cerca_nodo_postordine ===\n");
	printf("\ncerca_postordine valore 2, esito: %d.\n",cerca_postordine(t, 2)!=NULL);	// Atteso: 1

	if(cercaPost(t, 2))
		printf("\nValore 2, trovato nell'albero.\n");	// Atteso
	else
		printf("\nValore 2, non trovato nell'albero.\n");
		
	/* CERCA_NODO_SIMMETRICA */
	printf("\n=============================");
	printf("\n=== cerca_nodo_simmetrica ===\n");
	printf("\ncerca_simmetrica valore 2, esito: %d.\n", cerca_simmetrica(t, 2)!=NULL);	// Atteso: 1
	
	if(cercaSim(t, 2))
		printf("\nValore 2, trovato nell'albero.\n");	// Atteso
	else
		printf("\nValore 2, non trovato nell'albero.\n");
		
		
	/* CONTA NODI */
	printf("\nNodi contati: %d.\n", contaNodi(t));
}
