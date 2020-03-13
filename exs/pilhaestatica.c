#include "pilhaEstatica.h"

void iniciaPilha(pilhaEstatica *pilha) {
  pilha->topo = -1;
}

bool estaVazia(pilhaEstatica *pilha) {
  return (pilha->topo == -1);
}

bool estaCheia(pilhaEstatica *pilha) {
  return (pilha->topo == MAXTAM-1);
}

void empilha(Objeto item, pilhaEstatica *pilha) {
  pilha->topo ++;
  if(estaCheia(pilha)){
    printf("A pilha esta cheia\n");
    return;
  }
  pilha->array[pilha->topo] = item;
}

void desempilha(Objeto *item, pilhaEstatica *pilha) {
  *item = pilha->array[pilha->topo];
  pilha->topo --;
}

int tamanhoPilha(pilhaEstatica *pilha) {
  return (pilha->topo+1);
}

Objeto topo(pilhaEstatica *pilha) {
  return(pilha->array[pilha->topo]);
}

void imprimePilha(pilhaEstatica *pilha) {
  for (int i=0; i <= pilha->topo ; i++) {
    printf("%i  ", pilha->array[i].chave);
  }
}

int main(){
  pilhaEstatica pilha;
  iniciaPilha(&pilha);
  Objeto ob;

  srand(time(NULL));

  for(int i=0; i<10; i++){
    ob.chave = rand()%20;
    empilha(ob, &pilha);
  }

  imprimePilha(&pilha);
  printf("\nTamanho da pilha: %i\n",tamanhoPilha(&pilha));

  desempilha(ob,)
  return 0;
}
