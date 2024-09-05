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
#define MAX_CARROS 5  // Numero maximo de carros no estacionamento
#define NUMERO_RUAS 2 // Numero de ruas sendo monitoradas

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

void exibirRuas(TipoFila ruas[]) {
    int i;
    for (i = 0; i < NUMERO_RUAS; i++) {
        if (ruas[i].frente->prox == NULL) {
            printf("A rua %d está vazia\n", i+1);
            continue;
        }
        
        exibe(ruas[i]);
    }
}

int main() {

    TipoFila BomJesusDosPassos; // Estacionamento
    FFVazia(&BomJesusDosPassos);

    TipoFila MonsenhorJoaoPedro; // Entrada/Fila de espera
    FFVazia(&MonsenhorJoaoPedro);

    TipoFila ruas[NUMERO_RUAS];
    ruas[0] = BomJesusDosPassos;
    ruas[1] = MonsenhorJoaoPedro;

    TipoCarro carro;

    // TipoFila JaimeGoncalves; Eh necessaria?
    // FFVazia(&JaimeGoncalves);
    int opcao = 0;

    do {
        printf("1. Estacionar carro\n");
        printf("2. Retirar carro\n");
        printf("3. Exibir ruas\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer deixado pelo scanf

        switch (opcao) {
        case 1:
            printf("Digite a placa do carro: ");
            fgets(carro.placa, 10, stdin);
            // Remove o newline do final da string, se presente
            carro.placa[strcspn(carro.placa, "\n")] = '\0';

            printf("O carro tem alguma prioridade, [S]/[N]: ");
            char resposta[2];
            fgets(resposta, 2, stdin);
            if (strcmp("S", resposta) == 0) {
                carro.prioridade = 1;
            } else {
                carro.prioridade = 0;
            }

            carro.deslocamento = 0;

            estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);

            printf("%s %d\n", carro.placa, carro.prioridade);

            getchar();
            break;
        case 2:
            printf("Digite a placa do carro: ");
            char placa[10];
            fgets(placa, 10, stdin);

            break;
        case 3:
            exibirRuas(ruas);
            break;
        default:
            if (opcao != 0) {
                printf("Voce digitou uma opcao invalida. Por favor, digite outro valor.\n");
            }
            break;
        }

        printf("\nPressione Enter para continuar...");
        getchar();
        system("cls");
        system("clear");
    } while (opcao != 0);

    return 0;
}
