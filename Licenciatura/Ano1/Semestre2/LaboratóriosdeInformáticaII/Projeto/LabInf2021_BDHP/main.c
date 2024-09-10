/**
 *  @file main.c Ficheiro que contém a função principal do programa
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "parser.h"

/**
 * \brief Esta é a função principal do programa
 * 
 * Esta função recebe uma sequência de caracteres e forma uma string "line"
 * 
 * @returns O valor 0
 */
int main()
{
    char line[10240];
    assert (fgets(line, 10240, stdin) != NULL);
    assert (line[strlen(line) -1] == '\n');

    STACK *stack = novaStack();
    iniciarStack(stack);

    STACK *stackPointer[100];

    int flagMain = 0;

    for (unsigned int i=0; i < strlen(line)-1; i++)
    {
        if (flagMain == 1)
        {
            if (line[i] == ' ') line[i] = '.';
            if (line[i] == '"') flagMain = 0 ;
        }
        else
        {
            if (line[i] == '"') flagMain = 1 ;
        }
    }

    parser(line, stack, stackPointer);
    return 0;
}
