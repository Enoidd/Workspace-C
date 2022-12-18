#include <stdio.h>
#include <stdlib.h>

/* Struttura nodo della lista */
typedef struct nodo{
    int info;
    struct nodo* next;
}nodo; // elist è il nodo della list 

typedef nodo* lista;   // plist è un puntatore a elist

/* Funzione che crea una lista */
lista new_lista(){
    lista  new = malloc(sizeof(lista));  // alloca memoria per una nuova lista
    new = NULL; // lista vuota

    return new;
}

/* Funzione che stampa una lista */
void print_lista(lista  l){
    if(*(&l)==NULL){
        printf("\nError underflow. Lista vuota. Print fallita.\n\n");
        return;
    }
    // Lista non vuota
    while(l!=NULL){
        printf("[%d]--", l->info);
        l = l->next;    // passa al prossimo nodo della lista
    }
    printf("NULL\n");
}

/* Funzione che inserisce un elemento in testa alla lista */
void insert(lista* l, int v){
    nodo* new = malloc(sizeof(lista ));
    new->info = v;
    new->next = *l;
    *l = new;
}

int main(){

    /* Lista l1 */
    nodo* l1 = new_lista();

    print_lista(l1);    // Atteso: Error underflow. Lista vuota. Print fallita.

    /* Inserimenti in testa a 'l1' */
    insert(&l1, 1);
    insert(&l1, 2);
    insert(&l1, 3);

    print_lista(l1);    // [3]---[2]---[1]---NULL
    
   
}