#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char ** alocaMatrizChar (int lin, int col);
void liberaMatrizChar (char ** mat, int lin);
char ** aumentaLista (char ** P, int tamTabela, int max_tam_palavra);
void troca (int v[], int a, int b);
int sorteia (int min, int max);
int particiona (int v[], char ** lista_palavras, int ini, int fim);
void quicksort (int v[], char** lista_palavras, int ini, int fim);
int comparaPalavra(char * palavra1, char * palavra2);