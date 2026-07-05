#include <stdio.h>
#include <stdlib.h>
#define TAM 10

#include "trabalho2.h"

typedef struct EstruturaAux{
    No * inicio;
    int tamMaximo;
    int qtd;
}EstruturaAux;

EstruturaAux vetorPrincipal[TAM];

// se posição é um valor válido {entre 1 e 10}
int ehPosicaoValida(int posicao)
{
    int retorno = 0;
    if (posicao < 1 || posicao > 10)
    {
        retorno = POSICAO_INVALIDA;
    }
    else
        retorno = SUCESSO;

    return retorno;
}

/*
Objetivo: criar estrutura auxiliar na posição 'posicao'.
com tamanho 'tamanho'

Rertono (int)
    SUCESSO - criado com sucesso
    JA_TEM_ESTRUTURA_AUXILIAR - já tem estrutura na posição
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    SEM_ESPACO_DE_MEMORIA - Sem espaço de memória
    TAMANHO_INVALIDO - o tamanho deve ser maior ou igual a 1
*/
int criarEstruturaAuxiliar(int posicao, int tamanho)
{
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
    {
        return POSICAO_INVALIDA;
    }

    if (tamanho < 1)
    {
        return TAMANHO_INVALIDO;
    }

    int indice = posicao - 1;

    if (vetorPrincipal[indice].tamMaximo != 0)
    {
        return JA_TEM_ESTRUTURA_AUXILIAR;
    }

    vetorPrincipal[indice].inicio = NULL;
    vetorPrincipal[indice].tamMaximo = tamanho;
    vetorPrincipal[indice].qtd = 0;

    return SUCESSO;
}

/*
Objetivo: inserir número 'valor' em estrutura auxiliar da posição 'posicao'
Rertono (int)
    SUCESSO - inserido com sucesso
    SEM_ESPACO - não tem espaço
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
CONSTANTES
*/
int inserirNumeroEmEstrutura(int posicao, int valor)
{
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
    {
        return POSICAO_INVALIDA;
    }

    int indice = posicao - 1;

    if (vetorPrincipal[indice].tamMaximo == 0)
    {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    if (vetorPrincipal[indice].qtd >= vetorPrincipal[indice].tamMaximo)
    {
        return SEM_ESPACO;
    }

    No *novo = malloc(sizeof(No));
    if (novo == NULL)
    {
        return SEM_ESPACO_DE_MEMORIA;
    }

    novo->conteudo = valor;
    novo->prox = NULL;

    if (vetorPrincipal[indice].inicio == NULL)
    {
        vetorPrincipal[indice].inicio = novo;
    }
    else
    {
        No *atual = vetorPrincipal[indice].inicio;
        while (atual->prox != NULL)
        {
            atual = atual->prox;
        }
        atual->prox = novo;
    }

    vetorPrincipal[indice].qtd++;
    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar no final da estrutura.
ex: suponha os valores [3, 8, 7, 9,  ,  ]. Após excluir, a estrutura deve ficar da seguinte forma [3, 8, 7,  ,  ,  ].
Obs. Esta é uma exclusão lógica

Rertono (int)
    SUCESSO - excluido com sucesso
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int excluirNumeroDoFinaldaEstrutura(int posicao)
{
    if (ehPosicaoValida(posicao) == POSICAO_INVALIDA)
    {
        return POSICAO_INVALIDA;
    }

    int indice = posicao - 1;

    if(vetorPrincipal[indice].tamMaximo == 0){
        return SEM_ESTRUTURA_AUXILIAR;
    }

    if(vetorPrincipal[indice].qtd == 0){
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    No * removido = vetorPrincipal[indice].inicio;

    if(vetorPrincipal[indice].qtd == 1){
        vetorPrincipal[indice].inicio = NULL;
    } else {
        No * atual = vetorPrincipal[indice].inicio;
        No * anterior = atual;
        while(atual->prox != NULL){
            anterior = atual;
            atual = atual->prox;
        }
        anterior->prox = NULL; 
        removido = atual;
    }

    free(removido);
    vetorPrincipal[indice].qtd--;
    
    return SUCESSO;
}

/*
Objetivo: excluir o numero 'valor' da estrutura auxiliar da posição 'posicao'.
Caso seja excluido, os números posteriores devem ser movidos para as posições anteriores
ex: suponha os valores [3, 8, 7, 9,  ,  ] onde deve ser excluido o valor 8. A estrutura deve ficar da seguinte forma [3, 7, 9,  ,  ,  ]
Obs. Esta é uma exclusão lógica
Rertono (int)
    SUCESSO - excluido com sucesso 'valor' da estrutura na posição 'posicao'
    ESTRUTURA_AUXILIAR_VAZIA - estrutura vazia
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    NUMERO_INEXISTENTE - Número não existe
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar

*/
int excluirNumeroEspecificoDeEstrutura(int posicao, int valor)
{
    int retorno = SUCESSO;
    return retorno;
}


/*
Objetivo: retorna os números da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Retorno (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    if(ehPosicaoValida(posicao) == POSICAO_INVALIDA){
        return POSICAO_INVALIDA;
    }

    int indice = posicao - 1;

    if(vetorPrincipal[indice].tamMaximo == 0){
        return SEM_ESTRUTURA_AUXILIAR;
    }

    int contador = 0;
    No * aux = vetorPrincipal[indice].inicio;

    while(aux != NULL){
        vetorAux[contador] = aux->conteudo;
        aux = aux->prox;
        contador++;
    }

    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados da estrutura auxiliar da posição 'posicao (1..10)'.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao (1..10)'
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
*/
int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[])
{
    if(ehPosicaoValida(posicao) == POSICAO_INVALIDA){
        return POSICAO_INVALIDA;
    }

    int indice = posicao - 1;

    if(vetorPrincipal[indice].tamMaximo == 0){
        return SEM_ESTRUTURA_AUXILIAR;
    }

    getDadosEstruturaAuxiliar(posicao, vetorAux);

    for(int i = 1; i < vetorPrincipal[indice].qtd; i++){
            int chave = vetorAux[i];
            int j = i - 1;

            while(j >= 0 && vetorAux[j] > chave){
                vetorAux[j + 1] = vetorAux[j];
                j = j - 1;
            }

            vetorAux[j + 1] = chave;
    }

    return SUCESSO;
}

/*
Objetivo: retorna os números de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    int contador = 0;
    for(int i = 0; i < TAM; i++){

        No * atual = vetorPrincipal[i].inicio;

        while(atual != NULL){
            vetorAux[contador] = atual->conteudo;
            atual = atual->prox;
            contador++;
        }
    }

    if(contador == 0){
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }
    
    return SUCESSO;
}

/*
Objetivo: retorna os números ordenados de todas as estruturas auxiliares.
os números devem ser armazenados em vetorAux

Rertono (int)
    SUCESSO - recuperado com sucesso os valores da estrutura na posição 'posicao'
    TODAS_ESTRUTURAS_AUXILIARES_VAZIAS - todas as estruturas auxiliares estão vazias
*/
int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[])
{
    if(getDadosDeTodasEstruturasAuxiliares(vetorAux) == SUCESSO){
        int qtdTotalElementos = 0;
        for(int j = 0; j < TAM; j++){
            qtdTotalElementos = qtdTotalElementos + vetorPrincipal[j].qtd;
        }

        for(int i = 1; i < qtdTotalElementos; i++){
            int chave = vetorAux[i];
            int j = i - 1;

            while(j >= 0 && vetorAux[j] > chave){
                vetorAux[j + 1] = vetorAux[j];
                j = j - 1;
            }

            vetorAux[j + 1] = chave;
        }
        return SUCESSO;
    }

    return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
}

/*
Objetivo: modificar o tamanho da estrutura auxiliar da posição 'posicao' para o novo tamanho 'novoTamanho' + tamanho atual
Suponha o tamanho inicial = x, e novo tamanho = n. O tamanho resultante deve ser x + n. Sendo que x + n deve ser sempre >= 1

Rertono (int)
    SUCESSO - foi modificado corretamente o tamanho da estrutura auxiliar
    SEM_ESTRUTURA_AUXILIAR - Não tem estrutura auxiliar
    POSICAO_INVALIDA - Posição inválida para estrutura auxiliar
    NOVO_TAMANHO_INVALIDO - novo tamanho não pode ser negativo
    SEM_ESPACO_DE_MEMORIA - erro na alocação do novo valor
*/
int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho)
{

    int retorno = 0;
    return retorno;
}

