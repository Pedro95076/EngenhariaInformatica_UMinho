/**
  * @file Ficheiro header referente ao catálogo de Users.
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct users *USERS;
USERS insertDataUsers(FILE *file);
int isEmptyUsers(USERS users);
USERS obtain_nextUser(USERS users);
char * obtain_typeUsers(USERS users);
char * obtain_IdUsers(USERS users);
char * obtain_LoginUsers(USERS users);
char * obtain_followersUsers(USERS users);
char * obtain_followersListUsers(USERS users);
char * obtain_followingUsers(USERS users);
char * obtain_followingListUsers(USERS users);
void freeUsers(USERS head);