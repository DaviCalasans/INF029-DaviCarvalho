#include <stdio.h>

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

typedef struct{
    int dia;
    int mes;
    int ano;
}DiaMesAno;

int addDiaMesAno(DiaMesAno * diamesano,int resultado, int controlador){
    

    switch(controlador){
        case 0:
        diamesano->dia = resultado;
            break;
        case 1:
        diamesano->mes = resultado;
            break;
        case 2:
        diamesano->ano = resultado;
            break;
    }

    printf("Data: %d/%d/%d\n", diamesano->dia, diamesano->mes, diamesano->ano);
}

int q1(char data[])
{
    DiaMesAno * diamesano;
    diamesano = malloc(sizeof(DiaMesAno) * 3);
    int datavalida = 1;  
    int tam = strlen(data);
    int resultado = 0;
    int guardado = 0;
    int controlador = 0;
    int ant = 0;
    int lidos = 0;

    for(int i = 0; i < tam; i++){
        char c = data[i];
        int n = c - '0';
        printf("valor de n: %d\n", n);

    if(data[0] == '/'){
        printf("Data inválida");
        break;
    }

    if(data[i] == '/' && ant < 0){
        printf("Ant: %d", ant);
        printf("Anterior é barra. Data Inválida\n");
    }

    if(data[i] == '/'){
        controlador++;
        resultado = 0;
        guardado = 0;
        lidos = 0;
    }
    

    if(data[i] != '/' && n < 0) {
        printf("Número negativo: %d. Data inválida", n);
    } else if(n > 9){
        printf("Número maior que 9. Data inválida");
    } else if (n >= 0) {
        lidos++;
        resultado = (guardado * 10) + n;
        guardado = n;
        // printf("Controlador: %d\n", controlador);
        addDiaMesAno(diamesano, resultado, controlador);
    }

    // printf("O valor do resultado foi: %d\n", resultado);
    // printf("O valor do diamesano foi: %d\n", diamesano->mes);
    printf("Lidos: %d\n",lidos);
    // printf("%d\n", n);
    ant = n;
  }
  printf("A data inserida foi %s\n", data);

  if (datavalida)
      return 1;
  else
      return 0;
}

int main(){
    q1("29/03/2024");

    return 0;
}