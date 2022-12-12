#include <stdio.h>
#include <stdlib.h>

/* Struttura nodo della lista */
typedef struct l{
	int info;	// Campo informazione
	struct l* next;	// Campo next
	struct l* prev;	// Campo prev
}litem;

/* Struttura lista */
typedef struct ls{
	litem* head;	// testa della lista
}lista;

/* Funzione che crea una lista */
lista* new_lista(){
	/* Alloca memoria per una nuova lista */
	lista* out = malloc(sizeof(lista));
	out->head = NULL;	// Inizialmente la lista è vuota
	
	return out;
}

/* Funzione che stampa la lista */
void print_lista(lista* l){
	/* Se la lista è vuota */
	if(l->head==NULL)
		printf(" Error underflow. Lista vuota, stampa fallita.\n");
	// Altrimenti lista non vuota
	litem* i = l->head;	// per scorrere la lista
	/* Scorri la lista fintanto che ci sono nodi da visitare */
	while(i!=NULL){
		printf("[%d]---", i->info);
		i = i->next;	// aggiorna il prossimo nodo
	}	// seiuscito dal while hai visitato tutti i nodi della lista
	printf("NULL\n");
}

/* Funzione che fa un inserimento in testa alla lista */
void insert(lista* l, int x){
	/* Alloca memoria per un nuovo nodo */
	litem* new = malloc(sizeof(litem));
	/* inizialmente si assume che la lista è vuota */
	new->info = x;	// campo info
	new->prev = NULL;	// essendo il primo nodo non ha predecessori
	new->next = l->head;	// il next del nuovo primo nodo punta al "vecchio" primo nodo, si posiziona in testa alla lista
	/* Se la lista non è vuota */
	if(l->head!=NULL){
		l->head = new;
	}
	l->head = new;
}

/* Funzione che fa un inserimento in coda alla lista */
void add(lista* l, int x){
	/* Se la lista è vuota */
	if(l->head==NULL){
		insert(l, x);	// il nodo verrà inserito in testa
	}
	// Altrimenti la lista non è vuota
	litem* i = l->head;	// per scorrere la lista
	/* Scorri la lista fintanto che non sei sull'ultimo nodo */
	while(i->next!=NULL){
		i = i->next;	// per passare al prossimo nodo
	}	// sono uscito dal while, sono sull'ultimo nodo della lista
	/* Alloca memoria per un nuovo nodo */
	litem* new = malloc(sizeof(litem));
	new->info = x;	// memorizza il valore 'x' nel nuovo nodo
	i->next = new;	// il vecchio ultimo nodo punta al nuovo primo nodo
	new->prev = i;	// il prev nel nuovo nodo punta al vecchio ultimo nodo
	new->next = NULL;	// il nuovo nodo è l'ultimo
}

/* Funzione che effettua una cancellazione in testa alla lista */
int delete_head(lista* l){
	/* Se la lista è vuota */
	if(l->head==NULL)
		printf("\nError underflow. Lista vuota, cancellazione in testa fallita.\n");
	// Altrimenti lista non vuota
	int x = l->head->info;	// memorizzazione valore del primo nodo
	litem* temp = l->head;	// memorizzazione primo nodo da cancellare
	l->head = l->head->next;	// il successivo del primo nodo è il nuovo primo nodo
	l->head->next->prev = NULL;	// il nuovo primo nodo non ha predecessori
	free(temp);
	
	return x;
}

