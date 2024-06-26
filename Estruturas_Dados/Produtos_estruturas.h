#include "Estruturas.h"

#ifndef Produtos_estruturas
#define Produtos_estruturas

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

//Função para adicionar um produto ao banco de dados
void _add_produto(Array_produtos * array, int id, char nome[], char uniMedida[], char ingredientes[], float preco)
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

//Função que retorna o pedido através do índice do array
Produto * get_produto(Array_produtos * array, int index)
{
    if(index >= array->size || index < 0 )
    {
        return NULL;
    }

    return &array->array[index];
}

// fazer o sort aq
void swap_produtos(Array_produtos * array, int i, int j)
{
	Produto temp = array->array[i];

	array->array[i] = array->array[j];
	array->array[j] = temp;
}

//Função que organiza o array em ordem crescente
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

		swap_produtos(v, i, j);
		
		while(i < j && v->array[i].id <= v->array[j].id)
		{
			i++;
		}

		swap_produtos(v, i, j);
	}
	
	quick_sort(v, begin, i - 1);
	quick_sort(v, i + 1, end);
}

//Chama a função que organiza em ordem crescente
void organizar_array_produtos(Array_produtos * array)
{
    quick_sort(array, 0, array->size-1);
}

//Função que realiza a pesquisa por id no array de produtos
int _pesquisar_id_produto(Array_produtos * array, int id)
{
    // organizar pelo id
    organizar_array_produtos(array);

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

//Função que ordena a lista de produtos em ordem alfabética
void _ordem_alfabetica_produto(Array_produtos * array, int begin, int end)
{
    if(end <= begin)
	{
		return ;
	}
	
	int i = begin;
	int j = end;
	
	while(i != j)
	{
		while(j > i && strcmp(array->array[j].nome,array->array[i].nome) >= 0)
		{
			j--;
		}

		swap_produtos(array, i, j);
		
		while(i < j && strcmp(array->array[i].nome, array->array[j].nome) <= 0)
		{
			i++;
		}

		swap_produtos(array, i, j);
	}
	
	_ordem_alfabetica_produto(array, begin, i - 1);
	_ordem_alfabetica_produto(array, i + 1, end);
}

//Função que realiza a pesquisa por nome no array de produtos
Produto * _pesquisar_nome_produto(Array_produtos * array, char nome[]) 
{
    for(int i = 0; i < array->size; i++)
	{
        if(strcmp(array->array[i].nome, nome) == 0) {

            return &array->array[i];
        }
	}

    return NULL;
}

void split_line_produtos(char *buffer, int *id, char *nome, char *uniMedida, char *ingredientes, float *preco)
{
    char new_id[20], name[100], uniMed[20], ingred[50], new_preco[20];

    //ID
    int i=0;

    while(*buffer && *buffer != '\t')
    {
        new_id[i++] = *buffer++;
    }

    new_id[i] = '\0';
    buffer++;
    *id = atoi(new_id);

    // Nome
    i = 0;

    while(*buffer && *buffer !='\t')
    {
        name[i++] = *buffer++;
    }

    name[i] = '\0';
    buffer++;
    strcpy(nome,name);
    
    // Unidade de Medida
    i = 0;

    while(*buffer&&*buffer !='\t')
    {
        uniMed[i++] = *buffer++;
    }

    uniMed[i] = '\0';
    buffer++;
    strcpy(uniMedida,uniMed);

    // Ingredientes
    i = 0;

    while (*buffer && *buffer!='\t')
    {
        ingred[i++] = *buffer++;
    }

    ingred[i]='\0';
    strcpy(ingredientes,ingred);
    
    // Preço
    i = 0;

    while (*buffer && *buffer!='\n')
    {
        new_preco[i++] = *buffer++;
    }

    new_preco[i]='\0';

    *preco = atof(new_preco);

}

//Função que chama o arquivo tsv de produtos
// Começar a ver daqui
void get_tsv_produto(Array_produtos * array, char arquivo[])
{
    int id;
    float preco;
    char buffer[1000], nome[100], uniMed[100], ingred[100];
    
    FILE * arq = fopen(arquivo,"r");
    if(!arq) return;
    fgets(buffer,999,arq);

    while (fgets(buffer,999,arq))
    {
        split_line_produtos(buffer,&id, nome,uniMed,ingred, &preco);
        _add_produto(array, id, nome, uniMed, ingred, preco);
    }

    fclose(arq);
}

//Função que altera o arquivo tsv de produtos
void set_tsv_produtos(Array_produtos * array, char arquivo[])
{
    FILE *arq = fopen(arquivo,"w");
    fprintf(arq,"ID\tNOME\tUNI_MEDIDA\tINGREDIENTES\tPREÇO\n");

    for(int i=0;i<array->size;i++)
    {
        Produto * produto = get_produto(array, i);
        fprintf(arq,"%i\t%s\t%s\t%s\t%f\n",produto->id, produto->nome, produto->uniMedida, produto->ingredientes,produto->preco);
    }

    fclose(arq);
}

//Free do array de produtos
void destruir_array_produtos(Array_produtos * array)
{
    free(array->array);
    free(array);
}

//Função que remove o produto do array
void _deletar_produtos(Array_produtos * array, int id)
{
    int i = _pesquisar_id_produto(array, id);

    if (i < 0) {
        
        return;
    }

    swap_produtos(array, i, array->size-1);
    array->size--;
}

#endif 