#include "pilhaDinamica.h"

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
  PONT aux = (PONT) malloc(sizeof(obj));

}

int main(){
  return 0;
}
