#include <stdio.h>
#include <assert.h>

int main() {

    int matriz [10][10];
    int x;
    int i;
    int j;
    int k;
    int a;
    int b;


    // inicializar a matriz pondo todos os elementos a 0
    for (i = 0; i < 10; i++) {
        for (j = 0; j < 10; j++) {
            matriz [i][j] = 0;
        }
    }

    // guardar cada numero de vezes inserido de um numero no elemento da matriz correspondente
    assert (scanf ("%d", &x) == 1);
    while (x != -1) {

        for (k = 0; x >= 0; k++) {
            if (x < 10) {
                matriz[k][x] = matriz[k][x] + 1;
                break;
            }
            else x -= 10;
        }

        assert (scanf ("%d", &x) == 1);
    }

    // imprimir a matriz no formato diagrama de caule
    for (a = 0; a < 10; a++) {

        printf("%d|", a);
        for (b = 0; b < 10; b++) {
            while (matriz [a][b] > 0) {
                printf("%d", b);
                matriz [a][b] = matriz [a][b]-1;
            }
        }
        putchar ('\n');

    }

    return 0;
}