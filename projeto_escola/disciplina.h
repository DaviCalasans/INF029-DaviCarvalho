#ifndef DISCIPLINA_H
#define DISCIPLINA_H
#include <stdbool.h>
#include "professor.h"
#include "aluno.h"

#define TAM_LISTA_DISCIPLINA 3
#define MAX_ALUNOS_POR_DISCIPLINA 40

typedef struct
{
    int id;
    int codigo;
    char nome[100];
    int semestre;
    Professor *professor_responsavel;
    Aluno *alunos_matriculados[MAX_ALUNOS_POR_DISCIPLINA];
    int qtd_alunos_matriculados;
} Disciplina;

void detalhar_disciplina(Disciplina *d);
bool matricular_aluno_na_disciplina(Disciplina *d, Aluno *a);
bool remover_aluno_da_disciplina(Disciplina *d, int idAluno);
void listar_disciplinas(int qtdDisciplinas, Disciplina *listaDisciplinas);
Disciplina *busca_disciplina_por_id(int qtdDisciplinas, Disciplina *listaDisciplinas, int id);
bool deletar_disciplina(int *qtdDisciplinas, Disciplina *listaDisciplinas, int id);
void menuDisciplina(Disciplina *listaDisciplinas, int *qtdDisciplinas, int *codigoDisciplina,
Professor *listaProfessores, int qtdProfessores,Aluno *listaAlunos, int qtdAlunos);

#endif