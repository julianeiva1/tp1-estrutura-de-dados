#include <stdio.h>
#include "partida.h"

void inicializarPartida(
    Partida *partida,
    int id,
    int time1,
    int time2,
    int golsTime1,
    int golsTime2
) {
    partida->id = id;
    partida->time1 = time1;
    partida->time2 = time2;
    partida->golsTime1 = golsTime1;
    partida->golsTime2 = golsTime2;
}

void imprimirPartida(Partida partida) {
    printf("%d %d %d %d x %d\n",
           partida.id,
           partida.time1,
           partida.time2,
           partida.golsTime1,
           partida.golsTime2);
}

