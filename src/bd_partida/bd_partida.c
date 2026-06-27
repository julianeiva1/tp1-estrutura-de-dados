#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bd_partida.h"

/*
 * Nó interno da lista simplesmente encadeada de partidas.
 */
typedef struct no_partida {
    Partida *partida;
    struct no_partida *prox;
} NoPartida;

/*
 * Definicao da struct BDPartidas.
 * Armazena uma lista encadeada de partidas.
 */
struct bd_partidas {
    NoPartida *inicio;
    int quantidade;
};

/* === GERENCIAMENTO DE MEMORIA === */

BDPartidas *criarBDPartidas(void) {
    BDPartidas *bd = (BDPartidas *)malloc(sizeof(BDPartidas));
    if (bd == NULL) {
        return NULL;
    }

    bd->inicio = NULL;
    bd->quantidade = 0;

    return bd;
}

void liberarBDPartidas(BDPartidas *bd) {
    if (bd == NULL) {
        return;
    }

    NoPartida *atual = bd->inicio;
    while (atual != NULL) {
        NoPartida *prox = atual->prox;
        liberarPartida(atual->partida);
        free(atual);
        atual = prox;
    }

    free(bd);
}

/* === INTERFACE PUBLICA === */

int adicionarPartida(BDPartidas *bd, Partida *partida) {
    if (bd == NULL || partida == NULL) {
        return 0;
    }

    NoPartida *novoNo = (NoPartida *)malloc(sizeof(NoPartida));
    if (novoNo == NULL) {
        return 0;
    }

    novoNo->partida = partida;
    novoNo->prox = NULL;

    if (bd->inicio == NULL) {
        bd->inicio = novoNo;
    } else {
        NoPartida *ultimo = bd->inicio;
        while (ultimo->prox != NULL) {
            ultimo = ultimo->prox;
        }
        ultimo->prox = novoNo;
    }

    bd->quantidade++;
    return 1;
}

int removerPartidaPorId(BDPartidas *bd, int id) {
    if (bd == NULL) {
        return 0;
    }

    NoPartida *anterior = NULL;
    NoPartida *atual = bd->inicio;

    while (atual != NULL) {
        if (atual->partida != NULL && obterIdPartida(atual->partida) == id) {
            if (anterior == NULL) {
                bd->inicio = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }

            liberarPartida(atual->partida);
            free(atual);
            bd->quantidade--;
            return 1;
        }

        anterior = atual;
        atual = atual->prox;
    }

    return 0;
}

Partida *buscarPartidaPorId(BDPartidas *bd, int id) {
    if (bd == NULL) {
        return NULL;
    }

    NoPartida *atual = bd->inicio;
    while (atual != NULL) {
        if (atual->partida != NULL && obterIdPartida(atual->partida) == id) {
            return atual->partida;
        }
        atual = atual->prox;
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

    NoPartida *atual = bd->inicio;
    for (int i = 0; atual != NULL && i < indice; i++) {
        atual = atual->prox;
    }

    if (atual == NULL) {
        return NULL;
    }

    return atual->partida;
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

    if (fgets(linha, sizeof(linha), arquivo) == NULL) {
        fclose(arquivo);
        return 0;
    }

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
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
                printf("Erro ao adicionar partida na lista.\n");
                liberarPartida(partida);
                fclose(arquivo);
                return 0;
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

    NoPartida *atual = bd->inicio;
    while (atual != NULL) {
        if (atual->partida != NULL) {
            imprimirPartida(atual->partida);
        }
        atual = atual->prox;
    }
}