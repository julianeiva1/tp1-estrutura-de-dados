#include <stdio.h>
#include <stdlib.h>
#include "partida.h"

/*
 * Definicao opaca da struct Partida (privada a este arquivo)
 */
struct partida {
    int id;
    int time1;
    int time2;
    int golsTime1;
    int golsTime2;
};

/* === GERENCIAMENTO DE MEMORIA === */

Partida *criarPartida(int id, int time1, int time2, int golsTime1, int golsTime2) {
    Partida *partida = (Partida *)malloc(sizeof(Partida));
    if (partida == NULL) {
        return NULL;
    }
    
    partida->id = id;
    partida->time1 = time1;
    partida->time2 = time2;
    partida->golsTime1 = golsTime1;
    partida->golsTime2 = golsTime2;
    
    return partida;
}

void liberarPartida(Partida *partida) {
    free(partida);
}

/* === GETTERS === */

int obterIdPartida(Partida *partida) {
    return partida->id;
}

int obterTime1Partida(Partida *partida) {
    return partida->time1;
}

int obterTime2Partida(Partida *partida) {
    return partida->time2;
}

int obterGolsTime1Partida(Partida *partida) {
    return partida->golsTime1;
}

int obterGolsTime2Partida(Partida *partida) {
    return partida->golsTime2;
}

/* === FUNCOES UTILITARIAS === */

void imprimirPartida(Partida *partida) {
    printf("%d %d %d %d x %d\n",
           partida->id,
           partida->time1,
           partida->time2,
           partida->golsTime1,
           partida->golsTime2);
}

