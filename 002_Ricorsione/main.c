#include <stdio.h>

/* Funzioni ricorsive */

/* ======================================================================================================= */

/*
 * Esercizio 7 (NumeroPositivi) Scrivere un programma che prende in input 
 * una sequenza di interi e calcola e restituisce il numero di valori positivi nella sequenza. 
 * Definire una funzione ricorsiva per il calcolo del numero 
 * di elementi positivi in una sequenza.
 */

/* REALIZZAZIONE 1 */
int numeroPositivi_1(int A[], int length){
	int count;
	
	/* Passo base */
	if(length==0)
		count = 0;
	else	// Passo ricorsivo
		/* Il valore corrente è positivo */
		if(A[length-1]>0)
			count = 1 + numeroPositivi_1(A, length-1);
		else	// Altrimenti il valore corrente non è positivo
			count = numeroPositivi_1(A, length-1);
			
	return count;
}

/* REALIZZAZIONE 2 */
int numeroPositiviRic_2(int A[], int length, int indice){
	int count;
	
	/* Passo base */
	if(length==indice)
		count = 0;
	else	// Passo ricorsivo
		/* Il valore corrente è positivo */
		if(A[indice]>0)
			count = 1 + numeroPositiviRic_2(A, length, indice+1);
		else	// Altrimenti il valore corrente non è positivo
			count = numeroPositiviRic_2(A, length, indice+1);
			
	return count;
}

int numeroPositivi_2(int A[], int length){
	return numeroPositiviRic_2(A, length, 0);
}

/* REALIZZAZIONE 3 */
int numeroPositivi_3(int A[], int length){
	int count;
	
	/* Passo base */
	if(length==0)
		count = 0;
	else	// Passo ricorsivo
		/* Il valore corrente è positivo */
		if(A[0]>0)
			count = 1 + numeroPositivi_3(A+1, length-1);
		else	// Altrimenti il valore corrente non è positivo
			count = numeroPositivi_3(A+1, length-1);
	
	return count;
}

/* ======================================================================================================= */

/*
 * Esercizio 8 (ConsecutiviUguali) Scrivere un programma che prende in input una sequenza di interi e verifica 
 * se nella sequenza esistono due interi consecutivi uguali utilizzando una funzione ricorsiva.
 */

/* REALIZZAZIONE 1 */

//int consecutiviUguali_1(int A[], int length){
	//int count;
	
	/* Passo base */
	//if(length==0)
	//	count = 0;
	//else	// Passo ricorsivo
		//count = 1 + (A[length-1]
//} 

/* ======================================================================================================= */

/*
 * Esercizio 9 (Multiplodi3Positivo) Scrivere un programma che prende in input una sequenza di interi e 
 * verifica se nella sequenza esiste un intero positivo e multiplo di 3 utilizzando una funzione ricorsiva.
 */
 
/* REALIZZAZIONE 1 */
int multiplodi3Positivo1(int A[], int length){
	int multiplo;
	
	/* Passo base */
	if(length==0)
		multiplo = 0;
	else	// Passo ricorsivo
		/* Il valore corrente è multiplo di 3 */
		if(A[length-1]>0 && A[length-1]%3==0)	// verifica se il valore corrente è positivo e multiplo di 3
			multiplo = 1;
		else	// Altrimenti il valore corrente non è positivo
			multiplo = multiplodi3Positivo1(A, length-1);
	
	return multiplo;
}

/* REALIZZAZIONE 2 */
int multiplodi3Positivo_RIC2(int A[], int length, int indice){
	int multiplo;
	
	/* Passo base */
	if(length==indice)
		multiplo = 0;
	else	// Passo ricorsivo
		if(A[indice]>0 && A[indice]%3==0)	// verifica se il valore corrente è positivo e multiplo di 3
			multiplo = 1;
		else	// Altrimenti il valore corrente non è positivo
			multiplo = multiplodi3Positivo_RIC2(A, length, indice+1);
	
	return multiplo;
}

int multiplo3Positivo2(int A[], int length){
	return multiplodi3Positivo_RIC2(A, length, 0);
}

/* REALIZZAZIONE 3 */
int multiplodi3Positivo3(int A[], int length){
	int multiplo;
	
	/* Passo base */
	if(length==0)
		multiplo = 0;
	else	// passo ricorsivo
		if(A[0]>0 && A[0]%3==0)	// verifica se il valore corrente è positivo e multiplo di 3
			multiplo = 1;
		else
			multiplo = multiplodi3Positivo3(A+1,length-1);
	
	return multiplo;
}

int main(int argc, char **argv)
{
	int length = 5;	// dimensione dell'array
	
	int A[length];	// l'Array
	for(int i=0; i<length; i++){
		printf("\nInserisci il %d° intero: ", i+1);
		scanf("%d", &A[i]);
	}
	
	/* Stampa array */
	printf("\n======================\n");
	printf("\nStampa array: \n");
	for(int i=0; i<length; i++){
		printf("[%d] ", A[i]);
	}
	
	/* NUMERO POSITIVO */
	printf("\n\n==========================================================\n");
	printf("\nNUMERO_POSITIVI R1: %d.\n", numeroPositivi_1(A, length));
	printf("NUMERO_POSITIVI R2: %d.\n", numeroPositivi_2(A, length));
	printf("NUMERO_POSITIVI R3: %d.\n", numeroPositivi_3(A, length));
	printf("\n==========================================================\n");
	
	/* NUMERO MULTIPLODI3POSITIVO */
	printf("\n\n==========================================================\n");
	printf("\nMULTIPLODI3POSITIVO R1: %d.\n", multiplodi3Positivo1(A, length));
	printf("MULTIPLODI3POSITIVO R2: %d.\n", multiplo3Positivo2(A, length));
	printf("MULTIPLODI3POSITIVO R3: %d.\n", numeroPositivi_3(A, length));
	printf("\n==========================================================\n");
}
