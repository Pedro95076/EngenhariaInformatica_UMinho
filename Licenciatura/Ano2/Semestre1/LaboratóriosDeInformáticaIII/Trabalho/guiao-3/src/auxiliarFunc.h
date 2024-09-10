/**
  * @file Ficheiro header referente às funções auxiliares
  */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define TABLE_SIZE 300000

typedef struct data *Data;
int isValidDate(char *str);
void check_File(FILE *file);
unsigned int hash_key(char * id);
int testInt(char *str);
int testString(char *str);
int testDateHour(char *str);
int testFollowersList(char *follow, char *str);
int testFollowingList(char *follow, char *str);
int testType(char *str);
int testLogin(char *str);
int testBool(char *str);
int compareDates(char *start_date, char *end_date, char *date);
int verifyDate(char *start_date, char *date);