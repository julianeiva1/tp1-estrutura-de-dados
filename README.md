# Campeonato Computacional de Futebol — Parte I

Trabalho pratico de Programacao em C desenvolvido para o Instituto Federal do Espirito Santo — Campus Serra.

O objetivo do projeto e implementar um sistema simplificado para gerenciamento de dados de um campeonato computacional de futebol, utilizando arquivos CSV como forma de persistencia e estruturas de dados em memoria para consulta e processamento das informacoes.

## Objetivo

O sistema deve carregar dados de times e partidas a partir de arquivos CSV e permitir a consulta dessas informacoes por meio de um menu interativo no terminal.

Nesta primeira parte do trabalho, devem ser implementadas as seguintes funcionalidades:

- Consultar time;
- Consultar partidas;
- Imprimir tabela de classificacao;
- Encerrar o sistema.

As funcionalidades de inserir, atualizar e remover partidas aparecem no menu, mas permanecem desabilitadas nesta etapa do projeto.

## Campeonato

O campeonato e composto por 10 clubes, identificados por IDs de 0 a 9:

| ID | Time |
|---:|------|
| 0 | JAVAlis |
| 1 | ESCorpioes |
| 2 | SemCTRL |
| 3 | GOrilas |
| 4 | PYthons |
| 5 | SeQueLas |
| 6 | NETunos |
| 7 | LOOPardos |
| 8 | RUSTicos |
| 9 | REACTivos |

A competicao e disputada em pontos corridos, com 90 partidas registradas no arquivo padrao da entrega.

## Criterios da tabela de classificacao

A classificacao dos times considera os seguintes dados:

| Sigla | Descricao |
|------|-----------|
| V | Vitorias |
| E | Empates |
| D | Derrotas |
| GM | Gols marcados |
| GS | Gols sofridos |
| S | Saldo de gols |
| PG | Pontos ganhos |

O saldo de gols e calculado por:

```txt
S = GM - GS
```

Os pontos ganhos sao calculados por:

```txt
PG = 3 * V + E
```

## Funcionalidades do sistema

### 1. Consultar time

Permite buscar um ou mais times a partir do nome ou prefixo informado pelo usuario.

A consulta deve exibir os dados de desempenho do time:

```txt
ID Time V E D GM GS S PG
```

Caso nenhum time seja encontrado, o sistema deve exibir uma mensagem informativa.

### 2. Consultar partidas

Permite consultar partidas utilizando o nome do time mandante, do time visitante ou de ambos.

Os modos de consulta previstos sao:

```txt
1 - Por time mandante
2 - Por time visitante
3 - Por time mandante ou visitante
4 - Retornar ao menu principal
```

O sistema deve exibir as partidas correspondentes ao criterio informado.

### 3. Imprimir tabela de classificacao

Imprime todos os times cadastrados com suas estatisticas acumuladas, calculadas com base nas partidas carregadas.

Nesta primeira parte do trabalho, a tabela nao precisa ser ordenada por pontuacao. A impressao segue a ordem dos IDs dos times.

### 4. Sair

Encerra a execucao do sistema.

## Funcionalidades desabilitadas nesta etapa

As opcoes abaixo aparecem no menu, mas nao sao implementadas nesta primeira parte:

```txt
3 - Atualizar partida
4 - Remover partida
5 - Inserir partida
```

Essas funcionalidades serao tratadas em uma etapa futura do trabalho.

## Estrutura do projeto

Estrutura do projeto:

```txt
tp1-campeonato-futebol-c/
│
├── main.c
├── Makefile
├── README.md
│
├── time.h
├── time.c
│
├── partida.h
├── partida.c
│
├── bd_time.h
├── bd_time.c
│
├── bd_partida.h
├── bd_partida.c
│
├── menu.h
├── menu.c
│
├── times.csv
├── bd_partidas.csv          (criado para entrega)
├── partidas_vazio.csv       (fornecido pelo professor)
├── partidas_parcial.csv     (fornecido pelo professor)
└── partidas_completo.csv    (fornecido pelo professor)
```

**Sobre os arquivos CSV:**

- `times.csv` — fornecido pelo professor
- `bd_partidas.csv` — criado para a entrega com todas as 90 partidas
- `partidas_vazio.csv`, `partidas_parcial.csv`, `partidas_completo.csv` — fornecidos pelo professor como cenarios de teste

## TADs utilizados

### TAD Time

Representa uma equipe do campeonato.

Armazena:

- ID;
- Nome;
- Vitorias;
- Empates;
- Derrotas;
- Gols marcados;
- Gols sofridos.

Tambem possui funcoes para:

- Inicializar um time;
- Calcular saldo de gols;
- Calcular pontos ganhos;
- Imprimir os dados do time.

O saldo de gols e os pontos ganhos sao calculados a partir dos dados acumulados:

```txt
Saldo = gols marcados - gols sofridos
Pontos = 3 * vitorias + empates
```

### TAD BDTimes

Gerencia a colecao de times carregados do arquivo CSV.

Responsabilidades implementadas:

