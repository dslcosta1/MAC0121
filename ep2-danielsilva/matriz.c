#include <stdio.h>
#include <stdlib.h> 
#include "matriz.h"


int ** alocaMatriz (int lin, int col) {
  int ** mat = malloc (lin * sizeof(int *));
  int i;
  for (i = 0; i < lin; i++)
    mat[i] = malloc (col * sizeof(int));
  return (mat);
}

informacao ** alocaMatrizInfo (int lin, int col) {
  informacao ** mat = malloc (lin * sizeof(informacao *));
  int i;
  for (i = 0; i < lin; i++)
    mat[i] = malloc (col * sizeof(informacao));
  return (mat);
}

char ** alocaMatrizChar (int lin, int col){
    char ** mat = malloc (lin * sizeof(char *));
  int i;
  for (i = 0; i < lin; i++)
    mat[i] = malloc (col * sizeof(char));
  return (mat);
}


void liberaMatriz (int ** mat, int lin){
  int i;
  for (i = 0; i < lin; i++) free(mat[i]);
  free (mat);
}

void liberaMatrizInfo (informacao ** mat, int lin){
  int i;
  for (i = 0; i < lin; i++) free(mat[i]);
  free (mat);
}

void liberaMatrizChar (char ** mat, int lin){
  int i;
  for (i = 0; i < lin; i++) free(mat[i]);
  free (mat);
}

void imprimeMatriz (char **a, int m, int n) {
    int i,j;
    for (i = 0; i < m; i++){
        for (j = 0; j <n; j++)
          if(a[i][j] != '1') printf("%2c", a[i][j]);
          else printf("%2c", '*');
        printf("\n");
    }
}