/**
 * @file operations.c Ficheiro que contém as funções referentes às operações na stack do parser
 */
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/**
 * \brief Esta é a função auxiliar da função parserOperations que trata os casos relacionados com operações aritméticas
 *
 * @param stackPointer: array de apontadores para a stack ou arrays criados
 * @param flag : indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 * @param token: token
 *
 * @returns Se alguma das operações for bem sucessida retorna 1, caso contrário retorna 0
 */
int aritmeticas(char *token, STACK *stackPointer[], int *flag)
{
    int r=0;

    if(strcmp(token,"+") == 0) r = soma(stackPointer[*flag]);
    if(strcmp(token,"-") == 0) r = subtracao(stackPointer[*flag]);
    if(strcmp(token,"*") == 0) r = multiplicacao(stackPointer[*flag]);
    if(strcmp(token,"/") == 0) r = divisao(stackPointer, flag);
    if(strcmp(token,")") == 0) r = incrementar(stackPointer[*flag]);
    if(strcmp(token,"(") == 0) r = decrementar(stackPointer[*flag]);
    if(strcmp(token,"%") == 0) r = restoDivInt(stackPointer[*flag]);
    if(strcmp(token,"#") == 0) r = exponenciacao(stackPointer[*flag]);

    return r;
}

/**
 * \brief Esta é a função auxiliar da função parserOperations que trata os casos relacionados com operações lógicas
 *
 * @param stack: stack
 * @param token: token
 *
 * @returns Se alguma das operações for bem sucessida retorna 1, caso contrário retorna 0
 */
int logicas(char *token, STACK *stack)
{
    int r = 0;

    if(strcmp(token,"&") == 0) r = and(stack);
    if(strcmp(token,"|") == 0) r = or(stack);
    if(strcmp(token,"^") == 0) r = xor(stack);
    if(strcmp(token,"~") == 0) r = not(stack);
    if(strcmp(token,"e&")== 0) r = conjuncao(stack);
    if(strcmp(token,"e|")== 0) r = disjuncao(stack);

    return r;
}

/**
 * \brief Esta é a função auxiliar da função parserOperations que trata os casos relacionados com operações da stack
 *
 * @param stack: stack
 * @param token: token
 *
 * @returns Se alguma das operações for bem sucessida retorna 1, caso contrário retorna 0
 */

int opStack(char *token, STACK *stack)
{
    int r = 0;

    if(strcmp(token,"_")  == 0) r = duplicar(stack);
    if(strcmp(token,";")  == 0) r = lastOut(stack);
    if(strcmp(token,"\\") == 0) r = switchTwo(stack);
    if(strcmp(token,"@")  == 0) r = rotateThree(stack);
    if(strcmp(token,"$")  == 0) r = copyN(stack);
    if(strcmp(token,",")  == 0) r = stringSize(stack);

    return r;
}

/**
 * \brief Esta é a função auxiliar da função parserOperations que trata os casos relacionados com conversões entre tipos
 *
 * @param stack: stack
 * @param token: token
 *
 * @returns Se alguma das operações for bem sucessida retorna 1, caso contrário retorna 0
 */
int convertions(char *token, STACK *stack)
{
    int r = 0;

    if(strcmp(token,"i") == 0) r = convInteiro(stack);
    if(strcmp(token,"f") == 0) r = convDouble(stack);
    if(strcmp(token,"c") == 0) r = convCaracter(stack);
    if(strcmp(token,"l") == 0) r = lerLinha(stack);
    if(strcmp(token,"t") == 0) r = lerTudo(stack);

    return r;
}

/**
 * \brief Esta é a função auxiliar da função parserOperations que trata os casos relacionados com comparações de elementos da stack
 *
 * @param stack: stack
 * @param token: token
 *
 * @returns Se alguma das operações for bem sucessida retorna 1, caso contrário retorna 0
 */
int comparison(char *token, STACK *stack)
{
    int r = 0;

    if(strcmp(token,"<") == 0) r = menor(stack);
    if(strcmp(token,">") == 0) r = maior(stack);
    if(strcmp(token,"=") == 0) r = igual(stack);
    if(strcmp(token,"!") == 0) r = nao(stack);
    if(strcmp(token,"e<")== 0) r = menorDe2(stack);
    if(strcmp(token,"e>")== 0) r = maiorDe2(stack);
    if(strcmp(token,"?") == 0) r = ifThenElse(stack);
 
    return r;
}

/**
 * \brief Esta é a função auxiliar da função separateString que trata os casos de separação de strings por espaços, novas linhas ou substrings
 *
 * @param token: sinal ou símbolo respetivo a cada operação
 * @param stackPointer : sinal ou símbolo respetivo a cada operação
 * @param flag : indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 *
 * @returns Se alguma das operações for bem sucessida retorna 1, caso contrário retorna 0
 */
void stringOperations(char *token, STACK *stackPointer[], int *flag)
{
    if(strcmp(token,"S/") == 0)  spaces(stackPointer, flag);
    if(strcmp(token,"N/") == 0)  newline(stackPointer, flag);
    if(strcmp(token,"/")  == 0) divideString(stackPointer, flag);
}


