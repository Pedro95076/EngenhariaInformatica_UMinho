/**
  * @file Ficheiro header referente ao catálogo de Commits.
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct commits *COMMITS;
COMMITS insertDataCommits(FILE *file);
int isEmptyCommits(COMMITS commits);
COMMITS obtain_nextCommit(COMMITS commits);
char * obtain_commitsReposId(COMMITS commits);
char * obtain_commitsAuthorId(COMMITS commits);
char * obtain_commitsDate(COMMITS commits); 
char * obtain_commiterId(COMMITS commits);
char * obtain_messageCommit(COMMITS commits);
void freeCommits(COMMITS head);