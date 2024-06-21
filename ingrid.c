#include "Estruturas_Dados\Clientes_estruturas.h"

int main() {

    Array_cliente * newCliente = construtor_array_cliente();

    get_tsv_cliente(newCliente,"clientes.tsv");
    add_cliente(newCliente, 1, "Ingrid", "1111111111", "333333333", "ingrid@email.com", "rua lalalalalalallalalalalalalalal");
    add_cliente(newCliente, 2, "Mi", "2222211111", "333355553333", "mi@email.com", "rua lalalayaysysyfudyfudsuglalalalalal");
    
    int i = pesquisar_id_cliente(newCliente,1);
    printf("\n%i",i);

    ordem_alfabetica(newCliente, 0, newCliente->size-1);

    for(int j = 0; j < newCliente->size-1; j++)
    {
        Cliente * in = get_cliente(newCliente, j);
        printf("\n%s",in->nome);
    }

    ordem_alfabetica(newCliente, 0, newCliente->size-1);
    set_tsv_cliente(newCliente,"clientes.tsv");
    destruir_array_cliente(newCliente);
}