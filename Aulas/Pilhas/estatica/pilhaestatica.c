#include "pilhaestatica.h"

void iniciaPilha(pilhaEstatica *pilha) {
  pilha->topo = 0;
}

bool estaVazia(pilhaEstatica *pilha) {
  return (pilha->topo == 0);
}

bool estaCheia(pilhaEstatica *pilha) {
  return (pilha->topo == MAXTAM);
}

void empilha(Objeto item, pilhaEstatica *pilha) {
  if(estaCheia(pilha)){
    printf("A pilha esta cheia\n");
    return;
  }
  pilha->array[pilha->topo] = item;
  pilha->topo ++;
}

void desempilha(Objeto *item, pilhaEstatica *pilha) {
  if(estaVazia(pilha)){
    printf("A pilha ja esta vazia\n");
    return;
  }
  pilha->topo --;
  *item = pilha->array[pilha->topo];
}

int tamanhoPilha(pilhaEstatica *pilha) {
  return (pilha->topo);
}

Objeto topo(pilhaEstatica *pilha) {
  return(pilha->array[pilha->topo]);
}

void imprimePilha(pilhaEstatica *pilha) {
  for (int i=0; i < pilha->topo ; i++) {
    printf("%i  ", pilha->array[i]);
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
  printf("Valor no topo: %i\n",pilha.array[pilha.topo-1]);

  desempilha(&ob, &pilha);

  imprimePilha(&pilha);
  printf("\nTamanho da pilha: %i\n",tamanhoPilha(&pilha));
  printf("Valor no topo: %i\n",pilha.array[pilha.topo-1]);

  return 0;
}
