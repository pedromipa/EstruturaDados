#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
  int chave;
} Objeto;

typedef struct NoFila *PtrNoFila;

typedef struct NoFila{
  int x;
  Objeto obj;
  PtrNoFila proximo;
} NoFila;

typedef struct {
  PtrNoFila inicio;
  PtrNoFila fim;
  int tamanho;
} FilaDinamica;

// Iniciar a fila
void iniciaFila(FilaDinamica *fila){
  fila->inicio = NULL;
  fila->fim = NULL;
  fila->tamanho = 0;

}//void iniciaFila

int tamanhoFila(FilaDinamica *fila){
  return(fila->tamanho);
}//tamanhoFila

bool estaVazia(FilaDinamica *fila){
  return(fila->tamanho == 0);
}//estaVazia

// Inserção de elementos na fila
void enfileira(FilaDinamica *fila, int x){

  PtrNoFila aux;
  aux = (PtrNoFila)malloc(sizeof(NoFila));
  aux->x = x;

  if (estaVazia(fila)){
    fila->inicio = aux;
    fila->fim = aux;
    aux->proximo = NULL;

  }else{
    aux->proximo = NULL;
    fila->fim->proximo=aux;
    fila->fim = aux;
  }

  fila->tamanho++;
}//enfileira

void imprimeFila(FilaDinamica *fila){
  printf("Fila = [ ");
  PtrNoFila aux;

  for (aux = fila->inicio; aux!=NULL; aux = aux->proximo) {
    printf("%d ", aux->x);
  }

  printf("]\n");
}//imprimeFila

int desenfileira(FilaDinamica *fila){
  int temp = -999;
  PtrNoFila aux;

  if (!estaVazia(fila)){
    aux = fila->inicio;
    fila->inicio = fila->inicio->proximo;
    temp= aux->x;
    free(aux);
    fila->tamanho--;

  }else{
    printf("A fila esta vazia\n");
  }

  return(temp);
}//desenfileira

int inicioFila(FilaDinamica *fila){
  PtrNoFila aux;
  aux=fila->inicio;
  return(aux->x);
}//inicioFila


int fimFila(FilaDinamica *fila){
  PtrNoFila aux;
  aux=fila->fim;
  return(aux->x);
}//fimFila

void inverteFilas(FilaDinamica *F1, FilaDinamica *F2) {
  int eleF1, eleF2;
  eleF1 = tamanhoFila(F1);
  eleF2 = tamanhoFila(F2);

imprimeFila(F1);
imprimeFila(F2);
  //passando os elementos de uma fila para outra
  /* desenfileirar a fila 2 de acordo com o seu tamanho */
  for (int i = 0; i < eleF2; i++) {
    enfileira(F1, desenfileira(F2));
  }

  /* desenfileirar a fila 1 de acordo com o seu tamanho, sobrando os elementos da fila 2 nela */
  for (int i = 0; i < eleF1; i++) {
    enfileira(F2, desenfileira(F1));
  }

imprimeFila(F1);
imprimeFila(F2);

}

int main(){
  FilaDinamica F1;
  FilaDinamica F2;

  int y;

  iniciaFila(&F1);
  iniciaFila(&F2);

  enfileira(&F1, 10);
  enfileira(&F1, 20);
  enfileira(&F1, 30);

  enfileira(&F2, 1);
  enfileira(&F2, 2);
  enfileira(&F2, 3);
  enfileira(&F2, 4);

  imprimeFila(&F1);
  imprimeFila(&F2);

  inverteFilas(&F1,&F2);

  imprimeFila(&F1);
  imprimeFila(&F2);

  return 0;
}
