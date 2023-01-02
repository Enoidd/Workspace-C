#include <stdio.h>
#include <stdlib.h>

/* HEAP:
 * Una struttura dati definita come coda di priorità è definita HEAP. 
 * Un HEAP è rappresentato da una struttura avente come campi un ARRAY e la sua DIMENSIONE.
 * Un HEAP è quindi una collezione di elementi dove ad ogni elemento dell'array è associato un valore di proprità rappresentato dal suo indice.
 * Un HEAP è dunque un albero incompleto avente il sottoalbero destro minore di 1 unità l'altezza rispetto al sottoalbero sinistro.
 * Un nodo con indice i-esimo ha il figlio a sinistra in posizione: 2*i-esimo+1
 * Un nodo con indice i-esimo ha il figlio a destra in posizione: 2*i-esimo+2
 * Un nodo ha come genitore: i-esimo-1/2
 * Un HEAP è un MAX-HEAP se la radice è l'elemento più grande presente (ogni genitore deve essere >= figlio).
 * Un HEAP è un MIN-HEAP se la radice è l'elemento più piccolo presente (ogni genitore deve essere <= figlio).
 * UN HEAP ha n/2-1 nodi interni.
 *
 */

/* Struttura heap */
typedef struct hp{
    int* A;
    int size;   // size dell'array 'A'
}heap;

/* Funzione che crea un heap */
heap* newHeap(int dim){
    /* Alloca memoria per un nuovo heap (per un nuovo array) */
    heap* out = malloc(sizeof(heap));
    /* Definisci i campi */
    out->A = malloc(dim*sizeof(int));  // alloca memoria per l'array di dimensione dim
    out->size = 0;    // la dimensione è 'dim'
    return out;
}

/* Funzione che aggiunge un elemento all'interno dell'heap creato */
void add_number(heap* h, int valore){
    /* heap pieno */
    if(h->size==4)
        h->A = realloc(h->A, h->size*sizeof(int));  // raddoppia la dimensione dell'array
    
    // altrimenti heap non pieno
    h->A[h->size] = valore;
    h->size = h->size+1;
}

/* Funzione che stampa l'heap */
void print_heap(heap* h){
    printf("\n===== STAMPA HEAP =====\n");
    /* scorri tutto l'heap */
    for(int i = 0; i<h->size; i++){
        printf("[%d]", h->A[i]);
    }
    printf("\n=======================\n");
}

/* Funzione che ritorna l'indice del parent del nodo i-esimo */
int parent(int i){
    return (i-1)/2;
}

/* Funzione che ritorna l'indice del figlio sinistro del nodo con indice i-esimo */
int left(int i){
    return 2*i+1;
}

/* Funzione che ritorna l'indice del figlio destro del nodo con indice i-esimo */
int right(int i){
    return 2*i+2;
}

/* MAX_HEAP è una funzione che trasforma un sottoalbero radicato ad 'i' in un max_heap */
// Forward declaration
void scambia_caselle(int* A, int i, int max);

void max_heapify(heap* h, int i){   // COSTO THETA(1)
    
    int l = left(i);    // indice del figlio sinistro
    int r = right(i);   // indice del figlio destro
    int massimo;
    
    /* Se l'indice del figlio sinistro è minore o uguale alla dimensione dell'array e l'elemento a sinistra con indice 'l'
     * è maggiore dell'elemento i-esimo l'elemento in post 'l' è il più grande */
    if(l <= h->size-1 && h->A[l] > h->A[i])
        massimo = l;
    else
        massimo = i;
    // Stessa cosa per il figlio a destra
    if(r <= h->size-1 && h->A[r] > h->A[massimo])
        massimo = r;
    /* ora l massimo è il massimo tra h->A[l], h->A[r], h.>A[i] */
    if(massimo!=i){
        scambia_caselle(h->A, i, massimo);
        max_heapify(h, massimo);
    }
}

void scambia_caselle(int* A, int i, int max){
    int temp = A[i];
    A[i] = A[max];
    A[max] = temp;
}

/* Funzione BUILD_MAX_HEAP, trasforma un array in un heap */
void build_max_heap(heap* h){   // HA COSTO THETA(N)
    
    int nodi_interni = h->size/2-1; // indice più basso del primo nodo interno
    
    for(int i=nodi_interni; i>=0; i--)
        max_heapify(h, i);
}

/* Funzione che verifica se l'heap è vuoto */
int is_empty(heap* h){  // COSTO THETA(1)
    return h->size==0;
}

/* Funzione che ritorna il massimo elemento di un heap se questo è un max_heapify */
int maximum(heap* h){
    return h->A[0];
}

