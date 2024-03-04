#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define TAM_MAX_MAO 21    \

struct PecasDomino{   // Base das pecas de domino
    int ladoDireito;
    int ladoEsquerdo;
};

struct jogador{
    struct PecasDomino mao[21];
    int tamMao; //Quantas pecas ela tem na mao
};

typedef struct PecasDomino pecasDomino; // Nomeia struct PecasDomino para apenas pecasDomino

pecasDomino mesa[28];

int tamanhoMesa;

struct jogador jogadores[2];

pecasDomino pecasDisponiveis[28] = {
        {0, 0},
        {0, 1},
        {0, 2},
        {0, 3},
        {0, 4},
        {0, 5},
        {0, 6},
        {1, 1},
        {1, 2},
        {1, 3},
        {1, 4},
        {1, 5},
        {1, 6},
        {2, 2},
        {2, 3},
        {2, 4},
        {2, 5},
        {2, 6},
        {3, 3},
        {3, 4},
        {3, 5},
        {3, 6},
        {4, 4},
        {4, 5},
        {4, 6},
        {5, 5},
        {5, 6},
        {6, 6}
};


void distribuicaoPecas(
        pecasDomino pecasDisponiveis[],
        int numeroPecasDisponiveis,
        int pecasParaDistribuir,
        int indiceJogador){

    srand(time(NULL)); //Inicializa o gerador de números aleatórios com o valor da função time(NULL).

    for(int i = 0; i < pecasParaDistribuir; i++){
        int pecaAleatoria = rand() % numeroPecasDisponiveis; // Aleatoriza as pecas disponiveis;
        jogadores[indiceJogador].mao[i] = pecasDisponiveis[pecaAleatoria];
        jogadores[indiceJogador].tamMao++;
        pecasDisponiveis[pecaAleatoria] = pecasDisponiveis[numeroPecasDisponiveis - 1]; //Substitui a peca que acabou de ser distribuida pela ultima peca na lista
        numeroPecasDisponiveis--; // Diminui a contagem das pecas disponiveis
    }
}


