#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

// Função para exibir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("Tabuleiro:\n\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Verifica se o navio cabe horizontalmente
int cabeHorizontal(int linha, int coluna) {
    return coluna + TAM_NAVIO <= TAM_TABULEIRO;
}

// Verifica se o navio cabe verticalmente
int cabeVertical(int linha, int coluna) {
    return linha + TAM_NAVIO <= TAM_TABULEIRO;
}

// Verifica se o navio cabe na diagonal ↘
int cabeDiagonalPrincipal(int linha, int coluna) {
    return linha + TAM_NAVIO <= TAM_TABULEIRO && coluna + TAM_NAVIO <= TAM_TABULEIRO;
}

// Verifica se o navio cabe na diagonal ↙
int cabeDiagonalSecundaria(int linha, int coluna) {
    return linha + TAM_NAVIO <= TAM_TABULEIRO && coluna - TAM_NAVIO + 1 >= 0;
}

// Verifica sobreposição horizontal
int haSobreposicaoHorizontal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha][coluna + i] != 0)
            return 1;
    }
    return 0;
}

// Verifica sobreposição vertical
int haSobreposicaoVertical(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna] != 0)
            return 1;
    }
    return 0;
}

// Verifica sobreposição diagonal ↘
int haSobreposicaoDiagonalPrincipal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna + i] != 0)
            return 1;
    }
    return 0;
}

// Verifica sobreposição diagonal ↙
int haSobreposicaoDiagonalSecundaria(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna - i] != 0)
            return 1;
    }
    return 0;
}

int main() {
    // Inicializa o tabuleiro com água (0)
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0};

    // ----------- NAVIO 1: HORIZONTAL -----------
    int linha1 = 1, coluna1 = 2;
    if (cabeHorizontal(linha1, coluna1) && !haSobreposicaoHorizontal(tabuleiro, linha1, coluna1)) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha1][coluna1 + i] = 3;
        }
    } else {
        printf("Erro ao posicionar o navio 1 (horizontal).\n");
    }

    // ----------- NAVIO 2: VERTICAL -----------
    int linha2 = 4, coluna2 = 6;
    if (cabeVertical(linha2, coluna2) && !haSobreposicaoVertical(tabuleiro, linha2, coluna2)) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha2 + i][coluna2] = 3;
        }
    } else {
        printf("Erro ao posicionar o navio 2 (vertical).\n");
    }

    // ----------- NAVIO 3: DIAGONAL ↘ -----------
    int linha3 = 0, coluna3 = 0;
    if (cabeDiagonalPrincipal(linha3, coluna3) && !haSobreposicaoDiagonalPrincipal(tabuleiro, linha3, coluna3)) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha3 + i][coluna3 + i] = 3;
        }
    } else {
        printf("Erro ao posicionar o navio 3 (diagonal ↘).\n");
    }

    // ----------- NAVIO 4: DIAGONAL ↙ -----------
    int linha4 = 6, coluna4 = 9;
    if (cabeDiagonalSecundaria(linha4, coluna4) && !haSobreposicaoDiagonalSecundaria(tabuleiro, linha4, coluna4)) {
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linha4 + i][coluna4 - i] = 3;
        }
    } else {
        printf("Erro ao posicionar o navio 4 (diagonal ↙).\n");
    }

    // Exibe o tabuleiro completo
    printf("\n");
    exibirTabuleiro(tabuleiro);

    return 0;
}
