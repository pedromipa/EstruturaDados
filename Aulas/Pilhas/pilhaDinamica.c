#include "pilhaDinamica.h"
#include <time.h>

void iniciaPilha(PilhaDinamica *p) {
  p->topo = NULL;
  p->tamanho = 0;
}

bool estaVazia(PilhaDinamica *p) {
  return (p->tamanho == 0);
}

int tamanhoPilha(PilhaDinamica *p) {
  return (p->tamanho);
}

void empilha(Objeto obj, PilhaDinamica *p) {
  PtrNoPilha aux;
  aux = (PtrNoPilha) malloc(sizeof(NoPilha));
  aux->obj = obj;
  aux->proximo = p->topo;
  p->topo = aux;
  p->tamanho ++;
}

void desempilha(PilhaDinamica *p, Objeto *obj){
  if(estaVazia(p)){
    printf("A pilha ja esta vazia");
  }
  PtrNoPilha aux;
  aux = p->topo;
  p->topo = aux->proximo;
  free(aux);
  p->tamanho --;
}

void imprimePilha(PilhaDinamica *p){

}

void topo(PilhaDinamica *p, Objeto *obj){

}

int main(){
  PilhaDinamica pilha;
  Objeto obj;
  srand(time(NULL));

  iniciaPilha(&pilha);

  for(int i=0; i<10; i++){
    obj.chave = rand()%100;
    empilha(obj, &pilha);
  }
   imprimePilha(&pilha);

   desempilha(&pilha, &obj);

  return 0;
}
