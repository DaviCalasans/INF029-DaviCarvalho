#include "disciplina.h"
#include <stdio.h>
#include <stdlib.h>

void listar_disciplinas_lotadas_com_prof(int qtdDisciplinas, Disciplina *listaDisciplinas) {
    int encontradas = 0;

    printf("\n==================================================\n");
    printf("     DISCIPLINAS LOTADAS E COM PROFESSOR (40+ vagas)\n");
    printf("==================================================\n");

    for (int i = 0; i < qtdDisciplinas; i++) {
        
        if (listaDisciplinas[i].professor_responsavel != NULL && 
            listaDisciplinas[i].qtd_alunos_matriculados >= 40) {
            
            printf("ID: %d | Disciplina: %-15s | Prof: %-15s | Vagas Ocupadas: %d\n",
                   listaDisciplinas[i].id,
                   listaDisciplinas[i].nome,
                   listaDisciplinas[i].professor_responsavel->nome,
                   listaDisciplinas[i].qtd_alunos_matriculados);
            encontradas++;
        }
    }

    if (encontradas == 0) {
        printf(" -> Nenhuma disciplina atingiu 40 alunos com professor vinculado.\n");
    }
    printf("==================================================\n");
}
void detalhar_disciplina(Disciplina *d) {
    printf("\n==================================================\n");
    printf("              FICHA DA DISCIPLINA                 \n");
    printf("==================================================\n");
    printf("ID: %d | Codigo: %d\n", d->id, d->codigo);
    printf("Nome: %s\n", d->nome);
    printf("Semestre: %d\n", d->semestre);
    
    if (d->professor_responsavel != NULL) {
        printf("Professor Responsavel: %s\n", d->professor_responsavel->nome);
    } else {
        printf("Professor Responsavel: [Nenhum professor vinculado]\n");
    }
    printf("--------------------------------------------------\n");

    printf("ALUNOS MATRICULADOS (%d de %d vagas preenchidas):\n", 
           d->qtd_alunos_matriculados, MAX_ALUNOS_POR_DISCIPLINA);

    if (d->qtd_alunos_matriculados == 0) {
        printf(" -> Nenhuma matricula registrada ate o momento.\n");
    } else {
        for (int i = 0; i < d->qtd_alunos_matriculados; i++) {
            printf(" %d. ID: %d | Nome: %-20s | Mat: %d\n", 
                   i + 1, // Apenas para numerar a lista (1, 2, 3...)
                   d->alunos_matriculados[i]->id,
                   d->alunos_matriculados[i]->nome,
                   d->alunos_matriculados[i]->matricula);
        }
    }
    printf("==================================================\n\n");
}
bool remover_aluno_da_disciplina(Disciplina *d, int idAluno) {
    for (int i = 0; i < d->qtd_alunos_matriculados; i++) {
        if (d->alunos_matriculados[i]->id == idAluno) {
            d->alunos_matriculados[i]->qtd_disciplinas_matriculadas--;
            
            for (int j = i; j < d->qtd_alunos_matriculados - 1; j++) {
                d->alunos_matriculados[j] = d->alunos_matriculados[j + 1];
            }

            d->qtd_alunos_matriculados--;

            d->alunos_matriculados[d->qtd_alunos_matriculados] = NULL;
            
            return true;
        }
    }
    return false;
}

bool matricular_aluno_na_disciplina(Disciplina *d, Aluno *a) {
    if (d->qtd_alunos_matriculados >= MAX_ALUNOS_POR_DISCIPLINA) {
        printf("Erro: Turma lotada!\n");
        return false;
    }

    for (int i = 0; i < d->qtd_alunos_matriculados; i++) {
        if (d->alunos_matriculados[i]->id == a->id) {
            printf("Erro: Aluno já matriculado nesta disciplina!\n");
            return false;
        }
    }

    d->alunos_matriculados[d->qtd_alunos_matriculados] = a;
    d->qtd_alunos_matriculados++;
    a->qtd_disciplinas_matriculadas++;
    return true;
}

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

