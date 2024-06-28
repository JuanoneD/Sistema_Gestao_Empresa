#include "Funcoes_gerais\Ingredientes_funcoes.h"

int main() {

    int id = 1;
    Array_ingrediente * array = construtor_array_ingrediente();
    get_tsv_ingrediente(array,"ingredientes.tsv");

    Ingrediente * ing = get_ingrediente(array,array->size-1);
    //id = (ing != NULL) ? ing->id: 1;
    if (ing != NULL) id = ing->id+1;

    int acabar = 0;

    while (acabar == 0)
    {
        int op = menu_ingredientes();

        switch (op)
        {
            case 1:
                add_ingrediente(array, id++);
                break;

            case 2:
                deletar_ingrediente(array);
                break;

            case 3:
                pesquisar_ingrediente(array);
                break;
                
            case 4:
                editar_ingrediente(array, id++);
                break;
            
            case 5:
                visualizar_ingredientes(array);
                break;

            case 6:
                acabar = 1;
                break;

        }

        set_tsv_ingrediente(array, "ingredientes.tsv");

    }
}
















// Array_ingrediente * newingrediente = construtor_array_ingrediente();

    // get_tsv_ingrediente(newingrediente,"ingredientes.tsv");
    // _add_ingrediente(newingrediente, 1, "Ingrid", "1111111111", "333333333", "ingrid@email.com", "rua lalalalalalallalalalalalalalal");
    // _add_ingrediente(newingrediente, 2, "Mi", "2222211111", "333355553333", "mi@email.com", "rua lalalayaysysyfudyfudsuglalalalalal");
    
    // int i = pesquisar_id_ingrediente(newingrediente,1);
    // printf("\n%i",i);

    // ordem_alfabetica(newingrediente, 0, newingrediente->size-1);

    // for(int j = 0; j < newingrediente->size-1; j++)
    // {
    //     ingrediente * in = get_ingrediente(newingrediente, j);
    //     printf("\n%s",in->nome);
    // }

    // ordem_alfabetica(newingrediente, 0, newingrediente->size-1);
    // set_tsv_ingrediente(newingrediente,"ingredientes.tsv");
    // destruir_array_ingrediente(newingrediente);