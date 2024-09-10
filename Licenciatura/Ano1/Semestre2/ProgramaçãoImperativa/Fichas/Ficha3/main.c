#include <stdio.h>

// Lista de funçoes
void swapM (int *x, int *y);
void swap (int v[], int i, int j);
int soma (int v[], int n);
void inverteArray (int v[], int n);
int maximum (int v[], int n, int *m);
void quadrados (int q[], int n);
void pascal (int v[], int n);

int main() {

    int escolha;
    int x, y, m;
    int v3[] = {0,1,2,3,4,5,6,7,8,9};             // Vetor usado na pergunda 3
    int v4[] = {10,20,30,40,50,100};              // Vetor usado na pergunda 4
    int tamanhoV4 = 6;                            // Tamanho do vetor da pergunta 4
    int v5[] = {0,1,2,3,4,5,6,7,8,9};             // Vetor usado na pergunda 5
    int tamanhoV5 = 10;                           // Tamanho do vetor da pergunta 5
    int v6[] = {35,28,55,36,11,9,-7,-15,-90, 40}; // Vetor usado na pergunta 6
    int tamanhoV6 = 10;                           // Tamanho do vetor da pergunta 6
    int v7[10];                                   // Vetor usado na pergunta 7
    int tamanhoV7 = 10;                           // Tamanho do vetor da pergunta 7

    printf("Escolha um exercicio (2,3,4,5,6) :\n");
    scanf("%d", &escolha);
    switch (escolha) {
        case 2 : printf("Escolha dois numeros para fazer a troca : ");
                 scanf("%d%d", &x, &y);
                 swapM (&x, &y);
                 printf("%d %d\n", x, y);
                 break;
        case 3 : printf("Escolha que 2 posicoes (0 a 9) para fazer a troca do seguinte vetor :\n0 1 2 3 4 5 6 7 8 9\n --> ");
                 scanf("%d%d", &x, &y);
                 swap (v3, x, y);
                 for (int i=0; i<10; i++) printf("%d ", v3[i]); putchar('\n');
                 break;
        case 4 : printf("Calcula a soma dos delementos de um vetor com N inteiros (já prédefinido).\n");
                 printf("%d\n", soma(v4, tamanhoV4));
                 break;
        case 5 : printf("Inverte um array (já prédefinido).\n");
                 for (int i=0; i<tamanhoV5; i++) printf("%d ", v5[i]); putchar('\n');
                 inverteArray (v5, tamanhoV5);
                 for (int i=0; i<tamanhoV5; i++) printf("%d ", v5[i]); putchar('\n');
                 break;
        case 6 : printf("Coloca no pointer o maior valor do vetor (já prédefinido).\n");
                 x = maximum (v6, tamanhoV6, &m);
                 printf("O maior valor do vetor e que está no pointer é : %d\n", m);
                 printf ("O valor do return da função foi : %d\n", x);
                 break;
    }

    return 0;
}

void swapM (int *x, int *y) {

    int troca;

    troca = *x;
    *x = *y;
    *y = troca;
}

void swap (int v[], int i, int j) {

    int troca;

    troca = v[i];
    v[i] = v[j];
    v[j] = troca;
}

int soma (int v[], int n) {

    int total = 0;

    for (int i=0; i<n; i++)
    total += v[i];

    return total;
}

void inverteArray (int v[], int n) {

    int i, j;

    for (i=0, j=n-1; i<n/2; i++, j--){
        swap(v, i, j); // Para fazer com o swapM : 
    } 
}

int maximum (int v[], int n, int *m){

    int maximo = 0;

    for (int i=0; i<n; i++){
        if (v[i]>maximo) maximo = v[i];
    }

    *m = maximo;

    if (n>0) return 0; else return 1;
}

/*
void quadrados (int q[], int n) {

    int i;

    for (i=0; i<N; i++) q[i] = i*i;
}
*/

void quadrados (int q[], int n) {

    int i;

    q[0] = 0;
    for (i=1; i<n; i++) q[i] = q[i-1] + i + i - 1;
}

/* Recursiva
void pascal (int v[], int n) {

    int i;

    if (n == 0) v[0] = 1;
    else {
        pascal (v,n-1);
        v[n] = 1;
        for (i=n-1; i>o; i--) v[i] + v[i-1];
    }
}
*/

void pascal (int v[], int n) {

    int i, l;
    
    for (l = 0; l <= n; l++) {
        v[l] = 1;
        for (i = l - 1; i > 0; i--) {
            v[i] = v[i] + v[i-1];
        }
    }
}

void desenhaTrianguloP (int n) {

    int v[n+1];
    int i, l;
    
    for (l = 0; l <= n; l++) {
        v[l] = 1;
        for (i = l - 1; i > 0; i--) {
            v[i] = v[i] + v[i-1];
        }
        for (i = 0; i <= l; i++) printf("%d\t", v[i]); // \t = tab
        putchar('\n');
    }
}