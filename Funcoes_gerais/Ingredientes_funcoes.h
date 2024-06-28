#include "..\Estruturas_Dados\Ingredientes_estruturas.h"
#include <ctype.h>

int e_numero(char * buffer)
{
    while(*buffer && *buffer!='\0')
    {
        if(isdigit(*buffer++)== 0) return 0;
    }
    return 1;
}

//Função que possui um menu com todas as funcionalidades da estrutura ingredientes
int menu_ingredientes() {

    int op = 0;

    printf("\n-----------------------------------------\n");
    printf("|------------ Ingredientes -------------|\n");
    printf("|----- 1 - Adicionar ingrediente -------|\n");
    printf("|----- 2 - Remover ingrediente ---------|\n");
    printf("|----- 3 - Pesquisar ingrediente -------|\n");
    printf("|----- 4 - Visualizar estoque ----------|\n");
    printf("------ 5 - Sair ------------------------|\n");
    printf("-----------------------------------------\n");

    printf("\n\nDigite a opcao desejada: ");
    scanf("%i", &op);

    while(op <= 0 || op > 5) {
        
        printf("\n\nPor favor, digite uma opcao valida: ");
        scanf("%i", &op);   
    }

    return op;

}

//Função para pesquisar um ingrediente pelo nome ou id
Ingrediente * pesquisar_ingrediente(Array_ingrediente * array) {

    char search[100];

    printf("\n----------- PESQUISAR INGREDIENTE -------------");

    printf("\nDigite o ID ou Nome do ingrediente: ");
    scanf("%s", search);

    Ingrediente * ingrediente;
    
    if (e_numero(search) == 1)
    {
        ingrediente = get_ingrediente(array, pesquisar_id_ingrediente(array, atoi(search)));
    }
    else
    {
        ingrediente = pesquisar_nome_ingrediente(array,search);
    }

    if ( ingrediente == NULL)
    {
        printf("ingrediente não encontrado! ");
    } 
    else 
    {
        printf("\n\n---------- DADOS DO INGREDIENTE ----------");
        printf("\nID: %i", ingrediente->id);
        printf("\nNome: %s", ingrediente->nome);
        printf("\nQuantidade: %i", ingrediente->qta);       
        printf("\nPreco: R$ %i", ingrediente->preco);    
    }

    return ingrediente;
}

//Função que adiciona um novo ingrediente ao estoque
void add_ingrediente(Array_ingrediente * array, int id) {

    char nome[50];
    int qta;
    float preco;
    int op;

    printf("\n\nOpcoes: \n");
    printf("1 - Adicionar novo ingrediente \n");
    printf("2 - Acrescentar ingrediente ao estoque \n");

    printf("\n\nDigite a opcao desejada: ");
    scanf("%i", &op);

    switch (op)
    {
        case 1:
            printf("\n\n---------- CADASTRAR NOVO INGREDIENTE ----------");
            printf("\nNome: ");
            fflush(stdin);      //permite que o usuário escreva mais de uma palavra sem dar erro
            gets(nome);

            printf("\nQuantidade: ");
            scanf("%i", &qta);

            printf("\nPreco: ");
            scanf("%f", &preco);

            _add_ingrediente(array, id, nome, qta, preco);

            printf("\n\nNovo ingrediente cadastrado com sucesso!");
            break;
        
        case 2:

            printf("\nAntes de editar, sera preciso verificar no estoque os dados do item.\n");

            Ingrediente * ingrediente =  pesquisar_ingrediente(array);
            
            if(ingrediente == NULL) 
            {
                printf("Digite 1 para adicionar novo ingrediente ou 0 para voltar ao menu principal");
                scanf("%i", &op);

                if(op == 1) 
                {
                    add_ingrediente(array, id);
                }

                else 
                {
                    menu_ingredientes();
                    break;
                }
            }

            else 
            {
                printf("\nDigite a quantidade que sera adicionada: ");
                scanf("%i", &ingrediente->qta);
                break;
            }
    }
}

//Função que remove um ingrediente do estoque
void deletar_ingrediente(Array_ingrediente * array) {

    char search[50];

    printf("\n\n---------- DELETAR INGREDIENTE ----------");
    printf("\nDigite o ID ou Nome do cliente que deseja deletar: ");
    fflush(stdin);      //permite que o usuário escreva mais de uma palavra sem dar erro
    gets(search);

    Ingrediente * ingrediente = pesquisar_nome_ingrediente(array, search);

    //Caso a identificação informada não corresponda com nenhum ingrediente, será retornado uma mensagem de erro
    if(ingrediente == NULL) 
    {
        printf("\nIngrediente nao encontrado.");
    }

    _deletar_ingrediente(array, ingrediente->id);

}

//Função para visualizar o array de ingredientes em ordem alfabética ou por id (crescente e decrescente)
void visualizar_ingredientes(Array_ingrediente * array) {
    
    printf("\n\nTipos de visualizacao: \n");
    printf("1 - Ordem alfabetica \n");
    printf("2 - Ordem de ID \n");
    printf("3 - Ordem de quantidade");

    int op;
    
    printf("\n\nDigite a opcao desejada: ");
    scanf("%i", &op);

    switch (op)
    {
        case 1:
            ordem_alfabetica_ingrediente(array, 0, array->size-1);
            break;
        
        case 2:
            organizar_array_asc(array);
            break;

        case 3:
            organizar_array_qta(array);
            break;
    }

    if(array->array == NULL) 
    {

        printf("O estoque de ingredientes esta vazio.");
    }

    printf("\n\n---------- ESTOQUE DE INGREDIENTES ----------");

    for(int i = 0; i < array->size; i++) 
    {
        Ingrediente * ingrediente = get_ingrediente(array, i);
        
        printf("\n|  ID  |   NOME   |   QUANTIDADE   | PRECO |\n");
        printf("| %i |", ingrediente->id);
        printf(" %s |", ingrediente->nome);
        printf(" %i |", ingrediente->qta);
        printf(" %f |", ingrediente->preco);
    }
}


