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

// int numeroNosArvore(PtrNoArvore *tree){
// }
// int alturaArvore(PtrNoArvore *tree){
// }
//void EmOrdem(PtrNoArvore *tree){
  //}
// PtrArvore maximoIterativo(PtrNoArvore *tree){
// }
// PtrArvore minimo(PtrNoArvore *tree){
// }
// PtrArvore minimoIterativo(PtrNoArvore *tree){
//   }
// PtrArvore getMinAux(PtrNoArvore *tree){
// } //usado na remoção

int main(){
  // arvore na main
  PtrNoArvore raiz;
  iniciaArvore(&raiz);

  if(estaVazia(&raiz)) {
    printf("- Arvore está vazia!\n");
  } else {
    printf(" - Existe elemento dentro da árvore\n");
  }

  insereArvore(&raiz, 3);
  insereArvore(&raiz, 2);
  insereArvore(&raiz, 1);
  insereArvore(&raiz, 17);
  insereArvore(&raiz, 20);
  insereArvore(&raiz, -3);
  insereArvore(&raiz, 8);
  insereArvore(&raiz, 12);

  int vet[] = {3, 17, 12, -4};
  int i;
  for(i = 0; i < 4; i++) {
    if(procuraItem(&raiz, vet[i])){
      printf("Elemento %d existe\n", vet[i]);
    } else {
      printf("Elemento %d nao existe\n", vet[i]);
    }
  } // v v v f

  //            3
  //       2        17
  //    1       8      20
  //-3             12

//  Pre-ordem = {3, 2, 1, -3, 17, 8, 12, 20}
//  Pos-ordem = {-3, 1, 2, 12, 8, 20, 17, 3}
  // em-ordem = {-3, 1, 2, 3, 8, 12, 17, 20}

  printf("Pre-ordem ={");
  impressaoPreOrdem(&raiz);
  printf("}\n");

  printf("Pre-ordem ={");
  impressaoPosOrdem(&raiz);
  printf("}\n");

  removeItem(&raiz,-3);

//  // esta vazia!
//  if(estaVaziaArvore(&raiz)) {
//    printf("- Arvore está vazia!\n");
//  } else {
//    printf(" - Existe elemento dentro da árvore\n");
//  }

  return 0;
}
