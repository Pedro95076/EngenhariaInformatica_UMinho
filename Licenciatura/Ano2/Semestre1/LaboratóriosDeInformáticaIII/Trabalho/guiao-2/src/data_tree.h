/**
  * @file Ficheiro header referente às estruturas de árvores.
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "data_users.h"
#include "data_commits.h"
#include "data_repos.h"

typedef struct tree *TREE;
typedef struct treeUsers *TREEUSERS;
typedef struct treeUsers9 *TREEUSERS9;
typedef struct treeRepos *TREEREPOS;
TREE insert (TREE tree, int x);
TREE filterRepos_Lang(char *lang, REPOS repos, TREE tree);
TREEUSERS addUsersTREE(TREEUSERS place, char *id, char *login);
TREEUSERS iniUsersTREE(USERS users);
TREEUSERS9 addUsersTREE9(TREEUSERS9 tree, char *id, USERS user);
TREEUSERS9 iniUsersTREE9(USERS users);
TREEREPOS addReposTREE(TREEREPOS tree, char *id, char *message);
TREEREPOS iniReposTREE(REPOS repos);
TREEREPOS iniReposTREE9(REPOS repos);
int search (TREE tree, int x);
void printTree(TREE tree);
void freeTree(TREE node);
void freeTreeUsers(TREEUSERS node);
void freeTreeRepos(TREEREPOS node);
int countnodes(TREE tree);
char * searchUsers (TREEUSERS tree, char * x);
USERS searchUsers9 (TREEUSERS9 tree, char * x);
char * searchRepos (TREEREPOS tree, char * x);
TREE friendsTreeF(USERS users,int *k); 