int determinarJogadorInicial() {
    int maiorDuplaJogador1 = 0;
    int indiceMaiorDuplaJogador1 = 0;
    int maiorDuplaJogador2 = 0;
    int indiceMaiorDuplaJogador2 = 0;

    for (int i = 0; i < 7; i++) {
        if (jogadores[0].mao[i].ladoEsquerdo == jogadores[0].mao[i].ladoDireito && jogadores[0].mao[i].ladoEsquerdo > maiorDuplaJogador1) {
            maiorDuplaJogador1 = jogadores[0].mao[i].ladoEsquerdo;
            indiceMaiorDuplaJogador1 = i;
        }
        if (jogadores[1].mao[i].ladoEsquerdo == jogadores[1].mao[i].ladoDireito && jogadores[1].mao[i].ladoEsquerdo > maiorDuplaJogador2) {
            maiorDuplaJogador2 = jogadores[1].mao[i].ladoEsquerdo;
            indiceMaiorDuplaJogador2= i;
        }
    }

    if (maiorDuplaJogador1 > maiorDuplaJogador2) {
        mesa[tamanhoMesa] = jogadores[0].mao[indiceMaiorDuplaJogador1]; // está atribuindo a peça escolhida à próxima posição disponível na mesa.
        tamanhoMesa++; // uma nova peça foi adicionada à mesa, portanto, o tamanho da mesa deve ser atualizado.
        jogadores[0].mao[indiceMaiorDuplaJogador1] = jogadores[0].mao[jogadores[0].tamMao-1]; //Substitui a peca que acabou de ser distribuida pela ultima peca na lista
        jogadores[0].tamMao--;// Diminui a contagem das pecas disponiveis
        return 1; // Jogador 1 tem a maior dupla, inicia o jogo.
    } else if (maiorDuplaJogador2 > maiorDuplaJogador1) {
        mesa[tamanhoMesa] = jogadores[1].mao[indiceMaiorDuplaJogador2];
        tamanhoMesa++;
        jogadores[1].mao[indiceMaiorDuplaJogador2] = jogadores[1].mao[jogadores[1].tamMao-1];
        jogadores[1].tamMao--;
        return 2; // Jogador 2 tem a maior dupla, inicia o jogo.
    }

    // Se nenhum jogador possui dupla, verifique a soma das peças.
    int maiorSomaJogador1 = 0;
    int indiceMaiorSomaJogador1 = 0;
    int maiorSomaJogador2 = 0;
    int indiceMaiorSomaJogador2 = 0;

    for (int i = 0; i < 7; i++) {
        if(maiorSomaJogador1 < jogadores[0].mao[i].ladoEsquerdo + jogadores[0].mao[i].ladoDireito){
            maiorSomaJogador1 = jogadores[0].mao[i].ladoEsquerdo + jogadores[0].mao[i].ladoDireito;
            indiceMaiorSomaJogador1 = i;
        }
        else if(maiorSomaJogador2 < jogadores[1].mao[i].ladoEsquerdo + jogadores[1].mao[i].ladoDireito){
            maiorSomaJogador2 = jogadores[1].mao[i].ladoEsquerdo + jogadores[1].mao[i].ladoDireito;
            indiceMaiorSomaJogador2 = i;
        }
    }

    if (maiorSomaJogador1 > maiorSomaJogador2) {
        mesa[tamanhoMesa] = jogadores[0].mao[indiceMaiorSomaJogador1]; // está atribuindo a peça escolhida à próxima posição disponível na mesa.
        tamanhoMesa++; // uma nova peça foi adicionada à mesa, portanto, o tamanho da mesa deve ser atualizado.
        jogadores[0].mao[indiceMaiorSomaJogador1] = jogadores[0].mao[jogadores[0].tamMao-1]; //Substitui a peca que acabou de ser distribuida pela ultima peca na lista
        jogadores[0].tamMao--;// Diminui a contagem das pecas disponiveis
        return 1; // Jogador 1 tem a maior soma, inicia o jogo.
    } else if (maiorSomaJogador2 > maiorSomaJogador1) {
        mesa[tamanhoMesa] = jogadores[1].mao[indiceMaiorSomaJogador2];
        tamanhoMesa++;
        jogadores[1].mao[indiceMaiorSomaJogador2] = jogadores[1].mao[jogadores[1].tamMao-1];
        jogadores[1].tamMao--;
        return 2; // Jogador 2 tem a maior soma, inicia o jogo.
    }

    // Se a soma também for igual, verifique a peça de maior número.
    int maiorNumeroPecaJogador1;
    int maiorNumeroPecaJogador2;

    if(jogadores[0].mao[indiceMaiorSomaJogador1].ladoEsquerdo > jogadores[0].mao[indiceMaiorSomaJogador1].ladoDireito){
        maiorNumeroPecaJogador1 = jogadores[0].mao[indiceMaiorSomaJogador1].ladoEsquerdo;
    }
    else{
        maiorNumeroPecaJogador1 = jogadores[0].mao[indiceMaiorSomaJogador1].ladoDireito;
    }
    if(jogadores[1].mao[indiceMaiorSomaJogador2].ladoEsquerdo > jogadores[1].mao[indiceMaiorSomaJogador2].ladoDireito){
        maiorNumeroPecaJogador2 = jogadores[1].mao[indiceMaiorSomaJogador2].ladoEsquerdo;
    }
    else{
        maiorNumeroPecaJogador2 = jogadores[1].mao[indiceMaiorSomaJogador2].ladoDireito;
    }
    if (maiorNumeroPecaJogador1 > maiorNumeroPecaJogador2) {
        mesa[tamanhoMesa] = jogadores[0].mao[indiceMaiorSomaJogador1]; // está atribuindo a peça escolhida à próxima posição disponível na mesa.
        tamanhoMesa++; // uma nova peça foi adicionada à mesa, portanto, o tamanho da mesa deve ser atualizado.
        jogadores[0].mao[indiceMaiorSomaJogador1] = jogadores[0].mao[jogadores[0].tamMao-1]; //Substitui a peca que acabou de ser distribuida pela ultima peca na lista
        jogadores[0].tamMao--;// Diminui a contagem das pecas disponiveis
        return 1; // Jogador 1 tem a peça de maior número, inicia o jogo.
    }
    else {
        mesa[tamanhoMesa] = jogadores[1].mao[indiceMaiorSomaJogador2];
        tamanhoMesa++;
        jogadores[1].mao[indiceMaiorSomaJogador2] = jogadores[1].mao[jogadores[1].tamMao-1];
        jogadores[1].tamMao--;
        return 2; // Jogador 2 inicia o jogo.
    }
}


