#include "abin.h"

ABin newABin (int r, ABin e, ABin d) {
   ABin a = malloc (sizeof(struct nodo));
   if (a!=NULL) {
      a->valor = r; a->esq = e; a->dir = d;
   }
   return a;
}

ABin RandArvFromArray (int v[], int N) {
   ABin a = NULL;
    int m;
    if (N > 0){
    	m = rand() % N;
    	a = newABin (v[m], RandArvFromArray (v,m), RandArvFromArray (v+m+1,N-m-1));
    }
    return a;	
}


// Questão 1
ABin removeMenor (ABin *a){
    
    ABin aux;
    
    while ((*a)->esq /*!= NULL*/) {
        a = &((*a)->esq);
    }
    
    aux = *a;
    *a = (*a)->dir;
    
    return aux;
}

void removeRaiz (ABin *a){
    
    ABin aux;
    
    if( ( (*a)->esq == NULL) && ((*a)->dir == NULL) ) *a = NULL;
    if( ( (*a)->esq != NULL) && ((*a)->dir == NULL) ) {
        aux = *a;
        *a = (*a)->esq;
        free(aux);
    } else {
        aux = removeMenor(&(*a)->dir);
        (*a)->valor = aux->valor;
        free(aux);
    }
}

int removeElem (ABin *a, int x){
    
    while((*a) && (*a)->valor != x) {
        if((*a)->valor > x) a = &(*a)->esq;
        else a = &(*a)->dir;
    }
    
    if(*a == NULL) return 1; 
    removeRaiz(a);
    return 0;
}

/*
// Questão 2
void rodaEsquerda (ABin *a){
    ABin b = (*a)->dir;
    (*a)->dir = b->esq;
    b->esq = (*a);
    *a = b;
}
void rodaDireita (ABin *a){
    ABin b = (*a)->esq;
    (*a)->esq = b->dir;
    b->dir = *a;
    *a = b;
}
void promoveMenor (ABin *a){
}
void promoveMaior (ABin *a){
}
ABin removeMenorAlt (ABin *a){
    return NULL;
}

// Questão 3
int constroiEspinhaAux (ABin *a, ABin *ult){
    return (-1);
}
int constroiEspinha (ABin *a){
    ABin ult;
    return (constroiEspinhaAux (a,&ult));
}

ABin equilibraEspinha (ABin *a, int n) {
	return NULL;
}

void equilibra (ABin *a) {
}
*/
