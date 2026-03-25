#include <stdio.h>

int main()
{

    printf("Olá mundo\n");

    int listaAnos[3];
    int sair = 0;
    int qtdLivros = 0;
    int opcao;
    while (sair == 0)
    {
        printf("Escolha a opcão: \n");
        printf("0 - Sair \n");
        printf("1 - Cadastrar Livro \n");
        printf("2 - Listar Livros \n");
        printf("3 - Atualizar Livro \n");
        printf("4 - Excluir Livro \n");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 0:
        {
            sair = 1;
            break;
        }
        case 1:
        {
            // cadastrar livro
            if (qtdLivros == 3)
            {
                printf("Biblioteca cheia!\n");
            }
            else
            {
                printf("Digite um ano: \n");
                int ano;
                scanf("%d", &ano);
                listaAnos[qtdLivros] = ano;
                qtdLivros++;
            }
            break;
        }
        case 2:
        {
            // listar livro
            printf("### Listando os livros ###\n");
            for (int i = 0; i < qtdLivros; i++)
            {
                printf("%d\n", listaAnos[i]);
            }
            break;
        }
        case 3:
        {
            if (qtdLivros == 0)
            {
                printf("A estante de livros está vazia! \n");
            }

            printf("Os livros cadastrados atualmente são:");
            
            for (int i = 0; i < qtdLivros; i++)
            {
                printf("%d - %d\n", i + 1, listaAnos[i]);
            }

            printf("Digite a posição do livro que você vai atualizar \n");
            printf("Digite um número entre 1 e %d: ", qtdLivros);
            int posicao;
            scanf("%d", &posicao);

            if(posicao < 1 || posicao > qtdLivros){
                printf("Posição inválida! Digite entre 1 e %d\n", qtdLivros);
                break;
            }

            printf("O livro selecionado foi: %d \n", listaAnos[posicao - 1]);

            printf("Digite um novo conteúdo para esse livro: ");
            int newContent;
            scanf("%d", &newContent);
            listaAnos[posicao - 1] = newContent;
            printf("O conteúdo do livro foi alterado para: %d \n", listaAnos[posicao - 1]);

            break;
        }
        case 4:
        {
            // excluir livro
            if (qtdLivros == 0)
            {
                printf("Biblioteca vazia!\n");
            }
            else
            {
                printf("Livro excluido com sucesso!\n");
                qtdLivros--;
            }
            break;
        }
        }
    }
}