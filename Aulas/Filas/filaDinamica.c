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
  printf("Fila = { ");
  PtrNoFila aux;

  for (aux = fila->inicio; aux!=NULL; aux = aux->proximo) {
    printf("%d ", aux->x);
  }

  printf("}\n");
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

int main(){
  FilaDinamica fila;
  Objeto x;
  int y;

  iniciaFila(&fila);
    imprimeFila(&fila);

  enfileira(&fila, 10);
  enfileira(&fila, 230);
  enfileira(&fila, 123);
  enfileira(&fila, 1);
  enfileira(&fila, 5);

  imprimeFila(&fila);

  y = desenfileira(&fila);
    imprimeFila(&fila);
  printf("Tamanho da fila: %d\n", tamanhoFila(&fila));

  enfileira(&fila, 34);
    imprimeFila(&fila);

  printf("Tamanho da fila: %d\n", tamanhoFila(&fila));

  printf("Objeto no inicio: %d\n", inicioFila(&fila));
  printf("Objeto no fim: %d\n", fimFila(&fila));

  return 0;
}
