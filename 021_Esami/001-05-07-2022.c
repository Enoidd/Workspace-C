#include <stdio.h>
#include <stdlib.h>

/* ================================ STRUTTURE GRAFO ================================ */

typedef struct lista_nodi elem_nodi;
typedef struct lista_archi elem_archi;

/* Struttura nodo */
typedef struct nodo{
    int id;
    elem_archi* archi;
    elem_nodi* pos;
    int color;
}nodo;

typedef struct arco_grafo{
    int id;
    nodo* from;
    nodo* to;
    elem_archi* pos;
    elem_archi* f_pos;
    elem_archi* to_pos;
}arco;

/* Lista nodi */
typedef struct lista_nodi{
    nodo* info;
    struct lista_nodi* prev;
    struct lista_nodi* next;
}elem_nodi;

/* Lista archi */
typedef struct lista_archi{
    arco* info;
    struct lista_archi* prev;
    struct lista_archi* next;
}elem_archi;

/* Struttura grafo */
typedef struct grafo_oggetti{

    int numero_nodi;
    int numero_archi;
    elem_nodi* nodi;
    elem_archi* archi;
}go;

/* Funzione che crea un nuovo grafo */
go* new_grafo(){

    go* nuovo_grafo = (go*)malloc(sizeof(go));
    nuovo_grafo->numero_nodi = 0;
    nuovo_grafo->numero_archi = 0;
    nuovo_grafo->nodi = NULL;
    nuovo_grafo->archi = NULL;

    return nuovo_grafo;
}

/* Funzione aggiungi nodo al grafo di valore 'value' */
nodo* aggiungi_nodo(go* g, int value){

    nodo* new_nodo = (nodo*)malloc(sizeof(nodo));
    new_nodo->archi = NULL; // nessun arco32
    new_nodo->id = value;
    new_nodo->color = 0;

    elem_nodi* lista_nodi = (elem_nodi*)malloc(sizeof(elem_nodi));
    lista_nodi->info = new_nodo;    // adesso punta al nuovo nodo creato
    lista_nodi->prev = NULL;    // è il primo
    lista_nodi->next = g->nodi;

    if(g->nodi!=NULL){
        g->nodi->prev = lista_nodi;
    }

    g->nodi = lista_nodi;
    g->numero_nodi++;

    return new_nodo;
}

/* Funzione che aggiunge arco */
arco* aggiungi_arco(go* g, int id, nodo* to, nodo* from){
    
    arco* a = (arco*)malloc(sizeof(arco));
    a->id = id;
    a->from = from;
    a->to = to;
    
    // Aggiungo arco nella lista degli archi del grafo
    elem_archi* la = (elem_archi*)malloc(sizeof(elem_archi));
    la->info = a;
    la->prev = NULL;
    la->next = g->archi;

    if(g->archi!=NULL){
        g->archi->prev = la;
    }
    g->archi = la;
    g->numero_archi++;
    a->pos = g->archi;

    // from
    elem_archi* la_from = (elem_archi*)malloc(sizeof(elem_archi));
    la_from->info = a;
    la_from->prev = NULL;
    la_from->next = from->archi;

    if(from->archi!=NULL){
        from->archi->prev = la_from;
    }
    from->archi = la_from;
    a->f_pos = la_from;

    // to
    elem_archi* la_to = (elem_archi*)malloc(sizeof(elem_archi));
    la_to->info = a;
    la_to->prev = NULL;
    la_to->next = to->archi;

    if(to->archi!=NULL){
        to->archi->prev = la_to;
    }
    to->archi = la_to;
    a->to_pos = la_to;

    return a;
}

/* ================================ FUNZIONI ESAME ================================ */


/* La funzione restituisce 1 (cioè true) se il grafo contiene almeno una componente connessa il cui numero di 
nodi è pari al numero di componenti connesse del grafo stesso, altrimenti la funzione restituisce 0 (cioè 
false). Se il grafo è vuoto (cioè uguale a NULL) la funzione ritorna 1 (true). */

void dfs_colora(nodo* n, int color){
	n->color = color;
	elem_archi* lista_archi_n = n->archi;
	while(lista_archi_n!=NULL){
		nodo* x = lista_archi_n->info->from;
		if(x==n)
			x = lista_archi_n->info->to;
		if(x->color==0)
			dfs_colora(x, color);
		lista_archi_n = lista_archi_n->next;
	}
}

/* Calcola il numero dei nodi della componente connessa */
int componente_connessa(go* g, int comp){
	int count = 0;
	elem_nodi* n = g->nodi;
	while(n!=NULL){
		if(n->info->color==comp)
			count++;
		n = n->next;
	}
}

int verifica(go* g){
	if(g==NULL) return 1;

	elem_nodi* n = g->nodi;
	while(n!=NULL){
		n->info->color = 0;
		n = n->next;
	}
	int color = 0;
	n = g->nodi;
	while(n!=NULL){
		if(n->info->color==0){
			color++;
			dfs_colora(n->info, color);
		}
		n = n->next;
	}
	int comp;
	for(comp = 1; comp <= color; comp++){
		if(componente_connessa(g, comp) == color)
			return 1;
	}
	return 0;
}

/* ========================== MAIN ========================== */
int main(){

	go* grafo_oggetti_1 = new_grafo();

    nodo* nodo_1 = aggiungi_nodo(grafo_oggetti_1, 2);
    nodo* nodo_2 = aggiungi_nodo(grafo_oggetti_1, 3);
    nodo* nodo_3 = aggiungi_nodo(grafo_oggetti_1, 4);
    nodo* nodo_4 = aggiungi_nodo(grafo_oggetti_1, 5);
    nodo* nodo_5 = aggiungi_nodo(grafo_oggetti_1, 6);

    arco* arco_1 = aggiungi_arco(grafo_oggetti_1, 5, nodo_1, nodo_2);
    arco* arco_2 = aggiungi_arco(grafo_oggetti_1, 5, nodo_2, nodo_3);
    arco* arco_3 = aggiungi_arco(grafo_oggetti_1, 5, nodo_4, nodo_5);

	printf("\nIl grafo contiene una componente connessa il cui num di nodi e' pari alle componenti connesse del grafo: %d.\n", verifica(grafo_oggetti_1));
}