void menuDisciplina(Disciplina *listaDisciplinas, int *qtdDisciplinas, int *codigoDisciplina, Professor *listaProfessores, int qtdProfessores,Aluno *listaAlunos, int qtdAlunos)
{
    int opcao = 0;

    while (opcao >= 0)
    {
        printf("\n--- MENU DISCIPLINAS ---\n");
        printf("0 - Para voltar ao menu principal\n");
        printf("1 - Para cadastrar disciplina\n");
        printf("2 - Para listar disciplinas cadastradas\n");
        printf("3 - Para atualizar disciplina\n");
        printf("4 - Para deletar disciplina\n");
        printf("5 - Para matricular aluno\n");
        printf("6 - Para remover aluno\n");
        printf("7 - Para detalhar disciplina\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:
            opcao = -1;
            break;

        case 1:
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

                int idBuscaProf;
                Professor *profEncontrado = NULL;

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

                listaDisciplinas[*qtdDisciplinas].professor_responsavel = profEncontrado;
                
                for (int i = 0; i < MAX_ALUNOS_POR_DISCIPLINA; i++) {
                    listaDisciplinas[*qtdDisciplinas].alunos_matriculados[i] = NULL;
                }

                listaDisciplinas[*qtdDisciplinas].qtd_alunos_matriculados = 0;

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
        case 5: 
        {
            if (*qtdDisciplinas == 0 || qtdAlunos == 0) {
                printf("Erro: É necessário ter pelo menos uma disciplina e um aluno cadastrados.\n");
                break;
            }

            int idDisc, idAlu;
            printf("\n--- Matrícula de Aluno ---\n");
            listar_disciplinas(*qtdDisciplinas, listaDisciplinas);
            printf("Digite o ID da Disciplina: ");
            scanf("%d", &idDisc);

            Disciplina *dPos = busca_disciplina_por_id(*qtdDisciplinas, listaDisciplinas, idDisc);

            if (dPos != NULL) {
                listar_alunos(qtdAlunos, listaAlunos);
                printf("Digite o ID do Aluno: ");
                scanf("%d", &idAlu);

                Aluno *aPos = busca_aluno_por_id(qtdAlunos, listaAlunos, idAlu);

                if (aPos != NULL) {
                    if (matricular_aluno_na_disciplina(dPos, aPos)) {
                        printf("Aluno %s matriculado em %s com sucesso!\n", aPos->nome, dPos->nome);
                    }
                } else {
                    printf("Erro: Aluno não encontrado.\n");
                }
            } else {
                printf("Erro: Disciplina não encontrada.\n");
            }
            break;
        }

        case 6: 
        {
            if (*qtdDisciplinas == 0) {
                printf("Erro: Não há disciplinas cadastradas.\n");
                break;
            }

            int idDisc, idAlu;
            printf("\n--- Remover Aluno de Disciplina ---\n");
            listar_disciplinas(*qtdDisciplinas, listaDisciplinas);
            printf("Digite o ID da Disciplina: ");
            scanf("%d", &idDisc);

            Disciplina *dPos = busca_disciplina_por_id(*qtdDisciplinas, listaDisciplinas, idDisc);

            if (dPos != NULL) {
                if (dPos->qtd_alunos_matriculados == 0) {
                    printf("Aviso: Esta disciplina não possui alunos matriculados.\n");
                } else {
                    printf("\nAlunos matriculados em %s:\n", dPos->nome);
                    for (int i = 0; i < dPos->qtd_alunos_matriculados; i++) {
                        printf("ID: %d | Nome: %s\n", 
                               dPos->alunos_matriculados[i]->id, 
                               dPos->alunos_matriculados[i]->nome);
                    }

                    printf("\nDigite o ID do Aluno que deseja remover: ");
                    scanf("%d", &idAlu);

                    if (remover_aluno_da_disciplina(dPos, idAlu)) {
                        printf("Aluno removido da disciplina com sucesso!\n");
                    } else {
                        printf("Erro: Aluno com ID %d não está matriculado nesta disciplina.\n", idAlu);
                    }
                }
            } else {
                printf("Erro: Disciplina não encontrada.\n");
            }
            break;
        }

        case 7:
        {
            if (*qtdDisciplinas == 0) {
                printf("A lista de disciplinas esta vazia.\n");
                break;
            }

            int idBusca;
            printf("\n--- Visualizar Turma ---\n");
            listar_disciplinas(*qtdDisciplinas, listaDisciplinas); 
            
            printf("Digite o ID da disciplina para ver os detalhes: ");
            scanf("%d", &idBusca);

            Disciplina *discEncontrada = busca_disciplina_por_id(*qtdDisciplinas, listaDisciplinas, idBusca);

            if (discEncontrada != NULL) {
                detalhar_disciplina(discEncontrada);
            } else {
                printf("Erro: Disciplina com ID %d nao encontrada.\n", idBusca);
            }
            break;
        }

        case 8:
        {
            if (*qtdDisciplinas == 0) {
                printf("A lista de disciplinas esta vazia.\n");
            } else {
                listar_disciplinas_lotadas_com_prof(*qtdDisciplinas, listaDisciplinas);
            }
            break;
        }
        default:
            printf("Opcao invalida!\n");
            break;
        }
    }
}