/**
 * \brief Esta é a função auxiliar que permite a soma de dois elementos da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int soma (STACK *stack)
{
    int r = areNumbers(stack);

    DADOS P, Z;

    if (r == 1){

        if ((somaTiposTop(stack)) == 2) {
            P.data.vl = POPL(stack);
            Z.data.vl = POPL(stack);
            PUSHL(stack, Z.data.vl + P.data.vl);
        } else {
            P.data.vd = POPD(stack);
            Z.data.vd = POPD(stack);
            PUSHD(stack, Z.data.vd + P.data.vd);
        }
    }
    else r = concatenarStrings(stack);

    return r;
}

/**
 * \brief Esta é a função auxiliar que permite a concatenação de strings e/ou chars e strings
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int concatenarStrings(STACK *stack)
{
    int r = 0;

    if (somaTiposTop(stack) == 16) r = concatena2Strings(stack);
    else if (somaTiposTop(stack) == 12) r = concatenaCharString(stack);

    return r;
}

/**
 * \brief Esta é a função auxiliar que permite a concatenação de duas strings
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int concatena2Strings(STACK *stack)
{
    int r=0;
    DADOS P, Z;

    P.data.vs = POPS(stack);
    Z.data.vs = POPS(stack);
    char *s = calloc(strlen(P.data.vs)+strlen(Z.data.vs)+1, sizeof(char));
    unsigned int i;

    for (i=0; i<strlen(Z.data.vs); i++)
    {
        s[i] = Z.data.vs[i];
    }

    for (i=strlen(Z.data.vs); i < strlen(P.data.vs)+strlen(Z.data.vs); i++)
    {
        s[i] = P.data.vs[i-strlen(Z.data.vs)];
    }
    s[i] = '\0';

    PUSHS(stack, s);
    r=1;

    return r;
}

/**
 * \brief Esta é a função auxiliar que permite a concatenação de um caracter e uma string
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int concatenaCharString(STACK *stack)
{
    int r=0;
    DADOS P, Z;

    P = POP(stack);
    Z = POP(stack);

    if (P.tipo == CHAR)
    {
        char *s = malloc (2*sizeof(char));
        s[0] = P.data.vc;
        s[1] = '\0';
        Z.data.vs = realloc (Z.data.vs,5*sizeof(char));
        strcat(Z.data.vs, s);
        PUSHS(stack, Z.data.vs);
        free(s);
        r=1;
    }
    else
    {
        char *s = malloc (2*sizeof(char));
        s[0] = Z.data.vc;
        s[1] = '\0';
        s = realloc (s, (strlen(P.data.vs)) * sizeof(char));
        strncat(s, P.data.vs, strlen(P.data.vs));
        PUSHS(stack, s);
        free(P.data.vs);
        r=1;
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que permite a subtração de dois elementos da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int subtracao (STACK *stack)
{
    int r = areNumbers(stack);

    DADOS P, Z;

    if(r == 1) {

    if ((somaTiposTop(stack)) == 2)
    {
        P.data.vl = POPL(stack);
        Z.data.vl = POPL(stack);
        PUSHL (stack, Z.data.vl-P.data.vl);
    }
    else
    {
        P.data.vd = POPD(stack);
        Z.data.vd = POPD(stack);
        PUSHD(stack, Z.data.vd-P.data.vd);
    }
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que permite a multiplicação de dois elementos da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int multiplicacao (STACK *stack)
{
    int r = areNumbers(stack);

    DADOS P, Z;

    if(r == 1)
    {
        if ((somaTiposTop(stack)) == 2)
        {
            P.data.vl = POPL(stack);
            Z.data.vl = POPL(stack);
            PUSHL (stack, P.data.vl*Z.data.vl);
        }
        else
        {
            P.data.vd = POPD(stack);
            Z.data.vd = POPD(stack);
            PUSHD(stack, P.data.vd*Z.data.vd);
        }
    }
    else r = replicateString(stack);

    return r;
}

/**
 * \brief Esta é a função auxiliar que permite a replicação de strings
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int replicateString(STACK *stack)
{
    int r = 0;

    DADOS P, Z;

    if (somaTiposTop(stack) == 9)
    {
        P = POP(stack);
        Z = POP(stack);
        unsigned int x = strlen(Z.data.vs);
        Z.data.vs = realloc (Z.data.vs, (strlen(Z.data.vs) + 1) * sizeof(char));

        for (unsigned int i = 0; i < (P.data.vl-1)*x; i++)
        {
            Z.data.vs[x+i] = Z.data.vs[i];
        }
        PUSHS(stack, Z.data.vs);
        r = 1;
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que permite a divisão de dois elementos da stack
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag : indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int divisao (STACK *stackPointer[], int *flag)
{
    int r = areNumbers(stackPointer[*flag]);

    DADOS P, Z;

    if(r == 1)
    {
        if ((somaTiposTop(stackPointer[*flag])) == 2)
        {
            P.data.vl = POPL(stackPointer[*flag]);
            Z.data.vl = POPL(stackPointer[*flag]);
            PUSHL (stackPointer[*flag], Z.data.vl/P.data.vl);
        }
        else
        {
            P.data.vd = POPD(stackPointer[*flag]);
            Z.data.vd = POPD(stackPointer[*flag]);
            PUSHD(stackPointer[*flag], Z.data.vd/P.data.vd);
        }
    }
    else r = divideString(stackPointer, flag);

    return r;
}

/**
 * \brief Esta é a função auxiliar que permite o incremento de um elemento da stack e a remoção do último elemento de uma string
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int incrementar (STACK *stack)
{
    int r = 0;

    DADOS P = TOP(stack);

    if(P.tipo == DOUBLE) {P = POP(stack);PUSHD(stack, (P.data.vd+1)); r = 1;}
    if(P.tipo == CHAR) {P = POP(stack); PUSHC(stack, (P.data.vc+1)); r = 1;}
    if(P.tipo == LONG) {P = POP(stack);PUSHL(stack, (P.data.vl+1)); r = 1;}
    if(P.tipo == STRING)
    {
        P = POP(stack);
        unsigned long t = strlen(P.data.vs);
        char x = P.data.vs[t-1];
        P.data.vs[t-1] = '\0';
        PUSHS(stack, P.data.vs);
        PUSHC(stack, x);
        r=1;

    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que permite o decremento de um elemento da stack e a remoção do primeiro elemento de uma string
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int decrementar (STACK *stack)
{
    int r = 0;

    DADOS P = TOP(stack);
    if(P.tipo == DOUBLE) {P = POP(stack); PUSHD(stack, (P.data.vd-1)); r = 1;}
    if(P.tipo == CHAR) {P = POP(stack); PUSHC(stack, (P.data.vc-1)); r = 1;}
    if(P.tipo == LONG) {P = POP(stack); PUSHL(stack, (P.data.vl-1)); r = 1;}
    if(P.tipo == STRING)
    {
        P = POP(stack);
        char x = P.data.vs[0];
        unsigned long t = strlen(P.data.vs);
        for (unsigned int i=0; i < strlen(P.data.vs); i++)
        {
            P.data.vs[i] = P.data.vs[i+1];
        }
        P.data.vs[t-1] = '\0';
        PUSHS(stack, P.data.vs);
        PUSHC(stack, x);
        r = 1;
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que permite obter o resto da divisão inteira de dois elementos da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int restoDivInt(STACK *stack)
{
    int r = 0;
    
    DADOS P, Z;

    if ((somaTiposTop(stack)) == 2)
    {
        r = 1;
        P.data.vl = POPL(stack);
        Z.data.vl = POPL(stack);
        PUSHL(stack, (Z.data.vl) % (P.data.vl));
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que faz a exponenciação de dois elementos da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int exponenciacao(STACK *stack)
{
    int r = areNumbers(stack);
    int x = somaTiposTop(stack);

    DADOS P, Z;

    if (r == 1)
    {
        if (x == 2)
        {
            P.data.vl = POPL(stack);
            Z.data.vl = POPL(stack);
            PUSHL(stack, pow(Z.data.vl, P.data.vl));
        }
        else
        {
            P.data.vd = POPD(stack);
            Z.data.vd = POPD(stack);
            PUSHD(stack, pow(Z.data.vd, P.data.vd));
        }
    }
    else r = searchSubstring(stack);

    return r;
}

/**
 * \brief Esta é a função auxiliar que faz a procura de uma substring numa string
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int searchSubstring(STACK *stack)
{
    int r = 0;
    int x = somaTiposTop(stack);

    DADOS P = POP(stack);
    DADOS Z = POP(stack);

    if (x == 16)
    {
        long pos;
        char *s = strstr(Z.data.vs, P.data.vs);

        if (s != NULL)
        {
            pos = s - Z.data.vs;
            PUSHL(stack, pos);
        }
        else PUSHL(stack, -1);
        r = 1;
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que realiza operações de lógica binária (e(bitwise))
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int and(STACK *stack)
{
    int r = 0;
    
    DADOS P, Z;

    if ((somaTiposTop(stack)) == 2)
    {

        r = 1;
        P.data.vl = POPL(stack);
        Z.data.vl = POPL(stack);
        PUSHL(stack, (Z.data.vl) & (P.data.vl));
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que realiza operações de lógica binária (ou(bitwise))
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int or(STACK *stack)
{
    int r = 0;
    
    DADOS P, Z;

    if ((somaTiposTop(stack)) == 2)
    {
        r = 1;
        P.data.vl = POPL(stack);
        Z.data.vl = POPL(stack);
        PUSHL(stack, (Z.data.vl) | (P.data.vl));
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que realiza operações de lógica binária (xor(bitwise))
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int xor(STACK *stack)
{
    int r = 0;
    
    DADOS P, Z;

    if ((somaTiposTop(stack)) == 2)
    {
        r = 1;
        P.data.vl = POPL(stack);
        Z.data.vl = POPL(stack);
        PUSHL(stack, (Z.data.vl) ^ (P.data.vl));
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que realiza operações de lógica binária (not(bitwise))
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int not(STACK *stack)
{
    int r = 0;
    
    DADOS P = TOP(stack);

    if (P.tipo == LONG)
    {
        r = 1;
        P.data.vl = POPL(stack);
        PUSHL(stack, ~(P.data.vl));
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que verifica a relação lógica conjuntiva entre dois elementos da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int conjuncao(STACK *stack)
{
    int r = areNumbers(stack);

    DADOS P, Z;

    if(r == 1)
    {
        P.data.vd = POPD(stack);
        Z.data.vd = POPD(stack);
        ((P.data.vd != 0) && (Z.data.vd != 0)) ? PUSHD(stack, (P.data.vd)) : PUSHD(stack, 0);
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que verifica a relação lógica disjuntiva entre dois elementos da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int disjuncao(STACK *stack)
{
    int r = areNumbers(stack);

    DADOS P, Z;

    if(r == 1)
    {
        P.data.vd = POPD(stack);
        Z.data.vd = POPD(stack);
        (Z.data.vd != 0) ? PUSHD(stack, (Z.data.vd)):
        (P.data.vd != 0 && Z.data.vd == 0) ? PUSHD(stack, P.data.vd):PUSHL(stack, 0);
    }

    return r;

}

/**
 * \brief Esta é a função auxiliar que duplica o elemento do topo da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int duplicar(STACK *stack)
{
    DADOS P = POP(stack);
    PUSH(stack, P);
    PUSH(stack, P);

    return 1;
}

/**
 * \brief Esta é a função auxiliar que faz o POP do elemento no topo da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int lastOut(STACK *stack)
{
    POP(stack);

    return 1;
}

/**
 * \brief Esta é a função auxiliar que troca os dois elementos do topo da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int switchTwo(STACK *stack)
{
    DADOS P = POP(stack);
    DADOS Z = POP(stack);
    PUSH(stack, P);
    PUSH(stack, Z);

    return 1;
}

/**
* \brief Esta é a função auxiliar que roda os três elementos do topo da stack
*
* @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
*/
int rotateThree(STACK *stack)
{
    DADOS P = POP(stack);
    DADOS Z = POP(stack);
    DADOS T = POP(stack);
    PUSH(stack, Z);
    PUSH(stack, P);
    PUSH(stack, T);

    return 1;
}

