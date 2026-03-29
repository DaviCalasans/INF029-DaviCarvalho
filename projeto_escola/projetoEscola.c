#include <stdio.h>
#include <stdlib.h>

#define TAM_LISTA_ALUNOS 3

typedef struct
{
    int id;
    int matricula;
    char nome[50];
    char sexo[1];
    char data_nascimento[10];
    char cpf[11];
} Aluno;

int main()
{
    int sair = 0;
    int opcao;
    int qtdAlunos = 0;
    int codigoAluno = 1;

    Aluno listaAlunos[TAM_LISTA_ALUNOS];

    while (sair == 0)
    {
        printf("Digite uma opção:\n");
        printf("0 - para encerrar\n");
        printf("1 - para cadastrar aluno\n");
        printf("2 - para listar aluno\n");
        printf("3 - para cadastrar disciplina\n");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:
            sair = 1;
            break;

        case 1:
            if (qtdAlunos == TAM_LISTA_ALUNOS)
            {
                printf("A quantidade de alunos atingiu o limite\n");
            }
            else
            {
                listaAlunos[qtdAlunos].id = codigoAluno;

                printf("Matricula:\n");
                scanf("%d", &listaAlunos[qtdAlunos].matricula);

                printf("Nome:\n");
                scanf("%s", listaAlunos[qtdAlunos].nome);

                printf("Sexo (M/F):\n");
                scanf(" %c", &listaAlunos[qtdAlunos].sexo);

                printf("Data de Nascimento (dd/mm/aaaa):\n");
                scanf("%s", listaAlunos[qtdAlunos].data_nascimento);

                printf("CPF (somente números):\n");
                scanf("%s", listaAlunos[qtdAlunos].cpf);

                qtdAlunos++;
                codigoAluno++;
            }
            break;

        case 2:
            if (qtdAlunos == 0)
            {
                printf("A lista de alunos está vazia\n");
            }
            else
            {
                for (int i = 0; i < qtdAlunos; i++)
                {
                    printf("Matricula aluno: %d\n", listaAlunos[i].matricula);
                    printf("Nome aluno: %s\n", listaAlunos[i].nome);
                    printf("Sexo aluno: %c\n", listaAlunos[i].sexo);
                    printf("Data de Nascimento aluno: %s\n", listaAlunos[i].data_nascimento);
                    printf("CPF aluno: %s\n", listaAlunos[i].cpf);
                }
            }
            break;

        default:
            printf("Opção inválida\n");
            break;
        }
    }

    return 0;
}