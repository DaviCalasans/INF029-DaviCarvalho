#include "professor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void listar_aniversariantes_do_mes_prof(int qtdProfessores, Professor *listaProfessores, int mesBusca) {
    int encontrados = 0;
    char *meses[] = {"", "Janeiro", "Fevereiro", "Marco", "Abril", "Maio", "Junho", 
                     "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};

    printf("\n--- ANIVERSARIANTES DE %s (PROFESSORES) ---\n", meses[mesBusca]);

    for (int i = 0; i < qtdProfessores; i++) {
        if (listaProfessores[i].data_nascimento.mes == mesBusca) {
            printf("Dia %02d - %s (ID: %d)\n", 
                   listaProfessores[i].data_nascimento.dia, 
                   listaProfessores[i].nome, 
                   listaProfessores[i].id);
            encontrados++;
        }
    }

    if (encontrados == 0) {
        printf(" -> Nenhum professor faz aniversario neste mes.\n");
    }
    printf("-------------------------------------------------\n");
}
int comparar_datas_prof(Data d1, Data d2)
{
    if (d1.ano != d2.ano)
        return d1.ano - d2.ano;
    if (d1.mes != d2.mes)
        return d1.mes - d2.mes;
    return d1.dia - d2.dia;
}

void listar_professores_por_data(int qtdProfessores, Professor *listaProfessores)
{
    if (qtdProfessores <= 1)
    {
        listar_professores(qtdProfessores, listaProfessores);
        return;
    }

    for (int i = 0; i < qtdProfessores - 1; i++)
    {
        for (int j = i + 1; j < qtdProfessores; j++)
        {
            if (comparar_datas_prof(listaProfessores[i].data_nascimento, listaProfessores[j].data_nascimento) > 0)
            {
                Professor temp = listaProfessores[i];
                listaProfessores[i] = listaProfessores[j];
                listaProfessores[j] = temp;
            }
        }
    }

    printf("\n--- PROFESSORES ORDENADOS POR IDADE (Mais velhos primeiro) ---\n");
    listar_professores(qtdProfessores, listaProfessores);
}

void listar_professores_ordenados_por_nome(int qtdProfessores, Professor *listaProfessores)
{
    if (qtdProfessores <= 1)
    {
        listar_professores(qtdProfessores, listaProfessores);
        return;
    }

    for (int i = 0; i < qtdProfessores - 1; i++)
    {
        for (int j = i + 1; j < qtdProfessores; j++)
        {
            if (strcmp(listaProfessores[i].nome, listaProfessores[j].nome) > 0)
            {
                Professor temp = listaProfessores[i];
                listaProfessores[i] = listaProfessores[j];
                listaProfessores[j] = temp;
            }
        }
    }

    printf("\n--- PROFESSORES ORDENADOS DE A a Z ---\n");
    listar_professores(qtdProfessores, listaProfessores);
}

void listar_professores_por_sexo(int qtdProfessores, Professor *listaProfessores, char sexoBuscado)
{
    int encontrados = 0;
    char sexoMaiusculo = toupper(sexoBuscado);

    printf("\n--- RESULTADO DA BUSCA (SEXO: %c) ---\n", sexoMaiusculo);

    for (int i = 0; i < qtdProfessores; i++)
    {
        if (toupper(listaProfessores[i].sexo) == sexoMaiusculo)
        {
            printf("ID: %d | Matricula: %d | Nome: %s | Sexo: %c\n",
                   listaProfessores[i].id,
                   listaProfessores[i].matricula,
                   listaProfessores[i].nome,
                   listaProfessores[i].sexo);
            encontrados++;
        }
    }

    if (encontrados == 0)
    {
        printf(" -> Nenhum professor do sexo '%c' foi encontrado.\n", sexoMaiusculo);
    }
    printf("--------------------------------------\n");
}

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
        printf("ID: %d | Matricula: %d | Nome: %s | Sexo: %c | Data de Nasc.: %02d/%02d/%04d | CPF: %s\n",
               listaProfessores[i].id,
               listaProfessores[i].matricula,
               listaProfessores[i].nome,
               listaProfessores[i].sexo,
               listaProfessores[i].data_nascimento.dia,
               listaProfessores[i].data_nascimento.mes,
               listaProfessores[i].data_nascimento.ano,
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
        printf("5 - Para listar por sexo\n");
        printf("6 - Para listar ordenado por nome\n");
        printf("7 - Para listar ordenado por data de nascimento\n");
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
                scanf("%02d/%02d/%04d",
                      &listaProfessores[*qtdProfessores].data_nascimento.dia,
                      &listaProfessores[*qtdProfessores].data_nascimento.mes,
                      &listaProfessores[*qtdProfessores].data_nascimento.ano);

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
                        scanf("%02d/%02d/%04d",
                              &profEncontrado->data_nascimento.dia,
                              &profEncontrado->data_nascimento.mes,
                              &profEncontrado->data_nascimento.ano);
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
        case 5:
        {
            if (*qtdProfessores == 0)
            {
                printf("A lista de professores esta vazia.\n");
            }
            else
            {
                char sexoBusca;
                printf("\nQual sexo voce deseja listar? (M/F): ");
                scanf(" %c", &sexoBusca);
                listar_professores_por_sexo(*qtdProfessores, listaProfessores, sexoBusca);
            }
            break;
        }

        case 6:
        {
            if (*qtdProfessores == 0)
            {
                printf("A lista de professores esta vazia.\n");
            }
            else
            {
                listar_professores_ordenados_por_nome(*qtdProfessores, listaProfessores);
            }
            break;
        }

        case 7:
        {
            if (*qtdProfessores == 0)
            {
                printf("A lista de professores esta vazia.\n");
            }
            else
            {
                listar_professores_por_data(*qtdProfessores, listaProfessores);
            }
            break;
        }

        case 8:
        {
            if (*qtdProfessores == 0) {
                printf("A lista de professores esta vazia.\n");
            } else {
                int mes;
                do {
                    printf("Digite o numero do mes que deseja buscar (1 a 12): ");
                    scanf("%d", &mes);
                    
                    if (mes < 1 || mes > 12) {
                        printf("Erro: Mes invalido! Digite um valor entre 1 e 12.\n");
                    }
                } while (mes < 1 || mes > 12);

                listar_aniversariantes_do_mes_prof(*qtdProfessores, listaProfessores, mes);
            }
            break;
        }

        default:
            printf("Opcao invalida!\n");
            break;
        }
    }
}