void imprimirMesa(pecasDomino mesa[], int tamMesa) {
    printf("\n\n\nMesa:\n");
    for (int i = 0; i < tamMesa; i++) {
        printf("[%d|%d] ", mesa[i].ladoEsquerdo, mesa[i].ladoDireito);
    }
    printf("\n");
}


void imprimirPecasJogador(int indJogador) {
    for (int i = 0; i < jogadores[indJogador].tamMao; i++) {
        printf("[%d|%d] ", jogadores[indJogador].mao[i].ladoEsquerdo, jogadores[indJogador].mao[i].ladoDireito);
    }
    printf("\n");
}


int movimentoValido(pecasDomino peca, pecasDomino mesa[], int tamanhoMesa){
    if(tamanhoMesa == 0){ // Se a mesa estiver vazia, qualquer peça pode ser jogada
        return 1;
    } else {
        if (peca.ladoEsquerdo == mesa[0].ladoEsquerdo || peca.ladoEsquerdo == mesa[tamanhoMesa - 1].ladoDireito ||  // Verifica se a peça pode ser jogada no lado esquerdo ou direito da mesa
            peca.ladoDireito == mesa[0].ladoEsquerdo || peca.ladoDireito == mesa[tamanhoMesa - 1].ladoDireito){ // a mesa tiver três peças e tamanho for igual a 3, então a expressão mesa[tamanho - 1] se refere à última peça na mesa, que está no índice 2 (3 - 1).
            return 1;
        }
    }
    return 0;
}


