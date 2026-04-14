#include "disciplina.h"
#include <stdio.h>
#include <stdlib.h>

void listar_disciplinas(int qtdDisciplinas, Disciplina *listaDisciplinas)
{
    for (int i = 0; i < qtdDisciplinas; i++)
    {
        printf("ID: %d | Codigo: %d | Nome: %s | Semestre: %d | ",
               listaDisciplinas[i].id,
               listaDisciplinas[i].codigo,
               listaDisciplinas[i].nome,
               listaDisciplinas[i].semestre);

        // Verificação de segurança CRUCIAL para ponteiros
        if (listaDisciplinas[i].professor_responsavel != NULL) {
            printf("Professor: %s\n", listaDisciplinas[i].professor_responsavel->nome);
        } else {
            printf("Professor: [Nenhum professor vinculado]\n");
        }
    }
}

Disciplina *busca_disciplina_por_id(int qtdDisciplinas, Disciplina *listaDisciplinas, int id)
{
    for (int i = 0; i < qtdDisciplinas; i++)
    {
        if (id == listaDisciplinas[i].id)
        {
            return &listaDisciplinas[i];
        }
    }
    return NULL;
}

bool deletar_disciplina(int *qtdDisciplinas, Disciplina *listaDisciplinas, int id)
{
    for (int i = 0; i < *qtdDisciplinas; i++)
    {
        if (listaDisciplinas[i].id == id)
        {
            for (int j = i; j < *qtdDisciplinas - 1; j++)
            {
                listaDisciplinas[j] = listaDisciplinas[j + 1];
            }
            (*qtdDisciplinas)--;
            return true;
        }
    }
    return false;
}

