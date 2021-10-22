#include <stdio.h>
#include <stdlib.h>
#define NOTAS 8388868

int notas[NOTAS];

int main() {
    FILE *arq;
    arq = fopen("arquivo.bin", "wb");
    int i;

    for (i=0; i<NOTAS-1; i++)
    {
        notas[i] = 0;
    }

    if (arq == NULL)
    {
        printf("Problemas na abertura do arquivo\n");
        return 1;
    }

    fwrite(notas,sizeof(notas),1,arq);
    fclose(arq);

    return 0;
}
