#include "Produtos_estruturas.h"
#include <ctype.h>

#ifndef Produtos_funcoes
#define Produtos_funcoes

int menu_produtos(){
    printf("----------------------------------------");
    printf("|------------- Produtos ---------------|");
    printf("|------ 1 - Inserir novo produto ------|");
    printf("|------ 2 - Remover um produto --------|");
    printf("|------ 3 - Pesquisar um produto ------|");
    printf("|------ 4 - Vizualizar produtos -------|");
    printf("|------ 0 -  Sair ---------------------|");
    printf("---------------------------------------");
}

void adicionar_produto(Array_produtos * array, int id){
    char nome[50];
    char uniMedida[10];
    char ingredientes[50];
    float preco;

    printf("\nNome do produto: ");
    scanf("%s", &nome);

    printf("\nUnidade de medida: ");
    scanf("%s", &uniMedida);

    printf("\nIDs Ingredientes: ");
    scanf("%s", &ingredientes);

    printf("\nPreco: R$ ");
    scanf("%f", &preco);

    _add_produto(array, id, nome, uniMedida, ingredientes, preco);

    printf("O produto {%s} foi adicionado com sucesso!", nome);
}

void deletar_produto(Array_produtos * array){
    int id;

    printf("\nDigite o Nome ou ID do produto: ");
    scanf("%i", &id);

    Produto * produto = get_produto(array,_pesquisar_id_produto(array, id));

    if(produto == NULL){
        printf("Produto não encontrado!");

        return;
    }
    else{
        printf("Produto '{%s}' deletado!", produto->nome);
    }

    _deletar_produtos(array, id);

}

int eh_numero(char * buffer)
{
    while(*buffer && *buffer!='\0')
    {
        if(!isdigit(*buffer)) return 0;
    }
    return 1;
}

void pesquisar_produto(Array_produtos * array){

    int id;
    char search[50];

    printf("----------- Pesquisar Produto -------------");

    printf("\nDigite o ID ou Nome do produto que deseja pesquisar: ");
    scanf("%s", &search);
    Produto * produto;
    
    if (eh_numero(search))
    {
        produto = get_produto(array,_pesquisar_id_produto(array, atoi(search)));
    }
    else
    {
        produto = _pesquisar_nome_produto(array,search);
    }

    if( produto == NULL)
    {
        printf("Produto não encontrado! ");
    } 
    else 
    {
        printf("\nProduto: %s", produto->nome);
        printf("\nIngredientes: %s", produto->ingredientes);
        printf("\nUnidade de medida: %s", produto->uniMedida);
        printf("\nPreco:R$ %f", produto->preco);

    }
}

void visualizar_produtos(Array_produtos * array){
    int op;

    printf("1 - Visulizar em ordem alfabética");
    printf("2 - Visualizar em ordem de ID");
    scanf("%i", &op);


    switch (op)
    {
    case 1:
        _ordem_alfabetica_produto(array, 0, array->size);
        break;
    
    case 2:
        organizar_array(array);
        break;
    }

    printf("--------- Lista de Produtos -------");

    for (int i = 0; i < array->size; i++){
        Produto * produto = get_produto(array, i);
        
        printf("ID    | NOME          | INGREDIENTES        | UNI MED      |  PRECO       ");
        printf("\n%i\t\t", produto->id);
        printf("%s\t\t", produto->nome);
        printf(" %s\t\t", produto->ingredientes);
        printf("%s\t\t", produto->uniMedida);
        printf("%i\t\t", produto->preco);         

    }
}


#endif