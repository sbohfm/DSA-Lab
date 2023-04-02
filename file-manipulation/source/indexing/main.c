#include <stdio.h>
#include "address_index.h"

int main() {
    FILE *f = fopen("files/cep.dat","rb");

    if(f == NULL) {
        printf("Erro ao abrir arquivo\n");
        return 1;
    }

    create_index(f);
    fclose(f);

    f = fopen("if.dat","rb");

    if(f == NULL) {
        printf("Erro ao abrir arquivo\n");
        return 1;
    }

    sort_index(f);
    return 0;
}
