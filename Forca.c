#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"forca.h"


char palavrasecreta[20];
char chutes[26];
int chutesdados = 0;

void abertura(){
    printf("*********************\n");
    printf("*   Jogo de Forca   *\n");
    printf("*********************\n\n");
}

void chuta(){
    char chute;
    printf("Chute a letra: ");
    scanf(" %c", &chute);

    chutes[chutesdados] = chute;
    chutesdados++;
}

void desenhaForca(){
    for(int i = 0; i < strlen(palavrasecreta); i++){
    
        int achou = jaChutou(palavrasecreta[i]);
        if(achou){
            printf("%c ", palavrasecreta[i]);
        } else{
            printf("_ ");
        }
    }
}

void adicionapalavra(){
    char sim;
    printf("Gostaria de adicionar uma palavra? (S/N)");
    scanf(" %c", &sim);

    if(sim == 'S'){

        char novapalavra[20];
        printf("Qual a nova palavra? ");
        scanf("%s", novapalavra);

        FILE* f = fopen("palavras.txt", "r+");
        if(f == 0){
            printf("Desculpe, banco de dados nao disponivel");
            exit(1);
        }

        int qtd;
        fscanf(f, "%d", &qtd);
        qtd++;

        fseek(f, 0, SEEK_SET);
        fprintf(f, "%d", qtd);

        fseek(f, 0, SEEK_END);
        fprintf(f, "\n%s", novapalavra);
        fclose(f);
    }
}


void escolhePalavra(){
    //sprintf(palavrasecreta, "MELANCIA");
    FILE* f = fopen("palavras.txt", "r");

    if(f == 0){
        printf("Desculpe, banco de dados nao disponivel!!\n\n");
        exit(1);
    }

    int qtdpalavras;
    fscanf(f, "%d", &qtdpalavras);

    srand(time(0));
    int randomico = rand() % qtdpalavras;

    for(int i = 0; i <= randomico; i++){
        fscanf(f, "%s", palavrasecreta);
    }

    fclose(f);
}

int acertou(){
    for(int i = 0; i < strlen(palavrasecreta); i++){
        if(!jaChutou(palavrasecreta[i])){
            return 0;
        }
    }
    return 1;
}

int enforcou(){

    int erros = 0;

    for(int i = 0; i < chutesdados; i++){
        int existe = 0;

        for(int j = 0; j < strlen(palavrasecreta); j++){
            if(jaChutou(palavrasecreta[i])){

                existe = 1;
                break;
            }
        }
        if(!existe) erros++;

    }
    return erros >= 5;
}

int jaChutou(char letra){
    int achou = 0;

    for(int j = 0; j < chutesdados; j++){
        if(chutes[j] == letra){
            achou = 1;
            break;
        }
    }
    return achou;
}

int main(){

    escolhePalavra();
    abertura();

    do {

        desenhaForca();
        printf("\n");
        chuta();
        
    } while(!acertou() && !enforcou());
}