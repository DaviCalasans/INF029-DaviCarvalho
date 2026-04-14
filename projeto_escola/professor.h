#ifndef PROFESSOR_H
#define PROFESSOR_H
#include <stdbool.h>

#define TAM_LISTA_PROFESSOR 3

typedef struct {
    int id;
    int matricula;
    char nome[100];
    char sexo;
    char data_nascimento[11];
    char cpf[12];
} Professor;

void listar_professores(int qtdProfessores, Professor *listaProfessores);
Professor *busca_professor_por_id(int qtdProfessores, Professor *listaProfessores, int id);
bool deletar_professor(int *qtdProfessores, Professor *listaProfessores, int id);
void menuProfessor(Professor *listaProfessores, int *qtdProfessores, int *codigoProfessor);

#endif