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

/* Stubs para funcionalidades nao implementadas nesta Parte I */
void atualizarPartida(void);
void removerPartida(void);
void inserirPartida(void);

/* Imprime tabela de classificacao com todos os times e suas estatisticas */
void imprimirClassificacao(BDTimes *bd);

#endif