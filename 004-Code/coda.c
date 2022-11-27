#include <stdio.h>
#include <stdlib.h>
#include "coda.h"

/* Funzione che crea una coda di interi */
coda* new_coda(int size){
	/* Alloca memoria per una nuova coda */
	coda* out = malloc(sizeof(int));
	out->head = 0;		// head punta alla casella di 'A' con indice 0, perché inizialmente la coda è vuota
	out->tail = 0;		// tail punta alla casella di 'A' con indice 0, perché inizialmente la coda è vuota
	out->size = size;	// Inizializza la size di 'A' a quella fornita come parametro
	/* Inizializza tutti gli elementi di'A' a 0 */
	out->A = (int*)calloc(size, sizeof(int));
	
	return out;
}

/* Funzione che stampa una coda di interi */
void print_coda(coda* c){
	
	/* Se la coda è vuota */
	if(c->head==c->tail)
		printf("\nError underflow, coda vuota.\n");
	// Altrimenti la coda non è vuota
	for(int i=0; i<c->size; i++){
		printf("[%d] ", c->A[i]);
	}
	printf("c->head: %d, c->tail: %d.\n", c->head, c->tail);
}

/* Funzione che verifica se la coda è vuota */
int is_empty(coda* c){
	return c->head==c->tail;
}

/* Funzione che fa un inserimento in coda */
void enqueue(coda* c, int x){
	
	/* Se la coda è piena */
	if((c->head==c->tail+1) || (c->tail==c->size-1 && c->head==0))
		printf("\nError overflow. Coda piena\n");
	else{	// altrimenti coda non piena
		c->A[c->tail] = x;	// metti in posizione c->tail di 'A' l'elemento 'x'
		/* se c->tail è l'ultima cella di 'A'*/
		if(c->tail==c->size-1)
			c->tail=0;	// riparti dalla 1° posizione
		else	// altrimenti non è l'ultima cella di 'A'
			c->tail = c->tail+1;	// incrementa il c->tail alla prossima cella che dovrà essere riempita
	}
}

/* Funzione che fa una cancellazione dalla coda */
int dequeue(coda* c){
	/* Se la coda è vuota */
	if(c->head==c->tail)
		printf("\nError underflow. Coda vuota.\n");
	// altrimenti la coda non è piena
	int valore_da_rimuovere = c->A[c->head];	// memorizza il valore da rimuovere in posizione c->head
	c->head = c->head+1;	// incrementa c->head al prossimo elemento da cancellare
	/* Se il valore rimosso è l'ultimo */
	if(c->head == c->size-1)
		c->head = 0;	// re-inizializza c->head a 0
			
	return valore_da_rimuovere;
}

/* Funzione che svuota la coda */
void empty(coda* c){
	c->head = 0;
	c->tail = 0;
}

/* Funzione che ritorna il primo elemento in coda */
int front(coda* c){
	/* Se la coda è vuota */
	if(c->head == c->tail)
		printf("\nEmpty queue\n");
	return c->A[c->head];
}