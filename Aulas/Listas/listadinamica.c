#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Lista Single-linkage

typedef struct NoLista* PtrNoLista;

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
    return(lista->tamanho==0);
}

int tamanhoLista(Lista *lista){
    return(lista->tamanho);
}

void inserir(Lista *lista, int x){

    //criaçao e alocação do ponteiro novo
    PtrNoLista novo;
    novo = (PtrNoLista)malloc(sizeof( NoLista));
    novo->chave = x;

  //situação 1: se a lista vazia ou
  //o elemento que queremos inserir é menor que o primeiro
  if(estaVazia(lista) || x < lista->primeiro->chave){
    novo->proximo = lista->primeiro;
    lista->primeiro = novo;

  //situação 2: aux percorre a lista para encontrar o ponto de inserção
  }else{
    PtrNoLista aux;
    aux = lista->primeiro;
    while (aux->proximo!=NULL && x > aux->proximo->chave) {
      aux = aux->proximo;
    }//while

    novo->proximo = aux->proximo;
    aux->proximo = novo;

  }//if else

  lista->tamanho ++;

}//void inserir

void imprimirLista(Lista *lista){
  printf("Lista = {");
  PtrNoLista percorre;

  for(percorre = lista->primeiro; percorre != NULL; percorre = percorre->proximo) {
      printf("%d ", percorre->chave);
    }

  printf("}\n");

}

 bool pesquisar(Lista *lista, int key){
   if(estaVazia(lista)){
     return false;
   }

   PtrNoLista percorre = lista->primeiro;
   while(percorre != NULL && key > percorre->chave) {
     percorre = percorre->proximo;
   }

   printf("CONSULTA: %d\n", percorre->chave);
   if(percorre == NULL || percorre->chave > key) {
     return false;
   }

   // 3
   return true;
}

bool removeElemento(Lista *lista, int x){
  PtrNoLista aux;
  PtrNoLista anterior = NULL;

  if(estaVazia(lista) || x < lista->primeiro->chave){
    return false;
  }else{
      aux = lista->primeiro;
      while (aux!=NULL && x != aux->chave) {
        anterior = aux;
        aux = aux->proximo;
      }
      if (anterior==NULL){
        lista->primeiro=aux->proximo;
      }else{
      anterior->proximo = aux->proximo;
      }

    lista->tamanho--;
    return true;
    free(aux);
  }
  return false;
}

int main() {
  Lista lista;
  iniciaLista(&lista);

  inserir(&lista, 555);
  inserir(&lista, 0);
  inserir(&lista, 20);
  inserir(&lista, 7000);


  imprimirLista(&lista);
  printf("Tamanho = %d\n", tamanhoLista(&lista));



  if(pesquisar(&lista, 20)) {
     printf("Esta na lista \n");
  } else {
     printf("Try again\n");
  }

  removeElemento(&lista,555);
  imprimirLista(&lista);

  return 0;
}
