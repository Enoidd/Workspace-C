#include <stdio.h>
#include <stdlib.h>

/* Struttura nodo albero */
typedef struct nodo{
    struct nodo* p;
    struct nodo* l;
    struct nodo* r;
    int info;
}nodo;
typedef nodo* albero;

/*albero newTree(){
	albero new = (albero)malloc(sizeof(albero));	
	new = NULL;
    return new;
}*/

void add_root(nodo** t, int v){
    if((*t)!=NULL){
        printf("\nInserimento radice fallito. Radice gia' esistente\n");
        return;
    }
    nodo* root = (nodo*)malloc(sizeof(nodo));
    root->p = NULL;
    root->l = NULL;
    root->r = NULL;
    root->info = v;
    (*t) = root;
}

albero add_left(albero t, int v){
    if(t->l!=NULL){
        printf("\nNodo a sinistra gia' esistente.\n");
    }
    t->l = (nodo*)malloc(sizeof(nodo));
    t->l->p = t;
    t->l->l = NULL;
    t->l->r = NULL,
    t->l->info = v;

    return t->l;
}


albero add_right(albero t, int v){
    if(t->r!=NULL){
        printf("\nNodo a destra gia' esistente.\n");
    }
    t->r = (nodo*)malloc(sizeof(nodo));
    t->r->p = t;
    t->r->l = NULL;
    t->r->r = NULL;
    t->r->info = v;

    return t->r;
}

int is_empty(nodo* t){
    return t==NULL;
}

/* PREORDINE */
/* Funzione che cerca nell'albero se esiste un nodo con valore 'n', ritorna TRUE, FALSE altrimenti */
/* VERSIONE PROFESSORE */
nodo* search_pre(nodo* t, int n){
    if(t==NULL)
        return NULL;
    /* il nodo sono proprio io */
    if(t->info==n)   
        return t;

    nodo* l = search_pre(t->l, n);
    if(l!=NULL){
        return l;
    }
    return search_pre(t->r, n);
}

int search_pre_v1(albero t, int n){
    int trovato;

    if(t==NULL) // albero vuoto
        trovato = 0;
    else{
        if(t->info==n) // ho lanciato su di me
            trovato = 1;
        else{   // non ho lanciato su di me
            trovato = search_pre_v1(t->l, n);   // lo cerco a sinistra
            if(trovato==0)  // non l'ho ancora trovato 
                trovato = search_pre_v1(t->r, n);   // lo cerco a destra
        }
    }
    return trovato;
}

/* Funzione ricerca in postordine */
nodo* search_post(albero t, int n){
    if(t==NULL) return NULL; // albero vuoto

    nodo* l = search_post(t->l, n);
    nodo* r = search_post(t->r, n);

    if(l!=NULL) return l;

    if(r!=NULL) return r;

    if(t->info==n)
        return t;
    
    return NULL;    // altrimenti non l'ho trovato
}

int search_post_v1(albero t, int n){
    if(t==NULL) return 0;

    int trovato_dx = search_post_v1(t->l, n);
    int trovato_sx = search_post_v1(t->r, n);

    if(trovato_sx==1)
        return 1;

    if(trovato_dx==1)
        return 1;

    if(t->info==n)
        return 1;

    return 0;
}

/* Funzione ricerca simmetrica */
nodo* search_sim(nodo* t, int n){
    if(t==NULL) return NULL;

    nodo* l = search_sim(t->l, n);
    if(l!=NULL)  return l;

    if(t->info==n) return t;

    nodo* r = search_sim(t->r, n);
    if(r!=NULL) return r;

    return NULL;
}

int search_sim_v1(albero t, int n){
    if(t==NULL) return 0;
    
    if(search_post_v1(t->l, n)) return 1;

    if(t->info==n) return 1;

    if(search_sim_v1(t->r, n)) return 1;

    return 0;
}

/*  Funzione che conta i nodi */
int contaNodi(albero t){
    if(t==NULL) return 0;

    return 1 + contaNodi(t->l) + contaNodi(t->r);
}

/* Funzione che verifica se l'albero è un cammino, cioè se tutti i nodi hanno grado
1 con eccezione dell'unica foglia. Si assume che l'albero vuoto è un cammino */
/* POSTORDINE */
int cammino(albero t){
    if(t==NULL) return 1;

    if(cammino(t->l) && t->r==NULL)
        return 1;
    
    if(cammino(t->r) && t->l==NULL)
        return 1;
    
    if(t->l==NULL && t->r==NULL)
        return 1;

    return 0;
}


/* Funzione che calcola l'altezza di un albero, cioè il numero di archi del cammino che va dalla radice
 * alla foglia più profonda, ritorna -1 se l'albero è vuoto */
