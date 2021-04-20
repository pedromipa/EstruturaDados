#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct NoLista* PtrNoLista;

typedef struct  {
  int chave;
  char infos[100];
} Objeto;

typedef struct NoLista {
    Objeto elemento;
    PtrNoLista proximo;
    PtrNoLista anterior;
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

void inserir(Lista *lista, Objeto *objeto){

    //criaçao e alocação do ponteiro novo
    PtrNoLista novo;
    PtrNoLista aux;
    novo = (PtrNoLista)malloc(sizeof( NoLista));
    novo->elemento.chave = objeto->chave;
    //colocar as informações da string para o elemento na fila
    strcpy (novo->elemento.infos,objeto->infos);

  //situação 1: se a lista vazia ou
  //o elemento que queremos inserir é menor que o primeiro
  if(estaVazia(lista) || objeto->chave < lista->primeiro->elemento.chave){
    aux = lista->primeiro;
    novo->proximo = lista->primeiro;
    lista->primeiro = novo;
    // caso nao seja a primeira inserção na lista
    if (!estaVazia(lista)) {
      aux->anterior = lista->primeiro;
    }
  //situação 2: aux percorre a lista para encontrar o ponto de inserção
  }else{
    PtrNoLista aux2;
    aux = lista->primeiro;
    while (aux->proximo!=NULL && objeto->chave > aux->proximo->elemento.chave) {
      aux = aux->proximo;
    }//while

    aux2 = aux->proximo;
    //se nao estivermos inserindo o novo elemento na ultima posição, alteramos o anterior do aux2
    if (aux2!=NULL) {
      aux2->anterior = novo;
    }
    novo->anterior = aux;
    novo->proximo = aux->proximo;
    aux->proximo = novo;

  }//if else

  lista->tamanho ++;

}//void inserir

void imprimirLista(Lista *lista){
  printf("Lista = {");
  PtrNoLista percorre;

  for(percorre = lista->primeiro; percorre != NULL; percorre = percorre->proximo) {
      printf("%d ", percorre->elemento.chave);
    }

  printf("}\n");

}

// Função para a operaçao 1
void crescente(Lista *lista, FILE *arqsaida){
  PtrNoLista percorre;
  for(percorre = lista->primeiro; percorre != NULL; percorre = percorre->proximo) {
      fputc('{', arqsaida);
      fprintf(arqsaida, "%d",percorre->elemento.chave);
      fputs(percorre->elemento.infos, arqsaida);
    }
}

// Função para a operação 2
void decrescente(Lista *lista, FILE *arqsaida){
  PtrNoLista percorre;
  percorre = lista->primeiro;

  // Encontrar ultimo elemento
  while (percorre->proximo != NULL) {
    percorre = percorre->proximo;
  }

  // Imprimir de trás para frente
    while (percorre !=NULL) {
      fputc('{', arqsaida);
      fprintf(arqsaida, "%d",percorre->elemento.chave);
      fputs(percorre->elemento.infos, arqsaida);
      percorre = percorre->anterior;
    }
}//void decrescente

// Função para operação 3
 void pesquisar(Lista *lista, int key, FILE *arqsaida){
   if(estaVazia(lista)){
     //Nao encontrado: lista vazia
     fprintf(arqsaida, "Codigo nao encontrado! Cadastro vazio.");
     printf("Codigo nao encontrado!\n");
   }

   //pesquisa o elemento na lista
   PtrNoLista percorre = lista->primeiro;
   while(percorre != NULL && key > percorre->elemento.chave) {
     percorre = percorre->proximo;
   }

   // caso seja nulo, significa que percorreu a lista inteira e nao encontrou
   if(percorre == NULL || percorre->elemento.chave > key) {
     //nao encontrado: imprime erro
     fprintf(arqsaida, "Codigo nao encontrado!");
     printf("Codigo nao encontrado!\n");
   }else{
     //encontrado: imprime no arq de saida
     fputc('{', arqsaida);
     fprintf(arqsaida, "%d",percorre->elemento.chave);
     fputs(percorre->elemento.infos, arqsaida);
     printf("Codigo encontrado!\n");
   }//if else
}// void pesquisar

int main(int argc, char *argv[]) {
  int opcao;
  Lista lista;
  Objeto elemento;

  iniciaLista(&lista);

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

  // enquanto primeiro caracter for "{" salva os dados
  while (fgetc(arqentrada)=='{') {
    //Leitura do codigo de registro
    fscanf(arqentrada, "%d",&elemento.chave);
    //Leitura dos demais dados da pessoa
    fgets(elemento.infos,100,arqentrada);

    //para verificarmos se esta salvando corretamente
    printf("{%d",elemento.chave );
    printf("%s",elemento.infos );

  //insere o elemento na lista
    inserir(&lista, &elemento);

    // quando chegar na ultima linha, le a opcao escolhida
    fscanf(arqentrada, "%d",&opcao);
  }//while

  if (opcao == 1) {
    printf("opcao 1 \n");
    crescente(&lista,arqsaida);

  }else if(opcao == 2){
    printf("opcao 2 \n");
    decrescente(&lista,arqsaida);
  }else if(opcao == 3){
    printf("opcao 3 \n");
    int pesquisa;
    fscanf(arqentrada, "%d",&pesquisa);
    pesquisar(&lista,pesquisa,arqsaida);

  }else{
    printf("Opcao invalida!\n");
    fprintf(arqsaida, "Opção inválida!");
    exit(1);
  }

  imprimirLista(&lista);

  fclose(arqentrada);
  fclose(arqsaida);

  return 0;
}