- Inicializar o banco de times em memoria;
- Adicionar um time ao vetor de times;
- Buscar um time por ID;
- Carregar os times a partir do arquivo `times.csv`;
- Imprimir todos os times carregados;
- Calcular a classificacao com base nas partidas carregadas.

A estrutura utiliza um vetor estatico com capacidade para 10 times, pois o campeonato possui exatamente 10 clubes.

### TAD Partida

Representa uma partida do campeonato.

Armazena:

- ID da partida;
- ID do Time1;
- ID do Time2;
- Gols do Time1;
- Gols do Time2.

Tambem possui funcoes para:

- Inicializar uma partida;
- Imprimir os dados de uma partida.

### TAD BDPartidas

Gerencia a colecao de partidas carregadas dos arquivos CSV.

Responsabilidades implementadas:

- Carregar partidas do arquivo CSV;
- Armazenar partidas em memoria;
- Consultar partidas por ID;
- Imprimir todas as partidas;
- Tratamento de quebras de linha ao carregar os registros do CSV.

A estrutura utiliza um vetor estatico com capacidade para 100 partidas.

### Funcao calcularClassificacao

Implementada em `bd_time.c`, esta funcao:

- Percorre todas as partidas carregadas;
- Atualiza vitorias, empates e derrotas para cada time;
- Atualiza gols marcados e gols sofridos;
- Reseta as estatisticas antes do calculo (garantindo consistencia);
- Permite a impressao da tabela de classificacao com dados atualizados.

### Modulo menu

Implementado em `menu.c` e `menu.h`, fornece todas as funcionalidades de interacao com o usuario:

- `consultarTime()` — busca times por prefixo;
- `consultarPartidas()` — submenu para busca de partidas (mandante, visitante, ambos);
- `imprimirClassificacao()` — exibe tabela de classificacao atualizada;
- `atualizarPartida()`, `removerPartida()`, `inserirPartida()` — stubs com mensagem de "nao implementado";

## Arquivos CSV

O sistema utiliza arquivos CSV para simular um banco de dados.

Os arquivos de dados seguem o formato indicado no enunciado. O arquivo de times contem os IDs e nomes dos clubes, enquanto os arquivos de partidas contem os IDs dos times envolvidos e os respectivos gols.

### Arquivo de times

Arquivo utilizado:

```txt
times.csv
```

Formato:

```csv
ID,Time
0,JAVAlis
1,ESCorpioes
2,SemCTRL
```

A primeira linha e o cabecalho e e ignorada durante a leitura.

### Arquivos de partidas

O arquivo padrao carregado pelo sistema e **`bd_partidas.csv`**, criado para esta entrega, contendo todas as 90 partidas do campeonato.

Os arquivos `partidas_vazio.csv`, `partidas_parcial.csv` e `partidas_completo.csv` foram fornecidos pelo professor e foram mantidos conforme recebidos. Eles servem como cenarios de teste alternativos:

```txt
bd_partidas.csv          (90 partidas) — arquivo padrao da entrega (criado para esta Parte I)
partidas_vazio.csv       (0 partidas)  — cenario de teste fornecido pelo professor
partidas_parcial.csv     (45 partidas) — cenario de teste fornecido pelo professor
partidas_completo.csv    (90 partidas) — cenario de teste fornecido pelo professor
```

**Formato dos arquivos:**

Todos os arquivos de partidas seguem o mesmo formato CSV:

```csv
ID,Time1ID,Time2ID,GolsTime1,GolsTime2
0,5,7,4,1
1,9,1,2,5
```

O programa ignora a primeira linha do CSV (cabecalho), portanto os nomes exatos das colunas nao interferem na leitura dos dados. A interpretacao e feita pela ordem: ID (primeiro), Time1 mandante (segundo), Time2 visitante (terceiro), gols Time1 (quarto), gols Time2 (quinto).

**Como usar arquivos diferentes:**

Para testar outro cenario, altere em `main.c` a chamada da funcao `carregarPartidasCSV()`, substituindo `bd_partidas.csv` pelo arquivo desejado.

## Como compilar

Para compilar o projeto, execute no terminal:

```bash
make
```

Esse comando gera o executavel:

```txt
campeonato
```

## Como executar

Apos compilar, execute:

```bash
./campeonato
```

## Como limpar os arquivos de compilacao

Para remover os arquivos `.o` e o executavel gerado, execute:

```bash
make clean
```

## Exemplo de uso

Ao executar o programa, sera exibido o menu:

```txt
Sistema de Gerenciamento de Partidas
1 - Consultar time
2 - Consultar partidas
3 - Atualizar partida
4 - Remover partida
5 - Inserir partida
6 - Imprimir tabela de classificacao
Q - Sair

Escolha uma opcao: 
```

### Opcao 6 — Tabela de classificacao

- A opcao `6` imprime a tabela de classificacao dos times com estatisticas calculadas com base nas partidas carregadas.

- Se for utilizado o arquivo `bd_partidas.csv` (padrao), sera exibida a classificacao com as estatisticas acumuladas:

