#include "..\Estruturas_Dados\Produtos_estruturas.h"
#include "Ingredientes_funcoes.h"

#ifndef Produtos_funcoes
#define Produtos_funcoes

    // Funcao responsavel por mostrar as opçoes ao usuário
    int menu_produtos()
    {
        int op;

        printf("\n----------------------------------------");
        printf("\n|------------- Produtos ---------------|");
        printf("\n|------ 1 - Inserir novo produto ------|");
        printf("\n|------ 2 - Remover um produto --------|");
        printf("\n|------ 3 - Pesquisar um produto ------|");
        printf("\n|------ 4 - Vizualizar produtos -------|");
        printf("\n|------ 5 - Editar produto ------------|");
        printf("\n|------ 0 -  Sair ---------------------|");
        printf("\n---------------------------------------\n");

<<<<<<< HEAD
        printf("\n\nDigite a opcao desejada: ");
        scanf("%i", &op);
=======
            printf("\n----------------------------------------");
            printf("\n|------------- Produtos ---------------|");
            printf("\n|------ 1 - Inserir novo produto ------|");
            printf("\n|------ 2 - Remover um produto --------|");
            printf("\n|------ 3 - Pesquisar um produto ------|");
            printf("\n|------ 4 - Editar produto ------------|");
            printf("\n|------ 5 - Visualizar produtos -------|");
            printf("\n|------ 0 - Sair ----------------------|");
            printf("\n---------------------------------------\n");
>>>>>>> ingrid

        //Se o usuário digitar um número que não corresponda a nenhuma das opções, será retornada uma mensagem de erro
        if (op < 0 || op > 6) 
        {
            printf("\nPor favor, digite uma opcao valida");
        }

        return op;

    }

    // Todas as funções abaixo são responsáveis por executar as funcões da biblioteca Produtos_estruturas 
    // e serem funcoes secundárias 

    // funcao criada para a interação do usuario ao adicionar o produto 
    void adicionar_produto(Array_produtos * array, Array_ingrediente * ingred_array, int id)
    { 
        char nome[50];
        char uniMedida[20];
        char ingredientes[60];
        float preco;

        printf("\n ------- Inserir novo Produto ---------");
        printf("\nNome do produto: ");
        fflush(stdin);
        gets(nome);

        printf("\nUnidade de medida: ");
        fflush(stdin);
        gets(uniMedida);

        visualizar_ingredientes(ingred_array);
        printf("\nIDs Ingredientes: ");
        fflush(stdin);
        gets(ingredientes);

        printf("\nPreco: R$ ");
        scanf("%f", &preco);
        
        // Adiciona um produto a lista de produtos e no tsv , essa função de fato adiciona o produto
        _add_produto(array, id, nome, uniMedida, ingredientes, preco);

        printf("O produto '%s' foi adicionado com sucesso!", nome);
    }

    // o usuário irá inserir o nome ou id do produto que deseja
    void deletar_produto(Array_produtos * array)
    {  
        char prod[50];

        printf("\nDigite o ID ou Nome do produto que deseja deletar: ");
        fflush(stdin);
        gets(prod);
        Produto * produto;
        
        if (e_numero(prod) == 1)
        {
            produto = get_produto(array,_pesquisar_id_produto(array, atoi(prod)));
            
        }
        else
        {
            produto = _pesquisar_nome_produto(array,prod);
        }

        if( produto == NULL)
        {
            printf("Produto não encontrado! ");
            return;
        } 
        _deletar_produtos(array, produto->id);
        printf("Deletado com sucesso");
    }


    //Função para pesquisar um iproduto pelo nome ou id
    Produto * pesquisar_produto(Array_produtos * array, Array_ingrediente * ingred_array)
    {
        char search[50];

        printf("\n----------- Pesquisar Produto -------------");

        printf("\nDigite o ID ou Nome do produto que deseja pesquisar: ");
        fflush(stdin);
        gets(search);

        Produto * produto;
        
        if (e_numero(search) == 1)
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
            return NULL;
        } 
        else 
        {
            printf("\nProduto: %s", produto->nome);

            int *ids_ingredientes = malloc(sizeof(int));
            int size = split_ids(produto->ingredientes,&ids_ingredientes);

            printf("\nIngredientes: ");
            for(int i = 0; i < size; i++ )
            {
                Ingrediente * ingrediente = get_ingrediente(ingred_array,pesquisar_id_ingrediente(ingred_array, ids_ingredientes[i]));
                if(!ingrediente)break;
                printf(" %s,",ingrediente->nome);
            }

            printf("\nUnidade de medida: %s", produto->uniMedida);
            printf("\nPreco:R$ %.2f", produto->preco);

        }

        return produto;
    }

    //Função para visualizar o array de produtos em ordem alfabética ou por id (crescente e decrescente)
    void visualizar_produtos(Array_produtos * array)
    {
        int op;

        printf("\n1 - Visulizar em ordem alfabetica");
        printf("\n2 - Visualizar em ordem de ID");

        printf("\nOpcao: ");
        scanf("%i", &op);

        switch (op)
        {
            case 1:
                _ordem_alfabetica_produto(array, 0, array->size-1);
                break;
            
            case 2:
                organizar_array_produtos(array);
                break;
        }

        printf("\n--------- Lista de Produtos -------\n");
        printf("\nID\t| NOME\t\t| INGREDIENTES\t\t| UNI MED\t\t|  PRECO");

        for (int i = 0; i < array->size; i++)
        {
            Produto * produto = get_produto(array, i);
            
            printf("\n%i\t", produto->id);
            printf(" %s\t\t", produto->nome);
            printf(" %s\t\t", produto->ingredientes);
            printf(" %s\t\t", produto->uniMedida);
            printf("%f\t\t", produto->preco);         
        }
    }

    //Função para editar as informações de um produto específico
    void editar_produto(Array_produtos * array, Array_ingrediente * ingred_array, int id)
    {
        printf("\n----------- Editar Produto -------------");
        Produto * produto =  pesquisar_produto(array,ingred_array);
    
        if(produto != NULL)
        {
            printf("\n------ EDICAO DO PRODUTO ------");

            printf("\nNome do produto: ");
            fflush(stdin);
            gets(produto->nome);

            printf("\nUnidade de medida: ");
            fflush(stdin);
            gets(produto->uniMedida);

            printf("\nIDs Ingredientes: ");
            fflush(stdin);
            gets(produto->ingredientes);

            printf("\nPreco: R$ ");
            scanf("%f", &produto->preco);
        } 
        else
        {   int op;
            printf("Digite 1 para adicionar um novo produto ou 0 para voltar ao menu principal: ");
            scanf("%i", &op);

            if (op == 1)
            {
                adicionar_produto(array, ingred_array, id);
            }
            else
            {
                menu_produtos();
            }
        }
    }

    int get_id_produto(Array_produtos * array)
    {
        Produto * prod = get_produto(array,array->size-1);
        if(!prod) return -1;
        return prod->id + 1;
    }

#endif