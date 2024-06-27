#include "Funcoes_gerais\Clientes_funcoes.h"

int main() {

    int id = 1;
    Array_cliente * array = construtor_array_cliente();
    get_tsv_cliente(array,"clientes.tsv");

    Cliente * cli = get_cliente(array,array->size-1);
    //id = (cli != NULL) ? cli->id: 1;
    if (cli != NULL) id = cli->id+1;

    int acabar = 0;

    while (acabar == 0)
    {

        int op = menu_clientes();

        switch (op)
        {
            case 1:
                add_cliente(array, id++);
                break;

            case 2:
                deletar_clientes(array);
                break;

            case 3:
                pesquisar_cliente(array);
                break;
                
            case 4:
                visualizar_clientes(array);
                break;
            
            case 5:
                acabar = 1;
                break;

        }

        set_tsv_cliente(array, "clientes.tsv");

    }
}
















// Array_cliente * newCliente = construtor_array_cliente();

    // get_tsv_cliente(newCliente,"clientes.tsv");
    // _add_cliente(newCliente, 1, "Ingrid", "1111111111", "333333333", "ingrid@email.com", "rua lalalalalalallalalalalalalalal");
    // _add_cliente(newCliente, 2, "Mi", "2222211111", "333355553333", "mi@email.com", "rua lalalayaysysyfudyfudsuglalalalalal");
    
    // int i = pesquisar_id_cliente(newCliente,1);
    // printf("\n%i",i);

    // ordem_alfabetica(newCliente, 0, newCliente->size-1);

    // for(int j = 0; j < newCliente->size-1; j++)
    // {
    //     Cliente * in = get_cliente(newCliente, j);
    //     printf("\n%s",in->nome);
    // }

    // ordem_alfabetica(newCliente, 0, newCliente->size-1);
    // set_tsv_cliente(newCliente,"clientes.tsv");
    // destruir_array_cliente(newCliente);