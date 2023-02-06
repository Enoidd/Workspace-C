/*
Una coda di priorità viene realizzata tramite l'heap.

- Cos'è una coda di priorità?
- Una coda di priorità o priority queue è una collezione di elementi, dove ad ogni elemento è associato un valore di 
  priorità.

== COMPLESSITA' ==

- Si potrebbe realizzare un heap tramite liste.

Caso lista non ordinata.  In questo caso per aggiungere un elemento avremmo una complessità
Theta(n), mentre la rimozione dell'elemento a priorità più alta Theta(1)

Caso lista ordinata. In questo caso per aggiungere un elemento in TESTA avrebbe una complessità Theta(1),
mentre la ricerca e rimozione di un elemento a più alta priorità Theta(n)

====> lo "scopo" degli heap è bilanciare i due costi.

== COME E' FATTO UN HEAP ==

Rappresentano alberi binari quasi completi, ossia che risulta incompleto nel suo ultimo livello sulla parte destra

E' una struttura: che può essere utilizzata per realizzare code di priorità / i valori contenuti nell'array sono
in rapporto con la loro posizione / può essere un max heap o un min heap 

*/


#include <stdio.h>
#include <stdlib.h>

/* Struttura coda di prorità */
typedef struct coda_priorita{
  int size;
  int* A;
}heap;

/* Funzione che aggiunge un elemento nella coda di priorità */
heap* new_heap(int size){
  heap* h = (heap*)malloc(sizeof(heap));  // un nuovo heap che punta all'array
  h->A = malloc(size*sizeof(heap));  // l'array
  h->size = 0;  // dimensione iniziale 0

  return h;
}

/* Funzione che aggiunge un elemento nella coda di prorità */
void add_number_heap(heap* h, int value){
  /* Coda di proprità piena */
  if(h->size==5)
    h->A = realloc(h->A, h->size*sizeof(int));  // raddoppia la memoria

  // quando sei qui hai raddoppiato la memoria oppure heap non pieno
  h->A[h->size] = value;
  h->size = h->size+1;  // passa al prox elemento dell'array
}

/* Funzione che stampa l'array */
void print_heap(heap* h){
  printf("\n===== HEAP =====\n");
  for(int i=0; i<h->size; i++){
    printf("[%d] %d\n", h->A[i], i);
  }
  printf("\n================\n");
}

/* Operazioni sulle code di priorità */

/* Ritorna il parent del nodo 'i' */
int parent(int i){
  return (i-1)/2;
}

/* Ritorna l'indice del figlio sinistro di 'i' */
int left(int i){
  return 2*i+1;
}

/* Ritorna l'indice del figlio destro di 'i' */
int right(int i){
  return 2*i+2;
}

/* Appoggio MAX_HEAP */
void scambia_caselle(int* A, int i, int maximum);

/* MAX_HEAP trasforma un sottoalbero radicato a 'i' in un MAX_HEAP */
void max_heapify(heap* h, int i){
  int l = left(i);  // indice figlio sx
  int r = right(i); // indice figlio dx
  int maximum;

  if(l <= h->size-1 && h->A[l] > h->A[i])
    maximum = l;
  if(r < h->size-1 && h->A[r] > h->A[maximum])
    maximum = r;
  if(maximum != i){
    scambia_caselle(h->A, i, maximum);
    max_heapify(h, maximum);
  }
}

void scambia_caselle(int* A, int i, int maximum){
    int temp = A[i];
    A[i] = A[maximum];
    A[maximum] = temp;
}

/* Funzione che trasforma un array in un heap */

/* BUILD_MAX_HEAP esegue MAX_HEAPIFY su nodi che non sono foglie dal basso verso l'alto */
void build_max_heap(heap* h){
  
  int nodi_interni = h->size/2-1;
  for(int i=nodi_interni; i>=0; i--){
    max_heapify(h, i);
  }
}


int main(){

  heap* h1 = new_heap(5); // creazione heap didimensione 5

  add_number_heap(h1, 2);
  add_number_heap(h1, 3);
  add_number_heap(h1, 4);
  add_number_heap(h1, 5);
  add_number_heap(h1, 6);

  print_heap(h1);

  printf("\n===== MAX_HEAP =====\n");
  max_heapify(h1, 0);
  print_heap(h1);
}