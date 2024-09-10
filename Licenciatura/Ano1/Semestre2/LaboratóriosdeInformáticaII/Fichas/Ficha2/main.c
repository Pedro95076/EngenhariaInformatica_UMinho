#include <stdio.h>
#include <math.h>
#include <assert.h>

int main() {
    int a, b, c;
    double p;
    double area;

    assert (scanf ("%d%d%d", &a, &b, &c) == 3);

    p = a+b+c;
    area = sqrt ((p/2)*(p/2-a)*(p/2-b)*(p/2-c));

    if (a+b<=c || a+c<=b || b+c<=a) {
        printf ("INVALIDO\n");
    } else if (a*a + b*b == c*c || a*a + c*c == b*b || b*b + c*c == a*a) {
        printf ("RETANGULO %.0f %.2f\n", p, area);
    } else if (a == b && a==c && b==c) {
        printf ("EQUILATERO %.0f %.2f\n", p, area);
    } else if ((a==b && c != a && c != b) || (a==c && b!=a && b!= c) || (b==c && a!=b && a!=c)) {
        printf("ISOSCELES %.0f %.2f\n", p, area);
    } else {
        printf("ESCALENO %.0f %.2f\n", p, area);
    }


    return 0;
}