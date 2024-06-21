#include <stdio.h>

int main(void) {
  
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

  int opcao = 0;
  char voltar;

  int itensSexoNaoInformado = 0;

  int valoresAbaixo = 0;
  int valoresAcima = 0;
  float valorCompraExaminar = 0;
  float mediaCompras = 0;

  int codigoMaisVendidos = 0;
  int numeroDeVendas = 0;

  printf("BEM VINDO A PARMÊ PIZZARIA!!!\n\n");

  // CADASTRANDO OS PEDIDOS DA PIZZARIA

  for (int i = 0; i < 5; i++) {

    while (codigosDoPedido[i] < 1 || codigosDoPedido[i] > 10) {
      printf("\nDIGITE UM CÓDIGO ENTRE 01 E 10: ");
      scanf("%d", &codigosDoPedido[i]);

      if (codigosDoPedido[i] < 1 || codigosDoPedido[i] > 10) {
        printf("Erro: Código Inválido!!!! ");
      }
    }

    printf("ITENS QUE FORAM VENDIDOS: ");
    scanf("%d", &qtdDeItensPedido[i]);

    while (qtdDeItensPedido[i] < 0) {
      printf("Quantidade Inválida, Informar um valor Válido: ");
      scanf("%d", &qtdDeItensPedido[i]);
    }

    do {
      printf("VALOR DO PEDIDO: R$ ");
      scanf("%f", &valorPedidosPizza[i]);
      if (valorPedidosPizza[i] < 0) {
        printf("Pedido de valor inválido, Favor Informar um valor Válido: ");
      }
    } while (valorPedidosPizza[i] < 0);

    valorPedidosTotal += valorPedidosPizza[i];

    while (sexoClientes[i] != 'F' && sexoClientes[i] != 'M' &&
           sexoClientes[i] != 'N') {
      printf("SEXO (F, M ou N Caso não queira informar): ");
      scanf(" %c", &sexoClientes[i]);

      if (sexoClientes[i] == 'F') {
        clientesMulheres++;
      } else if (sexoClientes[i] == 'M') {
        clientesHomens++;
        somaCompraHomens = somaCompraHomens + valorPedidosPizza[i];
      } else if (sexoClientes[i] == 'N') {
        clientesNaoInformaramSexo++;
        qtdDeItensPedidoNaoInformaramSexo =
            qtdDeItensPedidoNaoInformaramSexo + qtdDeItensPedido[i];
      }
    }

    printf("\nPARABÉNS! CADASTRO FINALIZADO\n\n");
  }

  do {

    // CODIGO PARA O MENU PRINCIPAL

    printf("MENU PRINCIPAL\n");
    printf("Qual opção você deseja?\n");
    printf("1 - Informações específicas de um código\n");
    printf("2 - Informações de todos os pedidos cadastrados\n");
    printf("3 - Finalizar o programa\n");
    printf("R: ");
    scanf("%d", &opcao);

    switch (opcao) {
    case 1:

      // SE DIGITAR A OPCAO 01 É PRA PERGUNTAR QUAL CODIGO EU QUERO PROCURAR

      printf("DIGITE O CÓDIGO: ");
      int codigoDigitado;
      scanf("%d", &codigoDigitado);

      int codigoVerificado = 0;

      for (int i = 0; i < 10; i++) {
        if (codigoDigitado == codigosDoPedido[i]) {
          printf("Valor Gasto pelo código %d: R$ %.2f\n", codigosDoPedido[i],
                 valorPedidosPizza[i]);
          printf("Este cliente é do sexo: %c\n", sexoClientes[i]);

          codigoVerificado = 1;
        }
      }

      if (!codigoVerificado) {

        printf("CÓDIGO %d NÃO FOI ENCONTRADO!\n", codigoDigitado);
      }

      break;

    case 2:
      // SE DIGITAR A OPCAO 02 É PRA INFORMAR TUDO SOBRE AQUELE PEDIDO

      // COLOQUEI ESSES VALORES AQUI, PQ TODAS VEZ QUE EU PEDIA PRA VOLTAR NO
      // MENU, ELE TAVA SOMANDO.

      valoresAbaixo = 0;
      valoresAcima = 0;
      itensSexoNaoInformado = 0;

      printf("Digite um valor de pedido: ");
      scanf("%f", &valorCompraExaminar);

      for (int i = 0; i < 5; i++) {
        if (40 > valorPedidosPizza[i]) {
          valoresAbaixo++;
        }
        if (valorCompraExaminar < valorPedidosPizza[i]) {
          valoresAcima++;
        }
      }

      printf("EXISTEM %d valores abaixo de R$40 reais\n", valoresAbaixo);

      printf("EXISTEM %d valores acima de R$%.2f\n", valoresAcima,
             valorCompraExaminar);

      printf("EXISTEM %d pedidos feitos por mulheres!\n", clientesMulheres);

      printf("EXISTEM %d clientes que não informaram o sexo.\n",
             clientesNaoInformaramSexo);

      printf("VALOR TOTAL DE PEDIDOS: R$ %.2f\n", valorPedidosTotal);

      printf(" VALOR TOTAL COMPRADO POR HOMENS R$%.2f \n", somaCompraHomens);
      printf(" QUANTIDADE TOTAL DE PEDIDOS %d\n", qtdTotalProdutosVendidos);

      mediaCompras = valorPedidosTotal / 5;

      printf("VALOR MÉDIO DE PEDIDOS: R$ %.2f\n", mediaCompras);

      for (int i = 0; i < 5; i++) {
        if (sexoClientes[i] == 'n' || sexoClientes[i] == 'N') {
          itensSexoNaoInformado += qtdDeItensPedido[i];
        }
      }

      printf("Qtde itens por pessoas que não informaram o sexo: %d\n",
             itensSexoNaoInformado);

      for (int i = 0; i < 5; i++) {
        if (qtdDeItensPedido[i] > numeroDeVendas) {
          codigoMaisVendidos = codigosDoPedido[i];
          numeroDeVendas = qtdDeItensPedido[i];
        }
        qtdTotalProdutosVendidos =
            qtdTotalProdutosVendidos + qtdDeItensPedido[i];
      }

      printf("Código mais vendido: CÓDIGO %d (ITENS VENDIDOS: %d)\n",
             codigoMaisVendidos, numeroDeVendas);

      break;

    case 3:
      // SE DIGITAR A OPCAO 03 É PARA SAIR DO PROGRAMA
      voltar = 'n';
      break;

    default:
      printf("OPÇÃO INVÁLIDA!\n");
      while (opcao < 1 && opcao > 3) {
        printf("Digite uma opção válida: ");
        scanf("%d", &opcao);
      }
      break;
    }

    if (voltar != 'n') {
      printf("Deseja retornar ao menu? (s ou n): \n ");
      scanf(" %c", &voltar);
    }

  } while (voltar == 's');

  printf("Programa finalizado!");
  return 0;
}