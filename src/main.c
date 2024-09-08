// Nome de funcoes e variaveis eh passivel a mudanca

/*
typedef struct {
    char placa[10];
    int deslocamento;
    int prioridade;
} TipoCarro;
*/

#include "ruaFila.h"
#include <gtk/gtk.h>
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

typedef struct {
    GtkWidget *window;
    GtkWidget *bt_estacionar;
    GtkWidget *bt_retirar;
    GtkWidget *et_placa;
    GtkWidget *ck_prioridade;
    GtkWidget *lb_estacionamento;
    GtkWidget *lb_rua_espera;
    TipoFila BomJesusDosPassos;
    TipoFila MonsenhorJoaoPedro;
} widgets_t;

void atualizaTela(widgets_t *w) {
    char textoEstacionamento[4096] = {0}; // Aumente o tamanho conforme necessário
    char textoRuaEspera[4096] = {0};      // Aumente o tamanho conforme necessário
    const char *placaTemplate = "Placa: ";
    const char *deslocamentoTemplate = "Deslocamento: ";
    const char *prioridadeTemplate = "Prioridade: ";

    TipoApontador aux = w->BomJesusDosPassos.frente->prox;
    // Iterar sobre a fila estacionamento
    while (aux != NULL) {
        char carroFormatado[256] = {0};
        strcat(carroFormatado, placaTemplate);
        strcat(carroFormatado, aux->carro.placa);
        strcat(carroFormatado, "\n");
        char deslocamento[20] = {0};
        snprintf(deslocamento, 20, "%d", aux->carro.deslocamento);
        strcat(carroFormatado, deslocamentoTemplate);
        strcat(carroFormatado, deslocamento);
        strcat(carroFormatado, "\n\n");

        strncat(textoEstacionamento, carroFormatado, sizeof(textoEstacionamento) - strlen(textoEstacionamento) - 1);
        aux = aux->prox;
    }

    // Atualizar o texto do label com o conteúdo do buffer
    gtk_label_set_text(GTK_LABEL(w->lb_estacionamento), textoEstacionamento);

    aux = w->MonsenhorJoaoPedro.frente->prox;
    while (aux != NULL) {
        char carroFormatado[256] = {0};
        strcat(carroFormatado, placaTemplate);
        strcat(carroFormatado, aux->carro.placa);
        strcat(carroFormatado, "\n");
        strcat(carroFormatado, prioridadeTemplate);

        if (aux->carro.prioridade) {
            const char *prioridade = " 1\n\n";
            strcat(carroFormatado, prioridade);
        } else {
            const char *prioridade = " 0\n\n";
            strcat(carroFormatado, prioridade);
        }
        strncat(textoRuaEspera, carroFormatado, sizeof(textoRuaEspera) - strlen(textoRuaEspera) - 1);

        aux = aux->prox;
    }

    // Atualizar o texto do label com o conteúdo do buffer
    gtk_label_set_text(GTK_LABEL(w->lb_rua_espera), textoRuaEspera);
}

int main(int argc, char *argv[]) {
    GtkBuilder *builder;

    widgets_t *widgets = g_slice_new(widgets_t);

    gtk_init(&argc, &argv);

    builder = gtk_builder_new();

    gtk_builder_add_from_file(builder, "glade/window.glade", NULL);

    widgets->window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    widgets->bt_estacionar = GTK_WIDGET(gtk_builder_get_object(builder, "bt_estacionar"));
    widgets->bt_retirar = GTK_WIDGET(gtk_builder_get_object(builder, "bt_retirar"));
    widgets->et_placa = GTK_WIDGET(gtk_builder_get_object(builder, "et_placa"));
    widgets->ck_prioridade = GTK_WIDGET(gtk_builder_get_object(builder, "ck_prioridade"));
    widgets->lb_estacionamento = GTK_WIDGET(gtk_builder_get_object(builder, "lb_estacionamento"));
    widgets->lb_rua_espera = GTK_WIDGET(gtk_builder_get_object(builder, "lb_rua_espera"));

    // Estacionamento
    FFVazia(&widgets->BomJesusDosPassos);
    // Entrada/Fila de espera
    FFVazia(&widgets->MonsenhorJoaoPedro);

    gtk_builder_connect_signals(builder, widgets);

    g_object_unref(builder);

    gtk_widget_show(widgets->window);

    gtk_main();

    g_slice_free(widgets_t, widgets);

    return 0;
}

void on_window_destroy(void) {
    gtk_main_quit();
}

void on_bt_estacionar_clicked(GtkButton *bt_estacionar, void *dados) {
    widgets_t *w = (widgets_t *)dados;
    const gchar *placa = gtk_entry_get_text(GTK_ENTRY(w->et_placa));
    int prioridade = 0;
    if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(w->ck_prioridade))) {
        prioridade = 1;
    }

    printf("\nPlaca: %s\n", placa);
    printf("Prioridade: %d\n", prioridade);

    TipoCarro carro;
    carro.deslocamento = 0;
    strcpy(carro.placa, placa);
    carro.prioridade = prioridade;
    estacionarCarro(carro, &w->BomJesusDosPassos, &w->MonsenhorJoaoPedro);
    atualizaTela(w);
}

void on_bt_retirar_clicked(GtkButton *bt_retirar, void *dados) {
    widgets_t *w = (widgets_t *)dados;
    const gchar *placa = gtk_entry_get_text(GTK_ENTRY(w->et_placa));
    TipoCarro carro;
    strcpy(carro.placa, placa);
    retirarCarro(&w->MonsenhorJoaoPedro, &w->BomJesusDosPassos, carro);
    atualizaTela(w);
}