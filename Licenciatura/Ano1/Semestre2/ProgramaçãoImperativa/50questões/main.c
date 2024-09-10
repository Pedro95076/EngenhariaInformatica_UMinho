#include <stdio.h>
#include <assert.h>
#include <string.h>

void maior ();
void media ();
int segundoMaior ();
int bitsUm (int n);
int trailingZ (unsigned int n);
int qDig (unsigned int n);
char * concatenar (char s1[], char s2[]);
char * deslocaString (char *dest, char source[]);
int compara (char s1[], char s2[]);
char * mystrstr (char s1[], char s2[]);
void strrev (char s[]);
void strnoV (char s[]);
void truncW (char t[], int n);
char charMaisfreq (char s[]);

int main( ) {

    int escolha = 14;
    int x;
    char k [100];
    char a[100] = "liberdade, igualdade e fraternidade";
    char b[100]  = "fh";
    char source [100] = "Testa para a pergunta 8\n";
    char dest [100];
    char res;

    //printf("Escolha um exercicio (1 a 50)\n");
    //assert (scanf ("%d", &escolha) == 1);

    switch (escolha) {
        case 1  : printf("Ex.1 : Imprime no ecran o maior elemento da sequencia.\n") ; maior(); break;
        case 2  : printf("Ex.2 : Imprime no ecran a media da sequencia.\n"); media(); break;
        case 3  : printf("Ex.3 : Imprime no ecran o segundo maior elemento.\n"); segundoMaior(); break;
        case 4  : printf("Ex.4 : Calcula o numero de bits iguais a 1 usados na representaçao binaria do numero : "); scanf("%d", &x); printf("%d",bitsUm (x)); break;
        case 5  : printf("Ex.5 : Calcula o numero de bits a 0 no final da representaçao binaria do numero : "); scanf("%d", &x); printf("%d",trailingZ (x)); break;
        case 6  : printf("Ex.6 : Calcula o numero de digitos necessarios para escrever o seguinte inteiro em base decimal : "); scanf("%d", &x); printf("%d",qDig (x)); break;
        case 7  : printf("Ex.7 : Concatena a segunda string na primeira string"); concatenar(a,b), printf("\n%s", a); break; 
        case 8  : printf("Ex.8 : Copia a string source para dest e retorna o valor de dest"); deslocaString(dest,source), printf("\n%s", dest); break;
        case 9  : printf("Ex.9 : Compara duas strings lexicograficamente"); x = compara(a,b), printf("\n%d\n", x); break;
        case 10 : printf("Ex.10 : Que determina a posicao onde a string s2 ocorre em s1"); printf("\n%s\n", mystrstr(a,b)); break;
        case 11 : printf("Ex.11 : Inverte uma string"); strrev(a); printf("\n%s\n", a); break;
        case 12 : printf("Ex.12 : Retira  todas  as  vogais  de  uma  string"); strnoV(a); printf("\n%s\n", a); break;
        case 13 : printf("Ex.13 : Dado um texto com varias palavras (as palavras estao separadas em t por um ou mais espacos) e um inteiro n, trunca todas as palavras de forma a terem no maximo n caracteres"); truncW(a, 4); printf("\n%s\n", a); break;
        case 14 : printf("Ex.14 : Determina qual o caracter mais frequente numa string"); res = charMaisfreq(a); printf("\n%c\n", res); break;
        default: printf("Exercicio invalido\n");
    }

    return 0;
}

// Questao 1
void maior () {

    int num;
    int max;

    printf("Escreva numeros em sequencia (clique enter depois de cada numero\n(Escreva o 0 para fechar a sequencia)\n");

    assert (scanf ("%d", &num) == 1);
    if (num != 0) {
        max = num;
        while (num != 0) {
            if (num > max) { max = num; }
            scanf("%d", &num);
        }

        printf("O maior elemento da tua sequencia foi : %d\n", max);

    } else printf("Nao comece com o numero 0\n");
}

// Questao 2
void media () {

    int num;
    double soma = 0;
    double totalNum = 0;
    double media;

    printf("Escreva numeros em sequencia (clique enter depois de cada numero\n(Escreva o 0 para fechar a sequencia)\n");

    assert (scanf ("%d", &num) == 1);

    while (num != 0) {
        soma = soma + num;
        totalNum++;
        scanf ("%d", &num);
    }

    media = soma / totalNum;

    printf("A media da tua sequencia é : %f\n", media);
}

