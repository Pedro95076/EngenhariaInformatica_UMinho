#include <stdio.h>
#include <stdlib.h>

typedef struct celula {
    char *palavra;
    int ocorr;
    struct celula * prox;
} * Palavras;

void libertaLista (Palavras);
int quantasP (Palavras);
void listaPal (Palavras);
char * ultima (Palavras);
Palavras acrescentaInicio (Palavras, char *);
Palavras acrescentaFim (Palavras, char *);
Palavras acrescenta (Palavras, char *);
struct celula * maisFreq (Palavras);

void libertaLista (Palavras l){
    
    Palavras aux;
    
    while (l) {
        aux = l->prox;
        free(l);
        l = aux;
    }
}

int existeP (Palavras l, char *p) {
    
    while (l) {
        
        if (strcmp(l->palavra,p) == 0) return 1;
        l = l->prox;
    }
    
    return 0;
}


int quantasP (Palavras l){
    
    int i = 0;
    
    while (l) {
        if (!existeP(l->prox, l->palavra)) i++;
        l = l->prox;
    }

    return i;
}

void listaPal (Palavras l){

    while (l) { // l != NUL
        printf("%d : %s \n", l->ocorr, l->palavra);
        l = l->prox;
    }
}

char * ultima (Palavras l){
    
    if (l==NULL) return NULL;
    
    
    while(l->prox) {
        l = l->prox;
    }
    
    return l->palavra;
}

Palavras acrescentaInicio (Palavras l, char *p){ // l = copia do dic; p = pointer de uma palavra
    
    Palavras aux; // = struct celula * aux
    aux = malloc (sizeof(struct celula));
    if (aux == NULL) return NULL;
    
    aux->palavra = p;
    aux->ocorr = 1;
    aux->prox = l;
    
    return aux; // devolve o novo endereco da cabeca da lista
}

Palavras acrescentaFim (Palavras l, char *p){
    
    Palavras aux = l;
    
    if(l == NULL) {
    l = malloc (sizeof(struct celula));
    l->palavra = p;
    l->ocorr = 1;
    l->prox = NULL;
    return l;
    }
    
    while (aux->prox) aux = aux->prox;
    //aux->prox = acrescentaInicio(NULL,p);
    Palavras r;
    r = malloc (sizeof(struct celula));
    r->palavra = p;
    r->ocorr = 1;
    r->prox = NULL;
    aux->prox = r;
    
    return l;
}

Palavras acrescenta (Palavras l, char *p){
    
    Palavras aux = l; // variavel auxiliar para fazer a pesquisa
    Palavras nova;
    Palavras ant = NULL;
    
    while (aux != NULL && strcmp(aux->palavra,p) < 0) { // tem de ser nesta ordem, se for ao contrario ele vai fazer o strcmp com uma celula nula, desta maneira se a celula for nula ele ja nao testa a proxima condicao
        ant = aux;
        aux = aux->prox;
    }
    
    if (aux && strcmp(aux->palavra,p) == 0) {
        aux->ocorr++;
    } else {
        nova = malloc(sizeof(struct celula));
        if(nova == NULL) return NULL;
        nova->palavra = p;
        nova->ocorr = 1;
        nova->prox = aux;
        if(ant) {
        ant->prox = nova;
        } else {
            l = nova;
        }
    }
    
    return l;
}
struct celula * maisFreq (Palavras l){
    //...
    return NULL;
}

int main () {
    Palavras dic = NULL;

    char * canto1 [44] = {"as", "armas", "e", "os", "baroes", "assinalados",
                          "que", "da", "ocidental", "praia", "lusitana", 
                          "por", "mares", "nunca", "de", "antes", "navegados",
                          "passaram", "ainda", "alem", "da", "taprobana",
                          "em", "perigos", "e", "guerras", "esforcados",
                          "mais", "do", "que", "prometia", "a", "forca", "humana",
                          "e", "entre", "gente", "remota", "edificaram", 
                          "novo", "reino", "que", "tanto", "sublimaram"};

    printf ("\n_____________ Testes _____________\n\n");

    int i; struct celula *p;
    
    printf("PARTE 1 : \n");
    for (i=0;i<44;i++)
        dic = acrescentaInicio (dic, canto1[i]);

    printf ("Foram inseridas %d palavras\n", quantasP (dic));
    printf ("palavras existentes:\n");
    listaPal (dic);
    printf ("última palavra inserida: %s\n", ultima (dic));

    libertaLista (dic);

    dic = NULL;

    srand(42); // semente para rand gerar os numeros pseudo aleatorios
    
    printf("\nPARTE 2 : \n");
    for (i=0; i<1000; i++)
        dic = acrescenta (dic, canto1 [rand() % 44]); // rand da um numero pseudo aleatorio
    
    printf ("Foram inseridas %d palavras\n", quantasP (dic));
    printf ("palavras existentes:\n");
    listaPal (dic);
    printf ("última palavra inserida: %s\n", ultima (dic));
    
    //p = maisFreq (dic);
    //printf ("Palavra mais frequente: %s (%d)\n", p->palavra, p->ocorr);
    
    printf ("\n_________ Fim dos testes _________\n\n");

    return 0;
}

