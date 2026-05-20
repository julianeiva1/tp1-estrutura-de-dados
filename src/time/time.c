#include <stdio.h>
#include <string.h>
#include "time.h"

void inicializarTime(Time *time, int id, const char *nome) {
    time->id = id;
    strncpy(time->nome, nome, TAM_NOME_TIME);
    time->nome[TAM_NOME_TIME - 1] = '\0';

    time->vitorias = 0;
    time->empates = 0;
    time->derrotas = 0;
    time->golsMarcados = 0;
    time->golsSofridos = 0;
}

int calcularSaldoGols(Time time) {
    return time.golsMarcados - time.golsSofridos;
}

int calcularPontos(Time time) {
    return (time.vitorias * 3) + time.empates;
}

void imprimirTime(Time time) {
    printf("%d %-15s %d %d %d %d %d %d %d\n",
           time.id,
           time.nome,
           time.vitorias,
           time.empates,
           time.derrotas,
           time.golsMarcados,
           time.golsSofridos,
           calcularSaldoGols(time),
           calcularPontos(time));
}

