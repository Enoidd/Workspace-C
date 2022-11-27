#ifndef _PILA_H
#define _PILA_H

/* Struttura dati pila */
typedef struct pi{
    int* A; // array
    int size;   // dimensione array
    int top;    // indice dell'elemento affiorante
} pila;

/* Dichiarazione funzione che crea una nuova pila */
pila* new_pila(int size);

/* Dichiarazione funzione che stampa una nuova pila */
void print_pila(pila* p);

/* Dichiarazione funzione che verifica se la pilaè vuota */
int is_empty(pila* p);

/* Dichiarazione funzione che fa un PUSH di un elemento nella pila */
void push(pila* p, int x);

/* Dichiarazione funzione che fa un POP dell'elemento affiorante dalla pila */
int pop(pila* p);

/* Dichiarazione funione che permette di leggere l'elemento affiorante della pila */
int top(pila* p);

/* Dichirazione funzione che svuota una pila */
void empty(pila* p);

/* Dichiarazione funzione che calcola il numero di elementi presenti nella pila */
int size(pila* p);

/* Dichiarazione funzione che verifica se un elemento è contenuto nella pila */
int contains(pila* p, int x);

#endif
