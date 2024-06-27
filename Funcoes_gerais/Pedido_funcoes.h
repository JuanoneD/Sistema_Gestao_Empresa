#include <..\Estruturas_Dados\Pedidos_estruturas.h>
#include <Clientes_funcoes.h>
#include <Produtos_funcoes.h>

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

void split_ids(char * buffer,int * array)
{
    int i = 0;
    int size = 1;
    while(int id = single_split(&buffer,',') > 0)
    {
        array =(int *)realloc(array,size++ * sizeof(int));
        array[i++] = id;
    }
}

void menu_pedido()
{
    printf("----------------------------------------");
    printf("|------------- Pedidos ----------------|");
    printf("|------ 1 - Inserir novo pedido -------|");
    printf("|------ 2 - Remover um pedido ---------|");
    printf("|------ 3 - Pesquisar um pedido -------|");
    printf("|------ 4 - Vizualizar pedido ---------|");
    printf("|------ 0 -  Sair ---------------------|");
    printf("---------------------------------------");

}

void add_pedido(Array_pedidos * array,Array_cliente * array_clie,Array_produtos * array_prod,int id_pedido,int *id_cliente,int *id_produto)
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
        printf("Digite o id do cliente desejado,caso exista mais de um cliente separar por virgula:\n");
        scanf(" %s",new_client_id);
    }

    printf("Selecionar:\n1 - Produtos existentes\n2 - Adicionar novo\n");
    scanf("%i",&menu);
    if(menu == 2)
    {
        adicionar_produto(array_prod,*id_produto);
        *id_produto = *id_produto + 1;
    }
    else
    {
        visualizar_produtos(array_prod);
        printf("Digite o id do produto desejado,caso exista mais de um produto separar por virgula:\n");
        scanf(" %s",new_product_id);
    }
    printf("Digite a quantidade do produto na mesma ordem separado por virgulas");
    scanf(" %s",qtd_produto);





}

#endif // 