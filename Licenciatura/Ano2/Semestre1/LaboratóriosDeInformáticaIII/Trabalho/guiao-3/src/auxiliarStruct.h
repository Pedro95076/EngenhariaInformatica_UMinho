/**
  * @file Ficheiro header referente às estruturas de tuplos.
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string *STRING;
typedef struct topUsersStruct *TOPUSERSSTRUCT;
typedef struct data *DATA;
DATA insertData(DATA data, char *info);
void topUsersSave (TOPUSERSSTRUCT a, int k, char *id, char*login, int counter);
int isEmptyString(STRING top);
int isEmptyData(DATA data);
int isEmptyTopUsersStruct(TOPUSERSSTRUCT top, int i);
STRING obtain_nextString(STRING top);
DATA obtain_nextData(DATA data);
char * obtain_stringID(STRING head);
char *obtain_dataInfo(DATA data);
int obtain_TopUsersCount (TOPUSERSSTRUCT a, int i);
char *obtain_TopUsersLogin (TOPUSERSSTRUCT a, int i);
char *obtain_TopUsersId (TOPUSERSSTRUCT a, int i);
void obtain_topUsers(TOPUSERSSTRUCT a, int i, char *login, char *id, int *count);
void freeString(STRING head);
void freeData(DATA head);
void freeTopUsersStruct(TOPUSERSSTRUCT head);
STRING countInfoStr(STRING top, char *info, int *count);
char *mostFreqString(STRING string);
TOPUSERSSTRUCT initTopUsersStruct (int N);
void topUsersSort (TOPUSERSSTRUCT a, int f);
void freeTopUsersStructs(TOPUSERSSTRUCT topUsers, int N);