void comprarPeca(int indiceJogador, pecasDomino peca){
    int numeroPecasDisponiveis = 28;
    jogadores[indiceJogador].mao[jogadores[indiceJogador].tamMao] = peca;
    jogadores[indiceJogador].tamMao++;
    peca = pecasDisponiveis[numeroPecasDisponiveis - 1]; //Substitui a peca que acabou de ser distribuida pela ultima peca na lista
    numeroPecasDisponiveis--; // Diminui a contagem das pecas disponiveis
}


 void inverterPeca(pecasDomino *peca) {
    int temp = peca->ladoEsquerdo;
    peca->ladoEsquerdo = peca->ladoDireito;
    peca->ladoDireito = temp;
}


    void selecaolado(int selecaoLado, int indexPecaEscolhida, int tamanhoMesa, int jogadorAtual){
       pecasDomino pecaEscolhida = jogadores[jogadorAtual].mao[indexPecaEscolhida];

    if (jogadores[jogadorAtual].mao[indexPecaEscolhida].ladoEsquerdo == mesa[0].ladoEsquerdo ||
        jogadores[jogadorAtual].mao[indexPecaEscolhida].ladoEsquerdo == mesa[tamanhoMesa - 1].ladoDireito ||
        jogadores[jogadorAtual].mao[indexPecaEscolhida].ladoDireito == mesa[0].ladoEsquerdo ||
        jogadores[jogadorAtual].mao[indexPecaEscolhida].ladoDireito == mesa[tamanhoMesa - 1].ladoDireito) {

        printf("Escolha o lado direito (1) ou esquerdo (2): ");
        scanf("%d", &selecaoLado);

        if (selecaoLado == 1) {
            if (jogadores[jogadorAtual].mao[indexPecaEscolhida].ladoEsquerdo == mesa[tamanhoMesa - 1].ladoDireito ||
                jogadores[jogadorAtual].mao[indexPecaEscolhida].ladoDireito == mesa[tamanhoMesa - 1].ladoDireito) {
                if (jogadores[jogadorAtual].mao[indexPecaEscolhida].ladoEsquerdo == mesa[tamanhoMesa - 1].ladoDireito) {
                    mesa[tamanhoMesa] = jogadores[jogadorAtual].mao[indexPecaEscolhida];
                    tamanhoMesa++;
                } else {
                    inverterPeca(&jogadores[jogadorAtual].mao[indexPecaEscolhida]);
                    mesa[tamanhoMesa] = jogadores[jogadorAtual].mao[indexPecaEscolhida];
                    tamanhoMesa++;
                    jogadores[jogadorAtual].mao[indexPecaEscolhida] = jogadores[jogadorAtual].mao[jogadores[jogadorAtual].tamMao - 1];
                    jogadores[jogadorAtual].tamMao--; //Após a substituição da peça escolhida pela última peça na mão, o tamanho da mão do jogador é reduzido em 1 
                }
            }
        } else if (selecaoLado == 2) {
            if (jogadores[jogadorAtual].mao[indexPecaEscolhida].ladoEsquerdo == mesa[0].ladoEsquerdo ||
                jogadores[jogadorAtual].mao[indexPecaEscolhida].ladoDireito == mesa[0].ladoEsquerdo) {
                if (jogadores[jogadorAtual].mao[indexPecaEscolhida].ladoDireito == mesa[0].ladoEsquerdo) {
                    inverterPeca(&jogadores[jogadorAtual].mao[indexPecaEscolhida]);
                }
                mesa[tamanhoMesa] = jogadores[jogadorAtual].mao[indexPecaEscolhida];
                tamanhoMesa++;
                jogadores[jogadorAtual].mao[indexPecaEscolhida] = jogadores[jogadorAtual].mao[jogadores[jogadorAtual].tamMao - 1];
                jogadores[jogadorAtual].tamMao--;
            }
        }
    }

    if (movimentoValido(pecaEscolhida, mesa, tamanhoMesa)) {
        mesa[tamanhoMesa] = pecaEscolhida;
        tamanhoMesa++;
        jogadores[jogadorAtual].mao[indexPecaEscolhida] = jogadores[jogadorAtual].mao[jogadores[jogadorAtual].tamMao - 1];
        jogadores[jogadorAtual].tamMao--;
    } else {
        printf("\nMovimento invalido. Tente novamente.\n");
        realizarTurno(jogadorAtual);
    }
}





