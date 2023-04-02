#include "address_index.h"
#include <stdlib.h>
#include <string.h>

int compara(const void *e1, const void *e2)
{
	return strncmp(((Indexed*)e1)->cep,((Indexed*)e2)->cep,8);
}

int sort_index(FILE *f) {
	Indexed *e;         // Endereco auxiliar
  long pos;           // Posicao de registros
  long qtd;           // Quantidade de registros
  int chunk = 100;    // Tamanho do chunk

  fseek(f,0,SEEK_END);
	pos = ftell(f);
  qtd = pos/sizeof(pos);
	e = malloc(qtd * sizeof(Indexed));
  rewind(f);

	if(e == NULL) { // Verifica se a memoria foi alocada
		printf("Erro: Nao consegui alocar a memoria\n");
		fclose(f);
		return -1;
	}

	while(fread(e,sizeof(Indexed),1,f) == 1)
  {
		// Reading...
	}
  printf("Read = OK\n");

	fclose(f);

	qsort(e,qtd,sizeof(Indexed),compara); // Ordena o arquivo de indices
	printf("Ordered = OK\n");

	f = fopen("if_ordered.dat","wb");   // Abre o arquivo de indices ordenado
	fwrite(e,sizeof(Indexed),qtd,f);    // Escreve o arquivo de indices ordenado
	fclose(f);                          // Fecha o arquivo de indices ordenado

	printf("Written = OK\n");
	free(e);

	return 0;
}

int create_index(FILE *f)
{
	FILE *f_index;      // Arquivo de indices
	Indexed *e;         // Endereco auxiliar
	Endereco *e2;       // Endereco auxiliar
	int count;          // Contador de registros
  int chunk = 100;    // Tamanho do chunk

  e = malloc(sizeof(Indexed));
  e2 = malloc(sizeof(Endereco));

	count = 0;
	f_index = fopen("if.dat","wb");
	while(fread(e2,sizeof(Indexed),1,f) == 1)
  {
		strcpy(e->cep,e2->cep);
		e->index = count;
		fwrite(e,sizeof(Indexed),1,f_index);
		count++;
	}

  free(e);
  free(e2);
	fclose(f_index);
	return (count+1); // Retorna a quantidade de registros
}