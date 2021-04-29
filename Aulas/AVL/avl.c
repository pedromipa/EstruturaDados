#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NoArvoreAVL *PointeiroArvoreAVL;

typedef struct NoArvoreAVL {
    int chave;
    PointeiroArvoreAVL direita;
    PointeiroArvoreAVL esquerda;
    int altura; //fator de balanceamento
} NoArvoreAVL;

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

int profundidadeAVL(PointeiroArvoreAVL *node) {
  if ((*node) == NULL) return 0;
  else {
    int profEsquerda = profundidadeAVL(&(*node)->esquerda);
    int profDireita = profundidadeAVL(&(*node)->direita);
    if (profEsquerda > profDireita)
      return(profEsquerda+1);
    else return(profDireita+1);
  }
}

int alturaArvoreAVL(PointeiroArvoreAVL node){
  if(node == NULL) {
    return (0);
  } else {
    return ((node)->altura);
  }
}

int atualizaAlturaAVL(PointeiroArvoreAVL esquerda, PointeiroArvoreAVL direita){
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

/*
void destruirArvoreAVL(PointeiroArvoreAVL *node){
  if((*node) != NULL ) {
    destruirArvoreAVL( &(*node)->esquerda);
    destruirArvoreAVL( &(*node)->direita);
    free(*node);
    *node = NULL;
}
*/
void rotacaoSimplesEsquerda(PointeiroArvoreAVL *node){
  printf("Rotação simples p esquerda, com node: %d\n", (*node)->chave);

  PointeiroArvoreAVL u = (*node)->direita;
  (*node)->direita = u->esquerda;
  u->esquerda = (*node);

  //atualizar a altura dos nós modificados (node, u)
  (*node)->altura = atualizaAlturaAVL((*node)->esquerda, (*node)->direita);
  u->altura = atualizaAlturaAVL(u->esquerda, u->direita);

  //autualizacao da referencia do node
  (*node) = u;
}

void rotacaoSimplesDireita(PointeiroArvoreAVL *node){
  printf("Rotação simples p direita, com node: %d\n", (*node)->chave);

  PointeiroArvoreAVL u = (*node)->esquerda;
  (*node)->esquerda = u->direita;
  u->direita = (*node);

  //atualizar a altura dos nós modificados (node, u)
  (*node)->altura = atualizaAlturaAVL((*node)->esquerda, (*node)->direita);
  u->altura = atualizaAlturaAVL(u->esquerda, u->direita);

  //autualizacao da referencia do node
  (*node) = u;
}

void rotacaoDuplaEsquerda(PointeiroArvoreAVL *node){
  printf("Rotação dupla p esquerda, com node: %d\n", (*node)->chave);

  PointeiroArvoreAVL u, v;
  u = (*node)->direita;
  v = u->esquerda;

  (*node)->direita = v->esquerda;
  u->esquerda = v->direita;
  v->esquerda = (*node);
  v->direita = u;

  //atualizar a altura dos nós modificados (node, u, v)
  (*node)->altura = atualizaAlturaAVL((*node)->esquerda, (*node)->direita);
  u->altura = atualizaAlturaAVL(u->esquerda, u->direita);
  v->altura = atualizaAlturaAVL(v->esquerda, v->direita);

  //autualizacao da referencia do node
  (*node) = v;
}

void rotacaoDuplaDireita(PointeiroArvoreAVL *node){
  printf("Rotação dupla p direita, com node: %d\n", (*node)->chave);

  PointeiroArvoreAVL u, v;
  u = (*node)->esquerda;
  v = u->direita;

  (*node)->esquerda = v->direita;
  u->direita = v->esquerda;

  v->direita = (*node);
  v->esquerda = u;

  //atualizar a altura dos nós modificados (node, u, v)
  (*node)->altura = atualizaAlturaAVL((*node)->esquerda, (*node)->direita);
  u->altura = atualizaAlturaAVL(u->esquerda, u->direita);
  v->altura = atualizaAlturaAVL(v->esquerda, v->direita);

  //autualizacao da referencia do node
  (*node) = v;
}

void AplicarRotacoes(PointeiroArvoreAVL *node){
  int ad = alturaArvoreAVL((*node)->direita);
  int ae = alturaArvoreAVL((*node)->esquerda);

  // Verificar se é rotacao para direita
  if(ae > ad) {
    PointeiroArvoreAVL temp = (*node)->esquerda;
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
    PointeiroArvoreAVL tmp2 = (*node)->direita;
    int tmp2_ad = alturaArvoreAVL(tmp2->direita);
    int tmp2_ae = alturaArvoreAVL(tmp2->esquerda);

    if(tmp2_ad > tmp2_ae){
      rotacaoSimplesEsquerda(&(*node));
    } else {
      rotacaoDuplaEsquerda(&(*node));
    }
  }
}

bool inserirAVL(PointeiroArvoreAVL *node, int x){
  //1. condicao final da recursao (positiva)
  if((*node) == NULL) {
    (*node) = (PointeiroArvoreAVL)malloc(sizeof(NoArvoreAVL));
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
    auxiliar = inserirAVL(&(*node)->esquerda, x);
  } else {
    auxiliar = inserirAVL(&(*node)->direita, x);
  }

  // Daqui para baixo começa o codigo só tem na AVL
  // 4. Se o auxiliar for falso, nao houve mudança na arvore
  if(!auxiliar) return (false);

  // Se houve modificacao na arvore
  // Precisamos checar o desbalanceamento
  int ae; // altura da sub-arvore da esquerda
  int ad; // altura da sub-arvore da direita

  // 5. Calculando as alturas das sub-arvores
  ae = alturaArvoreAVL((*node)->esquerda);
  ad = alturaArvoreAVL((*node)->direita);

  // 6. Verificando desbalanceamento
  if((ad - ae) == +2 || (ad - ae) == -2) {
    // desbalancemaneto
    AplicarRotacoes(&(*node));
  }

  //7. ajuste da altura do no corrente
  (*node)->altura = atualizaAlturaAVL((*node)->esquerda, (*node)->direita);
  return(true);
}

/*
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

      if(node->direita != NULL) {
        rgt = node->direita->height;
      } else {
        rgt = 0;
      }

      if(node->esquerda != NULL) {
        lft = node->esquerda->height;
      } else {
        lft = 0;
      }

      printf("%d(%d),", node->chave, (rgt - lft));

      if(node->esquerda != NULL)
        enqueue(node->esquerda, &queue, level+1);
      if(node->direita != NULL)
        enqueue(node->direita, &queue, level+1);
    }
    printf("\n------------\n");
}
*/

PointeiroArvoreAVL maxAVL (PointeiroArvoreAVL *node) {
  PointeiroArvoreAVL aux;
  if((*node)->direita == NULL) {
    aux = (*node);
    (*node) = (*node)->esquerda;
    return(aux);
  }
  return(maxAVL(&(*node)->direita));
}

bool removeAVL(PointeiroArvoreAVL *node, int key) {

  bool teste;
  int h_esquerda, h_direita;

  if((*node) == NULL) {
    printf("Não existe o elemento %d para ser removido!\n", key);
    return (false);
  }

  // encontrei o que remover ...
  if((*node)->chave == key) {

    PointeiroArvoreAVL tmp = (*node);
    // case 1: sub-arvore esquerda é nula (cai aqui se for folha também)
    if((*node)->esquerda == NULL) {
      (*node) = (*node)->direita;
    }
    // case 2: sub-arvore direita é nula (poderia cair aqui tb no caso de folha)
    else if((*node)->direita == NULL) {
      (*node) = (*node)->esquerda;
    } else {
      // case 3: ambas subarvores existem: pegar o maior elemento da sub-arvore da esquerda
      tmp = maxAVL(&(*node)->esquerda);
//    tmp = getMinAux(&(*node)->direita);
      (*node)->chave = tmp->chave;
    }
    free(tmp);
    return true;
  }

  if((*node)->chave > key){
    teste = removeAVL(&(*node)->esquerda, key);
  } else {
    teste = removeAVL(&(*node)->direita, key);
  }

  if(teste == false) return (false);
  else {
    h_esquerda  = profundidadeAVL(&(*node)->esquerda);
    h_direita = profundidadeAVL(&(*node)->direita);

    if( abs(h_esquerda - h_direita) == 2 )
      AplicarRotacoes(&(*node));

    (*node)->altura = atualizaAlturaAVL((*node)->esquerda, (*node)->direita);
    return(true);
  }
}

int main(){
  PointeiroArvoreAVL raiz;

  iniciaArvoreAVL(&raiz);

  inserirAVL(&raiz, 823);
  inserirAVL(&raiz, 81);
  inserirAVL(&raiz, 82);

  preOrdem(&raiz);

  //destruirArvoreAVL(&raiz);
  return 0;
}
