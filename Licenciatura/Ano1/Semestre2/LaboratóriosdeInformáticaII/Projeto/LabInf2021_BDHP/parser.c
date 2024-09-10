/**
 * @file parser.c Ficheiro que contém as funções referentes ao parser.
 */
#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>

/**
 * \brief Esta é a função que cria a Stack
 *
 * @returns Stack
 */
STACK *novaStack() {
    return malloc(sizeof(STACK));
}

/**
 * \brief Esta é a função que vai fazer o parser de uma linha
 *
 * Esta função recebe uma string, faz o parser e redireciona para as devidas operações.
 *
 * @param line : A linha que foi lida e da qual se vai fazer o parser.
 */
void parser(char *line, STACK *stack, STACK *stackPointer[])
{
    int flag = 0;
    int bloco = 0;
    stackPointer[0] = stack;
    STACK *addressBloco = novaStack();
    STACK *choose;

    DADOS variaveis [26];
    atribuicao(variaveis);


    for (char *token = strtok(line, " \t\n"); token != NULL; token = strtok(NULL, " \t\n"))
    {
        char *sobra;

        if (bloco == 1) choose = addressBloco;
        else choose = stackPointer[flag];

        long val_i = strtol(token, &sobra, 10);
        if (strlen(sobra) == 0)
        {
            PUSHL(choose, val_i);
        }
        else
        {
            double val_d = strtod(token, &sobra);
            if (strlen(sobra) == 0)
            {
                PUSHD(choose, val_d);
            }
            else
            {
                ((choose->comp[choose->count-1].tipo == BLOCO)&&(strstr("~%,$|w*", token)  != NULL)) ? blocoOperations(token, stackPointer, &flag, &bloco, addressBloco):
                (strstr("[]{}", token)                                                     != NULL)  ? parserArrBlo(token, stackPointer, &flag, &bloco, addressBloco):
                (strstr("+-*/()%#&|^~e&e|_;\\@$clifts<>=!?e<e>,", token)                   != NULL)  ? decideOperations(token, stackPointer, &flag, &bloco, addressBloco):
                (strchr(token,34)                                                               != NULL)  ? criarString(token, stackPointer, &flag):
                (strcmp(token, "S/")                                                               == 0)     ? stringOperations(token, stackPointer, &flag):
                (strcmp(token, "N/")                                                               == 0)     ? stringOperations(token, stackPointer, &flag):
                (variableTeste(token)                                                              == 0)     ? variableOut(stackPointer, token, variaveis, &flag, &bloco, addressBloco):
                (twoPointsTeste(token)                                                             == 0)     ? variableIn (stackPointer, token, variaveis, &flag):
                exit(0);
            }
        }
    }

    PRINT_STACK(stack);
    putchar('\n');
 }


/**
 * \brief Esta é a função auxiliar do parser que permite criar os arrays e os blocos
 *
 * @param token : sinal ou símbolo respetivo a cada operação
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag : indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 * @param bloco : indicador de que possuímos um bloco (abertura de {)
 * @param addressBloco : stack onde vai ser guardado o bloco
 */
void parserArrBlo(char *token, STACK *stackPointer[], int *flag, int *bloco, STACK *addressBloco)
{
    if (strstr("[",token) != NULL) criarArray(stackPointer, flag);
    if (strstr("]",token) != NULL) (*flag)--;
    if (strstr("{",token) != NULL) {criarBloco(stackPointer, flag, addressBloco); (*bloco) = 1;}
    if (strstr("}",token) != NULL) {(*bloco) = 0;}
}

/**
 * \brief Esta é a função auxiliar que cria um Array quando introduzido o símbolo [
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag : indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void criarArray(STACK *stackPointer[],  int *flag)
{
    STACK *array = novaStack();
    iniciarStack(array);
    PUSHA(stackPointer[*flag], array);
    (*flag)++;
    stackPointer[*flag] = array;
}

/**
 * \brief Esta é a função auxiliar que inicializa uma stack
 *
 * @param stack : stack
 */
void iniciarStack(STACK *stack)
{
    stack->count = 0;
    stack->size  = 5;
    stack->comp = malloc (stack->size * sizeof(DADOS));
}

/**
 * \brief Esta é a função auxiliar que cria um Bloco quando introduzido o símbolo {
 *
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag : indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 * @param addressBloco : stack onde é guardado o bloco
 */
