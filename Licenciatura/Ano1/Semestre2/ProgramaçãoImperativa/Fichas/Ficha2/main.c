#include <stdio.h>

float multInt1 (int n, float m);
float multInt2 (int n, float m);
int mdc1 (int a, int b);
int mdc2 (int a, int b);
int mdc3 (int a, int b);
int fib1 (int a);
int fib2 (int a);

int main( ) {

    int escolha;
    int n, a, b;
    float m;
    char escolha2;

    printf("Escolha um dos exercicios (1,2,3,4,5 ou 6) : ");
    scanf ("%d", &escolha);

    switch (escolha) {
        case 1 : printf("Ex.1 : Podemos calcular o produto de um numero m por um inteiro n atraves de um somatorio de n parcelas constantes (e iguais a m).\n") ;
                 printf("Escolha o m : ");
                 scanf("%f", &m);
                 printf("Escolha o n : ");
                 scanf("%d", &n);
                 printf("%.2f\n", multInt1(n,m));
                 break;
        case 2 : printf("Ex.2 : Calcular o produto m por n.\n") ;
                 printf("Escolha o m : ");
                 scanf("%f", &m);
                 printf("Escolha o n : ");
                 scanf("%d", &n);
                 printf("%.2f\n", multInt2(n,m));
                 break;
        case 3 : printf("Ex.3 : Calcula o maximo divisor comum entre dois inteiros nao negativos.\n") ;
                 printf("Escolha os dois numeros : ");
                 scanf("%d%d", &a, &b);
                 printf("%d\n", mdc1 (a,b));
                 break;
        case 4 : printf("Ex.3 : Calcula o maximo divisor comum entre dois inteiros nao negativos.\n") ;
                 printf("Escolha os dois numeros : ");
                 scanf("%d%d", &a, &b);
                 printf("%d\n", mdc2 (a,b));
                 break;
        case 5 : printf("Ex.3 : Calcula o maximo divisor comum entre dois inteiros nao negativos.\n") ;
                 printf("Escolha os dois numeros : ");
                 scanf("%d%d", &a, &b);
                 printf("%d\n", mdc3 (a,b));
                 break;
        case 6 : printf("Este exercicio tem 2 alineas (a e b), escolhe uma : ");
                 scanf("%s", &escolha2);
                 printf("Calcula o n-ésimo numero da sequencia de Fibonacci.\n");
                 printf("Escolha o n: ");
                 scanf("%d", &a);
                 switch (escolha2) {
                     case 'a' : printf ("%d", fib1 (a)); break;
                     case 'b' : printf("%d", fib2 (a)); break;
                     default: printf("!! Exercicio invalido !!");
                 }
                 break;

        default: printf("!! Exercicio invalido !!\n");
    }

    return 0;
}

float multInt1 (int n, float m) {

    float r = 0;

    for (int i=0; i<n; i++) r += m;

    return r;
}

// Versao recursiva vista na aula (menos eficiente)
float multIntR (int n, float m) {
    if (n == 0) return 0;
    else return multIntR(n-1,m);
}

float multInt2 (int n, float m) {

    float r = 0;

    while (n>0) {

        if (n&1 == 1) r += m; // outra maneira de saber se é impar
        n = n>>1; // Para evitar a divisao
        m = m+m; // Em vez de de (2*m), pois estamos a fazer um exercicio aonde temos de implementar a operacao da multiplicaçao, logo nao faz sentido usarmos a multiplicaçao dentro dessa funçao.
    }

    return r;
}

int mdc1 (int a, int b) {
    int r;
    int troca;

    if (b<a) {
        troca = b;
        b = a;
        a = troca;
    }

    for (int i = 1; i < a+1; i++) {
        if (a%i == 0 && b%i == 0) r = i;
    }

    return r;
}

int mdc2 (int a, int b) {

    while (a>0 && b>0) {
        if (a<b) b = b-a;
        else a = a-b;
    }

    if (a==0) return b;
    else return a;
}

int mdc3 (int a, int b) {

    while (a != 0 && b != 0) {
        if (a<b) b = b%a;
        else if (a>b) a = a%b;
        else a = b%a;
    }

    if (a==0) return b;
    else return a;
}

int fib1 (int a) {

    if (a<=2) return 1;
    else return fib1(a - 1) + fib1(a - 2);

}

int fib2 (int a) {

    int x = 1;
    int y = 1;
    int troca;

    if (a==1 || a==2) return x;
    while (a>2) {
        troca = y;
        y += x;
        x = troca;
        a--;
    }

    return y;
}














