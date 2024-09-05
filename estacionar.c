#include "ruaFila.h"

#define MAX_CARROS 5

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

// TODO
void estacionarCarro(TipoFila *estacionamento) {
    /**
     *  Deve verificar se a fila BomJesusDosPassos (estacionamento) esta cheia
     *      Se estiver cheia deve ser enfileirado na fila MonsenhorJoaoPedro
     *      Caso nao estiver cheia deve imprimir/retornar que o carro foi estacionado
     */

    if (estacionamentoEstaCheio(estacionamento)) {
        // TODO EnfileiraEmMonsenhor();
    } else {
        
    }
}

int main() {
    
    return 0;
}