#include <stdio.h>
#include <stdlib.h>

/* Lezione 36, 37 */

/* =========================== GRAFO LISTE =========================== */

/* Elemento della lista di adiacenza che è doppiamente concatenata */
typedef struct adiacenti{
    int info;   // nodo adiacente
    struct adiacenti* prev;
    struct adiacenti* next;
}adiacenti_nodo;

typedef struct grafo_liste{
    int numero_nodi_liste;
    adiacenti_nodo** A_liste;
}grafo_liste;

/* ===================================================================== */

/* =========================== GRAFO MATRICE =========================== */

/* Struttura grafo matrice */
typedef struct grafo_matrice_adiacenza{
    int numero_nodi_matrice;    // numero dei nodi
    int** A_matrice;    // Matrice
}grafo_matrice;

/*
        A
        __            __     ______________
int**  |__|---> int* |__|-->|__|__|__|__|__|
                     |__|    int (tipo di ogni casella)
                     |__|   ________________
                     |__|-->|__|__|__|__|__|
                     |__|-->|__|__|__|__|__| 

*/

/* ===================================================================== */

/* ==== GRAFO MATRICE ==== */

/* Funzione che crea un grafo matrice con il numero dei nodi specificato e con zero archi */
grafo_matrice* new_grafo_matrice(int num_nodi){

    grafo_matrice* grafo = (grafo_matrice*)malloc(sizeof(grafo_matrice)); // allocazione memoria per un nuovo grafo
    grafo->numero_nodi_matrice = num_nodi;  // Assegnazione grandezza grafo
    grafo->A_matrice = (int**)calloc(num_nodi, sizeof(int*));   // (g->A è di tipo int**) Setta a tutti i nodi a 0
    /* per ogni elemento verticale devo allocare un elemento orizzontale */
    for(int i=0; i<num_nodi; i++){
        /* prendo la cella i-esima di questo array verticale e ci appoggio il risultato della calloc */
        grafo->A_matrice[i] = (int*)calloc(num_nodi, sizeof(int));
    }

    return grafo;   // ritorna un array pieno di 0 proprio perché è stata utilizzata la calloc
}

/* ========================= */

/* ==== GRAFO LISTE ==== */

/* Funzione che crea una grafo liste con il numero dei nodi specificato */
grafo_liste* new_grafo_liste(int num_nodi){
    
    grafo_liste* grafo = (grafo_liste*)malloc(sizeof(grafo_liste)); // ALloco memoria per un nuovo grafo lista

    grafo->numero_nodi_liste = num_nodi;    // della dimensione introdotta 'num_nodi'
    grafo->A_liste = (adiacenti_nodo**)calloc(num_nodi, sizeof(adiacenti_nodo*));   // (grafo->A_liste è di tipo int**)
    /* Non devo inizializzare a NULL tutto l'array g->A_liste perché ho fatto una calloc (clear calloc) e 0 è equivalente a NULL */
    return grafo;
}

/* ====================== */

/* Funzione LISTE(g): Vogliamo creare, aggiungere archi ai due tipi di nodi, perché vogliamo creare degli sul grafo fatto con matrici di adiacenza
 * e nuovi archi sul grafo fatto con liste adiacenza e poi fare la copia dell' uno nell'altro */

/* ==== GRAFO MATRICE ==== */
void aggiungi_arco_matrice(grafo_matrice* g, int u, int v){ // prende la matrice 'g', e gli identificatori dei due nodi (che sono interi)
    /* Deve mettere a 1 il valore nella posizione all'interno della matrice dov'è presente l'arco tra i due nodi (nodo 'v' riga - nodo 'u' colonna) */
    g->A_matrice[u][v] = 1;

    /*
    Es. Tra il nodo 2 e nodo 0 c'è un arco, mentre in tutti gli altri non ci sono archi.
  (V)_0__1__2___3_
    |__|__|__|__|0 (U)
    |__|__|__|__|1
    |1_|__|__|__|2
    |__|__|__|__|3
    
    */
}

/* ==== GRAFO LISTE ==== */