void criarBloco(STACK *stackPointer[], int *flag, STACK *addressBloco)
{
    iniciarStack(addressBloco);
    PUSHB(stackPointer[*flag], addressBloco);
}

/**
 * \brief Esta é a função auxiliar do parser que redireciona para as respetivas operações dos blocos
 *
 * @param token : sinal ou símbolo respetivo a cada operação
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag : indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 * @param bloco : indicador de que possuímos um bloco (abertura de {)
 * @param addressBloco : stack onde vai ser guardado o bloco
 */
void blocoOperations (char *token, STACK *stackPointer[], int *flag, int *bloco, STACK *addressBloco)
{
    if (strstr("~",token) != NULL) executaBloco(stackPointer, flag, bloco, addressBloco);
    if (strstr("%",token) != NULL) aplicaBloco(stackPointer, flag, addressBloco);
    if (strstr("*",token) != NULL) foldBloco(stackPointer, flag);
    if (strstr(",",token) != NULL) filtraBloco(stackPointer, flag);
    if (strstr("$",token) != NULL) ordenaBloco(stackPointer, flag);
}

/**
 * \brief Esta é a função auxiliar do parser que redireciona para as respetivas operações
 *
 * @param token : sinal ou símbolo respetivo a cada operação
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag : indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 * @param bloco : indicador de que possuímos um bloco (abertura de {)
 * @param addressBloco : stack onde vai ser guardado o bloco
 */
void decideOperations(char *token, STACK *stackPointer[], int *flag, int *bloco, STACK *addressBloco)
{
    if (*bloco == 1) PUSHS(addressBloco, token);
    else
    {
        int r = parserOperations (token,stackPointer, flag);
        if (r==0) arrayOperations(token, stackPointer, flag);
    }
}

/**
 * \brief Esta é a função auxiliar ao parser que redireciona para as respetivas operações da stack
 *
 * @param token : sinal ou símbolo respetivo a cada operação
 * @param stack : local onde se encontram os operadores e onde vai ser guardado o resultado
 *
 * @return valor que permite saber se as operações foram realizadas corretamente
 */
int parserOperations(char *token, STACK *stackPointer[], int *flag)
{
    int r = 0;

    if (strstr("+-*/()%#"   ,token)  != NULL) (r = aritmeticas(token,stackPointer, flag));
    if (strstr("&|^~e&e|"   ,token)  != NULL) (r = logicas    (token,stackPointer[*flag]));
    if (strstr("_;\\@$,S/N/",token)  != NULL) (r = opStack    (token,stackPointer[*flag]));
    if (strstr("clifst"     ,token)  != NULL) (r = convertions(token,stackPointer[*flag]));
    if (strstr("<>=!?e<e>"  ,token)  != NULL) (r = comparison (token,stackPointer[*flag]));

    return r;
}

/**
 * \brief Esta é a função auxiliar ao parser que redireciona para as respetivas operações dos arrays
 *
 * @param token : sinal ou símbolo respetivo a cada operação
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag : indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void arrayOperations(char *token, STACK *stackPointer[], int *flag)
{
    if(strstr("~=,*", token) != NULL) aritArrayOperations (token, stackPointer, flag);
    if(strstr("<>()", token) != NULL) elemArrayOperations (token, stackPointer, flag);
    if(strcmp(token,"+")             == 0) concatenarArrays(stackPointer, flag);
}

/**
 * \brief Esta é a função auxiliar ao parser que cria uma string na stack
 *
 * @param token : símbolo ou letra da string
 * @param stackPointer : array de apontadores para a stack ou arrays criados
 * @param flag : indicador de que possuímos um array e da sua posição na stackPointer (abertura de [)
 */
void criarString(char *token, STACK *stackPointer[], int *flag)
{
    for (unsigned int i = 0; i < strlen(token)-1; i++)
    {
        if (token[i] == '.') token[i] = ' ';
    }

    for (unsigned int i = 0; i < strlen(token)-1; i++)
    {
        token[i] = token[i+1];
    }

    for (int i=0; i<2; i++)
    {
        token[strlen(token)-1]='\0';
    }

    int tam = strlen(token);
    char *p = malloc((tam+1) * sizeof(char));
    strcpy(p,token);
    PUSHS(stackPointer[*flag], p);

}

