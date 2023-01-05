#include <stdio.h>
#include <stdlib.h>

/* Struttura nodo lista */
typedef struct l{
	int info;	// campo informazione
	struct l* next;	// campo next (contiene l'indirizzo del prossimo nodo)
}litem;

/* Struttura lista */
typedef struct ls{
	litem* head;	// testa della lista
}lista;

/* Funzione che crea una lista */
lista* new_lista(){
	/* alloca memoria per una nuova lista */
	lista* out = malloc(sizeof(lista));
	out->head = NULL;	// lista inizialmente vuota
	
	return out;
}

/* Funzione che stampa la lista */
void print_lista(lista* l){
	/* lista vuota */
	if(l->head==NULL)
		printf("\nError underflow. Lista vuota.\n");
	else{	// altrimenti lista non vuota
		litem* i = l->head;	// per scorrere la lista
		/* scorri la lista fintanto che non sei sull'ultimo nodo */
		while(i!=NULL){
			printf("[%d]--", i->info);
			i = i->next;	// passa al prossimo nodo della lista
		}	// sei uscito dal while, quindi non ci sono più elementi della lista da visitiare
	}
	printf("NULL\n");
}

/* Funzione che inserisce un elemento in testa alla lista */
void insert(lista* l, int x){
	/* Alloca memoria il nuovo nodo da introdurre */
	litem* new = malloc(sizeof(litem));
	new->info = x;	// memorizza nel nodo il valore 'x'
	new->next = l->head;	// il next del nuovo nodo punta al vecchio primo nodo
	l->head = new;	// il primo nodo adesso è new
}

/* Funzione che inserisce un elemento in coda alla lista */
void add(lista* l, int x){
	/* se la lista è vuota */
	if(l->head==NULL){
		insert(l, x);	// fai l'inserimento in testa
		return;
	}
	// Altrimenti lista non vuota
	litem* i = l->head;	// per scorrere la lista
	/* scorri la lista fintanto che non sei sull'ultimo elemento */
	while(i->next!=NULL){
		i = i->next;
	}	// sei uscito dal while, sei quindi sull'ultimo nodo
	litem* new = malloc(sizeof(litem));	// alloca memoria per un nuovo nodo
	new->info = x;	// memorizza nel nodo il valore 'x'
	new->next = NULL;	// il nuovo nodo è l'ultimo
	i->next = new;	// il vecchio ultimo nodo punta al nuovo nodo
}

/* Funzione che effettua una cancellazione in testa */
int delete_head(lista* l){
	/* lista vuota */
	if(l->head==NULL)
		printf("\nError underflow. Cancellazione in testa fallita.\n");
	// Altrimenti lista non vuota
	litem* temp = l->head;	// memorizza il nodo da cancellare
	int v = l->head->info;	// memorizza il valore del nodo da cancellare
	l->head = l->head->next;	// il secondo nodo diventa il primo
	free(temp);	// dealloca il nodo da cancellare
	
	return v;
}

/* Funzione che effettua una cancellazione in coda */
int delete_tail(lista* l){
	/* lista vuota */
	if(l->head==NULL)
		printf("\nError underflow. Cancellazione in coda fallita.\n");
	/* un solo elemento in lista */
	if(l->head->next==NULL)
		delete_head(l);	// fai una cancellazione in testa
	/* C'è più di un elemento in lista */
	litem* i = l->head;	// per scorrere la lista
	/* Salta il primo elemento e scorri la lista fintanto che non sei sull'ultimo elemento */
	while(i->next->next!=NULL){
		i = i->next;	// per passare al prossimo nodo della lista
	}	// sei uscito dal while, sei sull'ultimo nodo della lista
	litem* temp = i->next;	// memorizza l'ultimo nodo della lista
	int v = i->next->info;	// memorizza il valore dell'ultimo nodo
	i->next = NULL;	// il penultimo nodo diventa l'ultimo
	free(temp);	// dealloca l'ultimo nodo
	
	return v;
}

/* Funzione che verifica se la lista è vuota */
int is_empty(lista* l){
	return l->head==NULL;
}

/* Funzione che svuota la lista */
lista* empty(lista* l){
	
	/* lista vuota */
	if(l->head==NULL)
		printf("\nCancellazione fallita. Lista vuota.\n");
	// Altrimenti lista non vuota
	//litem* i = l->head;
	/* Scorri la listta fintanto che non sei sull'ultimo nodo */
	while(l->head!=NULL){
		litem* temp = l->head;	// il nodo da cancellare
		l->head = temp->next;	// memorizza il prossimo nodo
		free(temp);	// dealloca il nodo corrente
	}
	return NULL;
}

