#include <stdio.h>
#include <string.h>
#include "bd_partida.h"

void inicializarBDPartidas(BDPartidas *bd) {
    bd->quantidade = 0;
}

int adicionarPartida(BDPartidas *bd, Partida partida) {
    if (bd->quantidade >= MAX_PARTIDAS) {
        return 0;
    }

    bd->partidas[bd->quantidade] = partida;
    bd->quantidade++;

    return 1;
}

Partida* buscarPartidaPorId(BDPartidas *bd, int id) {
    for (int i = 0; i < bd->quantidade; i++) {
        if (bd->partidas[i].id == id) {
            return &bd->partidas[i];
        }
    }

    return NULL;
}

int carregarPartidasCSV(BDPartidas *bd, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de partidas: %s\n", nomeArquivo);
        return 0;
    }

    inicializarBDPartidas(bd);

    char linha[100];

    /* Ignora a primeira linha (cabecalho) */
    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        fclose(arquivo);
        return 0;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        /* strcspn localiza e remove quebras de linha (\r\n) do final */
        linha[strcspn(linha, "\r\n")] = '\0';

        int id;
        int time1;
        int time2;
        int golsTime1;
        int golsTime2;

        if (sscanf(linha, "%d,%d,%d,%d,%d",
                   &id,
                   &time1,
                   &time2,
                   &golsTime1,
                   &golsTime2) == 5) {
            Partida partida;

            inicializarPartida(
                &partida,
                id,
                time1,
                time2,
                golsTime1,
                golsTime2
            );

            if (!adicionarPartida(bd, partida)) {
                printf("Limite maximo de partidas atingido.\n");
                break;
            }
        }
    }

    fclose(arquivo);

    return 1;
}

void imprimirTodasPartidas(BDPartidas *bd) {
    printf("ID Time1 Time2 Placar\n");

    for (int i = 0; i < bd->quantidade; i++) {
        imprimirPartida(bd->partidas[i]);
    }
}