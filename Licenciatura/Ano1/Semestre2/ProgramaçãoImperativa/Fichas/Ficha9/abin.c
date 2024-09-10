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

#define max(x,y) (x > y ? x : y)
int altura (ABin a){
    
    int l, r;
    
    if(!a) return 0; // a == NULL
    
    l = altura(a->esq);
    r = altura(a->dir);
    return 1 + max(l,r);
}

int nFolhas (ABin a){
    
    int l, r;
    
    if(!a) return 0; // a == NULL
    if(!a->esq && !a->dir) return 1; // se for uma folha
    return nFolhas(a->esq) + nFolhas(a->dir);
}

ABin maisEsquerda (ABin a){
    
    if (!a) return NULL;
    
    while(a->esq) { 
    a = a->esq;
    }
    return a;
}

void imprimeNivel (ABin a, int l){
    
    if (a) {
        if (!l) printf("%d ", a->valor); // l == 0
        else {
            if (a->esq) imprimeNivel(a->esq, l-1);
            if (a->dir) imprimeNivel(a->dir, l-1);
        }
    }
}

int procuraE (ABin a, int x){
    
    if(!a) return 0;
    if(a->valor == x) return 1;
    else return ((procuraE(a->esq, x)) || (procuraE(a->dir, x)));
    
    //return (a && ((a->valor == x) || procuraE(a->esq,x) || procuraE(a->dir,x)));
}

struct nodo *procura (ABin a, int x){
    
    while(a && a->valor != x){
        if(a->valor > x) a = a->esq;
        else a = a->dir;
    }
    
    return a;
}

int nivel (ABin a, int x){
    
    int r = 0;
    
    while(a && a->valor != x){
        if(a->valor > x) a = a->esq;
        else a = a->dir;
        r++;
    }
    
    if (!a) r = -1;
    return r;
}

void imprimeAte (ABin a, int x){
   
    if(a) {
        imprimeAte(a->esq, x);
        if(x >= a->valor) {
            printf("%d ", a->valor);
            imprimeAte(a->dir, x);
        }
    }
}
