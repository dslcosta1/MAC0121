#include <stdio.h>

typedef struct {
  int lin;
  int col;
  int nPalavra;
  char direcao;
} palavra; 

typedef palavra item;

typedef struct {
  item * v;
  int topo;
  int tam;
} pilha;

pilha * criaPilha (int tam);
void destroiPilha (pilha * p);
void empilha (pilha * p, item x);
item desempilha (pilha * p);
int pilhaVazia (pilha * p);
item topoDaPilha (pilha *p);
pilha * aumentaPilha (pilha * p); 



