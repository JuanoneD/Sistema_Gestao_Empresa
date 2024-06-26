#include "Estruturas.h"

#ifndef Pedidos_estruturas
#define Pedidos_estruturas

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

    void _add_pedido(Array_pedidos * array,int id, char id_cliente[], char id_produto[], char qtd_produto[], float preco_custo, float preco_venda, char data_entrega[], char status[])
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
            array->array = (Pedido*)realloc(array->array,array->capacity*sizeof(Pedido));
        }
        array->array[array->size++] = novo_pedido;
    }

    Pedido * get_pedido(Array_pedidos * array,int index)
    {
        if(index >= array->size || index < 0) return NULL;

        return &array->array[index];
    }

    void swap_pedidos(Array_pedidos *array,int i,int j)
    {
        Pedido temp = array->array[i];
        array->array[i] = array->array[j];
        array->array[j] = temp;
    }

    void quick_sort_pedido(Array_pedidos * v, int begin, int end)
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
            swap_pedidos(v, i, j);
            
            while(i < j && v->array[i].id <= v->array[j].id)
            {
                i++;
            }
            swap_pedidos(v, i, j);
        }
        
        quick_sort_pedido(v, begin, i - 1);
        quick_sort_pedido(v, i + 1, end);
    }

    void organizar_array_pedido(Array_pedidos * array)
    {
        quick_sort_pedido(array, 0, array->size-1);
    }

    int pesquisar_id_pedido(Array_pedidos * array, int id)
    {
        // organizar pelo id
        organizar_array_pedido(array);
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

    void split_buffer_pedidos(char * buffer,int *id,char id_cliente[],char id_produto[],char qtd_produto[],float *preco_custo,float *preco_venda,char data_entrega[],char status[])
    {
        char temp[100];
        int i=0;
        while(*buffer && *buffer != '\t')
        {
            temp[i++] = *buffer++;
        }
        temp[i] = '\0';
        buffer++;
        *id = atoi(temp);

        i=0;
        while(*buffer && *buffer != '\t')
        {
            temp[i++] = *buffer++;
        }
        temp[i] = '\0';
        buffer++;
        strcpy(id_cliente,temp);

        i=0;
        while(*buffer && *buffer != '\t')
        {
            temp[i++] = *buffer++;
        }
        temp[i] = '\0';
        buffer++;
        strcpy(id_produto,temp);

        i=0;
        while(*buffer && *buffer != '\t')
        {
            temp[i++] = *buffer++;
        }
        temp[i] = '\0';
        buffer++;
        strcpy(qtd_produto,temp);

        i=0;
        while(*buffer && *buffer != '\t')
        {
            temp[i++] = *buffer++;
        }
        temp[i] = '\0';
        buffer++;
        *preco_custo = atof(temp);

        i=0;
        while(*buffer && *buffer != '\t')
        {
            temp[i++] = *buffer++;
        }
        temp[i] = '\0';
        buffer++;
        *preco_venda = atof(temp);

        i=0;
        while(*buffer && *buffer != '\t')
        {
            temp[i++] = *buffer++;
        }
        temp[i] = '\0';
        buffer++;
        strcpy(data_entrega,temp);

        i=0;
        while(*buffer && *buffer != '\t')
        {
            temp[i++] = *buffer++;
        }
        temp[i] = '\0';
        buffer++;
        strcpy(status,temp);
    }

    void get_tsv_pedido(Array_pedidos * array,char arquivo[])
    {
        int id;
        char id_cliente[100],id_produto[100],qtd_produto[100],data_entrega[100],buffer[1000],status[100];  
        float preco_custo,preco_venda;
        FILE * arq = fopen(arquivo,"r");
        if(!arq) return;
        fgets(buffer,999,arq);///ignorar primeira linha
        while (fgets(buffer,999,arq))
        {
            //printf("%s\n",buffer);
            split_buffer_pedidos(buffer,&id,id_cliente,id_produto,qtd_produto,&preco_custo,&preco_venda,data_entrega,status);
            _add_pedido(array,id,id_cliente,id_produto,qtd_produto,preco_custo,preco_venda,data_entrega,status);
            //printf("%i\t%s\t%s\t%s\t%f\t%f\t%s\t%s\n",id,id_cliente,id_produto,qtd_produto,preco_custo,preco_venda,data_entrega,status);
        }
        fclose(arq);
    }

    void set_tsv_produto(Array_pedidos * array,char arquivo[])
    {
        organizar_array_pedido(array);
        FILE *arq = fopen(arquivo,"w");
        fprintf(arq,"ID\tID_CLIENTE\tID_PRODUTO\tQTD_PRODUTO\tPRECO_CUSTO\tPRECO_VENDA\tDATA_ENTREGA\tSTATUS\n");
        for(int i=0;i<array->size;i++)
        {
            Pedido * ped = get_pedido(array,i);
            //printf("%i\t%s\t%s\t%s\t%f\t%f\t%s\t%s\n",ped->id,ped->id_cliente,ped->id_produto,ped->qtd_produto,ped->preco_custo,ped->preco_venda,ped->data_entrega,ped->status);      
            fprintf(arq,"%i\t%s\t%s\t%s\t%f\t%f\t%s\t%s\n",ped->id,ped->id_cliente,ped->id_produto,ped->qtd_produto,ped->preco_custo,ped->preco_venda,ped->data_entrega,ped->status);
        }
        fclose(arq);
    }

    void destruir_array_produtos(Array_pedidos * array)
    {
        free(array->array);
        free(array);
    }

    void deletar_produtos(Array_pedidos * array,int id)
    {
        int i = pesquisar_id_pedido(array,id);
        swap_pedidos(array,i,array->size-1);
        array->size--;
    }


#endif
