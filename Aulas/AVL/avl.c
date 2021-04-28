#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NoArvoreAVL *PointeiroArvoreAVL;

typedef struct NoArvoreAVL {
    int chave;
    PointeiroArvoreAVL direita;
    PointeiroArvoreAVL esquerda;
    int altura; //fator de balanceamento
} NodeNoArvoreAVLTree;

// =====================

void iniciaArvoreAVL(PointeiroArvoreAVL *node){
  *node = NULL;
}

bool estaVaziaArvoreAVL(PointeiroArvoreAVL *node){
  return((*node) == NULL);
}

void preOrdem(PointeiroArvoreAVL *node){
  if((*node) == NULL) return;
  printf("%d ", (*node)->chave);
  preOrdem(&(*node)->esquerda);
  preOrdem(&(*node)->direita);
}

void posOrdem(PointeiroArvoreAVL *node){
  if((*node) == NULL) return;
  preOrdem(&(*node)->esquerda);
  preOrdem(&(*node)->direita);
  printf("%d ", (*node)->chave);
}

void emOrdem(PointeiroArvoreAVL *node){
  if((*node) == NULL) return;
  emOrdem(&(*node)->esquerda);
  printf("%d ", (*node)->chave);
  emOrdem(&(*node)->direita);
}

int alturaArvoreAVL(PointeiroArvoreAVL *node){
  if(node == NULL) {
    return (0);
  } else {
    return ((node)->altura);
  }
}

int atualizaAlturaArvoreAVL(PointeiroArvoreAVL esquerda, PointeiroArvoreAVL direita){
  int ae = alturaArvoreAVL(esquerda);
  int ad = alturaArvoreAVL(direita);

  if(ae > ad) {
    return(ae + 1);
  } else {
    return(ad + 1);
  }
}

bool pesquisaArvoreAVL(PointeiroArvoreAVL *node, int key){
  if(*node == NULL ) {
    printf(" @ Elemento consultado: %d, não existe na arvore\n", key);
    return false;
  }
  if((*node)->chave == key){
    printf(" @ Elemento consultado: %d, existe na arvore\n", key);
    return true;
  }
  if((*node)->chave > key )
    return (pesquisaArvoreAVL( &(*node)->esquerda, key));
  else
    return (pesquisaArvoreAVL( &(*node)->direita, key));
}