int altezza(albero t){
    if(t==NULL){
        return -1;
    }

    int l = altezza(t->l);
    int r = altezza(t->r);

    int max = l;
    if(r>max){
        max = r;
    }

    return max+1;    
}

/* Funzione che calcola la media dei valori contenuti nell'abero binario */
void mediaRic(albero t, int* somma, int* count){
    /* Per calcolare la media ho bisogno di sapere quanti nodi ci sono e la
    somma di tutti i nodi*/
    if(t==NULL)
        return;
    
    (*somma) += t->info;
    (*count) += (*count)+1;

    mediaRic(t->l, somma, count);
    mediaRic(t->r, somma, count);

}

int media(albero t){
    
    int somma = 0;
    int count = 0;

    mediaRic(t, &somma, &count);

    float ris = (float)somma/(float)count;
    
    return ris;
}


/* Funzione che verifica se l'albero è completo */
int completoRic(albero t){
    if(t==NULL){
        return -1;
    }

    if(t->l==NULL && t->r==NULL){
        return 0;
    }

    int l = completoRic(t->l);
    int r = completoRic(t->r);

    if(l==0 &&  r==0)
        return -1;

    if(l!=r)
        return -1;

    return l+1;

}

int completo(albero t){
    if(t==NULL)
        return 1;
    int ris = completoRic(t);

    return ris!=-1;
}

/* ================================================================ PRE TEST ================================================================ */


int conta_nodi_foglie(albero t){
    if(t==NULL) return 0;

    int count = 0;
    if(t->l==NULL && t->r==NULL){
        count++;
    }
    return count + conta_nodi_foglie(t->l) + conta_nodi_foglie(t->r);
}

int foglia_dx(albero t){
    if(t==NULL) return 0;

    if(t->r!=NULL){
        if(t->r->l==NULL && t->r->r==NULL)
            return 1;
    }
    return foglia_dx(t->l) || foglia_dx(t->r);
}

int foglia_info_0(albero t){
    if(t==NULL) return 0;

    if((t->l==NULL && t->r==NULL) && t->info==0)
        return 1;
    
    return foglia_info_0(t->l) || foglia_info_0(t->r);
}

int foglie_2_info_0(albero t){
    if(t==NULL) return 0;

    int count = 0;
    if(t->l==NULL && t->r==NULL){
        if(t->info==0){
            count++;
            if(count==2)
                return 1;
        }
    }
    return count + foglie_2_info_0(t->l) || foglie_2_info_0(t->r);
}

int height(albero t){
    if(t==NULL) return -1;

    int l = height(t->l);
    int r = height(t->r);

    int max = l;
    if(r>max){
        max = r;
    }
    return l+1;
}

int numero_nodi(albero t){
    if(t==NULL) return 0;

    return 1 + numero_nodi(t->l) + numero_nodi(t->r);
}

int numero_nodi_campo_info_uguale_a(albero t, int value){
    if(t==NULL) return 0;

    int count = 0;
    if(t->info==value){
        count++;
    }
    return count + numero_nodi_campo_info_uguale_a(t->l, value) + numero_nodi_campo_info_uguale_a(t->r, value);
}

int verifica(albero t, int h){
    if(t==NULL) return 0;

    if(t->info==h) return 1;

    return verifica(t->l, h) || verifica(t->r, h);
}

int campo_info_uguale_altezza(albero t){
    
    int h = height(t);
    int verificato = verifica(t, h);

    return verificato;
}

int conta_nodi_interni(albero t){
    if(t==NULL) return 0;

    nodo* l = t->l;
    nodo* r = t->r;

    int count = 0;
    if((t->l!=NULL && t->r==NULL) || (t->l==NULL && t->r!=NULL) || (t->l!=NULL && t->r!=NULL)){
        count++;
    }
    return count + conta_nodi_interni(t->l) + conta_nodi_interni(t->r);
}

int campo_info_uguale_radice_ric(albero t, int i){
    if(t==NULL) return 0;

    if(t->info == i)    return 1;

    return campo_info_uguale_radice_ric(t->l, i+1) || campo_info_uguale_radice_ric(t->r, i+1);
}

int campo_info_uguale_radice(albero t){
    if(t==NULL) return 0;

    verifica(t, 0);
}

int nodo_con_entrambi_figli_foglie(albero t){
    if(t==NULL) return 0;

    if(t->l!=NULL && t->r!=NULL){
        if((t->l->l==NULL && t->l->r==NULL) && (t->r->l==NULL && t->r->r==NULL)) return 1;
    }

    return nodo_con_entrambi_figli_foglie(t->l) || nodo_con_entrambi_figli_foglie(t->r); 
}