/* Funzione che effettua una cancellazione in coda alla lista */
int delete_tail(lista* l){
	/* Se la lista è vuota */
	if(l->head==NULL)
		printf("\nError underflow. Lista vuota, cancellazione in coda fallita.\n");
	/* Se la lista contiene un solo elemento */
	if(l->head->next==NULL){
		delete_head(l);	// c'è un solo nodo, cancellalo in testa
	}
	// Altrimenti c'è più di un nodo nela lista
	litem* i = l->head;	// per scorrere la lista
	/* Scorri la lista fintanto che non sei sull'ultimo nodo, saltando un nodo */
	while(i->next!=NULL){
		i = i->next;	// per passare al prossimo nodo
	}	// Sono uscito dal while, sono sull'ultimo nodo
	int x = i->info;	// memorizza il valore del nodo da cancellare
	litem* temp = i;	// memorizza il nodo da cancellare
	i->prev->next = NULL;	// il vecchio ultimo nodo è scollegato dal resto della lista
	free(temp);	// dealloca memoria del nodo da cancellare
	
	return x;
}

/* Funzione che cerca un nodo con valore 'u' e lo cancella */
int search_and_delete(lista* l,int u){
	/* Se la lista è vuota */
	if(l->head==NULL)
		printf("\nCancellazione per ricerca fallita. Lista vuota.\n");
	if(l->head->info == u)
		return delete_head(l);	// cancellazione in testa
	// Altrimenti lista non vuota
	int trovato = -1;	// il valore 'u' è stato trovato?
	litem* prec = l->head;	// indice del nodo che precede succ
	litem* succ = l->head->next;	// indice da cui si parte per visitare tutta la lista
	/* Scorri la lista fintanto che non sei sull'ultimo nodo e che il valore non è stato trovato */
	while(succ!=NULL && trovato ==-1){
		/* l'elemento corrente è quello cercato */
		if(succ->info == u){
			trovato = u;
			/* Cancellalo */
			litem* temp = succ;	// memorizza il nodo da cancellare
			prec->next = succ->next;	// il next del precedente punta al next di quello che va cancellato
			free(temp);	// deallocalo
		}
		// altrimenti non l'ho trovato
		succ = succ->next;	// aggiorna il successivo
		prec = prec->next;	// aggiorna il precedente
	}	// sei uscito dal while
	return trovato;
}


/* Funzione che inserisce un nodo di valore 'n' nella lista prima del nodo in posizione 'i' */
void insert_before(lista* l, int n, int i){
	/* Se il valore 'i' è il primo oppure se la lista è vuota */
	if(i == 1 || l->head==NULL)
		insert(l, n);	// fai l'inserimento in testa
	else{ // Altrimenti 'i' non è il primo elemento
		litem* li = l->head;	// per scorrere la lista
		int count = 1;	// per contare i nodi, inizializzato a 1 perché si parte a visitare la lista dal secondo nodo
		/* Scorri la lista fintanto che non sei sull'ultimo nodo */
		while(li->next!=NULL){
			count++;	// aggiorna la posizione del nodo corrente
			/* L'elemento corrente è in posizione 'i' */
			if(count == i){
				litem* new = malloc(sizeof(litem));	// Alloca memoria per un nuovo nodo 
				new->info = n;	// inizializzazione campo info a valore 'n'
				li->prev->next = new;	// il nodo precedente a 'li' adesso punta al nuovo nodo
				new->next = li;	// il next del nuovo nodo punta al nodo corrente
				}	// Altrimenti non lo hai ancora trovato
			li = li->next;	// aggiorna al prossimo nodo
		}	// Sei uscito dal while
	}
}

/* Funzione che inserisce un nodo di valore 'n' nella lista dopo il nodo in posizione 'i' */
void add_after(lista* l, int n, int i){
	/* Se il valore 'i' è il primo oppure se la lista è vuota */
	if(i == 1 || l->head==NULL)
		insert(l, n);	// fai l'inserimento in testa
	else{ // Altrimenti 'i' non è il primo elemento
		litem* li = l->head;	// per scorrere la lista
		int count = 1;	// per contare i nodi, inizializzato a 1 perché si parte a visitare la lista dal secondo nodo
		/* Scorri la lista fintanto che non sei sull'ultimo nodo */
		while(li->next!=NULL){
			count++;	// aggiorna la posizione del nodo corrente
			/* L'elemento corrente è in posizione 'i' */
			if(count == i){
				litem* new = malloc(sizeof(litem));	// Alloca memoria per un nuovo nodo 
				new->info = n;	// inizializzazione campo info a valore 'n'
				new->next = li->next;	// il nuovo nodo punta al successivo del nodo corrente
				li->next = new;	// il nodo corrente adesso punta al nuovo nodo creato
				}	// Altrimenti non lo hai ancora trovato
			li = li->next;	// aggiorna al prossimo nodo
		}	// Sei uscito dal while
	}
}

