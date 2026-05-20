#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bd_partida.h"

/*
 * Definicao opaca da struct BDPartidas (privada a este arquivo)
 * Armazena um array de ponteiros para Partidas alocadas dinamicamente
 */
struct bd_partidas {
    Partida *partidas[MAX_PARTIDAS];
    int quantidade;
};

/* === GERENCIAMENTO DE MEMORIA === */

BDPartidas *criarBDPartidas(void) {
    BDPartidas *bd = (BDPartidas *)malloc(sizeof(BDPartidas));
    if (bd == NULL) {
        return NULL;
    }
    
    bd->quantidade = 0;
    for (int i = 0; i < MAX_PARTIDAS; i++) {
        bd->partidas[i] = NULL;
    }
    
    return bd;
}

void liberarBDPartidas(BDPartidas *bd) {
    if (bd != NULL) {
        for (int i = 0; i < bd->quantidade; i++) {
            if (bd->partidas[i] != NULL) {
                liberarPartida(bd->partidas[i]);
            }
        }
        free(bd);
    }
}

/* === INTERFACE PUBLICA === */

int adicionarPartida(BDPartidas *bd, Partida *partida) {
    if (bd == NULL || partida == NULL) {
        return 0;
    }
    
    if (bd->quantidade >= MAX_PARTIDAS) {
        return 0;
    }

    bd->partidas[bd->quantidade] = partida;
    bd->quantidade++;

    return 1;
}

Partida* buscarPartidaPorId(BDPartidas *bd, int id) {
    if (bd == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < bd->quantidade; i++) {
        if (bd->partidas[i] != NULL && obterIdPartida(bd->partidas[i]) == id) {
            return bd->partidas[i];
        }
    }

    return NULL;
}

int obterQuantidadePartidas(BDPartidas *bd) {
    if (bd == NULL) {
        return 0;
    }
    return bd->quantidade;
}

Partida *obterPartidaPorIndice(BDPartidas *bd, int indice) {
    if (bd == NULL || indice < 0 || indice >= bd->quantidade) {
        return NULL;
    }
    return bd->partidas[indice];
}

int carregarPartidasCSV(BDPartidas *bd, const char *nomeArquivo) {
    if (bd == NULL || nomeArquivo == NULL) {
        return 0;
    }
    
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de partidas: %s\n", nomeArquivo);
        return 0;
    }

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
            Partida *partida = criarPartida(id, time1, time2, golsTime1, golsTime2);
            
            if (partida == NULL) {
                printf("Erro ao alocar memoria para partida.\n");
                fclose(arquivo);
                return 0;
            }

            if (!adicionarPartida(bd, partida)) {
                printf("Limite maximo de partidas atingido.\n");
                liberarPartida(partida);
                break;
            }
        }
    }

    fclose(arquivo);

    return 1;
}

void imprimirTodasPartidas(BDPartidas *bd) {
    if (bd == NULL) {
        return;
    }
    
    printf("ID Time1 Time2 Placar\n");

    for (int i = 0; i < bd->quantidade; i++) {
        if (bd->partidas[i] != NULL) {
            imprimirPartida(bd->partidas[i]);
        }
    }
}