# Campeonato Computacional de Futebol — Parte II

![Linguagem](https://img.shields.io/badge/Linguagem-C-blue.svg)
![Status](https://img.shields.io/badge/Status-Parte%20II-brightgreen.svg)

Este projeto implementa um sistema de gerenciamento de campeonato de futebol em C, com foco em estruturas de dados, encapsulamento e persistência em arquivos CSV.

## Objetivo

O sistema carrega times e partidas, calcula a classificação do campeonato e permite interagir com os dados por meio de um menu no terminal. Na Parte II, foram adicionadas as operações de atualização, remoção e inserção de partidas, além da persistência dos arquivos CSV.

## Funcionalidades principais

O programa oferece as seguintes operações:

- Consultar time;
- Consultar partidas;
- Atualizar partida;
- Remover partida;
- Inserir partida;
- Imprimir classificação.

## Critérios de classificação

A classificação é ordenada de forma decrescente por:

1. Pontos ganhos (PG);
2. Vitórias (V);
3. Saldo de gols (S);
4. ID crescente como desempate final.

Os cálculos usados são:

- $S = GM - GS$
- $PG = 3 \times V + E$

## Estrutura do repositório

```txt
tp1-estrutura-de-dados/
├── Makefile
├── README.md
├── src/
│   ├── main.c
│   ├── time/
│   ├── partida/
│   ├── bd_time/
│   ├── bd_partida/
│   └── menu/
└── data/
    ├── times.csv
    ├── bd_partidas.csv
    ├── bd_classificacao.csv
    ├── partidas_vazio.csv
    ├── partidas_parcial.csv
    └── partidas_completo.csv
```

## TADs do projeto

### Time
Representa um clube do campeonato. Armazena ID, nome e estatísticas acumuladas.

### Partida
Representa uma partida entre dois times, com ID, IDs dos times e gols.

### BDTimes
Gerencia a coleção de times em memória. Usa uma lista simplesmente encadeada de nós alocados dinamicamente.

### BDPartidas
Gerencia a coleção de partidas em memória. Também usa uma lista simplesmente encadeada com nós alocados dinamicamente.

### menu
Responsável por toda a interação com o usuário no terminal, incluindo consultas, edição de partidas e impressão da classificação.

## Encapsulamento

As estruturas internas de Time, Partida, BDTimes e BDPartidas permanecem encapsuladas nos arquivos .c. Os arquivos .h expõem apenas a interface pública.

## Persistência

Os dados são salvos em arquivos CSV:

- data/times.csv: cadastro inicial dos times;
- data/bd_partidas.csv: partidas atuais;
- data/bd_classificacao.csv: classificação ordenada;
- data/partidas_vazio.csv, data/partidas_parcial.csv e data/partidas_completo.csv: cenários de teste.

Sempre que uma partida é inserida, atualizada ou removida, o programa recalcula as estatísticas dos times e atualiza os CSVs.

## Como compilar e executar no Linux

```bash
make
./campeonato
make clean
```

## Exemplo de uso

Ao iniciar, o programa exibe o menu principal:

```txt
Sistema de Gerenciamento de Partidas
1 - Consultar time
2 - Consultar partidas
3 - Atualizar partida
4 - Remover partida
5 - Inserir partida
6 - Imprimir tabela de classificacao
Q - Sair
```

Exemplos de uso:

- Consultar time por prefixo, como `jav`;
- Consultar partidas por time mandante ou visitante;
- Atualizar placar usando `-` para manter o valor anterior;
- Inserir uma nova partida com ID automático;
- Remover uma partida após confirmação.

## Decisões de implementação

- Uso de listas simplesmente encadeadas para armazenar times e partidas;
- Uso de alocação dinâmica para nós e objetos;
- Ordenação temporária com vetor de ponteiros para Times, sem alterar a ordem física da lista;
- Persistência em CSV para partidas e classificação;
- Validação de entradas e confirmação S/N para operações críticas.

## Status

Parte II implementada e validada.

- A opção `6` imprime a tabela de classificação dos times com estatísticas calculadas com base nas partidas carregadas.

- Se for utilizado o arquivo `data/bd_partidas.csv` (padrão), será exibida a classificação com as estatísticas acumuladas:

```txt
Imprimindo classificacao...

ID  Time              V   E   D  GM  GS    S   PG
--------------------------------------------------
0   JAVAlis          13   3   2  58  30   28   42
2   SemCTRL          11   2   5  43  34    9   35
1   ESCorpiões      10   2   6  55  39   16   32
4   PYthons           8   2   8  47  40    7   26
9   REACTivos         8   2   8  34  38   -4   26
5   SeQueLas          7   3   8  50  49    1   24
6   NETunos           7   2   9  48  53   -5   23
3   GOrilas           7   0  11  40  50  -10   21
7   LOOPardos         6   3   9  38  55  -17   21
8   RUSTicos          3   1  14  40  65  -25   10
```

- Se for utilizado o arquivo `data/partidas_vazio.csv`, os times aparecerão com todas as estatísticas zeradas:

```txt
Imprimindo classificacao...

ID  Time              V   E   D  GM  GS    S   PG
--------------------------------------------------
0   JAVAlis           0   0   0   0   0    0    0
1   ESCorpiões        0   0   0   0   0    0    0
2   SemCTRL           0   0   0   0   0    0    0
3   GOrilas           0   0   0   0   0    0    0
4   PYthons           0   0   0   0   0    0    0
5   SeQueLas          0   0   0   0   0    0    0
6   NETunos           0   0   0   0   0    0    0
7   LOOPardos         0   0   0   0   0    0    0
8   RUSTicos          0   0   0   0   0    0    0
9   REACTivos         0   0   0   0   0    0    0
```

- Para testar outro cenário, altere em `src/main.c` o segundo argumento de `carregarPartidasCSV()`, por exemplo para `"data/partidas_vazio.csv"`, `"data/partidas_parcial.csv"` ou `"data/partidas_completo.csv"`.

## Integrantes do Projeto

| Aluno | GitHub |
|-------|--------|
| Julia Neiva | [julianeiva1](https://github.com/julianeiva1) |
| Eduarda Ferrari | [dudaferrari](https://github.com/dudaferrari) |

## Ambiente recomendado

O projeto deve ser desenvolvido e testado preferencialmente em ambiente Linux.

Ambiente de referência indicado no enunciado:

```txt
Ubuntu 22.04
GCC 11
```
