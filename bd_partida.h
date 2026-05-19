#ifndef BD_PARTIDA_H
#define BD_PARTIDA_H

#include "partida.h"

/* Capacidade para 100 partidas (90 no campeonato + buffer para testes) */
#define MAX_PARTIDAS 100

/*
 * TAD BDPartidas: Gerenciador da colecao de partidas em memoria
 * Armazena as partidas carregadas do arquivo CSV
 */
typedef struct {
    Partida partidas[MAX_PARTIDAS];
    int quantidade;
} BDPartidas;

/* Inicializa o banco de partidas (zera quantidade) */
void inicializarBDPartidas(BDPartidas *bd);

/* Adiciona uma partida ao banco; retorna 1 se sucesso, 0 se banco cheio */
int adicionarPartida(BDPartidas *bd, Partida partida);

/* Busca e retorna ponteiro para uma partida pelo ID; retorna NULL se nao encontrada */
Partida* buscarPartidaPorId(BDPartidas *bd, int id);

/* Carrega todas as partidas do arquivo CSV (ignora primeira linha como cabecalho) */
int carregarPartidasCSV(BDPartidas *bd, const char *nomeArquivo);

/* Imprime todas as partidas carregadas */
void imprimirTodasPartidas(BDPartidas *bd);

#endif