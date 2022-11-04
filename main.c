#include "lista.h"

int main(int argc, char *argv[]){
	int op;
	long int tamanho = countLines() * 1.5; //Retorna a quantidade de linhas do arquivo e multiplicapor 1,5
	TElemento *vetor = (TElemento *)malloc(sizeof(TElemento) * tamanho); //Aloca espaco no vetor para que ele tenha o tamanho desejado
	FILE *arq;
	int valor;
	double time_spent = 0.0; //Define o timer como zero
	
	inicializaVetor(vetor, tamanho); //Incializa todas as posicoes do vetor com -1 e a flag com 0
	
	arq = fopen("randInt100K.txt", "r");
	if (!arq){ //Confere se existe o arquivo que sera aberto
		printf("Arquivo nao encontrado");
	}
	
	long int hash;
	clock_t begin = clock(); //Comeca a contar o tempo de inserir
	while (fgetc(arq) != EOF){
		fscanf(arq, "%d", &valor); //Pega o valor que esta no arquivo
		hash = hash_function(vetor, tamanho, valor); //Retorna a posicao que ele sera inserido
		vetor[hash].valor = valor; //Insere o valor na sua posicao do vetor
		vetor[hash].flag = 1; //A flag se torna true, nessa caso , 1
	}
	clock_t end = clock(); //Terminar o tempo de busca
	
	fclose(arq);
	
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC; //Retorna a diferenca de tempo do comeco e do final e dividi pelo tempo do clock em segundos
    printf("\tTempo gasto: %f \n\n", time_spent);
	system("pause");	
	
	do {
		op = menu();
		
		switch(op){
			case 1: insere(vetor, tamanho); break;
			case 2: exibir_lista(vetor, tamanho); break;
			case 3:	excluirElemento(vetor, tamanho); break;
			case 4: buscarValorHash(vetor, tamanho);break;
		}
		
	}while(op != 0);
	
	return 0;
}