void menuDisciplina(Disciplina *listaDisciplinas, int *qtdDisciplinas, int *codigoDisciplina, 
                    Professor *listaProfessores, int qtdProfessores)
{
    int opcao = 0;

    while (opcao >= 0)
    {
        printf("\n--- MENU DISCIPLINAS ---\n");
        printf("0 - Para voltar ao menu principal\n");
        printf("1 - Para cadastrar disciplina\n");
        printf("2 - Para listar disciplinas\n");
        printf("3 - Para atualizar disciplina\n");
        printf("4 - Para deletar disciplina\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:
            opcao = -1;
            break;

        case 1:
            // Trava de segurança: impede o cadastro se não houver professores!
            if (qtdProfessores == 0)
            {
                printf("Erro: Nao ha professores cadastrados! Cadastre um professor primeiro.\n");
            }
            else if (*qtdDisciplinas == TAM_LISTA_DISCIPLINA)
            {
                printf("Erro: A quantidade de disciplinas atingiu o limite maximo!\n");
            }
            else
            {
                listaDisciplinas[*qtdDisciplinas].id = *codigoDisciplina;

                printf("Codigo da Disciplina:\n");
                scanf("%d", &listaDisciplinas[*qtdDisciplinas].codigo);

                printf("Nome da Disciplina:\n");
                scanf(" %99[^\n]", listaDisciplinas[*qtdDisciplinas].nome);

                printf("Semestre:\n");
                scanf("%d", &listaDisciplinas[*qtdDisciplinas].semestre);

                // --- LÓGICA DE VÍNCULO COM O PROFESSOR ---
                int idBuscaProf;
                Professor *profEncontrado = NULL;

                // Fica no loop até o usuário digitar um ID válido
                while (profEncontrado == NULL)
                {
                    printf("\n--- Escolha o Professor Responsavel ---\n");
                    listar_professores(qtdProfessores, listaProfessores);
                    
                    printf("Digite o ID do professor para esta disciplina: ");
                    scanf("%d", &idBuscaProf);

                    profEncontrado = busca_professor_por_id(qtdProfessores, listaProfessores, idBuscaProf);

                    if (profEncontrado == NULL)
                    {
                        printf("Erro: Professor com ID %d nao encontrado! Tente novamente.\n", idBuscaProf);
                    }
                }

                // O ponteiro da disciplina recebe o endereço do professor
                listaDisciplinas[*qtdDisciplinas].professor_responsavel = profEncontrado;
                
                printf("Professor %s vinculado com sucesso!\n", profEncontrado->nome);
                printf("Disciplina cadastrada com sucesso!\n");

                (*qtdDisciplinas)++;
                (*codigoDisciplina)++;
            }
            break;

        case 2:
        { // ESCOPO DE BLOCO
            if (*qtdDisciplinas == 0)
            {
                printf("A lista de disciplinas esta vazia.\n");
            }
            else
            {
                printf("\n--- LISTA DE DISCIPLINAS ---\n");
                listar_disciplinas(*qtdDisciplinas, listaDisciplinas);
            }
            break;
        }

        case 3:
        { // ESCOPO DE BLOCO
            if (*qtdDisciplinas == 0)
            {
                printf("A lista de disciplinas esta vazia.\n");
            }
            else
            {
                int idBusca;
                printf("Qual disciplina voce quer atualizar?\n");
                listar_disciplinas(*qtdDisciplinas, listaDisciplinas);
                
                printf("Digite o ID da disciplina: ");
                scanf("%d", &idBusca);

                Disciplina *discEncontrada = busca_disciplina_por_id(*qtdDisciplinas, listaDisciplinas, idBusca);
                
                if (discEncontrada != NULL)
                {
                    int opcaoAtualizar;
                    printf("\nDisciplina encontrada! (Nome: %s)\n", discEncontrada->nome);
                    printf("Qual informacao voce quer atualizar?\n");
                    printf("1 - Codigo\n2 - Nome\n3 - Semestre\n4 - Professor Responsavel\n");
                    printf("Opcao: ");
                    scanf("%d", &opcaoAtualizar);

                    switch (opcaoAtualizar)
                    {
                    case 1:
                        printf("Digite o novo Codigo: ");
                        scanf("%d", &discEncontrada->codigo);
                        printf("Codigo atualizado com sucesso!\n");
                        break;
                    case 2:
                        printf("Digite o novo Nome: ");
                        scanf(" %99[^\n]", discEncontrada->nome);
                        printf("Nome atualizado com sucesso!\n");
                        break;
                    case 3:
                        printf("Digite o novo Semestre: ");
                        scanf("%d", &discEncontrada->semestre);
                        printf("Semestre atualizado com sucesso!\n");
                        break;
                    case 4:
                    {   // Novo bloco porque criamos variáveis aqui dentro
                        if (qtdProfessores == 0) {
                            printf("Erro: Nao ha professores cadastrados para vincular.\n");
                            break;
                        }

                        int idNovoProf;
                        Professor *profNovo = NULL;

                        while (profNovo == NULL)
                        {
                            printf("\n--- Escolha o Novo Professor ---\n");
                            listar_professores(qtdProfessores, listaProfessores); 
                            
                            printf("Digite o ID do novo professor: ");
                            scanf("%d", &idNovoProf);

                            profNovo = busca_professor_por_id(qtdProfessores, listaProfessores, idNovoProf);

                            if (profNovo == NULL) {
                                printf("Erro: Professor nao encontrado! Tente novamente.\n");
                            }
                        }

                        // Atualiza o ponteiro
                        discEncontrada->professor_responsavel = profNovo;
                        printf("Professor %s vinculado com sucesso!\n", profNovo->nome);
                        break;
                    }
                    default:
                        printf("Opcao invalida! Nenhuma alteracao foi feita.\n");
                        break;
                    }
                }
                else
                {
                    printf("Erro: Disciplina com ID %d nao encontrada.\n", idBusca);
                }
            }
            break;
        }

        case 4:
        { // ESCOPO DE BLOCO
            if (*qtdDisciplinas == 0)
            {
                printf("A lista de disciplinas esta vazia.\n");
            }
            else
            {
                int idBusca;
                printf("Qual disciplina voce deseja DELETAR?\n");
                listar_disciplinas(*qtdDisciplinas, listaDisciplinas);
                
                printf("Digite o ID da disciplina: ");
                scanf("%d", &idBusca);

                if (deletar_disciplina(qtdDisciplinas, listaDisciplinas, idBusca))
                {
                    printf("Disciplina deletada com sucesso!\n");
                }
                else
                {
                    printf("Erro: Disciplina com ID %d nao encontrada. Exclusao abortada.\n", idBusca);
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