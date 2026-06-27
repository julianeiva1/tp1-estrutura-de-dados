#include "menu.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>

/*
 * Compara se prefixo é prefixo de nome, ignorando maiúsculas/minúsculas.
 */
static int compararPrefixoIgnoreCase(const char *nome, const char *prefixo) {
    if (nome == NULL || prefixo == NULL) {
        return 0;
    }

    for (int i = 0; prefixo[i] != '\0'; i++) {
        if (nome[i] == '\0') {
            return 0;
        }
        if (tolower((unsigned char)nome[i]) != tolower((unsigned char)prefixo[i])) {
            return 0;
        }
    }
    return 1;
}

static void limparBufferEntrada(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
}

static int lerGolsValido(const char *mensagem, int valorAtual) {
    while (1) {
        char entrada[32];
        char *fim;
        long valor;

        printf("%s", mensagem);
        if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
            printf(COR_VERMELHA "Valor invalido. Use um numero inteiro nao negativo ou '-'.\n" COR_RESET);
            continue;
        }

        int temQuebraDeLinha = strchr(entrada, '\n') != NULL || strchr(entrada, '\r') != NULL;

        if (!temQuebraDeLinha) {
            limparBufferEntrada();
        }

        entrada[strcspn(entrada, "\r\n")] = '\0';
        if (strcmp(entrada, "-") == 0) {
            return valorAtual;
        }

        errno = 0;
        valor = strtol(entrada, &fim, 10);
        if (errno != 0 || fim == entrada || *fim != '\0' || valor < 0 || valor > INT_MAX) {
            printf(COR_VERMELHA "Valor invalido. Use um numero inteiro nao negativo ou '-'.\n" COR_RESET);
            continue;
        }

        return (int)valor;
    }
}

static int lerConfirmacao(const char *mensagem) {
    char entrada[8];

    printf("%s", mensagem);
    if (fgets(entrada, sizeof(entrada), stdin) == NULL) {
        return 0;
    }

    entrada[strcspn(entrada, "\r\n")] = '\0';
    return (strcmp(entrada, "S") == 0 || strcmp(entrada, "s") == 0);
}

static void mostrarPartidaFormatada(BDTimes *bd, Partida *partida) {
    if (bd == NULL || partida == NULL) {
        return;
    }

    const char *mandante = buscarNomeTime(bd, obterTime1Partida(partida));
    const char *visitante = buscarNomeTime(bd, obterTime2Partida(partida));
    printf("ID: %d\n", obterIdPartida(partida));
    printf("%s %d x %d %s\n",
           mandante,
           obterGolsTime1Partida(partida),
           obterGolsTime2Partida(partida),
           visitante);
}

static void mostrarPartidaComPlacares(BDTimes *bd, int id, int time1Id, int time2Id, int gols1, int gols2) {
    if (bd == NULL) {
        return;
    }

    const char *mandante = buscarNomeTime(bd, time1Id);
    const char *visitante = buscarNomeTime(bd, time2Id);
    printf("ID: %d\n", id);
    printf("%s %d x %d %s\n",
           mandante,
           gols1,
           gols2,
           visitante);
}

static int compararTimesPorClassificacao(const void *a, const void *b) {
    const Time *const *timeA = (const Time *const *)a;
    const Time *const *timeB = (const Time *const *)b;

    const Time *time1 = *timeA;
    const Time *time2 = *timeB;

    int pontosA = calcularPontos((Time *)time1);
    int pontosB = calcularPontos((Time *)time2);
    if (pontosA != pontosB) {
        return pontosB - pontosA;
    }

    int vitoriasA = obterVitorias((Time *)time1);
    int vitoriasB = obterVitorias((Time *)time2);
    if (vitoriasA != vitoriasB) {
        return vitoriasB - vitoriasA;
    }

    int saldoA = calcularSaldoGols((Time *)time1);
    int saldoB = calcularSaldoGols((Time *)time2);
    if (saldoA != saldoB) {
        return saldoB - saldoA;
    }

    return obterIdTime((Time *)time1) - obterIdTime((Time *)time2);
}

