#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

pilha * criaPilha (int tam) {
  pilha * p = malloc(sizeof(pilha));
  p->tam = tam;
  p->topo = 0;
  p->v = malloc (tam * sizeof(item));
  if (p->v == NULL)
    return NULL; 
  return p;
} 
  
void destroiPilha (pilha * p) {
  free (p->v);
  free (p);
} 
  
void empilha (pilha * p, item x) {
  if (p->topo == p->tam)
    p = aumentaPilha (p);
  p->v[p->topo] = x;
  p->topo ++;
}
  
item desempilha (pilha * p) {
  if (!pilhaVazia (p)){
    p->topo --;
    return (p->v[p->topo]);
  }
}
 
int pilhaVazia (pilha * p) {
  return (p->topo == 0); 
}

item topoDaPilha (pilha *p) {
  if (!pilhaVazia(p)){
    return (p->v[p->topo - 1]);
  }
}

/* dobra o tamanho da pilha */
pilha * aumentaPilha (pilha * P){
  item *w = malloc (2 * P->tam * sizeof(item)); 
  int i; 
  for (i = 0; i < P->tam; i++)
    w[i] = P->v[i]; 
  P->tam = 2 * P->tam; 
  free(P->v);
  P->v = w;
  return (P); 
} 