/* ====================== SESTO HOMERWORK ====================== */

/* Funione che prende in input un parametro di tipo plist* (cioè un puntatore ad un plist che è a sua volta 
 * un puntatore ad un elemento elist della lista) e rimuove (se c'è) il primo elemento della lista. Se la
 * lista è vuota la funzione non fa nulla */

typedef struct elist{
	int info;
	struct elist* prev;
	struct elist* next;
}elist;

typedef elist* plist;

void rimuovi_primo(plist* p){
	/* Se la lista è vuota */
	if(p==NULL){
		return;
	}
	else{ // Altrimenti la lista non è vuota
		/* C'è almeno un elemento nella lista */
		plist temp = *p;	// temp vale il primo nodo della lista
		(*p) = (*p)->next;	// aggiorna il vecchio primo nodo al secondo nodo della lista
		(*p)->prev = NULL;	// il nuovo primo nodo non ha predecessori
		free(temp);
	}
}

/* =================================================================== */

int main(int argc, char **argv)
{
	/* Creazione lista */
	lista* lista1 = new_lista();

	/* Stampa lista */
	printf("\nLista 'lista1': ");
	print_lista(lista1);
	
	/* Insert */
	insert(lista1, 1);
	printf("\nInserimento in testa: 1, lista: ");
	print_lista(lista1);
	insert(lista1, 2);
	printf("\nInserimento in testa: 2, lista: ");
	print_lista(lista1);
	insert(lista1, 3);
	printf("\nInserimento in testa: 3, lista: ");
	print_lista(lista1);
	insert(lista1, 4);
	printf("\nInserimento in testa: 4, lista: ");
	print_lista(lista1);
	
	/* Stampa lista */
	printf("\nLista 'lista1': ");
	print_lista(lista1);	// atteso: [4]---[3]---[2]---[1]---NULL
	
	/* Add */
	add(lista1, 6);
	printf("\nInserimento in coda: 6, lista: ");
	print_lista(lista1);
	add(lista1, 8);
	printf("\nInserimento in coda: 8, lista: ");
	print_lista(lista1);
	
	/* Stampa lista */
	printf("\nLista 'lista1': ");
	print_lista(lista1);	// atteso: [4]---[3]---[2]---[1]---[6]---[8]---NULL
	
	/* delete_head */
	delete_head(lista1);
	printf("\nCancellazione in testa effettuata, lista: ");
	print_lista(lista1);
	
	/* delete_tail */
	delete_tail(lista1);
	printf("\nCancellazione in coda effettuata, lista: ");
	print_lista(lista1);

	/* search_and_delete */
	printf("\nInserisci il valore che vuoi cancellare dalla lista: ");
	int v;
	scanf("%d", &v);
	search_and_delete(lista1, v);
	
	printf("\nLista 'lista1': ");
	print_lista(lista1);

	/* insert_before */
	printf("\nInserisci il valore che vuoi introdurre:");
	int n;
	scanf("%d", &n);
	printf("\nInroduci la posizione prima del quale vuoi inserirlo: ");
	int i;
	scanf("%d", &i);
	insert_before(lista1, n, i);
	printf("\nLista: "); 
	print_lista(lista1);
	
	/* add_after */
	printf("\nInserisci il valore che vuoi introdurre:");
	scanf("%d", &n);
	printf("\nInroduci la posizione dopo del quale vuoi inserirlo: ");
	scanf("%d", &i);
	add_after(lista1, n, i);
	printf("\nLista: "); 
	print_lista(lista1);
}
