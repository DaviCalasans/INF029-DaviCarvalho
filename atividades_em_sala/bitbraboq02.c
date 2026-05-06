#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    int x, y;
    int distSq;
    char original[100];
} Ponto;

int cmpStr(const void *a, const void *b) {
    return strcmp((char *)a, (char *)b);
}

int cmpInt(const void *a, const void *b) {
    return (*(int*)a - *(int*)b);
}

int cmpFloat(const void *a, const void *b) {
    float f1 = *(float*)a;
    float f2 = *(float*)b;
    if (f1 < f2) return -1;
    if (f1 > f2) return 1;
    return 0;
}

int cmpPonto(const void *a, const void *b) {
    Ponto *p1 = (Ponto *)a;
    Ponto *p2 = (Ponto *)b;
    if (p1->distSq != p2->distSq)
        return p1->distSq - p2->distSq;
    return 0;
}

int identificarTipo(char *s) {
    if (s[0] == '(') return 3; 
    if (strchr(s, '.')) return 2; 
    
    char *ptr = s;
    if (*ptr == '-') ptr++;
    if (*ptr != '\0' && isdigit(*ptr)) {
        while (*ptr) {
            if (!isdigit(*ptr)) return 0;
            ptr++;
        }
        return 1;
    }
    return 0;
}

int main() {
    int numLinhas;
    if (scanf("%d ", &numLinhas) != 1) return 0;

    char linha[1000];
    while (numLinhas--) {
        if (!fgets(linha, sizeof(linha), stdin)) break;
        linha[strcspn(linha, "\n\r")] = 0;

        char strings[100][100];
        int inteiros[100];
        float reais[100];
        Ponto pontos[100];
        int nS = 0, nI = 0, nR = 0, nP = 0;

        char *token = strtok(linha, " ");
        while (token != NULL) {
            int tipo = identificarTipo(token);
            if (tipo == 0) strcpy(strings[nS++], token);
            else if (tipo == 1) inteiros[nI++] = atoi(token);
            else if (tipo == 2) reais[nR++] = atof(token);
            else if (tipo == 3) {
                strcpy(pontos[nP].original, token);
                sscanf(token, "(%d,%d)", &pontos[nP].x, &pontos[nP].y);
                pontos[nP].distSq = (pontos[nP].x * pontos[nP].x) + (pontos[nP].y * pontos[nP].y);
                nP++;
            }
            token = strtok(NULL, " ");
        }

        qsort(strings, nS, 100, cmpStr);
        qsort(inteiros, nI, sizeof(int), cmpInt);
        qsort(reais, nR, sizeof(float), cmpFloat);
        qsort(pontos, nP, sizeof(Ponto), cmpPonto);

        printf("str:");
        for (int i = 0; i < nS; i++) printf("%s%s", (i > 0 ? " " : ""), strings[i]);
        
        printf(" int:");
        for (int i = 0; i < nI; i++) printf("%s%d", (i > 0 ? " " : ""), inteiros[i]);
        
        printf(" float:");
        for (int i = 0; i < nR; i++) {
            printf("%s%g", (i > 0 ? " " : ""), reais[i]);
        }
        
        printf(" p:");
        for (int i = 0; i < nP; i++) printf("%s%s", (i > 0 ? " " : ""), pontos[i].original);
        
        printf("\n");
    }

    return 0;
}