/**
 * \brief Esta é a função auxiliar que copia o n-ésimo elemento para o topo da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int copyN(STACK *stack)
{
    int r = 0;
    DADOS P = TOP(stack);

    if(P.tipo == LONG)
    {
        r = 1;
        long n = POPL(stack);
        PUSH(stack, stack->comp[stack->count - n - 1]);
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que converte o elemento do topo da stack para um inteiro
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int convInteiro(STACK *stack)
{
    int r = 0;

    DADOS P = POP(stack);

    if(P.tipo == LONG) {PUSH(stack, P); r = 1;}
    if(P.tipo == DOUBLE) {PUSHL(stack, P.data.vd); r = 1;}
    if(P.tipo == CHAR) {PUSHL(stack, P.data.vc); r = 1;}
    if(P.tipo == STRING) {PUSHL(stack, atol(P.data.vs)); r = 1;}

    return r;

}

/**
 * \brief Esta é a função auxiliar que converte o elemento do topo da stack para um double
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int convDouble(STACK *stack)
{
    int r = 0;

    DADOS P = POP(stack);

    if(P.tipo == LONG) {PUSHD(stack, P.data.vl); r = 1;}
    if(P.tipo == DOUBLE) {;PUSH(stack, P); r = 1;}
    if(P.tipo == STRING) {PUSHD(stack, atof(P.data.vs)); r = 1;}

    return r;
}

/**
 * \brief Esta é a função auxiliar que converte o elemento do topo da stack para um caracter
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int convCaracter(STACK *stack)
{
    int r = 0;

    DADOS P = POP(stack);

    if(P.tipo == LONG) {PUSHC(stack, P.data.vl); r = 1;}
    if(P.tipo == STRING) {PUSHC(stack, atof(P.data.vs)); r = 1;}

    return r;
}

/**
 * \brief Esta é a função auxiliar que lê o conteúdo da próxima linha
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int lerLinha(STACK *stack)
{
    char *s = malloc (10240 * sizeof(char));
    assert (fgets(s, 10240, stdin) != NULL);
    int x = strlen(s);
    char *p = malloc ((x+1) * sizeof(char));
    strcpy(p,s);
    PUSHS(stack, p);
    free(s);

    return 1;

}

/**
 * \brief Esta é a função auxiliar que lê o conteúdo de todas as linhas seguintes
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int lerTudo(STACK *stack)
{
    int r=0;
    char *s = malloc(10240*sizeof(char));
    char *t = malloc(10240*sizeof(char));
    while (fgets(s, 10240, stdin))
    {
        strcat(t, s);
        if (s[0] == '\n') break;
        r = 1;
    }

    PUSHS(stack, t);

    return r;
}

/**
 * \brief Esta é a função auxiliar que verifica se o penúltimo elemento da stack é menor que o último
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int menor(STACK *stack)
{
    int r = areNumbers(stack);

    DADOS P, Z;

    if (somaTiposTop(stack)==2 || somaTiposTop(stack) ==3 || somaTiposTop(stack)==4)
    {
        P.data.vd = POPD(stack);
        Z.data.vd = POPD(stack);
        ((Z.data.vd) < (P.data.vd)) ? PUSHL(stack, 1) : PUSHL(stack, 0);
        r=1;
    }
    else if (somaTiposTop(stack) == 16)
    {
        P = POP(stack);
        Z = POP(stack);
        if(strcmp(Z.data.vs, P.data.vs) < 0) PUSHL(stack, 1);
        else PUSHL(stack, 0);
        r=1;
    }
    else if (somaTiposTop(stack)==5) r = menorChar(stack);
    else r = firstChars(stack);

    return r;
}

/**
 * \brief Esta é a função auxiliar que trata dos casos em que comparamos números com caracteres
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int menorChar(STACK *stack)
{
    int r=0;
    DADOS P, Z;

    if (stack->comp[stack->count - 1].tipo == CHAR)
    {
        P.data.vc = POPD(stack);
        Z.data.vd = POPD(stack);
        (Z.data.vd < P.data.vc) ? PUSHL(stack, 1):PUSHL(stack, 0);
        r=1;
    }
    if (stack->comp[stack->count - 2].tipo == CHAR)
    {
        P.data.vd = POPD(stack);
        Z.data.vc = POPD(stack);
        (Z.data.vc < P.data.vd) ? PUSHL(stack, 1):PUSHL(stack, 0);
        r=1;
    }

    return r;
}


/**
 * \brief Esta é a função auxiliar que vai buscar x caracteres ao início da string
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int firstChars(STACK *stack)
{
    int r = 0;
    DADOS P, Z;

    if (somaTiposTop(stack) == 9)
    {
        P = POP(stack);
        Z = POP(stack);
        char *s = calloc(P.data.vl+1, sizeof(char));
        unsigned int i;

        for (i = 0; i < P.data.vl; i++)
        {
            s[i] = Z.data.vs[i];
        }
        s[i] = '\0';
        PUSHS(stack, s);
        r=1;
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que verifica se o penúltimo elemento da stack é maior que o último
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int maior(STACK *stack)
{
    int r = areNumbers(stack);

    DADOS P, Z;

    if (somaTiposTop(stack)==2 || somaTiposTop(stack) ==3 || somaTiposTop(stack)==4)
    {
        P.data.vd = POPD(stack);
        Z.data.vd = POPD(stack);
        ((Z.data.vd) > (P.data.vd)) ? PUSHL(stack, 1) : PUSHL(stack, 0);
        r=1;
    }
    else if (somaTiposTop(stack) == 16)
    {
        P = POP(stack);
        Z = POP(stack);
        if(strcmp(Z.data.vs, P.data.vs) > 0) PUSHL(stack, 1);
        else PUSHL(stack, 0);
        r=1;
    }
    else if (somaTiposTop(stack)==5) r = maiorChar(stack);
    else r = lastChars(stack);

    return r;
}

/**
 * \brief Esta é a função auxiliar que trata das comparações de números com caracteres
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int maiorChar(STACK *stack)
{
    int r=0;
    DADOS P, Z;

    if (stack->comp[stack->count - 1].tipo == CHAR)
    {
        P.data.vc = POPD(stack);
        Z.data.vd = POPD(stack);
        (Z.data.vd > P.data.vc) ? PUSHL(stack, 1):PUSHL(stack, 0);
        r=1;
    }
    if (stack->comp[stack->count - 2].tipo == CHAR)
    {
        P.data.vd = POPD(stack);
        Z.data.vc = POPD(stack);
        (Z.data.vc > P.data.vd) ? PUSHL(stack, 1):PUSHL(stack, 0);
        r=1;
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que vai buscar x caracteres ao fim da string
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int lastChars(STACK *stack)
{
    int r = 0;
    DADOS P, Z;

    if (somaTiposTop(stack) == 9)
    {
        P = POP(stack);
        Z = POP(stack);
        char *s = calloc(P.data.vl +1 ,sizeof(char));
        int x = 0;
        unsigned int i = 0;

        for (i = strlen(Z.data.vs)-P.data.vl; i < strlen(Z.data.vs); i++)
        {
            s[x] = Z.data.vs[i];
            x++;
        }
        s[i] = '\0';
        PUSHS(stack, s);
        r=1;
    }

    return r;
}

/**
 * \brief Esta é a função auxiliar que compara os elementos no topo da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int igual(STACK *stack)
{
    int r = areNumbers(stack);

    DADOS P, Z;

    if (r == 1)
    {
        P.data.vd = POPD(stack);
        Z.data.vd = POPD(stack);
        ((Z.data.vd) == (P.data.vd)) ? PUSHL(stack, 1) : PUSHL(stack, 0);
        r = 1;
    }
    else if (somaTiposTop(stack) == 16)
    {
        P = POP(stack);
        Z = POP(stack);
        int result = strcmp(P.data.vs, Z.data.vs);
        (result == 0) ? PUSHL(stack, 1) : PUSHL(stack, 0);
        r = 1;
    }
    else r = indexStrings(stack);

    return r;
}

/**
 * \brief Esta é a função auxiliar que compara os elementos no topo da stack que sejam strings
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int indexStrings (STACK *stack)
{
    int r;

    if (somaTiposTop(stack) == 9)
    {
        DADOS P = POP(stack);
        DADOS Z = POP(stack);
        PUSHC(stack, Z.data.vs[P.data.vl]);
        r = 1;
    }
    else  r = 0;

    return r;
}

/**
 * \brief Esta é a função auxiliar que coloca na stack o contrário do seu valor lógico
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int nao(STACK *stack)
{
    DADOS P = POP(stack);
    (P.tipo == LONG && P.data.vl!=0) ? PUSHL(stack, 0):
    (P.tipo == DOUBLE && P.data.vd!=0) ? PUSHL(stack, 0):
    (P.tipo == CHAR && P.data.vc!=0) ? PUSHL(stack, 0): PUSHL(stack, 1);

    return 1;
}

/**
 * \brief Esta é a função auxiliar que coloca na stack o menor de 2 valores
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int menorDe2(STACK *stack)
{
    int r = 0;

    DADOS P = POP(stack);
    DADOS Z = POP(stack);

    (P.tipo == LONG && Z.tipo == LONG) ?
    (((P.data.vl)<(Z.data.vl)) ? PUSH(stack, P): PUSH(stack, Z)):
    (P.tipo == STRING && Z.tipo == STRING) ?
    ((strcmp(Z.data.vs, P.data.vs) < 0) ? PUSH(stack, Z): PUSH(stack, P)) :
    (P.tipo == LONG && Z.tipo == DOUBLE) ?
    (((P.data.vl)<(Z.data.vd)) ? PUSH(stack, P): PUSH(stack, Z)) :
    (P.tipo == DOUBLE && Z.tipo == LONG) ?
    (((P.data.vd)<(Z.data.vl)) ? PUSH(stack, P) : PUSH(stack, Z)):
    (P.tipo == DOUBLE && Z.tipo == DOUBLE) ?
    (((P.data.vd)<(Z.data.vd)) ? PUSH(stack, P):PUSH(stack, Z)) :
    exit(0);
    r = 1;

    return r;
}

/**
 * \brief Esta é a função auxiliar que coloca na stack o maior de 2 valores
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int maiorDe2(STACK *stack)
{
    int r = 0;

    DADOS P = POP(stack);
    DADOS Z = POP(stack);

    (P.tipo == LONG && Z.tipo == LONG) ?
    (((P.data.vl)>(Z.data.vl)) ? PUSH(stack, P): PUSH(stack, Z)):
    (P.tipo == STRING && Z.tipo == STRING) ?
    ((strcmp(Z.data.vs, P.data.vs) > 0) ? PUSH(stack, Z): PUSH(stack, P)) :
    (P.tipo == LONG && Z.tipo == DOUBLE) ?
    (((P.data.vl)>(Z.data.vd)) ? PUSH(stack, P): PUSH(stack, Z)) :
    (P.tipo == DOUBLE && Z.tipo == LONG) ?
    (((P.data.vd)>(Z.data.vl)) ? PUSH(stack, P) : PUSH(stack, Z)):
    (P.tipo == DOUBLE && Z.tipo == DOUBLE) ?
    (((P.data.vd)>(Z.data.vd)) ? PUSH(stack, P):PUSH(stack, Z)) :
    exit(0);
    r = 1;

    return r;
}
/**
 * \brief Esta é a função auxiliar que verifica a condição if-then-else de 3 elementos da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int ifThenElse(STACK *stack)
{
    DADOS P = POP(stack);
    DADOS Z = POP(stack);
    DADOS T = POP(stack);
    STACK *array = T.data.va;

    (T.tipo == LONG && T.data.vl == 0) ? PUSH(stack, P) :
    (T.tipo == DOUBLE && T.data.vd == 0) ? PUSH(stack, P):
    (T.tipo == CHAR && T.data.vc == '\0') ? PUSH(stack, P):
    (T.tipo == STRING && strlen(T.data.vs) == 0) ? PUSH(stack, P) :
    (T.tipo == ARRAY) ? ((array->count == 0) ? PUSH(stack, P) : PUSH(stack, Z)):
    PUSH(stack, Z);

    return 1;
}

/**
 * \brief Esta é a função auxiliar que verifica o tamanho de uma string no topo da stack
 *
 * @param stack : stack
 *
 * @return Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int stringSize(STACK *stack)
{
    int r = 0;

    DADOS P = TOP(stack);
    if (P.tipo == STRING)
    {
        DADOS P = POP(stack);
        PUSHL(stack, strlen(P.data.vs));
        r = 1;
    }

    return r;
}


/**
 * \brief Esta é a função auxiliar que testa se a variável é um caracter do alfabeto maiúsculo
 *
 * @param t : string com o token
 *
 * @returns Verdadeiro ou Falso
 */
