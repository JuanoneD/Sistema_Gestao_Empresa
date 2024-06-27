#include "Estruturas_Dados\Ingredientes_estruturas.h"
#include "Estruturas_Dados\Pedidos_estruturas.h"
#include <ctype.h>

int single_split(char ** buffer,char endpoint)
{
    char word[100];
    int i=0;
    while(**buffer || **buffer != endpoint)
    {
        word[i++] = **buffer++;

    }
    word[i] = '\0';
    word[i+1] = **buffer++;
    if(i >= 0) return atoi(word);
    return -1;
}

int split_ids(char * buffer,int * array)
{
    int i = 0;
    int size = 1;
    int id = single_split(&buffer,',');
    while(id > 0)
    {
        array =(int *)realloc(array,size++ * sizeof(int));
        array[i++] = id;
        single_split(&buffer,',');
    }
    return i;
}

int main()
{
    char word[] = "23,23,23,";
    int * array = malloc(sizeof(int));

    int size = split_ids(word,array);

    for(int i =0;i<size;i++)
    {
        printf("%i ",array[i]);
    }

    
}