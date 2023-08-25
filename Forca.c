#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include"forca.h"


char palavrasecreta[TAMANHO_PALAVRA];
char chutes[26];
int chutesdados = 0;

void abertura(){
    printf("*********************\n");
    printf("*   Jogo de Forca   *\n");
    printf("*********************\n\n");
}

void chuta(){
    char chute;
    printf("\nChute a letra: ");
    scanf(" %c", &chute);

    chutes[chutesdados] = chute;
    chutesdados++;
}

void desenhaForca(){


    int erros = chutesErrados();
    printf("  _______       \n");
    printf(" |/      |      \n");
    printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
    printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
    printf(" |       %c     \n", (erros>=2?'|':' '));
    printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
    printf(" |              \n");
    printf("_|___           \n");
    printf("\n\n");


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

        char novapalavra[TAMANHO_PALAVRA];
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

int chutesErrados(){
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
    return erros;
}

int enforcou(){

    return chutesErrados() >= 5;
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
    if(acertou()) {


        printf("Parabens, voce ganhou!\n");
        printf("\n");
        printf("       ___________      \n");
        printf("      '._==_==_=_.'     \n");
        printf("      .-\\:      /-.     \n");
        printf("     | (|:.     |) |    \n");
        printf("      '-|:.     |-'     \n");
        printf("        \\::.    /       \n");
        printf("         '::. .'        \n");
        printf("           ) (          \n");
        printf("         _.' '._        \n");
        printf("        '-------'       \n");
        printf("\n");

        adicionapalavra();


    } else {

        printf("Puxa, voce foi enforcado!\n");
        printf("A palavra secreta era **%s**\n\n", palavrasecreta);
        printf("        _______________         \n");
        printf("       /               \\        \n");
        printf("      /                 \\       \n");
        printf("    //                   \\/\\    \n");
        printf("    \\|   XXXX     XXXX   | /    \n");
        printf("     |   XXXX     XXXX   |/     \n");
        printf("     |   XXX       XXX   |      \n");
        printf("     |                   |      \n");
        printf("     \\__      XXX      __/      \n");
        printf("       |\\     XXX     /|        \n");
        printf("       | |           | |        \n");
        printf("       | I I I I I I I |        \n");
        printf("       |  I I I I I I  |        \n");
        printf("       \\_             _/        \n");
        printf("         \\_         _/          \n");
        printf("           \\_______/            \n");
        printf("\n\n");

    }
}