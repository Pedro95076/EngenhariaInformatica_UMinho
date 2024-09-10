/**
  * @file Ficheiro com modularidade e encapsulamento referente a funções auxiliares.
  */
#include "data.h"

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

/**
 * @brief Função que conta o tamanho da mensagem (funciona para caracteres chineses e arabaes).
 * 
 * @param s Mensagem.
 * 
 * @return Tamanho da mensagem.
 */
int utf8_strlen(const char *s) // fonte: https://stackoverflow.com/questions/32936646/getting-the-string-length-on-utf-8-in-c
{
  int count = 0;
  while (*s) 
  {
    count += (*s++ & 0xC0) != 0x80;
  }
  return count;
}
