#include <stdio.h>
#include <string.h>

int q7(char matriz[3][3], char palavra[]) {
    int tamPalavra = strlen(palavra);

    // Percorre a matriz linha por linha e coluna por coluna
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            
            // 1. Achou a primeira letra?
            if (matriz[i][j] == palavra[0]) {
                
                // 2. Prepara para olhar nas 8 direções ao redor
                for (int dir_i = -1; dir_i <= 1; dir_i++) {
                    for (int dir_j = -1; dir_j <= 1; dir_j++) {
                        
                        // 3. Ignora o cenário sem movimento (ficar na mesma casa)
                        if (dir_i == 0 && dir_j == 0) {
                            continue;
                        }
                        
                        int k;
                        // 4. "Caminha" na direção escolhida para verificar o resto da palavra
                        for (k = 1; k < tamPalavra; k++) {
                            int linha = i + (dir_i * k);
                            int coluna = j + (dir_j * k);
                            
                            // 5. Verifica os limites seguros da matriz 3x3
                            if (linha >= 0 && linha <= 2 && coluna >= 0 && coluna <= 2) {
                                
                                // 6. Se a letra for diferente, interrompe a busca nessa direção
                                if (matriz[linha][coluna] != palavra[k]) {
                                    break;
                                }
                            } else {
                                // Se o cálculo sair da matriz, também interrompemos
                                break;
                            }
                        }
                        
                        // 7. Confirmação: se k chegou a ter o mesmo valor do tamanho da palavra, achamos!
                        if (k == tamPalavra) {
                            return 1; // Retorna sucesso imediatamente
                        }
                    }
                }
            }
        }
    }

    // Se os laços terminarem e não encontrar a palavra, retorna 0
    return 0;
}

int main() {
    // Declaração como string facilita o funcionamento correto do strlen
    char stringBusca[] = "BO"; 

    char matrix[3][3] = {
        {'Q', 'M', 'J'},
        {'N', 'B', 'Y'},
        {'V', 'O', 'W'},
    };

    int resultado = q7(matrix, stringBusca);
    
    if (resultado == 1) {
        printf("A palavra '%s' foi encontrada!\n", stringBusca);
    } else {
        printf("A palavra '%s' NAO foi encontrada.\n", stringBusca);
    }

    return 0;
}