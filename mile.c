#include "Funcoes_gerais\Produtos_funcoes.h"

int main()
{

<<<<<<< HEAD
=======
    int op = 0;
>>>>>>> ingrid
    Array_produtos * array = construtor_array_produtos();
    get_tsv_produto(array,"produtos.tsv");

    int id = 1;
    Produto * prod = get_produto(array,array->size-1);
    if (prod) id = prod->id + 1;

    Array_ingrediente * ingred_array = construtor_array_ingrediente();
    get_tsv_ingrediente(ingred_array, "ingredientes.tsv");
    int op = 1;

<<<<<<< HEAD
    while(op != 0){

=======
    while(op == 0){
>>>>>>> ingrid
        op = menu_produtos();

        switch(op)
        {
        case 1:
            adicionar_produto(array,ingred_array, id++);
            break;
        
        case 2:
            deletar_produto(array);
            break;

        case 3:
            pesquisar_produto(array, ingred_array);
            break;
        
        case 4:
            visualizar_produtos(array);
            break;
        
        case 5:
            editar_produto(array, ingred_array, id);
            break;
        }
    }
    set_tsv_produtos(array,"produtos.tsv");
}