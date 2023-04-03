#ifndef ADDRESS_INDEX_H
#define ADDRESS_INDEX_H

#include <stdio.h> 			// printf, scanf, fopen, fclose

typedef struct _Endereco Endereco;
typedef struct _Indexed Indexed;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};

struct _Indexed
{
	char cep[8];
	int index;
};

int compare(const void *e1, const void *e2);

int sort_index(FILE *f);

int create_index(FILE *f);

int search_index(FILE *f, char *cep, char mode);

int search_data(FILE *f, int index);

#endif /* ADDRESS_INDEX_H */
