/**
 * @file Ficheiro header referente às funções da Hashtable dos commits
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "HT_users.h"
#include "HT_repos.h"
#include "auxiliarStruct.h"
#include "auxiliarFunc.h"
#include "auxiliarTree.h"

typedef struct HashTableCommits *HT_Commits;

void init_HashTableCommits(HT_Commits *hash);
void print_tableCommits(HT_Commits *hash);
int insert_HashTableCommits(HT_Commits *hash, HT_Commits node);
HT_Commits find_HashTableCommits(HT_Commits *hash, char *id);
int find_HashTableCommitsBool(HT_Commits *hash, char *id);
void delete_tableCommits(HT_Commits *hash, char *id);
void handle_CommitsFile(FILE* file, HT_Commits *commits, HT_Users *users);
HT_Commits find_HashTableCommitsKey(HT_Commits *hash, int key);
HT_Commits obtain_nextCommit(HT_Commits commits);
char *obtain_commitsAuthorId(HT_Commits commits);
char *obtain_commitsCommiterId(HT_Commits commits);
char *obtain_commitsReposId(HT_Commits commits);
char *obtain_commitsDate(HT_Commits commits);
HT_Commits listC(HT_Commits commits);
DATA find_inactiveRepos(DATA data, HT_Commits *commits, char *str);
STRING counter_AllCommiters(STRING string, HT_Commits *commits, HT_Users *users, HT_Repos *repos, int *count);
TREE getAllColabs(HT_Commits *commits, TREE colabs);
TREE countAllBotsColabs(HT_Commits *commits, TREE bots, TREE repos);
float countCommits(HT_Commits *commits);
void compareAllDates(HT_Commits *commits, HT_Users *users, char *end_date, char *start_date);
void countCommitsReposLanguage(HT_Commits *commits, HT_Repos *repos, HT_Users *users, char *language, int flag);
void topNrepo(char *repoID, HT_Users *users, HT_Commits *commits, FILE *file, int N);
void free_TableCommits(HT_Commits *commits);