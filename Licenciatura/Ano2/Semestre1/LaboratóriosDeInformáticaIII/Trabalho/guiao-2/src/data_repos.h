/**
  * @file Ficheiro header referente ao catálogo de Repositórios.
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct repos *REPOS;
REPOS insertDataRepos(FILE *file);
int isEmptyRepos(REPOS repos);
REPOS obtain_nextRepos(REPOS repos);
char * obtain_langRepos(REPOS repos);
char * obtain_reposDate(REPOS repos);
char * obtain_reposID(REPOS repos);
char * obtain_reposOwnerID(REPOS repos);
char * obtain_reposDescription(REPOS repos);
void freeRepos(REPOS head);