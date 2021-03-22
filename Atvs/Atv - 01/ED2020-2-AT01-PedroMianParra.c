// atv 01
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Estrutura para receber conteudo do arquivo
typedef struct {
  char tipoPilha;
  float numero;
}DadosArquivo;

typedef struct {
  int chave;
} Objeto;

#define MAXTAM 100

// Estrutura da Pilha Estatica
typedef struct {
  Objeto array[MAXTAM];
  int topo;
} PilhaEstatica;

// Estruturas da Pilha Dinamica
typedef struct NoPilha* PtrNoPilha;

typedef struct NoPilha {
  Objeto obj;
  PtrNoPilha proximo;
} NoPilha;

typedef struct {
  PtrNoPilha topo;
  int tamanho;
} PilhaDinamica;

// Funções de manipulação da Pilha Estática

void iniciaPilhaEstatica(PilhaEstatica *pilha) {
  pilha->topo = 0;
}

bool estaVaziaPilhaEstatica(PilhaEstatica *pilhaEstatica) {
  return (pilhaEstatica->topo == 0);
}

bool estaCheiaPilhaEstatica(PilhaEstatica *pilhaEstatica) {
  return (pilhaEstatica->topo == MAXTAM);
}

void empilhaEstatica(PilhaEstatica *pilhaEstatica, int num) {
  if(estaCheiaPilhaEstatica(pilhaEstatica)){
    printf("A pilha esta cheia\n");
    return;
  }
  pilhaEstatica->array[pilhaEstatica->topo].chave = num;
  pilhaEstatica->topo ++;
}

int desempilhaEstatica(PilhaEstatica *pilhaEstatica) {
  if(!estaVaziaPilhaEstatica(pilhaEstatica)){
    pilhaEstatica->topo --;
    return(pilhaEstatica->array[pilhaEstatica->topo].chave);
  }
  printf("A pilha ja esta vazia\n");
}

void imprimePilhaEstatica(PilhaEstatica *pilhaEstatica) {
  printf("Pilha { ");
  for (int i=0; i < pilhaEstatica->topo ; i++) {
    printf("%i,  ", pilhaEstatica->array[i]);
  }
  printf(" }\n");
}

// Funções de manipulação da Pilha Dinâmica

void iniciaPilhaDinamica(PilhaDinamica *pilhaDinamica) {
  pilhaDinamica->topo = NULL;
  pilhaDinamica->tamanho = 0;
}

int tamanhoPilhaDinamica(PilhaDinamica *pilhaDinamica) {
  return (pilhaDinamica->tamanho);
}

bool estaVaziaDinamica(PilhaDinamica *pilhaDinamica) {
  return (pilhaDinamica->tamanho == 0);
}

void empilhaDinamica(PilhaDinamica *pilhaDinamica, int num) {
  PtrNoPilha aux;
  aux = (PtrNoPilha) malloc(sizeof(NoPilha));
  aux->obj.chave = num;
  aux->proximo = pilhaDinamica->topo; //novo proximo
  pilhaDinamica->topo = aux;
  pilhaDinamica->tamanho ++;
} // void empilha


int desempilhaDinamica(PilhaDinamica *pilhaDinamica){
  int valor = -99;

  if(!estaVaziaDinamica(pilhaDinamica)){
    PtrNoPilha aux;
    aux = pilhaDinamica->topo;
    valor = aux->obj.chave;
    pilhaDinamica->topo = aux->proximo; //p->topo = p->topo->prox
    free(aux);
    pilhaDinamica->tamanho --;

  }else{
    printf("A pilha ja esta vazia");
  }// if else

  return(valor);

}// void desempilha


void imprimePilhaDinamica(PilhaDinamica *pilhaDinamica){
  PtrNoPilha ptr;

  printf("Pilha { ");
  for (ptr = pilhaDinamica->topo; ptr !=NULL; ptr = ptr->proximo) {
    printf("%d, ", ptr->obj);
  }//for
  printf(" }\n");
}

// Função para verificarmos se o numero é inteiro. Comparamos o tipo int com float
bool verificaInteiro(float numero){
  int aux;
  aux = numero;
  return(aux!=numero);
}

