#include "Pedido_funcoes.h"

#ifndef Financeiro_funcoes
#define Financeiro_funcoes


void gerar_relatorio_finan(Array_pedidos * array_ped)
{
    char data_ini[20],data_fim[20];
    printf("Escreva a data de inicio mm/aa: ");
    fflush(stdin);
    gets(data_ini);
    printf("Escreva a data final mm/aa: ");
    fflush(stdin);
    gets(data_fim);
    float entrada,saida;
    entrada=saida=0;
    FILE * arq = fopen("Financeiro.txt","w");
    fprintf(arq,"Relatorio de %s a %s \n",data_ini,data_fim);
    fprintf(arq," PED | SAIDA | ENTRADA | LUCRO\n");
    printf(" PED | SAIDA | ENTRADA | LUCRO\n");
    for(int i=0;i<array_ped->size;i++)
    {
        Pedido * ped = get_pedido(array_ped,i);
        if(strcmp(data_ini,&ped->data_entrega[4])>=0 && strcmp(&ped->data_entrega[4],data_fim)<=0)
        {
            entrada += ped->preco_venda;
            saida += ped->preco_custo;
            printf(" %i | %.2f | %.2f | %.2f\n",ped->id,ped->preco_custo,ped->preco_venda,ped->preco_venda-ped->preco_custo);
            fprintf(arq," %i | %.2f | %.2f | %.2f\n",ped->id,ped->preco_custo,ped->preco_venda,ped->preco_venda-ped->preco_custo);
        }
    }
    printf("SAIDA TOTAL: %.2f | ENTRADA TOTAL: %.2f | LUCRO TOTAL: %.2f",saida,entrada,entrada-saida);
    fprintf(arq,"SAIDA TOTAL: %.2f | ENTRADA TOTAL: %.2f | LUCRO TOTAL: %.2f",saida,entrada,entrada-saida);
    fclose(arq);
}

#endif
