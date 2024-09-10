/**
  * @file Ficheiro referente ao exercicio 1 do ficheiro "repos.csv".
  */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "MAIN.h"

/**
  * @brief Função que imprime as linhas que estão corretas no ficheiro "repos-ok.csv".
  * 
  * @param file Ficheiro "repos.csv".
  *
  * @param reposList Struct que armazena os repositórios corretos.
  *
  * @param headline Headline do documento "repos.csv".
  */
void printReposFile(FILE *file, REPOS reposList, char *headline) 
{
    fprintf(file,"%s", headline);

    while (reposList->next != NULL) 
    {
        fprintf(file, "%s", reposList->line);
        // avançar para o próximo usuário
        reposList = reposList->next;
    }
}

/**
  * @brief Função que testa se o parametro recebido é do tipo Bool
  *
  * @param str Parametro (no tipo string) a ser testado
  *
  * @return Retorna 0 se for do tipo Bool e 1 se não for
  */
int testBool(char *str)
{
    int r;

    if(strcmp(str, "True") == 0 || strcmp(str, "False")==0 ) r=0;
    else r=1;

    return r;
}

/**
  * @brief Função que filtra os repositórios do ficheiro "repos.csv".
  * 
  * @param file Ficheiro "repos.csv".
  *
  * @param reposList Struct que armazena os repositórios corretos.
  * 
  * @param head Apontador para a cabeça da struct reposList.
  *
  * @param headline Headline do documento "repos.csv".
  */
void handle_ReposFile(FILE *file, REPOS reposList, REPOS head, char *headline)
{
    char c[524288];
    char *aux = NULL;
    int i=0;

    while(fgets(c, 524288, file) != NULL)
    {
        int flag = 0;
        char *str = strdup (c);
        char *line = strdup (c);
        reposList->line = line;
        aux = strsep(&str, ";\n\r");
        while (aux != NULL && flag == 0)
        {
            switch (i)
            {
            case 0:
                flag = testInt(strdup(aux));
                reposList->id = aux;
                break;
            case 1:
                flag = testInt(strdup(aux));
                reposList->owner_id = aux;
                break;
            case 2:
                flag = testString(strdup(aux));
                reposList->full_name = aux;
                break;
            case 3:
                flag = testString(strdup(aux));
                reposList->license = aux;
                break;
            case 4:
                flag = testBool(strdup(aux));
                reposList->has_wiki = aux;
                break;
            case 5:
                reposList->description = aux;
                break;
            case 6:
                flag = testString(strdup(aux));
                reposList->language = aux;
                break;
            case 7:
                            flag = testString(strdup(aux));
                reposList->default_branch = aux;
                break;
            case 8:
                flag = testDateHour(strdup(aux));
                reposList->created_at = aux;
                break;
            case 9:
                flag = testDateHour(strdup(aux));
                reposList->updated_at = aux;
                break;
            case 10:
                flag = testInt(strdup(aux));
                reposList->forks_count = aux;
                break;
            case 11:
                flag = testInt(strdup(aux));
                reposList->open_issues = aux;
                break;
            case 12:
                flag = testInt(strdup(aux));
                reposList->stargazers_count = aux;
                break;
            case 13:
                flag = testInt(strdup(aux));
                reposList->size = aux;
                break;
            default:
                break;
            }
            i++;
            if(i==14 && flag == 0) 
            {
                REPOS n = malloc(sizeof (struct repos));
                reposList->next = n;
                reposList = reposList->next;
            }

            aux = strsep(&str, ";\n\r");
        }    
        i=0;
    }
    reposList->next = NULL;
    
    fclose(file);

    FILE *final_file = fopen("./saida/repos-ok.csv", "w");
    printReposFile(final_file, head, headline);
    fclose(final_file);
}