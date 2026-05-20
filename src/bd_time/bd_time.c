#include <stdio.h>
#include <string.h>
#include "bd_time.h"

void inicializarBDTimes(BDTimes *bd) {
    bd->quantidade = 0;
}

int adicionarTime(BDTimes *bd, Time time) {
    if (bd->quantidade >= MAX_TIMES) {
        return 0;
    }

    bd->times[bd->quantidade] = time;
    bd->quantidade++;

    return 1;
}

Time* buscarTimePorId(BDTimes *bd, int id) {
    for (int i = 0; i < bd->quantidade; i++) {
        if (bd->times[i].id == id) {
            return &bd->times[i];
        }
    }

    return NULL;
}

int carregarTimesCSV(BDTimes *bd, const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de times: %s\n", nomeArquivo);
        return 0;
    }

    inicializarBDTimes(bd);

    char linha[100];

    /* Ignora a primeira linha do CSV (cabecalho com nomes das colunas) */
    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        fclose(arquivo);
        return 0;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        /* strcspn remove quebras de linha (\r\n) do final da linha */
        linha[strcspn(linha, "\r\n")] = '\0';

        int id;
        char nome[TAM_NOME_TIME];
        char *virgula = strchr(linha, ',');

        if (virgula != NULL) {
            if (sscanf(linha, "%d", &id) == 1) {
                strncpy(nome, virgula + 1, TAM_NOME_TIME - 1);
                nome[TAM_NOME_TIME - 1] = '\0';

                Time time;
                inicializarTime(&time, id, nome);
                if (!adicionarTime(bd, time)) {
                    printf("Limite maximo de times atingido.\n");
                    break;
                }
            }
        }
    }

    fclose(arquivo);

    return 1;
}

void imprimirTodosTimes(BDTimes *bd) {
    for (int i = 0; i < bd->quantidade; i++) {
        imprimirTime(bd->times[i]);
    }
}

void calcularClassificacao(BDTimes *bd, BDPartidas *bdPartidas) {
    /* 1. Reseta todas as estatisticas dos times para garantir consistencia */
    for (int i = 0; i < bd->quantidade; i++) {
        bd->times[i].vitorias = 0;
        bd->times[i].empates = 0;
        bd->times[i].derrotas = 0;
        bd->times[i].golsMarcados = 0;
        bd->times[i].golsSofridos = 0;
    }

    /* 2. Processa cada partida */
    for (int i = 0; i < bdPartidas->quantidade; i++) {
        Partida *partida = &bdPartidas->partidas[i];

        /* Busca os dois times pelo ID */
        Time *time1 = buscarTimePorId(bd, partida->time1);
        Time *time2 = buscarTimePorId(bd, partida->time2);

        if (time1 == NULL || time2 == NULL) {
            continue;
        }

        /* 3. Atualiza gols marcados e sofridos
         *    Time1 marcou golsTime1 e sofreu golsTime2
         *    Time2 marcou golsTime2 e sofreu golsTime1
         */
        time1->golsMarcados += partida->golsTime1;
        time1->golsSofridos += partida->golsTime2;

        time2->golsMarcados += partida->golsTime2;
        time2->golsSofridos += partida->golsTime1;

        /* 4. Atualiza vitorias, empates e derrotas */
        if (partida->golsTime1 > partida->golsTime2) {
            time1->vitorias++;
            time2->derrotas++;
        } else if (partida->golsTime1 < partida->golsTime2) {
            time2->vitorias++;
            time1->derrotas++;
        } else {
            time1->empates++;
            time2->empates++;
        }
    }
}