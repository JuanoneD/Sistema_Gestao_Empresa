#include "..\Estruturas_Dados\Pedidos_estruturas.h"
#include "Clientes_funcoes.h"
#include "Produtos_funcoes.h"

#ifndef Pedidos_funcoes
#define Pedidos_funcoes


    // Função que possui um menu com todas das funcionalidades da estrutura pedidos
    int menu_pedido()
    {
        int op = 0;

        while (op == 0)
        {
            printf("----------------------------------------");
            printf("|------------- Pedidos ----------------|");
            printf("|------ 1 - Inserir novo pedido -------|");
            printf("|------ 2 - Visualizar pedidos --------|");
            printf("|------ 3 - Pesquisar um pedido -------|");
            printf("|- 4 - Atualizar status de um pedido - |");
            printf("|------ 4 - Remover um pedido  --------|");
            printf("|------ 0 -  Sair ---------------------|");
            printf("---------------------------------------");
        
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

    // Função que adiciona um novo pedido no array de pedidos
    void add_pedido(Array_pedidos * array, Array_cliente * array_clie, Array_produtos * array_prod, Array_ingrediente * array_inged, int id_pedido, int *id_cliente, int *id_produto)
    {
        char new_client_id[100],new_product_id[100],qtd_produto[100],data[100];
        int menu = 0;

        printf("\nSelecionar:\n1 - Cliente existente\n2 - Criar novo cliente\n");
        scanf("%i",&menu);
        
        if(menu == 2) 
        {
            add_cliente(array_clie,*id_cliente);
            *id_cliente = *id_cliente + 1; 
        }
        else
        {
            visualizar_clientes(array_clie);
            printf("\nDigite o id do cliente desejado,caso exista mais de um cliente adicionar separado por virgula:\n");
            scanf(" %s",new_client_id);
        }

        printf("Selecionar:\n1 - Produtos existentes\n2 - Adicionar novo\n");
        scanf("%i",&menu);

        if(menu == 2)
        {
            adicionar_produto(array_prod,array_inged,*id_produto);
            *id_produto = *id_produto + 1;
        }
        visualizar_produtos(array_prod);
        printf("\nDigite o id do produto desejado,caso exista mais de um produto separar por virgula:\n");
        scanf(" %s",new_product_id);

        printf("Digite a quantidade do produto na mesma ordem separado por virgulas\n");
        scanf(" %s",qtd_produto);

        int *ids =(int *)malloc(sizeof(int));
        int size = split_ids(new_product_id,&ids);
        int *prices = (int *)malloc(sizeof(int));
        split_ids(qtd_produto,&prices);
        float cust = 0;
        for(int i = 0; i < size; i++)
        {
            Produto * prod = get_produto(array_prod,_pesquisar_id_produto(array_prod,ids[i]));
            if(!prod) break;
            cust += prod->preco * prices[i];
        }

        printf("O preco de custo foi: %.2f\n",cust);
        printf("O preco de venda e %.2f\n",cust *1.75);
        printf("Escreva a data de entrega dd/mm/aa ");
        scanf(" %s",data);

        _add_pedido(array,id_pedido,new_client_id,new_product_id,qtd_produto,cust,cust*1.75,data,"Preparação");
    }

    void print_pedido(Pedido * ped,Array_cliente * array_clie,Array_produtos * array_prod)
    {
        Cliente * clie;
        Produto * prod;
        int size;
        int *ids = (int*)malloc(sizeof(int));
        int *quant = (int*)malloc(sizeof(int));
        printf(" %i |",ped->id);

        size = split_ids(ped->id_cliente,&ids);
        for(int j=0;j<size;j++)
        {
            clie = get_cliente(array_clie,pesquisar_id_cliente(array_clie,ids[j]));
            if(!clie) break;
            printf(" %s", clie->nome);
            if(j+1<size)printf(",");
        }
        printf(" |");

        size = split_ids(ped->id_produto,&ids);
        split_ids(ped->qtd_produto,&quant);
        for(int j = 0; j < size; j++)
        {
            //printf(" %i ",ids[j]);
            prod = get_produto(array_prod,_pesquisar_id_produto(array_prod,ids[j]));
            if(!prod) break;
            printf(" %s x %i",prod->nome,quant[j]);
            if(j+2<size)printf(",");
        }
        printf(" |");

        printf(" %.2f | %.2f | %s | %s \n",ped->preco_custo,ped->preco_venda,ped->data_entrega,ped->status);
        free(ids);
        free(quant);
    }

    void ver_pedidos(Array_pedidos * array, Array_cliente * array_clie, Array_produtos * array_prod)
    {
        Pedido * ped;
        printf(" ___________________ PEDIDOS_________________\n");
        printf(" ID PEDIDO | CLIENTES | PRODUTOS x QUANTIDADE | PRECO DE CUSTO | PRECO DE VENDA | DATA | STATUS\n");
        for(int i = 0; i < array->size;i++)
        {
            ped = get_pedido(array,i);
            print_pedido(ped,array_clie,array_prod);
        }
        
    }

    Pedido *  pesquisar_pedido(Array_pedidos * array, Array_cliente * array_clie, Array_produtos * array_prod)
    {
        char op[100];
        Cliente * clie;
        Pedido * ped;
        printf("Digite o id do pedido ou nome do cliente:\n");
        fflush(stdin);
        gets(op);
        int *ids = (int*)malloc(sizeof(int));
        if(e_numero(op) == 1)
        {
            ped =  get_pedido(array, pesquisar_id_pedido(array,atoi(op)));
            if(!ped)
            {
                printf("Pedido não encontrado\n");
                return NULL;
            }
            print_pedido(ped,array_clie,array_prod);
            return ped;
        }

        clie = pesquisar_nome_cliente(array_clie,op);
        if(!clie)
        {
            printf("Cliente não encontrado\n");
            return NULL;
        }
        Pedido * ped2 = NULL;
        int first = 0;
        for(int i = 0; i < array->size; i++)
        {
            ped = get_pedido(array,i);
            int size = split_ids(ped->id_cliente,&ids);
            for(int j = 0; j < size; j++)
            {
                if(clie->id == ids[j])
                {
                    print_pedido(ped, array_clie, array_prod);
                    if(first == 0)
                    {
                        ped2 = ped;
                        first++;
                    }
                    break;
                }
            }
        }
        free(ids);
        return ped2;
    }

    void atualizar_status(Array_pedidos * array, Array_cliente * array_clie, Array_produtos * array_prod)
    {
        char status[100];
        Pedido * ped = pesquisar_pedido(array, array_clie, array_prod);
        if(!ped) return;
        printf("Digite o status do pedido");
        fflush(stdin);
        gets(status);
        strcpy(ped->status,status);
        printf("Status atualizado com sucesso\n");
    }

    void remover_pedido(Array_pedidos * array, Array_cliente * array_clie, Array_produtos * array_prod)
    {
        int menu;
        printf("Digite o ID do pedido que deseja remover ou 0 para ver todos os pedidos:\n");
        scanf("%i",&menu);
        if(menu == 0)
        {
            ver_pedidos(array, array_clie, array_prod);
            printf("Digite o ID do pedido que deseja remover:\n");
            scanf("%i",&menu);
        }
        if(pesquisar_id_pedido(array,menu) < 0)
        {
            printf("Pedido não encontrado");
            return;
        }
        deletar_pedidos(array,pesquisar_id_pedido(array,menu));
        printf("\nDeletado com sucesso\n");
    }

    int get_id_pedido(Array_pedidos * array)
    {
        Pedido * ped = get_pedido(array, array->size-1);
        if(!ped) return -1;
        return ped->id + 1;
    }

#endif 