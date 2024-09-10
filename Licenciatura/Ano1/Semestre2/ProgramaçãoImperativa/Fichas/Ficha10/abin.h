#include <stdio.h>
#include <stdlib.h>

typedef struct nodo {
    int valor;
    struct nodo *esq, *dir;
} * ABin;


ABin newABin (int r, ABin e, ABin d);
ABin RandArvFromArray (int v[], int N);
ABin cloneABin (ABin a);
void dumpABin (ABin a, int N);
void freeABin (ABin a);

// Questão 1
ABin removeMenor (ABin *a);
void removeRaiz (ABin *a);
int removeElem (ABin *a, int x);

/*
// Questão 2
void rodaEsquerda (ABin *a);
void rodaDireita (ABin *a);
void promoveMenor (ABin *a);
void promoveMaior (ABin *a);
ABin removeMenorAlt (ABin *a);

// Questão 3
int constroiEspinha (ABin *a);
ABin equilibraEspinha (ABin *a, int n);
void equilibra (ABin *a);
*/


