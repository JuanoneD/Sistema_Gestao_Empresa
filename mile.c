#include "Funcoes_gerais\Produtos_funcoes.h"

int main()
{

    int op = 1;
    Array_produtos * array = construtor_array_produtos();
    get_tsv_produto(array,"produtos.tsv");

    int id = 1;
    Produto * prod = get_produto(array,array->size-1);
    if (prod) id = prod->id + 1;

    while(op != 0){
        op = menu_produtos();

        switch(op)
        {
        case 1:
            adicionar_produto(array, id++);
            break;
        
        case 2:
            deletar_produto(array);
            break;

        case 3:
            pesquisar_produto(array);
            break;
        
        case 4:
            visualizar_produtos(array);
            break;
        
        case 5:
            editar_produto(array, id);
            break;
        }


    }
    set_tsv_produtos(array,"produtos.tsv");
}