// Função para realizar a conversão de decimal para binário e gravar no arquivo de saida
void converte(int num, DadosArquivo *dados, FILE *saida){
  int resto;
  PilhaEstatica pilhaEstaticaConv;
  PilhaDinamica pilhaDinamicaConv;

  if (dados->tipoPilha == 'e') {
    iniciaPilhaEstatica(&pilhaEstaticaConv);
  }else{
    iniciaPilhaDinamica(&pilhaDinamicaConv);
  }

  //caso o numero seja zero, ja gravamos no arquivo de saida
  if (num == 0) {
    fprintf(saida, "%d\n", num);

  }else{ //caso o numero seja diferente de zero, realiza a conversão
    while (num>0) {
      resto = num%2;
      num = num/2;
      if (dados->tipoPilha == 'e') {
          empilhaEstatica(&pilhaEstaticaConv, resto);
      }else{
          empilhaDinamica(&pilhaDinamicaConv, resto);
      }//if else
    }//while

    if (dados->tipoPilha == 'e') {
      while (!estaVaziaPilhaEstatica(&pilhaEstaticaConv)) {
        fprintf(saida, "%d", desempilhaEstatica(&pilhaEstaticaConv));
      }//while
      fprintf(saida, "\n");
    }else{
      while (!estaVaziaDinamica(&pilhaDinamicaConv)) {
        fprintf(saida, "%d", desempilhaDinamica(&pilhaDinamicaConv));
      }//while
      fprintf(saida, "\n");
    }

  }//if else numero diferente de 0
}// void converte

// Função main
int main(int argc, char *argv[]){

  //chamada das structs
  Objeto obj;
  PilhaEstatica pilhaEstatica;
  PilhaDinamica pilhaDinamica;
  DadosArquivo dados;

  FILE 	*arqentrada = fopen(argv[1], "r");
  FILE 	*arqsaida = fopen(argv[2], "w");

  if(arqentrada == NULL){
    printf("Erro ao abrir o arquivo de entrada\n");
    exit(1);
  }

  if(arqsaida == NULL){
    printf("Erro ao abrir o arquivo de saida\n");
    exit(1);
  }

  //verificar tipo de pilha escolhida
  dados.tipoPilha = fgetc(arqentrada);
  //trabalhar com caracteres minusculos
  dados.tipoPilha = tolower(dados.tipoPilha);

  // Verificar tipo de pilha escolhida
  if (dados.tipoPilha == 'e') {
    iniciaPilhaEstatica(&pilhaEstatica);
    printf("Pilha Estatica escolhida\n");
  }else if(dados.tipoPilha == 'd'){
    iniciaPilhaDinamica(&pilhaDinamica);
    printf("Pilha Dinamica escolhida\n");

  }else{
    printf("Arquivo de entrada invalido!");
    fprintf(arqsaida, "Arquivo de entrada inválido!");
    exit(1);

  }

  while(!feof(arqentrada)){
    fscanf(arqentrada, "%f\n", &dados.numero);
    //Caso algum numero nao seja inteiro, encerramos o programa
    if (verificaInteiro(dados.numero)) {
      printf("Numero inválido!\n");
      fprintf(arqsaida,"Numero inválido!\n");
      exit(1);
    }else{
      //Empilha na pilha escolhida
      if (dados.tipoPilha == 'e') {
        empilhaEstatica(&pilhaEstatica, dados.numero);
      }else{
        empilhaDinamica(&pilhaDinamica, dados.numero);
      }//if else
    }

  }//while

  if (dados.tipoPilha == 'e') {
   imprimePilhaEstatica(&pilhaEstatica);
    while (!estaVaziaPilhaEstatica(&pilhaEstatica)) {
      converte(desempilhaEstatica(&pilhaEstatica), &dados, arqsaida);
    }//while
  }else{
    imprimePilhaDinamica(&pilhaDinamica);
    while (!estaVaziaDinamica(&pilhaDinamica)) {
      converte(desempilhaDinamica(&pilhaDinamica), &dados, arqsaida);
    }//while
  }

  fclose(arqentrada);
  fclose(arqsaida);
  return 0;
}//main
