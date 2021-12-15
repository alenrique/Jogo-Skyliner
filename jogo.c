#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "jogo.h"
#include "lista.h"
#include "pilha.h"

struct jogador{
    Lista *pecas;
    int id;
    int andar;//vale 1
    int teto;//vale 0
    int parque;//vale 2
};

struct matriz{
    Pilha ***tab;
    int l;
    int c;
};

Jogador* criar_jogador(int id){
    int a,t,p,i;
    a = 12;
    t = 2;
    p = 1;
    Jogador *jog;
    jog = (Jogador*)malloc(sizeof(Jogador));
    jog->pecas = criar_lista();
    for(i = 0; i < t; i++){
        inserir_lista(jog->pecas,0);
    }
    for(i = 0; i < a; i++){
        inserir_lista(jog->pecas,1);
    }
    for(i = 0; i < p; i++){
        inserir_lista(jog->pecas,2);
    }
    jog->id = id;
    jog->andar = a;
    jog->teto = t;
    jog->parque = p;
    return jog;
}

Matriz *criar_tabuleiro(){
    int i,j;
    Matriz *mat;
    mat = (Matriz*)malloc(sizeof(Matriz));
    if(mat == NULL){
        return NULL;
    }
    mat->l = LINHA;
    mat->c = COLUNA;
    mat->tab = (Pilha***)malloc(mat->l*sizeof(Pilha**));
    if(mat->tab == NULL){
        return NULL;
    }
    for(i = 0; i < mat->l; i++){
        mat->tab[i] = (Pilha**)malloc(mat->c*sizeof(Pilha*));
    }
    for(i = 0; i < mat->l; i++){
        for(j = 0; j < mat->c; j++){
            mat->tab[i][j] = criar_pilha();
        }
    }
    return mat;

}

int imprimir_tabuleiro(Matriz *mat){
    system("cls");
    int i,j,t,p;
    printf("\n\n");
    printf("\t\t\tNorte");
    printf("\n\n");
    printf("\t\t+---+---+---+---+---+\n");
    for(i = 0; i < mat->l; i++){
        printf("\t");
        if(i == 2){
            printf("Oeste");
        }
        printf("\t|");
        for(j = 0; j < mat->c; j++){
            t = tamanho_pilha(mat->tab[i][j]);
            p = primeiro_pilha(mat->tab[i][j]);
            if(t == 0){
                printf("   |");
            }
            else{
                if(p == 1){
                    printf(" %d |",t);
                }
                else{
                    printf("[%d]|",t);
                }
            }
        }
        printf(" %c", 97 + i);
        if(i == 2){
            printf("\t  Leste");
        }
        printf("\n");
        printf("\t\t+---+---+---+---+---+\n");
    }
    printf("\t\t  ");
    for(i = 0; i < mat->c; i++){
        printf("%d   ",i + 1);
    }
    printf("\n\n");
    printf("\t\t\t Sul");
    printf("\n\n");
    return 1;
}

int inserir_peca(Matriz *mat,int l, int c, int num){
    int p,t;
    p = primeiro_pilha(mat->tab[l][c]);
    t = tamanho_pilha(mat->tab[l][c]);
    switch(num){
        case 0:
            if(t > 0 && p == 1){
                inserir_pilha(mat->tab[l][c],num);
                return 1;
            }
            else{
                return 0;
            }
        case 1:
            if(t == 0 || p == 1){
                inserir_pilha(mat->tab[l][c],num);
                return 1;
            }
            else{
                return 0;
            }
        case 2:
            if(t == 0){
                inserir_pilha(mat->tab[l][c],num);
                return 1;
            }
            else{
                return 0;
            }
        default:
            return 0;
    }
}

int distribuir(Matriz *mat){
    inserir_peca(mat,2,2,2);
    srand(time(0));
    int lin,col,tipo,i,ver;
    for(i = 0; i < 5; i++){
        lin = (rand() % 3) + 1;
        col = (rand() % 3) + 1;
        tipo = rand() % 2;
        ver = inserir_peca(mat,lin,col,tipo);
        if(ver == 0){
            i--;
            continue;
        }
    }
    return 1;
}

int linha_tabuleiro(char c){
        int n;
        if(c == 'a'){
            n = 0;
        }
        else if(c == 'b'){
            n = 1;
        }
        else if(c == 'c'){
            n = 2;
        }
        else if(c == 'd'){
            n = 3;
        }
        else if(c == 'e'){
            n = 4;
        }
        else{
            n = -1;
        }
        return n;
}