/* Aggiunge arco diretto da 'u' a 'v' */
void aggiungi_arco_liste(grafo_liste* g, int u, int v){ // prende la matrice 'g', e gli identificatori dei due nodi (che sono interi)
    /* Verifico se esiste l'arco */
    adiacenti_nodo* new = g->A_liste[u];  // prendo la lista di adiacenza dell'arco 'u' da cui parto
    /* Scorro tutta la lista di adiacenza */
    while(new!=NULL){
        /* se l'info del nodo 'u' da cui sono partito è proprio uguale a 'v', quindi ho trovato un arco già presente */
        if(new->info==v) return;    // se l'ho trovato esci con 'return'
        new = new->next;    // Altrimenti scorri tutta la lista
    }
    /* Reciclo il blocchetto 'new' che ho creato */
    new = (adiacenti_nodo*)malloc(sizeof(adiacenti_nodo));
    /* Adesso il 'new' creato ha tre campi */
    new->info = v;  // sto mettendo un arco tra 'u' e 'v'
    new->next = g->A_liste[u];  // è il primo elemento della lista di adiacenza
    new->prev = NULL;   // perché il blocchetto è stato messo per primo

    /* Devo verificare se c'era già un elemento nella lista di adiacenza, perché se c'era già il prev di questo elemento 
     * deve puntare al nuovo nodo creato 'new' */
    if(g->A_liste[u] != NULL){  // c'è almeno un elemento in lista
        g->A_liste[u]->prev = new;
    }

    /* Mi devo mettere in testa alla lista */
    g->A_liste[u] = new;    // new è il primo della lista
}

/* Funzione che stampa il grafo liste adiacenza */
void print_liste_adiacenza(grafo_liste* g){

    for(int i = 0; i<g->numero_nodi_liste; i++){
        printf("[%d]", i);  // Stampa l'array verticale
        adiacenti_nodo* x = g->A_liste[i];  // Per ogni elemento dell'array verticale scorri la lista in orizzontale corrispondente
        while(x!=NULL){ // fintanto che ci sono nodi da visitare nella lista dell'array in posizione i-esima
            printf("->[%d]", x->info);  // stampa il suo valore
            x = x->next;
        }   // ho finito di scorrere in orizzontale
        printf("\n");
    }
}

/* ====================== */

/* ==== GRAFO MATRICE ==== */

void print_matrice(grafo_matrice* g){
    /* Righe */
    for(int i=0; i < g->numero_nodi_matrice; i++){
        /* Colonne */
        for(int j=0; j < g->numero_nodi_matrice; j++){
            printf("[%d]", g->A_matrice[i][j]);
        }   // quando finisco di stampare una riga
        printf("\n");   // vado a capo (per sampare la matrice completa)
    }
}

/* ====================== */

/* =========== ESERCIZI SLIDE GRAFO MATRICE =========== */

/* Funzione LISTE(g) che ne restituisce la sua rappresentazione mediante un array di liste di adiacenza
 *  doppiamente concatenate */
/* Costruisce un grafo con liste di adiacenza da un grafo matrice */
grafo_liste* liste(grafo_matrice* g_matrice){
    
    grafo_liste* gl = new_grafo_liste(g_matrice->numero_nodi_matrice);    // creo un grafo liste, che è quello che devo ritornare di grandezza 'numero_nodi'
    /* Scorre la matrice */
    /* Righe */
    for(int i=0; i<g_matrice->numero_nodi_matrice; i++){
        /* Colonne */
        for(int j=0; j<g_matrice->numero_nodi_matrice; j++){
            /* L'elemento corrente è uguale a 1, c'è un arco */
            if(g_matrice->A_matrice[i][j]==1){
                aggiungi_arco_liste(gl, i, j);  // inserisco l'arco nel grafo liste
            }
        }
    }
    return gl;
}

/* Funzione GRADO_USCITA_MATRICE(g, u), che calcola il grado di uscita del nodo con indice 'u'.
 * Il grado di uscita rappresenta il numero dei suoi archi uscenti dal nodo 'u' */
