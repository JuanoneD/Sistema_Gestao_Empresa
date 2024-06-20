#include "Estruturas.h"

#ifndef Estruturas_dados_cliente
#define Estruturas_dados_cliente

typedef struct Array_dinamico_ingrediente
{
    Ingrediente * array;
    int size;
    int capacity;
}Array_ingrediente;

Array_ingrediente * construtor_array_ingrediente()
{
    Array_ingrediente * novo = (Array_ingrediente*)malloc(sizeof(Array_ingrediente));
    novo->array = NULL;
    novo->capacity = 0;
    novo->size = 0;
    return novo;
}

///addd
void add_ingrediente(Array_ingrediente * array,int id,char name[],char un_md[],float preco)
{
    Ingrediente novo_ingrediente = construtor_ingrediente(id,name,un_md,preco);
    if(!array->array)
    {
        array->capacity = 2;
        array->array =(Ingrediente*)malloc(array->capacity*sizeof(Ingrediente));
    }
    
    if(array->capacity == array->size)
    {
        array->capacity *=2;
        array->array =(Ingrediente*)realloc(array->array,array->capacity*sizeof(Ingrediente));
    }
    
    array->array[array->size++] = novo_ingrediente;
}


Ingrediente * get_ingrediente(Array_ingrediente *array, int index)
{
    if(index >= array->size || index < 0)
    {
        return NULL;
    }
    return &array->array[index];
}

//// espaço para fazer sort

void organizar_array(Array_ingrediente * array)
{
    quick_sort(array,0,array->size-1);
}

void swap(Array_ingrediente * array,int i,int j)
{
	Ingrediente temp = array->array[i];
	array->array[i] = array->array[j];
	array->array[j] = temp;
}

void quick_sort(Array_ingrediente * v, int begin, int end)
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

///

int pesquisar_id(Array_ingrediente *array,int id)
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

void split_line_ingrediente(char *buffer,int *id,char *nome,int *quant,float *preco)
{
    char new_id[20],name[100],quanti[20],new_preco[50];
    int i=0;
    while(*buffer && *buffer != '\t')
    {
        new_id[i++] = *buffer++;
    }
    new_id[i] = '\0';
    buffer++;
    *id = atoi(new_id);

    i = 0;
    while(*buffer&&*buffer !='\t')
    {
        name[i++] = *buffer++;
    }
    name[i] = '\0';
    buffer++;
    strcpy(nome,name);

    i=0;
    while(*buffer&&*buffer !='\t')
    {
        quanti[i++] = *buffer++;
    }
    quanti[i] = '\0';
    buffer++;
    *quant = atoi(quanti);

    i=0;
    while (*buffer && *buffer!='\t')
    {
        new_preco[i++] = *buffer++;
    }
    new_preco[i]='\0';
    *preco = atof(new_preco);

    
    
}
void get_tsv_ingrediente(Array_ingrediente * array)
{
    FILE * arq = fopen("ingrediente.tsv","r");
    if(!arq) return;
    char buffer[1000];
    fgets(buffer,999,arq);
    while (fgets(buffer,999,arq))
    {
        
    }
    
}

#endif