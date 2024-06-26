#include "Clientes_estruturas.h"

//Função que possui um menu com todas das funcionalidades da estrutura clientes
int menu_clientes() {

    printf("\n-----------------------------------------\n");
    printf("|-------------- Clientes ---------------|\n");
    printf("|----- 1 - Cadastrar novo cliente ------|\n");
    printf("|----- 2 - Remover cliente -------------|\n");
    printf("|----- 3 - Pesquisar cliente -----------|\n");
    printf("|----- 4 - Visualizar clientes ---------|\n");
    printf("------ 5 - Sair ------------------------|\n");
    printf("-----------------------------------------\n");

}

//Função que adiciona um novo cliente no array de clientes
void add_cliente(Array_cliente * array, int id) {

    char nome[50];
    char cpf[20];
    char telefone[15]; 
    char email[30]; 
    char endereco[50];

    printf("\n\n---------- CADASTRAR NOVO CLIENTE ----------");
    printf("\nNome: ");
    scanf("%s", &nome);

    printf("\nCPF: ");
    scanf("%s", &cpf);

    printf("\nTelefone: ");
    scanf("%s", &telefone);

    printf("\nE-mail: ");
    scanf("%s", &email);

    printf("\nEndereco: ");
    scanf("%s", &endereco);

    _add_cliente(array, id, nome, cpf, telefone, email, endereco);

    printf("\n\nNovo cliente cadastrado com sucesso!");

}

//Função que remove um cliente do array de clientes
void deletar_clientes(Array_cliente * array) {

    char nome[50];

    printf("\n\n---------- DELETAR CLIENTE ----------");
    printf("\nNome: ");
    scanf("%s", &nome);

    Cliente * cliente = pesquisar_nome_cliente(array, nome);

    //Caso o nome informado não corresponda com nenhum nome do array clientes, será retornado uma mensagem de erro
    if(cliente == NULL) 
    {
        printf("\nCliente nao encontrado.");
    }

    _deletar_clientes(array, cliente->id);

}

//Função para pesquisar um cliente pelo nome ou id
void pesquisar_cliente(Array_cliente * array) {

    char search[100];

    printf("----------- Pesquisar Cliente -------------");

    printf("\nDigite o ID ou Nome do cliente que deseja pesquisar: ");
    scanf("%s", &search);

    Cliente * cliente;
    
    if (e_numero(search))
    {
        cliente = get_produto(array,_pesquisar_id_produto(array, atoi(search)));
    }
    else
    {
        cliente = _pesquisar_nome_produto(array,search);
    }

    if ( cliente == NULL)
    {
        printf("Cliente não encontrado! ");
    } 
    else 
    {
        printf("\n\n---------- DADOS DO CLIENTE ----------");
        printf("\nID: %i", cliente->id);
        printf("\nNome: %s", cliente->nome);
        printf("\nCPF: %s", cliente->cpf);
        printf("\nTelefone: %s", cliente->telefone);
        printf("\nE-mail: %s", cliente->email);
        printf("\nEndereco: %s", cliente->endereco);
    }

    // printf("\n\nPesquisar por: \n");
    // printf("1 - Nome \n");
    // printf("2 - ID \n");

    // int op;

    // printf("\n\nDigite a opcao desejada: ");
    // scanf("%i", &op);

    // Cliente * cliente;

    // switch (op)
    // {
    //     case 1:
    //         char nome[50];
    //         printf("\nNome: ");
    //         scanf("%s", &nome);

    //         cliente = get_cliente(array,pesquisar_nome_cliente(array, nome));
    //         break;
        
    //     case 2:
    //         int id;
    //         printf("\nID: ");
    //         scanf("%s", &id);

    //         cliente = get_cliente(array,pesquisar_id_cliente(array, id));
    //         break;
    // }

    // if(array->array == NULL || cliente == NULL ) 
    // {

    //     printf("Cliente nao encontrado.");
    // }

    // printf("\n\n---------- DADOS DO CLIENTE ----------");
    // printf("\nID: %i", cliente->id);
    // printf("\nNome: %s", cliente->nome);
    // printf("\nCPF: %s", cliente->cpf);
    // printf("\nTelefone: %s", cliente->telefone);
    // printf("\nE-mail: %s", cliente->email);
    // printf("\nEndereco: %s", cliente->endereco);

}

//Função para visualizar o array de clientes em ordem alfabética ou por id (crescente e decrescente)
void visualizar_clientes(Array_cliente * array) {
    
    printf("\n\nTipos de visualização: \n");
    printf("1 - Ordem alfabetica \n");
    printf("2 - Ordem de ID \n");

    int op;
    
    printf("\n\nDigite a opcao desejada: ");
    scanf("%i", &op);

    switch (op)
    {
        case 1:
            ordem_alfabetica_cliente(array, 0, array->size);
            break;
        
        case 2:
            organizar_array(array);
            break;
    }

    if(array->array == NULL) 
    {

        printf("A lista de clientes esta vazia.");
    }

    printf("\n\n---------- LISTA DE CLIENTES ----------");

    for(int i = 0; i < array->size-1; i++) 
    {
        Cliente * cliente = get_cliente(array, i);
        
        printf("\n|  ID  |   NOME   |   CPF   | TELEFONE |  E-MAIL  | ENDERECO |\n");
        printf("| %i |", cliente->id);
        printf(" %s |", cliente->nome);
        printf(" %s |", cliente->cpf);
        printf(" %s |", cliente->telefone);
        printf(" %s |", cliente->email);
        printf(" %s |\n", cliente->endereco);
    }
}

int e_numero(char * buffer)
{
    while(*buffer && *buffer!='\0')
    {
        if(!isdigit(*buffer)) return 0;
    }
    return 1;
}

