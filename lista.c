#include "lista.h"

//Funcao para contar a quantidade de linhas do arquivo
long int countLines(){
	FILE *arq;
	long int cont=0;
	char linha[100];
	
	arq = fopen("randInt100K.txt", "r");
	if (!arq){
		printf("Arquivo não encontrado");
		return 0;
	}
	
	//Faz a leitura de cada linha e acrescenta 1 ao contador
	while (fgets(linha, sizeof(linha), arq)){ //Contar cada linha e adicionar 1 no contador
		cont++;
	}
	
	fclose(arq);
	
	return cont;	
}

//Primeira funcao da HASH
long int firstHash(TElemento vetor[], long int tamanho, int valor){
	long int first = valor % tamanho; //Retorna o mod do valor pelo tamanho
	return first;
}
 
//Segunda funcao hash
long int secondHash(TElemento vetor[], long int tamanho, int valor){
	long int second = 1 + (valor % (tamanho - 1));
	return second;
}

long int reHash(TElemento *vetor, long int tamanho, int sechash){
	long int cont = 3; //Inicializo o contador com 3
	long int terc = (sechash + cont) % tamanho; //Realiza a operacao de rehash
	if (vetor[terc].valor == -1){ //Se a posicao do vetor que retornar for vazia , ou seja, -1
		return terc; //retorna essa posicao
	}
	
	//Calcular ate encontrar uma posicao vazia para inserir
	while(vetor[terc].valor != -1){ //Enquanto nao achar uma posicao vazia
		cont++; //Incrementar o contador
		terc = (sechash + cont) % tamanho; //chamar a funcao novamente
	}
	return terc;
}
 
long int hash_function(TElemento vetor[], long int tamanho, int valor){
	long int prihash, sechash, terhash;
 
	prihash = firstHash(vetor, tamanho, valor); //Retorna a posicao da primeira formula (MOD)
	//Confere ser a posicao do vetor esta vazia, nesse caso o vazio � -1
	if(vetor[prihash].valor == -1){
		return prihash; //Se estiver vazia, retorna a posicao que o valor sera inserido
	}
 
 	//Confere ser a posicao do vetor esta vazia, nesse caso o vazio � -1
	sechash = secondHash(vetor, tamanho, valor); //Retorna a posicao da segunda formula
	if(vetor[sechash].valor == -1){ //Se a posicao no vetor estiver vazia, ira retornar a posicao em que o valor sera inserido
		return sechash; 
	}
 
 	//Se a primeira e a segunda formula retornarem posicoes nos vetores que estao ocupadas, a terceira formula
 	//ira retornar a posciao correta que o valor sera inserido
	terhash = reHash(vetor, tamanho, sechash); 
	return terhash;
}

//Inicializa todas as posicoes do Vetor
void inicializaVetor(TElemento *vetor, long int tamanho){
	long int i;
	for (i = 0; i < tamanho; i++){
		//Todas as posicoes sao inicializadas com -1
		vetor[i].valor = -1;
		//Flag 0 significa que n�o existe nenhum elemento na posicao;
		vetor[i].flag = 0;
	}
}

int menu(){
	int opcao;
	system("CLS"); //Limpa a Tela e posiciona o 
	               //CURSOR no canto esquerdo superior da mesma
    printf("\n\n\n\t=====| MENU |=====\n\n");
    printf("0 - SAIR (Encerrar Programa).\n\n");
    printf("1 - Inserir.\n");
    printf("2 - Exibir Lista Completa.\n");
    printf("3 - Excluir.\n");
    printf("4 - Buscar valor HASH.\n");
    printf("\tInforme OPCAO desejada: ");
    
    scanf("%d",&opcao);
	
	if ((opcao > 4) || (opcao < 0)){
		printf("\n\n\n");
		printf("+-------------------------------+\n");
		printf("|ERRO  	------------------------|\n");
		printf("|Op��o inv�lida	----------------|\n");
		printf("|Tente outra vez    ------------|\n");
		printf("+-------------------------------+\n\n\n");
		system("PAUSE");
	}
	return opcao;
}

