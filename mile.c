#include "Estruturas_Dados\Produtos_estruturas.h"

int main()
{
    Array_produtos *  produtos = construtor_array_produtos();
    get_tsv_produto(produtos, "produtos.tsv");
    add_produto(produtos, 0, "Bolo de cenoura", "1kg", "1,2", 30.00);
    add_produto(produtos, 1, "Bolinho de cenoura", "500g", "1,2", 15.00);
    add_produto(produtos, 2, "Bolo de  com cholate", "1kg", "1,2", 35.00);
    printf("%s",produtos->array[2].nome);

    int i = pesquisar_id_produto(produtos, 1);
    printf("\n%i", i);
    organizar_array(produtos);
    organizar_array(produtos);

   set_tsv_produtos(produtos, "produtos.tsv");
   destruir_array_produtos(produtos);
    
}