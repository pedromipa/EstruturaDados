#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct  {
  int chave;
} Objeto;

typedef struct NoLista *PtrNoLista;

typedef struct NoLista {
    int chave;
    PtrNoLista proximo;
} NoLista;

typedef struct {
    PtrNoLista primeiro;
    int tamanho;
} Lista;

void iniciaLista(Lista *lista){
  lista->primeiro = NULL;
  lista->tamanho = 0;

}

bool estaVazia(Lista *lista){
    return(lista->tamanho=0);
}

int tamanhoLista(Lista *lista){
    return(lista->tamanho);
}

void inserir(Lista *lista, int x){
  if(estaVazia(lista)){
    PtrNoLista novo;
    //
    novo = (PtrNoLista)malloc(sizeof( NoLista));
    //
    novo->chave = x;
    //
    novo->proximo = NULL;
    //
    lista->primeiro = novo;
    //

  }else{
    PtrNoLista aux;

    aux = lista->primeiro
    while (aux->proximo!=NULL && elemento > aux->proximo->chave) {
      aux = aux->proximo;
    }
  }//if else

  lista->tamanho = lista->tamanho + 1;

}//void inserir

void imprimirLista(Lista *lista){
  printf("Lista = {");
  PtrNoLista percorre;

  for(percorre = lista->primeiro; percorre != NULL; percorre = percorre->proximo) {
      printf("%d ", percorre->chave);
    }

  printf("}\n");

}

void destruirLista(Lista *lista){

}


bool pesquisar(Lista *lista, int key){

}


void removeElemento(Lista *lista, int chave, Objeto *item){

}

void removePrimeiro(Lista *lista, Objeto *item){

}

void removeUltimo(Lista *lista, Objeto *item){

}

Objeto primeiro(Lista *lista){

}

Objeto ultimo(Lista *lista){

}

int main() {
  Lista lista;
  iniciaLista(&lista);

  return 0;
}
