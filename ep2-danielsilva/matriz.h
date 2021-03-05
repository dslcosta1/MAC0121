#include <stdio.h>

typedef struct {
  int lin;
  int col;
  int direita;
  int baixo;
  int tamDireita;
  int tamBaixo;
  int marcado;
} informacao; 


int ** alocaMatriz (int lin, int col);
informacao ** alocaMatrizInfo (int lin, int col);
char ** alocaMatrizChar (int lin,int col);
void liberaMatriz (int ** mat, int lin);
void liberaMatrizInfo (informacao ** mat, int lin);
void liberaMatrizChar (char ** mat, int lin);
void imprimeMatriz (char **a, int m, int n); 