#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "time.h"

/*
 * Definicao da struct Time 
 */
struct time {
    int id;
    char nome[TAM_NOME_TIME];
    int vitorias;
    int empates;
    int derrotas;
    int golsMarcados;
    int golsSofridos;
};

/* === GERENCIAMENTO DE MEMORIA === */

Time *criarTime(int id, const char *nome) {
    Time *time = (Time *)malloc(sizeof(Time));
    if (time == NULL) {
        return NULL;
    }
    
    time->id = id;
    strncpy(time->nome, nome, TAM_NOME_TIME);
    time->nome[TAM_NOME_TIME - 1] = '\0';
    
    time->vitorias = 0;
    time->empates = 0;
    time->derrotas = 0;
    time->golsMarcados = 0;
    time->golsSofridos = 0;
    
    return time;
}

void liberarTime(Time *time) {
    free(time);
}

/* === GETTERS === */

int obterIdTime(Time *time) {
    return time->id;
}

const char *obterNomeTime(Time *time) {
    return time->nome;
}

int obterVitorias(Time *time) {
    return time->vitorias;
}

int obterEmpates(Time *time) {
    return time->empates;
}

int obterDerrotas(Time *time) {
    return time->derrotas;
}

int obterGolsMarcados(Time *time) {
    return time->golsMarcados;
}

int obterGolsSofridos(Time *time) {
    return time->golsSofridos;
}

/* === SETTERS === */

void zerarEstatisticasTime(Time *time) {
    time->vitorias = 0;
    time->empates = 0;
    time->derrotas = 0;
    time->golsMarcados = 0;
    time->golsSofridos = 0;
}

void adicionarGolsMarcados(Time *time, int gols) {
    time->golsMarcados += gols;
}

void adicionarGolsSofridos(Time *time, int gols) {
    time->golsSofridos += gols;
}

void adicionarVitoria(Time *time) {
    time->vitorias++;
}

void adicionarEmpate(Time *time) {
    time->empates++;
}

void adicionarDerrota(Time *time) {
    time->derrotas++;
}

/* === FUNCOES UTILITARIAS === */

int calcularSaldoGols(Time *time) {
    return time->golsMarcados - time->golsSofridos;
}

int calcularPontos(Time *time) {
    return (time->vitorias * 3) + time->empates;
}

void imprimirCabecalhoTimes(void) {
    printf("ID  %-15s %3s %3s %3s %3s %3s %4s %4s\n", "Time", "V", "E", "D", "GM", "GS", "S", "PG");
    printf("--------------------------------------------------\n");
}

void imprimirTime(Time *time) {
    printf("%-3d %-15s %3d %3d %3d %3d %3d %4d %4d\n",
           time->id,
           time->nome,
           time->vitorias,
           time->empates,
           time->derrotas,
           time->golsMarcados,
           time->golsSofridos,
           calcularSaldoGols(time),
           calcularPontos(time));
}

