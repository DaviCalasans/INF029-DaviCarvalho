#include <stdio.h>
#include <ctype.h>

// Função auxiliar para imprimir o tabuleiro no formato exigido
void imprimir_tabuleiro(char tab[3][3]) {
    printf("\n    1   2   3\n");
    printf("A   %c | %c | %c \n", tab[0][0], tab[0][1], tab[0][2]);
    printf("   ---+---+---\n");
    printf("B   %c | %c | %c \n", tab[1][0], tab[1][1], tab[1][2]);
    printf("   ---+---+---\n");
    printf("C   %c | %c | %c \n\n", tab[2][0], tab[2][1], tab[2][2]);
}

// Função auxiliar para verificar se houve ganhador
// Retorna 1 se houver vencedor, 0 caso contrário
int checar_vencedor(char tab[3][3]) {
    int i;
    // Checar linhas e colunas
    for(i = 0; i < 3; i++) {
        if(tab[i][0] != ' ' && tab[i][0] == tab[i][1] && tab[i][1] == tab[i][2]) return 1;
        if(tab[0][i] != ' ' && tab[0][i] == tab[1][i] && tab[1][i] == tab[2][i]) return 1;
    }
    // Checar diagonais
    if(tab[0][0] != ' ' && tab[0][0] == tab[1][1] && tab[1][1] == tab[2][2]) return 1;
    if(tab[0][2] != ' ' && tab[0][2] == tab[1][1] && tab[1][1] == tab[2][0]) return 1;
    
    return 0;
}

// Função principal solicitada no enunciado
void q8() {
    char tabuleiro[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    
    int turno = 0;
    int jogador = 1;
    char marca;
    char entrada_linha;
    int entrada_col;
    int linha_idx, col_idx;
    int venceu = 0;

    printf("=== JOGO DA VELHA ===\n");

    while (turno < 9 && !venceu) {
        imprimir_tabuleiro(tabuleiro);
        
        // Define o jogador (1 ou 2) e a marca ('X' ou '0')
        jogador = (turno % 2 == 0) ? 1 : 2;
        marca = (jogador == 1) ? 'X' : '0';

        int jogada_valida = 0;
        
        while (!jogada_valida) {
            printf("Jogador %d, informe sua jogada: ", jogador);
            
            // Lendo a entrada (ex: B3)
            // O espaço antes do %c limpa o buffer do teclado (como 'enters' residuais)
            if (scanf(" %c%d", &entrada_linha, &entrada_col) != 2) {
                printf("Entrada incorreta! Use o formato LetraNumero (ex: B3).\n");
                // Limpa o buffer em caso de erro de leitura do scanf
                while (getchar() != '\n'); 
                continue;
            }

            // Converte a letra para maiúscula para facilitar a validação
            entrada_linha = toupper(entrada_linha);

            // Verifica se a linha está entre A e C, e a coluna entre 1 e 3
            if (entrada_linha >= 'A' && entrada_linha <= 'C' && entrada_col >= 1 && entrada_col <= 3) {
                linha_idx = entrada_linha - 'A'; // 'A'-'A' = 0, 'B'-'A' = 1, 'C'-'A' = 2
                col_idx = entrada_col - 1;       // 1-1 = 0, 2-1 = 1, 3-1 = 2

                // Verifica se a célula já está ocupada
                if (tabuleiro[linha_idx][col_idx] == ' ') {
                    jogada_valida = 1;
                    tabuleiro[linha_idx][col_idx] = marca;
                } else {
                    printf("Célula já ocupada! Tente novamente.\n");
                }
            } else {
                printf("Célula inválida! A linha deve ser A, B ou C e a coluna 1, 2 ou 3.\n");
            }
        }

        // Após a jogada, checa se este jogador venceu
        if (checar_vencedor(tabuleiro)) {
            venceu = 1;
            imprimir_tabuleiro(tabuleiro);
            printf("Parabéns! O Jogador %d (com a marca '%c') foi o ganhador!\n", jogador, marca);
            break;
        }

        turno++;
    }

    // Se o loop terminar (9 turnos) e ninguém venceu, é empate
    if (!venceu) {
        imprimir_tabuleiro(tabuleiro);
        printf("Deu velha! Não houve ganhador.\n");
    }
}

int main() {
    // Chamada da função solicitada
    q8();
    return 0;
}