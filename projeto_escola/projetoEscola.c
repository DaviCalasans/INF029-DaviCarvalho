#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM_LISTA_ALUNOS 3
#define TAM_LISTA_PROFESSOR 3

typedef struct
{
    int id;
    int matricula;
    char nome[100];
    char sexo;
    char data_nascimento[11];
    char cpf[12];
} Aluno;

typedef struct
{
    int id;
    int matricula;
    char nome[100];
    char sexo;
    char data_nascimento[11];
    char cpf[12];
} Professor;

bool deletar_aluno(int *qtdAlunos, Aluno *listaAlunos, int id)
{
    for (int i = 0; i < *qtdAlunos; i++)
    {
        if(listaAlunos[i].id == id){
            for(int j = i; j < *qtdAlunos - 1;j++){
                listaAlunos[j] = listaAlunos[j + 1];
            }
        (*qtdAlunos)--;
        return true;
        }
    }

    return false;
}

void listar_alunos(int qtdAlunos, Aluno *listaAlunos)
{
    for (int i = 0; i < qtdAlunos; i++)
    {
        printf("ID: %d | Matricula aluno: %d | Nome aluno: %s | Sexo aluno: %c | Data de Nascimento aluno: %s | CPF aluno: %s\n",
               listaAlunos[i].id,
               listaAlunos[i].matricula,
               listaAlunos[i].nome,
               listaAlunos[i].sexo,
               listaAlunos[i].data_nascimento,
               listaAlunos[i].cpf);
    }
};

Aluno *busca_aluno_por_id(int qtdAlunos, Aluno *listaAlunos, int id)
{
    bool achou = false;
    for (int i = 0; i < qtdAlunos; i++)
    {
        if (id == listaAlunos[i].id)
        {
            return &listaAlunos[i];
        }
    }

    return NULL;
}

void menuAlunos(Aluno *listaAlunos, int *qtdAlunos, int *codigoAluno)
{
    int opcao = 0;
    printf("Menu alunos \n");
    while (opcao >= 0)
    {
        printf("Digite uma opção:\n");
        printf("0 - Para voltar ao menu principal\n");
        printf("1 - Para cadastrar aluno\n");
        printf("2 - Para listar aluno\n");
        printf("3 - Para atualizar aluno\n");
        printf("4 - Para deletar aluno\n");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:
            opcao = -1;
            break;

        case 1:
            if (*qtdAlunos == TAM_LISTA_ALUNOS)
            {
                printf("A quantidade de alunos atingiu o limite\n");
            }
            else
            {
                listaAlunos[*qtdAlunos].id = *codigoAluno;

                printf("Matricula:\n");
                scanf("%d", &listaAlunos[*qtdAlunos].matricula);

                printf("Nome:\n");
                scanf(" %99[^\n]", listaAlunos[*qtdAlunos].nome);

                printf("Sexo (M/F):\n");
                scanf(" %c", &listaAlunos[*qtdAlunos].sexo);

                printf("Data de Nascimento (dd/mm/aaaa):\n");
                scanf(" %10s", listaAlunos[*qtdAlunos].data_nascimento);

                printf("CPF (somente números):\n");
                scanf(" %11s", listaAlunos[*qtdAlunos].cpf);

                (*qtdAlunos)++;
                (*codigoAluno)++;
            }
            break;

        case 2:
            if (*qtdAlunos == 0)
            {
                printf("A lista de alunos está vazia\n");
            }
            else
            {
                listar_alunos(*qtdAlunos, listaAlunos);
            }
            break;

        case 3:
        {
            int idAlunoListar;
            if (*qtdAlunos == 0)
            {
                printf("A lista de alunos está vazia\n");
            }
            else
            {
                int opcaoAtualizar;
                printf("Qual aluno você quer atualizar?\n");
                listar_alunos(*qtdAlunos, listaAlunos);
                scanf("%d", &idAlunoListar);
                printf("O id escolhido foi: %d\n", idAlunoListar);
                Aluno *alunoEncontrado = busca_aluno_por_id(*qtdAlunos, listaAlunos, idAlunoListar);
                if (alunoEncontrado != NULL)
                {
                    printf("Aluno encontrado!\n");
                    printf("Qual informação você quer atualizar?\n");
                    printf("1 - para Matrícula\n");
                    printf("2 - para Nome\n");
                    printf("3 - para Data de Nascimento\n");
                    printf("4 - para Sexo\n");
                    printf("5 - para CPF\n");
                    scanf("%d", &opcaoAtualizar);

                    switch (opcaoAtualizar)
                    {
                    case 1:
                        printf("Digite a nova Matricula: ");
                        scanf("%d", &alunoEncontrado->matricula);
                        printf("Matricula atualizada com sucesso!\n");
                        break;

                    case 2:
                        printf("Digite o novo Nome: ");
                        scanf(" %[^\n]", alunoEncontrado->nome);
                        printf("Nome atualizado com sucesso!\n");
                        break;

                    case 3:
                        printf("Digite a nova Data de Nascimento (DD/MM/AAAA): ");
                        scanf(" %10s", alunoEncontrado->data_nascimento);
                        printf("Data de Nascimento atualizada com sucesso!\n");
                        break;

                    case 4:
                        printf("Digite o novo Sexo (M/F): ");
                        scanf(" %c", &alunoEncontrado->sexo);
                        printf("Sexo atualizado com sucesso!\n");
                        break;

                    case 5:
                        printf("Digite o novo CPF (apenas numeros): ");
                        scanf(" %11s", alunoEncontrado->cpf);
                        printf("CPF atualizado com sucesso!\n");
                        break;

                    default:
                        printf("Opção inválida! Nenhuma alteração foi feita.\n");
                        break;
                    }
                }
                else
                {
                    printf("Erro: Aluno com ID %d nao encontrado.\n", idAlunoListar);
                }
            }
            break;
        }

        case 4:
        {
            int idDeletarAluno;
            printf("Qual aluno você quer deletar?");
            listar_alunos(*qtdAlunos, listaAlunos);
            printf("Digite o ID: ");
            scanf("%d", &idDeletarAluno);
            
            bool resultDeletar = deletar_aluno(qtdAlunos, listaAlunos, idDeletarAluno);

            if(!resultDeletar){
                printf("O ID: %d não foi encontrado \n", idDeletarAluno);
            } else {
                printf("O aluno foi deletado com sucesso! A quantida de alunos agora é %d \n", *qtdAlunos);
            }
        }
        break;

        default:
            printf("Opção inválida\n");
            break;
        }
    }
}

void menuProfessor(Professor *listaProfessores, int *qtdProfessor, int *codigoProfessor, int *idProfessorEscolhido)
{
}
int main()
{
    int sair = 0;
    int opcao;
    int qtdAlunos = 0;
    int codigoAluno = 1;
    int idAlunoEscolhido;

    int qtdProfessores = 0;
    int codigoProfessor = 1;
    int idProfessorEscolhido;
    Aluno *listaAlunos;
    listaAlunos = malloc(TAM_LISTA_ALUNOS * sizeof(Aluno));

    Professor *listaProfessores;
    listaProfessores = malloc(TAM_LISTA_PROFESSOR * sizeof(Professor));

    while (sair == 0)
    {
        printf("Digite uma opção:\n");
        printf("0 - para encerrar\n");
        printf("1 - Menu aluno\n");
        printf("2 - Menu professor\n");

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
            break;
        default:
            printf("Opção inválida\n");
            break;
        }
    }

    free(listaAlunos);

    return 0;
}