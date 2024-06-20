#include "Estruturas.h"

#ifndef Produtos_dados
#define Produtos_dados

typedef struct Array_dinamico_produtos
{
    Produto * array;
    int size;
    int capacity;

}Array_produtos;

Array_produtos * construtor_array_produtos()
{
    Array_produtos * novo = (Array_produtos*)malloc(sizeof(Array_produtos));
    novo->size = 0;
    novo->capacity = 0;
    novo->array = NULL;

    return novo;
}

void add_produtos(Array_produtos * array, int id, char nome[], char uniMedida[], Ingrediente ingredientes, float preco)
{
    Produto novo_produto = construtor_produto(id,nome,uniMedida,ingredientes,preco);

    if (array->array == NULL)
    {
        array->capacity = 2;
        array->array = (Produto*)malloc(array->capacity*sizeof(Produto));

    }

    if(array->size == array->capacity)
    {
        array->capacity *=2;
        array->array = (Produto*)realloc(array->array, array->capacity*sizeof(Produto));

    }

    array->array[array->size++] = novo_produto;
}

Produto * get_produto(Array_produtos * array, int index)
{
    if(index >= array->size || index < 0 )
    {
        return NULL;
    }

    return &array->array[index];
}

// fazer o sort aq


void organizar_array(Array_produtos * array)
{
    quick_sort(array, 0, array->size-1);
}

void swap(Array_produtos * array, int i, int j)
{
	Produto temp = array->array[i];
	array->array[i] = array->array[j];
	array->array[j] = temp;
}

void quick_sort(Array_produtos * v, int begin, int end)
{
	if(end <= begin)
	{
		return;
	}
	
	int i = begin;
	int j = end;
	
	while(i != j)
	{
		while(j > i && v->array[j].id >= v->array[i].id)
		{
			j--;
		}
		swap(v, i, j);
		
		while(i < j && v->array[i].id <= v->array[j].id)
		{
			i++;
		}
		swap(v, i, j);
	}
	
	quick_sort(v, begin, i - 1);
	quick_sort(v, i + 1, end);
}

int pesquisar_id(Array_produtos * array, int id)
{
    // organizar pelo id
    organizar_array(array);
    //
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