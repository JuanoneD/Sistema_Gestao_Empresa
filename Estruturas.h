#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef Estruturas
#define Estruturas

    typedef struct Ingrediente
    {
        int id;
        char nome[50];
        char un_medida[50];
        float preço;
    }Ingrediente;

    Ingrediente construtor_ingrediente(int id,char name[],char un_med[],float preco)
    {
        Ingrediente novo;
        novo.id = id;
        strcpy(novo.nome,name);
        strcpy(novo.un_medida,un_med);
        novo.preço = preco;
        return novo;
    }



#endif

