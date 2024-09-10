#include <stdio.h>
#include <string.h>

//----------------------------------------------------------------------------------------------------//
int vogal (char c)
{
    char vogais [] = "aeiouAEIOU";
    char *v = vogais;
    while (*v) if (*v++ == c) return 1;
    return 0;
    
}

int contaVogais (char *s) 
{
    int r=0;
    while (*s)
    {
       if (vogal(*s)) r++;
       s++;
    }
    return r;
}

/* O que eu tinha feito
Mas teria de adicionar para funcionar com as vogais maisculas

int contaVogais (char *s)
{
    int i;
    int r = 0;
    int flag = 0;

    for (i = 0; flag == 0; i++) // Em vez da flag podemos por "s[i] != '\0'" ou simplesmente "s[i]"
    {
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') r++;
        if (s[i] == '\0') flag = 1; // E tirar isto
    }

    return r;
}
*/

//----------------------------------------------------------------------------------------------------//

void apaga (char *s, int i)
{
    while (s[i])
    {
        s[i] = s[i+1];
        i++;
    }
}

int retiraVogaisRep (char *s)
{
    int i, c = 0;
    for (i=0; s[i];)
    {
        if (vogal(s[i]) && s[i] == s[i+1])
        {
            c++;
            apaga (s,i);
        } else i++;
    }
    return c;
}

/* Versao com array auxiliar
int retiraVogaisRep (char *s)
{
    int i, c = 0, o = 0;
    char aux [strlen(s)+1];

    while (s[i])
    {
        if (vogal (s[i]) && s[i] == s[i+1])
        {
            c++;
        } else 
        {
            aux [o] = s[i];
            o++;
        }
        i++;
    }
    aux [o] = '\0';

    //Copiar a string aux para s
    for (i=0; aux[i]; i++) s[i] = s[i+1];
    s[i] = '\0';

    return c;
}
*/

/* O que eu tinha feito 
int retiraVogaisRep (char *s)
{
    char aux[1000];
    int tamanhoArray = strlen (s);
    int contador = 0;
    int i, j;

    for (i = 0, j = 0; i < tamanhoArray; i++)
    {
        if (s [i] == s [i+1]) contador++;
        else 
        {
            aux[j] = s [i];
            j++;
        }
    }

    troca (aux, s, tamanhoArray-contador);
    printf("A string sem as repeticoes é :\n");
    imprimirArray (s, tamanhoArray-contador);

    return contador;
}
*/

//----------------------------------------------------------------------------------------------------//

int duplicaVogais (char *s){
    return 0;
}

/* O que eu tinha feito
void troca (char *aux , char *s, int tamanho)
{
    int i;

    for (i = 0; i < tamanho; i++)
    {
        s[i] = aux [i];
    }
}

int duplicaVogais (char *s)
{
    char aux[1000];
    int tamanhoArray = strlen (s);
    int contador = 0;
    int i, j;

    for (i = 0, j = 0; i < tamanhoArray; i++, j++)
    {
        if (s[i] == 'a' || s[i] == 'e' || s[i] == 'i' || s[i] == 'o' || s[i] == 'u') 
        {
            aux [j] = s[i];
            j++;
            aux [j] = s[i];
            contador++;
        } else aux [j] = s[i];
    }

    troca (aux, s, tamanhoArray+contador);

    return contador;
}
*/

int main()
{   char s1 [100] = "Estaa e umaa string coom duuuplicadoos";
    int x;
    
    printf ("Testes\n");
    printf ("A string \"%s\" tem %d vogais\n", s1, contaVogais (s1));
    
    x = retiraVogaisRep (s1);
    printf ("Foram retiradas %d vogais, resultando em \"%s\"\n", x, s1);
    
    x = duplicaVogais (s1);
    printf ("Foram acrescentadas %d vogais, resultando em \"%s\"\n", x, s1);
    
    printf ("\nFim dos testes\n");

    return 0;
}