int coluna_tabuleiro(char c){
        int n;
        if(c == '1'){
            n = 0;
        }
        else if(c == '2'){
            n = 1;
        }
        else if(c == '3'){
            n = 2;
        }
        else if(c == '4'){
            n = 3;
        }
        else if(c == '5'){
            n = 4;
        }
        else{
            n = -1;
        }
        return n;
}

int validar_jogada(Jogador *jog, Matriz *tabuleiro, int ur){
        int l,c,verif,peca,p,fimdajogada,voltar,pon;
        char posicao[2];
        fimdajogada = 1;
        while(fimdajogada != 0){
            voltar = 0;
            if(ur == 0){
                printf("\t\t  [ULTIMA RODADA]\n\n");
            }
            if(jog->id == 1){
                printf("\t\tVez do Jogador Sul \n\n");
            }
            else if(jog->id == 2){
                printf("\t\tVez do Jogador Leste \n\n");
            }
            else if(jog->id == 3){
                printf("\t\tVez do Jogador Norte \n\n");
            }
            else{
                printf("\t\tVez do Jogador Oeste \n\n");
            }
            while(1){
                printf(" 0-Teto[%d] 1-Andar[%d] 2-Parque[%d] 3-Sua Vista \n\n",jog->teto,jog->andar,jog->parque);
                printf("Selecione a opcao: ");
                scanf("%d",&peca);
                while (getchar() != '\n');
                p = peca;
                if(p == 3){
                    pon = pontos(jog,tabuleiro,1);
                    printf("Pontos: %d \n\n",pon);
                    continue;
                }
                printf("\n");
                if(p == 0 && jog->teto == 0){
                    printf("Voce nao tem mais pecas do tipo teto \n\n\n");
                    continue;
                }
                else if(p == 2 && jog->parque == 0){
                    printf("Voce nao tem mais pecas do tipo parque \n\n\n");
                    continue;
                }
                else if(p >= 0 && p <= 2){
                    break;
                }
                else{
                    printf("Comando Invalido! \n\n\n");
                    continue;
                }
            }
            while(1){
                printf(" 0-Voltar \n\n");
                printf("Digite a posicao: ");
                scanf("%s",posicao);
                while (getchar() != '\n');
                printf("\n");
                if(posicao[0] == '0'){
                    voltar = 1;
                    break;
                }
                l = linha_tabuleiro(posicao[0]);
                c = coluna_tabuleiro(posicao[1]);
                if(l == -1 || c == -1){
                    printf("Comando Invalido! \n\n\n");
                    continue;
                }
                verif = inserir_peca(tabuleiro,l,c,p);
                if(verif == 0){
                    printf("Posicao Invalida! \n\n\n");
                    continue;
                }
                else{
                    remover_lista(jog->pecas,p);
                    if(p == 0){
                        jog->teto--;
                    }
                    else if(p == 1){
                        jog->andar--;
                    }
                    else{
                        jog->parque--;
                    }
                    break;
                }
            }
            imprimir_tabuleiro(tabuleiro);
            if(voltar == 1){
                continue;
            }
            else{
                fimdajogada = 0;
                break;
            }
        }
        return 1;
}

