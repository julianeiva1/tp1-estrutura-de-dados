#include "menu.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
 * Compara se prefixo é prefixo de nome, ignorando maiúsculas/minúsculas
 * Retorna 1 se sim, 0 caso contrário
 */
static int compararPrefixoIgnoreCase(const char *nome, const char *prefixo) {
    for (int i = 0; prefixo[i] != '\0'; i++) {
        if (tolower((unsigned char)nome[i]) != tolower((unsigned char)prefixo[i])) {
            return 0;
        }
    }
    return 1;
}

/*
 * Auxilia na busca de times: localiza o nome pelo ID
 * Retorna "Nao encontrado" se ID invalido
 */
char *buscarNomeTime(BDTimes *bd, int id) {
    for (int i = 0; i < bd->quantidade; i++) {
        if (bd->times[i].id == id) {
            return bd->times[i].nome;
        }
    }

    return "Nao encontrado";
}

void consultarTime(BDTimes *bd) {
    char busca[50];
    int encontrou = 0;

    printf("Digite o nome ou prefixo do time: ");
    scanf("%49s", busca);

    printf("\nID Time V E D GM GS S PG\n");

    /* Busca por prefixo ignorando maiúsculas/minúsculas
     * Exemplo: buscar "jav" encontra "JAVAlis" */
    for (int i = 0; i < bd->quantidade; i++) {
        if (compararPrefixoIgnoreCase(bd->times[i].nome, busca)) {
            encontrou = 1;
            imprimirTime(bd->times[i]);
        }
    }

    if (!encontrou) {
        printf(COR_VERMELHA "Nenhum time encontrado.\n" COR_RESET);
    }
}

void consultarPartidas(BDTimes *bd, BDPartidas *bdPartidas) {
    char opcao[10];
    char busca[50];
    int encontrou = 0;

    printf("\nEscolha o modo de consulta:\n");
    printf("1 - Por time mandante\n");
    printf("2 - Por time visitante\n");
    printf("3 - Por time mandante ou visitante\n");
    printf("4 - Retornar ao menu principal\n");
    printf("\nEscolha uma opcao: ");
    scanf("%9s", opcao);

    if (strcmp(opcao, "4") == 0) {
        return;
    }

    if ((strcmp(opcao, "1") != 0) && (strcmp(opcao, "2") != 0) && (strcmp(opcao, "3") != 0)) {
        printf(COR_VERMELHA "Opcao invalida!\n" COR_RESET);
        return;
    }

    printf("\nDigite o nome: ");
    scanf("%49s", busca);

    printf("\nID Time1 Time2\n");

    for (int i = 0; i < bdPartidas->quantidade; i++) {
        char *nomeMandante = buscarNomeTime(bd, bdPartidas->partidas[i].time1);
        char *nomeVisitante = buscarNomeTime(bd, bdPartidas->partidas[i].time2);

        /* Determina se a partida corresponde aos criterios da busca */
        int corresponde = 0;

        if (strcmp(opcao, "1") == 0) {
            if (compararPrefixoIgnoreCase(nomeMandante, busca)) {
                corresponde = 1;
            }
        } else if (strcmp(opcao, "2") == 0) {
            if (compararPrefixoIgnoreCase(nomeVisitante, busca)) {
                corresponde = 1;
            }
        } else if (strcmp(opcao, "3") == 0) {
            if (compararPrefixoIgnoreCase(nomeMandante, busca) ||
                compararPrefixoIgnoreCase(nomeVisitante, busca)) {
                corresponde = 1;
            }
        }

        if (corresponde) {
            encontrou = 1;

            printf("%d %s %d x %d %s\n",
                   bdPartidas->partidas[i].id,
                   nomeMandante,
                   bdPartidas->partidas[i].golsTime1,
                   bdPartidas->partidas[i].golsTime2,
                   nomeVisitante);
        }
    }

    if (!encontrou) {
        printf(COR_VERMELHA "Nenhuma partida encontrada.\n" COR_RESET);
    }
}

void atualizarPartida(void) {
    /* Stub: Funcionalidade sera implementada em versao futura (Parte II) */
    printf(COR_VERMELHA "Funcionalidade nao implementada nesta versao.\n" COR_RESET);
}

void removerPartida(void) {
    /* Stub: Funcionalidade sera implementada em versao futura (Parte II) */
    printf(COR_VERMELHA "Funcionalidade nao implementada nesta versao.\n" COR_RESET);
}

void inserirPartida(void) {
    /* Stub: Funcionalidade sera implementada em versao futura (Parte II) */
    printf(COR_VERMELHA "Funcionalidade nao implementada nesta versao.\n" COR_RESET);
}

void imprimirClassificacao(BDTimes *bd) {
    printf(COR_VERDE "\nImprimindo classificacao...\n" COR_RESET);
    printf("\nID Time V E D GM GS S PG\n");
    imprimirTodosTimes(bd);
}