int grado_uscita_matrice(grafo_matrice* g_matrice, int u){  // 'u' è un indice inserito
    int grado = 0;  // Inizialmente si suppone il grado essere 0
    /* Riga - Devo scorrere solo la riga */
    for(int i=0; i<g_matrice->numero_nodi_matrice; i++){
        /* Ho trovato un arco sulla riga */
        if(g_matrice->A_matrice[u][i]==1)
            grado++;
        }
    return grado;
}

/* Funzione GRADO_ENTRATA_MATRICE(g, u), che calcola il grado di entrata nel nodo con indice 'u' .
 * Il grado di entrata rappresenta il numero dei suoi archi entranti nel nodo 'u' */
int grado_entrata_matrice(grafo_matrice* g_matrice, int u){
    int grado = 0;  // si suppone il grado essere 0

    /* Colonna - Devo scorrere la colonna per vedere quanti archi arrivano sul nodo 'u' */
    for(int i=0; i<g_matrice->numero_nodi_matrice; i++){
        /* Ho trovato l'arco sulla colonna */
        if(g_matrice->A_matrice[i][u]==1)
            grado++;
    }
    return grado;
}

/* Funzione GRADO_USCITA_MEDIO(g), che calcola il grado di uscita medio all'interno del grafo matrice 'g' */
int grado_uscita_medio_matrice(grafo_matrice* g_matrice){
    int grado_medio = 0;    // inizialmente nessun grado calcolato, si suppone non ci siano archi presenti

    /* Riga */
    for(int i=0; i<g_matrice->numero_nodi_matrice; i++){
        /* Colonna */
        for(int j=0; j<g_matrice->numero_nodi_matrice; j++){
            /* il nodo che stai visitando ha un arco uscente */
            if(g_matrice->A_matrice[i][j]==1)
                grado_medio++;
        }
    }
    return (int)(grado_medio/g_matrice->numero_nodi_matrice);   // faccio il casting a tipo INT della divisione per il calcolo del grado medio
}

/* Funzione GRAFO_SEMPLICE_MATRICE(g) che verifica se il grafo è semplice (privo di cappi) */
/* Quando un nodo ha un cappio? Per la matrice se c'è un 1 nella stessa posizione, riga e colonna 
  (V)_0__1__2___3_
    |__|__|__|__|0 (U)
    |__|__|__|__|1
    |__|__|__|__|2
    |__|__|__|1_|3
    
*/
int grafo_semplice_matrice(grafo_matrice* g_matrice){
    int no_cappi = 1;   // Si suppone non ci siano cappi

    /* Riga */
    for(int i=0; i<g_matrice->numero_nodi_matrice; i++){
        /* Colonne */
        for(int j=0; j<g_matrice->numero_nodi_matrice; j++){
            /* C'è un cappio */
            if(((i==j) && g_matrice->A_matrice[i][j]==1) && no_cappi)
                no_cappi = 0;
        }
    }
    return no_cappi;
}

/* =========== ESERCIZI SLIDE GRAFO LISTE =========== */

/* Costruisce un grafo matrice da un grafo liste */
grafo_matrice* matrice(grafo_liste* g_liste){

    grafo_matrice* gm = new_grafo_matrice(g_liste->numero_nodi_liste);  // creo un grafo matrice, che è quello che devo ritornare di grandezza 'numero_nodi'
    
    /* Scorri l'array di liste verticale */
    for(int i=0; i<g_liste->numero_nodi_liste; i++){
        adiacenti_nodo* x = g_liste->A_liste[i];    // per scorrere in orizzontale a partire dall'elemento i-esimo in verticale
        /* c'è un nodo? - Scorri in orizzontale */
        while(x!=NULL){ // sei in posizione 'i-esima' verticale e stai correndo l'elemento x-esimo in orizzontale quindi ('i'-->arco-->'x!=NULL')
            gm->A_matrice[i][x->info] = 1;  // Nella posizione riga (i) e colonna (x->info) ci vado a mettere
            x = x->next;    // passa al prossimo nodo se ce ne sono
        }
    }
    return gm;
}


/* Funzione GRADO_USCITA_LISTE(g, u), che calcola il grado di uscita del nodo con indice 'u'.
 * Il grado di uscita rappresenta il numero dei suoi archi uscenti nel nodo 'u' */
