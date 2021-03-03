#include <stdio.h>
#include <stdlib.h>

int *alocaVetor(int N){
  int *vet=(int*)malloc(N * sizeof(int));
  if (N<0) {
    printf("Ponteiro não alocado\n");
    exit(1);
  }

  return vet;
}

void preencher(int N,int *vet){
  for (int i=0; i < N; i++){
  	printf("valor %d: ", i);
  	scanf("%d", &vet[i]);
  }
}

int main(){
  int N, *vet;
  printf("Digite o tamanho: ");
  scanf("%d", &N);

  vet = alocaVetor(N);

  preencher(N, &vet[0]);

//exibir
  for (int i=0; i < N; i++){
	printf("%d: ", vet[i]);

  }

  free(vet);
  return 0;
}
