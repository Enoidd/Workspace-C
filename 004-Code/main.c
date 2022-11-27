#include <stdio.h>
#include "coda.h"

/* CODE: Realizzano la strategia FIFO (First in first out, il primo ad entrare è il primo ad uscire)
 */

int main(int argc, char **argv)
{
	/* Creazione coda di interi */
	coda* coda1 = new_coda(5);
	
	/* Stampa coda */
	print_coda(coda1);	// atteso: Error underflow, coda vuota. [0][0][0][0][0]
	
	/* Verifica se la coda è vuota */
	if(is_empty(coda1))
		printf("\nIS_EMPTY: Coda vuota.\n");	// atteso
	else
		printf("\nIS_EMPTY: Coda non vuota.\n");
		
	/* Enqueue */
	printf("\n===== ENQUEUE =====");
	enqueue(coda1, 2);
	printf("\n");
	print_coda(coda1);	// Atteso: [2][0][0][0][0] c->head: 0, c->tail 1
	enqueue(coda1, 4);
	print_coda(coda1);	// Atteso: [2][4][0][0][0] c->head: 0, c->tail 2
	enqueue(coda1, 6);
	print_coda(coda1);	// Atteso: [2][4][6][0][0] c->head: 0, c->tail 3
	enqueue(coda1, 8);
	print_coda(coda1);	// Atteso: [2][4][6][8][0] c->head: 0, c->tail 4
	enqueue(coda1, 10);
	print_coda(coda1); // Atteso: Error overflow, coda piena.
	
	/* Dequeue */
	printf("\n===== DEQUEUE =====");
	dequeue(coda1);
	printf("\n");
	print_coda(coda1);	// Atteso: [x][4][6][8][0] c->head: 1, c->tail: 4
	dequeue(coda1);
	print_coda(coda1);	// Atteso: [x][x][6][8][0] c->head: 2, c->tail: 4
	dequeue(coda1);
	print_coda(coda1);	// Atteso: [x][x][x][8][0] c->head: 3, c->tail: 4
	dequeue(coda1);
	print_coda(coda1);	// Atteso: [x][x][x][x][0] c->head: 0, c->tail: 4 (NB: Poiché 8 è l'ultimo elemento in coda c->head diventa '0')
	
	/* FRONT */
	printf("\nPrimo elemento in coda: %d.\n", front(coda1));
	
	
	/* Empty */
	printf("==== EMPTY ====\n");
	empty(coda1);
	printf("Coda svuotata.\n");
	
	/* IS_EMPTY -> Controlla che la coda è stata svuotata veramente */
	if(is_empty(coda1))
		printf("\nIS_EMPTY: Coda vuota.\n");
	else
		printf("\nIS_EMPTY: Coda non vuota.\n");	// Atteso
		
	enqueue(coda1, 1);
	print_coda(coda1);
	
}
