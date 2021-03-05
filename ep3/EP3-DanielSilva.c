/*
EP3 - MAC0121 - Algoritmos e Estruturas de Dados I 
Autor: Daniel Silva Lopes da Consta 
N°UPS 11302720 

Foram implementados 4 algoritmos de ordenação: 
 - Bubblesort; 
 - Inserction sort; 
 - Mergesort; 
 - Quicksort. 
E foram contadas o número de comparações e movimentações de cada um para diferentes listas: 
 - Crescente; 
 - Descrescente, 
 - Semi-Crescente, 
 - Aleatória, 
 - Constante. 
Com os seguintes tamanhos: 250, 500, 1000, 2000, 4000, 8000, 16000, 32000.
*/

#include <stdio.h>
#include <stdlib.h> 
#include <time.h>

typedef struct{
  long int comparacao;
  long int movi;
} conta;

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



/*Bubblesort*/
void bubblesort (int v[], int n, conta * contagem)
{
  int inv = 1;
  int i, j;
  for(j = 0; j < n-1 && inv; j++){
    inv = 0;
    for(i = 0; i < n-j-1; i++){
      contagem -> comparacao ++;
      if( v[i] > v[i+1]){
        contagem -> movi = contagem -> movi + 3;
        troca(v, i, i+1);
        inv = 1;
      }
    }
  }
}



/*Inserction sort*/
void inserction (int v[], int n, conta * contagem)
{
  int bag, i, x;
  for( bag = 1; bag < n; bag++){
    x=v[bag];
    for( i = bag-1; i >= 0 && v[i]>x; i--){
      contagem -> comparacao = contagem -> comparacao + 1;
      contagem -> movi = contagem -> movi + 1;
      v[i+1]=v[i];
    }
    if(i>=0) contagem -> comparacao = contagem -> comparacao + 1;
    contagem -> movi = contagem -> movi + 2;
    v[i+1]=x;
  } 
}


/*Mergesort*/
void intercala (int v[], int ini, int meio, int fim, conta * contagem)
{
  int * av = malloc((fim-ini)*sizeof(int));
  int p = ini, s = meio, pav = 0;
  while( p < meio && s < fim){
    contagem -> comparacao = contagem -> comparacao + 1;
    contagem -> movi = contagem -> movi + 1;
    if( v[p] < v[s]){
      av[pav] = v[p]; p++; pav++;
    }else{
      av[pav] = v[s]; s++; pav++;
    }
  }
  while( p < meio ){
    av[pav++] = v[p++];
    contagem -> movi = contagem -> movi + 1;
  }
  while( s < fim ){
    av[pav++] = v[s++];
    contagem -> movi = contagem -> movi + 1;
  }
  int i;
  for( i = ini; i < fim; i++){
    contagem -> movi = contagem -> movi + 1;
    v[i] = av[i-ini];
  }
  free(av);
}

void mergesort (int v[], int i, int f, conta * contagem)
{
  int meio = (i+f)/2;
  if(f-i>1){
    mergesort(v, i, meio, contagem);
    mergesort(v, meio, f, contagem);
    intercala(v, i, meio, f, contagem);
  }
}


/* Quicksort*/
int particiona (int v[], int ini, int fim, conta * contagem)
{
  int i, j, pivo;
  pivo = v[ini];
  contagem -> movi = contagem -> movi + 1;
  j = ini + 1;
  for(i = ini + 1; i<=fim; i++){
    contagem -> comparacao = contagem -> comparacao + 1;
    if(v[i]<pivo){
      if(i != j){
        troca(v, i, j);
        contagem -> movi = contagem -> movi + 3;
      }
      j++;
    }
  }
  troca(v, ini, j-1);
  contagem -> movi = contagem -> movi + 3;
  return j-1;
}


void quicksort (int v[], int ini, int fim, conta * contagem)
{
  int pivo = sorteia(ini, fim);
  if(ini < fim){
    pivo = particiona(v, ini, fim, contagem);
    quicksort(v, ini, pivo-1, contagem);
    quicksort(v, pivo+1, fim, contagem);
  }

}


