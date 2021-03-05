#include <stdlib.h>
#include <string.h>

typedef char* item; 
typedef struct cel {
  item info;
  struct cel * prox;
  struct ind * prox_indice;
} celula;

typedef struct ind {
  int linha;
  int quantidade;
  struct ind * prox;
} indice;


int busca(celula * inicio, char * palavra);
celula * insereOrdenado (celula * inicio, char * palavra) ;
indice * imprime_indices(indice * inicio);
celula * removePrimeiro (celula * inicio);
void insereNoInicio (celula *ini, char* palavra, int linha);