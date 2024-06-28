#include "Estruturas_Dados\Ingredientes_estruturas.h"
#include "Estruturas_Dados\Pedidos_estruturas.h"
#include <ctype.h>

//Recebe um buffer == String e o endereço de array e adiciona os valores que existem no buffer no array e retorna o tamanho do array
int split_ids(char * buffer,int ** array)
{
    int i = 0;
    int size = 0;
    char word[100];
    while(*buffer)
    {
        i = 0;
        while(*buffer && *buffer != ',')
        {
            word[i++] = *buffer++;
        }
        word[i] = '\0';
        buffer++;
        *array =(int*)realloc(*array,(size+1)*sizeof(int));
        //printf("%i ",atoi(word));
        (*array)[size++] = atoi(word);
    }
    return size;
}

int main()
{
    char word[] = "23,23,23,23,23,23";
    int * ids = malloc(sizeof(int));

    int size = split_ids(word,&array);

    for(int i =0;i<size;i++)
    {
        printf("%i ",pesquisar_id_ingrediente(ids[i]));
    }

    free(array);
    
}