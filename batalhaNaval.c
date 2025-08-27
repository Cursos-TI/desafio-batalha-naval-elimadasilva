#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3

// Função para imprimir o tabuleiro
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("Tabuleiro:\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Função para verificar se o navio cabe no tabuleiro (horizontal)
int cabeHorizontal(int linha, int coluna) {
    return coluna + TAM_NAVIO <= TAM_TABULEIRO;
}

// Função para verificar se o navio cabe no tabuleiro (vertical)
int cabeVertical(int linha, int coluna) {
    return linha + TAM_NAVIO <= TAM_TABULEIRO;
}

// Função para verificar se há sobreposição (horizontal)
int haSobreposicaoHorizontal(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha][coluna + i] != 0)
            return 1; // Encontrou sobreposição
    }
    return 0;
}

// Função para verificar se há sobreposição (vertical)
int haSobreposicaoVertical(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO], int linha, int coluna) {
    for (int i = 0; i < TAM_NAVIO; i++) {
        if (tabuleiro[linha + i][coluna] != 0)
            return 1; // Encontrou sobreposição
    }
    return 0;
}

int main() {
    // Inicializa o tabuleiro com 0 (água)
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0};

    // Vetores representando os navios (3 posições com valor 3)
    int navio1[TAM_NAVIO] = {3, 3, 3}; // Horizontal
    int navio2[TAM_NAVIO] = {3, 3, 3}; // Vertical

    // Coordenadas iniciais dos navios (definidas diretamente no código)
    int linhaNavio1 = 2;
    int colunaNavio1 = 4;

    int linhaNavio2 = 5;
    int colunaNavio2 = 6;

    // Validação para o navio horizontal
    if (cabeHorizontal(linhaNavio1, colunaNavio1) &&
        !haSobreposicaoHorizontal(tabuleiro, linhaNavio1, colunaNavio1)) {
        // Posiciona navio horizontal
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linhaNavio1][colunaNavio1 + i] = navio1[i];
        }
    } else {
        printf("Erro ao posicionar o navio horizontal.\n");
    }

    // Validação para o navio vertical
    if (cabeVertical(linhaNavio2, colunaNavio2) &&
        !haSobreposicaoVertical(tabuleiro, linhaNavio2, colunaNavio2)) {
        // Posiciona navio vertical
        for (int i = 0; i < TAM_NAVIO; i++) {
            tabuleiro[linhaNavio2 + i][colunaNavio2] = navio2[i];
        }
    } else {
        printf("Erro ao posicionar o navio vertical.\n");
    }

    // Exibe o tabuleiro completo
    exibirTabuleiro(tabuleiro);

    return 0;
}
