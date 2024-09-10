/**
  * @file Ficheiro header referente às estruturas de tuplos.
  */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "data_commits.h"
#include "data_tree.h"

typedef struct top *TOP;
typedef struct string *STRING;
TOP insertDataTop(TOP top, int info, int counter);
int isEmptyTop(TOP top);
int isEmptyString(STRING top);
TOP obtain_nextTop(TOP top);
STRING obtain_nextString(STRING top);
int obtain_CountTop(TOP top);
TOP countInfo(TOP top, int id);
STRING countInfoStr(STRING top, char *info, int *count);
int obtain_topID(TOP head);
char * obtain_stringID(STRING head);
void mostFreq(TOP top, int *id, int *count);
char * mostFreqString(STRING string);
void printTop(TOP top);
void printString(STRING string);
void freeTop(TOP head);
void freeString(STRING head);
TOP countInfoLen(TOP top, int info, int count);