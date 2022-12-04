#include <stdio.h>
#include <stdlib.h>	// adesso puoi usare malloc, calloc, realloc
CIAO
/* ====================== QUARTO HOMERWORK ====================== */

/* La funzione ritorna 1 se esattamente due elementi di A sono anche elementi di B, ritorna 0
 * se B contiene un numero di elementi di A diverso da 2 ex. 0, 1, 3, 4 
 */
int dueComuni(int A[], int lA, int B[], int lB){
	int count = 0;	// Variabile contatore 

	for(int i=0; i<lA; i++){	// scorri 'A'
		for(int j=0; j<lB; j++){	// scorri'B'
			/* confronta gli elementi di 'A' con quelli di 'B' */
			if(A[i]==B[j]){
				/* se sono uguali */
				count++;	// aggiorna il contatore
			}
		}
	}
	if(count==2)
		count = 1;
	else
		count = 0;
	
	return count;
}

/*
 * Scrivi la funzione in linguaggio C int originale(int* A, int lenA, int* B, int lenB) che
 * accetta in input due array A e B di interi e le loro lunghezze lenA e lenB.
 * La funzione ritorna 1 (true) se l'array A contiene almeno un elemento che non è nell'array B e
 * ritorna 0 (false) se tutti gli elementi di A sono in B. Se A ha lunghezza zero la funzione ritorna 0 (false)
*/
int originale(int* A, int lenA, int* B, int lenB) {
	/* HP. Verifica Universale */
	
}

/* ============================================================== */
int main(int argc, char **argv)
{
	int lA = 5;
	int lB = 4;
	
	/* Per Array 'A' */
	printf("\nINSERIMENTO ARRAY 'A'\n");
	int A[lA];
	for(int i=0; i<lA; i++){
		printf("\nInserisci il %d° intero: ", i+1);
		scanf("%d", &A[i]);
	}
	
	/* Per Array 'B' */
	printf("\nINSERIMENTO ARRAY 'B'\n");
	int B[lB];
	for(int i=0; i<lB; i++){
		printf("\nInserisci il %d° intero: ", i+1);
		scanf("%d", &B[i]);
	}
	
	/* Array A */
	printf("\n\n=== STAMPA ARRAY 'A' ===\n");
	for(int i=0; i<lA; i++){
		printf("[%d]", A[i]);
	}
	printf("\n\n");
	
	
	/* Array B */
	printf("\n\n=== STAMPA ARRAY 'B' ===\n");
	for(int j=0; j<lB; j++){
		printf("[%d]", B[j]);
	}
	printf("\n\n");
	
	printf("Due_Comuni: %d.\n",dueComuni(A, lA, B, lB));
}