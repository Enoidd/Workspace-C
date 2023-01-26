/*
Una coda di priorità viene realizzata tramite l'heap.

- Cos'è una coda di priorità?
- Una coda di priorità o priority queue è una collezione di elementi, dove ad ogni elemento è associato un valore di 
  priorità.

== COMPLESSITA' ==

- Si potrebbe realizzare un heap tramite liste.

Caso lista non ordinata.  In questo caso per aggiungere un elemento avremmo una complessità
Theta(n), mentre la rimozione dell'elemento a priorità più alta Theta(1)

Caso lista ordinata. In questo caso per aggiungere un elemento in TESTA avrebbe una complessità Theta(1),
mentre la ricerca e rimozione di un elemento a più alta priorità Theta(n)

====> lo "scopo" degli heap è bilanciare i due costi.

== COME E' FATTO UN HEAP ==

Rappresentano alberi binari quasi completi, ossia che risulta incompleto nel suo ultimo livello sulla parte destra

E' una struttura: che può essere utilizzata per realizzare code di priorità / i valori contenuti nell'array sono
in rapporto con la loro posizione / può essere un max heap o un min heap 

*/


/* Operazioni sulle code di priorità */