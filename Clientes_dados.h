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

//Função para adicionar um cliente ao banco de dados
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

//Função que retorna o cliente através do índice do array
Cliente * get_cliente(Array_cliente *array, int index)
{
    if(index >= array->size)
    {
        return NULL;
    }
    return &array->array[index];
}

//// espaço para fazer sort

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

void organizar_array(Array_cliente * array)
{
    _quick_sort(array,0,array->size-1);
}

void ordem_decrescente(Array_cliente * v, int begin, int end)
{
	if(end <= begin)
	{
		return;
	}
	
	int i = begin;
	int j = end;
	
	while(i != j)
	{
		while(j > i && v->array[j].id <= v->array[j].id)
		{
			j--;
		}
		swap(v, i, j);
		
		while(i < j && v->array[j].id >= v->array[j].id)
		{
			i++;
		}
		swap(v, i, j);
	}
	
	ordem_decrescente(v, begin, i - 1);
	ordem_decrescente(v, i + 1, end);
}

void organizar_array_decrescente(Array_cliente * array)
{
    ordem_decrescente(array,0,array->size-1);
}

//Função que ordena a lista de clientes em ordem alfabética
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



Cliente * pesquisar_nome(Array_cliente * array, char nome[], int tamanho) {

    for(int i = 0; i < tamanho; i++)
	{
        if(strcmp(array->array[i].nome, nome) == 0) {

            return &array->array[i];
        }
	}
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




//alterar informações


void split_line_cliente(char *buffer,int *id,char *nome,char *quant,float *preco)
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
    strcpy(quant,quanti);

    i=0;
    while (*buffer && *buffer!='\t')
    {
        new_preco[i++] = *buffer++;
    }
    new_preco[i]='\0';
    *preco = atof(new_preco);
    
}
void get_tsv_cliente(Array_cliente * array,char arquivo[])
{
    int id;
    float preco;
    char buffer[1000],nome[100],quant[100];
    FILE * arq = fopen(arquivo,"r");
    if(!arq) return;
    fgets(buffer,999,arq);
    while (fgets(buffer,999,arq))
    {
        split_line_cliente(buffer,&id,nome,quant,&preco);
        add_cliente(array,id,nome,quant,preco);
    }
    fclose(arq);
}
void set_tsv_cliente(Array_cliente * array,char arquivo[])
{
    FILE *arq = fopen(arquivo,"w");
    fprintf(arq,"ID\tNOME\tQTD\tPREÇO\n");
    for(int i=0;i<array->size;i++)
    {
        Cliente * ingre = get_cliente(array,i);
        fprintf(arq,"%i\t%s\t%s\t%f\n",ingre->id,ingre->nome,ingre->un_medida,ingre->preco);
    }
    fclose(arq);
}

void destruir_array_cliente(Array_cliente * array)
{
    free(array->array);
    free(array);
}

#endif