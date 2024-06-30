#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Gerais.h"

#ifndef Estruturas
#define Estruturas

typedef struct Ingrediente
{
    int id;
    char nome[50];
    int qta;
    float preco;

} Ingrediente;

Ingrediente construtor_ingrediente(int id, char name[], int qta, float preco)
{
    Ingrediente novo;

    novo.id = id;
    strcpy(novo.nome, name);
    novo.qta = qta;
    novo.preco = preco;

    return novo;
}

typedef struct Produto
{
    int id;
    char nome[50];
    char uniMedida[10];
    char ingredientes[50];
    float preco;

} Produto;

Produto construtor_produto(int id, char nome[], char uniMedida[], char ingredientes[], float preco)
{
    Produto novo;

    novo.id = id;
    strcpy(novo.nome, nome);
    strcpy(novo.uniMedida, uniMedida);
    strcpy(novo.ingredientes, ingredientes);
    novo.preco = preco;

    return novo;
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
    strcpy(novo.nome, nome);
    strcpy(novo.cpf, cpf);
    strcpy(novo.telefone, telefone);
    strcpy(novo.email, email);
    strcpy(novo.endereco, endereco);

    return novo;
}

typedef struct Pedido
{
    int id;
    char id_cliente[50];
    char id_produto[20];
    char qtd_produto[10];
    float preco_custo;
    float preco_venda;
    char data_entrega[12];
    char status[20];

} Pedido;

Pedido construtor_pedido(int id, char id_cliente[], char id_produto[], char qtd_produto[], float preco_custo, float preco_venda, char data_entrega[], char status[])
{
    Pedido novo;
    
    novo.id = id;
    strcpy(novo.id_cliente, id_cliente);
    strcpy(novo.id_produto, id_produto);
    strcpy(novo.qtd_produto, qtd_produto);
    novo.preco_custo = preco_custo;
    novo.preco_venda = preco_venda;
    strcpy(novo.data_entrega, data_entrega);
    strcpy(novo.status, status);

    return novo;
}

#endif
