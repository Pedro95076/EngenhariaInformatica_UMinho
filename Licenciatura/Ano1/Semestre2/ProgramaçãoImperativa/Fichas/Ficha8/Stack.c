#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

void initStack (Stack *s){
    *s = NULL;
}

int SisEmpty (Stack s){
    return (s == NULL);
}

int push (Stack *s, int x){
    
    Stack aux = malloc(sizeof(struct slist));
    if (aux == NULL) return 1;
    
    aux->valor = x;
    aux->prox = *s;
    *s = aux;
    
    return 0;
}

int pop (Stack *s, int *x){
    
    Stack aux;
    if(SisEmpty(*s))
    *x = (*s)->valor;
    aux = (*s)->prox;
    free(*s);
    *s = aux;
    
    return 0;
}

int top (Stack s, int *x){
    
    if (s == NULL) return 1; // 0 : nao é erro, diferente de 0 é erro
    //if (x == NULL) return 2;
    
    *x = s->valor; 

    return 0;
}
