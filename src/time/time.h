#ifndef TIME_H
#define TIME_H

#define TAM_NOME_TIME 50

/*
 * TAD Time: Representa um time do campeonato 
 * A definicao completa da struct esta em time.c
 * A interface expoe apenas getters, setters e funcoes utilitarias
 */
typedef struct time Time;

/* Cria e aloca um novo time com ID, nome e estatisticas zeradas */
Time *criarTime(int id, const char *nome);

/* Libera memória alocada para o time */
void liberarTime(Time *time);

/* === GETTERS === */
int obterIdTime(Time *time);
const char *obterNomeTime(Time *time);
int obterVitorias(Time *time);
int obterEmpates(Time *time);
int obterDerrotas(Time *time);
int obterGolsMarcados(Time *time);
int obterGolsSofridos(Time *time);

/* === SETTERS === */
void zerarEstatisticasTime(Time *time);
void adicionarGolsMarcados(Time *time, int gols);
void adicionarGolsSofridos(Time *time, int gols);
void adicionarVitoria(Time *time);
void adicionarEmpate(Time *time);
void adicionarDerrota(Time *time);

/* === FUNCOES UTILITARIAS === */
/* Calcula saldo de gols: gols marcados - gols sofridos */
int calcularSaldoGols(Time *time);
/* Calcula pontos ganhos: vitorias*3 + empates */
int calcularPontos(Time *time);

/* Imprime as estatisticas do time em uma linha formatada */
void imprimirTime(Time *time);

#endif