void realizarTurno(int jogadorAtual) {
    //!!!int numeroPecasDisponiveis = numeroPecasDisponiveis - (jogadores[2].tamMao);
    imprimirMesa(mesa, tamanhoMesa);

    int indexPecaEscolhida;

    if (jogadorAtual == 0) {
        printf("\nJogador 1 - Suas pecas: \n");
        imprimirPecasJogador(0);
        printf("\nJogador 2 - Quantidade de peças: %d\n", jogadores[1].tamMao);
        //!!!printf("Pilha - Quantidade de peças: %d\n", numeroPecasDisponiveis);
    } else {
        printf("\nJogador 2 - Suas pecas: \n");
        imprimirPecasJogador(1);
        printf("\nJogador 1 - Quantidade de peças: %d\n", jogadores[0].tamMao);
        //!!!printf("Pilha - Quantidade de peças: %d\n", numeroPecasDisponiveis);
    }

    int tresAcoes;

    do{
        printf("\nJogar peca (1) | Comprar peca (2) | Passar a vez (3): ");
        scanf("%d", &tresAcoes);
    } while(tresAcoes < 1 || tresAcoes > 3);

     if (tresAcoes == 1) {
        int escolha;

        do {
            printf("\nEscolha uma peca para jogar entre 1 a %d: ", jogadores[jogadorAtual].tamMao);
            scanf("%d", &escolha);
        } while (escolha < 1 || escolha > jogadores[jogadorAtual].tamMao);

        pecasDomino pecaEscolhida = jogadores[jogadorAtual].mao[escolha - 1];

        for (indexPecaEscolhida = 0; indexPecaEscolhida < jogadores[jogadorAtual].tamMao; indexPecaEscolhida++) {
            if (jogadores[jogadorAtual].mao[indexPecaEscolhida].ladoEsquerdo == pecaEscolhida.ladoEsquerdo && jogadores[jogadorAtual].mao[indexPecaEscolhida].ladoDireito == pecaEscolhida.ladoDireito) {
                break; // Sai do loop quando encontra a peça escolhida
            }
        }

        if (movimentoValido(pecaEscolhida, mesa, tamanhoMesa)) {
            mesa[tamanhoMesa] = pecaEscolhida;
            (tamanhoMesa)++;
            jogadores[jogadorAtual].mao[indexPecaEscolhida] = jogadores[jogadorAtual].mao[jogadores[jogadorAtual].tamMao - 1];
            jogadores[jogadorAtual].tamMao--;
            int selecaoLado;
            selecaolado(selecaoLado, indexPecaEscolhida, tamanhoMesa, jogadorAtual);
        } else {
            printf("\nMovimento invalido. Tente novamente.\n");
            realizarTurno(jogadorAtual);
        }
    } else if (tresAcoes == 2) {
        int numeroPecasDisponiveis = 28;
        if (numeroPecasDisponiveis > 0) {
            int pecaAleatoria = rand() % numeroPecasDisponiveis;
            comprarPeca(jogadorAtual, pecasDisponiveis[pecaAleatoria]);
            printf("\n Jodador[%d] comprou peca. \n", jogadorAtual + 1);
        } else {
            printf("\n Nao ha mais pecas para comprar. \n");
            realizarTurno(jogadorAtual);
        }
    } else if (tresAcoes == 3) {
        if (jogadorAtual == 0) {
            printf("Jogador 1 passou a vez!\n");
            jogadorAtual = 1;
        } else {
            printf("Jogador 2 passou a vez!\n");
            jogadorAtual = 0;
        }
    } else {
        printf("Valor invalido. Tente novamente.\n");
        realizarTurno(jogadorAtual);
    }
}



   
int main() {
    int opcaoMenu;

    printf("\n");
    printf("1 - Começar novo jogo\n");
    printf("2 - Continuar jogo\n");
    printf("3 - Sair\n");

    printf("\nEscolha: ");
    scanf("%d", &opcaoMenu);

    switch(opcaoMenu){
        case 1:
            printf("\n-------------------------------------------------------\n\n");

            int numeroPecasDisponiveis = 28;
            int pecasParaCadaJogador = 7;
            distribuicaoPecas(pecasDisponiveis, numeroPecasDisponiveis, pecasParaCadaJogador, 0);
            distribuicaoPecas(pecasDisponiveis, numeroPecasDisponiveis - pecasParaCadaJogador, pecasParaCadaJogador,1);

            int jogadorInicial = determinarJogadorInicial();

            if (jogadorInicial == 1) {
                printf("Jogador 1 inicia o jogo!\n"); // Lógica do jogo para o jogador 1 iniciar.

                while(1){
                    realizarTurno(1);  // Jogador 1 vai lançar primeira peça do jogo, logo a jogada em seguida pertence ao jogador 2
                    realizarTurno(0);
                }
            } else {
                printf("Jogador 2 inicia o jogo!\n");  // Lógica do jogo para o jogador 2 iniciar.

                while(1){
                    realizarTurno(0);  // Jogador 2 vai lançar primeira peça do jogo, logo a jogada em seguida pertence ao jogador 1
                    realizarTurno(1);
                }
            }

            imprimirMesa(pecasDisponiveis, numeroPecasDisponiveis);
            break;

            //case 2: !!!ARQUIVO

        case 3:
            break;

        default:
            printf("Valor invalido. Tente novamente.\n");
            main();
    }
    return 0;
}
