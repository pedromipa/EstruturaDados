#include <stdio.h>
#include <stdlib.h>

int testaVogal (char letra) {
	if (letra=='a'||letra=='e'||letra=='i'||letra=='o'||letra=='u'){
		return 1;
	}else{
		return 0;
  }
}

int main(){
	FILE 	*arqentrada = fopen("entrada.txt", "r");
	FILE 	*arqsaida = fopen("saida.txt", "w");
	char caracter, comparativo[100];
  int contador=1;



  if(arqentrada == NULL){
	printf("Erro ao abrir o arquivo de entrada\n");
	exit(1);
  }else{
	printf("arquivo de entrada aberto com sucesso\n");
  }

  arqsaida = fopen("saida.txt", "w");
  if(arqsaida == NULL){
  printf("Erro ao abrir o arquivo de saida\n");
  exit(1);
  }else{
  printf("arquivo de saida aberto com sucesso\n");
  }

	caracter = fgetc(arqentrada);
	while (caracter!=EOF){

		if (testaVogal(caracter)){
			fputc("*", arqsaida);
		caracter=getc(arqentrada);
	 }else{
     fputc(caracter, arqsaida);
     caracter=getc(arqentrada);
    }
  }//while

   while (fgets(comparativo, 100, arqentrada) != NULL ){
 	   contador ++;
  }


   printf("Numero de linhas: %d\n", contador);

	fclose(arqentrada);
	fclose(arqsaida);

	return 0;
}