int grado_uscita_liste(grafo_liste* g_liste, int u){
    int grado = 0;  // inizialmente si suppone il grado essere 0
    /* Scorri l'array di liste verticale */
    for(int i=0; i<g_liste->numero_nodi_liste; i++){
        adiacenti_nodo* x = g_liste->A_liste[i];    // per scorrere in orizzontale a partire dall'elemento i-esimo in verticale
        /* c'è un nodo? - Scorri in orizzontale */
        while(x!=NULL){
            grado++;
            x = x->next;    // passa al prossimonodo in orizzontale
        }
    }
    return grado;
}

/* Funzione GRADO_ENTRATA_LISTE(g, u), che calcola il grado di entrata nel nodo con indice 'u' .
 * Il grado di entrata rappresenta il numero dei suoi archi entranti nel nodo 'u' */
int grado_entrata_liste(grafo_liste* g_liste, int u){
    int grado = 0;  // inizialmente si suppone il grado essere 0
    /* Scorri l'array di liste verticale */
    for(int i=0; i<g_liste->numero_nodi_liste; i++){
        adiacenti_nodo* x = g_liste->A_liste[i];    // per scorrere in orizzontale
        /* l'elemento corrente ha valore 'u' */
        if(x->info==u)  // c'è un arco allora
            grado++;
        x = x->next;
    }
}

/* Funzione GRADO_USCITA_MEDIO_LISTE(g), che calcola il grado di uscita medio all'interno del grafo matrice 'g' */
int grado_uscita_medio_liste(grafo_liste* g_liste){
    int grado = 0;  // inizialmente si suppone il grado essere 0
    /* Scorri la lista di array in verticale */
    for(int i=0; i<g_liste->numero_nodi_liste; i++){
        adiacenti_nodo* x = g_liste->A_liste[i];    // per scorrere orizzontalmente la lista
        /* Se ci sono nodi presenti allora c'è un arco */
        while(x!=NULL){
            grado++;
            x = x->next;
        }
    }
    return (int)grado/g_liste->numero_nodi_liste;
}


/* Funzione GRAFO_SEMPLICE_LISTE(g) che verifica se il grafo è semplice (privo di cappi) */
/* Quando un nodo ha un cappio? Per le liste se sull'array di liste in verticale in posizione i-esima questo punta ad un valore 'x' 
* e nell'array di liste in verticale nella posizione x-esima questo punta al valore i-esimo precedente allora c'è un cappio. 
*/
/* Funzione GRAFO_SEMPLICE_LISTE(g) che verifica se il grafo è semplice (privo di cappi)*/
int grafo_semplice_liste(grafo_liste* g_liste){
    int no_cappi = 1;
}


int main(){

    /* Si vuole creare un grafo matrice con 10 nodi */
    grafo_matrice* gm = new_grafo_matrice(10);

    /* Si vuole creare un grafo liste con 20 nodi */
    //grafo_liste* gl = new_grafo_liste(20);

    /* GRAFO LISTE Aggiungi arco (diretto) tra i nodi */
    //aggiungi_arco_liste(gl, 1, 2);  // aggiungi arco tra il nodo 1 e il nodo 2
    //aggiungi_arco_liste(gl, 2, 3);  // aggiungi arco tra il nodo 2 e il nodo 3
    //aggiungi_arco_liste(gl, 2, 6);  // aggiungi arco tra il nodo 2 e il nodo 6

    /* GRAFO LISTE Stampa grafo liste */
    //print_liste_adiacenza(gl);

    //printf("\n\n");

    /* GRAFO MATRICE Aggiungi arco (diretto) tra i nodi */
    aggiungi_arco_matrice(gm, 1, 2);
    aggiungi_arco_matrice(gm, 2, 3);
    aggiungi_arco_matrice(gm, 2, 6);


    /* GRAFO MATRICE Stampa grafo matrice */
    print_matrice(gm);

    printf("\n\n");

    /* Creo un grafo liste e gli passo la funzione che dal grafo matrice, trasforma il grafo in grafo liste */
    grafo_liste* gl = liste(gm);
    
    /* Stampo il grafo liste creato dal grafo matrice */
    print_liste_adiacenza(gl);
}