#include <stdio.h>
#include <stdlib.h>
#include "pila.h"

/* Funzione che crea una pila */
pila* new_pila(int size){
    /* Alloca memoria per la nuova pila di dimensione size */
    pila* out = malloc(sizeof(pila));
    out->top = -1;  // inizialmente la pila è vuota
    out->size = size;
    out->A = (int*)calloc(size, sizeof(int));   // formatta tutti gli elementi della pila a 0
    
    return out;
}

/* Funzione che stampa una pila */
void print_pila(pila* p){
    
    /* scorri la pila */
    for(int i=0; i<p->size; i++){
        printf("[%d] ", p->A[i]);
    }
    printf("p->top: %d.\n", p->top);
}

/* Funzione che verifica se la pila è vuota */
int is_empty(pila* p){
    return p->top==-1;
}

/* Funzione che fa un push di un intero nella pila */
void push(pila* p, int x){
    /* Se la pila è piena */
    if(p->top==p->size-1){
        //printf("Error overflow, pila piena.\n");
		// Con gestione telescopica della pila
		p->size = p->size*2;
		p->A = (int*)realloc(p->A, p->size*sizeof(int));
		printf("\nMemoria raddoppiata, size: %d.\n", p->size);
	}
    // Altrimenti la pila non è piena
    p->top = p->top+1;  // incremento il p->top di 1, così da avere la posizione di inserimento
    p->A[p->top] = x;
}

/* Funzione che fa un pop di un intero nella pila */
int pop(pila* p){
    /* Se la pila è vuota */
    if(p->top==-1)
        printf("Error underflow, pila vuota.\n");
    // Altrimenti c'è almeno un elemento
    p->top = p->top-1;  // decrementa il p->top in modo tale da escludere l'elemento in superficie
    return p->A[p->top+1];  // ritorna l'elemento che hai escluso 
}

/* Funione che permette di leggere l'elemento affiorante della pila */
int top(pila* p){
    return p->A[p->top];
}

/* Funzione che svuota la pila */
void empty(pila* p){
    //free(p->A); // Per rimuovere la pila dal heap
    //free(p);    // Per rimuovere la pila 
}

/* Funzione che calcola il numero di elementi presenti nella pila */
int size(pila* p){
	return p->top+1;
}

/* Funzione che verifica se un elemento è contenuto nella pila */
int contains(pila* p, int x){
	
	int trovato = 0;
	/* Se la pila è vuota */
	if(p->top==-1)
		printf("\nError underflow. Pila vuota.\n");
	// Altrimenti pila non vuota
	/* Scorri la pila */
	for(int i=0; i<p->size; i++){
		/* L'elemento corrente è quello cercato? */
		if(p->A[i] == x)
			trovato = 1;
	}
	return trovato;
}