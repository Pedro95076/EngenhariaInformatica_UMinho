/**
  * @file Ficheiro referente ao exercicio 2.
  */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "MAIN.h"

/**
 * @brief Função que insere um inteiro numa árvore binária de procura.
 * 
 * @param a Árvore binária de procura que armazena inteiros (ids).
 *
 * @param x Inteiro a ser armazenado.
 *
 * @return Retorna o endereço de memória da árvore binária de procura.
 */
TREE insert (TREE a, int x) 
{
   TREE *place;
	place = &a;

	while (*place != NULL)
		if (x < (*place)->value)
				 place = &((*place)->l);
		else place = &((*place)->r);

	(*place) = malloc (sizeof (struct tree));
	(*place)->value = x;
	(*place)->l = (*place)->r = NULL;

	return a;
}

/**
 * @brief Função que procura um inteiro numa árvore binária de procura.
 * 
 * @param a Árvore binária de procura que armazena inteiros (ids).
 *
 * @param x Inteiro a ser procurado.
 *
 * @return Retorna 1 se encontrou o inteiro na árvore binária e 0 se não encontrou.
 */
int search (TREE a, int x) 
{
	while (a != NULL && a->value != x)
    {
        if (a->value > x) a = a->l;
		else a = a->r;
    }

	return (a!=NULL);
}

/**
 * @brief Função que filtra os ids dos usuários presentes no file "users-ok.csv".
 *
 * @param file Ficheiro "users-ok.csv".
 * 
 * @return Retorna uma árvore binária de procura com todos os ids dos usuários presentes no "users-ok.csv".
 */
TREE handle_id(FILE *file) 
{
    char c[524288];
    char *aux = NULL;
    TREE idStore = NULL;

    while(fgets(c, 524288, file) != NULL)
    {
        char *str = strdup (c);
        aux = strsep(&str, ";\n");
        int id = atol(aux);

        idStore = insert(idStore, id);      
    }
    
    fclose(file);

    return idStore;
}

/**
 * @brief Função que filtra no ficheiro "commits-ok.csv", os commits que refiram usuários e repositórios existentes.
 * 
 * @param file Ficheiro "commits-ok.csv" que será filtrado.
 *
 * @param idStore Árvore binária de procura com todos os ids dos usuários.
 *
 * @param reposIdStore Árvore binária de procura com todos os ids dos repositórios.
 *
 * @param headline Headline do documento "commits-ok.csv".
 */
void filterCommits(FILE *file, TREE idStore, TREE reposIdStore, char *headline)
{    
    char c[524288];
    char *aux = NULL;
    int i;
    
    FILE *final_file = fopen("./saida/commits-final.csv", "w");
    fprintf(final_file,"%s", headline);

    while(fgets(c, 524288, file) != NULL)
    {
        int flag;
        int a;
        char *str = strdup (c);
        aux = strsep(&str, ";\n");

        a = atol(aux);
        flag = search(reposIdStore, a);
        aux = strsep(&str, ";\n");

        for(i=0; i<2 && flag == 1; i++) 
        {
            a = atol(aux);
            flag = search(idStore, a);
            aux = strsep(&str, ";\n");
        } 
 
        if(flag == 1) fprintf(final_file,"%s", c);
    }
    fclose(file);
}

/**
 * @brief Função que filtra no ficheiro "repos-ok.csv", os repositórios que refiram usuários existentes e que contenham algum commit.
 * 
 * @param file Ficheiro "repos-ok.csv" que será filtrado.
 *
 * @param idStore Árvore binária de procura com todos os ids dos usuários.
 *
 * @param commitsReposId Árvore binária de procura com todos os ids dos repositórios que tenham algum commit.
 *
 * @param headline Headline do documento "repos-ok.csv".
 */
void filterRepos(FILE *file, TREE idStore, TREE commitsReposId, char *headline)
{
    FILE *final_file = fopen("./saida/repos-final.csv", "w");
    fprintf(final_file,"%s", headline);

    char c[524288];
    char *aux = NULL;

    while(fgets(c, 524288, file) != NULL)
    {
        int flagUsers = 0, flagCommits = 0, a;
        char *str = strdup(c);
        aux = strsep(&str, ";\n");
        a = atol(aux);

        flagCommits = search(commitsReposId, a);

        aux = strsep(&str, ";\n");

        if (flagCommits == 1)
        {
             a = atol(aux);
             flagUsers = search(idStore, a);
             aux = strsep(&str, ";\n");
        }
       
        if( flagUsers == 1 && flagCommits == 1) 
        {
            fprintf(final_file, "%s", c);
        }

        aux = strsep(&str, ";\n");
    }
      
    fclose(file);
    char command[100];
    strcpy(command, "cp ../guiao-1/saida/users-ok.csv ../guiao-1/saida/users-final.csv" );
    system(command);
}
