#include <gtk/gtk.h>
#include <stdio.h>

// Variáveis globais para armazenar os dados
int codigosDoPedido[10];
float valorPedidosPizza[5];
int qtdDeItensPedido[10];
int qtdDeItensPedidoNaoInformaramSexo = 0;
int qtdTotalProdutosVendidos = 0;

char sexoClientes[5];
int clientesMulheres = 0;
int clientesHomens = 0;
int clientesNaoInformaramSexo = 0;

float somaCompraMulheres = 0;
float somaCompraHomens = 0;
float valorPedidosTotal = 0;

int itensSexoNaoInformado = 0;

int valoresAbaixo = 0;
int valoresAcima = 0;
float valorCompraExaminar = 0;
float mediaCompras = 0;

int codigoMaisVendidos = 0;
int numeroDeVendas = 0;

// Função para cadastrar pedidos
void cadastrar_pedido(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *grid;
    GtkWidget *entry_codigo;
    GtkWidget *entry_itens;
    GtkWidget *entry_valor;
    GtkWidget *entry_sexo;

    dialog = gtk_dialog_new_with_buttons("Cadastrar Pedido", GTK_WINDOW(data),
                                       GTK_DIALOG_MODAL,
                                       "Cadastrar", GTK_RESPONSE_ACCEPT,
                                       "Cancelar", GTK_RESPONSE_REJECT,
                                       NULL);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    grid = gtk_grid_new();
    gtk_container_add(GTK_CONTAINER(content_area), grid);

    entry_codigo = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Código (1-10):"), 0, 0, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_codigo, 1, 0, 1, 1);

    entry_itens = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Itens Vendidos:"), 0, 1, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_itens, 1, 1, 1, 1);

    entry_valor = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Valor do Pedido:"), 0, 2, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_valor, 1, 2, 1, 1);

    entry_sexo = gtk_entry_new();
    gtk_grid_attach(GTK_GRID(grid), gtk_label_new("Sexo (F/M/N):"), 0, 3, 1, 1);
    gtk_grid_attach(GTK_GRID(grid), entry_sexo, 1, 3, 1, 1);

    gtk_widget_show_all(dialog);

    if (gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_ACCEPT) {
        int codigo = atoi(gtk_entry_get_text(GTK_ENTRY(entry_codigo)));
        int itens = atoi(gtk_entry_get_text(GTK_ENTRY(entry_itens)));
        float valor = atof(gtk_entry_get_text(GTK_ENTRY(entry_valor)));
        char sexo = gtk_entry_get_text(GTK_ENTRY(entry_sexo))[0];

        if (codigo >= 1 && codigo <= 10 && itens >= 0 && valor >= 0 &&
            (sexo == 'F' || sexo == 'M' || sexo == 'N')) {
            codigosDoPedido[clientesMulheres + clientesHomens + clientesNaoInformaramSexo] = codigo;
            qtdDeItensPedido[clientesMulheres + clientesHomens + clientesNaoInformaramSexo] = itens;
            valorPedidosPizza[clientesMulheres + clientesHomens + clientesNaoInformaramSexo] = valor;
            sexoClientes[clientesMulheres + clientesHomens + clientesNaoInformaramSexo] = sexo;

            valorPedidosTotal += valor;

            if (sexo == 'F') {
                clientesMulheres++;
            } else if (sexo == 'M') {
                clientesHomens++;
                somaCompraHomens += valor;
            } else if (sexo == 'N') {
                clientesNaoInformaramSexo++;
                qtdDeItensPedidoNaoInformaramSexo += itens;
            }

            printf("Pedido cadastrado com sucesso!\n");
        } else {
            printf("Erro: Dados inválidos!\n");
        }
    }

    gtk_widget_destroy(dialog);
}

// Função para exibir informações
void exibir_informacoes(GtkWidget *widget, gpointer data) {
    GtkWidget *dialog;
    GtkWidget *content_area;
    GtkWidget *label;

    dialog = gtk_dialog_new_with_buttons("Informações", GTK_WINDOW(data),
                                       GTK_DIALOG_MODAL,
                                       "Fechar", GTK_RESPONSE_CLOSE,
                                       NULL);

    content_area = gtk_dialog_get_content_area(GTK_DIALOG(dialog));
    char buffer[512];

    snprintf(buffer, sizeof(buffer),
             "Pedidos feitos por mulheres: %d\n"
             "Pedidos feitos por homens: %d\n"
             "Pedidos sem sexo informado: %d\n"
             "Valor total de pedidos: R$ %.2f\n"
             "Valor médio de pedidos: R$ %.2f\n",
             clientesMulheres, clientesHomens, clientesNaoInformaramSexo,
             valorPedidosTotal, valorPedidosTotal / (clientesMulheres + clientesHomens + clientesNaoInformaramSexo));

    label = gtk_label_new(buffer);
    gtk_container_add(GTK_CONTAINER(content_area), label);
    gtk_widget_show_all(dialog);

    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *button_cadastrar;
    GtkWidget *button_informacoes;
    GtkWidget *box;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Pizzaria");
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 200);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(window), box);

    button_cadastrar = gtk_button_new_with_label("Cadastrar Pedido");
    g_signal_connect(button_cadastrar, "clicked", G_CALLBACK(cadastrar_pedido), window);
    gtk_box_pack_start(GTK_BOX(box), button_cadastrar, TRUE, TRUE, 0);

    button_informacoes = gtk_button_new_with_label("Exibir Informações");
    g_signal_connect(button_informacoes, "clicked", G_CALLBACK(exibir_informacoes), window);
    gtk_box_pack_start(GTK_BOX(box), button_informacoes, TRUE, TRUE, 0);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}