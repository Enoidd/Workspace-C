#include <stdio.h>
#include "pila.h"

/* PILE
 * Strategia: LIFO (Last in first out, l'ultimo che arriva è il primo ad uscire)
 * Una pila viene realizzata tramite un Array di interi
 */

int main(int argc, char **argv)
{
	/* crea una nuova pila */
    pila* pila1 = new_pila(5);
    
    /* Stampa pila */
    print_pila(pila1); // Atteso: Error underflow, pila vuota. Niente da stampare.
    
    /* Verifica se la pila è vuota */
    if(is_empty(pila1))
        printf("Pila vuota.\n"); // Atteso
    else
        printf("Pila non vuota.\n");
        
    /* ========== PUSH  ========== */
    printf("\n===== PUSH =====\n");
    push(pila1, 1); // p->top = 0
    push(pila1, 3); // p->top = 1
    push(pila1, 2); // p->top = 2
    push(pila1, 4); // p->top = 3
    
    print_pila(pila1);  // [1][3][2][4] p->top: 3
    
    /* Verifica se la pila è vuota */
    if(is_empty(pila1))
        printf("Pila vuota.\n");
    else
        printf("Pila non vuota.\n"); // Atteso
    
        
    /* ========== POP ========== */
    printf("\n===== POP =====\n");
    pop(pila1);
    pop(pila1);
    
    print_pila(pila1);  // [1][3][2][4] p->top: 1

    /* =========== TOP =========== */
    printf("\n-Elemento affiorante della pila (Funzione TOP): %d.\n", top(pila1));
    
    /* Invocazione funzione che svuota la pila */
    //empty(pila1);
    
    //print_pila(pila1);
    
    /* Crea una pila */
	pila* pila2 = new_pila(4);
	
	/* Invoca la funzione che calcola il numero di elementi presenti */
	printf("Elementi presenti in pila: %d.\n", size(pila2));	// atteso 0
	
	push(pila2, 1);
	push(pila2, 3);
	push(pila2, 2);
	push(pila2, 5);
	push(pila2, 9);
	
	/* Invoca la funzione che calcola il numero di elementi presenti */
	printf("Elementi presenti in pila: %d.\n", size(pila2));	// atteso 4
	
	/* Contains */
	printf("\n===== CONTAINS =====\n");
	int valore_cercato; 
	printf("\nInserisci un intero che vuoi cercare nella pila: ");
	scanf("%d", &valore_cercato);
	
	if(contains(pila2, valore_cercato))
		printf("\nIl valore: %d, è presente nella pila.\n", valore_cercato);
	else
		printf("\nIl valore: %d, non è presente nella pila.\n", valore_cercato);
}
