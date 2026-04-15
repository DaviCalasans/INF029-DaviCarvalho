#ifndef ALUNO_H
#define ALUNO_H
#include <stdbool.h>
#include "tipos.h"

#define TAM_LISTA_ALUNOS 3

typedef struct {
    int id;
    int matricula;
    char nome[100];
    char sexo;
    Data data_nascimento;
    char cpf[12];
} Aluno;

void listar_aniversariantes_do_mes(int qtdAlunos, Aluno *listaAlunos, int mesBusca);
void listar_alunos_por_data(int qtdAlunos, Aluno *listaAlunos);
void listar_alunos_ordenados_por_nome(int qtdAlunos, Aluno *listaAlunos);
void listar_alunos_por_sexo(int qtdAlunos, Aluno *listaAlunos, char sexoBuscado);
void listar_alunos(int qtdAlunos, Aluno *listaAlunos);
Aluno *busca_aluno_por_id(int qtdAlunos, Aluno *listaAlunos, int id);
bool deletar_aluno(int *qtdAlunos, Aluno *listaAlunos, int id);
void menuAlunos(Aluno *listaAlunos, int *qtdAlunos, int *codigoAluno);

#endif