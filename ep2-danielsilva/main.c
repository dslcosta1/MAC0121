/* EP2 - MAC0121

Autor: Daniel Silva Lopes da Costa
NUSP: 11302720 

Foi implementado um programa em C, onde foram chamadas as bibliotecas Matriz - responsável pela criação, impressão e liberção de espaço das matrizes - neste EP foram usadas três matrizes, a primeira do tipo inteiro com a entrado do usuário, a segunda formada por structs de Informação, que indica se naquela célula inicia-se palavra ou não, qual o tamanho da palavra, e quantas letras sobrepostas exite naquela célula. Por fim temos a matriz de char com a saída final do tabuleiro.

Também foi usado a biblioteca de Pilhas, a pilha foi utilizada no backtrak e ela foi formada por structs de palavra, que trazem a posição do início de uma palavra, a direção dela, para baixo ou para direita e o número correpondente a essa palavra na lista de palavras.

O Progama possui três parte principais:

* BACKTRACK (processamento)
  - apagaPalavra()
  - marcaPalavra()
  - palavraValida()
  - palavraCruzada() -> Função principal do módulo

* PRE-PROCESSAMENTO
  - tamDireita()
  - tamBaixo()
  - direita()
  - baixo()
  - pre_processamento() -> Função principal do módulo

* ENTRADA DE DADOS
  - main()
*/

#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include "pilha.h"
#include "matriz.h"

/*---------------- BackTrack ------------------*/

/*Função que apaga uma palavra que foi colocada no tabuleiro, para que o backtrack funcione, usa uma variável da matriz de informações que indica quantas vezes um letra foi marcada.*/
void apagaPalavra (informacao ** tabProcessado, char ** tabFinal, char * soPalavra, char dir, int i, int  j){
  int k;
  if(dir == 'd'){
    for(k = 0; k < tabProcessado[i][j].tamDireita; k++){
      if(tabProcessado[i][j+k].marcado == 1){
        tabFinal[i][j+k] = '0';
      }
      tabProcessado[i][j+k].marcado--;
    }
  }else{
    for(k = 0; k<tabProcessado[i][j].tamBaixo; k++){
      if(tabProcessado[i+k][j].marcado == 1){
        tabFinal[i+k][j] = '0';
      }
      tabProcessado[i+k][j].marcado--;
    }
  }
  return;
}



/*Função responável pela marcação das palavras no tabuleiro final */
void marcaPalavra (informacao ** tabProcessado, char ** tabFinal, char * soPalavra, char dir, int i, int  j){
  int k;
  int encaixa = 1;
  if(dir == 'd'){
    for(k = 0; k < tabProcessado[i][j].tamDireita; k++){
      tabFinal[i][j+k] = soPalavra[k];
      tabProcessado[i][j+k].marcado++;
    }
  }else{
    for(k = 0; k < tabProcessado[i][j].tamBaixo; k++){
      tabFinal[i+k][j] = soPalavra[k];
      tabProcessado[i+k][j].marcado++;
    }
  }
  return;
}


/*Função que testa se a palavra encaixa ou não, já sabemos que o tamanho está correto, falta apenas testar se as letras encaixam com as outras que já foram colocadas*/
int palavraValida(informacao ** tabProcessado, char ** tabFinal, char * soPalavra, char dir, int i, int j){
  int k;
  int encaixa = 1;
  if(dir == 'd'){
    for(k = 0; k < tabProcessado[i][j].tamDireita; k++){
      if(tabFinal[i][j+k] != '0'){
        if(tabFinal[i][j+k] != soPalavra[k]){
          encaixa = 0;
        }
      }
    }
  }else{
    for(k = 0; k < tabProcessado[i][j].tamBaixo; k++){
      if(tabFinal[i+k][j] != '0'){
        if(tabFinal[i+k][j] != soPalavra[k]){
          encaixa = 0;
        }
      }
    }
  }
  return encaixa;
}


