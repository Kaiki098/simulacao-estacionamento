// Nome de funcoes e variaveis eh passivel a mudanca

/*
typedef struct {
    char placa[10];
    int deslocamento;
    int prioridade;
} TipoCarro;
*/

#include "ruaFila.h"
#include <string.h>
// Depois de fazer todas as funcoes, separar as funcoes em outro arquivo
#define MAX_CARROS 5 // Numero maximo de carros no estacionamento

// Funcoes para gerenciamento do estacionamento
// funcoes para retirado de carros
void retirarCarro(TipoFila *estacionamento, TipoCarro carro) { // Void ou Int

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


// Funcoes para estacionar carro
int estacionamentoEstaCheio(TipoFila *estacionamento) {
    /**
     * Pode ser substituido por um campo tamanho na struct TipoFila
     * Talvez seja melhor
     */

    TipoApontador apontadorCarro = estacionamento->frente->prox;
    int numeroDeCarros = 0;

    while (apontadorCarro != NULL) {
        numeroDeCarros++;
        apontadorCarro = apontadorCarro->prox;
    }
    return numeroDeCarros == MAX_CARROS;
}

void estacionarCarro(TipoCarro carro, TipoFila *estacionamento, TipoFila *ruaMonsenhor) {
    /**
     *  Deve verificar se a fila BomJesusDosPassos (estacionamento) esta cheia
     *      Se estiver cheia deve ser enfileirado na fila MonsenhorJoaoPedro
     *      Caso nao estiver cheia deve imprimir/retornar que o carro foi estacionado
     */

    if (estacionamentoEstaCheio(estacionamento)) {
        Enfileira(carro, ruaMonsenhor);
    } else {
        Enfileira(carro, estacionamento);
    }
}

int main() {

    TipoFila BomJesusDosPassos; // Estacionamento
    FFVazia(&BomJesusDosPassos);

    TipoFila MonsenhorJoaoPedro; // Entrada/Fila de espera
    FFVazia(&MonsenhorJoaoPedro);

    TipoCarro carro;
    carro.deslocamento = 0;
    strcpy(carro.placa, "ADSCFEV");
    carro.prioridade = 1;

    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);
    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);
    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);
    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);
    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);
    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);

    printf("Estacionamento: \n");
    exibe(BomJesusDosPassos);
    printf("Espera: \n");
    exibe(MonsenhorJoaoPedro);
    // TipoFila JaimeGoncalves; Eh necessaria?
    // FFVazia(&JaimeGoncalves);

    /*
     Menu:
        RetirarCarro()
        EstacionarCarro() deve imprimir/retornar que o carro foi estacionado
    */
    return 0;
}
