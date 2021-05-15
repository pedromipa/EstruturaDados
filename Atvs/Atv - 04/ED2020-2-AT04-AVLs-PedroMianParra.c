#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

// Estruturas da Arvore AVL

typedef struct NoArvoreAVL *PointeiroArvoreAVL;

typedef struct NoArvoreAVL {
    int chave;
    PointeiroArvoreAVL direita;
    PointeiroArvoreAVL esquerda;
    int altura; //fator de balanceamento
} NoArvoreAVL;

// Estruturas da fila dinamica

typedef struct NoFila *PtrNoFila;

typedef struct NoFila{
  int chave;
  PtrNoFila proximo;
} NoFila;

typedef struct {
  PtrNoFila inicio;
  PtrNoFila fim;
  int tamanho;
} FilaDinamica;

// -----------------------------------------------

// Funções da Fila Dinamica

void iniciaFila(FilaDinamica *fila){
  fila->inicio = NULL;
  fila->fim = NULL;
  fila->tamanho = 0;

}//void iniciaFila

int tamanhoFila(FilaDinamica *fila){
  return(fila->tamanho);
}//tamanhoFila

bool estaVaziaFila(FilaDinamica *fila){
  return(fila->tamanho == 0);
}//estaVazia

// Inserção de elementos na fila
void enfileira(FilaDinamica *fila, int x){

  PtrNoFila aux;
  aux = (PtrNoFila)malloc(sizeof(NoFila));
  aux->chave = x;

  if (estaVaziaFila(fila)){
    fila->inicio = aux;
    fila->fim = aux;
    aux->proximo = NULL;

  }else{
    aux->proximo = NULL;
    fila->fim->proximo = aux;
    fila->fim = aux;
  }

  fila->tamanho++;
}//enfileira

int desenfileira(FilaDinamica *fila){
  int temp = -999;
  PtrNoFila aux;

  if (!estaVaziaFila(fila)){
    aux = fila->inicio;
    fila->inicio = fila->inicio->proximo;
    temp= aux->chave;
    free(aux);
    fila->tamanho--;

  }else{
    printf("A fila esta vazia\n");
  }

  return(temp);
}//desenfileira

// -----------------------------------------------
// Funções da Arvore AVL

void iniciaArvoreAVL(PointeiroArvoreAVL *node){
  *node = NULL;
}

