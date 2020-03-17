#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
  char valor;
  char naipe[8];
  bool foiJogada;
}Carta;

typedef struct {
  Carta carta[52];
}Baralho;
Baralho baralho;
int p=0;

void criaBaralho(Baralho *baralho){
  char type[13] = {'A','2','3','4','5','6','7','8','9','0','J','Q','K'};
  char suit[4][8] = {"Coracao", "Espadas", "Ouro", "Paus"};

  for (int i=0; i<13; i++){
    for (int j=0; j<4; j++){
      baralho->carta[p].valor = type[i];
      strcpy(baralho->carta[p].naipe, suit[j]);
      baralho->carta[p].foiJogada = false;
      p++;
    }
  }
}

void imprimeBaralho(Baralho *baralho){
  for (int i=0; i < 52; i++) {
    printf("Carta:  %c  %s \n", baralho->carta[i].valor, baralho->carta[i].naipe);
  }
}

int main(){
  criaBaralho(&baralho);
  imprimeBaralho(&baralho);

  return 0;
}
