#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#define BITS 8388608
#define CONTENT 32744

char *token[3];
int actual_offset;

typedef struct{
    int index_size;
    int cluster_size;
    int index_pt;
    int root_pt;
    char directory[200];
}Meta;

typedef struct{
    char arq_name[20]; //20
    char extension[3]; //3
    char pointer; //1
    char content[32744]; //32768 - 24 = 32744
    //32768
}Cluster;

    //0xFF - eof
    //0xFE - corrompido
    //0x?? - ocupado
    //0x00 - vazio

Meta meta;

char *strsep(char **stringp, const char *delim) {
  if (*stringp == NULL) { return NULL; }
  char *token_start = *stringp;
  *stringp = strpbrk(token_start, delim);
  if (*stringp) {
    **stringp = '\0';
    (*stringp)++;
  }
  return token_start;
}

char *strdup(const char *src) {
    char *dst = malloc(strlen (src) + 1);  // Space for length plus nul
    if (dst == NULL) return NULL;          // No memory
    strcpy(dst, src);                      // Copy the characters
    return dst;                            // Return the new string
}


void separaString(){

    char cmd_str[125];

    while (!fgets(cmd_str, 125, stdin));

    int token_count = 0;
    char *arg_ptr;
    char *working_str = strdup(cmd_str);
    char *working_root = working_str;

    while (((arg_ptr = strsep(&working_str, " \n\t")) != NULL) &&
           (token_count < 3))
    {
        token[token_count] = strdup(arg_ptr);
        if (strlen(token[token_count]) == 0)
        {
            token[token_count] = NULL;
        }
        token_count++;
    }

    for (int i=0; i<token_count; i++){
        printf("\n%s", token[i]);
    }

    free(working_root);

}

int seekDir(char *directory){

    char *directories[20], *actual_directories[19];
    int token_count = 0, j = 0, i, offset= meta.index_size+meta.index_pt;
    char *arg_ptr;
    char *working_str = strdup(directory);
    char *working_root = working_str;

    while ((arg_ptr = strsep(&working_str, "/")) != NULL){
        directories[token_count] = strdup(arg_ptr);
        if (strlen(directories[token_count]) == 0)
        {
            directories[token_count] = NULL;
        }
        token_count++;
    }

    for (i=0; i<token_count; i++){
        if(directories[i]!=NULL) {
            actual_directories[j]=directories[i];
            j++;
        }
    }

    free(working_root);

    FILE *arq;
    unsigned char ext[3], dir_name[20], pointers[32744], end;
    int count=0, offset_aux;

    arq = fopen("arquivo.bin", "rb");
    if (arq == NULL) printf("não abriu");

    for(i=0; i<j ; i++){

        fseek(arq, offset,SEEK_SET);
        if(fread(dir_name, 20, 1, arq)!=1) printf("não leu");
        if(strcmp(actual_directories[i], dir_name)){
            return -1;
        }else{
            if(fread(ext, 3, 1, arq)!=1) printf("não leu");
            printf("\nftell:%d", ftell(arq));
            if(strcmp("dir", ext)){
                return -2;
            }else{
                fseek(arq, 1,SEEK_CUR);
                printf("\n%d", ftell(arq));
                if(fread(pointers, 32744, 1, arq)!=1) printf("não leu");
                for (int k=0; k<32744; k++){
                    if(pointers[k]!=0) {
                        offset_aux=(int)pointers[k]+meta.index_pt;
                        fseek(arq, offset_aux, SEEK_SET);
                        if(fread(&end, 1, 1, arq)!=1) printf("não leu");
                        offset_aux=meta.index_size+meta.index_pt+(int)end*32768;
                        fseek(arq, offset_aux, SEEK_SET);
                        memset(dir_name, '\0', 20);
                        if(fread(dir_name, 20, 1, arq)!=1) printf("não leu");
                        if(!strcmp(actual_directories[i+1], dir_name)) offset = meta.index_size+meta.index_pt+(int)end*32768;
                        count++;
                    }
                }
                if(count==0){
                    printf("\n<vazio>");
                }
            }
        }
    }

    fclose(arq);

    return offset;

}

void cd(){

    int offset = seekDir(meta.directory);

    printf("\nOFFSET: %d", offset);

    FILE *arq;
    unsigned char buffer[32744];
    arq = fopen("arquivo.bin", "rb");

    if (arq == NULL) printf("não abriu");
    fseek(arq,meta.index_size+meta.index_pt,SEEK_SET);


    for (int i=0; i<32744; i++){
        fread(pt_buffer, 1, 1, arq);
        if(pt_buffer[i]!=0){
            printf("\n%x", pt_buffer[i]);
        }
    }

    fclose(arq);
    free(pt_buffer);


}

void ls(){


}

void getInfo(){

    FILE *arq;
    unsigned char ch[4], root[20];
    int teste;
    arq = fopen("arquivo.bin", "rb");

    if (arq == NULL) printf("não abriu");
    if(fread(ch, 4, 1, arq)!=1) printf("não leu");

    meta.index_size = ch[0] + 1;
    meta.cluster_size= pow(2,ch[1]);
    meta.index_pt = ch[2];
    meta.root_pt = ch[3];

    fseek(arq,meta.index_size+meta.index_pt,SEEK_SET);

    if(fread(root, 20, 1, arq)!=1) printf("não leu");

    strcpy(meta.directory,"/");
    strcat(meta.directory,root);

    fclose(arq);

}

int main(){


    //FILE arq;

    getInfo();
    separaString();

    int numero=0;

    if(stricmp(token[0], "CD")==0){
        cd();
    }
    else if(stricmp(token[0], "DIR")==0){
        ls();
    }
    else if(stricmp(token[0], "RM")==0){
        numero=3;
    }
    else if(stricmp(token[0], "MKDIR")==0){
        numero=4;
    }
    else if(stricmp(token[0], "MKFILE")==0){
        numero=5;
    }
    else if(stricmp(token[0], "EDIT")==0){
        numero=6;
    }
    else if(stricmp(token[0], "MOVE")==0){
        numero=7;
    }
    else if(stricmp(token[0], "RENAME")==0){
        numero=8;
    }
    else{
        printf("\nComando invalido\n");
        numero=-1;
    }

    return 0;
}
