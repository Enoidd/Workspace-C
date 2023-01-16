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

/*albero newTree(){
	albero new = (albero)malloc(sizeof(albero));	
	new = NULL;
    return new;
}*/

/* Funzione aggiungi radice */
void add_root(nodo** punta_albero, int v){
	/* Se l'albro ha già la radice */
	if(*punta_albero!=NULL)
		printf("\nError. Radice gia' esistente.\n");
	// Altrimenti radice non esistente
	nodo* root = malloc(sizeof(nodo));	// allocazione memoria per il nuovo nodo che rappresenta la radice dell'albero
	root->p = NULL;	// la radice non ha parent
	root->l = NULL;		// la radice inizialmente non ha nodi figli a sinistra
	root->r = NULL;		// la radice inizialmente non ha nodi figli a destra
	root->info = v;			// inizializzazione valore radice a 'v'
	(*punta_albero) = root;	// aggiorna la radice dell'albero con la nuova radice
}

/*void add_root(nodo** t, int v){
    if((*t)!=NULL){
        printf("\nInserimento radice fallito. Radice gia' esistente\n");
        return;
    }
    nodo* root = (nodo*)malloc(sizeof(nodo));
    root->p = NULL;
    root->l = NULL;
    root->r = NULL;
    root->info = v;
    (*t) = root;
}*/

/*albero add_left(albero t, int v){
    if(t->l!=NULL){
        printf("\nNodo a sinistra gia' esistente.\n");
    }
    t->l = (nodo*)malloc(sizeof(nodo));
    t->l->p = t;
    t->l->l = NULL;
    t->l->r = NULL,
    t->l->info = v;

    return t->l;
}*/
nodo* add_left(albero t, int x){
	/* Se il nodo è gia' esistente */
	if(t->l!=NULL)
		printf("\nError overflow, add_left fallito.\n");
	// Altrimenti 
	t->l = (nodo*)malloc(sizeof(nodo));	// allocazione memoria per il nuovo nodo a sinistra
	t->l->p = t;	// il nuovo nodo ha come parent il vecchio nodo 't'
	t->l->l = NULL;	// inizialmente il nuovo nodo non ha nodi figli a sinistra
	t->l->r = NULL;	// inizialmente il nuovo nodo non ha nodi figli a destra
	t->l->info = x;	// inizializzazione valore nuovo nodo creato
	
	return t->l;
}

albero add_right(albero t, int v){
    if(t->r!=NULL){
        printf("\nNodo a destra gia' esistente.\n");
    }
    t->r = (nodo*)malloc(sizeof(nodo));
    t->r->p = t;
    t->r->l = NULL;
    t->r->r = NULL;
    t->r->info = v;

    return t->r;
}

int is_empty(nodo* t){
    return t==NULL;
}

/* PREORDINE */
/* Funzione che cerca nell'albero se esiste un nodo con valore 'n', ritorna TRUE, FALSE altrimenti */
/* VERSIONE PROFESSORE */
nodo* search_pre(nodo* t, int n){
    if(t==NULL)
        return NULL;
    /* il nodo sono proprio io */
    if(t->info==n)   
        return t;

    nodo* l = search_pre(t->l, n);
    if(l!=NULL){
        return l;
    }
    return search_pre(t->r, n);
}

int search_pre_v1(albero t, int n){
    int trovato;

    if(t==NULL) // albero vuoto
        trovato = 0;

    if(t->info==n) // ho lanciato su di me
        trovato = 1;
    else{   // non ho lanciato su di me
        trovato = search_pre_v1(t->l, n);   // lo cerco a sinistra
        if(trovato==0)  // non l'ho ancora trovato 
            trovato = search_pre_v1(t->r, n);   // lo cerco a destra
    }
    return trovato;
}

/* Funzione ricerca in postordine */
nodo* search_post(albero t, int n){
    if(t==NULL) return NULL; // albero vuoto

    nodo* l = search_post(t->l, n);
    nodo* r = search_post(t->r, n);

    if(l!=NULL) return l;

    if(r!=NULL) return r;

    if(t->info==n)
        return t;
    
    return NULL;    // altrimenti non l'ho trovato
}

int search_post_v1(albero t, int n){
    if(t==NULL) return 0;

    int trovato_dx = search_post_v1(t->l, n);
    int trovato_sx = search_post_v1(t->r, n);

    if(trovato_sx==1)
        return 1;

    if(trovato_dx==1)
        return 1;

    if(t->info==n)
        return 1;

    return 0;
}