void destruirArvoreAVL(PointeiroArvoreAVL *node){
  if((*node) != NULL ) {
    destruirArvoreAVL( &(*node)->esquerda);
    destruirArvoreAVL( &(*node)->direita);
    free(*node);
    *node = NULL;
}

void rotacaoSimplesEsquerda(PointeiroArvoreAVL *node){
  printf("Rotação simples p esquerda, com node: %d\n", (*node)->chave);

  PtrNoAVL u = (*node)->direita;
  (*node)->direita = u->esquerda;
  u->esquerda = (*node);

  //atualizar a altura dos nós modificados (node, u)
  (*node)->altura = atualizaAltura((*node)->esquerda, (*node)->direita);
  u->altura = atualizaAltura(u->esquerda, u->direita);

  //autualizacao da referencia do node
  (*node) = u;
}

void rotacaoSimplesDireita(PointeiroArvoreAVL *node){
  printf("Rotação simples p direita, com node: %d\n", (*node)->chave);

  PtrNoAVL u = (*node)->esquerda;
  (*node)->esquerda = u->direita;
  u->direita = (*node);

  //atualizar a altura dos nós modificados (node, u)
  (*node)->altura = atualizaAltura((*node)->esquerda, (*node)->direita);
  u->altura = atualizaAltura(u->esquerda, u->direita);

  //autualizacao da referencia do node
  (*node) = u;
}

void rotacaoDuplaEsquerda(PointeiroArvoreAVL *node){
  printf("Rotação dupla p esquerda, com node: %d\n", (*node)->chave);

  PtrNoAVL u, v;
  u = (*node)->direita;
  v = u->esquerda;

  (*node)->direita = v->esquerda;
  u->esquerda = v->direita;
  v->esquerda = (*node);
  v->direita = u;

  //atualizar a altura dos nós modificados (node, u, v)
  (*node)->altura = atualizaAltura((*node)->esquerda, (*node)->direita);
  u->altura = atualizaAltura(u->esquerda, u->direita);
  v->altura = atualizaAltura(v->esquerda, v->direita);

  //autualizacao da referencia do node
  (*node) = v;
}

void rotacaoDuplaDireita(PointeiroArvoreAVL *node){
  printf("Rotação dupla p direita, com node: %d\n", (*node)->chave);

  PtrNoAVL u, v;
  u = (*node)->esquerda;
  v = u->direita;

  (*node)->esquerda = v->direita;
  u->direita = v->esquerda;

  v->direita = (*node);
  v->esquerda = u;

  //atualizar a altura dos nós modificados (node, u, v)
  (*node)->altura = atualizaAltura((*node)->esquerda, (*node)->direita);
  u->altura = atualizaAltura(u->esquerda, u->direita);
  v->altura = atualizaAltura(v->esquerda, v->direita);

  //autualizacao da referencia do node
  (*node) = v;
}

void AplicarRotacoes(PointeiroArvoreAVL *node){
  int ad = alturaArvoreAVL((*node)->direita);
  int ae = alturaArvoreAVL((*node)->esquerda);

  // Verificar se é rotacao para direita
  if(ae > ad) {
    PtrNoAVL temp = (*node)->esquerda;
    int temp_ad = alturaArvoreAVL(temp->direita);
    int temp_ae = alturaArvoreAVL(temp->esquerda);
    // temp_ae > ou >= temp_ad
    if(temp_ae > temp_ad) {
      rotacaoSimplesDireita(&(*node));
    } else {
      rotacaoDuplaDireita(&(*node));
    }
  }
  // Senao é rotacao para esquerda
  else { //(ad > ae)
    PtrNoAVL tmp2 = (*node)->direita;
    int tmp2_ad = alturaArvoreAVL(tmp2->direita);
    int tmp2_ae = alturaArvoreAVL(tmp2->esquerda);

    if(tmp2_ad > tmp2_ae){
      rotacaoSimplesEsquerda(&(*node));
    } else {
      rotacaoDuplaEsquerda(&(*node));
    }
  }
}

bool inserirArvoreAVL(PointeiroArvoreAVL *node, int x){
  //1. condicao final da recursao (positiva)
  if((*node) == NULL) {
    (*node) = (PtrNoAVL)malloc(sizeof(NoAVL));
    (*node)->direita = (*node)->esquerda = NULL;
    (*node)->chave = x;
    (*node)->altura = 1;
    return true;
  }

  //2. elemento ja existe
  if((*node)->chave == x) return false;

  bool auxiliar;

  // 3. Laço de chamadas recusivas
  if(x < (*node)->chave) {
    auxiliar = InserirAVL(&(*node)->esquerda, x);
  } else {
    auxiliar = InserirAVL(&(*node)->direita, x);
  }

  // Daqui para baixo começa o codigo só tem na AVL
  // 4. Se o auxiliar for falso, nao houve mudança na arvore
  if(!auxiliar) return (false);

  // Se houve modificacao na arvore
  // Precisamos checar o desbalanceamento
  int ae; // altura da sub-arvore da esquerda
  int ad; // altura da sub-arvore da direita

  // 5. Calculando as alturas das sub-arvores
  ae = alturaArvoreAVL((*node)->esq);
  ad = alturaArvoreAVL((*node)->dir);

  // 6. Verificando desbalanceamento
  if((ad - ae) == +2 || (ad - ae) == -2) {
    // desbalancemaneto
    AplicarRotacoes(&(*node));
  }

  //7. ajuste da altura do no corrente
  (*node)->altura = atualizaAltura((*node)->esquerda, (*node)->direita);
  return(true);
}

void imprimeArvoreAVLNivel(PointeiroArvoreAVL *node){

    DynamicQueue queue;
    initQueue(&queue);

    int level = 1;
    int previous;
    int lft, rgt;
    PointerNodeTree node;

    enqueue((*root), &queue, level);

    printf("\n------------\nTree:\n");
    while(!isEmpty(&queue)) {
      previous = level;
      node = dequeue(&queue, &level);
      if(previous != level)
        printf("\n");

      if(node->right != NULL) {
        rgt = node->right->height;
      } else {
        rgt = 0;
      }

      if(node->left != NULL) {
        lft = node->left->height;
      } else {
        lft = 0;
      }

      printf("%d(%d),", node->element.key, (rgt - lft));

      if(node->left != NULL)
        enqueue(node->left, &queue, level+1);
      if(node->right != NULL)
        enqueue(node->right, &queue, level+1);
    }
    printf("\n------------\n");
}

PointerNodeTree getMaxAux (PointerNodeTree *node) {
  PointerNodeTree ret;
  if((*node)->right == NULL) {
    ret = (*node);
    (*node) = (*node)->left; //
    return(ret);
  }
  return(getMaxAux(&(*node)->right));
}

bool removeAVL(PointerNodeTree *node, int key) {

  bool test;
  int h_left, h_right;

  if((*node) == NULL) {
    printf("Não existe o elemento %d para ser removido!\n", key);
    return (false);
  }

  // encontrei o que remover ...
  if((*node)->element.key == key) {

    PointerNodeTree tmp = (*node);
    // case 1: sub-arvore esquerda é nula (cai aqui se for folha também)
    if((*node)->left == NULL) {
      (*node) = (*node)->right;
    }
    // case 2: sub-arvore direita é nula (poderia cair aqui tb no caso de folha)
    else if((*node)->right == NULL) {
      (*node) = (*node)->left;
    } else {
      // case 3: ambas subarvores existem: pegar o maior elemento da sub-arvore da esquerda
      tmp = getMaxAux(&(*node)->left);
//    tmp = getMinAux(&(*node)->right);
      (*node)->element = tmp->element;
    }
    free(tmp);
    return true;
  }

  if((*node)->element.key > key){
    test = removeAVL(&(*node)->left, key);
  } else {
    test = removeAVL(&(*node)->right, key);
  }

  if(test == false) return (false);
  else {
    h_left  = depthAVLTree(&(*node)->left);
    h_right = depthAVLTree(&(*node)->right);

    if( abs(h_left - h_right) == 2 )
      applyRotations(&(*node));

    (*node)->height = updateHeight((*node)->left, (*node)->right);
    return(true);
  }
}
