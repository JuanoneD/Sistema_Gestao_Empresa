#include "..\Estruturas_Dados\Clientes_estruturas.h"
#include <ctype.h>

// Função que verifica se a string digitada é um número
int e_numero(char *buffer)
{
    while (*buffer && *buffer != '\0')
    {
        if (isdigit(*buffer++) == 0) return 0;
    }

    return 1;
}

// Função que possui um menu com todas das funcionalidades da estrutura clientes
int menu_clientes()
{
    int op = 0;

    while (op == 0)
    {

        printf("\n-----------------------------------------\n");
        printf("|-------------- Clientes ---------------|\n");
        printf("|----- 1 - Cadastrar novo cliente ------|\n");
        printf("|----- 2 - Remover cliente -------------|\n");
        printf("|----- 3 - Pesquisar cliente -----------|\n");
        printf("|----- 4 - Editar cliente --------------|\n");
        printf("|----- 5 - Visualizar clientes ---------|\n");
        printf("------ 6 - Sair ------------------------|\n");
        printf("-----------------------------------------\n");

        printf("\n\nDigite a opcao desejada: ");
        scanf("%i", &op);

        // Se o usuário digitar um número que não corresponda a nenhuma das opções, será retornada uma mensagem de erro
        if (op == 0 || op > 6)
        {
            printf("\nPor favor, digite uma opcao valida");
        }
    }

    return op;
}

// Função que adiciona um novo cliente no array de clientes
void add_cliente(Array_cliente *array, int id)
{
    char nome[50];
    char cpf[20];
    char telefone[15];
    char email[30];
    char endereco[50];

    printf("\n\n---------- CADASTRAR NOVO CLIENTE ----------");
    printf("\nNome: ");
    fflush(stdin); // permite que o usuário escreva mais de uma palavra sem dar erro
    gets(nome);    // semelhante ao scanf

    printf("\nCPF: ");
    scanf("%s", cpf);

    printf("\nTelefone: ");
    scanf("%s", telefone);

    printf("\nE-mail: ");
    scanf("%s", email);

    printf("\nEndereco: ");
    fflush(stdin);
    gets(endereco);

    _add_cliente(array, id, nome, cpf, telefone, email, endereco);

    printf("\n\nNovo cliente cadastrado com sucesso!");
}

// Função que remove um cliente do array de clientes
void deletar_clientes(Array_cliente *array)
{
    char nome[50];

    printf("\n\n---------- DELETAR CLIENTE ----------");
    printf("\nNome: ");
    fflush(stdin);
    gets(nome);

    // Pesquisa se o nome informado faz parte da lista de clientes
    Cliente *cliente = pesquisar_nome_cliente(array, nome);

    // Caso o nome informado não corresponda com nenhum nome do array clientes, será retornada uma mensagem de erro
    if (cliente == NULL)
    {
        printf("\nCliente nao encontrado.");
    }

    _deletar_clientes(array, cliente->id);
    printf("\nO cliente %s foi deletado com sucesso!", cliente->nome);
}

// Função para pesquisar um cliente pelo nome ou id
Cliente *pesquisar_cliente(Array_cliente *array)
{
    char search[100];

    printf("\n----------- Pesquisar Cliente -------------");

    printf("\nDigite o ID ou Nome do cliente: ");
    scanf("%s", search);

    Cliente *cliente;

    // Verifica se a string informada pelo usuário se trata de uma palavra (nome) ou um número (id)
    if (e_numero(search) == 1)
    {
        cliente = get_cliente(array, pesquisar_id_cliente(array, atoi(search)));
    }
    else
    {
        cliente = pesquisar_nome_cliente(array, search);
    }

    if (cliente == NULL)
    {
        printf("Cliente não encontrado! ");
        menu_clientes();
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

    return cliente;
}

// Função para visualizar o array de clientes em ordem alfabética ou por id (crescente e decrescente)
void visualizar_clientes(Array_cliente *array)
{
    printf("\n\nTipos de visualizacao: \n");
    printf("1 - Ordem alfabetica \n");
    printf("2 - Ordem de ID \n");

    int op;

    printf("\n\nDigite a opcao desejada: ");
    scanf("%i", &op);

    switch (op)
    {
        case 1:
            ordem_alfabetica_cliente(array, 0, array->size - 1);
            break;

        case 2:
            organizar_array(array);
            break;
        }

    // Se a lista estiver vazia, será retornada uma mensagem
    if (array->array == NULL)
    {
        printf("A lista de clientes esta vazia.");
    }

    printf("\n\n---------- LISTA DE CLIENTES ----------");

    for (int i = 0; i < array->size; i++)
    {
        Cliente *cliente = get_cliente(array, i);

        printf("\n|  ID  |   NOME   |   CPF   | TELEFONE |  E-MAIL  | ENDERECO |\n");
        printf("| %i |", cliente->id);
        printf(" %s |", cliente->nome);
        printf(" %s |", cliente->cpf);
        printf(" %s |", cliente->telefone);
        printf(" %s |", cliente->email);
        printf(" %s |\n", cliente->endereco);
    }
}

// Função para editar as informações de um cliente específico
void editar_cliente(Array_cliente *array, int id)
{
    printf("\n\n----------- EDITAR CLIENTE -------------");
    printf("\nAntes de editar, sera preciso verificar o cliente na lista\n");

    Cliente *cliente = pesquisar_cliente(array);

    if (pesquisar_cliente != NULL)
    {
        printf("\nNome: ");
        fflush(stdin);
        gets(cliente->nome);

        printf("\nCPF: ");
        fflush(stdin);
        gets(cliente->cpf);

        printf("\nTelefone: ");
        fflush(stdin);
        gets(cliente->telefone);

        printf("\nEmail: ");
        fflush(stdin);
        gets(cliente->email);

        printf("\nEndereco: ");
        fflush(stdin);
        gets(cliente->endereco);
    }

    else
    {
        // Se o cliente informado não existir na lista, o usuário terá a opção de cadastrá-lo ou retornar ao menu
        int op;
        printf("\nDigite 1 para adicionar um novo cliente ou 0 para voltar ao menu principal: ");
        scanf("%i", &op);

        if (op == 1)
        {
            add_cliente(array, id);
        }
        else
        {
            menu_clientes();
        }
    }
}
