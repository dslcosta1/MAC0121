#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "listaPalavras.h"


/*_____FUNÇÕES PARA LISTA DE PALAVRAS_____*/

/*Aloca a matriz de caracter que será a lista de palavras*/
char ** alocaMatrizChar (int lin, int col)
{
  char ** mat = malloc (lin * sizeof(char *));
  int i;
  for (i = 0; i < lin; i++)
    mat[i] = malloc (col * sizeof(char));
  return (mat);
}

/*Função que libera o espaço alocado para a lista de palavras*/
void liberaMatrizChar (char ** mat, int lin){
  int i;
  for (i = 0; i < lin; i++) free(mat[i]);
  free (mat);
}


/* Dobra o tamanho da lista de palavras */
char ** aumentaLista (char ** P, int tamTabela, int max_tam_palavra){
  char ** w = alocaMatrizChar(tamTabela, max_tam_palavra);
  int i;
  for (i = 0; i < tamTabela/2; i++)
    strcpy(w[i], P[i]);  
  liberaMatrizChar(P, tamTabela/2);
  return (w); 
} 

/* Ordenação da lista de palavras */
/*Troca*/
void troca (int v[], int a, int b)
{
  int aux;
  aux = v[a];
  v[a] = v[b];
  v[b] = aux;
}

/*Geração de números aleatórios*/
int sorteia(int min, int max)
{
    int k;
    double d;
    d = (double) rand() / ((double) RAND_MAX + 1);
    k = (int) (d * (max - min + 1));
    return (min + k);
}




/* Quicksort*/
int particiona (int v[], char ** lista_palavras, int ini, int fim)
{
  int i, j, pivo;
  pivo = v[ini];
  j = ini + 1;
  for(i = ini + 1; i<=fim; i++){
    if(strcmp(lista_palavras[v[i]],lista_palavras[pivo])<0){
      if(i != j){
        troca(v, i, j);
      }
      j++;
    }
  }
  troca(v, ini, j-1);
  return j-1;
}


void quicksort (int v[], char** lista_palavras, int ini, int fim)
{
  int pivo = sorteia(ini, fim);
  if(ini < fim){
    pivo = particiona(v, lista_palavras, ini, fim);
    quicksort(v,lista_palavras, ini, pivo-1);
    quicksort(v,lista_palavras, pivo+1, fim);
  }
}
