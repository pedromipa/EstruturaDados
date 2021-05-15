#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct NoLista* PtrNoLista;

typedef struct NoLista {
  int pag;
  PtrNoLista proximo;
} NoLista;

typedef struct {
  PtrNoLista primeiro;
  int tamanho;
} Lista;

typedef struct NoArvore *PtrNoArvore;

 typedef struct Objeto{
   char termo[30];
   Lista paginas;
} Objeto;

typedef struct NoArvore {
    Objeto obj;
    PtrNoArvore filhoDireita;
    PtrNoArvore filhoEsquerda;
} NoArvore;

// Funções para manipular a lista

void iniciaLista(Lista *lista){
  lista->primeiro = NULL;
  lista->tamanho = 0;
}

bool estaVaziaLista(Lista *lista){
    return(lista->tamanho==0);
}

bool pesquisarLista(Lista *lista, int key){
   if(estaVaziaLista(lista)){
     return false;
   }

  PtrNoLista percorre;

  for(percorre = lista->primeiro; percorre != NULL; percorre = percorre->proximo) {
      if (percorre->pag == key) return true;
  }

 return false;
}

void inserirLista(Lista *lista, int x){

    PtrNoLista aux;
    //criaçao e alocação do ponteiro novo
    PtrNoLista novo;
    novo = (PtrNoLista)malloc(sizeof( NoLista));
    novo->pag = x;

  //situação 1: se a lista vazia ou
  //o elemento que queremos inserir é menor que o primeiro
  if(estaVaziaLista(lista) || x < lista->primeiro->pag){
    novo->proximo = lista->primeiro;
    lista->primeiro = novo;

  //situação 2: aux percorre a lista para encontrar o ponto de inserção
  }else{
    aux = lista->primeiro;
    while (aux->proximo!=NULL && x > aux->proximo->pag) {
      aux = aux->proximo;
    }//while

    novo->proximo = aux->proximo;
    aux->proximo = novo;

  }//if else

  lista->tamanho ++;

}//void inserir

// Funções para manipular a árvore

void iniciaArvore(PtrNoArvore *tree){
  *tree = NULL;
}

bool insereArvore(PtrNoArvore *tree, char *termo){
  //caso 1: encontrou o ponto de inserção
  if(*tree == NULL){
    //novo nó
    (*tree) = malloc(sizeof(NoArvore));
    // filho da direita e filho da esquerda = NULL
    (*tree)->filhoDireita  = NULL;
    (*tree)->filhoEsquerda = NULL;

    //atribuindo o termo ao nó
    strcpy ((*tree)->obj.termo,termo);
    iniciaLista(&(*tree)->obj.paginas);
    return true;
  }

  if (strcmp((*tree)->obj.termo, termo) == 0) {
    return false;
  }

  //caso 3
  if(strcmp((*tree)->obj.termo, termo) > 0) {
    return(insereArvore(&(*tree)->filhoEsquerda, termo));
  } else {
    return(insereArvore(&(*tree)->filhoDireita, termo));
  }

}

bool procurar(PtrNoArvore *tree, char *palavra, int pag){
  // caso 1: nao achou o elemento/nao existe na arvore
  if(*tree == NULL) return (false);

  // caso 2: nó cujo valor é o procurado
  if(strcmp((*tree)->obj.termo, palavra) == 0 && !pesquisarLista(&(*tree)->obj.paginas,pag)){
    inserirLista(&(*tree)->obj.paginas, pag);
    return (true);
  }

  if(strcmp((*tree)->obj.termo, palavra) > 0) {
    return(procurar(&(*tree)->filhoEsquerda, palavra, pag));
  } else {
    return(procurar(&(*tree)->filhoDireita, palavra, pag));
  }
}

bool estaVazia(PtrNoArvore *tree){
  return (*tree == NULL);
}

void EmOrdem(PtrNoArvore *node, FILE *arqsaida){
  //Percorrer a arvore na ordem alfabética dos termos
  PtrNoLista percorre;
  if(*node == NULL) return;
  EmOrdem(&(*node)->filhoEsquerda, arqsaida);
  fprintf(arqsaida, "%s",(*node)->obj.termo);
  for(percorre = (*node)->obj.paginas.primeiro; percorre != NULL; percorre = percorre->proximo) {
      fprintf(arqsaida, ",%d", percorre->pag);
    }
  fprintf(arqsaida, "\n");
  EmOrdem(&(*node)->filhoDireita, arqsaida);
}

void destroiArvore(PtrNoArvore *node){
  //percorrer a arvore e desalocar memoria de tras p/ frente
  if ((*node)!=NULL){
    destroiArvore(&(*node)->filhoEsquerda);
    destroiArvore(&(*node)->filhoDireita);
    free(*node);
    (*node)=NULL;
  }
}

int main(int argc, const char * argv[]){
  char *palavra;
  char linha1[100];
  char texto[300];
  int pag=0;
  // arvore na main
  PtrNoArvore raiz;
  iniciaArvore(&raiz);

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

  if (fscanf(arqentrada,"%s[^\n]",&linha1) == -1) {
    printf("Arquivo de entrada vazio!\n");
    fprintf(arqsaida,"Arquivo de entrada vazio!\n");
    exit(1);
  }

  strlwr(linha1);

  palavra = strtok(linha1," .()<:,>\n");

  if (strcmp(palavra, "termos") != 0 && strcmp(palavra, "termo") != 0) {
    printf("Arquivo de entrada no formato errado\n");
    fprintf(arqsaida, "Arquivo de entrada no formato errado!\n");
    exit(1);
  }else{
    palavra = strtok(NULL," .()<:,>\n");
    while (palavra != NULL){
      //INSERIR NA ARVORE
      insereArvore(&raiz,palavra);
      palavra = strtok(NULL, " .()<:,>\n");
      }//while
  }//if else

  while (fgets(texto,299,arqentrada)!=NULL){
    strlwr(texto);
    palavra = strtok(texto," .()<:,>\n");
    while(palavra!=NULL){
      if (strcmp(palavra,"page")==0){
        pag++;
      }else{
        //PROCURA A PALAVRA
        procurar(&raiz, palavra, pag);
      }//if else
      palavra = strtok(NULL," .()<:,>\n");
    }//while interno
  }//while externo

  // Imprimir os termos em ordem alfabética
  EmOrdem(&raiz, arqsaida);
  printf("Arquivo de saida criado com sucesso!\n");

  destroiArvore(&raiz);
  fclose(arqentrada);
  fclose(arqsaida);


  return 0;
}
