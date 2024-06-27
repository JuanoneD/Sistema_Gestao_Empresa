#include "Estruturas.h"

#ifndef Ingredientes_estruturas
#define Ingredientes_estruturas

typedef struct Array_dinamico_ingrediente
{
    Ingrediente * array;
    int size;
    int capacity;

} Array_ingrediente;

Array_ingrediente * construtor_array_ingrediente()
{
    Array_ingrediente * novo = (Array_ingrediente*)malloc(sizeof(Array_ingrediente));
    novo->array = NULL;
    novo->capacity = 0;
    novo->size = 0;
    return novo;
}

//Função para adicionar um ingrediente na lista
void _add_ingrediente(Array_ingrediente * array,int id,char name[],int un_md,float preco)
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

//Função para retornar um ingrediente pelo index
Ingrediente * get_ingrediente(Array_ingrediente *array, int index)
{
    if(index >= array->size || index < 0)
    {
        return NULL;
    }
    return &array->array[index];
}

//Função para retornar o tamanho da lista de ingredientes
int get_size_ingrediente(Array_ingrediente * array)
{
    return array->size;
}

// Ordenação 
void swap(Array_ingrediente * array,int i,int j)
{
	Ingrediente temp = array->array[i];
	array->array[i] = array->array[j];
	array->array[j] = temp;
}

void quick_sort_asc(Array_ingrediente * v, int begin, int end)
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
	
	quick_sort_asc(v, begin, i - 1);
	quick_sort_asc(v, i + 1, end);
}

void organizar_array_asc(Array_ingrediente * array)
{
    quick_sort_asc(array,0,array->size-1);
}

void quick_sort_dsc(Array_ingrediente * v, int begin, int end)
{
	if(end <= begin)
	{
		return;
	}
	
	int i = begin;
	int j = end;
	
	while(i != j)
	{
		while(j > i && v->array[j].id <= v->array[i].id)
		{
			j--;
		}
		swap(v, i, j);
		
		while(i < j && v->array[i].id >= v->array[j].id)
		{
			i++;
		}
		swap(v, i, j);
	}
	
	quick_sort_dsc(v, begin, i - 1);
	quick_sort_dsc(v, i + 1, end);
}
void organizar_array_dsc(Array_ingrediente * array)
{
    quick_sort_dsc(array,0,array->size-1);
}

void quick_sort_qta(Array_ingrediente * v, int begin, int end)
{
	if(end <= begin)
	{
		return;
	}
	
	int i = begin;
	int j = end;
	
	while(i != j)
	{
		while(j > i && v->array[j].qta >= v->array[i].qta)
		{
			j--;
		}
		swap(v, i, j);
		
		while(i < j && v->array[i].qta <= v->array[j].qta)
		{
			i++;
		}
		swap(v, i, j);
	}
	
	quick_sort_qta(v, begin, i - 1);
	quick_sort_qta(v, i + 1, end);
}

void organizar_array_qta(Array_ingrediente * array)
{
    quick_sort_qta(array,0,array->size-1);
}

//Função que ordena a lista de ingredientes em ordem alfabética
void ordem_alfabetica_ingrediente(Array_ingrediente * array, int begin, int end) {

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
	
	ordem_alfabetica_ingrediente(array, begin, i - 1);
	ordem_alfabetica_ingrediente(array, i + 1, end);
}

///

int pesquisar_id_ingrediente(Array_ingrediente *array,int id)
{
    // organizar pelo id
    organizar_array_asc(array);
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

Ingrediente * pesquisar_nome_ingrediente(Array_ingrediente * array, char nome[]) {

    for(int i = 0; i < array->size; i++)
	{
        if(strcmp(array->array[i].nome, nome) == 0) {

            return &array->array[i];
        }
	}

    return NULL;
}

void split_line_ingrediente(char *buffer,int *id,char *nome,int *qta,float *preco)
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
    while(*buffer && *buffer !='\t')
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
    *qta = atoi(quanti);

    i=0;
    while (*buffer && *buffer!='\t')
    {
        new_preco[i++] = *buffer++;
    }
    new_preco[i]='\0';
    *preco = atof(new_preco);
    
}
void _deletar_ingrediente(Array_ingrediente * array, int id)
{
    int i = pesquisar_id_ingrediente(array, id);

    swap(array, i, array->size-1);
    array->size--;
}


void get_tsv_ingrediente(Array_ingrediente * array, char arquivo[])
{
    int id,quant;
    float preco;
    char buffer[1000],nome[100];
    FILE * arq = fopen(arquivo,"r");
    if(!arq) return;
    fgets(buffer,999,arq);
    while (fgets(buffer,999,arq))
    {
        split_line_ingrediente(buffer,&id,nome,&quant,&preco);
        add_ingrediente(array,id,nome,quant,preco);
    }
    fclose(arq);
}

void set_tsv_ingrediente(Array_ingrediente * array, char arquivo[])
{
    organizar_array_asc(array);
    FILE *arq = fopen(arquivo,"w");
    fprintf(arq,"ID\tNOME\tQTD\tPREÇO\n");
    for(int i=0;i<array->size;i++)
    {
        Ingrediente * ingre = get_ingrediente(array,i);
        fprintf(arq,"%i\t%s\t%i\t%f\n",ingre->id,ingre->nome,ingre->qta,ingre->preco);
    }
    fclose(arq);
}

void destruir_array_ingrediente(Array_ingrediente * array)
{
    free(array->array);
    free(array);
}

#endif