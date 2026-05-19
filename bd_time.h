#ifndef BD_TIME_H
#define BD_TIME_H

#include "time.h"
#include "bd_partida.h"

/* Campeonato possui exatamente 10 times (IDs 0-9) */
#define MAX_TIMES 10

/*
 * TAD BDTimes: Gerenciador da colecao de times em memoria
 * Armazena os times carregados do arquivo CSV
 */
typedef struct {
    Time times[MAX_TIMES];
    int quantidade;
} BDTimes;

/* Inicializa o banco de times (zera quantidade) */
void inicializarBDTimes(BDTimes *bd);

/* Adiciona um time ao banco; retorna 1 se sucesso, 0 se banco cheio */
int adicionarTime(BDTimes *bd, Time time);

/* Busca e retorna ponteiro para um time pelo ID; retorna NULL se nao encontrado */
Time* buscarTimePorId(BDTimes *bd, int id);

/* Carrega todos os times do arquivo CSV times.csv (ignora primeira linha) */
int carregarTimesCSV(BDTimes *bd, const char *nomeArquivo);

/* Imprime todos os times cadastrados com suas estatisticas */
void imprimirTodosTimes(BDTimes *bd);

/*
 * Calcula e atualiza a classificacao de todos os times baseado nas partidas
 * Reseta todas as estatisticas antes de processar as partidas
 * Itera sobre cada partida e atualiza: vitorias, empates, derrotas, gols
 */
void calcularClassificacao(BDTimes *bd, BDPartidas *bdPartidas);

#endif