/* Funzione ricerca simmetrica */
nodo* search_sim(nodo* t, int n){
    if(t==NULL) return NULL;

    nodo* l = search_sim(t->l, n);
    if(l!=NULL)  return l;

    if(t->info==n) return t;

    nodo* r = search_sim(t->r, n);
    if(r!=NULL) return r;

    return NULL;
}

int search_sim_v1(albero t, int n){
    if(t==NULL) return 0;
    
    if(search_post_v1(t->l, n)) return 1;

    if(t->info==n) return 1;

    if(search_sim_v1(t->r, n)) return 1;

    return 0;
}

/*  Funzione che conta i nodi */
int contaNodi(albero t){
    if(t==NULL) return 0;

    return 1 + contaNodi(t->l) + contaNodi(t->r);
}

/* Funzione che verifica se l'albero è un cammino, cioè se tutti i nodi hanno grado
1 con eccezione dell'unica foglia. Si assume che l'albero vuoto è un cammino */
/* POSTORDINE */
int cammino(albero t){
    if(t==NULL) return 1;

    if(cammino(t->l) && t->r==NULL)
        return 1;
    
    if(cammino(t->r) && t->l==NULL)
        return 1;
    
    if(t->l==NULL && t->r==NULL)
        return 1;

    return 0;
}


/* Funzione che calcola l'altezza di un albero, cioè il numero di archi del cammino che va dalla radice
 * alla foglia più profonda, ritorna -1 se l'albero è vuoto */
int altezza(albero t){
    if(t==NULL)     return 0;

    int l = altezza(t->l);
    int r = altezza(t->r);
    
    int max = l;
    if(r>max){
        max = r;
    }
    return max+1;    
}

int main(){

    //albero t1 = newTree();
    albero t1 = NULL;
    
    /* Is empty */
    printf("\nis empty: %d.\n", is_empty(t1)); // atteso 1

    /* Aggiungi radice */
    add_root(&t1, 1);

    /* Aggiungi nodo a sinistra */
    nodo* l = add_left(t1, 2);
    /* Aggiungi nodo a destra */
    nodo* r = add_right(t1, 3);

    nodo* ll = add_left(l, 4);
    nodo* lr = add_right(l, 5);

    /* Is empty */
    printf("\nis empty: %d.\n", is_empty(t1));  // atteso 0

    /* Search pre */
    printf("\n==Search pre\n");
    printf("\nNodo con valore 5 trovato (atteso 1): %d.\n", search_pre(t1, 5)!=NULL);
    printf("\nNodo con valore 2 trovato (atteso 1): %d.\n", search_pre(t1, 2)!=NULL);

    /* Search pre versione 1 */
    printf("\n==Search pre v1\n");
    printf("\nNodo con valore 4 trovato (atteso 1): %d.\n", search_pre_v1(t1, 4));
    printf("\nNodo con valore 2 trovato (atteso 1): %d.\n", search_pre_v1(t1, 2));

    /* Search_post */
    printf("\n==Search post\n");
    printf("\nNodo con valore 4 trovato (atteso 1): %d.\n", search_post(t1, 4)!=NULL);
    printf("\nNodo con valore 2 trovato (atteso 1): %d.\n", search_post(t1, 2)!=NULL);

    /* Search post versione 1 */
    printf("\n==Search post v1\n");
    printf("\nNodo con valore 4 trovato (atteso 1): %d.\n", search_post_v1(t1, 4));
    printf("\nNodo con valore 2 trovato (atteso 1): %d.\n", search_post_v1(t1, 2));

    /* Search sim */
    printf("\n==Search sim\n");
    printf("\nNodo con valore 4 trovato (atteso 1): %d.\n", search_post_v1(t1, 4));
    printf("\nNodo con valore 3 trovato (atteso 1): %d.\n", search_post_v1(t1, 3));
    
    /* Search sim v1 */
    printf("\n==Search sim v1\n");
    printf("\nNodo con valore 4 trovato (atteso 1): %d.\n", search_sim_v1(t1, 4));
    printf("\nNodo con valore 3 trovato (atteso 1): %d.\n", search_sim_v1(t1, 3));
    
    /* Funzione conta nodi */
    printf("\nNodi contati (atteso 5): %d.\n", contaNodi(t1));

    /* Funzione verifica albero se è cammino */
    printf("\nCammino (atteso 0): %d.\n", cammino(t1));

    /* Funzione che calcola l'altezza dell'albero */
    printf("\nAltezza (atteso: nd): %d.\n", altezza(t1));
}