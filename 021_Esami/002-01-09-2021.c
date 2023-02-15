

/* La funzione restituisce 1 (cioè true) se la 
profondità della foglia meno profonda dell’albero è uguale al numero di nodi della componente connessa 
del grafo g che ha meno nodi, altrimenti la funzione restituisce 0 (cioè false). Se uno (o entrambi) tra grafo 
e albero è vuoto (cioè uguale a NULL) la funzione ritorna 0 (false).  */



/* Per contare i nodi della componente connessa */
int dfs(nodo* n){

    n->color = 1;
    int count = 1;
    elem_archi* la = n->archi;
    while(la!=NULL){
        nodo* x = la->info->from;
        if(x==n)
            x = la->info->to;
        if(x->color==0)
            count += dfs(x);
        la = la->next;
    }
    return count;
}

int minimo(grafo* g){

    elem_nodi* ln = g->nodi;
    while(ln!=NULL){
        ln->info->color = 0;
        ln = ln->next;
    }
    ln = g->nodi;
    int min = dfs(ln->info);
    int temp;
    while(ln!=NULL){
        if(ln->info->color==0)
            temp = dfs(ln->info);
        if(min > temp) min = temp;
        ln = ln->next;
    }
    return min;
}


int foglia_meno_profonda_ric(nodo_albero* t){
    if(t==NULL) return 100;

    if(t->l==NULL && t->r==NULL)
        return 0;

    int hl = 1+foglia_meno_profonda_ric(t->l);
    int hr = 1+foglia_meno_profonda_ric(t->r);
    
    if(hl<hr) return hl;

    return hr;
}


int verifica(nodo_albero* a, grafo* g){
    
    if(a==NULL && g==NULL) return 0;

    if(foglia_meno_profonda_ric(a)==minimo(g))
        return 1;
    return 0;
}


/****************************************************/

// 02-07-2021 

/* La funzione restituisce 1 (cioè true) se 
esiste una profondità dell’albero alla quale ci sono tanti nodi quanti sono i nodi della componente connessa 
più grande del grafo g, altrimenti la funzione restituisce 0 (cioè false). Se uno (o entrambi) tra grafo e 
albero è vuoto (cioè uguale a NULL) la funzione ritorna 0 (false). */

// 01-09-2020

/* int verifica(nodo* a) che accetti 
in input un puntatore alla radice di un albero binario di interi e ritorni 1 se esiste un nodo 
dell’albero che è radice di un sottoalbero che ha esattamente la metà dei nodi dell’intero 
albero, altrimenti ritorna 0. Se i nodi dell’albero sono dispari la funzione verifica()
ritorna ovviamente 0.  */

/* SU PRE_TEST4*/


// 28-01-2020

/* La funzione restituisce 1 se esiste nodo 
dell’albero che ha tanti figli quanti sono i nodi di una componente connessa del grafo g, altrimenti la 
funzione restituisce 0. Se uno (o entrambi) tra grafo e albero è vuoto (cioè uguale a NULL) la funzione 
ritorna 0. */

/* Dfs conta componente connessa nodo */
int dfs_conta(nodo* n){
    n->color = 1;
    int count = 1;
    elem_archi* ln = n->archi;
    while(ln!=NULL){
        nodo* x = ln->info->from;
        if(x==n)
            x = ln->info->to;
        if(n->color==0)
            count += dfs(x);
        ln = ln->next;
    }
    return
}

/* Funzione che conta i figli di un nodo di un albero arbitrario */
int conta_nodi_figli(nodo* n){
    if(n==NULL) return 0;

    int count = 0;
    while(n->left!=NULL){
        count++;
        n = n->right;
    }
    return count;
}

int funzione(nodo_albero* t, int var){
    if(t==NULL) return 0;

    if(conta_nodi_figli(t)==var) return 1;

    return funzione(t->l, var) || funzione(t->r, var);
}

int verifica(nodo_albero* a, grafo* g){
    if(a==NULL && g==NULL) return 0;

    elem_nodi* n = g->nodi;
    while(n!=NULL){
        n->info->color = 0;
        n = n->next;
    }
    n = g->nodi;
    while(n!=NULL){
        if(n->info->color==0)   // se il nodo corrente non è stato visitato
            int var = dfs(n->info);
        if(funzione(a, var))
            return 1;
        n = n->next;
        }
    return 0;
}


// 02-09-2019

/* La funzione restituisce 1 se il numero di nodi 
dell’albero a che hanno un solo figlio sono tanti quanti sono i nodi della componente più piccola del grafo 
g, altrimenti la funzione restituisce 0. Se uno (o entrambi) tra grafo e albero è vuoto (cioè uguali a NULL) la 
funzione ritorna 0. */

int un_solo_figlio(albero t){
    if(t==NULL) return 0;

    int count = 0;
    if(t->l!=NULL && t->r==NULL || t->l==NULL && t->r!=NULL)
        count++;

    return count + un_solo_figlio(t->l) + un_solo_figlio(t->r);
}

int dfs(nodo* n){
    n->color = 1;
    int count = 1;
    elem_archi* la = n->archi;
    int min;
    while(la!=NULL){
        nodo* x = la->info->from;
        if(x==n)
            x = la->info->to;
        if(n->color==0)
            count += dfs(x);
        la = la->next;
    }
    return count;
}

int componente_connessa_minima(grafo* g){
    elem_nodi* ln = g->nodi;
    while(ln!=NULL){
        ln->color = 0;
        ln = ln->next;
    }
    ln = g->nodi;
    int min = dfs(ln->info);
    int temp;
    while(ln!=NULL){
        if(ln->info->color==0)
            temp = dfs(ln->info);
        if(min > temp) temp = min;
        ln = ln->next; 
    }
    return min;
}

int verifica(nodo_albero* a, grafo* g){
    if(a==NULL && g==NULL) return 0;

    int numero_nodi = un_solo_figlio(a);
    int cc_min = componente_connessa_minima(g);

    if(numero_nodi == cc_min)
        return 1;
    return 0;
}

// 20-06-2019

/* La funzione restituisce 1 se il numero di 
nodi dell’albero a che sono a profondità h sono tanti quanti sono i nodi della componente più grande del 
grafo g, altrimenti la funzione restituisce 0. Se uno (o entrambi) tra grafo e albero è vuoto (cioè uguali a 
NULL) la funzione ritorna 0. */

int dfs(nodo* n){
    n->color = 1;
    int count = 1;
    elem_archi* la = n->archi;
    while(la!=NULL){
        nodo* x = la->info->from;
        if(x==n)
            la->info->to;
        if(x->color==0)
            count += dfs(x);
        la = la->next;
    }
    return count;
}

int componente_connessa_max(grafo* g){
    elem_nodi* ln = g->nodi;
    while(ln!=NULL){
        ln->info->color = 0;
        ln = ln->next;
    }
    ln = g->nodi;
    int max = dfs(ln->info);
    int temp;
    while(ln!=NULL){
        if(ln->info->color==0)
            temp = dfs(ln->info);
        if(temp > max) max = temp;
        ln = ln->next;
    }
    return max;
}

int nodi_profondita_h(nodo_albero* t, int h){
    if(t==NULL) return 0;

    if(h==0) return 1;

    return nodi_profondita_h(t->l, h-1) || nodi_profondita_h(t->r, h-1);
}

int verifica(int h, nodo_albero* a, grafo* g){
    if(a==NULL && g==NULL) return 0;

    int nodi_in_profodinta_h = nodi_in_profodinta_h(a, h);
    int cc_max = componente_connessa_max(g);

    if(nodi_in_profodinta_h==cc_max)
        return 1;
    return 0;
}