int main(void) {
  int tipo, n, i;
  int comp[1000];
  int troc[1000];
  conta * contagem = malloc(sizeof(conta));
  printf("Selecione uma opção:\n");
  printf("1 : Bubblesort\n 2 : Ordenação por inserção\n 3 : Mergesort\n 4 : Quicksort\n");
  printf("Opção:");
  scanf("%d", &tipo);
  
  switch (tipo)
    {
    case 1:
      printf("# -------- BUBLESORT --------\n");
      break;
    case 2:
      printf("# -------- INSERCTION --------  \n");
      break;
    case 3: 
      printf("# --------  MERGESORT --------\n");
      break;
    case 4: 
      printf("# --------  QUICKSORT --------\n");
      break;
    default:
      printf("Modo de operação inválido! Entre com um número entre 1 e 4\n");
      printf("Opção:");
      scanf("%d", &tipo);
    }

  int k;
  int cont;
  for(k = 0; k < 5; k++){
    cont = 0;
    n = 250; /*Tamanho do vetor*/
    while(n<=32000){
      int * lista = malloc(n*sizeof(int));
      /*Geração das listas de instâncias*/
      if(k == 0){ /*Lista Ordenada Crescente*/
        for(i = 0; i < n; i++){
         lista[i] = i;
        }
      }else if (k == 1){ /*Lista Ordenada Descrescente*/
        for(i = 0; i < n; i++){
          lista[i] = n-i-1;
        }
      } else if (k == 2){ /*Lista Semi-Ordenada*/
        for(i = 0; i < n; i++){
         lista[i] = i;
        }
        int r, s;
        for(i = 0; i < n/10; i++){ 
          r = sorteia(0, n-1);
          s = sorteia(0, n-1);
          if(r != s){
            troca(lista, r, s);
          }
        }
      } else if (k == 3){ /*Lista Aleatória*/
        for(i = 0; i < n; i++){
          lista[i] = sorteia(-n, n);
        }
      } else{ /*Lista Constantes*/
        for(i = 0; i < n; i++){
          lista[i] = 1;
        }
      }
     
      contagem -> comparacao = 0;
      contagem -> movi = 0;
      if(tipo == 1){
        bubblesort (lista, n, contagem);
      } else if(tipo == 2){
        inserction(lista, n, contagem);
      } else if(tipo == 3){
        mergesort(lista, 0, n, contagem);
      }else{
        quicksort(lista, 0, n-1, contagem);
      }
      comp[cont] = contagem -> comparacao;
      troc[cont] = contagem -> movi;

      /*Testa se o vetor está mesmo ordenado, se não estiver é impresso a palavra ERRO*/
      int g;
      int testa = 0;
      for(g = 1; g < n; g++){
        if(lista[g-1]>lista[g]){
          testa = 1;
        }
      }
      if(testa) printf("\nERRO\n");


      free(lista);
      n = n * 2;
      cont++;
    }


    /* ----------- IMPRESSÃO ------------*/
    /*Os resultados das comparações e movimentações foram impressos desse jeito para facilitar a construção das lista em python, onde foram implementados os gráficos e tabelas*/

    switch(k)
    {
    case 0: /*Lista Ordenada Crescente*/
      printf("\n # LISTA ORDENADA CRESCENTE\n");
      break;
    case 1: /*Lista Ordenada Descrescente*/
      printf("\n # LISTA ORDENADA DECRESCENTE\n");
      break;
    case 2: /*Lista Semi-Ordenada*/
      printf("\n # LISTA SEMI-ORDENADA\n");
      break;
    case 3: /*Lista Aleatória*/
      printf("\n # LISTA ALEATÓRIA\n");
      break;  
    case 4: /*Lista Constantes*/
      printf("\n # LISTA CONSTANTE\n");
      break;
    }

    switch (tipo)
    {
    case 1:
      printf("buble_");
      break;
    case 2:
      printf("inser_");
      break;
    case 3: 
      printf("merge_");
      break;
    case 4: 
      printf("quick_");
      break;
    }

    switch (k)
    {
    case 0:
      printf("Cres_");
      break;
    case 1:
      printf("Decres_");
      break;
    case 2: 
      printf("semiCres_");
      break;
    case 3: 
      printf("alet_");
      break;
    case 4:
      printf("unif_");
      break;
    }

    printf("Comp = [");
    int i;
    for(i = 0; i < cont - 1; i++){
      printf("%d, ", comp[i]);
    }
    printf("%d] ", comp[cont-1]);
    printf("\n");

    switch (tipo)
    {
    case 1:
      printf("buble_");
      break;
    case 2:
      printf("inser_");
      break;
    case 3: 
      printf("merge_");
      break;
    case 4: 
      printf("quick_");
      break;
    }

    switch (k)
    {
    case 0:
      printf("Cres_");
      break;
    case 1:
      printf("Decres_");
      break;
    case 2: 
      printf("semiCres_");
      break;
    case 3: 
      printf("alet_");
      break;
    case 4:
      printf("unif_");
      break;
    }

    printf("Movi = [");
    for( i = 0; i < cont - 1; i++){
      printf("%d, ", troc[i]);    
    }
    printf("%d] ", troc[cont-1]);
    printf("\n");
  }
  free(contagem);
    
  return 0;
}