int variableTeste (char *token)
{
    char k;
    k = token[0];
    int res;

    if (k <= 90 && k >= 65) res = 0;
    else res = 1;

    return res;
}

/**
 * \brief Esta é a função auxiliar que testa se o primeiro caracter da string é :
 *
 * @param t : string com o token
 *
 * @returns Verdadeiro ou Falso
 */
int twoPointsTeste (char *token)
{
    char k;
    k = token[0];
    int res;

    if (k == ':') res = 0;
    else res = 1;

    return res;
}

/**
 * \brief Esta é a função auxiliar que coloca na stack a variável pretendida
 *
 * @param t : string com o token
 * @param variaveis : variáveis passíveis de serem colocadas (alfabeto maiúsculo)
 * @param stack : stack
 */
void variableOut (STACK *stackPointer[], char *token, DADOS variaveis[26], int *flag, int *bloco, STACK *addressBloco)
{
    char k;
    k = token[0];
    DADOS P;
    int i = k - 65;
    P = variaveis[i];
    ((*bloco) == 1) ? PUSH(addressBloco, P) : PUSH(stackPointer[*flag], P);
}

/**
 * \brief Esta é a função auxiliar que verifica o elemento do topo da stack e o guarda na variável pretendida
 *
 * @param token : string com o token
 * @param variaveis : variáveis passíveis de serem colocadas (alfabeto maiúsculo)
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag : indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 *
 */
