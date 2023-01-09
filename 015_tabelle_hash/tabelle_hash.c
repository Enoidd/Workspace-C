#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct nodo{
    int key;    // valore della chiave
    int info;   // valore associato alla chiave
    struct nodo* next;  // riferimento al prossimo nodo della lista
}nodo_lista;


/* 
 * La dimensione 'm' dell'array 'T':
 * - è < della dimensione dell'Universo K (possibili chiavi) 
 * - è molto vicina al numero delle chiavi effettivamente utilizzate 
 */
/* Si definisce fattore di carico il rapporto α tra il numero n di elementi memorizzati e il numero
 * m di posizioni disponibili, quindi α=n/m:
 * - α<1 molte posizioni disponibili rispetto agli elementi memorizzati 
 * - α=1 il numero di elementi corrisponde al numero delle posizioni disponibili
 * - α>1 molti elementi da memorizzare rispetto al numero delle posizioni disponibili*/
typedef struct hashtable{
    int m;  // Dimensione dell'array
    int n;  // Elementi memorizzati
    nodo_lista** T; // Array
    double alpha;   // numero di elementi memorizzati in ogni lista
}hashtable;

hashtable* new_table(){
    hashtable* table = (hashtable*)malloc(sizeof(hashtable));
    table->m = 4;   // Dimensione tabella
    table->n = 0;   // Tabella con 0 elementi
    table->T = (nodo_lista**)calloc(table->m, sizeof(nodo_lista*)); // alloca memoria per l'array 'T' di dimensione 'm'
    table->alpha = (sqrt(5.0)-1.0)*0.5;

    return table;
}

/* ========== Funzioni per gli hash  ========== */

/* Funzione Mod_hash, utilizza il resto della divisione intera */
int mod_hash(int k, int m){
    return k%m;
}

/* Funzione Mul_hash, riceve in input l'array associativo 'A' (per avere 'm' e 'alpha') e la chiave 'k' */
int mul_hash(hashtable* a, int k){
    int m = a->m;   // lunghezza dell'array
    double irr = k*a->alpha;        // reale in (0, m)
    int prodotto=m*(k*irr-(int)(k*irr));    // intero in [0, m-1]

    return prodotto;
}

/* Funzione simple_hash si utilizza per le stringhe, ritorna un numero intero che poi deve essere ridotto nell’intervallo [0…m-1] 
 * con la funzione MOD_HASH. Veloce ma generalmente considerato poco efficace nel distribuire i valori in modo pseudocausuale, 
 * ad esempio perchè permutazioni di caratteri hanno lo stesso hash */
int simple_hash(char s[]){
    int hash = 0;
    for(int i=0; i<strlen(s); i++)
        hash = hash + s[i];
    return hash;
}


/* Funzione djb2_hash, il numero 5381 è un numero primo, il "magic number" 33 non è giustificato teoricamente ma da ottimi risultati nella pratica
 * corrisponde al prodotto * 32 (traslazione di cinque caselle della rappresentazione) + un incremento di uno */
int djb2_hash(char s[]){
    int hash = 5381;
    for(int i=0; i<strlen(s); i++)
        hash = hash*33 + s[i];
    return hash;
}

/* ================================================ */

/* Funzione equal, che verifica se due valori sono uguali ritorno ture o false */
int equal(int k1, int k2){
    return k1==k2;
}

/* Funzione che ritorna il valore associato alla chiave o NULL */
int GET(hashtable* t, int k){
    int i = mod_hash(k, t->m);    // ritorna l'iteratore nell'array da cui parte 
    nodo_lista* lista = t->T[i];    // iteratore per elementi della lista T[i]
    while(lista!=NULL)
        if(equal(k, lista->key))
            return lista->info; // l'ho trovato
        lista = lista->next;
    
    return NULL;
}

/* Funzione che fa un inserimento di una coppia chiave, valore */
void put(hashtable* t, int key, int value){
    int i = mod_hash(key, t->m);  // cerca nella lista i-esima di 'T'
    nodo_lista* lista = t->T[i];
    while(lista!=NULL)
        if(equal(lista->key, key)){
            lista->info = value;    // sovrascrivo il vecchio valore
            return; // esco
        }
        lista = lista->next;
    // Altrimenti lista == NULL, non ci sono elementi aggiungilo in testa
    nodo_lista* y = (nodo_lista*)malloc(sizeof(nodo_lista));
    y->key = key;
    y->info = value;
    y->next = t->T[i];
    t->T[i] = y;
}

/* Funzione che effettua una cancellazione di un elemento in base alla chiave introdotta */
void delete(hashtable* t, int k){
    int i = mod_hash(k, t->m);  // devo cercare l'elemento nella lista i-esima
    nodo_lista* elem = t->T[i];    // iteratore per elementi della lista T[i]
    nodo_lista* prev = NULL;    // punta all'elemento che precede 'lista'
    while(elem!=NULL)
        if(equal(elem->key, k))    // l'ho trovato
            if(prev==NULL)  // 'elem' è il primo elemento nella lista
                t->T[i] = elem->next;
            else
                prev->next = elem->next;    // salto l'elemento
            return;
        prev = elem;    // non trovato, provo il prossimo
        prev = prev->next;
}

int main(){

    hashtable* table1 = new_table();    // creazione tabella hash 


}