// Questao 3
int segundoMaior () {

    int num;
    int max1;
    int max2;
    int troca;

    printf("Escreva numeros em sequencia (clique enter depois de cada numero\n(Escreva o 0 para fechar a sequencia)\n");

    // Primeiro numero
    scanf("%d", &num);
    if (num == 0) {
        printf("Nao comeces com o numero 0\n");
        return 1;
    } else max1 = num;

    // Segundo numero
    scanf("%d", &num);

        if (num == 0) {printf("So escreves te o numero %d.\n", max1); return 0;}
        if (num > max1) {troca = max1; max2 = troca; max1 = num;}
        if (num < max1) {max2 = num;}

    // A partir do terceiro numero

    scanf("%d", &num);

    while (num != 0) {
        if (num > max1) {troca = max1; max2 = troca; max1 = num; }
        if (num < max1 && num > max2) {max2 = num;}
        scanf("%d", &num);
    }

    printf("O segundo maior elemento da tua sequencia foi : %d\n", max2);

    return 0;
}

// Questao 4
int bitsUm (int n) {

    int r=0;

    while (n>0) {
        if (n%2 == 1) r++;
        n = n/2;
    }

    return r;
}

// Questao 5
int trailingZ (unsigned int n) {

    int conta;

    for (conta = 0; n%2 == 0; conta++) {
      n = n/2;
    };

    return conta;
}

// Questao 6
int qDig (unsigned int n) {

    int conta = 0;

    while (n>0) {
        conta++;
        n = n/10;
    }

    return conta;
}

// Questao 7
char * concatenar (char s1[], char s2[]) { 

	int l1 = strlen (s1),
	    l2 = strlen (s2),
			i, j;
  
	for (j=0; j<l2; j++) s1[l1+j] = s2[j]; 
	s1[l1+j] = '\0';  

	return s1;
}

// Questao 8
char * deslocaString (char *dest, char source[]) {

    int i;

    for (i = 0; source [i] != '\0'; i++) dest [i] = source [i];

    return dest;
}

// Questao 9
int compara (char s1[], char s2[]) {

    int i;
    int flag = 0;
    int tamanhoS1 = strlen (s1);
    int tamanhoS2 = strlen (s2);
    int tamanhoMax;

    if (tamanhoS1 < tamanhoS2) tamanhoMax = tamanhoS2; else tamanhoMax = tamanhoS1;

    for (i = 0; flag == 0 && i < tamanhoMax; i++) {
        if (s1[i] < s2[i]) flag = -1;
        if (s1[i] > s2[i]) flag =  1;
    }

    return flag;
}

// Questao 10
char * mystrstr (char s1[], char s2[]) {

    int flag = 0, i = 0, j = 0;

    while (flag == 0) {
        if (s1[i] == '\0') {flag = 1; break;}
        if (s2[j] == '\0') {flag = -1; s1 += (i-j);break;}
        if (s1[i] == s2[j]) {i++; j++;}
        else {i++; j = 0;}
    }

    if (flag == 1) return "NULL";
    else return s1;
}

//Questao 11
void swap (char s[], int i, int j) {
    char k = s[i];
    s[i] = s[j];
    s[j] = k;
}

void strrev (char s[]) {

    int tamanho = 1;
    while (s[tamanho] != '\0') tamanho++;

    int i;
    for (i = 0; i<tamanho/2; i++) swap(s, i, tamanho-1-i);
}

//Questao 12
void apaga (char *s, int i)
{
    while (s[i])
    {
        s[i] = s[i+1];
        i++;
    }
}

int vogal (char c) {
    char vogais [] = "aeiouAEIOU";
    char *v = vogais;
    while (*v) if (*v++ == c) return 1;
    return 0;
}

void strnoV (char s[]) {

    for (int i = 0; s[i]; i++) {
        if (vogal(s[i])) apaga(s, i);
    }
}

void truncW (char t[], int n) {
    char aux [strlen(t)+1];
    int x = 0;
    int k = 0;
    int i = 0;

    while (i<(strlen(t)+1)) {
        if (t[i] == ' ') {aux[k++] = ' '; i++; x=0;}
        else if (x<n) {aux[k++] = t[i++]; x++;}
        else if (x==n) {i++;} 
    }

    for (i = 0; i<k; i++) t[i] = aux[i];
    t[i] = '\0';
}

char charMaisfreq (char s[]) {
    
    char letras [256];
    int i, res;
    int k = 0;

    for (i = 0; i<256; i++) letras [i] = 0;

    for (i = 0; s[i] != '\0'; i++) 
    {
        int x = s[i];
        letras[x]++;
    }

    for (i = 0; i<256; i++)
    {
        if (letras[i] > k) {k = letras[i]; res = i; i++;}
    }

    char resC = res;

    return resC;
}