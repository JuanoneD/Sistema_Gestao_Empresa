#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef Gerais
#define Gerais

    //Recebe um buffer == String e o endereço de array e adiciona os valores que existem no buffer no array e retorna o tamanho do array
    int split_ids(char * buffer, int ** array)
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
        return size-1;
    }

    //Recebe um buffer e retorna 0 se não for um numero e 1 se for um numero
    int eh_numero(char * buffer)
    {
        while(*buffer || *buffer != '\0')
        {
            if(isdigit(*buffer++) == 0) return 0;
        }
        return 1;
    }

#endif