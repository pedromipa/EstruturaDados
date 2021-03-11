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
  return((i+1)%MAXTAM);
}//incrementaIndice

// Inserção de elementos na fila
void enfileira(FilaEstatica *fila, int x){
  if (!estaCheia(fila)){
    // incrementar o fim
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
  return(fila->tamanho);
}//tamanhoFila

void imprimeFila(FilaEstatica *fila){
  printf("Fila = { ");
  int n = fila->tamanho;

  for (int i = 0; i < n; i++) {
    int indice = (fila->inicio+i) %MAXTAM;
    printf("%d ", fila->array[indice].chave);
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

int inicioFila(FilaEstatica *fila){
  return(fila->array[fila->inicio].chave);
}//inicioFila

int fimFila(FilaEstatica *fila){
  return(fila->array[fila->fim].chave);

}//fimFila

int main(){
  FilaEstatica fila;
  Objeto x;
  int y;

  iniciaFila(&fila);
    imprimeFila(&fila);

  printf("Tamanho da fila: %d\n", tamanhoFila(&fila));

  enfileira(&fila, 10);
  enfileira(&fila, 230);
  enfileira(&fila, 123);
  enfileira(&fila, 1);
  enfileira(&fila, 5);

  imprimeFila(&fila);

  y = desenfileira(&fila);
    imprimeFila(&fila);

  enfileira(&fila, 5);
    imprimeFila(&fila);

  printf("Objeto no inicio: %d\n", inicioFila(&fila));
  printf("Objeto no fim: %d\n", fimFila(&fila));
  printf("Tamanho da fila: %d\n", tamanhoFila(&fila));

  return 0;
}
