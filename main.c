#include <stdio.h>
#include "bd_time.h"
#include "bd_partida.h"
#include "menu.h"

/*
 * Sistema de Gerenciamento de Campeonato de Futebol - Parte I
 * Carrega dados de times e partidas, calcula classificacao,
 * e oferece menu interativo para consultas.
 */
int main()
{
    BDTimes bd_times;
    BDPartidas bd_partidas;

    if (!carregarTimesCSV(&bd_times, "times.csv")) {
        printf("Erro ao carregar times!\n");
        return 1;
    }

    /*
     * Arquivo padrao: bd_partidas.csv (90 partidas)
     * Arquivos alternativos para teste:
     * - "partidas_vazio.csv" (sem partidas)
     * - "partidas_parcial.csv" (45 partidas)
     * - "partidas_completo.csv" (90 partidas)
     */
    if (!carregarPartidasCSV(&bd_partidas, "bd_partidas.csv")) {
        printf("Erro ao carregar partidas!\n");
        return 1;
    }

    calcularClassificacao(&bd_times, &bd_partidas);

    char opcao;

    do {
        printf("\nSistema de Gerenciamento de Partidas\n");
        printf("1 - Consultar time\n");
        printf("2 - Consultar partidas\n");
        printf("3 - Atualizar partida\n");
        printf("4 - Remover partida\n");
        printf("5 - Inserir partida\n");
        printf("6 - Imprimir tabela de classificacao\n");
        printf("Q - Sair\n");

        printf("\nEscolha uma opcao: ");
        scanf(" %c", &opcao);

        switch (opcao) {
            case '1':
                consultarTime(&bd_times);
                break;

            case '2':
                consultarPartidas(&bd_times, &bd_partidas);
                break;

            case '3':
                atualizarPartida();
                break;

            case '4':
                removerPartida();
                break;

            case '5':
                inserirPartida();
                break;

            case '6':
                imprimirClassificacao(&bd_times);
                break;

            case 'Q':
            case 'q':
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 'Q' && opcao != 'q');

    return 0;
}