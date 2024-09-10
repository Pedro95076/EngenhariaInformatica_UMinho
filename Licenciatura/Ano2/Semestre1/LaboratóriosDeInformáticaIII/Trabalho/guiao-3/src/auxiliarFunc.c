/**
  * @file Ficheiro com modularidade e encapsulamento referente às funções auxiliares
  */
#include "auxiliarFunc.h"

/**
 * @brief variável global que determina o ano máximo para verificação
 */
#define MAX_YR  2022

/**
 * @brief variável global que determina o ano mínimo para verificação
 */
#define MIN_YR  2005

/**
 * @brief estrutura de dados auxiliar para a verificação da data
 */
struct data
{
    /** inteiro que indica o ano */
    int yyyy;
    /** inteiro que indica o mês */
    int mm;
    /** inteiro que indica o dia */
    int dd;
};

/**
 * @brief função auxiliar que verifica se o ano é bissexto
 * 
 * @param year inteiro que indica o ano
 * 
 * @return retorna 1 se for verdade
 */
int IsLeapYear(int year)
{
    return (((year % 4 == 0) &&
             (year % 100 != 0)) ||
            (year % 400 == 0));
}

/**
 * @brief função auxlidade que verifica se a data é válida
 * 
 * @param str string com a data
 * 
 * @return retorna 1 se for válida
 */
int isValidDate(char *str)
{
    int ano;
    int mes;
    int dia;
    int hora;
    int minuto;
    int segundo;

    if (sscanf(str,"%d-%d-%d %d:%d:%d",&ano,&mes,&dia,&hora,&minuto,&segundo) != 6)
        return 1;

    Data validDate = malloc(sizeof(struct data));

    validDate->dd = dia;
    validDate->mm = mes;
    validDate->yyyy = ano;

    //check range of year,month and day
    if (validDate->yyyy > MAX_YR ||
            validDate->yyyy < MIN_YR)
        return 1;
    if (validDate->mm < 1 || validDate->mm > 12)
        return 1;
    if (validDate->dd < 1 || validDate->dd > 31)
        return 1;
    //Handle feb days in leap year
    if (validDate->mm == 2)
    {
        if (IsLeapYear(validDate->yyyy))
        {
            if (validDate->dd > 29)
                return 1;
        } 
        else 
        {
            if (validDate->dd > 28)
                return 1;
        }
    }
    //handle months which has only 30 days
    if (validDate->mm == 4 || validDate->mm == 6 ||
            validDate->mm == 9 || validDate->mm == 11)
        if (validDate->dd > 30)
            return 1;

    if(validDate->yyyy == 2005)
    {
        if(validDate->mm < 4)
            return 0;
        else if(validDate->mm == 4 && validDate->dd < 7)
                return 0;
    }
                
    if(hora < 0 || hora > 24)
        return 1;

    if(minuto < 0 || minuto > 60)
        return 1;  

    if(segundo < 0 || segundo > 60)
        return 1;

    return 0;
}

/**
 * @brief função que verifica se o ficheiro está fazio
 * 
 * @param file ficheiro a testar
 */
void check_File(FILE *file)
{
    if(file == NULL)
    {
        perror("Unable to open file\n");
        exit(1);
    }
}

/**
 * @brief função que associada a key da hashtable a um determinado ID
 * 
 * @param id string que inclui o ID
 * 
 * @return retorna a key associada a um determinado ID
 */
unsigned int hash_key(char * id)
{
    int length = strlen(id);
    unsigned int key = 0;
    for (int i = 0; i < length; i++)
    {
        key += id[i];
        key = (key * (id[i])) % TABLE_SIZE;
    }
    
    return key;
}

/**
 * @brief função que testa se o valor é um inteiro
 * 
 * @param str string a testar
 * 
 * @return retorna 0 se for verdadeiro
 */
int testInt(char *str)
{
    int r = 0, i = 0;

    if(str[i] == '\0' || str[i] == '\n' || str[i] == '\r') r = 1;

    for (i=0; str[i]!='\0' && r==0; i++)
    {
        if(str[i]>=48 && str[i]<=57) r = 0;
        else r=1;
    }

    return r;
}

