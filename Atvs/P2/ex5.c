#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NoArvore *PtrNoArvore;

typedef struct NoArvore {
    int chave;
    PtrNoArvore filhoDireita;
    PtrNoArvore filhoEsquerda;
} NoArvore;

void iniciaArvore(PtrNoArvore *tree){
  *tree = NULL;
}

void impressaoPreOrdem(PtrNoArvore *tree){
  //imprime valor contido no nó da corrente
  if((*tree) == NULL) return;
  printf("%d ", (*tree)->chave);
  // recursiva para filho esquerda
  impressaoPreOrdem(&(*tree)->filhoEsquerda);
  // recursiva para filho direita
  impressaoPreOrdem(&(*tree)->filhoDireita);
}

void impressaoPosOrdem(PtrNoArvore *tree){
  if((*tree) == NULL) return;
  //recursiva filho esquerda
  impressaoPosOrdem(&(*tree)->filhoEsquerda);
  //recursiva filho direita
  impressaoPosOrdem(&(*tree)->filhoDireita);

  // imprime o valor contido no nó corrente
  printf("%d ", (*tree)->chave);
}

bool insereArvore(PtrNoArvore *tree, int x){
  //caso 1: encontrou o ponto de inserção
  if(*tree == NULL){

    //novo nó
    (*tree) = malloc(sizeof(NoArvore));

    // filho da direita e filho da esquerda = NULL
    (*tree)->filhoDireita  = NULL;
    (*tree)->filhoEsquerda = NULL;
    //atribuindo o valor do elemento
    (*tree)->chave = x;
    printf("Inserindo %d\n", x);
    return true;

  }

  //caso 2: nao inserir numeros repetidos
  if ((*tree)->chave == x) {
    return false;
  }

  //caso 3
  if((*tree)->chave > x) {
    // numero maior: recursao para filho da esquerda
    return(insereArvore(&(*tree)->filhoEsquerda, x));
  } else {
    // numero menor: recursao para filho da direita
    return(insereArvore(&(*tree)->filhoDireita, x));
  }

}

bool procuraItem(PtrNoArvore *tree, int x){
  // caso 1: nao achou o elemento/nao existe na arvore
  if(*tree == NULL) return (false);

  // caso 2: nó cujo valor é o procurado
  if((*tree)->chave == x) return (true);

  // recursao para percorrer a arvore
  if((*tree)->chave > x) {
    // numero maior: recursao para filho da esquerda
    return(procuraItem(&(*tree)->filhoEsquerda, x));
  } else {
    // numero menor: recursao para filho da direita
    return(procuraItem(&(*tree)->filhoDireita, x));
  }
}

bool estaVazia(PtrNoArvore *tree){
  return (*tree == NULL);
}

// PtrArvore maximo(PtrNoArvore *tree){
//
// }

PtrNoArvore getMaxAux(PtrNoArvore *node){
  PtrNoArvore ret;
  // criterio de parada da recursao:
  // se filho direita do node == NULL
  // eu achei o maior elemento
  if((*node)->filhoDireita == NULL) {
    ret = (*node);
    // ajuste para remocao funcionar
    // remover o elemento da sub-arvore de node
    (*node) = (*node)->filhoEsquerda;
    return(ret);
  }
  return(getMaxAux(&(*node)->filhoDireita));
} //usado na remoção

bool removeItem(PtrNoArvore *node, int x){

  // se node == NULL, nao tem quem remover
  if((*node) == NULL) {
    printf("Warning: elemento %d não existe na árvore\n", x);
    return(false);
  }

  // Achou quem quer remover
  if((*node)->chave == x) {

    //variavel para desalocar memoria
    PtrNoArvore tmp = (*node);

    // caso 1: sub-arvore esquerda do node é nula (direita nao)
    if((*node)->filhoEsquerda == NULL && (*node)->filhoDireita !=NULL) {
      (*node) = (*node)->filhoDireita;
    }

    // caso 2: sub-arvore direita do node é nula (esquerda nao)
    else if((*node)->filhoEsquerda != NULL && (*node)->filhoDireita == NULL) {
      (*node) = (*node)->filhoEsquerda;
    }
    // caso 3: no folha (direita como esquerda sao nulos)
    else if((*node)->filhoDireita == NULL && (*node)->filhoEsquerda == NULL) {
      (*node) = NULL;
    }
    // caso 4: direita e esquerda nao sao nulos
    else {

      tmp = getMaxAux(&(*node)->filhoEsquerda);
      (*node)->chave = tmp->chave;
    }

    printf("Elemento %d removido com sucesso\n", x);
    free(tmp);
    return(true);
  }

  // passos de recursao
  if((*node)->chave > x) {
    return (removeItem(&(*node)->filhoEsquerda, x));
  } else {
    return(removeItem(&(*node)->filhoDireita, x));
  }

}//removeitem

void destroiArvore(PtrNoArvore *node){
  //percorrer a arvore e desalocar memoria de tras p/ frente
  if ((*node)!=NULL){
    destroiArvore(&(*node)->filhoEsquerda);
    destroiArvore(&(*node)->filhoDireita);
    free(*node);
    (*node)=NULL;
  }
}

void EmOrdem(PtrNoArvore *node){
  if(*node == NULL) return;
  EmOrdem(&(*node)->filhoEsquerda);
  printf("%d, ", (*node)->chave);
  EmOrdem(&(*node)->filhoDireita);
}


void ordenaVetorTree(int n, int* array){
  PtrNoArvore raiz;

  // Caso nao haja nenhum elemento no vetor
  if (n==0) {
    printf("O vetor nao possui elementos\n");
  }

  //inicia arvore
  iniciaArvore(&raiz);

  //Insere os elementos do vetor na arvore
  for (int i = 0; i < n; i++) {
    insereArvore(&raiz,array[i]);
  }

  printf("\nElementos ordenados{ ");
    EmOrdem(&raiz);
  printf("}\n" );
}

int main(){
  int *vetor;
  int n=5;

  vetor = malloc (n * sizeof (int));

  vetor[0] = 4;
  vetor[1] = 1;
  vetor[2] = 234;
  vetor[3] = 0;
  vetor[4] = 42;

  ordenaVetorTree(n,vetor);

  return 0;
}