/* Funzione che estrae il massimo elemento all'interno di un heap */
int extract_max(heap* h){   // la complessita è THETA(log n) nel caso peggiore -> quella di max_heapify
    /* se l'heap è vuoto */
    if(is_empty(h))
        printf("\nError \"Heap underflow\".");
    // Altrimenti
    int max = h->A[0];  // inizializzo max al primo elemento dell'array - ELIMINAZIONE PRIMO ELEMENTO DALLA CODA
    h->A[0] = h->A[h->size-1];  // l'ultimo valore lo metto al posto della radice - L'ULTIMO ELEMENTO VIENE MESSO AL SUO POSTO
    h->size = h->size-1;    // diminuisco la size di 1 - VIENE DECREMENTATA LA SIZE DELL'ARRAY
    max_heapify(h, 0);  // lancio max_heapify sulla radice fino a scendere
    return max;

}

/* Funzione che inserisce un valore all'interno dell'heap, in modo ordinato */
void insert(heap* h, int key){
    /* l'heap è pieno */
    if(h->size==4)
        printf("\nError \"overflow\"\n");
        //h->A = realloc(h->A, h->size*sizeof(int));  // raddoppia la dimensione dell'array
    // Altrimenti
    h->size = h->size+1;    // Aggiorno la size incrementandola (libero l'ultima cella)
    int i = h->size-1;      // risalgo (nuova cella allocata a size-1)
    while(i>0 && (h->A[parent(i)] < key)){
        h->A[i] = h->A[parent(i)];
        /* il genitore i-esimo è stato spostato più in basso */
        i = parent(i);
    }
    h->A[i] = key;
}

/* Funzione che riordina un heap */
void heap_sort(int* A, int dim){
    /* crea un nuovo heap */
    heap* new_heap = malloc(sizeof(heap));
    new_heap->A = A;
    new_heap->size = dim;
    build_max_heap(new_heap);   // trasformo questo array 'new_heap' in un heap
    for(int i = dim-1; i>=0; i--){
        scambia_caselle(A, 0, i);
        new_heap->size = new_heap->size-1;
        max_heapify(new_heap, 0);
    }
}

int main(int argc, char **argv)
{
    /* Crea un heap - vuole la dimensione */
    heap* heap_1 = newHeap(5);
    
    /* inserimento */
    add_number(heap_1, 5);
    add_number(heap_1, 4);
    add_number(heap_1, 3);
    add_number(heap_1, 2);
    add_number(heap_1, 1);
    
    /* Stampa l'heap */
    print_heap(heap_1);

    /* PARENT */
    printf("\nIl parent del nodo con indice 3 ha indice: %d.\n", parent(3));    // atteso 1
    
    /* LEFT - RIGHT */
    printf("\nIl nodo con indice 1 ha figlio sinistro con indice: %d.\n", left(1)); //   atteso indice: 3 (elemento con valore 2)
    printf("\nIl nodo con indice 1 ha figlio destro con indice: %d.\n", right(1)); //    atteso indice: 4 (elemento con valore 1)
    
    /* INSERT */
    insert(heap_1, 10);
    print_heap(heap_1); // [10][4][5][2][1][3]
    
    /* Crea un heap - vuole la dimensione */
    heap* heap_2 = newHeap(5);
    
    /* inserimento */
    add_number(heap_2, 2);
    add_number(heap_2, 4);
    add_number(heap_2, 3);
    add_number(heap_2, 5);
    add_number(heap_2, 1);
    
    /* Stampa l'heap */
    print_heap(heap_2);
    
    /* MAX_HEAP */
    max_heapify(heap_2, 0);

    /* Stampa l'heap */
    printf("\nMAX_HEAPIFY:\n");
    print_heap(heap_2);
    
    printf("\nBUILD_MAX_HEAP:\n");
    
    /* BUILD_MAX_HEAP */
    build_max_heap(heap_2);
    print_heap(heap_2); // Stampa l'array 'heap_2' ordinato [5][4][3][2][1]
    
    printf("\nEXTRACT_MAX: ");

    /* EXTRACT_MAX */
    printf("%d\n", extract_max(heap_2)); // 5
    
    /* Creo un array */
    printf("\n===== ARRAY PER HEAP_SORT =====\n");
    int array[] = {4,2,3,5,1};
    
    printf("\nStampa array inserito:\n");
    
    printf("\n[");
    for(int i=0; i<5; i++){
        printf("%d ", array[i]);
    }
    printf("]\n");
    
    heap_sort(array, 5);
    
    printf("\nStampa array dopo HEAP_SORT.\n");
    printf("\n[");
    for(int i=0; i<5; i++){
        printf("%d ", array[i]);
    }
    printf("]\n");
    
}