bool estaVaziaArvoreAVL(PointeiroArvoreAVL *node){
  return((*node) == NULL);
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

void destruirArvoreAVL(PointeiroArvoreAVL *node){
  if((*node) != NULL ) {
    destruirArvoreAVL( &(*node)->esquerda);
    destruirArvoreAVL( &(*node)->direita);
    free(*node);
    *node = NULL;
  }
}

void rotacaoSimplesEsquerda(PointeiroArvoreAVL *node){

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
    if(temp_ae > temp_ad) {
      rotacaoSimplesDireita(&(*node));
    } else {
      rotacaoDuplaDireita(&(*node));
    }
  }

  else { //(ad > ae) rotacao para esquerda
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
  //condicao final da recursao (positiva)
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

  // Se o auxiliar for falso, nao houve mudança na arvore
  if(!auxiliar) return (false);

  // checar desbalanceamento
  int ae;
  int ad;
  ae = alturaArvoreAVL((*node)->esquerda);
  ad = alturaArvoreAVL((*node)->direita);

  if((ad - ae) == +2 || (ad - ae) == -2) {
    AplicarRotacoes(&(*node));
  }

  // ajuste da altura do no corrente
  (*node)->altura = atualizaAlturaAVL((*node)->esquerda, (*node)->direita);
  return(true);
}

// Funções utilizadas na remoção conforme escolha do usuario

PointeiroArvoreAVL maxAVL (PointeiroArvoreAVL *node) {
  PointeiroArvoreAVL aux;
  if((*node)->direita == NULL) {
    aux = (*node);
    (*node) = (*node)->esquerda;
    return(aux);
  }
  return(maxAVL(&(*node)->direita));
}

PointeiroArvoreAVL minAVL (PointeiroArvoreAVL *node) {
  PointeiroArvoreAVL ret;
  if((*node)->esquerda == NULL) {
    ret = (*node);
    (*node) = (*node)->direita;
    return(ret);
  }
  return(minAVL(&(*node)->esquerda));
}

bool removeAVL(PointeiroArvoreAVL *node, int key, char opcao) {

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
        if (opcao == 'e') {
          tmp = maxAVL(&(*node)->esquerda);
        }else{
          tmp = minAVL(&(*node)->direita);
        }

      (*node)->chave = tmp->chave;
    }
    free(tmp);
    return true;
  }

  if((*node)->chave > key){
    teste = removeAVL(&(*node)->esquerda, key,opcao);
  } else {
    teste = removeAVL(&(*node)->direita, key,opcao);
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

void printAVL(PointeiroArvoreAVL *node, int level, FILE* arqsaida){
  if ((*node)!=NULL && level == 0) {
    int ae = alturaArvoreAVL((*node)->esquerda);
    int ad = alturaArvoreAVL((*node)->direita);

    printf("%d(%d), ", (*node)->chave, ad-ae);
    fprintf(arqsaida, " %d (%d),", (*node)->chave, ad-ae);
  }else if((*node)!=NULL){
    printAVL(&(*node)->esquerda,level-1,arqsaida);
    printAVL(&(*node)->direita,level-1,arqsaida);

  }
}

void imprimirAVL(PointeiroArvoreAVL *node, FILE* arqsaida){
  int altura = profundidadeAVL(&(*node));
  for (int i = 0; i < altura; i++) {
    printAVL(&(*node),i,arqsaida);
    printf("\n");
    fprintf(arqsaida, "\n" );
  }
}

int main(int argc, const char * argv[]){
  PointeiroArvoreAVL raiz;
  FilaDinamica fila;
  char* numeros;
  int num;
  char linha[100];
  char opcao;

  if(argc != 3) {
   printf("Numero de parametros não é o correto\n");
   exit(1);
  }

  FILE 	*arqentrada = fopen(argv[1], "r");
  FILE 	*arqsaida = fopen(argv[2], "w");

  //controle de erros da abertura dos arquivos
  if(arqentrada == NULL){
    printf("Erro ao abrir o arquivo de entrada\n");
    exit(1);
  }

  if(arqsaida == NULL){
    printf("Erro ao abrir o arquivo de saida\n");
    exit(1);
  }

  iniciaArvoreAVL(&raiz);
  iniciaFila(&fila);

  // Leitura da primeira linha
  fgets(linha,99,arqentrada);

  numeros = strtok(linha,",");
  while (numeros!=NULL){
    num=strtol(numeros,NULL,10);
    inserirAVL(&raiz, num);
    numeros = strtok(NULL,",");
  }

  // Leitura da segunda linha
  fgets(linha,99,arqentrada);

  numeros = strtok(linha,",");
  while (numeros!=NULL){
    num=strtol(numeros,NULL,10);
    enfileira(&fila,num);
    numeros = strtok(NULL,",");
  }

  opcao = fgetc(arqentrada);
  //trabalhar com caracteres minusculos
  opcao = tolower(opcao);

  if (opcao!='e' && opcao!= 'd') {
    fprintf(arqsaida, "Arquivo inválido!\n" );
    exit(1);
  }

  fprintf(arqsaida, "[*]antes\n");
  //imprimir estado inicial
  imprimirAVL(&raiz,arqsaida);

  while (!estaVaziaFila(&fila)) {
    num = desenfileira(&fila);
    removeAVL(&raiz,num,opcao);
  }

  fprintf(arqsaida, "\n[*]depois\n");
  imprimirAVL(&raiz,arqsaida);

  destruirArvoreAVL(&raiz);
  return 0;
}
