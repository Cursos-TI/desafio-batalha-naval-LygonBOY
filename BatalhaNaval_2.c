#include <stdio.h>

#define TAM 10
#define NAVIO 3

int main() {
    int tabuleiro[TAM][TAM];
    int i, j;

    // INICIALIZA O TABULEIREO COM ÁGUA (0)
    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // POSICIONA OS 4 NAVIOS

    //PRIMEIRO NAVIO HORIZONTAL (TAMANHO 3)
    int linhaH = 1, colunaH = 2;
    for (i = 0; i < NAVIO; i++) {
        tabuleiro[linhaH][colunaH + i] = 3;
    }

    // SEGUNDO NAVIO VERTICAL (TAMANHO 3)
    int linhaV = 4, colunaV = 7;
    for (i = 0; i < NAVIO; i++) {
        tabuleiro[linhaV + i][colunaV] = 3;
    }

    // TERCEIRO NAVIO DIAGONAL PRINCIPAL (LINHA E COLUNA CRESCEM)
    int linhaD1 = 0, colunaD1 = 0;
    for (i = 0; i < NAVIO; i++) {
        tabuleiro[linhaD1 + i][colunaD1 + i] = 3;
    }

    // QUARTO NAVIO DIAGONAL SECUNDÁRIA (LINHA CRESCE COLUNA CRESCE)
    int linhaD2 = 6, colunaD2 = 9;
    for (i = 0; i < NAVIO; i++) {
        tabuleiro[linhaD2 + i][colunaD2 + i] = 3;
    }

    // EXIBE O TABULEIRO
    printf("TABULEIRO BATALHA NAVAL (0 = ÁGUA | 3 = NAVIO)\n\n");

    for (i = 0; i < TAM; i++) {
        for (j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}
