/**
 * @file Ficheiro header referente às funções da Hashtable dos repositórios
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "HT_users.h"
#include "auxiliarTree.h"

typedef struct HashTableRepos *HT_Repos;

void init_HashTableRepos(HT_Repos *hash);
void print_tableRepos(HT_Repos *hash);
int insert_HashTableRepos(HT_Repos *hash, HT_Repos node);
HT_Repos find_HashTableRepos(HT_Repos *hash, char *id);
int find_HashTableReposBool(HT_Repos *hash, char *id);
void delete_tableRepos(HT_Repos *hash, char *id);
void handle_ReposFile(FILE* file, HT_Repos *Repos, HT_Users *users);
HT_Repos find_HashTableReposKey(HT_Repos *hash, int key);
char *obtain_reposLang(HT_Repos repos);
char *obtain_reposDate(HT_Repos repos);
char *obtain_reposId(HT_Repos repos);
char *obtain_reposDescription(HT_Repos repos);
HT_Repos obtain_nextRepos(HT_Repos repos);
HT_Repos listR(HT_Repos repos);
int find_reposLanguageBOOL(HT_Repos *hash, char *id, char *lang);
char *find_reposDescription(HT_Repos *repos, char *id);
char *find_reposOwnerId(HT_Repos *repos, char *id);
TREE filterRepos_Lang(char *lang, HT_Repos *repos, TREE tree);
STRING countLanguageRepos(HT_Repos *repos, char *start_date, STRING langTop, int *count);
float countRepos(HT_Repos *repos);
void free_TableRepos(HT_Repos *repos);