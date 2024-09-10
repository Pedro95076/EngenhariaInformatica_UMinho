#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct aluno {
    int numero;
    char nome[100];
    int miniT [6];
    float teste;
} Aluno;

///////////////////////////////////////////////////////////////////
int nota (Aluno a);

void ordenaPorNum (Aluno t [], int N);
int procuraNum (int num, Aluno t[], int N);

void criaIndPorNum (Aluno t [], int N, int ind[]);
int procuraNumInd (int num, int ind[], Aluno t[], int N);

void criaIndPorNome (Aluno t [], int N, int ind[]);

void imprimeTurmaInd (int ind[], Aluno t[], int N);
//////////////////////////////////////////////////////////////////

void dumpV (int v[], int N){
    int i;
    for (i=0; i<N; i++) printf ("%d ", v[i]);
}
void imprimeAluno (Aluno *a){
    int i;
    printf ("%-5d %s (%d", a->numero, a->nome, a->miniT[0]);
    for(i=1; i<6; i++) printf (", %d", a->miniT[i]);
    printf (") %5.2f %d\n", a->teste, nota(*a));
}

/* Minha versao
int nota (Aluno a){

    int notaFinal = 0;
    int notaMiniT = 0;
    int aproveitamento = 1;

    if (!(a.teste <= 20 && a.teste >=8)) aproveitamento = 0;

    for (int i = 0; aproveitamento == 1 && i<6; i++) {
        if (a.miniT[i] <= 2 && a.miniT >= 0) notaMiniT += a.miniT[i];
        else aproveitamento = 0;
    }

    if (notaMiniT * 20 / 12 < 8) aproveitamento = 0;

    if (aproveitamento == 1) {
        notaFinal = a.teste * 0.7;
        notaMiniT = notaMiniT * 20 / 12 * 0.3;
        notaFinal += notaMiniT;
    }
    
    if (aproveitamento == 1) return notaFinal;
    else return 0;
}
*/

int nota (Aluno a){

    int soma_miniT = 0;
    int i;
    float minis;
    float final;

    for (i = 0; i < 6; i++) {
        soma_miniT += a.miniT[i];
    }

    minis = ((float) soma_miniT)/12*20;
    final = round (minis*0.3 + a.teste*0.7);

    if (a.teste < 8 || minis < 8 || final < 10) final = 0;

    return final;
}

/* procuraNum : versao para quando nao esta ordenado
int procuraNum (int num, Aluno t[], int N){

    int i = 0;

    for (i = 0; i < N && t[i].numero != num; i++);
    if (i == N) i = -1;
    return i;
}
*/

/* procuraNum : versao para quando esta ordenado
int procuraNum (int num, Aluno t[], int N){

    int i = 0;

    for (i = 0; i < N && t[i].numero < num; i++);
    if (i == N || t[i].numero != num ) i = -1;
    return i;
}
*/

// procuraNum : Versao com a pesquisa binaria
int procuraNum (int num, Aluno t[], int N) {

    int l = 0;
    int r = N-1;
    int meio;
    while (l <= r) {
        meio = (l+r) / 2;
        if (t[meio].numero == num) return meio;
        if (t[meio].numero < num) l = meio +1;
        else r = meio - 1;
    }
    return -1;
}

void swapA (Aluno t[], int i, int j) {
    Aluno aux;
	aux = t[i];
	t[i] = t[j];
	t[j] = aux;
}

void ordenaPorNum (Aluno t [], int N){

    int i;
    int flag;

    while (flag) {
        flag = 0;
        for (i = 0; i<N-1; i++) {
            if (t[i].numero > t[i+1].numero) {swapA (t,i,i+1); flag = 1;}
        }
        N--;
    }
}

int procuraNumInd (int num, int ind[], Aluno t[], int N){
    int l = 0;
    int r = N-1;
    int meio;
    while (l <= r) {
        meio = (l+r) / 2;
        if (t[ind[meio]].numero == num) return ind[meio];
        if (t[ind[meio]].numero < num) l = meio +1;
        else r = meio - 1;
    }
    return -1;
}

void swapI (int t[], int i, int j) {
    int aux;
	aux = t[i];
	t[i] = t[j];
	t[j] = aux;
}

void criaIndPorNum (Aluno t [], int N, int ind[]){
    int i, flag = 1;
    for (i=0; i<N; i++) ind[i] = i;
    while (flag) {
        flag = 0;
        for (i = 0; i<N-1; i++) {
            if (t[ind[i]].numero > t[ind[i+1]].numero) {swapI (ind,i,i+1); flag = 1;}
        }
        N--;
    }
}
void criaIndPorNome (Aluno t [], int N, int ind[]){
    int i, flag = 1;
    for (i=0; i<N; i++) ind[i] = i;
    while (flag) {
        flag = 0;
        for (i = 0; i<N-1; i++) {
            if (strcmp(t[ind[i]].nome,t[ind[i+1]].nome) > 0) {swapI (ind,i,i+1); flag = 1;}
        }
        N--;
    }
}

void imprimeTurmaInd (int ind[], Aluno t[], int N){
    int i;
    for (i=0; i<N; i++) imprimeAluno(&t[ind[i]]);
}

int main() {
    Aluno Turma1 [7] = {{4444, "André", {2,1,0,2,2,2}, 10.5}
                       ,{3333, "Paulo", {0,0,2,2,2,1},  8.7}
                       ,{8888, "Carla", {2,1,2,1,0,1}, 14.5}
                       ,{2222, "Joana", {2,0,2,1,0,2},  3.5}
                       ,{7777, "Maria", {2,2,2,2,2,1},  5.5}
                       ,{6666, "Bruna", {2,2,2,1,0,0}, 12.5}
                       ,{5555, "Diogo", {2,2,1,1,1,0},  8.5}
                       } ;
    int indNome [7], indNum [7];
    int i;
    
    printf ("\n-------------- Testes --------------\n");
    
    ordenaPorNum (Turma1, 7);
    printf ("procura 5555: %d \n", procuraNum (5555, Turma1, 7));
    printf ("procura 9999: %d \n", procuraNum (9999, Turma1, 7));
    for (i=0; i<7; imprimeAluno (Turma1 + i++));

    criaIndPorNum (Turma1, 7, indNum);
    printf ("procura 5555:%d \n",  procuraNumInd (5555, indNum, Turma1, 7));
    printf ("procura 9999:%d \n",  procuraNumInd (9999, indNum, Turma1, 7));
    criaIndPorNome (Turma1, 7, indNome);

    putchar('\n');
    putchar('\n');

    printf("Impressao da turma ordenada por ind :\n");
    imprimeTurmaInd (indNum, Turma1, 7);
    putchar('\n');
    putchar('\n');
    printf("Impressao da turma ordenada por nome :\n");
    imprimeTurmaInd (indNome, Turma1, 7);

    printf ("\n---------- Fim dos Testes ----------\n");
    
    return 0;
}