/* Funzione che ritorna il massimo valore contenuto nella lista */
int massimo(lista* l){
	litem* i = l->head;
	
	/* lista vuota */
	if(i==NULL)
		printf("\nCalcolo del massimo fallito. Lista vuota.\n");
	/* Scorri la lista fintanto che non sei sull'ultimo nodo */
	int max = i->info;
	while(i!=NULL){
		/* l'elemento corrente è maggiore del massimo */
		if(i->info >= max)
			max = i->info;	// hai un nuovo massimo
		i = i->next;	// altrimenti passa al prossimo nodo
	}	// hai visitato tutti i nodi della lista
	return max;	// se hai calcolato il massimo restituiscilo
}

/* Funzione che ritorna la somma dei valori contenuti nei nodi della lista */
int somma(lista* l){
	int sum = 0;	// nessuna somma calcolata inizialmente
	
	/* se la lista non è vuota */
	if(l->head!=NULL){
		litem* i = l->head;	// per scorrere i nodi della lista
		/* scorri la lista fintanto che non sei sull'ultimo nodo */
		while(i!=NULL){
			sum += i->info;	// somma a 'sum' il valore dell'elemento corrente
			i = i->next;	// passa al prossimo nodo della lista
		}
	}
	return sum;
}

/* Funzione che verifica se un nodo contenente valore 'u' esiste nella lista */
int search(lista* l, int u){
	int exist = 0;	// inizialmente si assume che tale valore non esista
	
	/* Se la lista non è vuota */
	if(l->head!=NULL && exist==0){
		litem* i = l->head;
		/* scorri la lista fintanto che non sei sull'ultimo nodo */
		while(i!=NULL){
			/* l'elemento corrente ha valore di quello cercato */
			if(i->info == u){
				exist = 1;
			}
			i = i->next;	// e passa al prossimo nodo
		}
	}
	return exist;
}

/* Funzione che calcola il numero dei nodi nella lista */
int size(lista* l){
	int count = 0;	// contatore
	litem* i = l->head;	// per scorrere tutta la lista
	
	/* Scorri la lista fintanto che non sei sull'ultimo nodo */
	while(i!=NULL){
		count += 1;		// incrementa il contatore al nodo corrente
		i = i->next;	// passa al prossimo nodo
	}	// sei uscito dal while hai visitato tutti i nodi della lista
	
	return count;
}

