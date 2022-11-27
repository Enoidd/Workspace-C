#ifndef _CODA_H
#define _CODA_H

/* Struttura che definisce una coda */
typedef struct cd{
	int* A;
	int size;
	int head;
	int tail;
}coda;

/* Dichiarazine funzione che crea una coda di interi */
coda* new_coda(int size);

/* Dichiarazione funzione che stampa la coda*/
void print_coda(coda* c);

/* Dichiarazione funzione che verifica se la coda è vuota */
int is_empty(coda* c);

/* Dichiarazione funzione che fa un inserimento in coda */
void enqueue(coda* c, int x);

/* Dichiarazione funzione che fa una cancellazione dalla coda */
int dequeue(coda* c);

/* Dichiarazione funzione che svuota la coda */
void empty(coda* c);

/* Dichiarazione funzione che ritorna il primo elemento in coda */
int front(coda* c);

#endif