#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <time.h>   

typedef struct tipoElemento{
	int valor;
	int flag;
	struct tipoElemento *prox;
}TElemento;

long int countLines();
void inicializaVetor(TElemento *vetor, long int tamanho);
long int firstHash(TElemento vetor[], long int tamanho, int valor);
long int secondHash(TElemento vetor[], long int tamanho, int valor);
long int reHash(TElemento *vetor, long int tamanho, int sechash);
long int hash_function(TElemento vetor[], long int tamanho, int valor);
int menu();
void insere(TElemento *vetor, int tamanho);
void exibir_lista(TElemento *vetor, int tamanho);
int buscarHash(TElemento *vetor, int valor, long int tamanho);
void excluirElemento(TElemento *vetor, long int tamanho);
void buscarValorHash(TElemento *vetor, long int tamanho);


