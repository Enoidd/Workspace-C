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
    int color;  // marcatore per visita in ampiezza
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

/* Struttura nodo arco -  modificata per la cancellazione */
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

/* Struttura coda di interi per VISITA IN AMPIEZZA */
typedef struct coda_nodi{
    int head;
    int tail;
    nodo** A;   // Array di nodi*
    int size;
}struct_cn;

/* ====================================== PER VISITA IN AMPIEZZA ====================================== */

/* Costruttore - Costruisce una coda di nodi */
struct_cn* new_coda_di_nodi(int size){
    /* Alloco memoria per una coda di nodi */
    struct_cn* out = (struct_cn*)malloc(sizeof(struct_cn));
    out->head = 0;
    out->tail = 0;
    out->A = (nodo**)malloc(sizeof(nodo*)); // array di puntatori a nodo

    return out;
}

/* Funzione che fa un enqueue in una coda di nodi */
void enqueue(struct_cn* c, nodo* v){
    if((c->tail==c->head-1) || (c->tail==c->size-1 && c->head==0)){
        c->size = c->size*2;
        c->A = (nodo**)realloc(c->A, c->size*sizeof(nodo*));
        if(c->tail < c->head){
            int i;
            for(i=0; i<c->tail; i++){
                c->A[c->size/2+i] = c->A[i];
            }
            c->tail = c->size/2+i;
        }
    }
    c->A[c->tail] = v;
    c->tail = c->tail+1;
    if(c->tail == c->size)
        c->tail = 0;
}

/* Funzione che effettua una dequeue da una coda */
nodo* dequeue(struct_cn* c){

    if(c->head == c->tail){
        printf("\nErrore underflow: dequeue da coda vuota.\n");
        exit(1);
    }
    nodo* out = c->A[c->head];
    c->head = c->head+1;
    if(c->head == c->size)
        c->head = 0;
    
    return out;
}

/* Funzione che verifica se una coda di nodi è vuota */
int coda_di_nodi_is_empty(struct_cn* c){
    return c->head==c->tail;
}

/* ==================================================================================================== */


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
    n->color = 0;

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
        printf("\n        colore %d.\n", ln->info->color);
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

/* ====================================== VISITA IN AMPIEZZA ====================================== */

/* Funzione che fa una visita in ampiezza sul grafo oggetti a partire dal nodo 'n' */
void bfs_grafo_oggetti(grafo_oggetti* go, nodo* n){
    /* NB. Mi serve una coda che abbia dentro dei puntatori ai nodi, altrimenti non posso fare la visita */
    elem_nodi* ln = go->nodi;
    while(ln!=NULL){    // scorro la lista dei nodi
        // coloro il nodo corrente di 0
        ln->info->color = 0;
        ln = ln->next;
    }
    struct_cn* cn = new_coda_di_nodi(8);    // creo la coda di nodi
    /* Devo scegliere chi è il primo nodo */
    n->color = 1;   // marco come (visitato) "messo in coda"
    enqueue(cn, n); // metto in coda di nodi 'cn' il nodo 'n' (che è un puntatore al nodo 'n')
    /* Finot a che la coda non è vuota */
    while(!coda_di_nodi_is_empty(cn)){
        nodo* nodo_corrente = dequeue(cn);
        /* guardo i suoi vicini, che ho nella lista archi */
        elem_archi* la = nodo_corrente->archi;
        while(la!=NULL){    // socrro lista archi adiacenti
            nodo* altro_nodo = la->info->from;
            /* Se il from sono io */
            if(altro_nodo == nodo_corrente){
                altro_nodo = la->info->to;
            }
            /* Devo vedere se altro_nodo è marcato */
            if(altro_nodo->color == 0){ // è la prima volta che visito il nodo
                altro_nodo->color = 1;  // lo marco come visitato
                enqueue(cn, altro_nodo);    // lo metto in coda
            }
            la = la->next;  // passa al prossimo arco che esce da questo nodo
        }
    } 
}



/* =============================================== VISITA IN PROFONDITA' =============================================== */

/* Funzione che fa una visita in profondità per grafi NON CONNESSI */
void dfs_ricorsiva(nodo* n){
    /* Quando lancio la dfs e entro sul nodo lo marco come visitato (color 1) */
    n->color = 1;   // marco il nodo come visitato
    elem_archi* la = n->archi;
    // per tutti gli archi che ci sono sulla lista
    while(la!=NULL){
        nodo* altro_nodo = la->info->from;  // nodo from dell'arco
        if(altro_nodo == n)
            altro_nodo = la->info->to;
        if(altro_nodo->color == 0){    // se l'altro nodo non è colorato
            dfs_ricorsiva(altro_nodo);
        }
        la = la->next;
    }
}

