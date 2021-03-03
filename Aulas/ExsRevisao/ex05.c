#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
  char nome[21];
  char tipoMusica[21];
  int integrantes, ranking;
}Banda;

void preencher(int tam, Banda *banda){
  for (int i=0; i< tam; i++) {
  	printf("Digite o nome da Banda:");
    	fgets(banda[i].nome,20,stdin);
    	banda[i].nome[strcspn(banda[i].nome,"\n")]='\0';
  	   setbuf(stdin,NULL);
  	printf("Digite o tipo de musica que ela toca:");
    	fgets(banda[i].tipoMusica,20,stdin);
    	banda[i].tipoMusica[strcspn(banda[i].tipoMusica,"\n")]='\0';
    	setbuf(stdin,NULL);
  	printf("Digite o numero de integrantes que ela possui:");
    	scanf("%d", &banda[i].integrantes);
    	setbuf(stdin,NULL);
  	printf("Digite a posição dela de 1 a 5 no seu ranking de bandas favoritas:");
    	 scanf("%d", &banda[i].ranking);
    	setbuf(stdin,NULL);
  	printf("\n-----------\n");
  }//for
}//void preencher

void exibir(int tam, Banda *banda) {
  for (int i=0; i<tam; i++) {
  	printf("Nome: %s\n", banda[i].nome);
  	printf("Tipo de musica: %s\n", banda[i].tipoMusica);
  	printf("Numero de integrantes: %d\n", banda[i].integrantes);
  	printf("Ranking favoritos: %dº lugar\n", banda[i].ranking);
	  printf("\n");
  }//for
}//void exibir

void escolhaExibir(int tam, Banda *banda) {
  int opcao;

  	printf("Digite um número de 1 a 5 para visualizar a banda do ranking:");
  	scanf("%d", &opcao);

    if (opcao<1 || opcao>5){
    	printf("Numero invalido\n");
      return;
  	}//if else

    for (int i = 0; i < tam; i++) {
      if (banda[i].ranking == opcao) {
      	printf("Nome: %s\n", banda[i].nome);
      	printf("Tipo de musica: %s\n", banda[i].tipoMusica);
      	printf("Numero de integrantes: %d\n", banda[i].integrantes);
    	  printf("Ranking favoritos: %dº lugar\n", banda[i].ranking);
    }
  }//for
}//void exibir

int main(){
  Banda banda[5];

	preencher (5, banda);

	exibir (5, banda);

	escolhaExibir (5, banda);

  return 0;
}//main