void variableIn (STACK *stackPointer[], char *token, DADOS variaveis[26], int *flag)
{
    char k;
    k = token[1];
    DADOS P = TOP(stackPointer[*flag]);

    variaveis[k-65] = P;
}

/**
 * \brief Esta é a função auxiliar que coloca os espaços numa string e a converte num array com vários elementos
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag :  indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void spaces(STACK *stackPointer[], int *flag)
{
    char *delim = " \n";
    DADOS P = POP(stackPointer[*flag]);
    char *s = P.data.vs;
    criarArray(stackPointer, flag);


    for (char *t = strtok_r(s, delim, &s); t != NULL; t = strtok_r(s, delim, &s))
    {
        char *y = malloc((strlen(t)+1)*sizeof(char));
        strcpy (y, t);
        PUSHS(stackPointer[*flag], y);
    }

    (*flag)--;
}

/**
 * \brief Esta é a função auxiliar que coloca novas linhas numa string e a converte num array com vários elementos
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag :  indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void newline(STACK *stackPointer[], int *flag)
{
    char *delim = "\n";
    DADOS P = POP(stackPointer[*flag]);
    char *s = P.data.vs;
    criarArray(stackPointer, flag);


    for (char *t = strtok_r(s, delim, &s); t != NULL; t = strtok_r(s, delim, &s))
    {
        char *y = malloc((strlen(t)+1)*sizeof(char));
        strcpy (y, t);
        PUSHS(stackPointer[*flag], y);
    }

    (*flag)--;
}

/**
 * \brief Esta é a função auxiliar que divide uma string por uma substring colocando os restantes elementos num array
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag :  indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 *
 * @returns Se a operação for bem sucessida retorna 1, caso contrário retorna 0
 */