int pontos(Jogador *jog, Matriz *mat, int ativar){
    if(jog == NULL || mat == NULL){
        return 0;
    }
    int i,j,altura,cont,t,linha,coluna,li,co,k,sobra,ver,v,vis,lc,traco;
    int vista[5][10];
    for(i = 0; i < 5; i++){
        for(j = 0; j < 10; j++){
            vista[i][j] = 0;
        }
    }
    switch(jog->id){
        case 1:
            linha = 5;
            coluna = -1;
            li = 0;
            co = 4;
            break;

        case 2:
            linha = -1;
            coluna = -1;
            li = 4;
            co = 4;
            lc = 0;
            break;

        case 3:
            linha = -1;
            coluna = 5;
            li = 4;
            co = 0;
            vis = 4;
            lc = 0;
            break;

        default:
            linha = 5;
            coluna = 5;
            li = 0;
            co = 0;
            vis = 4;
            break;
    }
    cont = 0;
    i = li;
    while(i != linha){
        altura = 0;
        j = co;
        v = vis;
        while(j != coluna){
            if(jog->id == 1 || jog->id == 3){
                t = tamanho_pilha(mat->tab[j][i]);
                if(altura < t){
                    altura = t;
                    cont++;
                    for(k = 0; k < t; k++){
                        if(jog->id == 1){
                            if(vista[i][k] != 0){
                                continue;
                            }
                            vista[i][k] = j+1;
                        }
                        else{
                            if(vista[lc][k] != 0){
                                continue;
                            }
                            vista[lc][k] = v+1;
                        }
                    }
                }
            }
            else{
                t = tamanho_pilha(mat->tab[i][j]);
                if(altura < t){
                    altura = t;
                    cont++;
                    for(k = 0; k < t; k++){
                        if(jog->id == 4){
                            if(vista[i][k] != 0){
                                continue;
                            }
                            vista[i][k] = v+1;
                        }
                        else{
                            if(vista[lc][k] != 0){
                                continue;
                            }
                            vista[lc][k] = j+1;
                        }
                    }
                }
            }
            v--;
            if(jog->id == 1 || jog->id == 2){
                j--;
            }
            else{
                j++;
            }
        }
        if(jog->id == 2 || jog->id == 3){
            i--;
            lc++;
        }
        else{
            i++;
            lc--;
        }
    }
    if(ativar == 1){
        for(i = 9; i >= 0; i--){
            printf("");
            for(j = 0; j < 5; j++){
                if(vista[j][i] == 0){
                    printf("  ");
                    for(k = 1; k < vista[j][0]; k++){
                        printf("  ");
                    }
                    continue;
                }
                else{
                    printf(" ");
                    ver = 0;
                    if(vista[j][i] < vista[j][0]){
                        ver = 1;
                        sobra = (vista[j][0] - vista[j][i]);
                        for(k = 0; k < sobra; k++){
                            printf(" ");
                        }
                    }
                    printf("#");
                    for(k = 1; k < vista[j][i]; k++){
                        printf("##");
                    }
                    if(ver == 1){
                        for(k = 0; k < sobra; k++){
                            printf(" ");
                        }
                    }
                }
            }
            printf("\n");
        }
        traco = 15;
        for(k = 0; k < 5; k++){
            if(vista[k][0] == 0){
                traco-=2;
            }else{
                traco = traco + vista[k][0];
            }
        }
        printf("  ");
        for(k = 0; k < traco; k++){
            printf("-");
        }
        printf("\n");
    }
    return cont;
}

int jogo(){
    int rodada,l,maiorp,i,p,vencedor;
    int pont[4];
    maiorp = 0;
    rodada = 1;
    Matriz *tabuleiro;
    tabuleiro = criar_tabuleiro();
    distribuir(tabuleiro);
    Jogador *jogador_sul = criar_jogador(1);
    Jogador *jogador_leste = criar_jogador(2);
    Jogador *jogador_norte = criar_jogador(3);
    Jogador *jogador_oeste = criar_jogador(4);
    imprimir_tabuleiro(tabuleiro);
    while(rodada != 0){
        validar_jogada(jogador_sul,tabuleiro,rodada);
        if(jogador_sul->andar == 0){
            rodada = 0;
        }
        validar_jogada(jogador_leste,tabuleiro,rodada);
        if(jogador_leste->andar == 0){
            rodada = 0;
        }
        validar_jogada(jogador_norte,tabuleiro,rodada);
        if(jogador_norte->andar == 0){
            rodada = 0;
        }
        validar_jogada(jogador_oeste,tabuleiro,rodada);
        if(jogador_oeste->andar == 0){
            rodada = 0;
        }
    }
    pont[0] = pontos(jogador_sul,tabuleiro,0);
    pont[1] = pontos(jogador_leste,tabuleiro,0);
    pont[2] = pontos(jogador_norte,tabuleiro,0);
    pont[3] = pontos(jogador_oeste,tabuleiro,0);
    for(i = 0; i < 4; i++){
        if(maiorp < pont[i]){
            maiorp = pont[i];
            vencedor = i;
        }
    }
    switch(vencedor){
        case 0:
            printf("Vencedor: Jogador Sul \n\nOlha essa vista:");
            p = pontos(jogador_sul,tabuleiro,1);
            printf("Pontos: %d\n",p);
            break;

        case 1:
            printf("Vencedor: Jogador Leste \n\nOlha essa vista:");
            p = pontos(jogador_leste,tabuleiro,1);
            printf("Pontos: %d\n",p);
            break;

        case 2:
            printf("Vencedor: Jogador Norte \n\nOlha essa vista:");
            p = pontos(jogador_norte,tabuleiro,1);
            printf("Pontos: %d\n",p);
            break;

        default:
            printf("Vencedor: Jogador Oeste \n\nOlha essa vista:");
            p = pontos(jogador_oeste,tabuleiro,1);
            printf("Pontos: %d\n",p);
            break;
    }
    return 1;
}
