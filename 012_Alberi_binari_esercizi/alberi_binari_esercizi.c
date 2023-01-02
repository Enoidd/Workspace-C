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
		nodo* l = cerca_postordine(t->left, v);
		nodo* r = cerca_postordine(t->right, v);
		/* Lancio la procedura su sotto albero radicato a sx e su sotto albero radicato a dx */
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
			/* Eseguo la computazione su 't' */
			if(t->info==v){
				trovato = 1;
			}
		}
		else if(trovato==0){	// non lo hai trovato a sx e non ' t'
			/* Lancio la procedura sul sotto albero radicato a dx */
			trovato = cercaSim(t->right, v);
			/* Non lo hai trovato a dx */
			if(trovato!=0){
				trovato = 1;
			}
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

/* Funzione che verifica se l'albero è un cammino, cioè se tutti i nodi hanno grado 1, con l'eccezione 
 * dell'unica foglia. Si assume che un albero vuoto sia un cammino. */
/* POSTORDINE */
int cammino(albero t){
	/* Se l'albero è vuoto */
	if(t==NULL)
		return 1;	// è un cammino
	/* Guarda il sotto albero radicato a sx */
	if(cammino(t->left) && t->right==NULL)
		return 1;
	/* Guarda il sotto albero radicato a dx */
	if(cammino(t->right) && t->left==NULL)
		return 1;
	/* Se è presente soltanto la radice */
	if(t->left==NULL && t->right==NULL)
		return 1;
	return 0;
}

/* Funzione che calcola l'altezza di un albero, cioè il numero di archi del cammino che va dalla radice
 * alla foglia più profonda, ritorna -1 se l'albero è vuoto */
int height(albero t){
	/* Se l'albero è vuoto */
	if(t==NULL){
		return -1;
	}	// Altrimenti l'albero non è vuoto
	int l = height(t->left);
	int r = height(t->right);

	int max = l;	// l'altezza è massima è l'altezza del sotto albero radicato a sx
	/* Se il sotto albero radicato a destra è maggiore di max */
	if(r>max){
		max = r;	// Aggiorna il nuovo max
	}
	return max+1;
}

/* Funzione che calcola la media dei valori contenuti nell'albero binario */
void averageRic(nodo* t, int* somma, int* contatore){
	/* Se l'albero è vuoto */
	if(t==NULL)
		return;
		
	/* Calcola la somma */
	*somma += t->info;	// somma a somma il valore del nodo corrente
	(*contatore) += (*contatore)+1;	// Aggiorna il contatore
	
	/* Lancia la procedura sul sotto albero radicato a sx e dx */
	averageRic(t->left, somma, contatore);
	averageRic(t->right, somma, contatore);

}

int average(nodo* t){
	int somma = 0;	// la somma dei valori dei nodi dell'albero
	int contatore = 0;	// il numero di nodi presenti nell'albero
	
	/* Invocazione della funzione ricorsiva */
	averageRic(t, &somma, &contatore);
	
	int media = somma/contatore;
	
	return media;
}

/* Funzione che verifica se l'albero binario è completo, ritorna true se l'albero è vuoto */
int completoRic(albero t){
	/* Se l'albero è vuoto */
	if(t==NULL)
		return -1;
	
	/* Lancio la procedura su 't' */
	/* Il nodo non ha figlio sinistro e figlio destro */
	if(t->left==NULL && t->right==NULL){
		return 0;
	}
	
	int l = completoRic(t->left);	// guardo sul sotto albero radicato a sx
	int r = completoRic(t->right);	// guardo sul sotto albero radicato a dx
	
	/* Il sotto albero radicato a sx e a dx non è un albero completo */
	if(l==-1 && r==-1)
		return -1;
	
	/* Altrimenti in questo punto i sotto alberi radicati a sx e dx sono due sottoalberi radicati completi */
	/* Se la profondità del sotto albero a sx è diversa dalla profondità del sotto albero a dx uno dei due non è completo */
	if(l!=r)
		return -1;
		
	return l+1;
}

int completo(nodo* n){
	/* Se l'albero è vuoto */
	if(n==NULL)
		return 1;
	// Altrimenti se sei qui non è un albero completo
	int risultato = completoRic(n);
	
	return risultato!=-1;	// ritorna il risultato se è diverso da 1
}

/* Funzione che dealloca tutti i nodi di un albero */
void dealloca(nodo** t){
	/* Se l'albero è vuoto */
	if((*t)==NULL)
		return;
	/* Lancia la procedura sul sotto albero radicato a sx e sul sotto albero radicato a dx */
	dealloca(&(*t)->left);
	dealloca(&(*t)->right);

	free(*t);
	(*t) = NULL;
}

/* Funzione che elimina un sotto albero radicato al nodo 'x' */
void pota(nodo** n, nodo* x){
	if((*n)==NULL) return;
	if((*n)==x){
		dealloca(n);
		return;
	}
	/* Sx */
	if((*n)->left==x){
		dealloca(&(*n)->left);
	}

	/* Dx */
	if((*n)->right==x){
		dealloca(&(*n)->right);
	}
}

/* PARENTETICA SIMMETRICA */
void parenteticaSim(albero t){
	if(t==NULL){
		printf("()");
		return;
	}

	printf("(");
	parenteticaSim(t->left);
	printf("%d", t->info);
	printf(")");
	parenteticaSim(t->right);
}

/* PARENTETICA PREORDINE */

/* Funzione che calcola il numero di nodi dell'albero che hanno lo stesso valore del genitore del genitore
 * cioè del nonno */
int valoreNonno(albero t){
	if(t==NULL) return 0;

	int count = 0;

	if(t->parent!=NULL){
		if(t->parent->parent!=NULL){
			if(t->parent->parent->info == t->info)
				count++;
		}
	}
	count = count + valoreNonno(t->left);
	count = count + valoreNonno(t->right);
}

/* Funzione che calcola il numero di nodi che hanno esattamente due figli */
int dueFigli(albero t){
	if(t==NULL) return 0;

	int count = 0;

	/* caso base */
	if(t->left!=NULL && t->right!=NULL)
		count++;

	return count + dueFigli(t->left) + dueFigli(t->right);
}

/* Funzione che calcola il numero di nodi che hanno esattamente 4 nipoti */
int quattroNipoti(albero t){
	if(t==NULL) return 0;

	int count = 0;

	/* caso base */
	if(t->left!=NULL && t->right!=NULL){
		if(t->left->left!=NULL && t->right->right!=NULL){
			count++;
		}
	}
	return count + quattroNipoti(t->left) + quattroNipoti(t->right);
}

/* HOMEWORK */

/* PRE_ESAME */

/* Funzione che conta tutti i nodi che sono foglie */
int contaFigliFoglie(albero t){
	if(t==NULL) return 0;

	albero l = t->left;
	albero r = t->right;
	
	int count = 0;
	/* il sotto albero radicato a sx non è vuoto */
	if(l!=NULL){
		/* cerca a sx e dx */
		if(l->left==NULL && l->right==NULL)	// è una foglia
			count++;
	}
	else{
		if(r!=NULL){
			if(r->left==NULL && r->right==NULL)	// è una foglia
				count++;
		}
	}
	return count + contaFigliFoglie(t->left) && contaFigliFoglie(t->right);
}

/* Funzione che verifica se esiste almeno una foglia a destra in un albero */
int fogliaDestra(albero t){
	if(t==NULL) return 0;

	albero r = t->right;

	if(r!=NULL){
		return 1;
	}
	return fogliaDestra(t->left) || fogliaDestra(t->right);
}

/* Funzione che conta i nodi che hanno figli foglie */
int contaNodiConFigliFoglie(albero t){
	if(t==NULL) return 0;

	int count = 0;

	if(t->left==NULL && t->right==NULL){
		count++;
	}
	return count + contaNodiConFigliFoglie(t->left) + contaNodiConFigliFoglie(t->right);
}

/* Funzione che verifica se in un albero esiste una foglia e se questa ha valore uguale a 0 */
int fogliaZero(albero t){
	if(t==NULL)	return 0;

	/* E'una foglia */
	if(t->left==NULL && t->right==NULL){
		if(t->info==0)
			return 1;
	}
	return fogliaZero(t->left) || fogliaZero(t->right);
}

/* Funzione che verifica se in un albero ci sono esattamente 2 foglie con valore uguale a 0 */
int DieciFoglie(albero t){
	if(t==NULL) return 0;

	int count = 0;

	/* E' una foglia */
	if(t->left==NULL && t->right==NULL){
		if(t->info==0){	// campo info uguale a 0
			count++;
			if(count==2)
				return 1;
		}
	}
	return count + DieciFoglie(t->left) + DieciFoglie(t->right);
}

/* Funzione che calcola se esiste un nodo dell'albero che ha campo info pari alla sua distanza dalla radice */
int nodiDistanzaRic(albero t, int count){
	/* Se l'albero è vuoto */
	if(t==NULL){
		return 0;
	}	// Altrimenti l'albero non è vuoto

	if(t->info==count) return 1;

	return nodiDistanzaRic(t->left,count+1) || nodiDistanzaRic(t->right,count+1);
}

int nodiDistanza(albero t){
	if(t==NULL) return 0;

	nodiDistanzaRic(t, 0);
}

/* Funzione che calcola il n° di nodi dell'albero che hanno campo info
pari alla loro distanza dalla radice */
int numero_nodiDistanzaRic(albero t, int count){
	/* Se l'albero è vuoto */
	if(t==NULL){
		return 0;
	}	// Altrimenti l'albero non è vuoto

	int contatore = 0;

	if(t->info==count)
		contatore++;

	return contatore + numero_nodiDistanzaRic(t->left,count+1) + numero_nodiDistanzaRic(t->right,count+1);
}

int numero_nodiDistanza(albero t){
	if(t==NULL) return 0;

	numero_nodiDistanzaRic(t, 0);
}

/* Funzione che conta i nodi che hanno campo info uguale all'altezza dell'albero */
int altezza(albero t){
	if(t==NULL) return -1;

	int l = altezza(t->left);
	int r = altezza(t->right);

	if(l>r) return l+1;
	return r+1;
}


int campoInfo_ugualeLunghezza(albero t, int distanza){	// Funzione che verifica se campo info è uguale a lunghezza
	if(t==NULL) return 0;

	int count = 0;

	if(t->info == distanza) 
		count++;
	return count + campoInfo_ugualeLunghezza(t->right, distanza) + campoInfo_ugualeLunghezza(t->left, distanza);
}

int conta_campoInfoUgualeLunghezza(albero t){	// Funzione che conta i nodi che hanno campo info pari all'altezza
	if(t==NULL) return 0;

	int distanza = altezza(t);	// calcola l'altezza 

	return campoInfo_ugualeLunghezza(t, distanza);
}

/* Funzione che verifica che tutti i nodi dell'albero hanno campo info uguale all'altezza dell'albero */
int nodi(albero t){
	if(t==NULL)
		return 0;
	return 1 + nodi(t->left) + nodi(t->right);
}

int tuttiNodi(albero t){	// Verifica se tutti i nodi hanno campo info pari all'altezza dell'albero
	if(t==NULL) return 0;

	int tutti = nodi(t);
	int distanza = altezza(t);

	return tutti = campoInfo_ugualeLunghezza(t, distanza);
}

/* Funzione che verifica se ogni nodo di un albero ha campo info uguale al numero di nodi dell'albero completo */
int verificaOgniNodo(albero t){
	if(t==NULL) return 0;

	int tutti = nodi(t);

	return tutti == campoInfo_ugualeLunghezza(t, tutti);
}

/* Funzione che conta i nodi interni dell'albero */
int contatoreNodiInterni(albero t){
	if(t==NULL) return 0;

	int count = 0;

	if(t->left!=NULL && t->right==NULL)	count++;
	if(t->left==NULL && t->right!=NULL)	count++;

	return 1 + contatoreNodiInterni(t->left) + contatoreNodiInterni(t->right);
}

/* Funzione che verifica nell'albero se esiste un nodo che ha entrambi i figli foglie */
int entrambi_figli_foglie(albero t){
	if(t==NULL) return 0;

	albero l = t->left;
	albero r = t->right;

	if(l!=NULL && r!=NULL){
		if((l->left==NULL && l->right==NULL) && (r->left==NULL && r->right==NULL))
			return 1;
	}
	return entrambi_figli_foglie(l->right) || entrambi_figli_foglie(r->left); 
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
	add_root(&t, 4);	// 10
	/* Inserimento nodi */
	nodo* tleft = add_left(t, 4);	// 2
	nodo* tright = add_right(t, 4);	// 3
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
	
	/* CAMMINO */
	if(cammino(t))
		printf("\nL'albero %c un cammino.\n", 138);
	else
		printf("\nL'albero non %c un cammino.\n", 138);
	
	/* AVERAGE */
	printf("\nMedia dei nodi contenuti nell'albero: %d.\n", average(t));	// Atteso: 4

	/* PARENTETICA SIMMETRICA */
	printf("\n");
	parenteticaSim(t);
	printf("\n");

	/* ========= PRE ESAME ========= */
	
	/* CONTA NODI FOGLIE */
	printf("\nNodi foglie contati: %d.\n", contaFigliFoglie(t));

	/* Verifica se nell'albero c'è almeno una foglia a destra */
	printf("Una foglia a destra: %d.\n", fogliaDestra(t)); // Atteso: 1

	/* Conta nodi con figli che sono foglie */
	printf("ContaNodiConFigliFoglie: %d.\n", contaNodiConFigliFoglie(t));	// Atteso: 2

	/* Verifica se esiste foglia con valore 0 */
	printf("Foglia con valore 0: %d.\n", fogliaZero(t));	// Corretto

	/* Verifica se nell'albero ci sono 2 foglie con valore 0 */
	printf("Foglie con valore 0 contate: %d.\n", DieciFoglie(t));	// Corretto

	/* Funzione che calcola se esiste un nodo dell'albero che ha campo info pari alla sua distanza dalla radice */
	printf("Nodi con campo info pari alla loro distanza dalla radice trovati: %d.\n", nodiDistanza(t));	// Corretto

	/* Funzione che calcola il n° di nodi dell'albero che hanno campo info
	 * pari alla loro distanza dalla radice */
	printf("Nodi con campo info pari alla loro distanza dalla radice contati: %d.\n", numero_nodiDistanza(t));

	/* Funzione che conta i nodi che hanno campo info uguale all'altezza dell'albero */
	printf("Numero nodi che hanno campo info pari all'altezza dell'albero: %d.\n", conta_campoInfoUgualeLunghezza(t));

	/* Funzione che verifica che tutti i nodi dell'albero hanno campo info uguale all'altezza dell'albero */
	printf("Tutti i nodi hanno campo info pari all'altezza dell'albero: %d.\n", tuttiNodi(t));

	/* Funzione che verifica se ogni nodo di un albero ha campo info uguale al numero di nodi dell'albero completo */
	printf("Ogni nodo ha campo info uguale al numero dei nodi dell'albero completo: %d.\n", verificaOgniNodo(t));	// Corretto

	/* Funzione che conta i nodi interni dell'albero */
	printf("Nodi interni dell'albero: %d.\n", contatoreNodiInterni(t));

	/* Funzione che verifica se esiste nell'albero un nodo che ha entrambi figli foglie */
	printf("Verifica se esiste un nodo con entrambi i figli foglie: %d.\n", entrambi_figli_foglie(t));

	/* =============================== */

	/* DEALLOCA ALBERO */
	dealloca(&t);

	/* IS_EMPTY */
	printf("\nVerifica se l'albero 't' e' vuoto, valore calcolato: %d.\n", is_empty(t));	// Atteso: 1

}
