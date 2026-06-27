#ifndef BD_PARTIDA_H
#define BD_PARTIDA_H

#include "partida.h"

/* Limite usado como referência para a estrutura interna, sem depender de um vetor fixo. */
#define MAX_PARTIDAS 100

/*
 * TAD BDPartidas: Gerenciador da colecao de partidas em memoria 
 * A definicao completa da struct esta em bd_partida.c
 * Armazena as partidas carregadas do arquivo CSV usando alocacao dinamica
 */
typedef struct bd_partidas BDPartidas;

/* === GERENCIAMENTO DE MEMORIA === */

/* Cria e aloca um novo banco de partidas inicializado */
BDPartidas *criarBDPartidas(void);

/* Libera toda a memória alocada para o banco de partidas */
void liberarBDPartidas(BDPartidas *bd);

/* === INTERFACE PUBLICA === */

/* Adiciona uma partida ao banco; retorna 1 em caso de sucesso e 0 em caso de erro */
int adicionarPartida(BDPartidas *bd, Partida *partida);

/* Remove a partida com o ID informado; retorna 1 se sucesso, 0 se nao encontrada */
int removerPartidaPorId(BDPartidas *bd, int id);

/* Busca e retorna ponteiro para uma partida pelo ID; retorna NULL se nao encontrada */
Partida* buscarPartidaPorId(BDPartidas *bd, int id);

/* Retorna a quantidade de partidas cadastradas */
int obterQuantidadePartidas(BDPartidas *bd);

/* Retorna a partida no indice especificado; retorna NULL se indice invalido */
Partida *obterPartidaPorIndice(BDPartidas *bd, int indice);

/* Carrega todas as partidas do arquivo CSV (ignora primeira linha como cabecalho) */
int carregarPartidasCSV(BDPartidas *bd, const char *nomeArquivo);

/* Imprime todas as partidas carregadas */
void imprimirTodasPartidas(BDPartidas *bd);

#endif