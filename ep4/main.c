/*
EP4 - MAC0121
Autor: Daniel Silva Lopes da Costa

Implementação de um indice remissivo, 
que receber um arquivo texto e devolve em quais linhas
a palavra ocorreu e quantas vezes ela ocorreu.

Foi adotado o valor 50 para o tamanho das palavra, 
pois a maior palavra da lingua portuguesa tem 46 letras.

No hash foi usado uma tabela de 400013 lugares, 
que é aproximadamente a quantidade de palavras que existe na lingua portuguesa.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listasligadas.h"
#include "listaPalavras.h"

/*_____FUNÇÕES PARA O HASH_____*/
int hashstring (char *str)
{
  int max_quant_palavra = 400013;
  /*int max_quant_palavra = 13;*/
  unsigned long hash = 5381;
  int caracter;
  int i = 0;
  caracter = str[0];
  while (caracter != '\0'){
      hash = ((hash << 5) + hash) + caracter; 
      i++;
      caracter = str[i];      
  }
  return(hash % max_quant_palavra);
}


int main(void) {
  /*Abertura do arquivo de entrada.*/
  char nome_arq_entrada[100];
  printf("Digite o nome do arquivo de texto a ser lido: ");
  scanf("%s", nome_arq_entrada);
  FILE *arq_entrada;
  arq_entrada = fopen(nome_arq_entrada, "r");
  if (arq_entrada == NULL) {
    printf ("Não encontrei o arquivo %s\n", nome_arq_entrada);
    printf("Digite o nome do arquivo de texto a ser lido: ");
    scanf("%s", nome_arq_entrada);
    FILE *arq_entrada;
    arq_entrada = fopen(nome_arq_entrada, "r");
  }

  char entrada;
  char entrada_anterior = '\0';
  char entrada_mais_anterior = '\0';
  int max_tam_palavra = 50;
  int max_quant_palavra = 400013;
  char* palavra = malloc(max_tam_palavra * sizeof(char));
  int tamPalavra = 0;
  int tamTabela = 100;
  int quant_palavra = 0;
  int contaLinha = 1;
  int indice_soma_linha = 0;
  celula ** lista = malloc(max_quant_palavra * sizeof(celula*));
  char ** lista_palavras = alocaMatrizChar(tamTabela,max_tam_palavra);
  int i;
  for(i = 0; i < max_quant_palavra; i++){
    lista[i] = 0;
  }
  palavra[0] = '\0';
  /*Leitura do arquivo, identificando as palavras e alocando elas na lista de palavras e na tabela hash*/
  while (fread(&entrada, sizeof(char), 1, arq_entrada) == 1) {
    if(('a' <= entrada_anterior && entrada_anterior <= 'z') || ('A' <= entrada_anterior && entrada_anterior <= 'Z') ||( entrada_anterior == '-' && 'a' <= entrada && entrada <= 'z' && 'a' <= entrada_mais_anterior && entrada_mais_anterior <= 'z') ||('0' <= entrada_anterior && entrada_anterior <= '9') || (entrada_anterior == '\'' && 'a' <= entrada && entrada <= 'z' && 'a' <= entrada_mais_anterior && entrada_mais_anterior <= 'z')){
      palavra[tamPalavra] = entrada_anterior;
      tamPalavra ++;
      palavra[tamPalavra] = '\0';
    }else if((entrada_anterior == '\n' && entrada == '-') || (entrada_anterior == '-' && entrada_mais_anterior == '\n')){
        indice_soma_linha = 1;
    }else{
      if (palavra[0] != '\0'){
        int hash_palavra = hashstring(palavra);
        if(!busca(lista[hash_palavra], palavra)){
          if(quant_palavra >= tamTabela){
            tamTabela = 2 * tamTabela; 
            lista_palavras = aumentaLista(lista_palavras, tamTabela,  max_tam_palavra); 
          }
          strcpy(lista_palavras[quant_palavra], palavra);
          quant_palavra++;
          lista[hash_palavra] = insereOrdenado(lista[hash_palavra], palavra);
        }
        insereNoInicio (lista[hash_palavra], palavra, contaLinha);
        palavra[0] = '\0';
        tamPalavra=0;
      }
      if(entrada_anterior == '\n') indice_soma_linha = 1;
      contaLinha += indice_soma_linha;
      indice_soma_linha = 0;
    }
    entrada_mais_anterior = entrada_anterior;
    entrada_anterior = entrada;
  }

  if(('a' <= entrada && entrada <= 'z') || ('A' <= entrada && entrada <= 'Z')){
      palavra[tamPalavra] = entrada;
      tamPalavra ++;
      palavra[tamPalavra] = '\0';
  }
  /*Mecanismo para quando o texto não tem ponto final, quando existe uma alavra no final do arquivo*/
  if (palavra[0] != '\0'){
    int hash_palavra = hashstring(palavra);
    if(!busca(lista[hash_palavra], palavra)){
      if(quant_palavra >= tamTabela){
        tamTabela = 2 * tamTabela; 
        lista_palavras = aumentaLista(lista_palavras, tamTabela,  max_tam_palavra); 
      }
        strcpy(lista_palavras[quant_palavra], palavra);
        quant_palavra++;
        lista[hash_palavra] = insereOrdenado(lista[hash_palavra], palavra);
      }
      insereNoInicio (lista[hash_palavra], palavra, contaLinha);
      palavra[0] = '\0';
      tamPalavra=0;
  }


  /*Ordenar lista de palavras*/
  int * indice_palavra = malloc(quant_palavra * sizeof(int));
  int f;
  for(f = 0; f < quant_palavra; f++){
    indice_palavra[f] = f; 
  } 
  quicksort(indice_palavra, lista_palavras, 0, quant_palavra-1);

  fclose(arq_entrada);
  
  /*Impressão de liberação das funções*/
  int e;
  int id;
  int hash_palavra;
  for(e = 0; e < quant_palavra; e++){
    id = indice_palavra[e];
    hash_palavra = hashstring(lista_palavras[id]);
    lista[hash_palavra] = removePrimeiro(lista[hash_palavra]);
  }
  free(indice_palavra);
  liberaMatrizChar(lista_palavras, tamTabela);
  free(palavra);
  free(lista);
  
  return(0);
}