#include <stdio.h>

#define TAM_TABULEIRO 10
#define TAM_NAVIO 3
#define TAM_HABILIDADE 5

// Função para exibir o tabuleiro com elementos distintos
void exibirTabuleiro(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO]) {
    printf("Tabuleiro (0=água, 3=navio, 5=habilidade):\n\n");
    for (int i = 0; i < TAM_TABULEIRO; i++) {
        for (int j = 0; j < TAM_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

// Cria a matriz da habilidade em cone
void criarCone(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int meio = TAM_HABILIDADE / 2;
            if (j >= meio - i && j <= meio + i)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// Cria a matriz da habilidade em cruz
void criarCruz(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (i == TAM_HABILIDADE / 2 || j == TAM_HABILIDADE / 2)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// Cria a matriz da habilidade em octaedro (losango)
void criarOctaedro(int habilidade[TAM_HABILIDADE][TAM_HABILIDADE]) {
    int centro = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// Aplica a matriz da habilidade ao tabuleiro, centralizando em (linha, coluna)
void aplicarHabilidade(int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO],
                       int habilidade[TAM_HABILIDADE][TAM_HABILIDADE],
                       int origemLinha, int origemColuna) {
    int offset = TAM_HABILIDADE / 2;
    for (int i = 0; i < TAM_HABILIDADE; i++) {
        for (int j = 0; j < TAM_HABILIDADE; j++) {
            int linhaTab = origemLinha - offset + i;
            int colunaTab = origemColuna - offset + j;

            // Verifica limites do tabuleiro
            if (linhaTab >= 0 && linhaTab < TAM_TABULEIRO &&
                colunaTab >= 0 && colunaTab < TAM_TABULEIRO) {
                if (habilidade[i][j] == 1 && tabuleiro[linhaTab][colunaTab] == 0)
                    tabuleiro[linhaTab][colunaTab] = 5;
            }
        }
    }
}

// Verificações e posicionamentos dos navios (mesmo código anterior)
int cabeHorizontal(int linha, int coluna) {
    return coluna + TAM_NAVIO <= TAM_TABULEIRO;
}
int cabeVertical(int linha, int coluna) {
    return linha + TAM_NAVIO <= TAM_TABULEIRO;
}
int haSobreposicaoHorizontal(int t[TAM_TABULEIRO][TAM_TABULEIRO], int l, int c) {
    for (int i = 0; i < TAM_NAVIO; i++)
        if (t[l][c + i] != 0) return 1;
    return 0;
}
int haSobreposicaoVertical(int t[TAM_TABULEIRO][TAM_TABULEIRO], int l, int c) {
    for (int i = 0; i < TAM_NAVIO; i++)
        if (t[l + i][c] != 0) return 1;
    return 0;
}
int cabeDiagonalPrincipal(int l, int c) {
    return l + TAM_NAVIO <= TAM_TABULEIRO && c + TAM_NAVIO <= TAM_TABULEIRO;
}
int cabeDiagonalSecundaria(int l, int c) {
    return l + TAM_NAVIO <= TAM_TABULEIRO && c - TAM_NAVIO + 1 >= 0;
}
int haSobreposicaoDiagonalPrincipal(int t[TAM_TABULEIRO][TAM_TABULEIRO], int l, int c) {
    for (int i = 0; i < TAM_NAVIO; i++)
        if (t[l + i][c + i] != 0) return 1;
    return 0;
}
int haSobreposicaoDiagonalSecundaria(int t[TAM_TABULEIRO][TAM_TABULEIRO], int l, int c) {
    for (int i = 0; i < TAM_NAVIO; i++)
        if (t[l + i][c - i] != 0) return 1;
    return 0;
}

int main() {
    int tabuleiro[TAM_TABULEIRO][TAM_TABULEIRO] = {0};

    // Posicionamento dos navios (2 normais + 2 diagonais)
    int l1 = 1, c1 = 2;
    if (cabeHorizontal(l1, c1) && !haSobreposicaoHorizontal(tabuleiro, l1, c1))
        for (int i = 0; i < TAM_NAVIO; i++) tabuleiro[l1][c1 + i] = 3;

    int l2 = 4, c2 = 6;
    if (cabeVertical(l2, c2) && !haSobreposicaoVertical(tabuleiro, l2, c2))
        for (int i = 0; i < TAM_NAVIO; i++) tabuleiro[l2 + i][c2] = 3;

    int l3 = 0, c3 = 0;
    if (cabeDiagonalPrincipal(l3, c3) && !haSobreposicaoDiagonalPrincipal(tabuleiro, l3, c3))
        for (int i = 0; i < TAM_NAVIO; i++) tabuleiro[l3 + i][c3 + i] = 3;

    int l4 = 6, c4 = 9;
    if (cabeDiagonalSecundaria(l4, c4) && !haSobreposicaoDiagonalSecundaria(tabuleiro, l4, c4))
        for (int i = 0; i < TAM_NAVIO; i++) tabuleiro[l4 + i][c4 - i] = 3;

    // Criação e aplicação das habilidades
    int cone[TAM_HABILIDADE][TAM_HABILIDADE];
    int cruz[TAM_HABILIDADE][TAM_HABILIDADE];
    int octaedro[TAM_HABILIDADE][TAM_HABILIDADE];

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Aplicar habilidades no tabuleiro com pontos de origem
    aplicarHabilidade(tabuleiro, cone, 2, 2);       // Exemplo de cone no topo esquerdo
    aplicarHabilidade(tabuleiro, cruz, 5, 5);       // Cruz no centro
    aplicarHabilidade(tabuleiro, octaedro, 7, 7);   // Octaedro no canto inferior direito

    // Exibir resultado final
    exibirTabuleiro(tabuleiro);

    return 0;
}