int divideString(STACK *stackPointer[], int *flag)
{
    int r = 0;

    DADOS P = POP(stackPointer[*flag]);
    char *delim = P.data.vs;
    DADOS Z = POP(stackPointer[*flag]);
    char *s = Z.data.vs;

    criarArray(stackPointer, flag);

    for (char *t = strtok_r(s, delim, &s); t != NULL; t = strtok_r(s, delim, &s))
    {
        char *y = malloc((strlen(t)-strlen(P.data.vs)-1)*sizeof(char));
        strcpy (y, t);
        PUSHS(stackPointer[*flag], y);
        r = 1;
    }

    (*flag)--;

    return r;

}

/**
 * \brief Esta é a função auxiliar da arrayOperations que redireciona para as operações nos Arrays
 *
 * @param token : Símbolo da operação
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag : indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
*/
void aritArrayOperations (char *token, STACK *stackPointer[], int *flag)
{
    if (strcmp(token,"~") == 0) arrayToStack    (stackPointer[*flag], stackPointer[*flag+1]);
    if (strcmp(token,"=") == 0) indexArray      (stackPointer[*flag], stackPointer[*flag+1]);
    if (strcmp(token,",") == 0) range           (stackPointer, flag);
    if (strcmp(token,"*") == 0) replicate       (stackPointer, flag);
}

/**
 * \brief Esta é a função auxiliar da arrayOperations que redireciona para operações com os elementos do Array
 *
 * @param token : Símbolo da operação
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag : indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
*/
void elemArrayOperations (char *token, STACK *stackPointer[], int *flag)
{
    if (strcmp(token,"(") == 0) removeFirst     (stackPointer, flag);
    if (strcmp(token,")") == 0) removeLast      (stackPointer, flag);
    if (strcmp(token,"<") == 0) firstElements   (stackPointer, flag);
    if (strcmp(token,">") == 0) lastElements    (stackPointer, flag);
}


/**
 * \brief Esta é a função auxiliar da aritArrayOperations que coloca na stack todos os elementos do array
 *
 * @param stack : stack
 * @param array : local onde está o array
 */
void arrayToStack(STACK *stack, STACK *array)
{
    int i;
    int x = array->count;

    DADOS P[x];

    x = sizeof(P)/sizeof(P[0]);

    for (i = 0; i < x; i++)
    {
        P[i] = POP(array);
    }

    stack->count--;

    for (i = 0; i < x; i++)
    {
        PUSH(stack, P[x-i-1]);
    }
}

