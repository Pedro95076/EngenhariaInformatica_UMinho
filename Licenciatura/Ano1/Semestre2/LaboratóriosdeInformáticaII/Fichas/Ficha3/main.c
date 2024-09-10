#include <stdio.h>
#include <assert.h>

int main() {

    int a, i, j;
    int total;

    assert (scanf ("%d", &a) == 1);

    total = a*2;

    for (i = 1; i < a+1; i++) {
        for (j = 1; j < i+1; j++) {printf("*");}
        for (j = 1; j < total - i - i + 1; j++) {printf(".");}
        for (j = 1; j < i+1; j++) {printf("*");}
        printf("\n");
    }

    for (i = (a-1); i > 0; i--) {
        for (j = 0; j < i; j++) {printf("*");}
        for (j = 0; j < total - i - i; j++) {printf(".");}
        for (j = 0; j < i; j++) {printf("*");}
        printf("\n");
    }

    return 0;
}
