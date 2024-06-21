#include "Estruturas_Dados\Ingredientes_estruturas.h"

int main()
{
    Array_ingrediente * ingredientes = construtor_array_ingrediente();
    get_tsv_ingrediente(ingredientes,"ingrediente.tsv");
    add_ingrediente(ingredientes, 0, "jao", 30, 30);
    add_ingrediente(ingredientes, 1, "bolo", 40, 40);
    add_ingrediente(ingredientes, 2, "cenora", 30, 30);
    int i = pesquisar_id_ingrediente(ingredientes, 2);
    printf("\n%i",i);
    organizar_array_qta(ingredientes);
    for(int j = 0; j < get_size_ingrediente(ingredientes); j++)
    {
        Ingrediente * in = get_ingrediente(ingredientes,j);
        printf("\n%i",in->qta);
    }
    organizar_array_asc(ingredientes);
    set_tsv_ingrediente(ingredientes,"ingrediente.tsv");
    destruir_array_ingrediente(ingredientes);

}