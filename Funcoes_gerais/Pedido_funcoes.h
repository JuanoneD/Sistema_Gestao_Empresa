#include <..\Estruturas_Dados\Pedidos_estruturas.h>
#include <Clientes_funcoes.h>
#include <Produtos_funcoes.h>
#include <..\Estruturas_Dados\Gerais.h>

#ifndef Pedidos_funcoes
#define Pedidos_funcoes

int single_split(char ** buffer,char endpoint)
{
    char word[100];
    int i=0;

    while(**buffer || **buffer != endpoint)
    {
        word[i++] = **buffer++;
    }

    word[i] = '\0';
    **buffer++;
    if(i >= 0) return atoi(word);

    return -1;
}

// Função que possui um menu com todas das funcionalidades da estrutura pedidos
void menu_pedido()
{
    printf("----------------------------------------");
    printf("|------------- Pedidos ----------------|");
    printf("|------ 1 - Inserir novo pedido -------|");
    printf("|------ 2 - Vizualizar pedidos --------|");
    printf("|------ 3 - Pesquisar um pedido -------|");
    printf("|------ 4 - Remover um pedido  --------|");
    printf("|------ 0 -  Sair ---------------------|");
    printf("---------------------------------------");

}

// Função que adiciona um novo pedido no array de pedidos
void add_pedido(Array_pedidos * array,Array_cliente * array_clie,Array_produtos * array_prod,Array_ingrediente * array_inged,int id_pedido,int *id_cliente,int *id_produto)
{
    char new_client_id[100],new_product_id[100],qtd_produto[100],data[100],status[100];
    float preco_custo,preco_venda;
    int menu = 0;

    printf("Selecionar:\n1 - Cliente existente\n2 - Criar novo cliente\n");
    scanf("%i",&menu);
    
    if(menu == 2) 
    {
        add_cliente(array_clie,*id_cliente);
        *id_cliente = *id_cliente + 1; 
    }
    else
    {
        visualizar_clientes(array_clie);
        printf("Digite o id do cliente desejado,caso exista mais de um cliente adicionar separado por virgula:\n");
        scanf(" %s",new_client_id);
    }

    printf("Selecionar:\n1 - Produtos existentes\n2 - Adicionar novo\n");
    scanf("%i",&menu);

    if(menu == 2)
    {
        adicionar_produto(array_prod,array_inged,*id_produto);
        *id_produto = *id_produto + 1;
    }
    else
    {
        visualizar_produtos(array_prod);
        printf("Digite o id do produto desejado,caso exista mais de um produto separar por virgula:\n");
        scanf(" %s",new_product_id);
    }

    printf("Digite a quantidade do produto na mesma ordem separado por virgulas\n");
    scanf(" %s",qtd_produto);

    int *ids =(int *)malloc(sizeof(int));
    int size = split_ids(new_product_id,&ids);
    int *prices = (int *)malloc(sizeof(int));
    split_ids(qtd_produto,&prices);
    float cust = 0;

    for(int i=0;i<size;i++)
    {
        Produto * prod = get_produto(array_prod,_pesquisar_id_produto(array_prod,ids[i]));
        cust += prod->preco * prices[i];
    }

    printf("O preco de custo foi: %.2f\n",cust);
    printf("O preco de venda e %.2f\n",cust *1.75);
    printf("Escreva a data de entrega dd/mm/aa");
    scanf(" %s",data);

    _add_pedido(array,id_pedido,new_client_id,new_product_id,qtd_produto,cust,cust*1.75,data,"Preparação");
}

void print_pedido(Pedido * ped,Array_cliente * array_clie,Array_produtos * array_prod)
{
    Pedido * ped;
    Cliente * clie;
    Produto * prod;
    int size;
    int *ids = (int*)malloc(sizeof(int));
    int *quant = (int*)malloc(sizeof(int));
    printf("\t %i |",ped->id);

    size = split_ids(ped->id_cliente,&ids);
    printf("\t");
    for(int j=0;j<size;j++)
    {
        clie = get_cliente(array_clie,pesquisar_id_cliente(array_clie,ids[j]));
        printf(" %s",clie->nome);
        if(j+1<size)printf(",");
    }
    printf(" |");

    size = split_ids(ped->id_produto,&ids);
    split_ids(ped->id_produto,&quant);
    printf("\t");
    for(int j=0;j<size;j++)
    {
        prod = get_produto(array_prod,_pesquisar_id_produto(array_prod,ids[j]));
        printf(" %s x %i",prod->nome,quant[j]);
        if(j+1<size)printf(",");
    }
    printf(" |");

    printf("\t %.2f |\t %.2f |\t %s |\t %s \n",ped->preco_custo,ped->preco_venda,ped->data_entrega,ped->status);
    free(ids);
    free(quant);
}

void ver_pedidos(Array_pedidos * array,Array_cliente * array_clie,Array_produtos * array_prod)
{
    Pedido * ped;
    printf(" ___________________ PEDIDOS_________________");
    printf("\t ID PEDIDO |\t CLIENTES |\t PRODUTOS x QUANTIDADE |\t PRECO DE CUSTO |\t PRECO DE VENDA |\t DATA |\t STATUS\n");
    for(int i=0;i<array->size;i++)
    {
        ped = get_pedido(array,i);
        print_pedido(ped,array_clie,array_prod);
    }

}

void pesquisar_pedido(Array_pedidos * array,Array_cliente * array_clie,Array_produtos * array_prod)
{
    char op[100];
    Cliente * clie;
    Pedido * ped;
    Produto * prod;
    int size;
    printf("Digite o id do pedido que deseja pesquisar ou nome do cliente:\n");
    fflush(stdin);
    gets(op);
    int *ids = (int*)malloc(sizeof(int));
    int *quant = (int*)malloc(sizeof(int));
    if(e_numero(op)==1)
    {
        ped =  get_pedido(array,pesquisar_id_pedido(array,atoi(op)));
        if(!ped)
        {
            printf("Pedido não encontrado\n");
            return;
        }
        print_pedido(ped,array_clie,array_prod);
        return;
    }

    clie = pesquisar_nome_cliente(array_clie,op);
    if(!clie)
    {
        printf("Cliente não encontrado\n");
        return;
    }
    int *ids = (int*)malloc(sizeof(int));
    for(int i=0;i<array->size;i++)
    {
        ped = get_pedido(array,i);
        int size = split_ids(ped->id_cliente,&ids);
        for(int j=0;j<size;j++)
        {
            if(clie->id == ids[j])
            {
                print_pedido(ped,array_clie,array_prod);
                break;
            }
        }
    }
    free(ids);
}

void remover_pedido(Array_pedidos * array,Array_cliente * array_clie,Array_produtos * array_prod)
{
    int menu;
    printf("Digite o ID do pedido que deseja remover ou 0 para ver todos os pedidos:\n");
    scanf("%i",&menu);
    if(menu == 0) ver_pedidos(array,array_clie,array_prod);
    printf("Digite o ID do pedido que deseja remover:\n");
    scanf("%i",&menu);
    if(pesquisar_id_pedido(array,menu) < 0)
    {
        printf("Pedido não encontrado");
        return;
    }
    deletar_pedidos(array,pesquisar_id_pedido(array,menu));
}
#endif 