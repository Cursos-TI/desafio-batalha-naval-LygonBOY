#include <stdio.h>
#include <stdlib.h>

#define TAM 10 // TAMANHO DO TABULEIRO (10X10)
#define NAVIO 3 // TAMANHO DO NAVIO (3 POSIÇÕES)
#define TAM_HAB 5 // TAMANHO DAS MATRIZES DE HABILIDADE (5X5)
#define EFEITO 5 // VALOR PARA MARCAR A ÁREA AFETADA POR UMA HABILIDADE

// FUNÇÃO PARAR A HABILIDADE - CONE
void criarCone(int hab[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            // EXPANDE A ÁREA DE CIMA PARA BAIXO COMO UM CONE
            if (j >= TAM_HAB/2 - i && j <= TAM_HAB/2 + i) {
                hab[i][j] = 1; // atinge essa posição
            } else
                hab[i][j] = 0; // Não atinge essa posição
        }
    }
}

// FUNÇÃO PARA CRIAR A HABILIDADE - CRUZ
void criarCruz(int hab[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            // Linhas e colunas centrais são atingidas
            if (i == TAM_HAB/2 || j == TAM_HAB/2) {
                hab[i][j] = 1;
            } else {
                hab [i][j] = 0;
            }
        }
    }
}

// FUNÇÃO PARA CRIAR A HABILIDADE - OCTAEDRO
void criarOctaedro(int hab[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int dist = abs(i - 2) + abs(j - 2); // distância até o centro
            if (dist <= 2)
                hab[i][j] = 1;
            else
                hab[i][j] = 0;
        }
    }
}

// FUNÇÃO QUE APLICA A MATRIZ DE HABILIDADE NO TABULEIRO, COM BASE EM UM PONTO DE ORIGEM
void aplicarHabilidade(int tab[TAM][TAM], int hab[TAM_HAB][TAM_HAB], int linha, int coluna) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            if (hab[i][j] == 1) {
                // CALCULA A POSIÇÃO REAL NO TABULEIRO
                int linTab = linha + i - TAM_HAB/2;
                int colTab = coluna + j - TAM_HAB/2;

                // GARANTE QUE A POSIÇÃO ESTEJA DENTRO DOS LIMITES DO TABULEIRO
                if (linTab >= 0 && linTab < TAM && colTab >= 0 && colTab < TAM) {
                    // SE NAO FOR NAVIO, MARCA COMO AREA DE EFEITO
                    if (tab[linTab][colTab] != 3) {
                        tab[linTab][colTab] = EFEITO;
                    }
                }
            }
        }
    }
}

// EXIBE O TABULEIRO NO CONSOLE
void imprimirTabuleiro(int tab[TAM][TAM]) {
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tab[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAM][TAM];
    int i, j;

    // INICIALIZA O TABULEIRO
    for (int i = 0; i < TAM; i++) {
        for (int j = 0; j < TAM; j++) {
            tabuleiro[i][j] = 0;
        }
    }

    // POSICIONA OS 4 NAVIOS

    // PRIMEIRO NAVIO - HORIZONTAL (LINHA 1, COLUNAS 2 A 4)
    int linhaH = 1, colunaH = 2;
    for (i = 0; i < NAVIO; i++) {
        tabuleiro[linhaH][colunaH + i] = 3;
    }

    //SEGUNDO NAVIO - VERTICAL (COLUNA 7, LINHAS 4 A 6)
    int linhaV = 4, colunaV = 7;
    for (i = 0; i < NAVIO; i++) {
        tabuleiro[linhaV + i][colunaV] = 3;
    }

    // TERCEIRO NAVIO - DIAGONAL PRINCIPAL (0,0) (1,1) (2,2)
    int linhaD1 = 0, colunaD1 = 0;
    for (i = 0; i < NAVIO; i++) {
        tabuleiro[linhaD1 + i][colunaD1 + i] = 3;
    }

    // QUARTO NAVIO - DIAGONAL SECUNDÁRIA (LINHA 6, COLUNA 9 EM DIANTE)
    int linhaD2 = 6, colunaD2 = 9;
    for (i = 0; i < NAVIO; i++) {
        tabuleiro[linhaD2 + i][colunaD2 + i] = 3;
    }

    // DECLARAÇÃO DA MATRIZ DE HABILIDADE 5X5
    int habilidade[TAM_HAB][TAM_HAB];
    int tipo, origem_linha, origem_coluna;

    // ESCOLHA DA HABILIDADE PELO JOGADOR
    printf("Escolha uma habilidade:\n1 - CONE\n2 - CRUZ\n3 - Octaedro\nOpção: ");
    scanf("%d", &tipo);

    // DEFINE O PONTO DE ORIGEM (CENTRO DA HABILIDADE)
    printf("Informe a linha e coluna de origem da habilidade (0 a 9): ");
    scanf("%d %d", &origem_linha, &origem_coluna);

    // CRIA A MATRIZ DE HABILIDADE COM BASE NO TIPO ESCOLHIDO
    switch (tipo) {
        case 1: criarCone(habilidade); break;
        case 2: criarCruz(habilidade); break;
        case 3: criarOctaedro(habilidade); break;
        default:
            printf("Tipo inválido.\n");
            return 1;
    }

    // APLICA A MATRIZ DA HABILIDADE NO TABULEIRO, CENTRALIZADA NO PONTO ESCOLHIDO
    aplicarHabilidade(tabuleiro, habilidade, origem_linha, origem_coluna);

    // MOSTRA O TABULEIRO FINAL COM OS NAVIOS E ÁREAS AFETADAS
    printf("\nTABULEIRO BATALHA NAVAL (0 = ÁGUA | 3 = Návio | 5 = ÁREA AFETADA)\n\n");
    imprimirTabuleiro(tabuleiro);

    return 0;
}
