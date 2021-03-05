/*
MAC0121 - Algoritmos e Estruturas de Dados
EP1 - Cifra de Cesar
Aluno: Daniel Silva Lopes da Costa
N°USP 11302720

O objetivo desse programa é receber o título de um documento em txt, ler esse arquivo e gerar uma criptografia simples do arquivo. Além disso o usário deve entrar também com duas chaves da a criptografia uma para as letras maiúsculas e outra para as minúsculas.

Desculpa não ter feito vários arquivos, ainda não me sinto muito seguro em relação a isso e quando o Professor explicou eu já tinha implementado esse modelo e deu certo. Nos proximos EPs isso não vai ocorre novamente :)

*/
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 1000

/*Função que aumenta o tamanho do vetor se necessário*/
char * realocaVetor(char *vet, int tam){
  char *v=malloc(2*tam*sizeof(char));
  int i;
  for(i=0;i<tam;i++){
    v[i]=vet[i];
  }
  free(vet);
  return(v);
}

/*Função que retura os caracteres especiais*/
char * tiraEspecial(char * texto, int tam, int * cont){
  char *nova=malloc(2*tam*sizeof(char));
  int contador=0;
  while(contador<tam){
    if(texto[contador]==','){
      nova[*cont]='v';
      nova[*cont+1]='r';
      *cont+=2;
    }else{
      if(texto[contador]=='.'){
        nova[*cont]='p';
        nova[*cont+1]='t';
        *cont+=2;
      }else{
        if(texto[contador]==':'){
          nova[*cont]='d';
          nova[*cont+1]='p';
          *cont+=2;
        }else{
          if(texto[contador]=='!'){
            nova[*cont]='e';
            nova[*cont+1]='x';
            *cont+=2;
          }else{
            if(texto[contador]=='?'){
              nova[*cont]='i';
              nova[*cont+1]='n';
              *cont+=2;
            }else{
              if(texto[contador]=='\n'){
                nova[*cont]='n';
                nova[*cont+1]='l';
                *cont+=2;
              }else{
                if(texto[contador]!=' '){
                  nova[*cont]=texto[contador];
                  *cont+=1;
                }
              }
            }
          }
        }
      }
    }
    contador++;
  }
  free(texto);
  return(nova);
}

/*Função que troca os caracteres, com base nas chaves*/
char * criptografa(char *nova, int d1, int d2, int tam, int * cont){
  char *cript=malloc(sizeof(char)*tam*2);
  int i;
  for(i=0;i<*cont;i++){
    if(nova[i]>='a'){
      if(nova[i]+d2<='z'){
        cript[i]=nova[i]+d2;
      }else{
        cript[i]=(nova[i]+d2)-('z'-'a'+1);
      }
    }else{
      if(nova[i]+d1<='Z'){
        cript[i]=nova[i]+d1;
      }else{
        cript[i]=(nova[i]+d1)-('Z'-'A'+1);
      }
    }
  }
  free(nova);
  return(cript);

}


int main() {
  char *texto=malloc(sizeof(char)*MAX);
  char name[MAX]; 
  int tam;

  /*Leitura do documento*/ 
  
  printf ("Digite o nome do arquivo que será criptografado: ");
  scanf ("%s", name);

  FILE * arq;
  arq = fopen (name, "r"); 
  if (arq == NULL) {
    printf ("Não encontrei o arquivo %s\n", name);
  }
  tam = 0;
  int tamanhoMax;
  tamanhoMax=MAX;
  while (!feof (arq)) {
    if(tam<tamanhoMax){
      fscanf (arq, "%c", &texto[tam]);
      tam++;
    }else{
      texto=realocaVetor(texto, tam);
      tamanhoMax=2*tamanhoMax;
    }
  }

  /* Criação dos vetores de ponteiro: Como os novos vetores terão no máximo o dobro do tamanho da anterior, na caso em que ele for formado apenas por caracteres especiais, eu não tenho que me preocupar mais em o arquivo não espaço reservado. */
  char *novoTexto=malloc(sizeof(char)*tam*2);
  char *textoCriptografado=malloc(sizeof(char)*tam*2);

  /*Entrada das chaves de criptografia */
  int d1,d2;
  printf ("Entre com a chave para letras maiuscula: ");
  scanf("%d",&d1);
  printf ("Entre com a chave para letras minuscula: ");
  scanf("%d",&d2);

  /*Mecanismo para evitar chave negativa*/
  if(d1<0 || d2<0){
    printf ("Chave com valor impróprio, negativo. Será considerado o módulo do valor.\n");
    if(d1<0) d1=-d1;
    if(d2<0) d2=-d2;
  }


  int t;
  t=0;
  int *cont=&t;

  /*Retirada dos espaços e pontuação*/
  novoTexto=tiraEspecial(texto, tam, cont); 
  
  /* Mecanismo para garantir a efetividade do uso da chave, para valores maiores que 26*/
  if(d1>26){
    d1=d1%26;
  }
  if(d2>26){
    d2=d2%26;
  }

  /*Alteração das letras, por meio das chaves*/ 
  textoCriptografado=criptografa(novoTexto,d1,d2,tam,cont);

  /*Impressão da mensagem criptografada*/
  int k;
  for(k=0;k<*cont;k++){
    printf("%c",textoCriptografado[k]);
  }
  printf("\n");

  free(textoCriptografado);
  return(0);
}