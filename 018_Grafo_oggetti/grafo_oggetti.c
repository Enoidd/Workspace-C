#include <stdio.h>
#include <stdlib.h>

// Forward declaration
typedef struct elem_lista_archi elem_archi;  // struttura elem_lista_archi che ho richiamato elem_archi;
// Forward declaration fatta quando ho modificato la struttura nodo per fare la cancellazione 
typedef struct elem_lista_nodi elem_nodi;

/* ===================================================================================================================== */

/* Struttura nodo */
/* NB. Se volessi cancellare un nodo in questo caso dovrei scorrere la lista dei nodi, per evitare di fare questo lavoro
vado a modificare la struttura del nodo e vado a metterci il puntatore alla sua posizione nella lista nodi */
//typedef struct struct_nodo{
//    int id;
    /* Il nodo ha una lista di archi */
//    elem_archi* archi;
//}nodo; 

/* Struttura nodo modificata con aggiunta del puntatore alla sua posizione nella lista nodi per effettuare la 
cancellazione*/
typedef struct struct_nodo{
    int id;
    elem_archi* archi;  // il nodo ha una lista di archi
    elem_nodi* pos; // posizione nella lista dei nodi del grafo
}nodo;
/* ===================================================================================================================== */


/* ===================================================================================================================== */
/* Struttura nodo arco */
/* NB. Per rimuovere un nodo ovviamente devo rimuovere anche l'arco, quindi devo modificare questa struttura */
//typedef struct struct_arco{
//    int id;
//    nodo* from; // l'arco arriva dal nodo 'from'
//    nodo* to;   // l'arco va al nodo 'to'
//}arco;

/* Struttura modificata per la cancellazione */
typedef struct struct_arco{
    int id;
    nodo* from; // l'arco arriva dal nodo 'from'
    nodo* to;   // l'arco va al nodo 'to'
    elem_archi* pos;    // posizione nella lista degli archi del grafo 
    elem_archi* from_pos;   // posizione nella lista degli archi del nodo from
    elem_archi* to_pos; // posizione nella lista degli archi del nodo to
}arco;
/* ===================================================================================================================== */


/* Struttura elementi lista nodi */
/* NB. 'elem_nodi' e il tipo 'struct elem_lista_nodi' sono esattamente la stessa cosa */
typedef struct elem_lista_nodi{
    /* Puntatore ad un nodo quindi avremo prev, next, info */
    nodo* info; // puntatore ad un nodo che conterrà il campo info
    struct elem_lista_nodi* prev;
    struct elem_lista_nodi* next;
}elem_nodi;

/* Struttura elementi lista archi */
typedef struct elem_lista_archi{
    arco* info;
    struct elem_lista_archi* prev;
    struct elem_lista_archi* next;
}elem_archi;

/* Struttura grafo oggetti */
typedef struct go{
    int numero_nodi;
    int numero_archi;
    elem_nodi* nodi;    // puntatore alla lista dei nodi
    elem_archi* archi;  // puntatore alla lista degli archi
}grafo_oggetti;


/* Costruttore - Costruisco un nuovo grafo oggetti vuoto */
grafo_oggetti* new_grafo_oggetti(){
    /* Nel grafo oggetti ci sono tre campi: numero_nodi, numero_archi, nodi e archi */
    /* Creo un grafo oggetti */
    grafo_oggetti* go = (grafo_oggetti*)malloc(sizeof(grafo_oggetti));
    go->numero_nodi = 0;
    go->numero_archi = 0;
    /* lista nodi - non c'è nessun nodo inizialmente */
    go->nodi = NULL;
    /* lista archi - non c'è nessun arco inizialmente */
    go->archi = NULL;

    return go;
}

/* Funzione che aggiunge un nodo con un id - ritorna un nodo quindi è di tipo 'nodo*' */
nodo* aggiungi_nodo(grafo_oggetti* go, int id){
    /* creo un nuovo nodo */
    nodo* n = (nodo*)malloc(sizeof(nodo));
    n->id = id;
    n->archi = NULL;    // non ho inizialmente nessun arco su questo nodo

    elem_nodi* ln = (elem_nodi*)malloc(sizeof(elem_nodi));
    ln->info = n;
    ln->prev = NULL;    // metto 'ln' in testa alla lista
    ln->next = go->nodi;    // metto in testa alla lista nodi

    /* Vedo se c'èra già almeno un nodo */
    if(go->nodi!=NULL){
        go->nodi->prev = ln;
    }
    go->nodi = ln;
    go->numero_nodi++;  // incremento il numero di nodi nel grafo

    n->pos = ln;
}

