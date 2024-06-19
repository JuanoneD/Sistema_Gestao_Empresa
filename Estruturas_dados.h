#include "Estruturas.h"

#ifndef Estruturas_dados
#define Estruturas_dados

typedef struct Array_dinamico_produtos
{
    Produtos * array;
    int size;
    int capacity;
}Array_produtos;

Array_produtos * construtor_array_produtos()
{
    Array_produtos * novo = (Array_produtos*)malloc(sizeof(Array_produtos));
    novo->array = NULL;
    novo->capacity = 0;
    novo->size = 0;
    return novo;
}

///addd


Produtos * get_produto(Array_produtos *array,int index)
{
    if(index>= array->size)
    {
        return NULL;
    }
    return &array->array[index];
}

//// espaço para fazer sort

void organizar_array(Array_produtos * array)
{
    _quick_sort(array,0,array->size-1);
}

void swap(Array_produtos * array,int i,int j)
{
	Produtos temp = array->array[i];
	array->array[i] = array->array[j];
	array->array[j] = temp;
}

void _quick_sort(Array_produtos * v, int begin, int end)
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

///

int pesquisar_id(Array_produtos *array,int id)
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