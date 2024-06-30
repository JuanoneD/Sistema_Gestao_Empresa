#include "Estruturas.h"

#ifndef Clientes_estruturas
#define Clientes_estruturas

typedef struct Array_dinamico_cliente
{
    Cliente * array;
    int size;
    int capacity;

} Array_cliente;

//Cria o construtor de cliente
Array_cliente * construtor_array_cliente()
{
    Array_cliente * novo = (Array_cliente*)malloc(sizeof(Array_cliente));
    
    novo->array = NULL;
    novo->capacity = 0;
    novo->size = 0;

    return novo;
}

//Função para adicionar um cliente ao banco de dados
void _add_cliente(Array_cliente * array, int id, char nome[], char cpf[], char telefone[], char email[], char endereco[]) 
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
    if(index >= array->size || index < 0)
    {
        return NULL;
    }

    return &array->array[index];
}

// Ordenação 
void swap(Array_cliente * array, int i, int j)
{
	Cliente temp = array->array[i];
	array->array[i] = array->array[j];
	array->array[j] = temp;
}

//Função que organiza o array em ordem crescente
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
	
	_quick_sort(v, begin, i - 1);
	_quick_sort(v, i + 1, end);
}

//Chama a função que organiza em ordem crescente
void organizar_array(Array_cliente * array)
{
    _quick_sort(array,0,array->size-1);
}

//Função que organiza o array em ordem decrescente
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
	
	ordem_decrescente(v, begin, i - 1);
	ordem_decrescente(v, i + 1, end);
}

//Chama a função que organiza em ordem decrescente
void organizar_array_decrescente(Array_cliente * array)
{
    ordem_decrescente(array,0,array->size-1);
}

//Função que ordena a lista de clientes em ordem alfabética
void ordem_alfabetica_cliente(Array_cliente * array, int begin, int end) 
{
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
	
	ordem_alfabetica_cliente(array, begin, i - 1);
	ordem_alfabetica_cliente(array, i + 1, end);
}

//Função que realiza a pesquisa por nome no array de clientes
Cliente * pesquisar_nome_cliente(Array_cliente * array, char nome[]) {

    for(int i = 0; i < array->size; i++)
	{
        if(strcmp(array->array[i].nome, nome) == 0) 
        {
            return &array->array[i];
        }
	}

    return NULL;
}

//Função que realiza a pesquisa por id no array de clientes
int pesquisar_id_cliente(Array_cliente *array, int id)
{
    organizar_array(array);

    //organizar pelo id
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
void split_line_cliente(char * buffer, int * id, char * nome, char * cpf, char * telefone, char * email, char * endereco)
{
    char new_id[20], new_nome[100], new_cpf[20], new_telefone[30], new_email[60], new_endereco[60];
    
    int i = 0;

    while(*buffer && *buffer != '\t')
    {
        new_id[i++] = *buffer++;
    }

    new_id[i] = '\0';
    buffer++;
    *id = atoi(new_id);

    i = 0;

    while(*buffer && *buffer != '\t')
    {
        new_nome[i++] = *buffer++;
    }

    new_nome[i] = '\0';
    buffer++;
    strcpy(nome,new_nome);

    i = 0;

    while(*buffer && *buffer != '\t')
    {
        new_cpf[i++] = *buffer++;
    }

    new_cpf[i] = '\0';
    buffer++;
    strcpy(cpf,new_cpf);

    i = 0;

    while(*buffer && *buffer != '\t')
    {
        new_telefone[i++] = *buffer++;
    }

    new_telefone[i] = '\0';
    buffer++;
    strcpy(telefone,new_telefone);

    i = 0;

    while(*buffer && *buffer != '\t')
    {
        new_email[i++] = *buffer++;
    }

    new_email[i] = '\0';
    buffer++;
    strcpy(email,new_email);

    i = 0;

    while(*buffer && *buffer != '\n')
    {
        new_endereco[i++] = *buffer++;
    }

    new_endereco[i] = '\0';
    buffer++;
    strcpy(endereco,new_endereco);
    
}

//Função que chama o arquivo tsv de clientes
void get_tsv_cliente(Array_cliente * array, char arquivo[])
{
    int id;
    char buffer[1000], nome[100], cpf[100], telefone[100], email[100], endereco[100];

    FILE * arq = fopen(arquivo, "r");
    if(!arq) return;
    fgets(buffer,999,arq);

    while (fgets(buffer,999,arq))
    {
        split_line_cliente(buffer, &id, nome, cpf, telefone, email, endereco);
        _add_cliente(array, id, nome, cpf, telefone, email, endereco);
    }

    fclose(arq);
}

//Função que altera o arquivo tsv de clientes
void set_tsv_cliente(Array_cliente * array, char arquivo[])
{
    organizar_array(array);

    FILE * arq = fopen(arquivo, "w");
    fprintf(arq,"ID\tNOME\tCPF\tTELEFONE\tEMAIL\tENDERECO\n");

    for(int i=0;i<array->size;i++)
    {
        Cliente * cliente = get_cliente(array, i);
        fprintf(arq,"%i\t%s\t%s\t%s\t%s\t%s\n", cliente->id, cliente->nome, cliente->cpf, cliente->telefone, cliente->email, cliente->endereco);
    }

    fclose(arq);
}

//Função que remove o cliente do array
void _deletar_clientes(Array_cliente * array, int id)
{
    int i = pesquisar_id_cliente(array, id);

    swap(array, i, array->size-1);
    array->size--;
}

//Free do array de clientes
void destruir_array_cliente(Array_cliente * array)
{
    free(array->array);
    free(array);
}

#endif