#ifndef PARTIDA_H
#define PARTIDA_H

/*
 * TAD Partida: Representa uma partida do campeonato
 * A definicao completa da struct esta em partida.c
 * A interface expoe apenas getters e funcoes utilitarias
 */
typedef struct partida Partida;

/* Cria e aloca uma nova partida com os dados fornecidos */
Partida *criarPartida(int id, int time1, int time2, int golsTime1, int golsTime2);

/* Libera memória alocada para a partida */
void liberarPartida(Partida *partida);

/* === GETTERS === */
int obterIdPartida(Partida *partida);
int obterTime1Partida(Partida *partida);
int obterTime2Partida(Partida *partida);
int obterGolsTime1Partida(Partida *partida);
int obterGolsTime2Partida(Partida *partida);

/* Imprime os dados basicos da partida, usando os IDs dos times */
void imprimirPartida(Partida *partida);

#endif