/* Funzione che aggiunge un arco */
arco* aggiungi_arco(grafo_oggetti* go, int id, nodo* from, nodo* to){
    /* Creo l'arco */
    arco* a = (arco*)malloc(sizeof(arco));
    a->id = id;
    a->from = from;
    a->to = to;

    // aggiungo l'arco alla lista degli archi del grafo 
    // 
    elem_archi* la = (elem_archi*)malloc(sizeof(elem_archi));
    la->info = a;
    la->prev = NULL;    // lo metto in testa
    la->next = go->archi;   // attuale primo elemento della lista archi

    /* Se c'èra già un arco */
    if(go->archi!=NULL){
        go->archi->prev = la;
    }
    go->archi = la;
    go->numero_archi++; // avendo aggiunto un arco devo incrementare il numero di archi inseriti
    a->pos = la;    // ricordo quale è la posizione degli archi nel grafo

    /* ==================================================================================== */
    /* Creo blocchetto la (lista archi) da mettere sul 'from' */
    /* inserisco l'arco nella lista degli archi del nodo 'from' */
    elem_archi* la_from = (elem_archi*)malloc(sizeof(elem_archi));
    la_from->info = a;
    la_from->prev = NULL;    // lo metto in testa
    la_from->next = from->archi;

    /* Se c'èra già un arco */
    if(from->archi!=NULL){
        from->archi->prev = la_from;  // vai al primo elemento from->archi, prendi il suo prev e mettici la_from
    }
    from->archi = la_from;
    a->from_pos = la_from;
    /* ==================================================================================== */

    /* ==================================================================================== */
    /* Inserisco l'arco nella lista degli archi del nodo to */
    /* Creo blocchetto la (lista archi) da mettere sul 'to' */
    elem_archi* la_to = (elem_archi*)malloc(sizeof(elem_archi));
    la_to->info = a;
    la_to->prev = NULL;    // lo metto in testa
    la_to->next = to->archi;   // attuale primo elemento della lista archi

    /* Se c'èra già un arco */
    if(to->archi!=NULL){
        to->archi->prev = la_to;
    }
    to->archi = la_to;
    a->to_pos = la_to;
    /* ==================================================================================== */

    return a;
}

/* Funzione che stampa un grafo oggetti */
void stampa_grafo_oggetti(grafo_oggetti* go){
    printf("\n======= STAMPO GRAFO OGGETTI =======\n");
    printf("\nil grafo ha %d nodi\n", go->numero_nodi);
    printf("\nil grafo ha %d archi\n", go->numero_archi);
    /* Per scorrere la lista */
    elem_nodi* ln = go->nodi;
    printf("\n======== STAMPO I NODI ========\n");
    while(ln!=NULL){    // scorro la lista fintanto che ci sono nodi
        printf("\ntrovato nodo %d\n", ln->info->id);
        ln = ln->next;
    }
    elem_archi* la = go->archi;
    printf("\n======== STAMPO GLI ARCHI ========\n");
    while(la!=NULL){    // scorro la lista fintanto che ci sono archi
        printf("\ntrovato arco %d\n", la->info->id);
        printf("          da %d\n", la->info->from->id);
        printf("          a %d\n", la->info->to->id);
        la = la->next;
    }
    printf("\n=======================================\n");
}

// Forward declaration
void rimuovi_arco(grafo_oggetti* go, arco* a);

/* Funzione che cancella un nodo */
void rimuovi_nodo(grafo_oggetti* go, nodo* n){
    /* 1. Elimino tutti gli archi del nodo */
    elem_archi* la = n->archi;
    while(la!=NULL){    // fino a che ho un arco
        elem_archi* prossimo_arco = la->next;
        rimuovi_arco(go, la->info);
        la = prossimo_arco;
    }
    /* 2. HP. Non ci sono archi, rimuovo questo nodo 'n' dalla lista dei nodi del grafo */
    /* Voglio dunque rimuovere il nodo dalla lista dei nodi */
    if(n->pos->next != NULL){   // c'è un altro elemento della lista che punta ad un nodo che mi segue 
        n->pos->next->prev = n->pos->prev; // dell'oggetto n->pos->next il campo prev deve essere uguale al prev di n->pos quindi n->pos->prev
    }
    /* Se c'è un elemento che mi precede */
    if(n->pos->prev != NULL){
        n->pos->prev->next = n->pos->next;  // il suo next deve saltarmi
    }   // Altrimenti se non c'è nessuno che mi precede
    else{   // n->pos è il primo elemento della lista
        go->nodi = n->pos->next;
    }
    free(n->pos);   // dealloco il blocchetto della lista
    /* 3. libero la memoria (lo cancello) */
    free(n);
    go->numero_nodi--;  // decremento il numero dei nodi perché ho cancellato un nodo
}

