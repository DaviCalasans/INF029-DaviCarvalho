#ifndef PROFESSOR_H
#define PROFESSOR_H
#include <stdbool.h>
#include "tipos.h"

#define TAM_LISTA_PROFESSOR 3

typedef struct {
    int id;
    int matricula;
    char nome[100];
    char sexo;
    Data data_nascimento;
    char cpf[12];
} Professor;

void listar_aniversariantes_do_mes_prof(int qtdProfessores, Professor *listaProfessores, int mesBusca);
void listar_professores_por_data(int qtdProfessores, Professor *listaProfessores);
void listar_professores_ordenados_por_nome(int qtdProfessores, Professor *listaProfessores);
void listar_professores_por_sexo(int qtdProfessores, Professor *listaProfessores, char sexoBuscado);
void listar_professores(int qtdProfessores, Professor *listaProfessores);
Professor *busca_professor_por_id(int qtdProfessores, Professor *listaProfessores, int id);
bool deletar_professor(int *qtdProfessores, Professor *listaProfessores, int id);
void menuProfessor(Professor *listaProfessores, int *qtdProfessores, int *codigoProfessor);

#endif