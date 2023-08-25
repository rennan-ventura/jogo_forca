#include<stdio.h>
#include<string.h>

char palavrasecreta[20];
char chutes[26];
int tentativas = 0;

void abertura(){
    printf("*********************\n");
    printf("*   Jogo de Forca   *\n");
    printf("*********************\n\n");
}

void chuta(){
    char chute;
    printf("Chute a letra: ");
    scanf(" %c", &chute);

    chutes[tentativas] = chute;
    tentativas++;
}

int jaChutou(char letra){
    int achou = 0;

    for(int j = 0; j < tentativas; j++){
        if(chutes[j] == letra){
            achou = 1;
            break;
        }
    }
    return achou;
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

void escolhePalavra(){
    sprintf(palavrasecreta, "MELANCIA");
}

int main(){
    int acertou = 0;
    int enforcou = 0;

    escolhePalavra();
    abertura();

    do {
        desenhaForca();
        printf("\n");

        chuta();
        
        
    } while(!acertou && !enforcou);
}