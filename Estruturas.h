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
    
    typedef struct Produto
    {   
        int id;
        char nome[50];
        char uniMedida[10];
        Ingrediente ingredientes;
        float preco;
        
    } Produto;

    Produto construtor_produto(int id, char nome[], char uniMedida[], Ingrediente ingredientes, float preco)
    {
        Produto novo;
        novo.id = id;
        novo.nome = nome;
        novo.uniMedida = uniMedida;
        novo.
        
    }
    

    typedef struct Cliente
    {
        int id;
        char nome[50];
        char cpf[15];
        char telefone[15];
        char email[30];
        char endereco[50];

    } Cliente;
    
    Cliente construtor_cliente(int id, char nome[], char cpf[], char telefone[], char email[], char endereco[])
    {
        Cliente novo;
        novo.id = id;
        strcpy(novo.nome,nome);
        strcpy(novo.cpf,cpf);
        strcpy(novo.telefone,telefone);
        strcpy(novo.email,email);
        strcpy(novo.endereco,endereco);
    }


    


#endif

