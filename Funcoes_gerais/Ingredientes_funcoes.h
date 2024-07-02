#include "..\Estruturas_Dados\Ingredientes_estruturas.h"

#ifndef Ingrediente_funcoes
#define Ingrediente_funcoes

    //Função que possui um menu com todas as funcionalidades da estrutura ingredientes
    int menu_ingredientes() 
    {
        int op = 0;

        while(op == 0) {

            printf("\n-----------------------------------------\n");
            printf("|------------ Ingredientes -------------|\n");
            printf("|----- 1 - Adicionar ingrediente -------|\n");
            printf("|----- 2 - Remover ingrediente ---------|\n");
            printf("|----- 3 - Pesquisar ingrediente -------|\n");
            printf("|----- 4 - Editar ingrediente ----------|\n");
            printf("|----- 5 - Visualizar estoque ----------|\n");
            printf("------ 6 - Sair ------------------------|\n");
            printf("-----------------------------------------\n");

            printf("\n\nDigite a opcao desejada: ");
            scanf("%i", &op);

            //Se o usuário digitar um número que não corresponda a nenhuma das opções, será retornada uma mensagem de erro
            if (op == 0 || op > 6) 
            {
                printf("\nPor favor, digite uma opcao valida");
            }
        }

        return op;
    }

    //Função para pesquisar um ingrediente pelo nome ou id
    Ingrediente * pesquisar_ingrediente(Array_ingrediente * array) 
    {
        char search[100];

        printf("\n\n----------- PESQUISAR INGREDIENTE -------------");

        printf("\nDigite o ID ou Nome do ingrediente: ");
        scanf("%s", search);

        Ingrediente * ingrediente;
        
        //Verifica se a string informada pelo usuário se trata de uma palavra (nome) ou um número (id)
        if (e_numero(search) == 1)
        {
            ingrediente = get_ingrediente(array, pesquisar_id_ingrediente(array, atoi(search)));
        }
        else
        {
            ingrediente = pesquisar_nome_ingrediente(array,search);
        }

        if (ingrediente == NULL)
        {
            printf("Ingrediente nao encontrado! ");
            return NULL;
        } 
        else 
        {
            printf("\n\n---------- DADOS DO INGREDIENTE ----------");
            printf("\nID: %i", ingrediente->id);
            printf("\nNome: %s", ingrediente->nome);
            printf("\nQuantidade: %i", ingrediente->qta);       
            printf("\nPreco: R$ %f", ingrediente->preco);    
        }

        return ingrediente;
    }

    //Função que adiciona um novo ingrediente ao estoque
    void add_ingrediente(Array_ingrediente * array, int id) 
    {   
        char search[100];
        int valido = 0;
        char nome[50];
        int qta;
        float preco;
        int op;
        int new_qta = 0;

        printf("\n\nOpcoes: \n");
        printf("1 - Adicionar novo ingrediente \n");
        printf("2 - Acrescentar ingrediente ao estoque \n");

        printf("\n\nDigite a opcao desejada: ");
        scanf("%i", &op);

        switch (op)
        {
            //Adiciona um novo ingrediente ao estoque
            case 1:
                
                printf("\n\n---------- ADICIONAR NOVO INGREDIENTE ----------");
                printf("\nNome: ");
                fflush(stdin);      //permite que o usuário escreva mais de uma palavra sem dar erro
                gets(nome);         //semelhante ao scanf

                //verifica se o valor digitado pelo usuario eh um numero
                while(valido == 0) 
                {
                    printf("\nQuantidade: ");
                    scanf("%s", search);

                    if (e_numero(search) == 1)
                    {
                        qta = atoi(search);
                        valido = 1;
                        break;
                    }
                    else
                    {
                        printf("\nPor favor, digite um valor valido\n");
                    }
                }

                valido = 0;
                while(valido == 0) 
                {
                    printf("\nPreco: ");
                    scanf("%s", search);

                    if (e_numero(search) == 1)
                    {
                        preco = atoi(search);
                        valido = 1;
                        break;
                    }
                    else
                    {
                        printf("\nPor favor, digite um valor valido\n");
                    }
                }

                _add_ingrediente(array, id, nome, qta, preco);

                printf("\n\nNovo ingrediente adicionado com sucesso!\n");
                break;
            
            //Acrescenta de um mesmo ingrediente já existente no estoque
            case 2:

                printf("\n\n----------- ACRESCENTAR INGREDIENTE -------------");
                printf("\nAntes de acrescentar, sera preciso verificar o item no estoque\n");

                Ingrediente * ingrediente =  pesquisar_ingrediente(array);
            
                if(ingrediente != NULL)
                {
                    //verifica se o valor digitado pelo usuario eh um numero
                    while(valido == 0) 
                    {
                        printf("\nDigite a quantidade que sera adicionada: ");
                        scanf("%s", search);

                        if (e_numero(search) == 1)
                        {
                            new_qta = atoi(search);
                            valido = 1;
                            break;
                        }
                        else
                        {
                            printf("\nPor favor, digite um valor valido\n");
                        }
                    }
                    ingrediente->qta = ingrediente->qta + new_qta;  //atualiza a quantidade do ingrediente
                } 
                else
                {   
                    //Se o ingrediente informado não existir no estoque, o usuário terá a opção de adicioná-lo ou retornar ao menu
                    printf("\nDigite 1 para adicionar um novo ingrediente ou 0 para voltar ao menu principal: ");
                    scanf("%i", &op);

                    if (op == 1){
                        add_ingrediente(array, id);
                    }
                    else
                    {
                        menu_ingredientes();
                    }
                }
                
                break;
        }
    }

    //Função que remove um ingrediente do estoque
    void deletar_ingrediente(Array_ingrediente * array) 
    {
        char search[50];

        printf("\n\n---------- DELETAR INGREDIENTE ----------");
        printf("\nDigite o ID ou Nome do cliente que deseja deletar: ");
        fflush(stdin);      
        gets(search);

        Ingrediente * ingrediente;

        //Verifica se a string informada pelo usuário se trata de uma palavra (nome) ou um número (id)
        if (e_numero(search) == 1)
        {
            ingrediente = get_ingrediente(array, pesquisar_id_ingrediente(array, atoi(search)));
        }
        else
        {
            ingrediente = pesquisar_nome_ingrediente(array,search);
        }

        //Caso a identificação informada não corresponda com nenhum ingrediente, será retornado uma mensagem de erro
        if(ingrediente == NULL) 
        {
            printf("\n\nIngrediente nao encontrado.");
        }
        else 
        {
            _deletar_ingrediente(array, ingrediente->id); 
        }

        printf("\nO ingrediente %s foi deletado com sucesso!", ingrediente->nome);

    }

    //Função para visualizar o array de ingredientes em ordem alfabética, por id (crescente e decrescente) ou por quantidade
    void visualizar_ingredientes(Array_ingrediente * array) 
    {    
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

        //Se a lista estiver vazia, será retornada uma mensagem 
        if(array->array == NULL) 
        {
            printf("\n\nO estoque de ingredientes esta vazio.");
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

    //Função para editar as informações de um ingrediente específico
    void editar_ingrediente(Array_ingrediente * array, int id){

        int valido = 0;
        char search[100];

        printf("\n\n----------- EDITAR INGREDIENTE -------------");
        printf("\nAntes de editar, sera preciso verificar o item no estoque\n");
        
        Ingrediente * ingrediente =  pesquisar_ingrediente(array);

        if(ingrediente != NULL)
        {
            printf("\n\nNome do ingrediente: ");
            fflush(stdin);
            gets(ingrediente->nome);

            //verifica se o valor digitado pelo usuario eh um numero
            while(valido == 0) 
            {
                printf("\nQuantidade: ");
                scanf("%s", search);

                if (e_numero(search) == 1)
                {
                    ingrediente->qta = atoi(search);
                    valido = 1;
                    break;
                }
                else
                {
                    printf("\nPor favor, digite um valor valido\n");
                }
            }

            while(valido == 0) 
            {
                printf("\nDigite a quantidade que sera adicionada: ");
                scanf("%s", search);

                if (e_numero(search) == 1)
                {
                    ingrediente->preco = atoi(search);
                    valido = 1;
                    break;
                }
                else
                {
                    printf("\nPor favor, digite um valor valido\n");
                }
            }

            printf("\nPreco: R$ ");
            scanf("%f", &ingrediente->preco);
        } 
        else
        {   
            //Se o ingrediente informado não existir no estoque, o usuário terá a opção de adicioná-lo ou retornar ao menu
            int op;
            printf("\nDigite 1 para adicionar um novo ingrediente ou 0 para voltar ao menu principal: ");
            scanf("%i", &op);

            if (op == 1){
                add_ingrediente(array, id);
            }
            else
            {
                menu_ingredientes();
            }
        }
    }
    
    int get_id_ingrediente(Array_ingrediente * array)
    {
        Ingrediente * ingred = get_ingrediente(array,array->size-1);
        if(!ingred) return -1;
        return ingred->id+1;
    }
    
#endif

