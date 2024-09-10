#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

// Static stacks 

void SinitStack (SStack s){
	s->sp = 0;
}

int  SisEmpty (SStack s){
    int r;
    if (s->sp == 0) r = 1;
    else r = 0;
    return r; // se for falso retorna 0, se for verdadeiro retorna alguma coisa diferente de 0
}

int  Spush (SStack s, int x){
	// primeiro detetar se há capacidade no array
	if (s->sp == Max) return 1;
	// Se houver espaço, inserir o valor na stack
	s->values[s->sp] = x;
	s->sp++;
	
	return 0;
}

int  Spop (SStack s, int *x) {
	int r=0;
	if (s->sp == 0) r = 1;
	else {
	    s->sp--;
	    *x = s->values[s->sp];
	}
	return r;
}

int  Stop (SStack s, int *x) {
	int r=0;
	if (s->sp == 0) r = 1;
	else {
	    *x = s->values[s->sp-1];
	}
	return r;
}

void ShowSStack (SStack s){
    int i;
    printf ("%d Items: ", s->sp);
    for (i=s->sp-1; i>=0; i--) 
        printf ("%d ", s->values[i]);
    putchar ('\n');
}

// Stacks with dynamic arrays

int dupStack (DStack s) {
	int r = 0, i;
	int *t = malloc (2*s->size*sizeof(int)); // Neste caso estamos a reservar o dobro do espaco que tinhamos antes

	if (t == NULL) r = 1; // verificar o resultado do malloc para ter certeza que a alocacao de memoria nao falha
	else {
		for (i=0; i<s->size; i++) // copiar os elementos
			t[i] = s->values[i]; // para a nova memoria alocada
		free (s->values); // libertar a memoria antiga
		s->values = t; // guardo o t em values, ou seja, values fica a apontar para a nova zona de memoria
		s->size*=2; // muda o valor do tamanho total da struct
	}
	return r;
	
	/*
	Esta funcao copia os elementos na struct inicial para a outra que foi criada com um espaco maior
	*/
}

/*
int dupStack (DStack s) {
	int r = 0, i;
	int *t = realloc (s->values, 2*s->size*sizeof(int)); // Neste caso estamos a reservar o dobro do espaco que tinhamos antes

	if (t == NULL) r = 1; // verificar o resultado do malloc para ter certeza que a alocacao de memoria nao falha
	else {
		s->values = t; // guardo o t em values, ou seja, values fica a apontar para a nova zona de memoria
		s->size*=2; // muda o valor do tamanho total da struct
	}
	return r;
*/	
	/*
	Esta funcao copia os elementos na struct inicial para a outra que foi criada com um espaco maior
	*/
//}

void DinitStack (DStack s) {
		s->sp = 0;
		s->size = 1; // memoria a ser alocada inicialmente (é aconselhado alocar um pedaco maior ja no começo)
		s->values = malloc (s->size * sizeof(int)); // alocar memoria
}

int  DisEmpty (DStack s) {
    int r;
    if (s->sp == 0) r = 1;
    else r = 0;
    return r; // se for falso retorna 0, se for verdadeiro retorna alguma coisa diferente de 0
}

int  Dpush (DStack s, int x){
	int r=0;
	if (s->sp == s->size) { // se nao tiver capacidade aloca mais memoria
	    r = dupStack(s);
	}
	if (r == 0) { // ou seja, se tiver capacidade
	    s->values[s->sp] = x;
	    s->sp++;
	}
	return r;
}

int  Dpop (DStack s, int *x){
	int r=0;
	
	return r;
}

int  Dtop (DStack s, int *x){
	int r=0;
	
	return r;
}

void ShowDStack (DStack s){
    int i;
    printf ("%d Items: ", s->sp);
    for (i=s->sp-1; i>=0; i--) 
        printf ("%d ", s->values[i]);
    putchar ('\n');
}