/**
 * \brief Esta é a função auxiliar da aritArrayOperations que dá o tamanho do array
 *
 * @param stack : stack
 * @param array : local onde está o array
 */
void size(STACK *stack, STACK *array)
{
    POP(stack);
    PUSHL(stack, array->count);
}

/**
 * \brief Esta é a função auxiliar da aritArrayOperations que vai buscar o valor por índice
 *
 * @param stack : stack
 * @param array : local onde está o array
 */
void indexArray(STACK *stack, STACK *array)
{
    DADOS Z = POP(stack);
    POP(stack);

    for (int i = array->count-1; i >= 0; i--)
    {
        if (i == Z.data.vl) PUSH(stack, array->comp[i]);
    }
}

/**
 * \brief Esta é a função auxiliar da aritArrayOperations que cria um array com x número de elementos
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag: indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void range (STACK *stackPointer[], int *flag)
{
    DADOS P = POP(stackPointer[*flag]);

    if (P.tipo == LONG)
    {
        criarArray(stackPointer, flag);

        for (long i=0; i < P.data.vl; i++)
        {
            PUSHL(stackPointer[*flag], i);
        }
        (*flag)--;
    }
    else
    {
        PUSHL(stackPointer[*flag], stackPointer[*flag+1]->count);
    }
}

/**
 * \brief Esta é a função auxiliar da aritArrayOperations que repete um array
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag: indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void replicate (STACK *stackPointer[], int *flag)
{
    DADOS P = POP(stackPointer[*flag]);
    STACK *array = stackPointer[*flag+1];
    int x = array->count;
    int i;

    for (i=0; i < (P.data.vl-1)*x; i++)
    {
        PUSH(array, array->comp[i]);
    }
}

/**
 * \brief Esta é a função auxiliar da elemArrayOperations que remove o primeiro elemento e o coloca na stack
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag: indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void removeFirst (STACK *stackPointer[], int *flag)
{
    DADOS P = POP(stackPointer[*flag]);
    STACK *aux = P.data.va;
    DADOS Z = aux->comp[0];

    int x = aux->count;

    for (int i=0; i < x; i++)
    {
        aux->comp[i] = aux->comp[i+1];
    }

    aux->count--;
    PUSHA(stackPointer[*flag], aux);
    PUSH(stackPointer[*flag], Z);
}

/**
 * \brief Esta é a função auxiliar da elemArrayOperations que remove o último elemento e o coloca na stack
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag: indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void removeLast (STACK *stackPointer[], int *flag)
{
    DADOS P = POP(stackPointer[*flag]);
    STACK *aux = P.data.va;
    DADOS Z = POP(P.data.va);


    PUSHA(stackPointer[*flag], aux);
    PUSH(stackPointer[*flag], Z);
}

/**
 * \brief Esta é a função auxiliar da elemArrayOperations que vai buscar x valores do ínicio de um array
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag: indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void firstElements(STACK *stackPointer[], int *flag)
{
    DADOS P = POP(stackPointer[*flag]);
    STACK *array = stackPointer[*flag+1];

    unsigned int i;

    for (i = array->count; i > P.data.vl ; i--)
    {
        POP(array);
    }
}

/**
 * \brief Esta é a função auxiliar da elemArrayOperations que vai buscar x valores do fim de um array
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag: indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void lastElements(STACK *stackPointer[], int *flag)
{
    DADOS P = POP(stackPointer[*flag]);
    STACK *array = stackPointer[*flag+1];
    int x = array->count;
    int i;

    for (i=0; i < P.data.vl; i++)
    {
        array->comp[i] = array->comp[x-P.data.vl+i];
    }

    for (i=0; i < x-P.data.vl; i++)
    {
        POP(array);
    }
}

/**
 * \brief Esta é a função auxiliar da aritArrayOperations que concatena arrays e/ou outros elementos
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag: indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void concatenarArrays(STACK *stackPointer[], int *flag)
{
    DADOS P = TOP(stackPointer[*flag]);

    if (P.tipo == ARRAY) concatenaResto(stackPointer, flag);
    else concatenaArrNum(stackPointer, flag);

}

/**
 * \brief Esta é a função auxiliar da concatenarArrays que concatena um array e um número, por esta ordem
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag: indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void concatenaArrNum(STACK *stackPointer[], int *flag)
{
    DADOS P = POP(stackPointer[*flag]);

    PUSH(stackPointer[*flag+1], P);
}

/**
 * \brief Esta é a função auxiliar da concatenarArrays que concatena dois arrays ou um número e um array
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag: indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void concatenaResto(STACK *stackPointer[], int *flag)
{
    int x = somaTiposTop(stackPointer[*flag]);
    DADOS P = POP(stackPointer[*flag]);
    DADOS Z = POP(stackPointer[*flag]);
    STACK *arrayP = P.data.va;

    if (x == 17 || x == 18) concatenaNumArr(arrayP, stackPointer, flag, Z);
    else concatenaArrArr(arrayP, stackPointer, flag, Z);
}

/**
 * \brief Esta é a função auxiliar da concatenarArrays que concatena um número e um array, por esta ordem
 *
 * @param stackPointerarr : array de apontadores para a stack ou arrays criados
 * @param flag: indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 * @param array : array retirado da stack
 * @param P : local onde está guardado o array
 */
void concatenaNumArr (STACK *array, STACK *stackPointer[], int *flag, DADOS P)
{
    criarArray(stackPointer, flag);
    (*flag)--;

    PUSH(stackPointer[*flag+1], P);

    for (int i=0; i<array->count; i++)
    {
        PUSH(stackPointer[*flag+1], array->comp[i]);
    }
}

/**
 * \brief Esta é a função auxiliar da concatenarArrays que concatena dois arrays
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag: indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 * @param array : array retirado da stack
 * @param P : local onde está guardado um dos arraya
 */
