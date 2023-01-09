#include <stdio.h>
#include <stdlib.h>

/* Lezione 36 */

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
                     |__|
                     |__|
                     |__|

*/

/* ===================================================================== */

/* ==== GRAFO MATRICE ==== */

/* Funzione che crea un grafo matrice con il numero dei nodi specificato e con zero archi */
grafo_matrice* new_grafo_matrice(int num_nodi){

    grafo_matrice* grafo = (grafo_matrice*)malloc(sizeof(grafo_matrice)); // allocazione memoria
    grafo->numero_nodi_matrice = num_nodi;
    grafo->A_matrice = (int**)calloc(num_nodi, sizeof(int*));   // g->A è di tipo int**
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
    
    grafo_liste* grafo = (grafo_liste*)malloc(sizeof(grafo_liste));

    grafo->numero_nodi_liste = num_nodi;
    grafo->A_liste = (adiacenti_nodo**)calloc(num_nodi, sizeof(adiacenti_nodo*));
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
}

/* ==== GRAFO LISTE ==== */

/* Aggiunge arco diretto da 'u' a 'v' */
void aggiungi_arco_liste(grafo_liste* g, int u, int v){ // prende la matrice 'g', e gli identificatori dei due nodi (che sono interi)
    /* Verifico se esiste l'arco */
    adiacenti_nodo* new = g->A_liste[u];  // prendo la lista di adiacenza dell'arco 'u' da cui parto
    /* Scorro tutta la lista di adiacenza */
    while(new!=NULL){
        /* se l'info è proprio uguale a 'v', quindi ho trovato un arco già presente */
        if(new->info==v) return;
        new = new->next;
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
        printf("[%d]", i);
        adiacenti_nodo* x = g->A_liste[i];
        while(x!=NULL){
            printf("->[%d]", x->info);
            x = x->next;
        }   // ho finito di scorrere in orizzontale
        printf("\n");
    }
}

int main(){

    /* Si vuole creare un grafo matrice con 10 nodi */
    grafo_matrice* gm = new_grafo_matrice(10);

    /* Si vuole creare un grafo liste con 20 nodi */
    grafo_liste* gl = new_grafo_liste(20);

    /* Aggiungi arco tra i nodi */
    aggiungi_arco_liste(gl, 1, 2);  // aggiungi arco tra il nodo 1 e il nodo 2
    aggiungi_arco_liste(gl, 2, 3);  // aggiungi arco tra il nodo 2 e il nodo 3
    aggiungi_arco_liste(gl, 2, 6);  // aggiungi arco tra il nodo 2 e il nodo 6

    /* Stampa */
    print_liste_adiacenza(gl);
   
}