#include <stdio.h>
#include <stdlib.h>
#include "../003_Pile/pila.h" // Adesso puoi usare le funzioni in 003_Pile


/* Struttura che contiene due pile di tipo pila */
typedef struct ppi{
	pila* p1;
	pila* p2;
}pp;

/* Funzione NEW_QUEUE che crea due pile p1 e p2 di dimensione 'size' fornita */
pila* new_queue(int size){
	/* Alloca memoria per una pila */
	struct ppi* out = malloc(sizeof(pp));
	out->p1 = new_pila(size);	// crea la pila p1 di dimensione size
	out->p2 = new_pila(size);	// crea la pila p2 di dimensione size
	
	return out;	// ritorna le pile
}

int main(int argc, char **argv)
{
	printf("hello world\n");
	return 0;
}