/* Funzione che cancella un arco */
void rimuovi_arco(grafo_oggetti* go, arco* a){
    
    // 1. rimuovo l'arco dalla lista degli archi del grafo
    if(a->pos->next != NULL){   // c'è un altro elemento della lista che punta ad un nodo che mi segue 
        a->pos->next->prev = a->pos->prev; // dell'oggetto a->pos->next il campo prev deve essere uguale al prev di a->pos quindi a->pos->prev
    }
    /* Se c'è un elemento che mi precede */
    if(a->pos->prev != NULL){  
        a->pos->prev->next = a->pos->next;  // il suo next deve saltarmi
    }   // Altrimenti se non c'è nessuno che mi precede
    else{   // a->pos è il primo elemento della lista
        go->archi = a->pos->next;    // mi salto
    }
    free(a->pos);   // dealloco il blocchetto della lista

    /* NODO FROM ========================================================================================================= */
    // 2. rimuovo l'arco dalla lista degli archi del nodo from
    if(a->from_pos->next != NULL){   // c'è un altro elemento della lista che punta ad un nodo che mi segue 
        a->from_pos->next->prev = a->from_pos->prev; // dell'oggetto a->pos->next il campo prev deve essere uguale al prev di a->pos quindi a->pos->prev
    }
    /* Se c'è un elemento che mi precede */
    if(a->from_pos->prev != NULL){  
        a->from_pos->prev->next = a->from_pos->next;  // il suo next deve saltarmi
    }   // Altrimenti se non c'è nessuno che mi precede
    else{   // a->pos è il primo elemento della lista
        a->from->archi = a->from_pos->next;    // mi salto
    }
    free(a->from_pos);   // dealloco il blocchetto della lista

    /* NODO TO ========================================================================================================= */
    // 3. rimuovo l'arco dalla lista degli archi del nodo to
    if(a->to_pos->next != NULL){   // c'è un altro elemento della lista che punta ad un nodo che mi segue 
        a->to_pos->next->prev = a->to_pos->prev; // dell'oggetto a->pos->next il campo prev deve essere uguale al prev di a->pos quindi a->pos->prev
    }
    /* Se c'è un elemento che mi precede */
    if(a->from_pos->prev != NULL){  
        a->to_pos->prev->next = a->to_pos->next;  // il suo next deve saltarmi
    }   // Altrimenti se non c'è nessuno che mi precede
    else{   // a->pos è il primo elemento della lista
        a->to->archi = a->to_pos->next;    // mi salto
    }
    free(a->to_pos);   // dealloco il blocchetto della lista

    // 4. libera la memoria (cancellalo)
    go->numero_archi--; // avendo cancellato un nodo decremento il numero di archi
    free(a);
}

int main(){

    /* Definisco (creo) un grafo oggetti chiamato 'go' */
    grafo_oggetti* go = new_grafo_oggetti();

    /* Aggiungo un nodo */
    nodo* n1 = aggiungi_nodo(go, 1);
    nodo* n2 = aggiungi_nodo(go, 2);
    nodo* n3 = aggiungi_nodo(go, 3);
    nodo* n4 = aggiungi_nodo(go, 4);

    /* Stampa grafo oggetti */
    stampa_grafo_oggetti(go);

    /* Rimuovo il nodo */
    printf("\nHo effettuato la cancellazione di un nodo (n3\n");
    rimuovi_nodo(go, n3);

    /* Stampa grafo oggetti */
    stampa_grafo_oggetti(go);

    /* Aggiungo un arco */
    arco* a1 = aggiungi_arco(go, 1, n1, n2);   // aggiungo arco con id 1 che va da n1 a n2
    arco* a2 = aggiungi_arco(go, 2, n2, n4);   // aggiungo arco con id 2 che va da n2 a n4
    arco* a3 = aggiungi_arco(go, 3,  n4, n1);  // aggiungo arco con id 3 che va da n4 a n1
    /* NB. avendo collegato in questo modo gli archi ho praticamente collegato i nodi formando un grafo a forma di triangolo */

    /* Stampa grafo oggetti */
    stampa_grafo_oggetti(go);

    /* Rimuovo un arco */
    printf("\nArco 'a2' rimosso.\n");
    rimuovi_arco(go, a2);   // rimuovo l'arco 'a2' 

    /* Ristampo */
    stampa_grafo_oggetti(go);

    /* Rimuovo un nodo */
    printf("\nNodo 'n1' rimosso.\n");
    rimuovi_nodo(go, n1);   // rimuovo il nodo 'n1'

    /* Ristampo */
    stampa_grafo_oggetti(go);
}