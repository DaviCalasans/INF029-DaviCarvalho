#ifndef ALUNO_H
#define ALUNO_H
#include <stdbool.h>

#define TAM_LISTA_ALUNOS 3

typedef struct {
    int id;
    int matricula;
    char nome[100];
    char sexo;
    char data_nascimento[11];
    char cpf[12];
} Aluno;

void listar_alunos(int qtdAlunos, Aluno *listaAlunos);
Aluno *busca_aluno_por_id(int qtdAlunos, Aluno *listaAlunos, int id);
bool deletar_aluno(int *qtdAlunos, Aluno *listaAlunos, int id);
void menuAlunos(Aluno *listaAlunos, int *qtdAlunos, int *codigoAluno);

#endif