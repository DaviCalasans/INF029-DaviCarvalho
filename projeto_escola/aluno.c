#include "aluno.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void listar_alunos_poucas_disciplinas(int qtdAlunos, Aluno *listaAlunos)
{
    int encontrados = 0;

    printf("\n--- ALUNOS COM MENOS DE 3 MATRICULAS ---\n");
    for (int i = 0; i < qtdAlunos; i++)
    {
        if (listaAlunos[i].qtd_disciplinas_matriculadas < 3)
        {
            printf("ID: %d | Nome: %-20s | Matriculas: %d\n",
                   listaAlunos[i].id,
                   listaAlunos[i].nome,
                   listaAlunos[i].qtd_disciplinas_matriculadas);
            encontrados++;
        }
    }

    if (encontrados == 0)
    {
        printf("Todos os alunos estao matriculados em 3 ou mais disciplinas.\n");
    }
    printf("------------------------------------------\n");
}

void listar_aniversariantes_do_mes(int qtdAlunos, Aluno *listaAlunos, int mesBusca)
{
    int encontrados = 0;
    char *meses[] = {"", "Janeiro", "Fevereiro", "Marco", "Abril", "Maio", "Junho",
                     "Julho", "Agosto", "Setembro", "Outubro", "Novembro", "Dezembro"};

    printf("\n--- ANIVERSARIANTES DE %s ---\n", meses[mesBusca]);

    for (int i = 0; i < qtdAlunos; i++)
    {
        if (listaAlunos[i].data_nascimento.mes == mesBusca)
        {
            printf("Dia %02d - %s (ID: %d)\n",
                   listaAlunos[i].data_nascimento.dia,
                   listaAlunos[i].nome,
                   listaAlunos[i].id);
            encontrados++;
        }
    }

    if (encontrados == 0)
    {
        printf("Nenhum aluno faz aniversario neste mes.\n");
    }
    printf("---------------------------------------\n");
}

int comparar_datas(Data d1, Data d2)
{
    if (d1.ano != d2.ano)
        return d1.ano - d2.ano;

    if (d1.mes != d2.mes)
        return d1.mes - d2.mes;

    return d1.dia - d2.dia;
}

void listar_alunos_por_data(int qtdAlunos, Aluno *listaAlunos)
{
    if (qtdAlunos <= 1)
    {
        listar_alunos(qtdAlunos, listaAlunos);
        return;
    }

    for (int i = 0; i < qtdAlunos - 1; i++)
    {
        for (int j = i + 1; j < qtdAlunos; j++)
        {
            if (comparar_datas(listaAlunos[i].data_nascimento, listaAlunos[j].data_nascimento) > 0)
            {
                Aluno temp = listaAlunos[i];
                listaAlunos[i] = listaAlunos[j];
                listaAlunos[j] = temp;
            }
        }
    }

    printf("\n--- ALUNOS ORDENADOS POR IDADE (Mais velhos primeiro) ---\n");
    listar_alunos(qtdAlunos, listaAlunos);
}

void listar_alunos_ordenados_por_nome(int qtdAlunos, Aluno *listaAlunos)
{
    if (qtdAlunos <= 1)
    {
        listar_alunos(qtdAlunos, listaAlunos);
        return;
    }

    for (int i = 0; i < qtdAlunos - 1; i++)
    {
        for (int j = i + 1; j < qtdAlunos; j++)
        {
            if (strcmp(listaAlunos[i].nome, listaAlunos[j].nome) > 0)
            {
                Aluno temp = listaAlunos[i];
                listaAlunos[i] = listaAlunos[j];
                listaAlunos[j] = temp;
            }
        }
    }
    printf("\n--- ALUNOS ORDENADOS DE A a Z ---\n");
    listar_alunos(qtdAlunos, listaAlunos);
}

void listar_alunos_por_sexo(int qtdAlunos, Aluno *listaAlunos, char sexoBuscado)
{
    int encontrados = 0;

    char sexoMaiusculo = toupper(sexoBuscado);

    printf("\n--- RESULTADO DA BUSCA (SEXO: %c) ---\n", sexoMaiusculo);

    for (int i = 0; i < qtdAlunos; i++)
    {
        if (toupper(listaAlunos[i].sexo) == sexoMaiusculo)
        {
            printf("ID: %d | Matricula: %d | Nome: %s | Sexo: %c\n",
                   listaAlunos[i].id,
                   listaAlunos[i].matricula,
                   listaAlunos[i].nome,
                   listaAlunos[i].sexo);
            encontrados++;
        }
    }

    if (encontrados == 0)
    {
        printf(" -> Nenhum aluno do sexo '%c' foi encontrado.\n", sexoMaiusculo);
    }
    printf("--------------------------------------\n");
}

