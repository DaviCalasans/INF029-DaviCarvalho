#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Definição da struct armazenando x, y e a distância até (0,0)
typedef struct {
    int x;
    int y;
    double dist_origem;
} Ponto;

// Função para calcular a distância Euclidiana entre dois pontos
double calc_dist(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// Função de comparação obrigatória para usarmos o qsort do C
int comparar_pontos(const void *a, const void *b) {
    Ponto *p1 = (Ponto *)a;
    Ponto *p2 = (Ponto *)b;
    
    // Compara as distâncias com a origem para ordenar em ordem crescente
    if (p1->dist_origem < p2->dist_origem) return -1;
    if (p1->dist_origem > p2->dist_origem) return 1;
    return 0;
}

int main() {
    int num_linhas;
    char linha[2048]; // Tamanho aumentado para suportar linhas muito longas

    // Lê a primeira linha indicando o número de entradas
    if (scanf("%d", &num_linhas) != 1) {
        return 0;
    }
    
    // Limpa o caractere de "Enter" (\n) deixado pelo scanf na primeira linha
    while(getchar() != '\n'); 

    // Laço principal para processar cada linha
    for (int i = 0; i < num_linhas; i++) {
        if (fgets(linha, sizeof(linha), stdin) == NULL) {
            break;
        }

        Ponto pontos[500];
        int qtd = 0;
        char *pos = linha;
        
        // Pula os 7 caracteres iniciais da palavra "points "
        pos += 7; 

        int x, y, n;
        double distancia_total = 0.0;
        double atalho = 0.0;

        // Extrai as coordenadas enquanto houver o padrão " ( %d , %d )"
        while (sscanf(pos, " ( %d , %d )%n", &x, &y, &n) == 2) {
            pontos[qtd].x = x;
            pontos[qtd].y = y;
            pontos[qtd].dist_origem = calc_dist(x, y, 0, 0); // Já salva a distância para o (0,0)
            
            // Calcula e soma a distância de um ponto a outro na ordem ORIGINAL da entrada
            if (qtd > 0) {
                distancia_total += calc_dist(pontos[qtd-1].x, pontos[qtd-1].y, pontos[qtd].x, pontos[qtd].y);
            }
            
            qtd++;
            pos += n; // Avança o ponteiro na string
        }

        if (qtd == 0) continue; // Prevenção contra linhas vazias

        // Distância entre o primeiro e o último ponto da ordem original
        atalho = calc_dist(pontos[0].x, pontos[0].y, pontos[qtd-1].x, pontos[qtd-1].y);

        // Ordena o vetor original com base nas distâncias do (0,0) calculadas acima
        qsort(pontos, qtd, sizeof(Ponto), comparar_pontos);

        // Impressão idêntica às regras de formatação (sem espaços extras, duas casas decimais)
        printf("points");
        for (int j = 0; j < qtd; j++) {
            printf(" (%d,%d)", pontos[j].x, pontos[j].y);
        }
        printf(" distance %.2f shortcut %.2f\n", distancia_total, atalho);
    }

    return 0;
}