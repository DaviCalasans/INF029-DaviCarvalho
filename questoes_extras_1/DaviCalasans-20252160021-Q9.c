#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// a) Parâmetro global para o número de navios. 
// O mínimo é 5. Se aumentar, os próximos serão tamanho 2.
int NUM_NAVIOS = 5;

// Função auxiliar para determinar o tamanho do navio baseado no índice (regra b)
int get_tamanho_navio(int indice) {
    if (indice == 0) return 4; // 1 barco de tamanho 4
    if (indice == 1) return 3; // 1 barco de tamanho 3
    if (indice >= 2 && indice <= 4) return 1; // 3 barcos de tamanho 1
    return 2; // Demais barcos de tamanho 2
}

// Inicializa o tabuleiro 10x10 com espaços em branco
void inicializar_tabuleiro(char tab[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tab[i][j] = ' ';
        }
    }
}

// e) Imprime o mapa com a configuração solicitada
void imprimir_tabuleiro(char tab[10][10], int esconder_navios) {
    printf("     0   1   2   3   4   5   6   7   8   9\n");
    for (int i = 0; i < 10; i++) {
        printf(" %c ", 'A' + i);
        for (int j = 0; j < 10; j++) {
            char celula = tab[i][j];
            // f.ii) Esconder os navios do oponente
            if (esconder_navios && celula == 'N') {
                celula = ' ';
            }
            printf("[ %c ]", celula);
        }
        printf("\n");
    }
}

// f) Lista o tabuleiro (o próprio com tudo, o do adversário escondendo navios)
void listar_tabuleiros(char meu_tabuleiro[10][10], char tabuleiro_adversario[10][10]) {
    printf("\n=== SEU TABULEIRO ===\n");
    imprimir_tabuleiro(meu_tabuleiro, 0); // 0 = Mostrar navios
    
    printf("\n=== TABULEIRO DO ADVERSÁRIO ===\n");
    imprimir_tabuleiro(tabuleiro_adversario, 1); // 1 = Esconder navios
}

// d) Função para posicionar barcos de forma correta
void posicionar_barcos(char tab[10][10], int jogador) {
    printf("\n>>> JOGADOR %d, POSICIONE SEUS NAVIOS <<<\n", jogador);
    
    for (int i = 0; i < NUM_NAVIOS; i++) {
        int tam = get_tamanho_navio(i);
        int posicionado = 0;
        
        while (!posicionado) {
            char linha_c, ori = 'H';
            int col;
            
            imprimir_tabuleiro(tab, 0);
            
            if (tam > 1) {
                printf("\nNavio %d (Tamanho: %d). Informe Linha (A-J), Coluna (0-9) e Orientacao (H/V): ", i+1, tam);
                if (scanf(" %c %d %c", &linha_c, &col, &ori) != 3) {
                    while (getchar() != '\n'); continue;
                }
            } else {
                printf("\nNavio %d (Tamanho: %d). Informe Linha (A-J) e Coluna (0-9): ", i+1, tam);
                if (scanf(" %c %d", &linha_c, &col) != 2) {
                    while (getchar() != '\n'); continue;
                }
            }
            
            linha_c = toupper(linha_c);
            ori = toupper(ori);
            int linha = linha_c - 'A';
            
            // Validação de limites
            int valido = 1;
            if (linha < 0 || linha > 9 || col < 0 || col > 9) {
                printf("Erro: Coordenadas fora do tabuleiro!\n");
                valido = 0;
            } else if (ori == 'H' && col + tam > 10) {
                printf("Erro: Navio ultrapassa o limite direito do tabuleiro!\n");
                valido = 0;
            } else if (ori == 'V' && linha + tam > 10) {
                printf("Erro: Navio ultrapassa o limite inferior do tabuleiro!\n");
                valido = 0;
            }
            
            // Validação de sobreposição
            if (valido) {
                for (int k = 0; k < tam; k++) {
                    int l = (ori == 'V') ? linha + k : linha;
                    int c = (ori == 'H') ? col + k : col;
                    if (tab[l][c] != ' ') {
                        printf("Erro: Já existe um navio nesta posição!\n");
                        valido = 0;
                        break;
                    }
                }
            }
            
            // Grava no tabuleiro se válido
            if (valido) {
                for (int k = 0; k < tam; k++) {
                    int l = (ori == 'V') ? linha + k : linha;
                    int c = (ori == 'H') ? col + k : col;
                    tab[l][c] = 'N';
                }
                posicionado = 1;
            }
        }
    }
    // Opcional: imprimir vários espaços em branco (ou usar system clear) para esconder os navios do P1 para o P2
    printf("\n\n\n\n\n\n\n\n\n\n--- FIM DO POSICIONAMENTO DO JOGADOR %d ---\n", jogador);
}