void concatenaArrArr (STACK *array, STACK *stackPointer[], int *flag, DADOS P)
{
    criarArray(stackPointer, flag);
    (*flag)--;

    STACK *arrayP = P.data.va;

    for (int i=0; i < arrayP->count; i++)
    {
        PUSH(stackPointer[*flag+1], arrayP->comp[i]);
    }
    for (int i=0; i<array->count; i++)
    {
        PUSH(stackPointer[*flag+1], array->comp[i]);
    }
}

/**
 * \brief Esta é a função auxiliar da parserBloco que executa um bloco
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag : indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 * @param bloco : indicador de que possuímos um bloco (abertura de {)
 * @param addressBloco : stack onde vai ser guardado o bloco
 */
void executaBloco(STACK *stackPointer[], int *flag, int *bloco, STACK *addressBloco)
{
    int x = addressBloco->count;
    DADOS block = POP(stackPointer[*flag]);
    STACK *bl = block.data.vb;

    for (int i = 0; i < x; i++)
    {

        if (bl->comp[i].tipo == LONG) PUSH(stackPointer[*flag], bl->comp[i]);
        else {
            DADOS P = bl->comp[i];
            decideOperations(P.data.vs, stackPointer, flag, bloco, addressBloco);
        }
    }
}

/**
 * \brief Esta é a função auxiliar da parserBloco que aplica o bloco a todos os elementos de um array
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag : indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 * @param addressBloco : stack onde vai ser guardado o bloco
 */
void aplicaBloco(STACK *stackPointer[], int *flag, STACK *addressBloco)
{
    int x = addressBloco->count;
    int k, a = -1;

    DADOS block = POP(stackPointer[*flag]);
    STACK *bl = block.data.vb;
    DADOS n;
    for (int i = 0; i < x; i++) {
        if (bl->comp[i].tipo == LONG) {
            n = bl->comp[i];
            a = 0;
        } else {
            DADOS array = POP(stackPointer[*flag]);
            STACK *arr = array.data.va;
            k = arr->count;
            criarArray(stackPointer, flag);
            for (int j = 0; j < k; j++) {
                PUSH(stackPointer[*flag], arr->comp[j]);
                if (a == 0) PUSH(stackPointer[*flag], n);
                if ((bl->comp[i].data.vc) == ' ') PUSHC(stackPointer[*flag],' ');
                else if ((bl->comp[i].data.vc) == '\n') PUSHC(stackPointer[*flag],'\n');
                else parserOperations(bl->comp[i].data.vs, stackPointer, flag);
            }
            (*flag)--;
            a = -1;
        }
    }

}

/**
 * \brief Esta é a função auxiliar da parserBloco que faz o fold sobre um array ou string usando o bloco
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag : indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void foldBloco(STACK *stackPointer[], int *flag)
{
    DADOS block = POP(stackPointer[*flag]);
    STACK *bl = block.data.vb;

    DADOS array = POP(stackPointer[*flag]);
    STACK *arr = array.data.va;
    int k = arr->count;

    char *operador = bl->comp[0].data.vs;

    for (int i = 0; i < k; i++)
    {
        if (i == 0)
        {
            PUSH(stackPointer[*flag], arr->comp[i]);
            PUSH(stackPointer[*flag], arr->comp[++i]);
            parserOperations(operador, stackPointer, flag);
        } else
        {
            PUSH(stackPointer[*flag], arr->comp[i]);
            parserOperations(operador, stackPointer, flag);
        }
    }
}

/**
 * \brief Esta é a função auxiliar da parserBloco que filtra o bloco
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag : indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void filtraBloco(STACK *stackPointer[], int *flag)
{
    DADOS block = POP(stackPointer[*flag]);
    STACK *bl = block.data.vb;
    DADOS array = POP(stackPointer[*flag]);
    STACK *a = array.data.va;
    int x = a->count;
    int k = 1;

    if ((bl->count > 2) && (strstr("!",bl->comp[2].data.vs) != NULL)) k = 0;

    criarArray(stackPointer, flag);
    (*flag)--;

    for (int i = 0; i < x; i++)
    {
        if ((a->comp[i].data.vl % bl->comp[0].data.vl) == k) PUSH(stackPointer[*flag+1], a->comp[i]);
    }

    free(bl);
    free(a);
}

/**
 * \brief Esta é a função auxiliar da parserBloco ordena usando o bloco
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag : indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void ordenaBloco(STACK *stackPointer[], int *flag)
{
    STACK *array = stackPointer[(*flag)+1];
    DADOS strings [100];
    long tamanho [100];
    int x = array->count;

    for (int i = 0; i < x; i++)
    {
        strings [i] = TOP(array);
        stringSize(array);
        tamanho[i] = POPL(array);
    }
    POP(stackPointer[(*flag)]);

    selSort(tamanho, x, strings);

    for(int j = 0; j < x; j++)
    {
        PUSH(array, strings[j]);
    }
}

/**
 * \brief Esta é a função auxiliar de ordenação da ordenaBloco
 *
 * @param v : array a ser ordenado
 * @param n : tamanho dos arrays
 * @param s : array a ser ordenado
 */
void selSort (long v[], int n, DADOS s[]) 
{

	int i, j;

	for (j=0; j<n-1; j++)
		for (i=j+1; i<n; i++)
			if (v[i] < v[j]) 
            {
                swapL(v, i, j);
                swapD(s, i, j);
            }
}

/**
 * \brief Esta é a função auxiliar da selSort que troca dois elementos entre si
 *
 * @param v : array a ser ordenado
 * @param i : indice do elemento a ser trocado
 * @param j : indice do elemento a ser trocado
 */
void swapL (long v[], int i, int j) 
{
	long t = v[i];
	v[i] = v[j];
	v[j] = t;
}

/**
 * \brief Esta é a função auxiliar da selSort que troca dois elementos entre si
 *
 * @param v : array a ser ordenado
 * @param i : indice do elemento a ser trocado
 * @param j : indice do elemento a ser trocado
 */
void swapD (DADOS v[], int i, int j) 
{
	DADOS t = v[i];
	v[i] = v[j];
	v[j] = t;
}
