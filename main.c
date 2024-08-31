// Nome de funcoes e variaveis eh passivel a mudanca

/*
typedef struct {
    char placa[10];
    int deslocamento;
    int prioridade;
} TipoCarro;
*/

#include "ruaFila.h"
#define MAX = 5 // Numero maximo de carros no estacionamento

// Funcoes para gerenciamento do estacionamento
// TODO
void retirarCarro() { // Void ou Int

    /**
     * - Deve utilizar a fila ruaAuxiliar para quando o carro nao eh o primeiro da fila
     *   e garantir que as filas estao na mesma ordem com a retirada do carro;
     * 
     * - Deve retornar/exibir o número de vezes que o carro foi deslocado
     *   dentro da fila BomJesusDosPassos, incluindo a partida, mas nao a chegada;
     * 
     * - Deve estacionar os carros que estao na fila de espera com maior prioriade,
     *   se nao tiver um com maior prioridade o mais a frente deve estacionar;
    */
}

// TODO
void estacionarCarro() {
    /** 
     *  Deve verificar se a fila BomJesusDosPassos esta cheia
     *      Se estiver cheia deve ser enfileirado na fila MonsenhorJoaoPedro
     *      Caso nao estiver cheia deve imprimir/retornar que o carro foi estacionado
     */
}


int main() {

    TipoFila BomJesusDosPassos; // Estacionamento
    FFVazia(&BomJesusDosPassos);

    TipoFila MonsenhorJoaoPedro; // Entrada/Fila de espera
    FFVazia(&MonsenhorJoaoPedro);

    // TipoFila JaimeGoncalves; Eh necessaria?
    // FFVazia(&JaimeGoncalves);

    TipoFila ruaAuxiliar; // Usada para auxiliar a retirada de carros
    FFVazia(&ruaAuxiliar);// Talvez seja usada apenas dentro de funções como uma variavel auxiliar

    /*
     Menu:
        RetirarCarro()
        EstacionarCarro() deve imprimir/retornar que o carro foi estacionado
    */
    return 0;
}
