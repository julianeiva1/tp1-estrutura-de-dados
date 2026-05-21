#ifndef BD_TIME_H
#define BD_TIME_H

#include "time.h"

/* Campeonato possui exatamente 10 times (IDs 0-9) */
#define MAX_TIMES 10

/*
 * TAD BDTimes: Gerenciador da colecao de times em memoria 
 * A definicao completa da struct esta em bd_time.c
 * Armazena os times carregados do arquivo CSV usando alocacao dinamica
 */
typedef struct bd_times BDTimes;

/* === GERENCIAMENTO DE MEMORIA === */

/* Cria e aloca um novo banco de times inicializado */
BDTimes *criarBDTimes(void);

/* Libera toda a memória alocada para o banco de times */
void liberarBDTimes(BDTimes *bd);

/* === INTERFACE PUBLICA === */

/* Adiciona um time ao banco; retorna 1 se sucesso, 0 se banco cheio */
int adicionarTime(BDTimes *bd, Time *time);

/* Busca e retorna ponteiro para um time pelo ID; retorna NULL se nao encontrado */
Time* buscarTimePorId(BDTimes *bd, int id);

/* Retorna a quantidade de times cadastrados */
int obterQuantidadeTimes(BDTimes *bd);

/* Retorna o time no indice especificado; retorna NULL se indice invalido */
Time *obterTimePorIndice(BDTimes *bd, int indice);

/* Carrega todos os times do arquivo CSV times.csv (ignora primeira linha) */
int carregarTimesCSV(BDTimes *bd, const char *nomeArquivo);

/* Imprime todos os times cadastrados com suas estatisticas */
void imprimirTodosTimes(BDTimes *bd);

/* Declara BDPartidas aqui para evitar dependencia circular */
typedef struct bd_partidas BDPartidas;

/*
 * Calcula e atualiza a classificacao de todos os times baseado nas partidas
 * Reseta todas as estatisticas antes de processar as partidas
 * Itera sobre cada partida e atualiza: vitorias, empates, derrotas, gols
 */
void calcularClassificacao(BDTimes *bd, BDPartidas *bdPartidas);

#endif