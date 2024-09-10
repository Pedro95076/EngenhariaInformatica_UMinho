#include <stdio.h>
#include <math.h>

int quadrado    (int x);
int quadrado2   (int x);
int triangulo   (int x);
int triangulo2  (int x);
void circulo (int raio);

int main() {
    int a;
    int escolha;

    printf ("Escolha um exercicio : 1, 2, 31, 32 ou 4\n");
    scanf ("%d", &escolha);
    printf ("Escolha o tamanho da figura\n");
    scanf ("%d", &a);

    if (escolha == 1) {
        quadrado (a);
    } else if (escolha == 2) {
        quadrado2 (a);
    } else if (escolha == 31) {
        triangulo (a);
    } else if (escolha == 32) {
        triangulo2 (a);
    } else if (escolha == 4) {
        circulo (a);
    } else printf("Exercicio invalido\n");

    return 0;
}

// Funçao do exercicio 1
int quadrado (int x) {

    int i, j;

    for (i = 0; i < x; i++) {

      for (j = 0; j < x; j++) {
          printf ("#");
      }

      printf ("\n");
    }

    return 0;
}

// Funçao do exercicio 2
int quadrado2 (int x) {

    int i, j;

    for (i = 0; i < x; i++) {
        if (i % 2 == 0) {
            for (j = 0; j < x; j++) {
                if (j % 2 == 0) {
                    printf("#");
                } else printf("_");
            }

        } else for (j = 0; j < x; j++) {
            if (j % 2 == 0) {
                printf("_");
            } else printf("#");
        }

        printf("\n");
    }

    return 0;
}

/*
// Exemplo de outra funcao
void xadrez (int n) {
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            if ((i+j)%2 == 0) printf ("#");
            else printf ("_");
        }
        printf ("\n");
    }
}
 */

// Funçao do exercicio 3 (parte 1)
int triangulo (int x) {

    int i, j;

    // Primeira parte
    for (i = 1; i < (x+1); i++) {
         for (j = 0; j < i; j++) {printf("#");}
         printf("\n");
    }

    // Segunda parte
    for (i = 1; i < x; i++) {
        for (j = 0; j < (x-i); j++) {printf("#");}
        printf("\n");
    }

    return 0;
}

// Funçao do exercicio 3 (parte 2)
int triangulo2 (int x) {

    int i = 0;
    int j;
    int k = 1;

    while (i < x) {
        for (j = 0; j < (x-i-1); j++) printf(" ");
        for (j = 0; j < k; j++) printf("#");
        i++;
        k = k + 2;
        printf("\n");
    }

    return 0;
}

// Funçao do exercicio 4
void circulo (int raio) {

    double centroX = raio + 1;
    double centroY = raio + 1;
    double i, j;

    for (i = 1; i < 2*raio + 2; i++) {
        for (j = 1; j < 2*raio + 2; j++) {
            if (sqrt (pow (centroX-j, 2) + pow (centroY-i,2)) > raio) putchar(' '); else putchar('#');
        }
        putchar('\n');
    }

}