/**
 * \brief Esta é a função que atribui os valores por omissão às diferentes variáveis
 *
 * @param variaveis : o array que irá conter as variáveis do alfabeto maiúsculo introduzido
 */
void atribuicao (DADOS *variaveis)
{
    int i=10;
    for (char a='A'; a<='F'; a++, i++)
    {
        variaveis[a-65].tipo=1;
        variaveis[a-65].data.vl=i;
    }
    for (char a='X', i=0; a<='Z'; a++, i++)
    {
        variaveis[a-65].tipo=1;
        variaveis[a-65].data.vl=i;
    }
    variaveis['S'-65].tipo=4;
    variaveis['S'-65].data.vc=' ';
    variaveis['N'-65].tipo=4;
    variaveis['N'-65].data.vc='\n';
}

/**
 * \brief Esta é a função auxiliar da parser que imprime a stack
 *
 * @param stack: stack
 */
void PRINT_STACK(STACK *stack)
{
    int i;
    for (i = 0; i < stack->count; i++) {
        PRINT_DADOS (stack->comp[i]);
    }

    //printf("\n\nCOUNT : %d\n", stack->count);
    //printf ("SIZE : %d\n", stack->size);
}

/**
 * \brief Esta é a função auxiliar da PRINT_STACK que imprime um elemento dos diferentes tipos de dados
 *
 * @param P : É o elemento a ser imprimido
 */
void PRINT_DADOS (DADOS P)
{
    switch (P.tipo)
    {
        case LONG : printf("%ld", P.data.vl); break;
        case DOUBLE : printf("%g", P.data.vd); break;
        case CHAR : printf("%c", P.data.vc); break;
        case STRING : printf("%s", P.data.vs); break;
        case ARRAY : PRINT_STACK(P.data.va); break;
        case BLOCO : PRINT_BLOCO(P.data.vb); break;
    }
}

/**
 * \brief Esta é a função auxiliar da print_DADOS que imprime os blocos
 *
 * @param stack: stack
 */
void PRINT_BLOCO(STACK *stack)
{
    int i;

    printf("{ ");

    for (i = 0; i < stack->count; i++)
    {
        PRINT_DADOS (stack->comp[i]);
        putchar(' ');
    }
    printf("}");

    //printf("\n\nCOUNTB : %d\n", stack->count);
    //printf ("SIZEB : %d\n", stack->size);
}

/**
 * \brief Esta é a função auxiliar que retira o último elemento do tipo long da stack
 *
 * @param stack: stack
 *
 * @returns O último elemento da stack
 */
long POPL(STACK *stack)
{
    long x = stack->comp[stack->count -1].data.vl;
    stack->count--;
    return x;
}

/**
 * \brief Esta é a função auxiliar que retira o último elemento do tipo double da stack
 *
 * @param stack: stack
 *
 * @returns O último elemento da stack
 */
double POPD(STACK *stack)
{
    double x;
    if (stack->comp[stack->count-1].tipo == LONG) x = stack->comp[stack->count -1].data.vl;
    else x = stack->comp[stack->count -1].data.vd;
    stack->count--;
    return x;
}

/**
 * \brief Esta é a função auxiliar que retira o último elemento do tipo char da stack
 *
 * @param stack: stack
 *
 * @returns O último elemento da stack
 */
char POPC(STACK *stack)
{
    char x = stack->comp[stack->count -1].data.vc;
    stack->count--;
    return x;
}

/**
 * \brief Esta é a função auxiliar que retira o último elemento do tipo string da stack
 *
 * @param stack: stack
 *
 * @returns O último elemento da stack
 */
char *POPS(STACK *stack)
{
    char *x = stack->comp[stack->count-1].data.vs;
    stack->count--;
    return x;
}

/**
 * \brief Esta é a função auxiliar que retira o último elemento da stack
 *
 * @param stack: stack
 *
 * @returns O último elemento da stack
 */
DADOS POP(STACK *stack)
{
    DADOS P = stack->comp[stack->count-1];
    stack->count--;
    return P;
}

/**
 * @brief Esta é a função que verifica o elemento do topo da stack
 *
 * @param stack: stack
 *
 * @returns O elemento no topo da stack
 */
DADOS TOP(STACK *stack)
{
    DADOS P = stack->comp[stack->count-1];
    return P;
}

