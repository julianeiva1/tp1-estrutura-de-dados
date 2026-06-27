#include <stdio.h>
#include <string.h>
#include "bd_time.h"
#include "bd_partida.h"
#include "menu.h"

/*
 * Sistema de Gerenciamento de Campeonato de Futebol - Parte II
 * Carrega dados de times e partidas, calcula classificacao,
 * oferece menu interativo e persiste os dados em CSV.
 */
int main(void)
{
    BDTimes *bd_times = criarBDTimes();
    BDPartidas *bd_partidas = criarBDPartidas();

    if (bd_times == NULL || bd_partidas == NULL) {
        printf(COR_VERMELHA "Erro ao alocar memoria!\n" COR_RESET);
        if (bd_times != NULL) liberarBDTimes(bd_times);
        if (bd_partidas != NULL) liberarBDPartidas(bd_partidas);
        return 1;
    }

    if (!carregarTimesCSV(bd_times, "data/times.csv")) {
        printf(COR_VERMELHA "Erro ao carregar times!\n" COR_RESET);
        liberarBDPartidas(bd_partidas);
        liberarBDTimes(bd_times);
        return 1;
    }

    if (!carregarPartidasCSV(bd_partidas, "data/bd_partidas.csv")) {
        printf(COR_VERMELHA "Erro ao carregar partidas!\n" COR_RESET);
        liberarBDPartidas(bd_partidas);
        liberarBDTimes(bd_times);
        return 1;
    }

    calcularClassificacao(bd_times, bd_partidas);

    char opcao[10];
    int sair = 0;

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
        scanf("%9s", opcao);

        if (strlen(opcao) != 1) {
            printf(COR_VERMELHA "Opcao invalida!\n" COR_RESET);
            continue;
        }

        switch (opcao[0]) {
            case '1':
                consultarTime(bd_times);
                break;

            case '2':
                consultarPartidas(bd_times, bd_partidas);
                break;

            case '3':
                atualizarPartida(bd_times, bd_partidas);
                break;

            case '4':
                removerPartida(bd_times, bd_partidas);
                break;

            case '5':
                inserirPartida(bd_times, bd_partidas);
                break;

            case '6':
                imprimirClassificacao(bd_times, bd_partidas);
                break;

            case 'Q':
            case 'q':
                printf(COR_VERDE "Saindo do sistema...\n" COR_RESET);
                sair = 1;
                break;

            default:
                printf(COR_VERMELHA "Opcao invalida!\n" COR_RESET);
        }

    } while (!sair);

    liberarBDPartidas(bd_partidas);
    liberarBDTimes(bd_times);

    return 0;
}