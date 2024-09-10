#include "abin.h"
#include <time.h>


int main (){
  int v1[15] = { 1, 3, 5, 7, 9,11,13,15,17,19,21,23,25,27,29},
      N=15, i;
  ABin a1,r;
  
  srand(time(NULL));
  
  printf ("_______________ Testes _______________\n\n");
  // N = rand() % 16;
  a1 = RandArvFromArray (v1, N);
  printf ("________________________________________\n");
  printf ("Primeira árvore de teste (%d elementos)\n", N);
  dumpABin (a1, N);
  
  /*
  printf ("Espinha\n");
  constroiEspinha_sol (&a1);

  dumpABin (a1, N);
  
  printf ("Equilibrar espinha\n");
  equilibraEspinha_sol (&a1,N);
  dumpABin (a1, N);
  */
  
  i = rand() %N;
  printf ("Remoção do elemento %d\n", v1[i]);
  removeElem (&a1,v1[i]);
  dumpABin (a1, --N);
  
  
  r = removeMenor (&a1);
  printf ("Remoção do menor %d\n", r->valor);
  dumpABin (a1, --N);

  printf ("Remoção da raiz %d\n", a1->valor);
  removeRaiz (&a1);
  dumpABin (a1, --N);

  freeABin (a1);

/*
  a1 = newABin(v1[7], RandArvFromArray (v1  ,7), 
                      RandArvFromArray (v1+8,7));
  N = 15;
  printf ("_______________________________________\n");
  printf ("Segunda árvore de teste (%d elementos)\n", N);
  dumpABin (a1, N);
  
  printf ("Rotação à direita\n");
  rodaDireita (&a1);
  dumpABin (a1, N);

  printf ("Rotação à esquerda\n");
  rodaEsquerda (&a1);
  dumpABin (a1, N);
  
  printf ("Promoção do maior\n");
  promoveMaior_sol (&a1);
  dumpABin (a1, N);
  
  printf ("Promoção do menor\n");
  promoveMenor_sol (&a1);
  dumpABin (a1, N);
  

  printf ("\n\n___________ Fim dos testes ___________\n\n");
*/
  return 0;
} 