/*Função onde será realizado o backtrak, vai receber todas as informações vindas do pré-processamento e vai criar um matriz cópia da entrada, no formato char, vai chamar a função que testa se aquela palavra determinada cabe naquela posição.

Também criará a pilha responsável pelo Backtrack, a qual será formada por uma esturtura que marcará a posiçõa inicial daquela palavra, o indice da palavra na lista e se ela está para direita ou para baixo;
*/
void palavraCruzada(int ** tab, informacao ** tabProcessado, char ** listaPalavras, int * tamPalavras,
int * dispoPalavras, int x, int y, int n){
  char ** tabFinal = alocaMatrizChar (x, y);
  int p, q;
  for(p = 0; p < x; p++){
    for(q = 0; q < y; q++){
      if(tab[p][q] == 0){
        tabFinal[p][q]='0';
      }else{
        tabFinal[p][q]='1';
      }
    }
  }

  pilha *dec = criaPilha (2 * x * y);
  int i = 0, j = 0;
  palavra nova;
  nova.direcao = 'd';
  nova.nPalavra = 0;
  nova.lin = 0;
  nova.col = 0;

  while(i < x && j < y){
      if((nova.direcao == 'd' && tabProcessado[i][j].direita == 1) || (nova.direcao == 'b' && tabProcessado[i][j].baixo == 1)){
        int segue;
        segue = 0;

        while(!segue && nova.nPalavra<n){
          if(nova.direcao == 'd'){ 
            if( tabProcessado[i][j].tamDireita == tamPalavras[nova.nPalavra] && dispoPalavras[nova.nPalavra] == 0){
              if(palavraValida(tabProcessado, tabFinal, 
              listaPalavras[nova.nPalavra], nova.direcao, i, j)){
                segue = 1;
              }else{
                nova.nPalavra++;
              }
            }else{
              nova.nPalavra++;
            }
          }else if(nova.direcao == 'b'){ 
            if(tabProcessado[i][j].tamBaixo == tamPalavras[nova.nPalavra] && dispoPalavras[nova.nPalavra] == 0){
              if(palavraValida(tabProcessado, tabFinal, listaPalavras[nova.nPalavra], nova.direcao, i, j)){
                segue = 1;
              }else{
                nova.nPalavra++;
              }
            }else{
              nova.nPalavra++;
            }
          }
        }
      
          if(segue){
            marcaPalavra(tabProcessado, tabFinal, listaPalavras[nova.nPalavra], nova.direcao, i, j);
            empilha(dec, nova);
            dispoPalavras[nova.nPalavra]=1;
            if(nova.direcao == 'd'){
              nova.direcao = 'b';
            }else{
              nova.direcao = 'd';
              if(j == y-1){
                i++;
                j = 0;
              }else{
                j++;
              }
            }
            nova.nPalavra = 0;
            nova.lin = i;
            nova.col = j;
          }else{/*BackTrack*/
            if (pilhaVazia (dec)) {
	            printf("nao ha solucao\n");
              liberaMatrizChar(tabFinal, x);
	            destroiPilha (dec);
	            return;
            }
            nova = desempilha (dec);
            i = nova.lin;
            j = nova.col;
            apagaPalavra(tabProcessado, tabFinal, listaPalavras[nova.nPalavra], nova.direcao, i, j);
            dispoPalavras[nova.nPalavra] = 0;
            nova.nPalavra++;
            
          }
        }else{
          if(nova.direcao == 'd'){
              nova.direcao = 'b';
          }else{
              nova.direcao = 'd';
              if(j == y-1){
                i++;
                j = 0;
              }else{
                j++;
              }
            }
          nova.nPalavra = 0;
          nova.lin = i;
          nova.col = j;
        } 
  }
  imprimeMatriz (tabFinal, x, y);
  destroiPilha(dec);
  liberaMatrizChar(tabFinal, x);
  return;
}


/*------------ PRE-PROCESSAMENTO --------------*/


/*Função que na certeza de que naquela célula se inicia palavra, devolve quantas letras tem nessa palavra, para a direita*/
int tamDireita(int ** tab, int linha, int coluna, int x, int y, int inicio){
  int tamanho = 1;
  if(inicio == 0){
    return 0;
  }else{
    while(tab[linha][coluna+tamanho]==0 && coluna+tamanho<y-1) tamanho++;
    if(coluna+tamanho == y-1){
      if(tab[linha][coluna+tamanho]==0){
        tamanho++;
      }
    }
  return tamanho;
  }
}

/*Função que na certeza de que naquela célula se inicia palavra, devolve quantas letras tem nessa palavra, para baixo*/
int tamBaixo(int ** tab, int linha, int coluna, int x, int y, int inicio){
  int tamanho = 1;
  if(inicio == 0){
    return 0;
  }else{
    while(tab[linha+tamanho][coluna]==0 && linha+tamanho<x-1) tamanho++;
    /*if(tab[linha+tamanho][coluna]==0) tamanho++;*/
    if(linha+tamanho == x-1){
      if(tab[linha+tamanho][coluna]==0){
        tamanho++;
      }
    }
  return tamanho;
  }
}


/*Função que testa se é início da palavra para direita em determinada posição*/
int baixo(int ** tab, int linha, int coluna, int x, int y){
  int iniPalavra = 0;
  if(linha+1<x){
    if(linha == 0 && tab[linha+1][coluna] == 0){
      iniPalavra = 1;
    }
    if(linha>0){
      if(tab[linha-1][coluna]==-1 && tab[linha+1][coluna]==0){
        iniPalavra = 1;
      }
    }
  }
  return iniPalavra;
}


