#ifndef DISCIPLINA_H
#define DISCIPLINA_H
#include <stdbool.h>
#include "professor.h"

#define TAM_LISTA_DISCIPLINA 3

typedef struct{
    int id;
    int codigo;
    char nome[100];
    int semestre;
    Professor * professor_responsavel;
} Disciplina;

void listar_disciplinas(int qtdDisciplinas, Disciplina *listaDisciplinas);
Disciplina *busca_disciplina_por_id(int qtdDisciplinas, Disciplina *listaDisciplinas, int id);
bool deletar_disciplina(int *qtdDisciplinas, Disciplina *listaDisciplinas, int id);
void menuDisciplina(Disciplina *listaDisciplinas, int *qtdDisciplinas, int *codigoDisciplina, Professor *listaProfessores, int qtdProfessores);

#endif