int numero_nodi_info_distanza_radice_ric(albero t, int i){
    if(t==NULL) return 0;

    int count = 0;
    if(t->info == i){
        count++;
    }
    return count + numero_nodi_info_distanza_radice_ric(t->l, i+1) + numero_nodi_info_distanza_radice_ric(t->r, i+1);
}

int numero_nodi_info_distanza_radice(albero t){
    
    int h = height(t);
    
    numero_nodi_info_distanza_radice_ric(t, 0);
}

int numero_nodi_foglie(albero t){
    if(t==NULL) return 0;

    int count = 0;
    if(t->l==NULL && t->r==NULL){
        count++;
    }
    return count + numero_nodi_foglie(t->l) + numero_nodi_foglie(t->r);
}

int ogni_nodo_due_figli(albero t){
    if(t==NULL) return 0;

    if(t->l!=NULL && t->r!=NULL){
        return 1;
    }
    return ogni_nodo_due_figli(t->l) && ogni_nodo_due_figli(t->r);
}


int main(){
    //albero t1 = newTree();
    albero t2 = NULL;

    /* Aggiungi radice */
    add_root(&t2, 3);
    /* Aggiungi nodo a sinistra */
    nodo* l_t2 = add_left(t2, 1);   // 2
    /* Aggiungi nodo a destra */
    //nodo* r_t2 = add_right(t2, 0);
    /* Aggiungi nodo a sinistra e a destra del nodo '1'*/
    nodo* ll_t2 = add_left(l_t2, 1);
    nodo* lr_t2 = add_right(l_t2, 6);
    /* Aggiungi nodo a sinistra del nodo '3'*/
    //nodo* sinistro_di_ll_t2 = add_left(ll_t2, 5);

/* ALBERI

IN ORDINE SIA SOPRA CHE SOTTO

- Numero nodi che hanno entrambi i figli foglie -OK
- Numero nodi foglie -OK 
- Esiste foglia a destra -OK
- Esiste foglia a sinistra -OK
- Foglia con campo info 0 	-OK
- Due foglie con campo info 0	-OK
- Altezza -OK
- Numero nodi -OK
- Numero nodi con campo info pari a 'x'	-OK
- Esiste campo info stessa altezza albero	-OK
- Conta nodi interni	-OK
- Entrambi figli foglie	-OK
- Esiste nodo campo info uguale distanza radice	-OK
- Numero nodi con campo info uguale distanza radice -OK
- Verifica se ogni nodo di un albero binario ha 2 figli (tranne le foglie)	-OK
- ULTIMO PRE TEST - Verifica se esiste un nodo che abbia due nodi figli e il figlio a sx ha campo info uguale al figlio a dx
- Somma e conta nodi -OK (Si ma non trovo dove l'ho presa e non mi ricordo se doveva ritornare la somma sommata al numero di nodi)

INVENTATE

- Albero con soli figli a sinistra -OK
- Conta nodi a sx (variante a dx) - OK
- Nodi interni con campo info uguale distanza radice
- Nodi foglie con campo info uguale distanza radice
- Nodi con campo info uguale
 */

    /* OK - Conta nodi con figli foglie */
    printf("\nNumero nodi foglie (atteso: 3): %d.\n", conta_nodi_foglie(t2));

    /* OK - Esiste foglia a destra */
    printf("\nEsiste foglia a destra (atteso: 1): %d.\n", foglia_dx(t2));

    /* OK - Esiste foglia a sinistra */
    //printf("\nEsiste foglia a sinistra (atteso: 1): %d.\n", foglia_sx(t2));

    /* OK - Esiste foglia con campo info 0 */
    printf("\nEsiste foglia con campo info 0 (atteso: 0): %d.\n", foglia_info_0(t2));

    /* OK - Esistono due foglie con campo info 0 */
    printf("\nEsistono 2 foglie con campo info 0 (atteso: 1): %d.\n", foglie_2_info_0(t2));

    /* OK - Altezza dell'albero */
    printf("\nAltezza albero (atteso 2): %d.\n", height(t2));

    /* OK - Numero nodi */
    printf("\nNumero nodi albero (atteso 5): %d.\n", numero_nodi(t2));

    /* OK - Nodi con campo info uguale a '2'*/
    printf("\nNumero di nodi con campo info pari a 2 (atteso 1): %d.\n", numero_nodi_campo_info_uguale_a(t2, 6));

    /* OK - Esiste nodo con campo info pari all'altezza dell'albero */
    printf("\nEsiste nodo con campo info pari altezza albero (altezza albero = 2 - Atteso 1): %d.\n", campo_info_uguale_altezza(t2));

    /* OK - Conta nodi interni (i nodi interni sono 2, root e l)*/
    printf("\nNumero nodi interni (atteso 2): %d.\n", conta_nodi_interni(t2));

    /* OK - Esiste nodo con campo info uguale alla sua distanza dalla radice */
    printf("\nEsiste nodo con campo info pari alla sua distanza dalla radice (atteso 1): %d.\n", campo_info_uguale_radice(t2));

    /* OK - Esiste un nodo con entrambi i figli foglie */
    printf("\nEsiste un nodo con entrambi figli foglie (atteso 1): %d.\n", nodo_con_entrambi_figli_foglie(t2));

    /* OK - Numero nodi con campo info pari alla loro distanza dalla radice */
    printf("\nNumero nodi con campo info pari alla loro distanza dalla radice (atteso 2): %d.\n", numero_nodi_info_distanza_radice(t2));

    /* OK - Numero di nodi che hanno entrambi i figli foglie */
    printf("\nNumero nodi che hanno entrambi i figli foglie: %d.\n", numero_nodi_foglie(t2));

    /* OK - Ogni nodo dell'albero ha due figli tranne le foglie */
    printf("\nOgni nodo dell'albero ha due figli (atteso 1): %d.\n", ogni_nodo_due_figli(t2));

    /* OK - Somma e conta nodi */
    // NB. non ritrovo da dove l'ho presa la consegna e non ricordo cosa doveva ritornare *PACE*

    /* INVENTATE */
    
    /* Solo nodi a sinistra */
    //printf("\nSolo nodi a sinistra (atteso 1): %d.\n", solo_nodi_sx(t2));

    /* Conta nodi a sinistra */
    //printf("\nConta nodi a sinistra (atteso 2): %d.\n", conta_solo_nodi_sinistra(t2));

}

