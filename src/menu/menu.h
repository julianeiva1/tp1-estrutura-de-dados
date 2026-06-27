#ifndef MENU_H
#define MENU_H

#include "bd_time.h"
#include "bd_partida.h"

/* Códigos de cor ANSI para terminal */
#define COR_VERDE "\033[32m"
#define COR_VERMELHA "\033[31m"
#define COR_RESET "\033[0m"

/* Busca o nome de um time pelo seu ID */
char *buscarNomeTime(BDTimes *bd, int id);

/* Consulta times por prefixo do nome (busca case-insensitive) */
void consultarTime(BDTimes *bd);

/*
 * Consulta partidas com tres modos:
 * 1 - por time mandante
 * 2 - por time visitante
 * 3 - por qualquer um dos dois times
 */
void consultarPartidas(BDTimes *bd, BDPartidas *bdPartidas);

/* Atualiza uma partida existente, recalculando estatisticas e persistindo os dados */
void atualizarPartida(BDTimes *bd, BDPartidas *bdPartidas);

/* Remove uma partida existente, com confirmacao, recalculando estatisticas e persistindo os dados */
void removerPartida(BDTimes *bd, BDPartidas *bdPartidas);

/* Insere uma nova partida com ID automatico, validando os dados e persistindo */
void inserirPartida(BDTimes *bd, BDPartidas *bdPartidas);

/* Imprime tabela de classificacao com todos os times e suas estatisticas */
void imprimirClassificacao(BDTimes *bd, BDPartidas *bdPartidas);

/* Persiste os dados em CSV para partidas e classificacao */
void salvarDadosPersistidos(BDTimes *bd, BDPartidas *bdPartidas);

#endif