static Time **obterTimesOrdenados(BDTimes *bd, int *quantidade) {
    if (bd == NULL || quantidade == NULL) {
        return NULL;
    }

    int qtdTimes = obterQuantidadeTimes(bd);
    Time **timesOrdenados = NULL;

    if (qtdTimes > 0) {
        timesOrdenados = (Time **)malloc(sizeof(Time *) * qtdTimes);
        if (timesOrdenados == NULL) {
            *quantidade = 0;
            return NULL;
        }

        for (int i = 0; i < qtdTimes; i++) {
            timesOrdenados[i] = obterTimePorIndice(bd, i);
        }

        qsort(timesOrdenados, qtdTimes, sizeof(Time *), compararTimesPorClassificacao);
    }

    *quantidade = qtdTimes;
    return timesOrdenados;
}

static void escreverCabecalhoClassificacao(FILE *arquivo) {
    fprintf(arquivo, "ID,Time,V,E,D,GM,GS,S,PG\n");
}

static int buscarMaiorIdPartida(BDPartidas *bdPartidas) {
    int maior = -1;
    int qtdPartidas = obterQuantidadePartidas(bdPartidas);
    for (int i = 0; i < qtdPartidas; i++) {
        Partida *partida = obterPartidaPorIndice(bdPartidas, i);
        if (partida != NULL) {
            int id = obterIdPartida(partida);
            if (id > maior) {
                maior = id;
            }
        }
    }
    return maior;
}

void salvarDadosPersistidos(BDTimes *bd, BDPartidas *bdPartidas) {
    if (bd == NULL || bdPartidas == NULL) {
        return;
    }

    FILE *arquivo = fopen("data/bd_partidas.csv", "w");
    if (arquivo == NULL) {
        printf(COR_VERMELHA "Erro ao abrir data/bd_partidas.csv para escrita.\n" COR_RESET);
        return;
    }

    fprintf(arquivo, "ID,Time1ID,Time2ID,GolsTime1,GolsTime2\n");
    int qtdPartidas = obterQuantidadePartidas(bdPartidas);
    for (int i = 0; i < qtdPartidas; i++) {
        Partida *partida = obterPartidaPorIndice(bdPartidas, i);
        if (partida != NULL) {
            fprintf(arquivo, "%d,%d,%d,%d,%d\n",
                    obterIdPartida(partida),
                    obterTime1Partida(partida),
                    obterTime2Partida(partida),
                    obterGolsTime1Partida(partida),
                    obterGolsTime2Partida(partida));
        }
    }
    fclose(arquivo);

    FILE *arquivoClassificacao = fopen("data/bd_classificacao.csv", "w");
    if (arquivoClassificacao == NULL) {
        printf(COR_VERMELHA "Erro ao abrir data/bd_classificacao.csv para escrita.\n" COR_RESET);
        return;
    }

    escreverCabecalhoClassificacao(arquivoClassificacao);

    int qtdTimes = 0;
    Time **timesOrdenados = obterTimesOrdenados(bd, &qtdTimes);
    if (timesOrdenados == NULL && qtdTimes > 0) {
        fclose(arquivoClassificacao);
        printf(COR_VERMELHA "Erro ao alocar memoria para ordenacao.\n" COR_RESET);
        return;
    }

    for (int i = 0; i < qtdTimes; i++) {
        Time *time = timesOrdenados[i];
        if (time != NULL) {
            fprintf(arquivoClassificacao, "%d,%s,%d,%d,%d,%d,%d,%d,%d\n",
                    obterIdTime(time),
                    obterNomeTime(time),
                    obterVitorias(time),
                    obterEmpates(time),
                    obterDerrotas(time),
                    obterGolsMarcados(time),
                    obterGolsSofridos(time),
                    calcularSaldoGols(time),
                    calcularPontos(time));
        }
    }

    free(timesOrdenados);
    fclose(arquivoClassificacao);
}

char *buscarNomeTime(BDTimes *bd, int id) {
    Time *time = buscarTimePorId(bd, id);
    if (time != NULL) {
        return (char *)obterNomeTime(time);
    }
    return "Nao encontrado";
}

