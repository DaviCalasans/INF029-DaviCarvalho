#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"
#include "professor.h"
#include "disciplina.h"
#include <string.h>
#include <ctype.h>

void texto_para_maiusculo(const char *origem, char *destino)
{
    int i = 0;
    while (origem[i] != '\0')
    {
        destino[i] = toupper(origem[i]);
        i++;
    }
    destino[i] = '\0';
}

void busca_global_por_nome(int qtdAlunos, Aluno *listaAlunos, int qtdProfessores, Professor *listaProfessores, char *termo)
{
    char termoMaiusculo[100];
    char nomeTemp[100];
    int encontrados = 0;

    texto_para_maiusculo(termo, termoMaiusculo);

    printf("\n==================================================\n");
    printf("        RESULTADOS DA BUSCA GLOBAL PARA: '%s'\n", termo);
    printf("==================================================\n");

    for (int i = 0; i < qtdAlunos; i++)
    {
        texto_para_maiusculo(listaAlunos[i].nome, nomeTemp);

        // Verifica se o termo existe DENTRO do nome do aluno
        if (strstr(nomeTemp, termoMaiusculo) != NULL)
        {
            printf("[ALUNO] ID: %d | Nome: %s\n", listaAlunos[i].id, listaAlunos[i].nome);
            encontrados++;
        }
    }

    for (int i = 0; i < qtdProfessores; i++)
    {
        texto_para_maiusculo(listaProfessores[i].nome, nomeTemp);

        if (strstr(nomeTemp, termoMaiusculo) != NULL)
        {
            printf("[PROFESSOR] ID: %d | Nome: %s\n", listaProfessores[i].id, listaProfessores[i].nome);
            encontrados++;
        }
    }

    if (encontrados == 0)
    {
        printf(" -> Nenhuma pessoa encontrada contendo '%s' no nome.\n", termo);
    }
    printf("==================================================\n");
}

int main()
{
    int sair = 0;
    int opcao;

    int qtdAlunos = 0;
    int codigoAluno = 1;
    Aluno *listaAlunos = malloc(TAM_LISTA_ALUNOS * sizeof(Aluno));

    Professor *listaProfessores = malloc(TAM_LISTA_PROFESSOR * sizeof(Professor));
    int qtdProfessores = 0;
    int codigoProfessor = 1;

    Disciplina *listaDisciplinas = malloc(TAM_LISTA_DISCIPLINA * sizeof(Disciplina));
    int qtdDisciplinas = 0;
    int codigoDisciplina = 1;

    while (sair == 0)
    {
        printf("\n--- MENU PRINCIPAL ---\n");
        printf("0 - Sair\n1 - Alunos\n2 - Professores\n3 - Disciplinas\n4 - Pesquisar com string\n");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:
            sair = 1;
            break;
        case 1:
            menuAlunos(listaAlunos, &qtdAlunos, &codigoAluno);
            break;
        case 2:
            menuProfessor(listaProfessores, &qtdProfessores, &codigoProfessor);
            break;
        case 3:
            menuDisciplina(listaDisciplinas, &qtdDisciplinas, &codigoDisciplina, listaProfessores, qtdProfessores, listaAlunos, qtdAlunos);
            break;

        case 4:
        {
            char termoBusca[100];

            do
            {
                printf("\nDigite pelo menos 3 letras para buscar: ");
                scanf(" %99[^\n]", termoBusca);

                if (strlen(termoBusca) < 3)
                {
                    printf("Erro: O termo de busca é muito curto!\n");
                }
            } while (strlen(termoBusca) < 3);

            busca_global_por_nome(qtdAlunos, listaAlunos, qtdProfessores, listaProfessores, termoBusca);
            break;
        }
        }
    }

    free(listaAlunos);
    free(listaProfessores);
    free(listaDisciplinas);
    return 0;
}