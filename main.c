#include "Funcoes_gerais\Financeiro_funcoes.h"

int main()
{
    Array_pedidos * array_ped = construtor_array_pedidos();
    get_tsv_pedido(array_ped,"pedidos.tsv");
    Array_cliente * array_clie = construtor_array_cliente();
    get_tsv_cliente(array_clie,"clientes.tsv");
    Array_produtos * array_prod = construtor_array_produtos();
    get_tsv_produto(array_prod,"produtos.tsv");
    Array_ingrediente * array_ingred = construtor_array_ingrediente();
    get_tsv_ingrediente(array_ingred,"ingredientes.tsv");
    
    int id_pedido = get_id_pedido(array_ped)>=0?get_id_pedido(array_ped):1;
    int id_cliente = get_id_cliente(array_clie)>=0?get_id_cliente(array_clie):1;
    int id_produto = get_id_produto(array_prod)>=0?get_id_produto(array_prod):1;
    int id_ingred = get_id_ingrediente(array_ingred)>=0?get_id_ingrediente(array_ingred):1;

    
    int op_menu = 0;
    int acabar = 0;
    char buffer[50];

    while (op_menu != 6)
    {
        system("cls");

        printf("\n-----------------------------------------\n");
        printf("|---------------- Menu -----------------|\n");
        printf("|----- 1 - Clientes --------------------|\n");
        printf("|----- 2 - Ingredientes ----------------|\n");
        printf("|----- 3 - Produtos --------------------|\n");
        printf("|----- 4 - Pedidos ---------------------|\n");
        printf("|----- 5 - Financeiro ------------------|\n");
        printf("------ 6 - Sair ------------------------|\n");
        printf("-----------------------------------------\n");

        printf("\n\nDigite a opcao desejada: ");
        scanf("%i", &op_menu);

        // Se o usuário digitar um número que não corresponda a nenhuma das opções, será retornada uma mensagem de erro
        if (op_menu == 0 || op_menu > 6)
        {
            printf("\nPor favor, digite uma opcao valida");
        }

        switch (op_menu)
        {   
            //Funções clientes
            case 1:
                acabar = 0;
                while (acabar == 0)
                {
                    system("cls");
                    int op = menu_clientes();

                    switch (op)
                    {
                        case 1:
                            system("cls");
                            add_cliente(array_clie, id_cliente++);
                            printf("\n\nAperte enter para continuar");
                            fflush(stdin);
                            gets(buffer);
                            break;

                        case 2:
                            system("cls");
                            deletar_clientes(array_clie);
                            printf("\n\nAperte enter para continuar");
                            fflush(stdin);
                            gets(buffer);
                            break;

                        case 3:
                            system("cls");
                            pesquisar_cliente(array_clie);
                            printf("\n\nAperte enter para continuar");
                            fflush(stdin);
                            gets(buffer);
                            break;
                            
                        case 4:
                            system("cls");
                            editar_cliente(array_clie, id_cliente++);
                            printf("\n\nAperte enter para continuar");
                            fflush(stdin);
                            gets(buffer);
                            break;
                        
                        case 5:
                            system("cls");
                            visualizar_clientes(array_clie);
                            printf("\n\nAperte enter para continuar");
                            fflush(stdin);
                            gets(buffer);
                            break;

                        case 6:
                            acabar ++;
                            break;
                    }
                }
                break;

            //Funções ingredientes
            case 2:
                acabar = 0;
                while (acabar == 0)
                {
                    system("cls");
                    int op = menu_ingredientes();

                    switch (op)
                    {
                        case 1:
                            system("cls");
                            add_ingrediente(array_ingred, id_ingred++);
                            printf("\n\nAperte enter para continuar");
                            fflush(stdin);
                            gets(buffer);
                            break;

                        case 2:
                            system("cls");
                            deletar_ingrediente(array_ingred);
                            printf("\n\nAperte enter para continuar");
                            fflush(stdin);
                            gets(buffer);
                            break;

                        case 3:
                            system("cls");
                            pesquisar_ingrediente(array_ingred);
                            printf("\n\nAperte enter para continuar");
                            fflush(stdin);
                            gets(buffer);
                            break;
                            
                        case 4: 
                            system("cls");
                            editar_ingrediente(array_ingred, id_ingred++);
                            printf("\n\nAperte enter para continuar");
                            fflush(stdin);
                            gets(buffer);
                            break;
                        
                        case 5:
                            system("cls");
                            visualizar_ingredientes(array_ingred);
                            printf("\n\nAperte enter para continuar");
                            fflush(stdin);
                            gets(buffer);
                            break;
                        case 6:
                            acabar++;
                            break;
                    }
                }
                
                break;

            //Funções produtos
            case 3:
                acabar = 0;
                while (acabar == 0)
                {
                    system("cls");
                    int op = menu_produtos();

                    switch (op)
                    {
                        case 1:
                            system("cls");
                            adicionar_produto(array_prod, array_ingred, id_produto++);
                            printf("\n\nAperte enter para continuar");
                            fflush(stdin);
                            gets(buffer);
                            break;

                        case 2:
                            system("cls");
                            deletar_produto(array_prod);
                            printf("\n\nAperte enter para continuar");
                            fflush(stdin);
                            gets(buffer);
                            break;

                        case 3:
                            system("cls");
                            pesquisar_produto(array_prod, array_ingred);
                            printf("\n\nAperte enter para continuar");
                            fflush(stdin);
                            gets(buffer);
                            break;
                            
                        case 4:
                            system("cls");
                            visualizar_produtos(array_prod,array_ingred);
                            printf("\n\nAperte enter para continuar");
                            fflush(stdin);
                            gets(buffer);
                            break;
                        
                        case 5:
                            system("cls");
                            editar_produto(array_prod, array_ingred, id_produto++);
                            printf("\n\nAperte enter para continuar");
                            fflush(stdin);
                            gets(buffer);
                            break;

                        case 6:
                            acabar ++;
                            break;
                    }
                }
                break;
            
            //Funções pedidos
            case 4:
                acabar = 0;
                while (acabar == 0)
                {
                    system("cls");
                    int op = menu_pedido();

                    switch (op)
                    {
                        case 1:
                            system("cls");
                            add_pedido(array_ped, array_clie, array_prod, array_ingred, id_pedido++, &id_cliente, &id_produto);
                            printf("\n\nAperte enter para continuar");
                            fflush(stdin);
                            gets(buffer);
                            break;

                        case 2:
                            system("cls");
                            ver_pedidos(array_ped, array_clie, array_prod);
                            printf("\n\nAperte enter para continuar");
                            fflush(stdin);
                            gets(buffer);
                            break;

                        case 3:
                            system("cls");
                            pesquisar_pedido(array_ped, array_clie, array_prod);
                            printf("\n\nAperte enter para continuar");
                            fflush(stdin);
                            gets(buffer);
                            break;
                            
                        case 4:
                            system("cls");
                            atualizar_status(array_ped, array_clie, array_prod);
                            printf("\n\nAperte enter para continuar");
                            fflush(stdin);
                            gets(buffer);
                            break;
                        
                        case 5:
                            system("cls");
                            remover_pedido(array_ped,array_clie,array_prod);
                            printf("\n\nAperte enter para continuar");
                            fflush(stdin);
                            gets(buffer);
                            break;

                        case 6:
                            acabar ++;
                            break;

                    }

                }
                
                break;
            
            //Funções controle financeiro
            case 5:

                acabar = 0;

                while (acabar == 0)
                {
                    system("cls");
                    int op = menu_financeiro();

                    switch (op)
                    {
                        case 1:
                            system("cls");
                            gerar_relatorio_finan(array_ped);
                            printf("\n\nAperte enter para continuar");
                            fflush(stdin);
                            gets(buffer);
                            break;
                        
                        case 2:
                            acabar ++;
                            break;
                        }
                }
                
                break;
            
            //Sair
            case 6:
                printf("\nAte logo!");
                break;
        }
    }

    set_tsv_pedido(array_ped, "pedidos.tsv");
    set_tsv_cliente(array_clie, "clientes.tsv");
    set_tsv_ingrediente(array_ingred, "ingredientes.tsv");
    set_tsv_produtos(array_prod, "produtos.tsv");

    return 1;
}