void consultarTime(BDTimes *bd) {
    char busca[50];
    int encontrou = 0;

    printf("Digite o nome ou prefixo do time: ");
    scanf("%49s", busca);
    limparBufferEntrada();

    printf("\n");
    imprimirCabecalhoTimes();

    int qtdTimes = obterQuantidadeTimes(bd);
    for (int i = 0; i < qtdTimes; i++) {
        Time *time = obterTimePorIndice(bd, i);
        if (time != NULL && compararPrefixoIgnoreCase(obterNomeTime(time), busca)) {
            encontrou = 1;
            imprimirTime(time);
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
    limparBufferEntrada();

    if (strcmp(opcao, "4") == 0) {
        return;
    }

    if ((strcmp(opcao, "1") != 0) && (strcmp(opcao, "2") != 0) && (strcmp(opcao, "3") != 0)) {
        printf(COR_VERMELHA "Opcao invalida!\n" COR_RESET);
        return;
    }

    printf("\nDigite o nome: ");
    scanf("%49s", busca);
    limparBufferEntrada();

    printf("\nID  %-15s %-7s %-15s\n", "Mandante", "Placar", "Visitante");
    printf("---------------------------------------------\n");

    int qtdPartidas = obterQuantidadePartidas(bdPartidas);
    for (int i = 0; i < qtdPartidas; i++) {
        Partida *partida = obterPartidaPorIndice(bdPartidas, i);
        if (partida == NULL) {
            continue;
        }

        char *nomeMandante = buscarNomeTime(bd, obterTime1Partida(partida));
        char *nomeVisitante = buscarNomeTime(bd, obterTime2Partida(partida));

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
            printf("%-3d %-15s %d x %-3d %-15s\n",
                   obterIdPartida(partida),
                   nomeMandante,
                   obterGolsTime1Partida(partida),
                   obterGolsTime2Partida(partida),
                   nomeVisitante);
        }
    }

    if (!encontrou) {
        printf(COR_VERMELHA "Nenhuma partida encontrada.\n" COR_RESET);
    }
}

void atualizarPartida(BDTimes *bd, BDPartidas *bdPartidas) {
    if (bd == NULL || bdPartidas == NULL) {
        return;
    }

    int id;
    printf("Digite o ID da partida para atualizar: ");
    if (scanf("%d", &id) != 1) {
        limparBufferEntrada();
        printf(COR_VERMELHA "ID invalido.\n" COR_RESET);
        return;
    }
    limparBufferEntrada();

    Partida *partida = buscarPartidaPorId(bdPartidas, id);
    if (partida == NULL) {
        printf(COR_VERMELHA "Partida nao encontrada.\n" COR_RESET);
        return;
    }

    int placarAtualTime1 = obterGolsTime1Partida(partida);
    int placarAtualTime2 = obterGolsTime2Partida(partida);

    printf("Partida encontrada:\n");
    mostrarPartidaFormatada(bd, partida);
    printf("Placar atual: %d x %d\n", placarAtualTime1, placarAtualTime2);

    int gols1 = lerGolsValido("Novo placar do time 1 (ou '-'): ", placarAtualTime1);
    int gols2 = lerGolsValido("Novo placar do time 2 (ou '-'): ", placarAtualTime2);

    printf("Nova versao da partida:\n");
    mostrarPartidaComPlacares(bd,
                              obterIdPartida(partida),
                              obterTime1Partida(partida),
                              obterTime2Partida(partida),
                              gols1,
                              gols2);

    if (!lerConfirmacao("Confirmar atualizacao? (S/N): ")) {
        printf("Operacao cancelada.\n");
        return;
    }

    atualizarPlacarPartida(partida, gols1, gols2);
    calcularClassificacao(bd, bdPartidas);
    salvarDadosPersistidos(bd, bdPartidas);
    printf(COR_VERDE "Partida atualizada com sucesso.\n" COR_RESET);
}

void removerPartida(BDTimes *bd, BDPartidas *bdPartidas) {
    if (bd == NULL || bdPartidas == NULL) {
        return;
    }

    int id;
    printf("Digite o ID da partida para remover: ");
    if (scanf("%d", &id) != 1) {
        limparBufferEntrada();
        printf(COR_VERMELHA "ID invalido.\n" COR_RESET);
        return;
    }
    limparBufferEntrada();

    Partida *partida = buscarPartidaPorId(bdPartidas, id);
    if (partida == NULL) {
        printf(COR_VERMELHA "Partida nao encontrada.\n" COR_RESET);
        return;
    }

    printf("Partida encontrada:\n");
    mostrarPartidaFormatada(bd, partida);

    if (!lerConfirmacao("Deseja realmente remover esta partida? (S/N): ")) {
        printf("Operacao cancelada.\n");
        return;
    }

    if (!removerPartidaPorId(bdPartidas, id)) {
        printf(COR_VERMELHA "Partida nao encontrada para remocao.\n" COR_RESET);
        return;
    }

    calcularClassificacao(bd, bdPartidas);
    salvarDadosPersistidos(bd, bdPartidas);
    printf(COR_VERDE "Partida removida com sucesso.\n" COR_RESET);
}

void inserirPartida(BDTimes *bd, BDPartidas *bdPartidas) {
    if (bd == NULL || bdPartidas == NULL) {
        return;
    }

    int idTime1;
    int idTime2;
    int gols1;
    int gols2;

    printf("ID do time mandante: ");
    if (scanf("%d", &idTime1) != 1) {
        limparBufferEntrada();
        printf(COR_VERMELHA "ID do time mandante invalido.\n" COR_RESET);
        return;
    }

    printf("ID do time visitante: ");
    if (scanf("%d", &idTime2) != 1) {
        limparBufferEntrada();
        printf(COR_VERMELHA "ID do time visitante invalido.\n" COR_RESET);
        return;
    }

    printf("Gols do time mandante: ");
    if (scanf("%d", &gols1) != 1 || gols1 < 0) {
        limparBufferEntrada();
        printf(COR_VERMELHA "Gols invalidos para o time mandante.\n" COR_RESET);
        return;
    }

    printf("Gols do time visitante: ");
    if (scanf("%d", &gols2) != 1 || gols2 < 0) {
        limparBufferEntrada();
        printf(COR_VERMELHA "Gols invalidos para o time visitante.\n" COR_RESET);
        return;
    }
    limparBufferEntrada();

    Time *time1 = buscarTimePorId(bd, idTime1);
    Time *time2 = buscarTimePorId(bd, idTime2);

    if (time1 == NULL || time2 == NULL) {
        printf(COR_VERMELHA "Os dois times devem existir no cadastro.\n" COR_RESET);
        return;
    }

    if (idTime1 == idTime2) {
        printf(COR_VERMELHA "Os times devem ser diferentes.\n" COR_RESET);
        return;
    }

    int novoId = buscarMaiorIdPartida(bdPartidas) + 1;
    Partida *novaPartida = criarPartida(novoId, idTime1, idTime2, gols1, gols2);
    if (novaPartida == NULL) {
        printf(COR_VERMELHA "Erro ao alocar memoria para nova partida.\n" COR_RESET);
        return;
    }

    printf("Registro a inserir:\n");
    printf("ID: %d\n", novoId);
    printf("%s %d x %d %s\n",
           obterNomeTime(time1),
           gols1,
           gols2,
           obterNomeTime(time2));

    if (!lerConfirmacao("Confirmar insercao? (S/N): ")) {
        printf("Operacao cancelada.\n");
        liberarPartida(novaPartida);
        return;
    }

    if (!adicionarPartida(bdPartidas, novaPartida)) {
        liberarPartida(novaPartida);
        printf(COR_VERMELHA "Erro ao inserir partida na lista.\n" COR_RESET);
        return;
    }

    calcularClassificacao(bd, bdPartidas);
    salvarDadosPersistidos(bd, bdPartidas);
    printf(COR_VERDE "Partida inserida com sucesso.\n" COR_RESET);
}

void imprimirClassificacao(BDTimes *bd, BDPartidas *bdPartidas) {
    if (bd == NULL || bdPartidas == NULL) {
        return;
    }

    calcularClassificacao(bd, bdPartidas);
    printf(COR_VERDE "\nImprimindo classificacao...\n" COR_RESET);
    printf("\n");
    imprimirCabecalhoTimes();

    int qtdTimes = 0;
    Time **timesOrdenados = obterTimesOrdenados(bd, &qtdTimes);
    if (timesOrdenados == NULL && qtdTimes > 0) {
        printf(COR_VERMELHA "Erro ao montar a classificacao ordenada.\n" COR_RESET);
        return;
    }

    for (int i = 0; i < qtdTimes; i++) {
        if (timesOrdenados != NULL && timesOrdenados[i] != NULL) {
            imprimirTime(timesOrdenados[i]);
        }
    }

    free(timesOrdenados);
}