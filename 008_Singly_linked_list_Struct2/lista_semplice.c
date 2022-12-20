#include <stdio.h>
#include <stdlib.h>

/* Struttura nodo della lista */
typedef struct nodo{
    int info;
    struct nodo* next;
}nodo; // nodo è il nodo della lista

typedef nodo* lista;   // plist è un puntatore a elist

/* Funzione che crea una lista */
lista new_lista(){
    lista  new = malloc(sizeof(lista));  // alloca memoria per una nuova lista
    return new;
}

/* Funzione che crea un nodo */
nodo* node_new(){
  nodo* n = (nodo*)malloc(sizeof(nodo));
  n->next=NULL;
  return n;
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
    nodo* new = node_new();

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
int somma(lista* l){
    int somma = 0;
    if((*l)!=NULL){
        nodo* i = (*l);
        while(i!=NULL){
            somma += i->info;
            i = i->next;
        }
    }
    return somma;
}


/* Funzione che verifica se un nodo contenente valore 'u' esiste nella lista */
int search(lista* l, int u){
    int esiste = 0;
    if((*l)!=NULL && esiste==0){
        nodo* i = (*l);
        while(i!=NULL){
            if(i->info==u)
                esiste = 1;
            i = i->next;
        }
    }
    return esiste;
}

/* PRE-ESAME */

/* Verifica se la lista ordinata in modo crescente */
int crescente(lista* l){
    int verificata = 1;
    if((*l)==NULL)
        verificata = 0;
    if((*l)->next==NULL)
        verificata = 1;
    nodo* i = (*l);
    while(i->next!=NULL && verificata){
        if(i->info > i->next->info){
            verificata = 0;
        }
        i = i->next;   
    }
    return verificata;
}

/* Verifica se il primo e l'ultimo nodo sono uguali */
int primo_ultimo(lista* l){
    if((*l)==NULL) return 0;
    int v = (*l)->info;
    nodo* i = (*l);
    while(i->next!=NULL){
        i = i->next;
    }
    return i->info == v;
}

/* Verifica se due valori consecutivi nella lista sono duplicati */
int consecutivi_uguali(lista* l){
    if((*l)==NULL) return 0;
    if((*l)->next==NULL) return 0;
    nodo* i = (*l);
    while(i->next!=NULL){
        if(i->info==i->next->info)
            return 1;
        else
            i = i->next;
    }
    return 0;
}

/* Verifica se esiste un nodo con campo info pari alla lunghezza della lista */
int info_lunghezza(lista* l){
    if((*l)==NULL) return 0;
    int count = 0;
    nodo* i = (*l);
    while(i!=NULL){
        count++;
        //printf("\nCount: %d.\n", count); DEBUG
        i = i->next;
    }
    nodo* j = (*l);
    while(j->next!=NULL){
        if(count == j->info)
            return 1;
        j = j->next;
    }
    return 0;
}

/* Conta quanti sono i nodi minori del successivo */
int minori_successivo(lista* l){
    if((*l)==NULL) return 0;

    int count = 0;
    nodo* i = (*l);
    while(i->next!=NULL){
        if(i->info <= i->next->info)
            count++;
        i = i->next;
    }
    return count;
}

/* HOMEWORK */


/* Verifica se tutti i nodi della lista hanno valore positivo */
int tuttiPositivi(lista* l){
    if((*l)==NULL) return 0;
    
    int tuttiPos = 1;
    nodo* i = (*l);
    while(i!=NULL && tuttiPos){
        if(i->info < 0)
            tuttiPos = 0;
        else
            i = i->next;
    }
    return tuttiPos;
}

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

    /* TUTTI POSITIVI */
    printf("\nVerifico se tutti i nodi della lista hanno campo info positivo |si(1)/no(0)|, calcolato: %d.\n", tuttiPositivi(&l1));

    /* MINORI DEL SUCCESSIVO */
    printf("\nVerifico quanti sono i nodi con valore minore del nodo successivo, calcolato: %d.\n", minori_successivo(&l1));

    /* CONSECUTIVI UGUALI */
    printf("\nControllo esistenza due consecutivi uguali(1-Si/0-No), calcolato: %d.\n", consecutivi_uguali(&l1));

    /* INFO_LUNGHEZZA */
    printf("\nVerifico se esiste un nodo con campo info pari alla lunghezza della lista, valore calcolato: %d.\n", info_lunghezza(&l1));
    
    /* MASSIMO */
    printf("\nMassimo valore calcolato: %d.\n", massimo(&l1));

    /* SEARCH */
    printf("\nRicerca valore 5 nella lista, esiste(1)/non esiste(0), calcolato: %d.\n", search(&l1, 5));

    /* LISTA IN ORDINE CRESCENTE */
    printf("\nControllo se la lista e' ordinata in modo crescente, in ordine crescente(1)/non e' in ordine crescente(0), calcolato: %d.\n", crescente(&l1));

    /* PRIMO_ULTIMO UGUALI */
    printf("\nIl primo nodo è uguale(1), non è uguale(0) all'ultimo nodo, valore calcolato: %d.\n", primo_ultimo(&l1));

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

    /* SOMMA */
    printf("\nSOMMA dei valori contenuti nella lista: %d.\n", somma(&l1));
}