bool deletar_aluno(int *qtdAlunos, Aluno *listaAlunos, int id)
{
    for (int i = 0; i < *qtdAlunos; i++)
    {
        if (listaAlunos[i].id == id)
        {
            for (int j = i; j < *qtdAlunos - 1; j++)
            {
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
        printf("ID: %d | Matricula aluno: %d | Nome aluno: %s | Sexo aluno: %c | Data de Nasc: %02d/%02d/%04d\n | CPF aluno: %s\n",
               listaAlunos[i].id,
               listaAlunos[i].matricula,
               listaAlunos[i].nome,
               listaAlunos[i].sexo,
               listaAlunos[i].data_nascimento.dia,
               listaAlunos[i].data_nascimento.mes,
               listaAlunos[i].data_nascimento.ano,
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
        printf("5 - para listar por sexo\n");
        printf("6 - para listar ordenado por nome\n");
        printf("7 - para listar por data de nascimento\n");
        printf("8 - para listar aniversariantes do mês\n");
        printf("9 - para listar alunos cadastrados em menos de 3 disciplinas\n");
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

                char sexoLido;
                do
                {
                    printf("Sexo (M/F):\n");
                    scanf(" %c", &sexoLido);

                    sexoLido = toupper(sexoLido);

                    if (sexoLido != 'M' && sexoLido != 'F')
                    {
                        printf("Erro: Entrada invalida! Digite apenas 'M' para Masculino ou 'F' para Feminino.\n");
                    }

                } while (sexoLido != 'M' && sexoLido != 'F');

                listaAlunos[*qtdAlunos].sexo = sexoLido;

                printf("Data de Nascimento (dd/mm/aaaa):\n");
                scanf("%d/%d/%d",
                      &listaAlunos[*qtdAlunos].data_nascimento.dia,
                      &listaAlunos[*qtdAlunos].data_nascimento.mes,
                      &listaAlunos[*qtdAlunos].data_nascimento.ano);

                char cpfTemp[30];

                do
                {
                    printf("CPF (exatamente 11 numeros, sem pontos ou tracos):\n");
                    scanf(" %29s", cpfTemp); // Lê até 29 caracteres com segurança

                    if (strlen(cpfTemp) != 11)
                    {
                        printf("Erro: O CPF deve conter exatamente 11 digitos! Voce digitou %zu.\n", strlen(cpfTemp));
                    }

                } while (strlen(cpfTemp) != 11);

                strcpy(listaAlunos[*qtdAlunos].cpf, cpfTemp);

                listaAlunos[*qtdAlunos].qtd_disciplinas_matriculadas = 0;

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
                        scanf("%02d/%02d/%04d",
                              &alunoEncontrado->data_nascimento.dia,
                              &alunoEncontrado->data_nascimento.mes,
                              &alunoEncontrado->data_nascimento.ano);
                        printf("Data de Nascimento atualizada com sucesso!\n");
                        break;

                    case 4:
                        printf("Digite o novo Sexo (M/F): ");
                        scanf(" %c", &alunoEncontrado->sexo);
                        printf("Sexo atualizado com sucesso!\n");
                        break;

                    case 5:
                    {
                        char cpfTemp[30];
                        do
                        {
                            printf("Digite o novo CPF (exatamente 11 numeros, sem pontos ou tracos):\n");
                            scanf(" %29s", cpfTemp);

                            if (strlen(cpfTemp) != 11)
                            {
                                printf("Erro: O CPF deve conter exatamente 11 digitos! Voce digitou %zu.\n", strlen(cpfTemp));
                            }
                        } while (strlen(cpfTemp) != 11);

                        strcpy(alunoEncontrado->cpf, cpfTemp);
                        printf("CPF atualizado com sucesso!\n");
                        break;
                    }
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

            if (!resultDeletar)
            {
                printf("O ID: %d não foi encontrado \n", idDeletarAluno);
            }
            else
            {
                printf("O aluno foi deletado com sucesso! A quantida de alunos agora é %d \n", *qtdAlunos);
            }
        }
        break;

        case 5:
        {
            if (*qtdAlunos == 0)
            {
                printf("A lista de alunos esta vazia.\n");
            }
            else
            {
                char sexoBusca;
                printf("\nQual sexo voce deseja listar? (M/F): ");

                scanf(" %c", &sexoBusca);

                listar_alunos_por_sexo(*qtdAlunos, listaAlunos, sexoBusca);
            }
            break;
        }
        case 6:
        {
            if (*qtdAlunos == 0)
            {
                printf("A lista de alunos esta vazia.\n");
            }
            else
            {
                listar_alunos_ordenados_por_nome(*qtdAlunos, listaAlunos);
            }
            break;
        }
        case 7:
        {
            if (*qtdAlunos == 0)
            {
                printf("A lista de alunos esta vazia.\n");
            }
            else
            {
                // Chama a função mágica que construímos!
                listar_alunos_por_data(*qtdAlunos, listaAlunos);
            }
            break;
        }
        case 8:
        {
            if (*qtdAlunos == 0)
            {
                printf("A lista de alunos esta vazia.\n");
            }
            else
            {
                int mes;
                do
                {
                    printf("Digite o numero do mes (1-12): ");
                    scanf("%d", &mes);
                    if (mes < 1 || mes > 12)
                    {
                        printf("Mes invalido! Digite um valor entre 1 e 12.\n");
                    }
                } while (mes < 1 || mes > 12);

                listar_aniversariantes_do_mes(*qtdAlunos, listaAlunos, mes);
            }
            break;
        }

        case 9:
        {
            if (*qtdAlunos == 0)
            {
                printf("A lista de alunos esta vazia.\n");
            }
            else
            {
                listar_alunos_poucas_disciplinas(*qtdAlunos, listaAlunos);
            }
            break;
        }

        default:
            printf("Opção inválida\n");
            break;
        }
    }
}