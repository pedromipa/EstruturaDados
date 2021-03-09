#include "pilhadinamica.h"

void iniciaPilha(PilhaDinamica *p) {
  p->topo = NULL;
  p->tamanho = 0;
}

int tamanhoPilha(PilhaDinamica *p) {
  return (p->tamanho);
}

bool estaVazia(PilhaDinamica *p) {
  return (p->tamanho == 0);
}

void empilha(PilhaDinamica *p, Objeto *obj) {
  // Primeiro passo
    // Nó de pilha aux
  PtrNoPilha aux;
  aux = (PtrNoPilha) malloc(sizeof(NoPilha));
  // Segundo passo
    // Aux recebe o conteúdo do topo
  aux->obj = *obj;
  // Terceiro passo
   // Aux aponta para o nó do topo atual
  aux->proximo = p->topo; //novo proximo
  // Quarto passo
   // Topo recebe o próximo nó do nó do atual topo
  p->topo = aux;
  //Quinto passo
  p->tamanho ++;
} // void empilha


int desempilha(PilhaDinamica *p, Objeto *obj){
  // Passo zero
  // Valor para retorno
  int valor = -99;

  if(!estaVazia(p)){
    // Primeiro passo
    PtrNoPilha aux;
    // Segundo passo
    aux = p->topo;
    // Terceiro Passo
    valor = aux->obj.chave;
    // Quarto passo
    p->topo = aux->proximo; //p->topo = p->topo->prox
    // Quinto passo
      // deslocar memória
    free(aux);
    // Sexto passo
      // decrementar a quantidade da pilha
    p->tamanho --;

  }else{
    printf("A pilha ja esta vazia");
  }// if else

  // Sétimo Passo
    // retornar o valor da pilha

  return(valor);

}// void desempilha


void imprimePilha(PilhaDinamica *p){
  PtrNoPilha ptr;

  printf("\nPilha: ");
  for (ptr = p->topo; ptr !=NULL; ptr = ptr->proximo) {
    printf("%d ", ptr->obj);
  }//for
  printf("\n");
}

/*
void topo(PilhaDinamica *p, Objeto *obj){

}
*/

int main(){
  PilhaDinamica pilha;
  Objeto obj;

  iniciaPilha(&pilha);

  imprimePilha(&pilha);
    printf("tamanho = %d\n", tamanhoPilha(&pilha));

  obj.chave = 10;
  empilha(&pilha, &obj);
    imprimePilha(&pilha);
    printf("Tamanho = %d\n", tamanhoPilha(&pilha));

  obj.chave = 4;
  empilha(&pilha, &obj);
    imprimePilha(&pilha);
    printf("Tamanho = %d\n", tamanhoPilha(&pilha));

  obj.chave = 300;
  empilha(&pilha, &obj);
    imprimePilha(&pilha);
    printf("Tamanho = %d\n", tamanhoPilha(&pilha));

  int x = desempilha(&pilha, &obj);
    printf("Valor removido = %d\n", x);
    imprimePilha(&pilha);
    printf("Tamanho = %d\n", tamanhoPilha(&pilha));

  x = desempilha(&pilha, &obj);
    printf("Valor removido = %d\n", x);
    imprimePilha(&pilha);
    printf("Tamanho = %d\n", tamanhoPilha(&pilha));

  return 0;
}
