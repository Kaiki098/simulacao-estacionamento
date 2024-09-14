#include "ruaFila.h"
#include <gtk/gtk.h>
#include <string.h>
#define MAX_CARROS 5 // Numero maximo de carros no estacionamento

/* Funcoes para gerenciamento do estacionamento */

// Funcao que verifica se o estacionamento possui mais de 5 carros (MAX_CARROS)
int estacionamentoEstaCheio(TipoFila *estacionamento) {
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
     *  Verifica se a fila BomJesusDosPassos (estacionamento) esta cheia
     *      Se estiver cheia enfileira na fila MonsenhorJoaoPedro
     *      Caso nao estiver cheia imprimir/retornar que o carro foi estacionado
     */

    if (estacionamentoEstaCheio(estacionamento)) {
        Enfileira(carro, ruaMonsenhor);
        printf("Carro de placa %s esta aguardando na rua Monsenhor Joao Pedro.\n", carro.placa);
        return;
    }

    Enfileira(carro, estacionamento);
    printf("Carro de placa %s foi estacionado.\n", carro.placa);
}

/* Funcoes para retirada de carros */

// Função para retirar o carro específico
int verificarCarro(TipoFila *estacionamento, TipoCarro carro, TipoFila *filaAuxiliar) {
    TipoCarro carroAtual;
    int carroEncontrado = 0;

    while (!Vazia(*estacionamento)) {
        Desenfileira(estacionamento, &carroAtual);
        if (strcmp(carroAtual.placa, carro.placa) == 0) {
            carroEncontrado = 1;
            printf("\nCarro de placa: %s removido. Deslocamentos: %d\n", carroAtual.placa, carroAtual.deslocamento + 1); // deslocamentos + 1, pois a sáida conta como deslocamento
            break;
        }
        carroAtual.deslocamento++;
        Enfileira(carroAtual, filaAuxiliar);
    }
    return carroEncontrado;
}

/* Função para restaurar a fila auxiliar de volta ao estacionamento */
void restaurarFilaAuxiliar(TipoFila *filaAuxiliar, TipoFila *estacionamento) {
    TipoCarro carroAtual;
    while (!Vazia(*filaAuxiliar)) {
        Desenfileira(filaAuxiliar, &carroAtual);
        Enfileira(carroAtual, estacionamento);
    }
}

// Função para estacionar carros da fila ruaMonsenhor no estacionamento
void estacionarCarrosDaRua(TipoFila *ruaMonsenhor, TipoFila *estacionamento, TipoFila *filaAuxiliar) {
    TipoCarro carroAtual;

    while (!Vazia(*ruaMonsenhor)) {
        Desenfileira(ruaMonsenhor, &carroAtual);
        if (!estacionamentoEstaCheio(estacionamento) && carroAtual.prioridade == 1) {
            Enfileira(carroAtual, estacionamento);
            printf("Carro de placa %s foi estacionado.\n", carroAtual.placa);
            continue;
        }
        Enfileira(carroAtual, filaAuxiliar);
    }
}

// Função principal para retirada de carro
void retirarCarro(TipoFila *ruaMonsenhor, TipoFila *estacionamento, TipoCarro carro) {
    TipoFila filaAuxiliar;
    FFVazia(&filaAuxiliar);

    // Verifica e remove o carro, e organiza os carros na filaAuxiliar
    int carroEncontrado = verificarCarro(estacionamento, carro, &filaAuxiliar);

    // Restaura os carros da fila auxiliar para o estacionamento
    restaurarFilaAuxiliar(&filaAuxiliar, estacionamento);

    if (!carroEncontrado) {
        printf("\nCarro de placa: %s não encontrado no estacionamento...\n", carro.placa);
        return;
    }

    // Estaciona carros com prioridade da ruaMonsenhor
    estacionarCarrosDaRua(ruaMonsenhor, estacionamento, &filaAuxiliar);

    // Finaliza estacionando carros restantes
    restaurarFilaAuxiliar(&filaAuxiliar, ruaMonsenhor);

    while (!Vazia(*ruaMonsenhor) && !estacionamentoEstaCheio(estacionamento)) {
        TipoCarro carroAtual;
        Desenfileira(ruaMonsenhor, &carroAtual);
        Enfileira(carroAtual, estacionamento);
        printf("Carro de placa %s foi estacionado.\n", carroAtual.placa);
    }
}

// Função para exibir as ruas
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
    GtkWidget *lb_log;
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
    gtk_label_set_text(GTK_LABEL(w->lb_log), "Opa");
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
    widgets->lb_log = GTK_WIDGET(gtk_builder_get_object(builder, "lb_log"));

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