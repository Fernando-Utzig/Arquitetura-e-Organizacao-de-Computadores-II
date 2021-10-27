#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BITS 8388608

char vet_bits[BITS-32768];

typedef struct{
    char index_size;
    char cluster_size;
    char index_pt;
    char root_pt;
}Meta;

typedef struct{
    char arq_name[20]; //20
    char extension[3]; //3
    char pointer; //1
    char content[32744]; //32768 - 24 = 32744
    //32768
}Cluster;

int main() {
    FILE *arq;
    Meta meta;
    Cluster cluster;
    int i;
    meta.index_size = 0xFF;
    meta.cluster_size = 0x0F;
    meta.index_pt = 0x04;
    meta.root_pt = 0x00;
    char eof = 0xFF, empty = 0x00;

    arq = fopen("arquivo.bin", "wb");
    if (arq == NULL) printf("Problemas na abertura do arquivo\n");

    fwrite(&meta,sizeof(meta),1,arq);
    fwrite(&eof, sizeof(char),1, arq );
    //0xFF - eof
    //0xFE - corrompido
    //0x?? - ocupado
    //0x00 - vazio
    for (i=0; i<255; i++){
        fwrite(&empty,sizeof(char),1,arq);
    }

    strcpy(cluster.arq_name,"root");
    strcpy(cluster.extension,"dir");
    memset(cluster.content,0,sizeof(cluster.content));
    cluster.pointer=0x00;

    fwrite(&cluster,32768,1,arq);
    fwrite(vet_bits,sizeof(vet_bits),1,arq);

    fclose(arq);

    return 0;
}