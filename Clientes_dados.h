#include "Estruturas.h"

#ifndef Clientes_dados
#define Clientes_dados

typedef struct Array_dinamico_cliente
{
    Cliente * array;
    int size;
    int capacity;

} Array_cliente;

Array_cliente * construtor_array_cliente()
{
    Array_cliente * novo = (Array_cliente*)malloc(sizeof(Array_cliente));
    novo->array = NULL;
    novo->capacity = 0;
    novo->size = 0;

    return novo;
}

///add
void add_cliente(Array_cliente * array, int id, char nome[], char cpf[], char telefone[], char email[], char endereco[]) 
{
    Cliente novo_cliente = construtor_cliente(id, nome, cpf, telefone, email, endereco);

    if(array->array == NULL)
    {
        array->capacity = 2;
        array->array = (Cliente*) malloc(array->capacity * sizeof(Cliente));
    }

    if(array->capacity == array->size) 
    {
        array->capacity *= 2;
        array->array = (Cliente*) realloc(array->array, array->capacity * sizeof(Cliente));
    }

    array->array[array->size++] = novo_cliente;

}

Cliente * get_cliente(Array_cliente *array, int index)
{
    if(index >= array->size)
    {
        return NULL;
    }
    return &array->array[index];
}

//// espaço para fazer sort

void organizar_array(Array_cliente * array)
{
    _quick_sort(array,0,array->size-1);
}

void swap(Array_cliente * array, int i, int j)
{
	Cliente temp = array->array[i];
	array->array[i] = array->array[j];
	array->array[j] = temp;
}

void _quick_sort(Array_cliente * v, int begin, int end)
{
	if(end <= begin)
	{
		return;
	}
	
	int i = begin;
	int j = end;
	
	while(i != j)
	{
		while(j > i && v->array[j].id >= v->array[j].id)
		{
			j--;
		}
		swap(v, i, j);
		
		while(i < j && v->array[j].id <= v->array[j].id)
		{
			i++;
		}
		swap(v, i, j);
	}
	
	_quick_sort(v, begin, i - 1);
	_quick_sort(v, i + 1, end);
}

void ordem_alfabetica(Array_cliente * array, int begin, int end) {

    if(end <= begin)
	{
		return;
	}
	
	int i = begin;
	int j = end;
	
	while(i != j)
	{
		while(j > i && strcmp(array->array[j].nome,array->array[i].nome) >= 0)
		{
			j--;
		}
		swap(array, i, j);
		
		while(i < j && strcmp(array->array[i].nome, array->array[j].nome) <= 0)
		{
			i++;
		}
		swap(array, i, j);
	}
	
	ordem_alfabetica(array, begin, i - 1);
	ordem_alfabetica(array, i + 1, end);
}

int pesquisar_id(Array_cliente *array,int id)
{
    // organizar pelo id
    int begin = 0;
    int end = array->size - 1;
    int mid;

    while (begin <= end)
    {
        mid = begin + (end - begin) / 2;

        if(array->array[mid].id == id)
        {
            return mid;
        }

        if(array->array[mid].id < id)
        {
            begin = mid + 1;
        }

        if(array->array[mid].id > id)
        {
            end = mid - 1;
        }
    }

    return -1;
}

#endif