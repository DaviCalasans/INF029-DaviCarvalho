#include "professor.h"
#include <stdio.h>
#include <stdlib.h>

bool deletar_professor(int *qtdProfessores, Professor *listaProfessores, int id)
{
    for (int i = 0; i < *qtdProfessores; i++)
    {
        if (listaProfessores[i].id == id)
        {
            for (int j = i; j < *qtdProfessores - 1; j++)
            {
                listaProfessores[j] = listaProfessores[j + 1];
            }
            (*qtdProfessores)--;
            return true;
        }
    }
    return false;
}

void listar_professores(int qtdProfessores, Professor *listaProfessores)
{
    for (int i = 0; i < qtdProfessores; i++)
    {
        printf("ID: %d | Matricula: %d | Nome: %s | Sexo: %c | Data de Nasc.: %s | CPF: %s\n",
               listaProfessores[i].id,
               listaProfessores[i].matricula,
               listaProfessores[i].nome,
               listaProfessores[i].sexo,
               listaProfessores[i].data_nascimento,
               listaProfessores[i].cpf);
    }
}

Professor *busca_professor_por_id(int qtdProfessores, Professor *listaProfessores, int id)
{
    for (int i = 0; i < qtdProfessores; i++)
    {
        if (id == listaProfessores[i].id)
        {
            return &listaProfessores[i];
        }
    }
    return NULL;
}

void menuProfessor(Professor *listaProfessores, int *qtdProfessores, int *codigoProfessor)
{
    int opcao = 0;
    
    while (opcao >= 0)
    {
        printf("\n--- MENU PROFESSORES ---\n");
        printf("0 - Para voltar ao menu principal\n");
        printf("1 - Para cadastrar professor\n");
        printf("2 - Para listar professores\n");
        printf("3 - Para atualizar professor\n");
        printf("4 - Para deletar professor\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:
            opcao = -1;
            break;

        case 1:
            if (*qtdProfessores == TAM_LISTA_PROFESSOR)
            {
                printf("Erro: A quantidade de professores atingiu o limite maximo!\n");
            }
            else
            {
                listaProfessores[*qtdProfessores].id = *codigoProfessor;

                printf("Matricula:\n");
                scanf("%d", &listaProfessores[*qtdProfessores].matricula);

                printf("Nome:\n");
                scanf(" %99[^\n]", listaProfessores[*qtdProfessores].nome);

                printf("Sexo (M/F):\n");
                scanf(" %c", &listaProfessores[*qtdProfessores].sexo);

                printf("Data de Nascimento (dd/mm/aaaa):\n");
                scanf(" %10s", listaProfessores[*qtdProfessores].data_nascimento);

                printf("CPF (somente numeros):\n");
                scanf(" %11s", listaProfessores[*qtdProfessores].cpf);

                (*qtdProfessores)++;
                (*codigoProfessor)++;
                printf("Professor cadastrado com sucesso!\n");
            }
            break;

        case 2:
        { 
            if (*qtdProfessores == 0)
            {
                printf("A lista de professores esta vazia.\n");
            }
            else
            {
                printf("\n--- LISTA DE PROFESSORES ---\n");
                listar_professores(*qtdProfessores, listaProfessores);
            }
            break;
        }

        case 3:
        { 
            if (*qtdProfessores == 0)
            {
                printf("A lista de professores esta vazia.\n");
            }
            else
            {
                int idBusca;
                printf("Qual professor voce quer atualizar?\n");
                listar_professores(*qtdProfessores, listaProfessores);
                
                printf("Digite o ID do professor: ");
                scanf("%d", &idBusca);

                Professor *profEncontrado = busca_professor_por_id(*qtdProfessores, listaProfessores, idBusca);
                
                if (profEncontrado != NULL)
                {
                    int opcaoAtualizar;
                    printf("\nProfessor encontrado! (Matricula: %d | Nome: %s)\n", profEncontrado->matricula, profEncontrado->nome);
                    printf("Qual informacao voce quer atualizar?\n");
                    printf("1 - Matricula\n2 - Nome\n3 - Data de Nascimento\n4 - Sexo\n5 - CPF\n");
                    printf("Opcao: ");
                    scanf("%d", &opcaoAtualizar);

                    switch (opcaoAtualizar)
                    {
                    case 1:
                        printf("Digite a nova Matricula: ");
                        scanf("%d", &profEncontrado->matricula);
                        printf("Matricula atualizada com sucesso!\n");
                        break;
                    case 2:
                        printf("Digite o novo Nome: ");
                        scanf(" %99[^\n]", profEncontrado->nome);
                        printf("Nome atualizado com sucesso!\n");
                        break;
                    case 3:
                        printf("Digite a nova Data de Nascimento (DD/MM/AAAA): ");
                        scanf(" %10s", profEncontrado->data_nascimento);
                        printf("Data de Nascimento atualizada com sucesso!\n");
                        break;
                    case 4:
                        printf("Digite o novo Sexo (M/F): ");
                        scanf(" %c", &profEncontrado->sexo);
                        printf("Sexo atualizado com sucesso!\n");
                        break;
                    case 5:
                        printf("Digite o novo CPF (apenas numeros): ");
                        scanf(" %11s", profEncontrado->cpf);
                        printf("CPF atualizado com sucesso!\n");
                        break;
                    default:
                        printf("Opcao invalida! Nenhuma alteracao foi feita.\n");
                        break;
                    }
                }
                else
                {
                    printf("Erro: Professor com ID %d nao encontrado.\n", idBusca);
                }
            }
            break;
        }

        case 4:
        {
            if (*qtdProfessores == 0)
            {
                printf("A lista de professores esta vazia.\n");
            }
            else
            {
                int idBusca;
                printf("Qual professor voce deseja DELETAR?\n");
                listar_professores(*qtdProfessores, listaProfessores);
                
                printf("Digite o ID do professor: ");
                scanf("%d", &idBusca);

                // Chama a função e já verifica o retorno booleano
                if (deletar_professor(qtdProfessores, listaProfessores, idBusca))
                {
                    printf("Professor deletado com sucesso!\n");
                }
                else
                {
                    printf("Erro: Professor com ID %d nao encontrado. Exclusao abortada.\n", idBusca);
                }
            }
            break;
        }

        default:
            printf("Opcao invalida!\n");
            break;
        }
    }
}