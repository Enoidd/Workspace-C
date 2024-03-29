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

/* ================================ STRUTTURA ALBERO ================================ */

typedef struct nodo_a{
    struct nodo_a* p;
    struct nodo_a* l;
    int info;
    struct nodo_a* r; 
}nodo_albero;

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

/* Funzione che conta e colora i nodi che appartengono alla stessa componente connessa del nodo passato */
int dfs_count(nodo* n){
    
    n->color = 1;
    int count = 1;
    elem_archi* lista_archi_n = n->archi;   // 1° arco notevole di 'n'
    while(lista_archi_n!=NULL){
        nodo* x = lista_archi_n->info->from;
        if(x==n) 
            x = lista_archi_n->info->to;
        if(x->color==0)
            count += dfs_count(x);
        lista_archi_n = lista_archi_n->next;
    }
    return count;
}

/* Funzione che ritorna il numero di nodi della componente connessa più grande */
int componente_connessa_maggiore(go* g){

    elem_nodi* clear_nodi = g->nodi;
    while(clear_nodi!=NULL){
        clear_nodi->info->color = 0;
        clear_nodi = clear_nodi->next;
    }
    elem_nodi* lista_nodi = g->nodi;    // riparto dal primo nodo del grafo
    int max = dfs_count(lista_nodi->info); // contiene il numero di nodi della componente connessa a cui appartiene il primo nodo salvato nella lista del grafo
    int temp;
    lista_nodi = lista_nodi->next;  // parto dal 2° nodo del grafo
    while(lista_nodi!=NULL){    // scorro la lista dei nodi
        /* per ogni nodo che visito devo vedere se l'ho già visto */
        if(lista_nodi->info->color==0)
            temp = dfs_count(lista_nodi->info);
            if(temp>max)
                max = temp;
        lista_nodi = lista_nodi->next;
    }
    return max;
}

/* Funzione che conta i nodi dell'albero */
int nodi_albero(nodo_albero* t, int h){

    if(t==NULL) return 0;
    int count = 0;
    if(h==0) count++;

    nodo_albero* x = t->l;
    while(x!=NULL){
        count += nodi_albero(x, h-1);
        x = x->r;
    }
}

int height(nodo_albero* t){
    if(t==NULL) return -1;

    int max = 0;
    nodo_albero* x = t->l;
    while(x!=NULL){
        int temp = height(x);
        if(x->info > max) // x > max 
            max = temp;
        x = x->r;
    }
    return max+1;
}

/* */
int verifica_ric(nodo_albero* a, int v){
    if(a==NULL) return 0;

    for(int i=0; i<height(a); i++){
        if(nodi_albero(a, i)==v)
            return 1;
    }
    return 0;
}

/* Funzione che conta la componente connessa del grafo */
int verifica(nodo_albero* a, go* g){

    if(a==NULL && g==NULL) return 0;
    int numero_nodi_componente_max = componente_connessa_maggiore(g);

    return verifica_ric(a, numero_nodi_componente_max);
}

/* ========================== MAIN ========================== */
int main(){

	go* grafo_oggetti_1 = new_grafo();

    nodo* nodo_1 = aggiungi_nodo(grafo_oggetti_1, 2);
    nodo* nodo_2 = aggiungi_nodo(grafo_oggetti_1, 3);
    nodo* nodo_3 = aggiungi_nodo(grafo_oggetti_1, 4);
    nodo* nodo_4 = aggiungi_nodo(grafo_oggetti_1, 5);

    arco* arco_1 = aggiungi_arco(grafo_oggetti_1, 5, nodo_1, nodo_2);
    arco* arco_2 = aggiungi_arco(grafo_oggetti_1, 5, nodo_2, nodo_3);

	//TEST SU alberi arbitrari
	nodo_albero* a0 = NULL;
	
	//liv 0
	add_root_arb(&a0,3);

	//liv 1
	nodo* n2=add_left_arb(a0,20);
	nodo* n1=add_left_arb(a0,1);
	//liv 2
	nodo* n3=add_left_arb(n1,1); //foglia
	nodo* n4=add_left_arb(n1,1); //foglia
	nodo* n5=add_left_arb(n1,1);
	nodo* n6=add_left_arb(n1,1); //foglia
	nodo* n7=add_left_arb(n2,1);
	//liv 3
	nodo* n8=add_left_arb(n5,3); //foglia
	nodo* n9=add_left_arb(n5,30);
	nodo* n10=add_left_arb(n7,1); //foglia
	nodo* n11=add_left_arb(n7,1); //foglia
	//liv 4
	nodo* n12=add_left_arb(n9,32); //foglia

    printf("\nVerifica: %d.\n", a0, grafo_oggetti_1);
	
}