/* Funzione che fa una visita in profondità di una componente connessa e la colora con il colore 'colore'  */
void dfs_ricorsiva_colora(nodo* n, int colore){
    /* Quando lancio la dfs e entro sul nodo lo marco come visitato (color 1) */
    n->color = colore;   // marco il nodo come visitato
    elem_archi* la = n->archi;
    // per tutti gli archi che ci sono sulla lista
    while(la!=NULL){
        nodo* altro_nodo = la->info->from;  // nodo from dell'arco
        if(altro_nodo == n)
            altro_nodo = la->info->to;
        if(altro_nodo->color == 0){    // se l'altro nodo non è colorato
            dfs_ricorsiva_colora(altro_nodo, colore);
        }
        la = la->next;
    }
}

/* Funzione che restituisce il numero dei nodi visitati */
int dfs_ricorsiva_conta(nodo* n){   // ritorna i nodi visitati

    int cont = 1;    // nodi visitati
    n->color = 1;    // marco il nodo passato come visitato
    elem_archi* la = n->archi;
    // per tutti gli archi che ci sono sulla lista
    while(la!=NULL){
        nodo* altro_nodo = la->info->from;  // nodo from dell'arco
        if(altro_nodo == n)
            altro_nodo = la->info->to;
        if(altro_nodo->color == 0){    // se l'altro nodo non è colorato
            cont = cont + dfs_ricorsiva_conta(altro_nodo);    // lancio ricorsivamente sui nodi raggiungibili, si prende altro_nodo
            //  e riporta tutti i nodi raggiunti dal lancio ricorsivo compreso 'altro_nodo' passato
        }
        la = la->next;
    }
    return cont;
}

void dfs_grafo_oggetti(grafo_oggetti* go, nodo* n){
    /* Quando faccio una visita la prima cosa che devo fare è marcare tutti i nodi con un colore non visitato (colore 0) */
    elem_nodi* ln = go->nodi;
    while(ln!=NULL){
        ln->info->color = 0;    // coloro tutto di zero
        ln = ln->next;
    }
    /* A questo punto lancio la procedura ricorsiva della funzione di visita */
    if(go->numero_nodi==0) return;  // verifica che ci sia almeno un nodo
    // se sei qui c'è almeno un nodo
    dfs_ricorsiva(n);

}

/* Funzione che conta le componenti connesse */
int num_componenti_connesse_grafo_oggetti(grafo_oggetti* go){
    
    int componenti_connesse = 0;
    /* procedura che mette tutti i colori a 0 */
    elem_nodi* ln = go->nodi;
    while(ln!=NULL){
        ln->info->color = 0;    // coloro tutto di zero
        ln = ln->next;
    }
    ln = go->nodi;  // ripercorro la lista dei nodi e controllo quali sono i nodi non marcati
    while(ln!=NULL){
        /* Se il nodo corrente non è marcato */
        if(ln->info->color==0){ // trovato nodo non visitato
            componenti_connesse = componenti_connesse+1;
            dfs_ricorsiva(ln->info);    // coloro il nodo
        }
        ln = ln->next;
    }
    return componenti_connesse;
}

/* VERSIONE 1 - Funzione che verifica se tutte le componenti hanno la stessa dimensione */
int dimensione_componenti_uguali(grafo_oggetti* go){

    int componenti_connesse = 0;
    /* procedura che mette tutti i colori a 0 */
    elem_nodi* ln = go->nodi;
    while(ln!=NULL){
        ln->info->color = 0;    // coloro tutto di zero
        ln = ln->next;
    }
    ln = go->nodi;  // ripercorro la lista dei nodi e controllo quali sono i nodi non marcati
    while(ln!=NULL){
        /* Se il nodo corrente non è marcato */
        if(ln->info->color==0){ // trovato nodo non visitato
            componenti_connesse = componenti_connesse+1;
            dfs_ricorsiva_colora(ln->info, componenti_connesse);    // coloro il nodo
        }
        ln = ln->next;
    }
    /* Quando ho finito di fare le visite */
    /* Dentro componenti_connesse ho: il numero delle componenti connesse trovate */
    /* Definisco un array di interi */
    int* dim = (int*)calloc(componenti_connesse+1, sizeof(int));
    ln = go->nodi;
    /* Scorro nuovamente i nodi */
    while(ln!=NULL){
        /* Se il nodo corrente non è marcato */
        dim[ln->info->color]++; // incremento l'array dim nella posizione del colore del nodo
        ln = ln->next;
    }    /* Qui l'array dim ha tutte le componenti connesse */
    int j;
    for(j = 2; j<=componenti_connesse; j++){
        
        if(dim[j]!=dim[1]){
            free(dim);
            return 0;   // trovata una componente connessa di dimensione diversa dalla prima 
        }
    }
    free(dim);
    return 1;
}

