#include <stdio.h>
#include <stlib.h>
#include <ctype.h>

#define CD 1
#define DIR 2
#define RM 3
#define MKDIR 4
#define MKFILE 5
#define EDIT 6
#define MOVE 7
#define RENAME 8

typedef struct Cluster{
    char flag_dir_arq;
    char nomeArquivo[32];
    int conteudo[256];

} STRUCT;


cd(char nome_do_arquvio){
    if(existe_arquivo(nome_do_arquivo){

    }else{
}

dir(char nome_do_arquvio){
    if(existe_arquivo(nome_do_arquivo){

    }else{
}

rm(char nome_do_arquvio){
    if(existe_arquivo(nome_do_arquivo){

    }else{
}

mkdir(char nome_do_arquvio){
    if(existe_arquivo(nome_do_arquivo){

    }else{
}

mkfile(char nome_do_arquvio){
    if(existe_arquivo(nome_do_arquivo){

    }else{
}

rm(char nome_do_arquvio){
    if(existe_arquivo(nome_do_arquivo){

    }else{
}

int main(){

    char string[];
    FILE arq;

    scanf("%s", &string[0]);
    toupper(string);

    switch(string)
    {
        case 1: cd(params);
                break;

        case 2: dir(params);
                break;

        case 3: rm(params);
                break;

        case 4: mkdir(params);
                break;

        case 5: mkfile(params);
                break;

        case 6: edit(params);
                break;

        case 7: move(params);
                break;

        case 8: rename(params);
                break;
    }

    return 1;
}
