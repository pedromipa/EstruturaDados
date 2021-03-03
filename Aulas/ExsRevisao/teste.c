#include <stdio.h>
#include <stdlib.h>

int *receberValor(int *vetA, int *vetB, int N){
  int *vetC =(int*)malloc(N * sizeof(int));

  for (int i=0; i < N; i++){
	vetC[i] = vetA[i]*vetB[i];
  }

  return vetC;
}

int main(){
  int N, *vetC;
  printf("Digite um valor: ");
  scanf("%d", &N);

  int *vetA =(int*)malloc(N * sizeof(int));
  int *vetB =(int*)malloc(N * sizeof(int));

  for (int i = 0; i < N; i++) {
	printf("Digite o valor %d do vetor A: ",i);
	scanf("%d", &vetA[i]);
	printf("Digite o valor %d do vetor B: ",i);
	scanf("%d", &vetB[i]);
  }

  vetC = receberValor(vetA, vetB, N);

  for (int i=0; i<N; i++){
	printf("%d\n", vetC[i]);
  }
  return 0;
}
