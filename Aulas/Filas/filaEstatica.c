#include "filaEstatica.h"

void iniciaFila(FilaEstatica *fila);
bool estaVazia(FilaEstatica *fila);
bool estaCheia(FilaEstatica *fila);
int tamanhoFila(FilaEstatica *fila);
int incrementaIndice(int i);
void enfileira(Objeto x, FilaEstatica *fila);
void imprimeFila(FilaEstatica *fila);
Objeto desenfileira(FilaEstatica *fila);
Objeto inicioFila(FilaEstatica *fila);
Objeto fimFila(FilaEstatica *fila);
