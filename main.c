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
        printf("Carro de placa %s esta aguardando na rua Monsenhor Joao Pedro.\n", carro.placa);
        return;
    }

    Enfileira(carro, estacionamento);
    printf("Carro de placa %s foi estacionado.\n", carro.placa);
}

// Funcoes para gerenciamento do estacionamento
// funcoes para retirado de carros
void retirarCarro(TipoFila *ruaMonsenhor, TipoFila *estacionamento, TipoCarro carro) { // Void ou Int

    // Foi adicionado o parametro 'ruaMonsenhor' que atuará como uma "Fila de Espera"

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

    // A variavel filaAuxiliar ira atuar como uma fila temporaria para armazenar os carros posteriores ao que sera removido
    TipoFila filaAuxiliar;
    FFVazia(&filaAuxiliar);

    // Variaveis de apoio referente ao carro e o flag de encontre
    TipoCarro carroAtual;
    int carroEncontrado = 0;

    // Percorrer a fila do estacionamento até esvaziar em busca do carro
    while (!Vazia(*estacionamento)) {
        // Começa desenfileirando, devido a simulacao, e armazenando o mesmo no campo temporario
        Desenfileira(estacionamento, &carroAtual);

        // Verificacao de placa
        if (strcmp(carroAtual.placa, carro.placa) == 0) {
            // Se encontrou o carro a ser retirado...
            carroEncontrado = 1; // Sinaliza sinal 1
            printf("\nCarro de placa: %s removido. Deslocamentos: %d\n", carroAtual.placa, carroAtual.deslocamento);
            continue;
        }
        // Se não, irá movendo os demais para a rua auxiliar ate encontra-lo
        carroAtual.deslocamento++;            // Incrementar deslocamento simbolizando a rua
        Enfileira(carroAtual, &filaAuxiliar); // Enfileirando na filaAuxiliar
    }

    // Retornando os carros da 'ruaAuxiliar' para o estacionamento
    while (!Vazia(filaAuxiliar)) {
        Desenfileira(&filaAuxiliar, &carroAtual);
        Enfileira(carroAtual, estacionamento);
    }

    // Verificação de flag 0, Se Nao achou...
    if (!carroEncontrado) {
        printf("\nCarro de placa: %s não encontrado no estacionamento...\n", carro.placa);
        return;
    }

    //
    while (!Vazia(*ruaMonsenhor)) {
        Desenfileira(ruaMonsenhor, &carroAtual);
        if (!estacionamentoEstaCheio(estacionamento) && carroAtual.prioridade == 1) {
            Enfileira(carroAtual, estacionamento);
            printf("Carro de placa %s foi estacionado.\n", carroAtual.placa);
            continue;
        }
        Enfileira(carroAtual, &filaAuxiliar);
    }
    while (!Vazia(filaAuxiliar)) {
        Desenfileira(&filaAuxiliar, &carroAtual);
        Enfileira(carroAtual, ruaMonsenhor);
    }

    while (!Vazia(*ruaMonsenhor) && !estacionamentoEstaCheio(estacionamento)) {
        Desenfileira(ruaMonsenhor, &carroAtual);
        Enfileira(carroAtual, estacionamento);
        printf("Carro de placa %s foi estacionado.\n", carroAtual.placa);
    }
}

void exibirRuas(TipoFila BomJesusDosPassos, TipoFila MonsenhorJoaoPedro) {
    printf("\nEstacionamento: \n");
    Vazia(BomJesusDosPassos) ? printf("\nNao ha carros no estacionamento.") : exibe(BomJesusDosPassos);

    printf("\n\nRua Monsenhor Joao Pedro: \n");
    Vazia(MonsenhorJoaoPedro) ? printf("\nNao ha carros na rua Monsenhor Joao Pedro.") : exibe(MonsenhorJoaoPedro);
}

int main() {

    TipoFila BomJesusDosPassos; // Estacionamento
    FFVazia(&BomJesusDosPassos);

    TipoFila MonsenhorJoaoPedro; // Entrada/Fila de espera
    FFVazia(&MonsenhorJoaoPedro);

    TipoCarro carro;

    carro.deslocamento = 0;
    carro.prioridade = 0;
    strcpy(carro.placa, "1");
    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);
    strcpy(carro.placa, "2");
    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);
    strcpy(carro.placa, "3");
    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);
    strcpy(carro.placa, "4");
    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);
    strcpy(carro.placa, "5");
    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);
    carro.prioridade = 1;
    strcpy(carro.placa, "6");
    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);
    carro.prioridade = 0;
    strcpy(carro.placa, "7");
    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);
    carro.prioridade = 1;
    strcpy(carro.placa, "8");
    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);
    carro.prioridade = 0;
    strcpy(carro.placa, "9");
    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);
    carro.prioridade = 1;
    strcpy(carro.placa, "10");
    estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);

    // TipoFila JaimeGoncalves; Eh necessaria?
    // FFVazia(&JaimeGoncalves);
    int opcao = 0;

    do {
        printf("\nSISTEMA DE ESTACIONAMENTO\n");
        printf("\n 1. Estacionar carro\n");
        printf(" 2. Retirar carro\n");
        printf(" 3. Exibir ruas\n");
        printf(" 0. Sair\n\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer deixado pelo scanf

        switch (opcao) {
        case 1:
            printf("\nDigite a placa do carro: ");
            fgets(carro.placa, 10, stdin);
            // Remove o newline do final da string, se presente
            carro.placa[strcspn(carro.placa, "\n")] = '\0';

            printf("\nO carro tem alguma prioridade, [S]/[N]: ");
            char resposta[2];
            fgets(resposta, 2, stdin);

            if (strcmp("S", resposta) == 0 || strcmp("s", resposta) == 0) {
                carro.prioridade = 1;
            } else {
                carro.prioridade = 0;
            }

            carro.deslocamento = 0;

            estacionarCarro(carro, &BomJesusDosPassos, &MonsenhorJoaoPedro);
            getchar();
            break;
        case 2:
            printf("\nDigite a placa do carro: ");
            char placa[10];
            fgets(placa, 10, stdin);
            // Remove o newline do final da string, se presente
            placa[strcspn(placa, "\n")] = '\0';

            // TipoCarro temporário para remocao
            TipoCarro carroBusca;
            // Atribuindo a placa obtida anteriormente ao carroBusca
            strcpy(carroBusca.placa, placa);

            // Chamando a funcao
            retirarCarro(&MonsenhorJoaoPedro, &BomJesusDosPassos, carroBusca);

            break;
        case 3:
            exibirRuas(BomJesusDosPassos, MonsenhorJoaoPedro);
            break;
        default:
            if (opcao != 0) {
                printf("\nVoce digitou uma opcao invalida. Por favor, digite outro valor.\n");
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
