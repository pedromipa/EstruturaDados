#include <stdio.h>
#include <stdlib.h>

void converteHora(int totalMinutos, int *hora, int *minutos){

  if (totalMinutos>=60){
    *hora = totalMinutos/60;
    *minutos = totalMinutos%60;
  }else{
    *hora = 0;
    *minutos = totalMinutos;
  }
}

int main(){
  int totalMinutos;
  int hora, minutos;

  printf("Digite os minutos: \n");
  scanf("%d", &totalMinutos);

  converteHora(totalMinutos, &hora, &minutos);

  printf("%d horas e %d minutos\n", hora, minutos);
  return 0;
}
//00