//Insere um elemento no vetor informado pelo usuario
void insere(TElemento *vetor, int tamanho){
	long int hash, valor;
	printf("Insira um valor: ");
	scanf("%d" ,&valor);
	
	hash = hash_function(vetor, tamanho, valor);
	vetor[hash].flag = 1;
	vetor[hash].valor = valor;
	printf("\n\tValor inserido na posicao %d com SUCESSO...\n\n", hash);
	system("pause");
}

void exibir_lista(TElemento *vetor, int tamanho){
	int i;
	
	//Percorre o vetor e mostra no prompt somente as posicoes que possuem um valor inserido,
	//ou seja, que o valor no vetor seja diferente de -1
	for(i = 0; i < tamanho; i++){ 
		if (vetor[i].valor != -1){
			printf("\n(%d) - Valor: %d\n" ,i, vetor[i].valor);
		}
	}
	printf("\n\n");
	system("pause");
}

//Funcao para verificar se um elemento existe utilizando a HASH
int buscarHash(TElemento *vetor, int valor, long int tamanho){
	int confirmar=0;
	//Se encontrar o elemento no vetor ir� retornar a posicao dele
	int primHash = firstHash(vetor, tamanho, valor);
	if(vetor[primHash].valor == valor){ //Se o valor buscado for igual ao valor encontrado na posicao do vetor da primeira funcao hash
		return primHash; //Retorna a posicao que o valor ocupa no vetor
	}
	
	int secHash = secondHash(vetor, tamanho, valor);
	if(vetor[secHash].valor == valor){ //Se o valor buscado for igual ao valor encontrado na posicao do vetor da segunda funcao hash
		return secHash; //Retorna a posicao que o valor ocupa no vetor
	}
	
	int cont = 3;
	int tercHash = (secHash + cont) % tamanho; //Retorna uma possivel posicao que o valor ocupa no vetor
	while(vetor[tercHash].flag != 0){ //Se a flag e zero significa que nenhum elemento foi adicionado na posicao
		if(vetor[tercHash].valor == valor){
			return tercHash;
		}
		cont++;
		tercHash = (secHash + cont) % tamanho;
	}
	
	//Caso nao encontre o valor no vetor, ira retornar -1
	return -1;
	
}

void excluirElemento(TElemento *vetor, long int tamanho){
	int argumento;
		
	printf("\n\nInsira o valor que ser� removido: ");
	scanf("%d" ,&argumento);
	
	int long hash = buscarHash(vetor, argumento, tamanho); //Retorna a posicao do valor no vetor
	if (hash != -1){ 
		printf("\n\tValor exclu�do com SUCESSO!\n\n");
		vetor[hash].valor = -1;
	} else {
		//Se o retorno for -1 significa que o valor nao existe no vetor
		printf("\t\n\nElemento %d n�o encontrado!!", argumento);
		printf("\t\n\nTente novamente\n\n\n");
	}
	
	system("pause");
}

void buscarValorHash(TElemento *vetor, long int tamanho){
	int argumento;
	long int hash;
	double time_spent = 0.0; //Define o timer como zero

	printf("\n\n\t|======= Buscar Elemento utilizando pela HASH =======|\n");
	printf("\tInsira o valor para ser encontrado: ");
	scanf("%d", &argumento);
	clock_t begin = clock(); //Comeca a contar o tempo de busca
	
	int i=0;
	hash = buscarHash(vetor, argumento, tamanho); //Retorna a posicao na hash
	if (hash != -1){ //Se a hash for diferente de -1 eh sinal que existe o valor no vetor
		clock_t end = clock(); //Terminar o tempo de busca
		printf("\n\n\tElemento %d encontrado!\n", argumento);
		printf("\nPosicao no vetor: %d\n\n\n", hash);
		time_spent += (double)(end - begin) / CLOCKS_PER_SEC; //Retorna a diferenca de tempo do comeco e do final e dividi pelo tempo do clock em segundos
    	printf("\tTempo gasto: %f \n\n", time_spent);
	} else {
		//Se nao existir o valor no vetor
		printf("\t\n\nElemento %d nao encontrado!!", argumento);
		printf("\t\n\nTente novamente\n\n\n");
	}
	
	system("pause");	
}
