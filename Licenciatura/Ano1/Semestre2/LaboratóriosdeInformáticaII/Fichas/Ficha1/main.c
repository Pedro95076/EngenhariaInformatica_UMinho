#include <stdio.h>
#include <assert.h>

int main() {
    int a, b;
    assert (scanf ("%d%d", &a, &b) == 2);
    printf("%d\n", a*a + b*b);
    return 0;
}