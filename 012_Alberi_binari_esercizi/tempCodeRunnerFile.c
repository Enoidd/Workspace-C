nodo* add_left(albero t, int x){
	/* Se il nodo è gia' esistente */
	if(t->left!=NULL)
		printf("\nError overflow, add_left fallito.\n");
	// Altrimenti 
	t->left = malloc(sizeof(nodo));	// allocazione memoria per il nuovo nodo a sinistra
	t->left->parent = t;	// il nuovo nodo ha come parent il vecchio nodo 't'
	t->left->left = NULL;	// inizialmente il nuovo nodo non ha nodi figli a sinistra
	t->left->right = NULL;	// inizialmente il nuovo nodo non ha nodi figli a destra
	t->left->info = x;	// inizializzazione valore nuovo nodo creato
	
	return t->left;
}