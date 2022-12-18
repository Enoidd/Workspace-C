#include <stdio.h>
#include <stdlib.h>

/* Struttura nodo della lista */
typedef struct l{
    int info;
    struct l* next;
}elist;

typedef elist* plist;   // lista

/* Funzione che crea una lista */
plist new_lista(){
    plist new = malloc(sizeof(plist));  // alloca memoria per una nuova lista
    new = NULL; // lista vuota

    return new;
}

/* Funzione che stampa una lista */
void print_lista(plist l){
    if(l==NULL){
        printf("\nError underflow. Lista vuota. Print fallita.\n");
        return;
    }
    // Lista non vuota
    while(l!=NULL){
        printf("[%d]--", l->info);
        l = l->next;    // passa al prossimo nodo della lista
    }
    printf("NULL\n");
}

int main(){

    /* Lista l1 */
    plist l1 = new_lista();

    print_lista(l1);    // Atteso: Error underflow. Lista vuota. Print fallita.
}