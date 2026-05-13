// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Análise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratório de Programação
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientações gerais -----
//  Descrição: esse arquivo deve conter as questões do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questões do trabalho

//  ----- Dados do Aluno -----
//  Nome:
//  email:
//  Matrícula:
//  Semestre:

//  Copyright © 2016 Renato Novais. All rights reserved.
// Última atualização: 07/05/2021 - 19/08/2016 - 17/10/2025

// #################################################

#include <stdio.h>
#include "trabalho1.h" 
#include <stdlib.h>
#include <string.h>

DataQuebrada quebraData(char data[]);

/*
## função utilizada para testes  ##

 somar = somar dois valores
@objetivo
    Somar dois valores x e y e retonar o resultado da soma
@entrada
    dois inteiros x e y
@saida
    resultado da soma (x + y)
 */
int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}

/*
## função utilizada para testes  ##

 fatorial = fatorial de um número
@objetivo
    calcular o fatorial de um número
@entrada
    um inteiro x
@saida
    fatorial de x -> x!
 */
int fatorial(int x)
{ //função utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mês, e aaaa, igual ao ano. dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data inválida
    1 -> se data válida
 @restrições
    Não utilizar funções próprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */


typedef struct
{
    int dia;
    int mes;
    int ano;
} DiaMesAno;

int validarDiaParaMes(int dia, int mes, int ano)
{
    int diasPorMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (mes == 2 && ((ano % 4 == 0 && ano % 100 != 0) || (ano % 400 == 0)))
    {
        diasPorMes[2] = 29;
    }

    if (dia < 1 || dia > diasPorMes[mes])
    {
        return 0;
    }
    return 1; 
}

int addDiaMesAno(DiaMesAno *diamesano, int resultado, int controlador, int temZero, int *qtdCaractere)
{

    switch (controlador)
    {
    case 0:
        diamesano->dia = resultado;
        (*qtdCaractere)++;
        break;
    case 1:
        diamesano->mes = resultado;
        (*qtdCaractere)++;
        break;
    case 2:
        (*qtdCaractere)++;
        diamesano->ano = resultado;
        break;
    }

}

int validarData(DiaMesAno *diamesano, int controlador, int *qtdCaractere)
{
    switch (controlador)
    {
    case 0:
        if (*qtdCaractere < 1 || *qtdCaractere > 2)
        {
            return 0;
        }
        if (diamesano->dia <= 0 || diamesano->dia > 31)
        {
            return 0;
        }
        break;
    case 1:
        if (*qtdCaractere < 1 || *qtdCaractere > 2)
        {
            return 0;
        }
        if (diamesano->mes <= 0 || diamesano->mes > 12)
        {
            return 0;
        }
        break;
    case 2:
        if (*qtdCaractere < 2 || *qtdCaractere > 4 || *qtdCaractere == 3)
        {
            return 0;
        }
        if (diamesano->ano < 0)
        {
            return 0;
        }

        if (!validarDiaParaMes(diamesano->dia, diamesano->mes, diamesano->ano))
        {
            return 0;
        }
        break;
    }
    return 1;
}

int q1(char data[])
{
    DiaMesAno temp = {-1, -1, -1};
    DiaMesAno *diamesano = &temp;

    int datavalida = 1;
    int tam = strlen(data);
    int resultado = 0;
    int guardado = 0;
    int controlador = 0;
    int ant = 0;
    int lidos = 0;
    int temZero = 0;
    int tempCaractere = 0;
    int *qtdCaractere = &tempCaractere;

    for (int i = 0; i < tam; i++)
    {
        char c = data[i];
        int n = c - '0';

        if (data[0] == '/')
        {
            datavalida = 0;
            break;
        }

        if (data[i] == '/' && ant < 0)
        {
            datavalida = 0;
            break;
        }

        if (data[i] == '/')
        {
            if (!validarData(diamesano, controlador, qtdCaractere))
            {
                datavalida = 0;
                break;
            }
            controlador++;
            resultado = 0;
            guardado = 0;
            lidos = 0;
            *qtdCaractere = 0;
        }

        if (data[i] != '/' && n < 0)
        {
            datavalida = 0;
            break;
        }
        else if (n > 9)
        {
            datavalida = 0;
            break;
        }
        else if (n >= 0)
        {
            lidos++;
            resultado = (guardado * 10) + n;
            guardado = resultado;
            addDiaMesAno(diamesano, resultado, controlador, temZero, qtdCaractere);
        }

        ant = n;
    }
    if (!validarData(diamesano, 2, qtdCaractere))
    {
        datavalida = 0;
    }

    if (datavalida)
        return 1;
    else
        return 0;
}


/*
 Q2 = diferença entre duas datas
 @objetivo
    Calcular a diferença em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possíveis valores abaixo
    1 -> cálculo de diferença realizado com sucesso
    2 -> datainicial inválida
    3 -> datafinal inválida
    4 -> datainicial > datafinal
    Caso o cálculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos calcularDiferenca(int d1, int m1, int a1, int d2, int m2, int a2)
{
    DiasMesesAnos dma;
    int diasNoMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if ((a2 % 4 == 0 && a2 % 100 != 0) || (a2 % 400 == 0))
    {
        diasNoMes[2] = 29;
    }

    if (d2 < d1)
    {
        if (m2 == 1)
        {
            d2 = d2 + diasNoMes[12];
            m2 = 12;
            a2--;
        }
        else
        {
            m2--;
            d2 = d2 + diasNoMes[m2];
        }
    }
    dma.qtdDias = d2 - d1;

    if (m2 < m1)
    {
        a2--;
        m2 = m2 + 12;
    }
    dma.qtdMeses = m2 - m1;

    dma.qtdAnos = a2 - a1;
    dma.retorno = 1;

    return dma;
}

DiasMesesAnos converterData(char datainicial[], char datafinal[], DiasMesesAnos dma)
{
    int ano1 = (datainicial[6] - '0') * 1000 + (datainicial[7] - '0') * 100 + (datainicial[8] - '0') * 10 + (datainicial[9] - '0');
    int mes1 = (datainicial[3] - '0') * 10 + (datainicial[4] - '0');
    int dia1 = (datainicial[0] - '0') * 10 + (datainicial[1] - '0');
    int dataInicialInvertida = (ano1 * 10000) + (mes1 * 100) + dia1;

    int ano2 = (datafinal[6] - '0') * 1000 + (datafinal[7] - '0') * 100 + (datafinal[8] - '0') * 10 + (datafinal[9] - '0');
    int mes2 = (datafinal[3] - '0') * 10 + (datafinal[4] - '0');
    int dia2 = (datafinal[0] - '0') * 10 + (datafinal[1] - '0');
    int dataFinalInvertida = (ano2 * 10000) + (mes2 * 100) + dia2;

    if (dataInicialInvertida > dataFinalInvertida)
    {
        dma.retorno = 4;
        return dma;
    }

    return calcularDiferenca(dia1, mes1, ano1, dia2, mes2, ano2);
}

DiasMesesAnos q2(char datainicial[], char datafinal[])
{
    DiasMesesAnos dma;

    if (q1(datainicial) == 0)
    {
        dma.retorno = 2;
        return dma;
    }
    if (q1(datafinal) == 0)
    {
        dma.retorno = 3;
        return dma;
    }
    else
    {
        dma = converterData(datainicial, datafinal, dma);

        return dma;
    }
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se é uma pesquisa Case Sensitive ou não. Se isCaseSensitive = 1, a pesquisa deve considerar diferenças entre maiúsculos e minúsculos.
        Se isCaseSensitive != 1, a pesquisa não deve  considerar diferenças entre maiúsculos e minúsculos.
 @saida
    Um número n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int qtdOcorrencias = 0;
    int j;
    char *cpyTxt;
    cpyTxt = malloc(sizeof(char) * strlen(texto) + 1);

    if (isCaseSensitive != 1)
    {
        if (c >= 'a' && c <= 'z')
        {
            c = c - 32;
        }

        for (j = 0; j < strlen(texto); j++)
        {
            cpyTxt[j] = texto[j];

            if (cpyTxt[j] >= 'a' && cpyTxt[j] <= 'z')
            {
                cpyTxt[j] = cpyTxt[j] - 32;
            }

            if (cpyTxt[j] == c)
            {
                qtdOcorrencias++;
            }
        }
        cpyTxt[j] = '\0';
    }
    else
    {
        for (int i = 0; i < strlen(texto); i++)
        {

            if (texto[i] == c)
            {
                qtdOcorrencias++;
            }
        };
    }

    return qtdOcorrencias;
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrências de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irá guardar as posições de início e fim de cada ocorrência da palavra (strBusca) no texto base (texto).
 @saida
    Um número n >= 0 correspondente a quantidade de ocorrências encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saída correspondente. Por exemplo, se tiver uma única ocorrência, a posição 0 do vetor deve ser preenchido com o índice de início do texto, e na posição 1, deve ser preenchido com o índice de fim da ocorrencias. Se tiver duas ocorrências, a segunda ocorrência será amazenado nas posições 2 e 3, e assim consecutivamente. Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera". Como há uma ocorrência da palavra de busca no texto, deve-se armazenar no vetor, da seguinte forma:
        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o índice da posição no texto deve começar ser contado a partir de 1.
        O retorno da função, n, nesse caso seria 1;

 */
int contagemCaracteresAte(const char *str, int bytePos) {
    int count = 1;
    for (int i = 0; i < bytePos; i++) {
        if ((str[i] & 0xC0) != 0x80) count++;
    }
    return count;
}

int q4(char *strTexto, char *strBusca, int posicoes[30])
{
    int qtdOcorrencias = 0;
    int i;
    int tam = strlen(strTexto);
    int tamBusca = strlen(strBusca);
    int contPos = 0;

    for (i = 0; i < tam; i++)
    {
        if (strBusca[0] == strTexto[i])
        {
            int letrasIguais = 1;
            int p = i + 1;
            for (int j = 1; j < tamBusca; j++)
            {
                if (strBusca[j] == strTexto[p])
                {
                    p++;
                    letrasIguais++;
                }
                else
                {
                    break;
                }
            }
        
            if (letrasIguais == tamBusca)
            {
                posicoes[contPos] = contagemCaracteresAte(strTexto, i);     
                posicoes[contPos + 1] = contagemCaracteresAte(strTexto, p - 1); 
                contPos += 2;               
                qtdOcorrencias++;
            }
        }
    }

    return qtdOcorrencias;
}

/*
 Q5 = inverte número
 @objetivo
    Inverter número inteiro
 @entrada
    uma int num.
 @saida
    Número invertido
 */

int q5(int num)
{

    return num;
}

/*
 Q6 = ocorrência de um número em outro
 @objetivo
    Verificar quantidade de vezes da ocorrência de um número em outro
 @entrada
    Um número base (numerobase) e um número de busca (numerobusca).
 @saida
    Quantidade de vezes que número de busca ocorre em número base
 */

int q6(int numerobase, int numerobusca)
{
    int qtdOcorrencias;
    return qtdOcorrencias;
}

/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direções e sentidos possíves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se não achou
 */

 int q7(char matriz[8][10], char palavra[5])
 {
     int achou;
     return achou;
 }



DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}
