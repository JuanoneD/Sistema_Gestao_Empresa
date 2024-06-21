#include "Estruturas.h"

typedef struct Array_Dinamico_Pedidos
{
    Pedido * array;
    int size;
    int capacity;
}Array_pedidos;

Array_pedidos * construtor_array_pedidos()
{
    Array_pedidos * new_ped = (Array_pedidos*)malloc(sizeof(Array_pedidos));
    new_ped->array = NULL;
    new_ped->size = 0; 
    new_ped->capacity = 0;
    return new_ped;
}

void add_pedido(Array_pedidos * array,int id, char id_cliente[], char id_produto[], char qtd_produto[], int preco_custo, int preco_venda, char data_entrega[], char status[])
{
    Pedido novo_pedido = construtor_pedido(id,id_cliente,id_produto,qtd_produto,preco_custo,preco_venda,data_entrega,status);
    if(!array->array)
    {
       array->capacity=2;
       array->array =(Pedido*)malloc(array->capacity*sizeof(Pedido));
    }
    if(array->size == array->capacity)
    {
        array->capacity*=2;
        array->array = (Pedido*)malloc(array->capacity*sizeof(Pedido));
    }
    array->array[array->size++] = novo_pedido;
}

