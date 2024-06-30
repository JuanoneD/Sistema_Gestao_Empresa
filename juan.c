#include "..\Funcoes_gerais\Pedido_funcoes.h"



int main()
{
    Array_pedidos * array_ped = construtor_array_pedidos();
    get_tsv_pedido(array_ped,"pedidos.tsv");

}