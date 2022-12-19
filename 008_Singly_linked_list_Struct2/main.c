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
    if(l==NULL){
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
    nodo* new = malloc(sizeof(lista));
    new->info = v;
    new->next = *l;
    *l = new;
}

/* Funzione che inserisce un elemento in coda alla lista  */
void add(lista* l, int v){
    if((*l)==NULL){
        insert(l, v);
        return;
    }
    nodo* i = (*l); // per scorrere la lista
    while(i->next!=NULL){
        i = i->next;
    }
    nodo* out = malloc(sizeof(nodo));
    out->info = v;
    out->next = NULL;
    i->next = out;
}

/* Funzione che fa una cancellazione in testa */
int delete_head(lista* l){
    if((*l)==NULL)
        printf("\nError underflow. Lista vuota, cancellazione in coda.\n");
    nodo* temp = (*l);
    int v = (*l)->info;
    (*l) = (*l)->next;
    free(temp);

    return v;
}


/* Funzione che fa una cancellazione in coda */
int delete_tail(lista* l){
    if((*l)==NULL){
        printf("\nError underflow. Lista vuota, cancellaione in coda fallita.\n");
    }
    if((*l)->next==NULL)
        return delete_head(l);
    nodo* i = (*l);
    while(i->next->next!=NULL){
        i = i->next;
    }
    nodo* temp = i->next;
    int v = i->next->info;
    i->next = NULL;
    free(temp);

    return v;
}

/* Funzione che verifica se una lista è vuota */
int is_empty(lista* l){
    return (*l)==NULL;
}

/* Funzione che svuota la lista */
lista* empty(lista* l){
    if((*l)==NULL){
        printf("\nSvuotamento lista fallito. Lista vuota.\n");
    }
    nodo* i = (*l);
    while(i!=NULL){
        nodo* temp = i;
        i = i->next;
        free(temp);
    }
    return NULL;
}

/* Funzione che ritorna il massimo valore contenuto nella lista */
int massimo(lista* l){
    int max;
    if((*l)==NULL){
        printf("\nCalcolo del massimo fallito. Lista vuota.\n");
    }
    nodo* i = (*l);
    max = i->info;
    while(i->next!=NULL){
        if(i->info>=max)
            max = i->info;
        i = i->next;
    }
    return max;
}

/* Funzione che ritorna la somma dei valori contenuti nei nodi della lista */

int main(){

    /* Lista l1 */
    nodo* l1 = new_lista();

    print_lista(l1);    // Atteso: Error underflow. Lista vuota. Print fallita.

    /* IS_EMPTY */
    printf("\nIS_EMPTY: %d.\n\n", is_empty(&l1)); // atteso: 0

    /* Inserimenti in testa a 'l1' */
    insert(&l1, 1);
    add(&l1, 2);
    add(&l1, 3);
    insert(&l1, 4);

    print_lista(l1);    // [4]---[1]---[2]---[3]---NULL
    printf("\nMassimo valore calcolato: %d.\n", massimo(&l1));
    /* Cancellazione in testa a 'l1' */
    delete_head(&l1);

    print_lista(l1);    // [1]---[2]---[3]---NULL

    /* Cancellazione in coda di 'l1' */
    delete_tail(&l1);
    printf("\n");
    print_lista(l1);    // [1]---[2]---NULL

    /* IS_EMPTY */
    printf("\nIS_EMPTY: %d.\n\n", is_empty(&l1)); // atteso: 0
    
    /* MASSIMO */
    printf("\nMassimo valore calcolato: %d.\n", massimo(&l1));
}