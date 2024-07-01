#include "Funcoes_gerais\Pedido_funcoes.h"



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

    //adicionar_produto(array_prod,array_ingred,id_produto++);
    //add_pedido(array_ped,array_clie,array_prod,array_ingred,id_pedido++,&id_cliente,&id_produto);
    ver_pedidos(array_ped,array_clie,array_prod);
    //pesquisar_pedido(array_ped,array_clie,array_prod);
    //atualizar_status(array_ped,array_clie,array_prod);
    remover_pedido(array_ped,array_clie,array_prod);



    set_tsv_pedido(array_ped,"pedidos.tsv");
    set_tsv_produtos(array_prod,"produtos.tsv");
}