```txt
Imprimindo classificacao...

ID Time V E D GM GS S PG
0 JAVAlis         13 3 2 58 30 28 42
1 ESCorpioes     10 2 6 55 39 16 32
2 SemCTRL         11 2 5 43 34 9 35
3 GOrilas         7 0 11 40 50 -10 21
4 PYthons         8 2 8 47 40 7 26
5 SeQueLas        7 3 8 50 49 1 24
6 NETunos         7 2 9 48 53 -5 23
7 LOOPardos       6 3 9 38 55 -17 21
8 RUSTicos        3 1 14 40 65 -25 10
9 REACTivos       8 2 8 34 38 -4 26
```

- Se for utilizado o arquivo `partidas_vazio.csv`, os times aparecerao com todas as estatisticas zeradas:

```txt
Imprimindo classificacao...

ID Time V E D GM GS S PG
0 JAVAlis         0 0 0 0 0 0 0
1 ESCorpioes      0 0 0 0 0 0 0
2 SemCTRL         0 0 0 0 0 0 0
3 GOrilas         0 0 0 0 0 0 0
4 PYthons         0 0 0 0 0 0 0
5 SeQueLas        0 0 0 0 0 0 0
6 NETunos         0 0 0 0 0 0 0
7 LOOPardos       0 0 0 0 0 0 0
8 RUSTicos        0 0 0 0 0 0 0
9 REACTivos       0 0 0 0 0 0 0
```

- Para usar um arquivo diferente, edite a chamada de `carregarPartidasCSV()` em `main.c`, substituindo `"bd_partidas.csv"` pelo arquivo desejado.

## Ambiente recomendado

O projeto deve ser desenvolvido e testado preferencialmente em ambiente Linux.

Ambiente de referencia indicado no enunciado:

```txt
Ubuntu 22.04
GCC 11
```

## Decisoes de implementacao

As principais decisoes de implementacao tomadas ate o momento sao:

- Utilizar linguagem C;
- Organizar o codigo em modulos;
- Manter o programa principal em `main.c`;
- Representar times e partidas por meio de `structs`;
- Utilizar TADs para separar responsabilidades;
- Separar cada TAD em um arquivo `.h` e um arquivo `.c`;
- Utilizar arquivos CSV como fonte de dados;
- Ignorar o cabecalho dos arquivos CSV durante a leitura;
- Utilizar vetor estatico para armazenar os times, pois o campeonato possui 10 clubes;
- Utilizar os campos `time1` e `time2` na estrutura de partidas para armazenar os IDs dos times, conforme os campos `Time1ID` e `Time2ID` dos arquivos CSV;
- Calcular saldo de gols e pontos ganhos por meio de funcoes proprias do TAD `Time`;
- Manter as opcoes de insercao, atualizacao e remocao desabilitadas nesta primeira etapa.

## Status atual

**Projeto completo — Parte I implementada com sucesso.**

### Funcionalidades implementadas:

- Menu principal com todas as opcoes;
- Leitura da opcao do usuario;
- Encerramento do sistema (Q);
- Opcoes 3, 4 e 5 desabilitadas (com mensagem "nao implementada nesta versao");
- TAD `Time`;
- TAD `Partida`;
- TAD `BDTimes`;
- TAD `BDPartidas`;
- Leitura do arquivo `times.csv`;
- Leitura do arquivo de partidas configurado no `main.c`, atualmente `bd_partidas.csv` (90 partidas);
- Calculo da classificacao com base nas partidas (`calcularClassificacao()`);
- Consulta de time por prefixo;
- Consulta de partidas (mandante, visitante, ambos);
- Impressao da tabela de classificacao com estatisticas atualizadas;
- Integracao completa das funcionalidades ao menu;
- Makefile com compilacao modularizada;
- Leitura e exibicao dos nomes dos times, incluindo acentos, quando os arquivos e o terminal utilizam codificacao compativel;
- Testes com os tres cenarios de partidas (vazio, parcial, completo).

### Observacoes sobre a implementacao:

- A tabela de classificacao segue a ordem dos IDs dos times conforme especificado para a Parte I;
- O arquivo de partidas padrao utilizado e `bd_partidas.csv` (90 partidas). Para usar outro arquivo, edite a chamada de `carregarPartidasCSV()` em `main.c`, substituindo `"bd_partidas.csv"` pelo arquivo desejado;
- Cenarios de teste estao disponiveis:
  - `bd_partidas.csv` — arquivo padrao da entrega com 90 partidas
  - `partidas_vazio.csv` — arquivo sem partidas (testa tabela zerada)
  - `partidas_parcial.csv` — arquivo com 45 partidas (testa campeonato parcial)
  - `partidas_completo.csv` — arquivo com 90 partidas (cenario de teste alternativo)
- O programa foi testado em ambiente Linux com GCC 11 e esta livre de warnings, erros de segmentacao e problemas de leitura de CSV;
- Os nomes dos times, incluindo acentos, sao lidos e exibidos corretamente quando os arquivos e o terminal utilizam codificacao compativel;