// g) Função para atirar
void atirar(char tab_alvo[10][10], int *partes_restantes, int jogador) {
    int valido = 0;
    while (!valido) {
        char linha_c;
        int col;
        
        printf("\nJogador %d, informe a célula do seu tiro (Ex: A 5): ", jogador);
        if (scanf(" %c %d", &linha_c, &col) != 2) {
            printf("Entrada inválida!\n");
            while (getchar() != '\n'); 
            continue;
        }
        
        linha_c = toupper(linha_c);
        int linha = linha_c - 'A';
        
        if (linha < 0 || linha > 9 || col < 0 || col > 9) {
            printf("Coordenada fora do mapa!\n");
            continue;
        }
        
        char alvo = tab_alvo[linha][col];
        if (alvo == '0' || alvo == 'X') {
            printf("Você já atirou nesta célula. Tente novamente.\n");
            continue;
        }
        
        if (alvo == 'N') {
            printf("\n>>> FOGO! Você acertou um navio! <<<\n");
            tab_alvo[linha][col] = '0'; // Posição abatida
            (*partes_restantes)--;
        } else if (alvo == ' ') {
            printf("\n>>> ÁGUA! Tiro no mar. <<<\n");
            tab_alvo[linha][col] = 'X'; // Tiro inválido/Água
        }
        valido = 1;
    }
}

// Função principal solicitada
void q9() {
    char tab_j1[10][10];
    char tab_j2[10][10];
    
    inicializar_tabuleiro(tab_j1);
    inicializar_tabuleiro(tab_j2);
    
    // Calcula o total de partes de navios para definir a condição de vitória
    int total_partes = 0;
    for (int i = 0; i < NUM_NAVIOS; i++) {
        total_partes += get_tamanho_navio(i);
    }
    
    int partes_restantes_j1 = total_partes;
    int partes_restantes_j2 = total_partes;
    
    // Posicionamento inicial
    posicionar_barcos(tab_j1, 1);
    posicionar_barcos(tab_j2, 2);
    
    int turno = 1;
    int vencedor = 0;
    
    printf("\n\n>>> O JOGO COMEÇOU! <<<\n");
    
    // h) Alternância de turnos; i) Verifica quem acertou tudo
    while (!vencedor) {
        if (turno % 2 != 0) {
            // Turno do Jogador 1
            printf("\n--- TURNO DO JOGADOR 1 ---");
            listar_tabuleiros(tab_j1, tab_j2);
            atirar(tab_j2, &partes_restantes_j2, 1);
            if (partes_restantes_j2 == 0) vencedor = 1;
        } else {
            // Turno do Jogador 2
            printf("\n--- TURNO DO JOGADOR 2 ---");
            listar_tabuleiros(tab_j2, tab_j1);
            atirar(tab_j1, &partes_restantes_j1, 2);
            if (partes_restantes_j1 == 0) vencedor = 2;
        }
        turno++;
    }
    
    printf("\n\n#####################################\n");
    printf(" FIM DE JOGO! O JOGADOR %d VENCEU!\n", vencedor);
    printf("#####################################\n");
}

int main() {
    q9();
    return 0;
}