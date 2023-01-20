#include <stdio.h>
#include <stdlib.h>

typedef struct l{
    int info;
    struct l* next;
}lista;

typedef lista* elist;

/* Funzione che fa un inserimento in testa */
void inserisci_in_testa(lista** l, int v){
    lista* new = (lista*)malloc(sizeof(lista));
    new->info = v;
    new->next = *l;
    *l = new;
    
}

/* Funzione che fa un inserimento in coda */
void inserisci_in_coda(lista** l, int v){
    
    if((*l)==NULL){
        inserisci_in_testa(l, v);
        return;
    }
    
    lista* i = (*l);
    while(i->next!=NULL){
        i = i->next;
    }
    
    lista* new = (lista*)malloc(sizeof(lista));
    new->info = v;
    new->next = NULL;
    i->next = new;
}

/* Stampa lista */
void stampa_lista(elist l){
    printf("\n");
    if(l==NULL){
        printf("\nLista vuota.\n");
        return;
    }
    while(l!=NULL){
        printf("[%d]-->", l->info);
        l = l->next;
    }
    printf("NULL\n");
}

/* Lista crescente */
int lista_crescente(elist l){
    if(l==NULL){
        return 0;
    }

    if(l->next==NULL){
        return 1;
    }
    
    int verificata = 1;
    lista* i = l;
    while(i->next!=NULL && verificata){
        if(i->info > i->next->info)
            verificata = 0;
        i = i->next;
    }
    return verificata;
}

/* Primo e ultimo valore uguale */
int primo_ultimo_uguale(elist l){
    if(l==NULL){
        return 0;
    }

    if(l->next==NULL){
        return 0;
    }

    lista* temp = l;
    lista* i = l;
    while(i->next!=NULL){
        i = i->next;
    }
    if(i->info==temp->info)
        return 1;
    return 0;
}

/* Valore nodo uguale lunghezza lista */
int info_uguale_lunghezza(elist l){
    if(l==NULL){
        return 0;
    }

    int h_list = 0;
    lista* i = l;
    while(i!=NULL){
        h_list++;
        i = i->next;
    }
    printf("%d\n", h_list);

    i = l;
    while(i->next!=NULL){
        if(i->info==h_list)
            return 1;
        i = i->next;
    }
    return 0;
}

/* Esistono consecutivi uguali */
int esistono_consecutivi_uguali(elist l){
    if(l==NULL){
        return 0;
    }

    if(l->next==NULL){
        return 0;
    }
    lista* i = l;
    while(i->next!=NULL){
        if(i->info==i->next->info)
            return 1;
        else
            i = i->next;
    }
    return 0;
}


/* Numero nodi campo info minore del successivo */
int numero_nodi_minori_successivo(elist l){
    if(l==NULL){
        return 0;
    }

    int count = 0;
    lista* i = l;
    while(i->next!=NULL){
        if(i->info < i->next->info)
            count++;
        i = i->next;
    }
    return count;
}

int main(){

    elist l1 = NULL;

    inserisci_in_testa(&l1, 7);
    inserisci_in_testa(&l1, 1);
    inserisci_in_testa(&l1, 3);
    inserisci_in_coda(&l1, 2);
    inserisci_in_coda(&l1, 9);
    inserisci_in_coda(&l1, 8);
    
    /* Lista crescente */
    printf("\nLista crescente (atteso 1): %d.\n", lista_crescente(l1));

    /* Primo e ultimo valore della lista uguale */
    printf("\nPrimo e ultimo campo info uguale (atteso 1): %d.\n", primo_ultimo_uguale(l1));

    /* info uguale lunghezza */
    printf("\nInfo uguale lunghezza (atteso 1): %d.\n", info_uguale_lunghezza(l1));

    /* Esistono consecutivi uguali */
    printf("\nConsecutivi uguali (atteso 1): %d.\n", esistono_consecutivi_uguali(l1));

    /* Nodi minori del nodo successivo */
    printf("\nNodi minori del nodo successivo (atteso 1): %d.\n", numero_nodi_minori_successivo(l1));

    stampa_lista(l1);
    
}