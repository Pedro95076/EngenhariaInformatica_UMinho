/**
 * @file Ficheiro header referente às funções da Hashtable dos users
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "auxiliarTree.h"
#include "auxiliarStruct.h"

typedef struct HashTableUser *HT_Users;

void init_HashTableUsers(HT_Users *hash);
void print_tableUsers(HT_Users *hash);
int insert_HashTableUsers(HT_Users *hash, HT_Users node);
HT_Users find_HashTableUsers(HT_Users *hash, char *id);
HT_Users listU(HT_Users users);
int find_HashTableUsersBool(HT_Users *hash, char *id);
void incrementAuxCount (HT_Users *hash, char *id);
void handle_UsersFile(FILE* file, HT_Users *users);
HT_Users find_HashTableUsersKey(HT_Users *hash, int key);
char *obtain_userType(HT_Users user);
char *obtain_userId(HT_Users user);
HT_Users obtain_nextUser(HT_Users user);
char *obtain_userLogin(HT_Users user);
int obtain_userAuxCount(HT_Users user);
void resetUsersCounter(HT_Users *hash);
char *find_userFollowers(HT_Users *users, char *id);
char *find_userFollowing(HT_Users *users, char *id);
char *find_userFollowersList(HT_Users *users, char *id);
char *find_userFollowingList(HT_Users *users, char *id);
char *find_userLogin(HT_Users *users, char *id);
int countTypeUsers(HT_Users *users);
int countTypeOrganizations(HT_Users *users);
int countTypeBots(HT_Users *users);
TREE countBotsTree(HT_Users *users, TREE bots);
TREE friendsTree(HT_Users *users, char *id, int *k);
float countUsers(HT_Users *users);
TOPUSERSSTRUCT activeUsers(HT_Users *users, TOPUSERSSTRUCT topUsers, int N);
TREE friendsTree(HT_Users *users, char *id, int *k);
void free_TableUsers(HT_Users *users);