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

/* ====================================================================================================== */

int conta_nodi_foglie(albero t){
    if(t==NULL) return 0;

    int count = 0;
    if(t!=NULL) 
        count++;

    return count + conta_nodi_foglie(t->l)+conta_nodi_foglie(t->r);
}

int foglia_dx(albero t){
    if(t==NULL) return 0;

    if(t->r!=NULL)
        return 1;
    
    return foglia_dx(t->l) || foglia_dx(t->r);
}

int foglia_info_0(albero t){
    if(t==NULL) return 0;

    if((t->l==NULL && t->r==NULL) && (t->info==2))
        return 1;

    return foglia_info_0(t->l) || foglia_info_0(t->r);
}

int foglie_2_info_0(albero t){
    if(t==NULL) return 0;

    int count = 0;
    if((t->l==NULL && t->r==NULL) || (t->info==2))
        count++;
        if(count==2)
            return 1;

    return count + foglie_2_info_0(t->l) || foglie_2_info_0(t->r);
}

int altezza(albero t){
    if(t==NULL) return -1;

    int l = altezza(t->l);
    int r = altezza(t->r);

    int max = l;
    if(r>max){
        max = r;
    }
    return max+1;
}

int numero_nodi(albero t){
    if(t==NULL) return 0;

    return 1 + numero_nodi(t->l) + numero_nodi(t->r);
}

int numero_nodi_campo_info_uguale_a(albero t){
    if(t==NULL) return 0;

    int count = 0;
    if(t->info==2)
        count++;

    return count + numero_nodi_campo_info_uguale_a(t->l) + numero_nodi_campo_info_uguale_a(t->r);
}

int campo_info_uguale_altezzaRIC(albero t, int h){
    if(t==NULL) return 0;

    if(t->info==h)
        return 1;

    return campo_info_uguale_altezzaRIC(t->l, h) || campo_info_uguale_altezzaRIC(t->r, h);
}

int campo_info_uguale_altezza(albero t){

    int h = altezza(t);
    int ris = campo_info_uguale_altezzaRIC(t, h);

    return ris;
}

int campo_info_uguale_radice_VER(albero t, int i){
    if(t==NULL) return 0;

    if(t->info==i)
        return 1;

    return campo_info_uguale_radice_VER(t->l, i) || campo_info_uguale_radice_VER(t->r, i);
}

int campo_info_uguale_radice(albero t){
    if(t==NULL) return 0;

    campo_info_uguale_radice_VER(t, 0);
}

int nodo_con_entrambi_figli_foglie(albero t){
    if(t==NULL) return 0;

    if(t->l==NULL && t->r==NULL)
        return 1;

    return nodo_con_entrambi_figli_foglie(t->l) && nodo_con_entrambi_figli_foglie(t->r);
}

int numero_nodi_info_distanza_radiceRIC(albero t, int i){
    if(t==NULL) return 0;

    int count = 0;
    if(t->info==i)
        count++;

    return count + numero_nodi_info_distanza_radiceRIC(t->l, i+1) + numero_nodi_info_distanza_radiceRIC(t->r, i+1);
}

int numero_nodi_info_distanza_radice(albero t){
    if(t==NULL) return 0;

    numero_nodi_info_distanza_radiceRIC(t, 0);
}

int numero_nodi_foglie(albero t){
    if(t==NULL) return 0;

    int count = 0;
    if(t->l==NULL && t->r==NULL)
        count++;

    return count + numero_nodi_foglie(t->l) + numero_nodi_foglie(t->r); 
}

int solo_nodi_sx(albero t){
    if(t==NULL) return 0;

    if(t->l!=NULL && t->r==NULL)
        return 1;
    
    return solo_nodi_sx(t->l);
}

int main(){
    //albero t1 = newTree();
    albero t2 = NULL;

    /* Aggiungi radice */
    add_root(&t2, 1);
    /* Aggiungi nodo a sinistra */
    nodo* l_t2 = add_left(t2, 1);   // 2
    /* Aggiungi nodo a destra */
    //nodo* r_t2 = add_right(t2, 0);
    //nodo* ll_t2 = add_left(l_t2, 2);
    //nodo* lr_t2 = add_right(l_t2, 0);


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
    printf("\nAltezza albero (atteso 2): %d.\n", altezza(t2));

    /* OK - Numero nodi */
    printf("\nNumero nodi albero (atteso 5): %d.\n", numero_nodi(t2));

    /* OK - Nodi con campo info uguale a */
    printf("\nNumero di nodi con campo info pari a 2 (atteso 1): %d.\n", numero_nodi_campo_info_uguale_a(t2));

    /* OK - Esiste nodo con campo info pari all'altezza dell'albero */
    printf("\nEsiste nodo con campo info pari altezza albero (altezza albero = 2 - Atteso 1): %d.\n", campo_info_uguale_altezza(t2));

    /* OK - Conta nodi interni (i nodi interni sono 2, root e l)*/
    //printf("\nNumero nodi interni (atteso 2): %d.\n", conta_nodi_interni(t2));

    /* OK - Esiste nodo con campo info uguale alla sua distanza dalla radice */
    printf("\nEsiste nodo con campo info pari alla sua distanza dalla radice (atteso 1): %d.\n", campo_info_uguale_radice(t2));

    /* OK - Esiste un nodo con entrambi i figli foglie */
    printf("\nEsiste un nodo con entrambi figli foglie (atteso 1): %d.\n", nodo_con_entrambi_figli_foglie(t2));

    /* OK - Numero nodi con campo info pari alla loro distanza dalla radice */
    printf("\nNumero nodi con campo info pari alla loro distanza dalla radice (atteso 2): %d.\n", numero_nodi_info_distanza_radice(t2));

    /* OK - Numero di nodi che hanno entrambi i figli foglie */
    printf("\nNumero nodi che hanno entrambi i figli foglie (atteso 2): %d.\n", numero_nodi_foglie(t2));

    /* OK - Ogni nodo dell'albero ha due figli tranne le foglie */
    //printf("\nOgni nodo dell'albero ha due figli (atteso 1): %d.\n", ogni_nodo_due_figli(t2));

    /* OK - Somma e conta nodi */
    // NB. non ritrovo da dove l'ho presa la consegna e non ricordo cosa doveva ritornare *PACE*

    /* INVENTATE */
    
    /* Solo nodi a sinistra */
    printf("\nSolo nodi a sinistra (atteso 1): %d.\n", solo_nodi_sx(t2));

    /* Conta nodi a sinistra */
    //printf("\nConta nodi a sinistra (atteso 2): %d.\n", conta_solo_nodi_sinistra(t2));

    /* Il nonno ha soltanto un figlio a sinistra */
    //printf("\nEsiste un nodo nonno che ha soltanto figli a sinistra (atteso 0): %d.\n" nodo_nonno(t2));

}