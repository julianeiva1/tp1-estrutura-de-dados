#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bd_time.h"
#include "bd_partida.h"

/*
 * Definicao opaca da struct BDTimes (privada a este arquivo)
 * Armazena um array de ponteiros para Times alocados dinamicamente
 */
struct bd_times {
    Time *times[MAX_TIMES];
    int quantidade;
};

/* === GERENCIAMENTO DE MEMORIA === */

BDTimes *criarBDTimes(void) {
    BDTimes *bd = (BDTimes *)malloc(sizeof(BDTimes));
    if (bd == NULL) {
        return NULL;
    }
    
    bd->quantidade = 0;
    for (int i = 0; i < MAX_TIMES; i++) {
        bd->times[i] = NULL;
    }
    
    return bd;
}

void liberarBDTimes(BDTimes *bd) {
    if (bd != NULL) {
        for (int i = 0; i < bd->quantidade; i++) {
            if (bd->times[i] != NULL) {
                liberarTime(bd->times[i]);
            }
        }
        free(bd);
    }
}

/* === INTERFACE PUBLICA === */

int adicionarTime(BDTimes *bd, Time *time) {
    if (bd == NULL || time == NULL) {
        return 0;
    }
    
    if (bd->quantidade >= MAX_TIMES) {
        return 0;
    }

    bd->times[bd->quantidade] = time;
    bd->quantidade++;

    return 1;
}

Time* buscarTimePorId(BDTimes *bd, int id) {
    if (bd == NULL) {
        return NULL;
    }
    
    for (int i = 0; i < bd->quantidade; i++) {
        if (bd->times[i] != NULL && obterIdTime(bd->times[i]) == id) {
            return bd->times[i];
        }
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
    return bd->times[indice];
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

                Time *time = criarTime(id, nome);
                if (time == NULL) {
                    printf("Erro ao alocar memoria para time.\n");
                    fclose(arquivo);
                    return 0;
                }
                
                if (!adicionarTime(bd, time)) {
                    printf("Limite maximo de times atingido.\n");
                    liberarTime(time);
                    break;
                }
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
    
    for (int i = 0; i < bd->quantidade; i++) {
        if (bd->times[i] != NULL) {
            imprimirTime(bd->times[i]);
        }
    }
}

void calcularClassificacao(BDTimes *bd, BDPartidas *bdPartidas) {
    if (bd == NULL || bdPartidas == NULL) {
        return;
    }
    
    /* 1. Reseta todas as estatisticas dos times para garantir consistencia */
    for (int i = 0; i < bd->quantidade; i++) {
        if (bd->times[i] != NULL) {
            zerarEstatisticasTime(bd->times[i]);
        }
    }

    /* 2. Processa cada partida */
    int qtdPartidas = obterQuantidadePartidas(bdPartidas);
    for (int i = 0; i < qtdPartidas; i++) {
        Partida *partida = obterPartidaPorIndice(bdPartidas, i);
        if (partida == NULL) {
            continue;
        }

        /* Busca os dois times pelo ID */
        int time1Id = obterTime1Partida(partida);
        int time2Id = obterTime2Partida(partida);
        
        Time *time1 = buscarTimePorId(bd, time1Id);
        Time *time2 = buscarTimePorId(bd, time2Id);

        if (time1 == NULL || time2 == NULL) {
            continue;
        }

        /* 3. Atualiza gols marcados e sofridos
         *    Time1 marcou golsTime1 e sofreu golsTime2
         *    Time2 marcou golsTime2 e sofreu golsTime1
         */
        int golsTime1 = obterGolsTime1Partida(partida);
        int golsTime2 = obterGolsTime2Partida(partida);
        
        adicionarGolsMarcados(time1, golsTime1);
        adicionarGolsSofridos(time1, golsTime2);

        adicionarGolsMarcados(time2, golsTime2);
        adicionarGolsSofridos(time2, golsTime1);

        /* 4. Atualiza vitorias, empates e derrotas */
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