/*
Objetivo: retorna a quantidade de elementos preenchidos da estrutura auxiliar da posição 'posicao'.

Retorno (int)
    POSICAO_INVALIDA - posição inválida
    SEM_ESTRUTURA_AUXILIAR - sem estrutura auxiliar
    ESTRUTURA_AUXILIAR_VAZIA - estrutura auxiliar vazia
    Um número int > 0 correpondente a quantidade de elementos preenchidos da estrutura
*/
int getQuantidadeElementosEstruturaAuxiliar(int posicao)
{

    int retorno = 0;

    return retorno;
}

/*
Objetivo: montar a lista encadeada com cabeçote com todos os números presentes em todas as estruturas.

Retorno (No*)
    NULL, caso não tenha nenhum número nas listas
    No*, ponteiro para o início da lista com cabeçote
*/
No *montarListaEncadeadaComCabecote()
{

    return NULL;
}

/*
Objetivo: retorna os números da lista enceada com cabeçote armazenando em vetorAux.
Retorno void
*/
void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[])
{
}

/*
Objetivo: Destruir a lista encadeada com cabeçote a partir de início.
O ponteiro inicio deve ficar com NULL.

Retorno 
    void.
*/
void destruirListaEncadeadaComCabecote(No **inicio)
{
}

/*
Objetivo: inicializa o programa. deve ser chamado ao inicio do programa 

*/

void inicializar()
{
    for (int i = 0; i < TAM; i++)
    {
        vetorPrincipal[i].inicio = NULL;
        vetorPrincipal[i].tamMaximo = 0;
        vetorPrincipal[i].qtd = 0;
    }
}

/*
Objetivo: finaliza o programa. deve ser chamado ao final do programa 
para poder liberar todos os espaços de memória das estruturas auxiliares.

*/

void finalizar()
{
}