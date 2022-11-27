#include <stdio.h>

/* Selection sort */
void selection_sort(int* A, int lung){
    /* Scorri la sequenza a partire dall'i-esimo elemento fino al penultimo */
    for(int i=0; i<lung-1; i++){
        int min = i;
        /* Confronta l'i-esimo elemento con i successivi  fino all'ultimo */
        for(int j=i+1; j<lung; j++){
            /* L'elemento corrente j è minore del i-esimo? */
            if(A[j]<A[min])
                min = j;    // aggiorna il min all'indice i-esimo
            // Altrimenti non fare nulla
        }
        /* Hai visitato tutte gli elementi della seconda sottosequenza */
        /* Fai lo scambio */
        int temp = A[i];
        A[i] = A[min];
        A[min] = temp;
    }
}

/* Isertion sort */
void insertion_sort(int* A, int lung){
    /* Scorri tutta la sequenza a partire dal 2° elemento */
    for(int i=1; i<lung; i++){
        int key = A[i]; // memorizza in key il valore del 2° elemento
        int j = i-1;    // j parte dal 1° elemento
        while(j>=-1 && A[j]>key){   // fintanto che j è valida e che l'elemento che precede quello corrente del for è maggiore del successivo (key)
            A[j+1] = A[j];  // scambiali
            j = j-1;
        }
        A[j+1] = key;
    }
}

int main(int argc, char **argv)
{
	int lung;   // Dimensione dell'array
    /* Leggi quanti interi si vuole inserire */
    printf("\nQuanti interi vuoi introdurre?\n");
        scanf("%d", &lung);
        
    int A[lung];    // Dichiarazione array 'A'
    /* Leggi quali interi si vuole inserire */
    for(int i=0; i<lung; i++){
        printf("Inserisci il %d%c intero: ", i+1, 167);
        scanf("%d", &A[i]);
    }
    
    printf("\nSelection sort\n");
    /* Invocazione funzione selection sort */
    selection_sort(A, lung);
    
    /* prova di stampa */
    printf("\n");
    for(int i=0; i<lung; i++){
        printf("[%d]", A[i]);
        printf(" ");
    }
    printf("\n");
    
    printf("\nInsertion sort\n");
    /* Invocazione funzione insertion sort */
    insertion_sort(A, lung);
    
    /* prova di stampa */
    printf("\n");
    for(int i=0; i<lung; i++){
        printf("[%d]", A[i]);
        printf(" ");
    }
    printf("\n");
}
