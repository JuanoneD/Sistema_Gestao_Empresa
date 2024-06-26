#include "Estruturas_Dados\Ingredientes_estruturas.h"
#include "Estruturas_Dados\Pedidos_estruturas.h"

int main()
{
    int id = 1;
    Array_pedidos * array = construtor_array_pedidos();
    get_tsv_pedido(array,"pedido.tsv");

    Pedido * ped = get_pedido(array,array->size-1);
    if (ped) id = ped->id+1;

    _add_pedido(array,id++,"JAO","23,24","23,24",23,24.6,"23/23/2323","OK");
    _add_pedido(array,id++,"JAO","23,24","23,24",23,24.6,"23/23/2323","OK");

    printf("\n%i\n",array->size);
    for(int i=0;i<array->size;i++)
    {
        ped = get_pedido(array,i);
        printf("%i\t%s\t%s\t%s\t%f\t%f\t%s\t%s\n",ped->id,ped->id_cliente,ped->id_produto,ped->qtd_produto,ped->preco_custo,ped->preco_venda,ped->data_entrega,ped->status);
    }
    set_tsv_produto(array,"pedido.tsv");

}