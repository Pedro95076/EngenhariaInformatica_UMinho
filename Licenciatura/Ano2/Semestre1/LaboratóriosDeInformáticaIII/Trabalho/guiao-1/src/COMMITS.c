/**
  * @file Ficheiro referente ao exercicio 1 do ficheiro "commits.csv".
  */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "MAIN.h"

/**
  * @brief Função que imprime as linhas que estão corretas no ficheiro "commits-ok.csv".
  * 
  * @param file Ficheiro "commits.csv".
  *
  * @param commitsList Struct que armazena os repositórios corretos.
  *
  * @param headline Headline do documento "commits.csv".
  */
void printCommitsFile (FILE *file, COMMITS commitsList, char *headline) 
{
    fprintf(file,"%s", headline);

    while (commitsList->next != NULL) 
    {
        fprintf(file, "%s", commitsList->line);
        commitsList = commitsList->next;
        }
}

/**
  * @brief Função que filtra os commits do ficheiro "commits.csv".
  * 
  * @param file Ficheiro "commits.csv".
  *
  * @param commitsList Struct que armazena os commits corretos.
  * 
  * @param head Apontador para a cabeça da struct commitsList.
  *
  * @param headline Headline do documento "commits.csv".
  */
void handle_CommitsFile(FILE *file, COMMITS commitsList, COMMITS head, char *headline)
{
    char c[1000000];
    char *aux = NULL;
    int i=0;

    while(fgets(c, 1000000, file) != NULL)
    {
        int flag = 0;
        char *str = strdup (c);
        char *line = strdup(c);
        commitsList->line = line;
        aux = strsep(&str, ";\n\r");
        while (aux != NULL && flag == 0)
        {
            switch (i)
            {
            case 0:
                flag = testInt(strdup(aux));
                commitsList->repo_id = aux;
                break;
            case 1:
                flag = testInt(strdup(aux));
                commitsList->author_id = aux;
                break;
            case 2:
                flag = testInt(strdup(aux));
                commitsList->commiter_id = aux;
                break;
            case 3:
                flag = testDateHour(strdup(aux));
                commitsList->commit_at = aux;
                break;
            case 4:
                commitsList->message = aux;
                break;
            default:
                break;
            }
            i++;
            if(i==5 && flag==0) 
            {
                COMMITS n = malloc(sizeof (struct commits));
                commitsList->next = n;
                commitsList = commitsList->next;
            }
            aux = strsep(&str, ";\n\r");
        }    
        i=0;
    }
    commitsList->next = NULL;
    
    fclose(file);

    FILE *final_file = fopen("./saida/commits-ok.csv", "w");
    printCommitsFile(final_file, head, headline);
    fclose(final_file);
}