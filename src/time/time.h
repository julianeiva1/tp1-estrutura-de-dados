#ifndef TIME_H
#define TIME_H

#define TAM_NOME_TIME 50

/*
 * TAD Time: Representa um time do campeonato
 * Armazena ID, nome e estatisticas acumuladas:
 * - vitorias, empates, derrotas
 * - golsMarcados, golsSofridos
 */
typedef struct {
    int id;
    char nome[TAM_NOME_TIME];

    int vitorias;
    int empates;
    int derrotas;
    int golsMarcados;
    int golsSofridos;
} Time;

/* Inicializa um novo time com ID, nome e estatisticas zeradas */
void inicializarTime(Time *time, int id, const char *nome);

/* Calcula saldo de gols: gols marcados - gols sofridos */
int calcularSaldoGols(Time time);
/* Calcula pontos ganhos: vitorias*3 + empates */
int calcularPontos(Time time);

/* Imprime as estatisticas do time em uma linha formatada */
void imprimirTime(Time time);

#endif

