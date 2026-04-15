#include <stdio.h>
#include <stdlib.h>
#include "aluno.h"
#include "professor.h"
#include "disciplina.h"


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
        printf("0 - Sair\n1 - Alunos\n2 - Professores\n3 - Disciplinas\n");
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
        }
    }

    free(listaAlunos);
    return 0;
}