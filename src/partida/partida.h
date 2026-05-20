#ifndef PARTIDA_H
#define PARTIDA_H

/*
 * TAD Partida: Representa uma partida do campeonato
 * Armazena ID de identificacao, IDs dos dois times e placar
 */
typedef struct {
    int id;
    int time1;
    int time2;
    int golsTime1;
    int golsTime2;
} Partida;

/* Inicializa uma nova partida com os dados fornecidos */
void inicializarPartida(
    Partida *partida,
    int id,
    int time1,
    int time2,
    int golsTime1,
    int golsTime2
);

/* Imprime os dados basicos da partida, usando os IDs dos times */
void imprimirPartida(Partida partida);

#endif