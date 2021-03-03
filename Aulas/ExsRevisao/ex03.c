#include <stdio.h>
#include <stdlib.h>

int multiplica(int x, int y){

  if(y==1){
	return x;
  }else{
	return x * multiplica(x, y-1);
  }//if else
}//multiplica

 int main(){
   int x, y, resultado=0;
   printf("Digite um número para ser a base:");
   scanf("%d", &x);
   printf("Digite um número para ser o expoente:");
   scanf("%d", &y);

   resultado = multiplica(x, y);

   printf("Resultado: %d\n", resultado);

   return 0;
 }//main