/**
 * @brief função que testa se o valor é uma string não nula
 * 
 * @param str string a testar
 * 
 * @return retorna 0 se for verdadeiro
 */

int testString(char *str)
{
    int r = 0, i = 0;

    if (str[i] == '\0') r=1;
    else r = 0;

    return r;
}

/**
 * @brief função que testa se a lista de followers apresenta o mesmo número de elementos que o valor de followers
 * 
 * @param follow string com o número de followers
 * 
 * @param str string com a lista de followers
 * 
 * @return retorna 0 se for verdadeiro
 */
int testFollowersList(char *follow, char *str)
{
    int r = 0;
    int count=0;
    int followers = atol(follow);

    if (str[0] != '[') r = 1;
    else if (strcmp(str,"[]") == 0 && followers == 0) r = 0;
    else 
    {
        if (strcmp(str,"[]") == 0 && followers != 0) r=1;
        else 
        {
           int i;

           for(i=0; str[i]!='\0'; i++) 
           {
               if(str[i] == ',') count++;
           }
           count++;
           
           if(followers==count) r = 0;
           else r=1;
        }
    }

    return r;
}

/**
 * @brief função que testa se a lista de following apresenta o mesmo número de elementos que o valor de following
 * 
 * @param follow string com o número de following
 * 
 * @param str string com a lista de following
 * 
 * @return retorna 0 se for verdadeiro
 */
int testFollowingList(char *follow, char *str)
{
    int r = 0;
    int count=0;
    int following = atol(follow);

    if (str[0] != '[') r = 1;
    else if (strcmp(str,"[]") == 0 && following == 0) r = 0;
    else 
    {
        if (strcmp(str,"[]") == 0 && following != 0) r=1;
        else 
        {
           int i;

           for(i=0; str[i]!='\0'; i++) 
           {
               if(str[i] == ',') count++;
           }
           count++;
           
           if(following==count) r = 0;
           else r=1;
        }
    }

    return r;
}

/**
 * @brief função que testa o tipo do utilizador
 * 
 * @param str string a testar
 * 
 * @return retorna 0 se for um tipo válido
 */
int testType(char *str)
{
    int r = 0;

    if(strcmp(str, "Bot") == 0 || strcmp(str, "Organization")==0 || strcmp(str,"User")==0) r=0;
    else r=1;

    return r;
}

/**
 * @brief função que testa se a string de login é válida
 * 
 * @param str string a testar
 * 
 * @return retorna 0 se for um login válido
 */
int testLogin(char *str)
{
    int r = 1;
    for (int i=0; str[i]!='\0' ; i++)
    {
        if((str[i]>=48 && str[i]<=57) || (str[i]>=65 && str[i]<=90) || (str[i]>=97 && str[i]<=122) || str[i]==45) r=0;
        else r=1;
    }

    return r;
}

/**
 * @brief função que testa se a string é um booleano
 * 
 * @param str string a testar
 * 
 * @return retorna 0 se for verdadeiro
 */
int testBool(char *str)
{
    int r = 1;

    if(strcmp(str, "True") == 0 || strcmp(str, "False")==0 ) r=0;
    else r=1;

    return r;
}

/**
 * @brief Função que permite a comparação entre 3 datas.
 * 
 * @param start_date Data inicial.
 * 
 * @param end_date Data final.
 * 
 * @param date Data a descobrir se se encontra entre a inicial e a final.
 * 
 * @return Retorna 1 se a data se encontra entre a inicial e a final.
 */
int compareDates(char *start_date, char *end_date, char *date)
{
    int r = 0;
    if (strcmp(start_date, date) < 0 && strcmp(date, end_date) < 0) r = 1;
    return r;
}

/**
 * @brief Função que permite a comparação entre 2 datas.
 * 
 * @param start_date Data inicial.
 * 
 * @param date Data a descobrir se é maior do que a final.
 * 
 * @return Retorna 1 se a data é maior do que a inicial.
 */
int verifyDate(char *start_date, char *date)
{
    int r = 0;
    if (strcmp(start_date, date) < 0) r = 1;
    return r;
}