#include <stdio.h>
#include <stdlib.h>

#define TAM 10
#define TAM_HAB 5

void imprimirTabuleiro(int tabuleiro[TAM][TAM]) {
    printf("  ");
    for (int col = 0; col < TAM; col++) printf("%d ", col);
    printf("\n");

    for (int i = 0; i < TAM; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAM; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void posicionarNavios(int tabuleiro[TAM][TAM]) {
    // Navios como na imagem
    for (int j = 3; j <= 5; j++) tabuleiro[0][j] = 3;
    for (int i = 1; i <= 3; i++) tabuleiro[i][3] = 3;
    for (int j = 2; j <= 4; j++) tabuleiro[2][j] = 3;
}

void aplicarHabilidade(int tabuleiro[TAM][TAM], int habilidade[TAM_HAB][TAM_HAB], int x, int y, int valor) {
    int offset = TAM_HAB / 2;
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            int lin = x + i - offset;
            int col = y + j - offset;
            if (lin >= 0 && lin < TAM && col >= 0 && col < TAM && habilidade[i][j] == 1) {
                if (tabuleiro[lin][col] == 0)
                    tabuleiro[lin][col] = valor;
            }
        }
    }
}

void criarCone(int cone[TAM_HAB][TAM_HAB]) {
    // Cone para baixo
    int temp[5][5] = {
        {0, 0, 1, 0, 0},
        {0, 1, 1, 1, 0},
        {1, 1, 1, 1, 1},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}
    };
    for (int i = 0; i < TAM_HAB; i++)
        for (int j = 0; j < TAM_HAB; j++)
            cone[i][j] = temp[i][j];
}

void criarCruz(int cruz[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            cruz[i][j] = (i == TAM_HAB/2 || j == TAM_HAB/2) ? 1 : 0;
        }
    }
}

void criarOctaedro(int octaedro[TAM_HAB][TAM_HAB]) {
    for (int i = 0; i < TAM_HAB; i++) {
        for (int j = 0; j < TAM_HAB; j++) {
            octaedro[i][j] = (abs(i - 2) + abs(j - 2) <= 2) ? 1 : 0;
        }
    }
}

int main() {
    int tabuleiro[TAM][TAM] = {0};
    posicionarNavios(tabuleiro);

    int cone[TAM_HAB][TAM_HAB], cruz[TAM_HAB][TAM_HAB], octaedro[TAM_HAB][TAM_HAB];
    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    aplicarHabilidade(tabuleiro, cruz, 2, 3, 3);       // Cruz
    aplicarHabilidade(tabuleiro, octaedro, 4, 7, 2);   // Octaedro
    aplicarHabilidade(tabuleiro, cone, 6, 3, 1);       // Cone

    imprimirTabuleiro(tabuleiro);
    return 0;
}