/**
 * \brief Esta é a função auxiliar que coloca um elemento do tipo long na stack
 *
 * @param x : É o elemento que queremos colocar na stack
 * @param stack: stack
 */
void PUSHL(STACK *stack, long x)
{
    if (stack->count == stack->size) realocarM(stack);

    stack->comp[stack->count].tipo = LONG;
    stack->comp[stack->count].data.vl = x;
    stack->count++;
}

/**
 * \brief Esta é a função auxiliar que coloca um elemento do tipo double na stack
 *
 * @param x : É o elemento que queremos colocar na stack
 * @param stack: stack
 */
void PUSHD(STACK *stack, double x)
{
    if (stack->count == stack->size) realocarM(stack);

    stack->comp[stack->count].tipo = DOUBLE;
    stack->comp[stack->count].data.vd = x;
    stack->count++;
}

/**
 * \brief Esta é a função auxiliar que coloca um elemento do tipo char na stack
 *
 * @param x : É o elemento que queremos colocar na stack
 * @param stack: stack
 */
void PUSHC(STACK *stack, char x)
{
    if (stack->count == stack->size) realocarM(stack);

    stack->comp[stack->count].tipo = CHAR;
    stack->comp[stack->count].data.vc = x;
    stack->count++;
}

/**
 * \brief Esta é a função auxiliar que coloca um elemento do tipo string na stack
 *
 * @param x : É o elemento que queremos colocar na stack
 * @param stack: stack
 */
void PUSHS(STACK *stack, char *x)
{
    if (stack->count == stack->size) realocarM(stack);

    stack->comp[stack->count].tipo = STRING;
    stack->comp[stack->count].data.vs = x;
    stack->count++;
}

/**
 * \brief Esta é a função auxiliar que coloca um elemento do tipo array na stack
 *
 * @param array : É o array que queremos colocar na stack
 * @param stack: stack
 */
void PUSHA(STACK *stack, STACK *array)
{
    if (stack->count == stack->size) realocarM(stack);

    stack->comp[stack->count].tipo = ARRAY;
    stack->comp[stack->count].data.va = array;
    stack->count++;
}

/**
 * \brief Esta é a função auxiliar que coloca um elemento do tipo bloco na stack
 *
 * @param array : É o bloco que queremos colocar na stack
 * @param stack: stack
 */
void PUSHB (STACK *stack, STACK *bloco)
{
    if (stack->count == stack->size) realocarM(stack);

    stack->comp[stack->count].tipo = BLOCO;
    stack->comp[stack->count].data.vb = bloco;
    stack->count++;
}

/**
 * \brief Esta é a função auxiliar que põe um elemento na stack
 *
 * @param P : É o elemento que queremos colocar na stack
 * @param stack: stack
 */
void PUSH(STACK *stack, DADOS P)
{
    if (stack->count == stack->size) realocarM(stack);

    stack->comp[stack->count] = P;
    stack->count++;
}


/**
 * \brief Esta é a função auxiliar que verifica os tipos dos dois últimos elementos no topo da stack
 *
 * @param stack: stack
 *
 * @returns O valor da soma dos tipos dos dois elementos
 */
int somaTiposTop(STACK *stack)
{
    TIPO x = stack->comp[stack->count - 1].tipo;
    TIPO y = stack->comp[stack->count - 2].tipo;
    return (x+y);
}

/**
 * \brief Esta é a função auxiliar que verifica se os tipos dos dois últimos elementos no tipo da stack são números
 *
 * @param stack: stack
 *
 * @returns Caso a resposta seja afirmativa retorna 1, caso contrário retorna 0
 */
int areNumbers(STACK *stack)
{
    int r = 0;

    TIPO x = stack->comp[stack->count - 1].tipo;
    TIPO y = stack->comp[stack->count - 2].tipo;

    if((x == LONG || x == DOUBLE || x == CHAR ) && (y == LONG || y == DOUBLE || y == CHAR)) r = 1;

    return r;
}

/**
 * \brief Esta é a função auxiliar que realoca memória na stack, caso necessário
 *
 * @param stack : stack
 */
void realocarM (STACK *stack)
{
    DADOS *t = realloc (stack->comp, 2*stack->size*sizeof(DADOS));

    stack->comp = t;
    stack->size*=2;
}