//int main1(){

    //albero t1 = newTree();
    //albero t1 = NULL;
    
    /* Is empty */
    //printf("\nis empty: %d.\n", is_empty(t1)); // atteso 1

    /* Aggiungi radice */
    //add_root(&t1, 1);

    /* Aggiungi nodo a sinistra */
    //nodo* l = add_left(t1, 2);
    /* Aggiungi nodo a destra */
    //nodo* r = add_right(t1, 3);

    //nodo* ll = add_left(l, 4);
    //nodo* lr = add_right(l, 6);

    /* Is empty */
    //printf("\nis empty: %d.\n", is_empty(t1));  // atteso 0

    /* Search pre */
    //printf("\n==Search pre\n");
    //printf("\nNodo con valore 5 trovato (atteso 1): %d.\n", search_pre(t1, 5)!=NULL);
    //printf("\nNodo con valore 2 trovato (atteso 1): %d.\n", search_pre(t1, 2)!=NULL);

    /* Search pre versione 1 */
    //printf("\n==Search pre v1\n");
    //printf("\nNodo con valore 4 trovato (atteso 1): %d.\n", search_pre_v1(t1, 4));
    //printf("\nNodo con valore 2 trovato (atteso 1): %d.\n", search_pre_v1(t1, 2));

    /* Search_post */
    //printf("\n==Search post\n");
    //printf("\nNodo con valore 4 trovato (atteso 1): %d.\n", search_post(t1, 4)!=NULL);
    //printf("\nNodo con valore 2 trovato (atteso 1): %d.\n", search_post(t1, 2)!=NULL);

    /* Search post versione 1 */
    //printf("\n==Search post v1\n");
    //printf("\nNodo con valore 4 trovato (atteso 1): %d.\n", search_post_v1(t1, 4));
    //printf("\nNodo con valore 2 trovato (atteso 1): %d.\n", search_post_v1(t1, 2));

    /* Search sim */
    //printf("\n==Search sim\n");
    //printf("\nNodo con valore 4 trovato (atteso 1): %d.\n", search_sim(t1, 4));
    //printf("\nNodo con valore 3 trovato (atteso 1): %d.\n", search_sim(t1, 3));
    
    /* Search sim v1 */
    //printf("\n==Search sim v1\n");
    //printf("\nNodo con valore 4 trovato (atteso 1): %d.\n", search_sim_v1(t1, 4));
    //printf("\nNodo con valore 3 trovato (atteso 1): %d.\n", search_sim_v1(t1, 3));
    
    /* Funzione conta nodi */
    //printf("\nNodi contati (atteso 5): %d.\n", contaNodi(t1));

    /* Funzione verifica albero se è cammino */
    //printf("\nCammino (atteso 0): %d.\n", cammino(t1));

    /* Funzione che calcola l'altezza dell'albero */
    //printf("\nAltezza (atteso: nd): %d.\n", altezza(t1));

    /* Funzione che calcola la media dei nodi nell'albero */
    //printf("\nMedia: %d.\n", media(t1));

    /* Funzione albero completo */
    //printf("\nAlbero completo (atteso 1): %d.\n", completo(t1));

    /* PRE-ESAME */
    //printf("\n====== PRE-ESAME ======\n");
//}