int delete(lista* l, int u){
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

/* Funzione che ritorna il numero di elementi comuni in due liste */
int comuni(lista* l1, lista* l2){
	int count = 0;	// inizialmente nessun nodo comune calcolato tra le due liste
	
	/* Se le liste non sono vuote */
	if(l1->head!=NULL && l2->head!=NULL){
		litem* i1 = l1->head;	// per scorrere 'l1'
		/* Scorri la lista 'l1' fintanto che non sei sull'ultimo nodo */
		while(i1!=NULL){
			litem* i2 = l2->head;	// per scorrere 'l2'
			/* Scorri la lista 'l2' fintanto che non sei sull'ultimo nodo */
			while(i2!=NULL){
				/* Confronta il valore del nodo di 'l1' con quelli correnti della lista 'l2' e stabilisci se sono uguali */
				if(i1->info == i2->info)
					count++;	// aggiorna il numero di elementi comuni calcolati tra le due liste
				i2 = i2->next;	// passa al prossimo nodo di 'l2'
			}
			i1 = i1->next;	// passa al prossimo nodo di 'l1'
		}	// Hai visitato tutti i nodi della lista 'l1' e li hai confrontati con i nodi della lista 'l2'
	}
	return count;
}

/* Funzione che ritorna gli elementi di una lista invertiti */
lista* inversa(lista* l){
	/* alloca memoria per una nuova lista (sarà la lista 'l' ma invertita) */
	lista* lista_inversa = new_lista();
	
	/* Se la lista è vuota */
	if(l->head==NULL){
		printf("\nError underflow. Lista vuota, non posso calcolare la sua inversa.\n");
	}	// altrimenti la lista non è vuota
	litem* i = l->head;	// per scorrere la lista
	/* Scorri la lista che devi invertire */
	while(i!=NULL){
		insert(lista_inversa, i->info);	// inverti la lista ( basta un inserimento in testa )
		i = i->next;	// passa al prossimo nodo
	}	// sei uscito dal while
	
	return lista_inversa;	// ritorna la lista invertita
}

/* Funzione che accoda gli elementi della lista 'l2' alla lista 'l1' mantenendo l'ordine delle liste originarie */
void accoda(lista* l1, lista* l2){
	/* Se la lista 'l2' è vuota */
	if(l2->head==NULL){
		printf("\nError underflow. Non posso accodare la lista perché vuota.\n");
		printf("\nLista generata con accodamento fallito: ");
		print_lista(l1);
		exit(1);
	}	// Altrimenti lista 'l2' non vuota
	litem* i2 = l2->head;	// per scorrere la lista 'l2'
	/* Scorri la lista 'l2' fintanto che non sei sull'ultimo nodo */
	while(i2!=NULL){
		add(l1, i2->info);	// aggiungi in coda l'elemento corrente alla lista 'l1'
		i2 = i2->next;	// passa al prossimo nodo
	}	// sei uscito dal while, hai accodato tutti gli elementi
}

/* Funzione che verifica se all'interno di una lista tutti gli elementi sono positivi,
 * quindi restituisce 1, restituisce 0 se c'è almeno un elemento negativo o uguale a 0 */
int tutti_positivi_lista(lista* l1){
	
	int isPos = 1;	// HP. Tutti gli elementi sono positivi
	// altrimenti lista non vuota
	litem* i = l1->head;	// per scorrere la lista
	/* Scorri la lista fintanto che ci sono elementi da visitare */
	while(i!=NULL && isPos){
	/* Il nodo corrente ha valore negativo o uguale a 0 */
		if(i->info<=0)
			isPos = 0;
		else
			i = i->next;	// Altrimenti passa al prossimo nodo
	}	// Sei uscito dal while, hai visitato tutti i nodi della lista
	return isPos;
}

/* Funzione che verifica se gli elementi in lista sono in ordine crescente */
int ordine_crescente(lista* l1){
	int ordinata = 1;

	if(l1==NULL)
		ordinata = 0;
	litem* i = l1->head;
	while(i->next!=NULL && ordinata){
		if(i->info > i->next->info)
			ordinata = 0;
		else
			i = i->next;
	}
	return ordinata;
}

/* Funzione che verifica se il primo e l'ultimo elemento della lista sono uguali */
int primo_ultimo(lista* l1){
	/* Lista vuota */
	if(l1==NULL) return 0;
	// Altrimenti lista non vuota
	/* Un solo elemento in lista */
	if(l1->head->next==NULL) return 0;
	/* C'è più di un elemento in lista */
	litem* i = l1->head;
	while(i->next!=NULL){
		i = i->next;
	}	// hai visitato tutti i nodi della lista
	if(i->info && l1->head->info)
			return 1;
		
	return 0;
}

/* Funzione che verifica se ci sono due elementi consecutivi uguali nella lista */
int doppioni(lista* l1){
	/* Se la lista è vuota */
	if(l1==NULL) return 0;
	/* C'è un solo elemento nella lista */
	if(l1->head->next==NULL) return 0;
	/* C'è più di un elemento */
	litem* i = l1->head;
	while(i->next!=NULL){
		if(i->info==i->next->info)
			return 1;
		else
			i = i->next;
	}
	return 0;
}

/*  Verifica se esiste un campo info di un nodo della lista uguale alla lunghezza della lista */
int info_uguale_lunghezza(lista* l1){
	int count = 0;	// Lunghezza della lista 
	int trovato = 0;	// HP. inizialmente nessun nodo con valore pari alla lunghezza è stato trovato 
	/* Se la lista non è vuota */
	if(l1!=NULL){
		litem* i = l1->head;	// per scorrere la lista
		/* Scorri la lista fintanto che ci sono nodi da visitare */
		while(i!=NULL){
			count++;	// nuovo nodo contato
			i = i->next;	// passa al prossimo nodo della lista
		}	// hai visitato tutti i nodi della lista
		/* Controlla se l'elemento corrente ha valore pari alla dimensione della lista che vale 'count' */
		litem* j = l1->head;
		while(j!=NULL && !trovato){
			/* verifica se c'è nodo con valore uguale a count */
			if(j->info==count)
				trovato = 1;
			else
				j = j->next;
		}	// Hai visitato tutti i nodi della lista
	}
	return trovato;
}

/* Funzione che conta quanti sono i nodi della lista con campo info minore del campo info del nodo successivo */
int minore_successivo(lista* l1){
	int count = 0; 

	if(l1!=NULL){
		//litem* i = l1->head;
		while(l1->head->next!=NULL){
			//if(i->info < i->next->info)
			if(l1->head->info < l1->head->next->info)
				count++;
			//i = i->next;
			l1->head = l1->head->next;
		}
	}
	return count;

	/* === NB. NON CONOSCO BENE LA RICHIESTA PRECISA DELLA FUNZIONE */
}

int main(int argc, char **argv)
{

	/* Creazione lista */
	lista* lista1 = new_lista();
	
	/* INSERT */
	printf("\nInserimento in testa di 2.\n");
	insert(lista1, 2);
	printf("\nInserimento in testa di 3.\n");
	insert(lista1, 3);
	printf("\nInserimento in testa di 4.\n");
	insert(lista1, 4);
	
	/* Stampa*/
	printf("\nStampa lista: ");
	print_lista(lista1);
	
	/* CONOSCERE GLI ELEMENTI DELLA LISTA */
	//printf("\n===============================================\n");
	//printf("\nl->head = %d --- l->head->info = %d.\n", lista1->head, lista1->head->info);	// [4]
	//litem* i = lista1->head;
	//printf("i = %d --- i->info = %d.\n", i, i->info);	// [4]
	//printf("\n");
	//printf("l->head->next = %d --- l->head->next->info = %d.\n", lista1->head->next, lista1->head->next->info);	// [3]
	//printf("i->next = %d--- i->next->info = %d.\n", i->next, i->next->info);	// [3]
	//printf("\n");
	//printf("l->head->next->next = %d --- l->head->next->next->info = %d.\n", lista1->head->next->next, lista1->head->next->next->info);	// [2]
	//printf("i->next->next = %d --- i->next->next->info = %d.\n", i->next->next, i->next->next->info);	// [2]
	//printf("\n===============================================\n");
	
	
	/* ADD */
	printf("\ninserimento in coda di: 5\n");
	add(lista1, 5);
	
	/* Stampa*/
	printf("\nStampa lista: ");
	print_lista(lista1);
	
	/* Cancellazione in testa */
	printf("\nCancellazione in testa di: %d.", delete_head(lista1));
	
	printf(" Stampa lista: ");
	print_lista(lista1);
	
	/* Cancellazione in coda */
	printf("\nCancellazione in coda di: %d.", delete_tail(lista1));
	
	printf(" Stampa lista: ");
	print_lista(lista1);
	
	/* MASSIMO -> Calcola il massimo valore contenuto nella lista */
	printf("\nIl massimo valore contenuto nella lista ha valore: %d.\n", massimo(lista1));	// atteso
	/* Lista vuota */
	
	/* SOMMA -> Ritorna la somma di tutti i valori contenuti nella lista */
	printf("\nLa somma di tutti gli elementi della lista: %d.\n", somma(lista1));
	
	/* SEARCH -> Funzione che verifica se un valore esiste */
	int val;	// valore cercato
	printf("\nInserisci di seguito un valore che vuoi ricercare nella lista: ");
	scanf("%d", &val);
	
	if(search(lista1, val))
		printf("\nIl valore %d è nella lista.\n", val);
	else
		printf("\nIl valore %d non è nella lista.\n", val);
		
	printf("\nNodi contati: %d.\n", size(lista1));
	
	printf("\nInserisci di seguito un valore che vuoi ricercare nella lista e cancellare: ");
	scanf("%d", &val);
	delete(lista1, val);
	
	printf("\nLista: ");
	print_lista(lista1);
	
	/*==========================================================================================================================*/
	
	/* Creazione lista */
	lista* lista2 = new_lista();
	
	/* ADD */
	add(lista2, 5);
	add(lista2, 7);
	add(lista2, 3);
	add(lista2, 9);
	add(lista2, 11);
	
	/* INSERT */
	insert(lista2, 8);
	insert(lista2, 2);
	
	printf("\n============================\n");
	printf("\nLista: ");
	print_lista(lista2);
	
	/* IS_EMPTY -> Verifica se la lista 'lista2' è vuota */
	if(is_empty(lista2))
		printf("\nIS_EMPTY Lista2 vuota.\n");
	else
		printf("\nIS_EMPTY Lista2 non vuota.\n");	// atteso
	
	/* EMPTY -> Svuota la lista 'lista2' */
	empty(lista2);
	printf("\nEMPTY Lista svuotata.\n");
	
	/* IS_EMPTY -> Verifica se la lista 'lista2' è vuota */
	if(is_empty(lista2))
		printf("\nIS_EMPTY Lista2 vuota.\n");	// atteso
	else
		printf("\nIS_EMPTY Lista2 non vuota.\n");
	
	/*==========================================================================================================================*/
	
	/* Creazione lista */
	lista* lista3 = new_lista();
	lista* lista4 = new_lista();
	
	/* Inserimento in testa 'lista3'*/
	insert(lista3, 1);
	insert(lista3, 2);
	insert(lista3, 3);
	insert(lista3, 4);
	
	/* Inserimento in coda 'lista4' */
	add(lista4, 4);
	add(lista4, 3);
	add(lista4, 2);
	add(lista4, 1);
			
	printf("\nStampa lista 'lista3': ");
	print_lista(lista3);
	printf("\nStampa lista 'lista4': ");
	print_lista(lista4);

	/* Funzione che stabilisce e calcola quanti sono gli elementi comuni tra le due liste */
	int iscomuni = comuni(lista3, lista4);
	
	if(iscomuni==0)
		printf("\nNessun elemento in comune.\n");
	else
		printf("\nElementi comuni: %d.\n", iscomuni);
		
	/* Funzione che calcola l'inversa di una lista */
	lista* lista3_invertita = inversa(lista3);	// inverti la lista 'lista3' e mettila in 'lista3_invertita'
	
	printf("\nInversa della lista 'lista3': ");
	print_lista(lista3_invertita);	// stampa la lista 'lista3'
	
	/* Accodamento dei nodi della lista 'lista3' alla lista 'lista4' */
	accoda(lista3, lista4);
	
	printf("\nAccodamento lista, lista generata: ");
	print_lista(lista3);
	printf("\n");
	
	/*==========================================================================================================================*/
	
	/* Creazione lista */
	lista* lista5 = new_lista();
	
	/* Inserimento in testa 'lista5'*/
	insert(lista5, 0);
	insert(lista5, 22);
	insert(lista5, 33);
	insert(lista5, 45);
	
	/* Inserimento in coda 'lista4' */
	add(lista5, 46);
	add(lista5, 37);
	add(lista5, 28);
	add(lista5, 19);
	
	printf("\nStampa lista 'lista5': ");
	print_lista(lista5);
	
	/* Verifica se tutti gli elementi della lista 'lista5' sono positivi */
	if(tutti_positivi_lista(lista5))
		printf("\nTutti i nodi della lista: 'lista5' hanno valore positivo.\n");
	else
		printf("\nNon tutti i nodi della lista: 'lista5' hanno valore positivo.\n");	// Atteso

	

	/* PRETEST */

	lista* listaT = new_lista();
	insert(listaT, 3);
	insert(listaT, 5);
	insert(listaT, 4);
	insert(listaT, 5);
	lista* listaT1 = new_lista();

	/* Verifica se la lista è ordinata in modo crescente */
	printf("\nordina_lista, atteso: 1, calcolato: %d.\n", ordine_crescente(listaT));	// CORRETTA
	/* Verifica se il primo e l'ultimo elemento della lista sono uguali */
	printf("\nprimo_ultimo, atteso: 1, calcolato: %d.\n", primo_ultimo(listaT));		// CORRETTA
	/* Verifica se nella ci sono due elementi consecutivi uguali */
	printf("\nelementi doppi, atteso: 1, calcolato: %d.\n", doppioni(listaT));			// CORRETTA
	/* Verifica se esiste un campo info di un nodo della lista uguale alla lunghezza della lista */
	printf("\ninfo_uguale_lunghezza, atteso: 1, calcolato: %d.\n", info_uguale_lunghezza(listaT));	// Dimensione lista 4 // CORRETTA
	/* Funzione che conta quanti sono i nodi della lista con campo info minore del campo info del nodo successivo */
	printf("\nminore_successivo, atteso 2, calcolato: %d.\n", minore_successivo(listaT));
}
