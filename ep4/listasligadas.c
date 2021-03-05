#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "listasligadas.h"

/*_____FUNÇÕES PARA LISTA LIGADA_____*/

/*Função que busca na tabela hash a palavra*/
int busca(celula * inicio, char * palavra){
    if (inicio == NULL) return 0;
    else if(strcmp(inicio -> info, palavra)==0) return 1;
  return (busca (inicio->prox, palavra));
}


/*Função que insere nova celula de palavra na tabela hash, já é alocado de forma ordenada*/
celula * insereOrdenado (celula * inicio, char * palavra) {
  celula * aux; 
  if (inicio == NULL || strcmp(inicio->info, palavra) >= 0) {
    aux = inicio; 
    inicio = malloc(sizeof(celula));
    inicio->info = malloc(46 * sizeof(char));
    strcpy(inicio->info, palavra);
    inicio->prox = aux;
    inicio->prox_indice = NULL;
  }
  else inicio->prox = insereOrdenado (inicio->prox, palavra);
  return inicio;
}

/*Imprime e libera os indices remissivos da lista ligada de indices*/
indice * imprime_indices(indice * inicio){
  /*indice * aux = inicio;*/
  if(inicio != NULL && inicio->prox != NULL){
    inicio->prox = imprime_indices(inicio->prox);
  }
  if(inicio->quantidade>1)
    printf(" %d(%d)", inicio->linha, inicio->quantidade);
  else printf(" %d", inicio->linha);
  free(inicio);
  return (NULL);
}

/*Remove o termo inicial da lista ligada de palavras*/ 
celula * removePrimeiro (celula * inicio) {
  celula * aux = inicio;
  if (inicio != NULL){
    printf("%s", inicio->info); 
    inicio->prox_indice = imprime_indices
    (inicio->prox_indice);
    printf("\n");
    inicio = inicio->prox;
    free (aux->info);
    free (aux);
  } 
  return inicio;
} 




/*Coloca o indice remissivo referente a uma linha na celula da palavra*/
void insereNoInicio (celula *ini, char* palavra, int linha) {
  celula * p;
  for (p = ini; p != NULL && strcmp(p->info,palavra)!=0; p = p->prox);
  /*indice * inicio = ini->prox_indice;*/
  if(p != NULL && p->prox_indice != NULL && p->prox_indice->linha == linha){
    p->prox_indice->quantidade++;
  }else{
    indice * novo = malloc (sizeof(indice)); 
    novo->linha = linha;
    novo->quantidade = 1;
    novo->prox = p->prox_indice;
    p->prox_indice = novo;
  } 
}