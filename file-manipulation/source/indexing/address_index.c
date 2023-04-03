#include "address_index.h" 		// compare, sort_index, create_index, search_index
#include <stdio.h> 				// printf, scanf, fopen, fclose
#include <stdlib.h> 			// malloc, free
#include <string.h> 			// strcmp, strcpy
#include <time.h>

int compare(const void *e1, const void *e2)
{
	return strncmp(((Indexed*)e1)->cep,((Indexed*)e2)->cep,8);
}

int create_index(FILE *f)
{
	FILE *f_index;      // Arquivo de indices
	Indexed *e;         // Endereco auxiliar
	Endereco *e2;       // Endereco auxiliar
	int count = 0;      // Contador de registros
  	int chunk = 100;    // Tamanho do chunk

	e = malloc(sizeof(Indexed));
	e2 = malloc(sizeof(Endereco));

  	if ((f_index = fopen("if.dat", "wb")) == NULL) { 	// Abre o arquivo de indices
		printf("Error opening file if.dat\n");
		return -1; 										//// fim : Retorna -1 se ocorrer algum erro
	}

	while(fread(e2,sizeof(Endereco),1,f) == 1) { 		// Le o arquivo de dados
		strcpy(e->cep,e2->cep);
		e->index = count;
		fwrite(e,sizeof(Indexed),1,f_index); 			// Escreve no arquivo de indices
		count++;
	}

	printf("Created index file = OK\n");

  	free(e);
  	free(e2);
	fclose(f_index);
	return (count+1); 	// Retorna a quantidade de registros
}

int sort_index(FILE *f) {
	FILE *f2;           // Arquivo de indices
	Indexed *e;         // Endereco auxiliar
	long pos;           // Posicao de registros
	long qtd;           // Quantidade de registros
	int chunk = 100;    // Tamanho do chunk

	fseek(f,0,SEEK_END);
	pos = ftell(f);
	qtd = pos/sizeof(Indexed);
	e = malloc(qtd * sizeof(Indexed));
	rewind(f);

	if(e == NULL) { 									// Verifica se a memoria foi alocada
		printf("Error while allocating memory\n");
		return -1; 										//// fim : Retorna -1 se ocorrer algum erro
	}

	if(fread(e,sizeof(Indexed),qtd,f) > 0) { 			// Le o arquivo de indices
		printf("Read index file = OK\n");
	}

	qsort(e,qtd,sizeof(Indexed),compare);				// Ordena o arquivo de indices
	printf("Ordered index file = OK\n");

	if ((f2 = fopen("if_ordered.dat", "wb")) == NULL) { // Abre o arquivo de indices ordenado
		printf("Error opening file if.dat\n");
		return -1; 										//// fim : Retorna -1 se ocorrer algum erro
	}

	Indexed *e2;
	for(int i = 0; i < qtd; i++) { 						// Escreve o arquivo de indices ordenado
		e2 = (e+i);
		fwrite(e2,sizeof(Indexed),1,f2);
	}

	printf("Save ordered index file = OK\n");
	
	free(e);
	fclose(f2);                          				// Fecha o arquivo de indices ordenado
	return 0; 											//// fim : Retorna 0 se tudo ocorrer bem
}

int search_index(FILE *f, char *cep, char mode)
{
	Indexed *e;         // Endereco auxiliar
	int left = 0;
	int right = 0;
	int middle = 0;
	int result = 0;
	int found = 0;

	clock_t start, end;
	double cpu_time_used;

	e = malloc(sizeof(Indexed));

	if(e == NULL) { 									// Verifica se a memoria foi alocada
		printf("Error while allocating memory\n");
		return -1; 										//// fim : Retorna -1 se ocorrer algum erro
	}

	start = clock();

	if(mode == 'b') { 						// Busca binaria
		fseek(f,0,SEEK_END);
		right = ftell(f)/sizeof(Indexed);
		rewind(f);

		while(left <= right) {
			middle = (left + right)/2;
			fseek(f,middle * sizeof(Indexed),SEEK_SET);
			fread(e,sizeof(Indexed),1,f);
			result = strncmp(e->cep,cep,8);
			if(result == 0) {
				found = 1; // Encontrou
				break;
			}
			else if(result < 0) {
				left = middle + 1;
			}
			else {
				right = middle - 1;
			}
		}

	}
	else if(mode == 's') { 					// Busca sequencial
		while(fread(e,sizeof(Indexed),1,f) == 1) {
			if(strncmp(e->cep,cep,8) == 0) {
				found = 1; 									// Encontrou
				break;
			}
		}
	}
	else {
		printf("Invalid mode\n");
	}

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("Time: %f\n",cpu_time_used);

	rewind(f); 											// Volta para o inicio do arquivo
	free(e);

	if(found == 1) {
		return e->index; 									// Retorna o indice do registro
	}

  	return -1; 											//// fim : Retorna -1 se nao encontrar
}

int search_data(FILE *f, int index)
{
	Endereco *e;        // Endereco auxiliar

	e = malloc(sizeof(Endereco));

	if(e == NULL) { 									// Verifica se a memoria foi alocada
		printf("Error while allocating memory\n");
		return -1; 										//// fim : Retorna -1 se ocorrer algum erro
	}

	fseek(f,index * sizeof(Endereco),SEEK_SET); 		// Posiciona o ponteiro
	fread(e,sizeof(Endereco),1,f); 						// Le o registro

	printf("\n");

	printf("Endereco: %.72s\n",e->logradouro);
	printf("Bairro: %.72s\n",e->bairro);
	printf("Cidade: %.72s\n",e->cidade);
	printf("UF: %.72s\n",e->uf);
	printf("SIGLA: %.2s\n",e->sigla);

	rewind(f); 											// Volta para o inicio do arquivo
	free(e);
	return 0; 											//// fim : Retorna 0 se tudo ocorrer bem
}