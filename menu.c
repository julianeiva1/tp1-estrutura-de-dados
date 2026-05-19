#include "menu.h"
#include <stdio.h>
#include <string.h>

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

    /* Busca por prefixo: strncmp compara os primeiros strlen(busca) caracteres
     * Exemplo: buscar "JAV" encontra "JAVAlis" */
    for (int i = 0; i < bd->quantidade; i++) {
        if (strncmp(bd->times[i].nome, busca, strlen(busca)) == 0) {
            encontrou = 1;
            imprimirTime(bd->times[i]);
        }
    }

    if (!encontrou) {
        printf("Nenhum time encontrado.\n");
    }
}

void consultarPartidas(BDTimes *bd, BDPartidas *bdPartidas) {
    char opcao;
    char busca[50];
    int encontrou = 0;

    printf("\nEscolha o modo de consulta:\n");
    printf("1 - Por time mandante\n");
    printf("2 - Por time visitante\n");
    printf("3 - Por time mandante ou visitante\n");
    printf("4 - Retornar ao menu principal\n");
    printf("\nEscolha uma opcao: ");
    scanf(" %c", &opcao);

    if (opcao == '4') {
        return;
    }

    if (opcao < '1' || opcao > '3') {
        printf("Opcao invalida!\n");
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

        if (opcao == '1') {
            if (strncmp(nomeMandante, busca, strlen(busca)) == 0) {
                corresponde = 1;
            }
        } else if (opcao == '2') {
            if (strncmp(nomeVisitante, busca, strlen(busca)) == 0) {
                corresponde = 1;
            }
        } else if (opcao == '3') {
            if (strncmp(nomeMandante, busca, strlen(busca)) == 0 ||
                strncmp(nomeVisitante, busca, strlen(busca)) == 0) {
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
        printf("Nenhuma partida encontrada.\n");
    }
}

void atualizarPartida(void) {
    /* Stub: Funcionalidade sera implementada em versao futura (Parte II) */
    printf("Funcionalidade nao implementada nesta versao.\n");
}

void removerPartida(void) {
    /* Stub: Funcionalidade sera implementada em versao futura (Parte II) */
    printf("Funcionalidade nao implementada nesta versao.\n");
}

void inserirPartida(void) {
    /* Stub: Funcionalidade sera implementada em versao futura (Parte II) */
    printf("Funcionalidade nao implementada nesta versao.\n");
}

void imprimirClassificacao(BDTimes *bd) {
    printf("\nImprimindo classificacao...\n");
    printf("\nID Time V E D GM GS S PG\n");
    imprimirTodosTimes(bd);
}