/*Função que testa se é início de palavra para baixo em determinada posição*/
int direita(int ** tab, int linha, int coluna, int x, int y){
  int iniPalavra = 0;
  if(coluna+1 < y){
    if(coluna == 0 && tab[linha][coluna+1] == 0){
      iniPalavra=1;
    }
    if(coluna > 0){
      if(tab[linha][coluna-1] == -1 && tab[linha][coluna+1] == 0){
        iniPalavra=1;
      }
    }
  }
  return iniPalavra;
}


/*Função responsável pelo pré-processamento, para otimizar o backtrack*/
void pre_processamento(int ** tab, char ** listaPalavras, int * tamPalavras, int * dispoPalavras, int x, int y, int n){
  informacao ** tabProcessado = alocaMatrizInfo (x, y);
  int i, j;
  for( i = 0; i < x; i++){
    for( j = 0; j < y; j++){
      informacao nova;
      nova.lin = i;
      nova.col = j;
      nova.direita = -1;
      nova.tamDireita = -1;
      nova.baixo = -1;
      nova.tamBaixo = -1;
      if(tab[i][j]==0){
        nova.direita = direita(tab, i, j, x, y);
        nova.tamDireita = tamDireita(tab, i, j, x, y,nova.direita);
        nova.baixo = baixo(tab, i, j, x, y);
        nova.tamBaixo = tamBaixo(tab, i, j, x, y, nova.baixo);
      }
      nova.marcado = 0;
      tabProcessado[i][j] = nova;
    }
  }
  /*Parte que testa se existem palavras suficiente para todos os espaços que precisam ser preenchidos*/
  int a, b;
  int preProcesso = 1;
  for (a = 0; a<x && preProcesso; a++){
    for(b = 0; b<y && preProcesso; b++){
      if(tabProcessado[a][b].direita == 1){
        int cont1 = 0;
        int ok1 = 0;
        while(!ok1 && cont1<n){
          if(tamPalavras[cont1] == tabProcessado[a][b].tamDireita && dispoPalavras[cont1] == 0){
            dispoPalavras[cont1] = 1;
            ok1 = 1;
          }
          cont1++;
        }
        if(cont1 == n && ok1 == 0) preProcesso = 0;
      }
      if(tabProcessado[a][b].baixo == 1){
        int cont2 = 0;
        int ok2 = 0;
        while(!ok2 && cont2 < n){
          if(tamPalavras[cont2] == tabProcessado[a][b].tamBaixo && dispoPalavras[cont2] == 0){
            dispoPalavras[cont2] = 1;
            ok2 = 1;
          }
          cont2++;
        }
        if(cont2 == n && ok2 == 0) preProcesso = 0;
      }
    }
  }
  int indice;
  for(indice = 0;indice < n;indice++){
    dispoPalavras[indice] = 0;
  }
  /*Se passar no pre-processamento chama a função palavraCruzada, se não imprime que não há solução*/
  if(preProcesso==0) printf("nao ha solucao\n");
  else palavraCruzada(tab, tabProcessado, listaPalavras, tamPalavras, dispoPalavras, x, y, n);

  liberaMatrizInfo (tabProcessado, x);
  return;
}


/*---------------- ENTRADA DE DADOS ------------------*/

/*Função principal: Entrada de dados*/
int main()
{
  int x, y, n, contador; 
  scanf("%d %d",&x, &y);
  contador=1;
  while(x!=0 && y!=0){
    int ** tab = alocaMatriz (x, y);
    int i, j;
    for (i = 0; i < x; i++){
      for (j = 0; j < y; j++){
        scanf("%d",&tab[i][j]);
      }
    }
    scanf("%d",&n);
    int k, d;
    char ** listaPalavras = malloc(n*sizeof(char *));
    int * tamPalavras = malloc(n*sizeof(int));
    int * dispoPalavras = malloc(n*sizeof(int));
    for(k=0; k<n; k++){
      listaPalavras[k] = malloc((x+y)*sizeof(char));
      scanf ("%s", listaPalavras[k]);
      tamPalavras[k] = strlen(listaPalavras[k]);
      dispoPalavras[k] = 0;
    }

    printf("Instancia %d\n", contador);
    /*chamada Função de preprocessamento*/
    pre_processamento(tab, listaPalavras, tamPalavras, dispoPalavras, x, y, n);


    for(d=0; d<n; d++){
      free(listaPalavras[d]);
    }
    free(tamPalavras);
    free(listaPalavras);
    free(dispoPalavras);
    liberaMatriz(tab, x);
    printf("\n");
    scanf("%d %d",&x, &y);
    contador++;
  }  
  return 0;
} 
   
