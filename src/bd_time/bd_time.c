#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bd_time.h"
#include "bd_partida.h"

/*
 * Nó interno da lista simplesmente encadeada de times.
 * Cada nó aponta para um Time e para o próximo elemento da coleção.
 */
typedef struct no_time {
    Time *time;
    struct no_time *prox;
} NoTime;

/*
 * Definicao da struct BDTimes.
 * Agora ela armazena uma lista encadeada de times, preservando encapsulamento.
 */
struct bd_times {
    NoTime *inicio;
    int quantidade;
};

/* === GERENCIAMENTO DE MEMORIA === */

BDTimes *criarBDTimes(void) {
    BDTimes *bd = (BDTimes *)malloc(sizeof(BDTimes));
    if (bd == NULL) {
        return NULL;
    }

    bd->inicio = NULL;
    bd->quantidade = 0;

    return bd;
}

void liberarBDTimes(BDTimes *bd) {
    if (bd == NULL) {
        return;
    }

    NoTime *atual = bd->inicio;
    while (atual != NULL) {
        NoTime *prox = atual->prox;
        liberarTime(atual->time);
        free(atual);
        atual = prox;
    }

    free(bd);
}

/* === INTERFACE PUBLICA === */

int adicionarTime(BDTimes *bd, Time *time) {
    if (bd == NULL || time == NULL) {
        return 0;
    }

    NoTime *novoNo = (NoTime *)malloc(sizeof(NoTime));
    if (novoNo == NULL) {
        return 0;
    }

    novoNo->time = time;
    novoNo->prox = NULL;

    if (bd->inicio == NULL) {
        bd->inicio = novoNo;
    } else {
        NoTime *ultimo = bd->inicio;
        while (ultimo->prox != NULL) {
            ultimo = ultimo->prox;
        }
        ultimo->prox = novoNo;
    }

    bd->quantidade++;
    return 1;
}

Time *buscarTimePorId(BDTimes *bd, int id) {
    if (bd == NULL) {
        return NULL;
    }

    NoTime *atual = bd->inicio;
    while (atual != NULL) {
        if (atual->time != NULL && obterIdTime(atual->time) == id) {
            return atual->time;
        }
        atual = atual->prox;
    }

    return NULL;
}

int obterQuantidadeTimes(BDTimes *bd) {
    if (bd == NULL) {
        return 0;
    }
    return bd->quantidade;
}

Time *obterTimePorIndice(BDTimes *bd, int indice) {
    if (bd == NULL || indice < 0 || indice >= bd->quantidade) {
        return NULL;
    }

    NoTime *atual = bd->inicio;
    for (int i = 0; atual != NULL && i < indice; i++) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        return NULL;
    }

    return atual->time;
}

int carregarTimesCSV(BDTimes *bd, const char *nomeArquivo) {
    if (bd == NULL || nomeArquivo == NULL) {
        return 0;
    }

    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de times: %s\n", nomeArquivo);
        return 0;
    }

    char linha[100];

    /* Ignora a primeira linha do CSV (cabecalho com nomes das colunas). */
    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        fclose(arquivo);
        return 0;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        linha[strcspn(linha, "\r\n")] = '\0';

        int id;
        char nome[TAM_NOME_TIME];
        char *virgula = strchr(linha, ',');

        if (virgula != NULL && sscanf(linha, "%d", &id) == 1) {
            strncpy(nome, virgula + 1, TAM_NOME_TIME - 1);
            nome[TAM_NOME_TIME - 1] = '\0';

            Time *time = criarTime(id, nome);
            if (time == NULL) {
                printf("Erro ao alocar memoria para time.\n");
                fclose(arquivo);
                return 0;
            }

            if (!adicionarTime(bd, time)) {
                printf("Erro ao adicionar time na lista.\n");
                liberarTime(time);
                fclose(arquivo);
                return 0;
            }
        }
    }

    fclose(arquivo);
    return 1;
}

void imprimirTodosTimes(BDTimes *bd) {
    if (bd == NULL) {
        return;
    }

    NoTime *atual = bd->inicio;
    while (atual != NULL) {
        if (atual->time != NULL) {
            imprimirTime(atual->time);
        }
        atual = atual->prox;
    }
}

void calcularClassificacao(BDTimes *bd, BDPartidas *bdPartidas) {
    if (bd == NULL || bdPartidas == NULL) {
        return;
    }

    /* 1. Reseta todas as estatisticas dos times para garantir consistencia. */
    NoTime *atualTime = bd->inicio;
    while (atualTime != NULL) {
        if (atualTime->time != NULL) {
            zerarEstatisticasTime(atualTime->time);
        }
        atualTime = atualTime->prox;
    }

    /* 2. Processa cada partida e atualiza as estatisticas dos times. */
    int qtdPartidas = obterQuantidadePartidas(bdPartidas);
    for (int i = 0; i < qtdPartidas; i++) {
        Partida *partida = obterPartidaPorIndice(bdPartidas, i);
        if (partida == NULL) {
            continue;
        }

        int time1Id = obterTime1Partida(partida);
        int time2Id = obterTime2Partida(partida);

        Time *time1 = buscarTimePorId(bd, time1Id);
        Time *time2 = buscarTimePorId(bd, time2Id);

        if (time1 == NULL || time2 == NULL) {
            continue;
        }

        int golsTime1 = obterGolsTime1Partida(partida);
        int golsTime2 = obterGolsTime2Partida(partida);

        adicionarGolsMarcados(time1, golsTime1);
        adicionarGolsSofridos(time1, golsTime2);

        adicionarGolsMarcados(time2, golsTime2);
        adicionarGolsSofridos(time2, golsTime1);

        if (golsTime1 > golsTime2) {
            adicionarVitoria(time1);
            adicionarDerrota(time2);
        } else if (golsTime1 < golsTime2) {
            adicionarVitoria(time2);
            adicionarDerrota(time1);
        } else {
            adicionarEmpate(time1);
            adicionarEmpate(time2);
        }
    }
}