#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAXTAM 5

typedef struct {
  int chave;
} Objeto;

typedef struct {
  Objeto array[MAXTAM];
  int tamanho;
  int inicio;
  int fim;
} FilaEstatica;

// Iniciar a fila
void iniciaFila(FilaEstatica *fila){
  fila->inicio = 0;
  fila->fim = -1;
  fila->tamanho = 0;

}//void iniciaFila

bool estaVazia(FilaEstatica *fila){
  return(fila->tamanho == 0);
}//estaVazia

bool estaCheia(FilaEstatica *fila){
  return(fila->tamanho == MAXTAM);
}//estaCheia

// Calcular posição seguindo o buffer circular
int incrementaIndice(int i){
  int novaPos;
  if (i == MAXTAM-1){
    novaPos = 0;
  }else{
    novaPos = i++;
  }

  return(novaPos);
}//incrementaIndice

// Inserção de elementos na fila
void enfileira(FilaEstatica *fila, Objeto *x){
  if (!estaCheia(fila)){
    // incrementar o fim
    fila->fim++;
    fila->fim = incrementaIndice(fila->fim);
    // novo elemento
    fila->array[fila->fim].chave = x;
    // incrementar a quantidade de elementos
    fila->tamanho++;

  }else{
    printf("A fila esta cheia.\n");
  }

}//enfileira

int tamanhoFila(FilaEstatica *fila){

}//tamanhoFila

void imprimeFila(FilaEstatica *fila){
  printf("Fila = { ");
  int n = fila->tamanho;

  for (int i = 0; i < n; i++) {
    int indice = (fila->inicio+i) %MAXTAM;
    printf("%d ", fila->array[indice]);
  }

  printf("}\n");
}//imprimeFila

int desenfileira(FilaEstatica *fila){
  int temp = -999;

  if (!estaVazia(fila)){
    temp = fila->array[fila->inicio].chave;

    fila->inicio = incrementaIndice(fila->inicio);

    fila->tamanho--;
  }else{
      printf("A fila ja esta vazia\n");
  }

  return(temp);
}//desenfileira

Objeto inicioFila(FilaEstatica *fila){

}//inicioFila

Objeto fimFila(FilaEstatica *fila){

}//fimFila

int main(){
  FilaEstatica fila;
  Objeto x;

  iniciaFila(&fila);
  imprimeFila(&fila);

  x.chave = 13;
  enfileira(&fila, &x);
  imprimeFila(&fila);

  return 0;
}