/* VERSIONE 2 - Funzione che verifica se tutte le componenti hanno la stessa dimensione */
int dimensione_componenti_uguali_dfs_conta(grafo_oggetti* go){

    /* procedura che mette tutti i colori a 0 */
    elem_nodi* ln = go->nodi;
    while(ln!=NULL){
        ln->info->color = 0;    // coloro tutto di zero
        ln = ln->next;
    }
    int nodi_prima_componente_connessa = 0;
    ln = go->nodi;  // ripercorro la lista dei nodi e controllo quali sono i nodi non marcati
    while(ln!=NULL){
        /* Se il nodo corrente non è marcato */
        if(ln->info->color==0){ // trovato nodo non visitato
            int nodi_visitati = dfs_ricorsiva_conta(ln->info);    // coloro il nodo
            if(nodi_prima_componente_connessa==0){  // ho visitato la prima componente
                nodi_prima_componente_connessa = nodi_visitati;
            }   // altrimenti se non è uguale a 0 non sono sulla prima componenti (l'ho già vista)
            else{   // sono su una componente successiva
                if(nodi_visitati != nodi_prima_componente_connessa){
                    return 0;   // torvata una componente di diversa grandezza
                }
            }
        }
        ln = ln->next;
    }
    return 1;
}

/* ===================================================================================================================== */

int main(){

    /* Definisco (creo) un grafo oggetti chiamato 'go' */
    grafo_oggetti* go = new_grafo_oggetti();

    /* Aggiungo un nodo */
    nodo* n1 = aggiungi_nodo(go, 1);
    nodo* n2 = aggiungi_nodo(go, 2);
    nodo* n3 = aggiungi_nodo(go, 3);
    nodo* n4 = aggiungi_nodo(go, 4);
    nodo* n5 = aggiungi_nodo(go, 5);
    nodo* n6 = aggiungi_nodo(go, 6);
    nodo* n7 = aggiungi_nodo(go, 7);

    /* Stampa grafo oggetti */
    stampa_grafo_oggetti(go);

    /* Rimuovo il nodo */
    printf("\nHo effettuato la cancellazione di un nodo (n3)\n");
    rimuovi_nodo(go, n3);

    /* Stampa grafo oggetti */
    stampa_grafo_oggetti(go);

    /* Aggiungo un arco */
    arco* a1 = aggiungi_arco(go, 1, n1, n2);   // aggiungo arco con id 1 che va da n1 a n2
    arco* a2 = aggiungi_arco(go, 2, n2, n4);   // aggiungo arco con id 2 che va da n2 a n4
    arco* a3 = aggiungi_arco(go, 3,  n4, n1);  // aggiungo arco con id 3 che va da n4 a n1
    arco* a4 = aggiungi_arco(go, 4,  n5, n6);  // aggiungo arco con id 4 che va da n5 a n6
    arco* a5 = aggiungi_arco(go, 5,  n6, n7);  // aggiungo arco con id 4 che va da n6 a n7
    
    /* NB. avendo collegato in questo modo gli archi ho praticamente collegato i nodi formando un grafo a forma di triangolo */

    /* Stampa grafo oggetti */
    stampa_grafo_oggetti(go);

    /* Faccio la visita in ampiezza */
    //bfs_grafo_oggetti(go, n1);
    dfs_grafo_oggetti(go, n1);

     /* Stampa grafo oggetti */
    stampa_grafo_oggetti(go);

    /* Conto le componenti connesse */
    printf("\nNumero componenti connesse: %d.\n\n", num_componenti_connesse_grafo_oggetti(go));

    /* Componenti connesse uguali */
    printf("\nComponenti uguali: %d.\n\n", dimensione_componenti_uguali(go));

    /* Componenti uguali dfs conta */
    printf("\nComponenti uguali dfs conta: %d.\n\n", dimensione_componenti_uguali_dfs_conta(go));

     /* Stampa grafo oggetti */
    stampa_grafo_oggetti(go);

    /* Rimuovo un arco */
    //printf("\nArco 'a2' rimosso.\n");
    //rimuovi_arco(go, a2);   // rimuovo l'arco 'a2' 

    /* Ristampo */
    //stampa_grafo_oggetti(go);

    /* Rimuovo un nodo */
    //printf("\nNodo 'n1' rimosso.\n");
    //rimuovi_nodo(go, n1);   // rimuovo il nodo 'n1'

    /* Ristampo */
    //stampa_grafo_oggetti(go);

}