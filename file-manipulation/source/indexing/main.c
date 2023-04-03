/*
    [GRAD EXEC]
*/

#include "address_index.h"      // compare, sort_index, create_index, search_index
#include <stdio.h>              // printf, scanf, fopen, fclose

int main() {
    FILE *f1 = fopen("files/cep.dat","rb"); // Abre o arquivo de dados

    if(f1 == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    create_index(f1);                       // Cria o arquivo de indices

    FILE *f2 = fopen("if.dat","rb");        // Abre o arquivo de indices

    if(f2 == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    sort_index(f2);                        // Ordena o arquivo de indices
    fclose(f2);                            // Fecha o arquivo de indices

    f2 = fopen("if_ordered.dat","rb");     // Abre o arquivo de indices ordenados

    if(f2 == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    while(1) {
        char cep[9] = {'a'};
        printf("Find address by CEP (0 to exit): ");
        scanf("%s",cep);                   // Le o CEP

        while(cep[0] < '0' || cep[0] > '9') { // Verifica se o CEP e valido
            printf("Invalid CEP. Try again: ");
            scanf(" %s",cep);
        }

        if(cep[0] == '0') break;

        int c;
        while ((c = getchar()) != '\n' && c != EOF) {} // Limpa o buffer

        printf("Choose the search mode (0 to go back):\n");
        printf("s - Sequential search\n");
        printf("b - Binary search\n\n");
        
        char mode;
        scanf(" %c",&mode);               // Le o modo de busca

        while(mode != 's' && mode != 'b' && mode != '0') {
            printf("Invalid mode. Try again: ");
            scanf(" %c",&mode);
        }

        if(mode == '0') continue;

        int pos = search_index(f2,cep,mode); // Busca o CEP
        if(pos == -1) {
            printf("CEP not found at all :(\n");
        } else {
            printf("CEP found at line %d\n",pos);
            search_data(f1,pos);              // Busca o endereco
        }

    }

    fclose(f1);                           // Fecha o arquivo de dados
    fclose(f2);                           // Fecha o arquivo de indices ordenados

    return 0;
}