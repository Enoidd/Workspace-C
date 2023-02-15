#include <stdio.h>
#include <stdlib.h>

/* ================================ STRUTTURE GRAFO ================================ */

typedef struct lista_nodi elem_nodi;
typedef struct lista_archi elem_archi;

/* Struttura nodo */
typedef struct nodo{
    int id;
    elem_archi* archi;
    elem_nodi* pos;
    int color;
}nodo;

typedef struct arco_grafo{
    int id;
    nodo* from;
    nodo* to;
    elem_archi* pos;
    elem_archi* from_pos;
    elem_archi* to_pos;
}arco;

/* Lista nodi */
typedef struct lista_nodi{
    nodo* info;
    struct lista_nodi* prev;
    struct lista_nodi* next;
}elem_nodi;

/* Lista archi */
typedef struct lista_archi{
    arco* info;
    struct lista_archi* prev;
    struct lista_archi* next;
}elem_archi;

/* Struttura grafo */
typedef struct grafo_oggetti{

    int numero_nodi;
    int numero_archi;
    elem_nodi* nodi;
    elem_archi* archi;
}go;

/* ================================ STRUTTURA ALBERO ================================ */
