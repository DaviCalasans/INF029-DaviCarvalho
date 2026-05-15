#include <stdio.h>
#include "trabalho1.h" 
#include <stdlib.h>
#include <string.h>

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
    int qtdOcorrencias = 0;
    int modBase;
    int modBusca;
    int encontrado = 0; 
    int mult = 1;
    int cpyBusca = numerobusca;

    while(numerobase > 0){
        modBase = numerobase % 10;
        numerobase = numerobase / 10;
        modBusca = numerobusca % 10;

        if(modBase == modBusca){
            encontrado = (modBase * mult) + encontrado;
            if(mult == 1){
                mult *= 10;
            }
            printf("modBase: %d igual a modBusca: %d\n", modBase, modBusca);
        };

        if(encontrado == cpyBusca){
            printf("O númerobusca: %d foi encontrado!", numerobusca);
        }
    }
    return qtdOcorrencias;
}

int main(){
    printf("%d", q6(123, 23));
    return 0;
}