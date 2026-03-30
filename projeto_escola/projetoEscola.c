#include <stdio.h>
#include <stdlib.h>

#define TAM_LISTA_ALUNOS 3

typedef struct
{
    int id;
    int matricula;
    char nome[100];
    char sexo;
    char data_nascimento[11];
    char cpf[12];
} Aluno;

void listar_alunos(int qtdAlunos, Aluno * listaAlunos)
{
    for (int i = 0; i < qtdAlunos; i++)
    {
        printf("ID: %d\n", listaAlunos[i].id);
        printf("Matricula aluno: %d\n", listaAlunos[i].matricula);
        printf("Nome aluno: %s\n", listaAlunos[i].nome);
        printf("Sexo aluno: %c\n", listaAlunos[i].sexo);
        printf("Data de Nascimento aluno: %s\n", listaAlunos[i].data_nascimento);
        printf("CPF aluno: %s\n", listaAlunos[i].cpf);
    }
};

void busca_aluno_por_id(int qtdAlunos, Aluno * listaAlunos, int id)
{
    for (int i = 0; i < qtdAlunos; i++)
    {
        if (id == listaAlunos[i].id)
        {
            printf("ID: %d\n", listaAlunos[i].id);
            printf("Matricula aluno: %d\n", listaAlunos[i].matricula);
            printf("Nome aluno: %s\n", listaAlunos[i].nome);
            printf("Sexo aluno: %c\n", listaAlunos[i].sexo);
            printf("Data de Nascimento aluno: %s\n", listaAlunos[i].data_nascimento);
            printf("CPF aluno: %s\n", listaAlunos[i].cpf);
            break;
        } else {
            printf("ID %d não encontrado!", id);
        }
    }
}

int main()
{
    int sair = 0;
    int opcao;
    int qtdAlunos = 0;
    int codigoAluno = 1;
    int idAlunoEscolhido;

    Aluno listaAlunos[TAM_LISTA_ALUNOS];

    while (sair == 0)
    {
        printf("Digite uma opção:\n");
        printf("0 - para encerrar\n");
        printf("1 - para cadastrar aluno\n");
        printf("2 - para listar aluno\n");
        printf("3 - para atualizar aluno\n");
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
                listar_alunos(qtdAlunos, listaAlunos);
            }
            break;

        case 3:
            if (qtdAlunos == 0)
            {
                printf("A lista de alunos está vazia\n");
            }
            else
            {
                printf("Qual aluno você quer atualizar?\n");
                listar_alunos(qtdAlunos, listaAlunos);
                scanf("%d", &idAlunoEscolhido);
                printf("O id escolhido foi: %d", idAlunoEscolhido);
                busca_aluno_por_id(qtdAlunos, listaAlunos, idAlunoEscolhido);
                printf("Qual informação você quer atualizar?");
                
            }
            break;

        default:
            printf("Opção inválida\n");
            break;
        }
    }

    return 0;
}