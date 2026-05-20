# Campeonato Computacional de Futebol — Parte I

![Linguagem](https://img.shields.io/badge/Linguagem-C-blue.svg)
![Status](https://img.shields.io/badge/Status-Concluido-brightgreen.svg)

Trabalho prático de Programação em C desenvolvido para a Disciplina de Estrutura de Dados do Instituto Federal do Espírito Santo — Campus Serra.

O objetivo do projeto é implementar um sistema simplificado para gerenciamento de dados de um campeonato computacional de futebol, utilizando arquivos CSV como forma de persistência e estruturas de dados em memória para consulta e processamento das informações.

## Objetivo

O sistema deve carregar dados de times e partidas a partir de arquivos CSV e permitir a consulta dessas informações por meio de um menu interativo no terminal.

Nesta primeira parte do trabalho, devem ser implementadas as seguintes funcionalidades:

- Consultar time;
- Consultar partidas;
- Imprimir tabela de classificação;
- Encerrar o sistema.

As funcionalidades de inserir, atualizar e remover partidas aparecem no menu, mas permanecem desabilitadas nesta etapa do projeto.

## Campeonato

O campeonato é composto por 10 clubes, identificados por IDs de 0 a 9:

| ID | Time |
|---:|------|
| 0 | JAVAlis |
| 1 | ESCorpiões |
| 2 | SemCTRL |
| 3 | GOrilas |
| 4 | PYthons |
| 5 | SeQueLas |
| 6 | NETunos |
| 7 | LOOPardos |
| 8 | RUSTicos |
| 9 | REACTivos |

A competição é disputada em pontos corridos, com 90 partidas registradas no arquivo padrão da entrega.

## Critérios da tabela de classificação

A classificação dos times considera os seguintes dados:

| Sigla | Descrição |
|------|-----------|
| V | Vitórias |
| E | Empates |
| D | Derrotas |
| GM | Gols marcados |
| GS | Gols sofridos |
| S | Saldo de gols |
| PG | Pontos ganhos |

O saldo de gols é calculado por:

```txt
S = GM - GS
```

Os pontos ganhos são calculados por:

```txt
PG = 3 * V + E
```

## Funcionalidades do sistema

### 1. Consultar time

Permite buscar um ou mais times a partir do nome ou prefixo informado pelo usuário.

A busca por prefixo ignora diferenças entre letras maiúsculas e minúsculas. Por exemplo, `j`, `J`, `jav` e `JAV` encontram o time `JAVAlis`.

A consulta deve exibir os dados de desempenho do time:

```txt
ID Time V E D GM GS S PG
```

Caso nenhum time seja encontrado, o sistema deve exibir uma mensagem informativa.

### 2. Consultar partidas

Permite consultar partidas utilizando o nome do time mandante, do time visitante ou de ambos.

Os modos de consulta previstos são:

```txt
1 - Por time mandante
2 - Por time visitante
3 - Por time mandante ou visitante
4 - Retornar ao menu principal
```

O sistema deve exibir as partidas correspondentes ao critério informado. A busca também ignora diferenças entre maiúsculas e minúsculas.

### 3. Imprimir tabela de classificação

Imprime todos os times cadastrados com suas estatísticas acumuladas, calculadas com base nas partidas carregadas.

Nesta primeira parte do trabalho, a tabela não precisa ser ordenada por pontuação. A impressão segue a ordem dos IDs dos times.

### 4. Sair

Encerra a execução do sistema. O programa só encerra quando o usuário digita exatamente `q` ou `Q`.

## Funcionalidades desabilitadas nesta etapa

As opções abaixo aparecem no menu, mas não são implementadas nesta primeira parte:

```txt
3 - Atualizar partida
4 - Remover partida
5 - Inserir partida
```

Essas funcionalidades serão tratadas em uma etapa futura do trabalho.

## Estrutura do projeto

Estrutura do projeto:

```txt
tp1-estrutura-de-dados/
│
├── README.md
├── Makefile
│
├── src/
│   ├── main.c
│   │
│   ├── time/
│   │   ├── time.h
│   │   └── time.c
│   │
│   ├── partida/
│   │   ├── partida.h
│   │   └── partida.c
│   │
│   ├── bd_time/
│   │   ├── bd_time.h
│   │   └── bd_time.c
│   │
│   ├── bd_partida/
│   │   ├── bd_partida.h
│   │   └── bd_partida.c
│   │
│   └── menu/
│       ├── menu.h
│       └── menu.c
│
└── data/
    ├── times.csv
    ├── bd_partidas.csv          (criado para entrega)
    ├── partidas_vazio.csv       (fornecido pelo professor)
    ├── partidas_parcial.csv     (fornecido pelo professor)
    └── partidas_completo.csv    (fornecido pelo professor)
```

**Sobre a organização:**

- `src/` — contém todo o código-fonte, organizado por módulo (TAD)
- `data/` — contém todos os arquivos CSV

**Sobre os arquivos CSV:**

- `data/times.csv` — fornecido pelo professor
- `data/bd_partidas.csv` — criado para a entrega com todas as 90 partidas
- `data/partidas_vazio.csv`, `data/partidas_parcial.csv`, `data/partidas_completo.csv` — fornecidos pelo professor como cenários de teste

## TADs utilizados

### TAD Time

Representa uma equipe do campeonato.

Armazena:

- ID;
- Nome;
- Vitórias;
- Empates;
- Derrotas;
- Gols marcados;
- Gols sofridos.

Também possui funções para:

- Inicializar um time;
- Calcular saldo de gols;
- Calcular pontos ganhos;
- Imprimir os dados do time.

O saldo de gols e os pontos ganhos são calculados a partir dos dados acumulados:

```txt
Saldo = gols marcados - gols sofridos
Pontos = 3 * vitórias + empates
```

### TAD BDTimes

Gerencia a coleção de times carregados do arquivo CSV.

Responsabilidades implementadas:

- Inicializar o banco de times em memória;
- Adicionar um time ao vetor de times;
- Buscar um time por ID;
- Carregar os times a partir do arquivo `times.csv`;
- Imprimir todos os times carregados;
- Calcular a classificação com base nas partidas carregadas.

A estrutura utiliza um vetor estático com capacidade para 10 times, pois o campeonato possui exatamente 10 clubes.

### TAD Partida

Representa uma partida do campeonato.

Armazena:

- ID da partida;
- ID do Time1;
- ID do Time2;
- Gols do Time1;
- Gols do Time2.

Também possui funções para:

- Inicializar uma partida;
- Imprimir os dados de uma partida.

### TAD BDPartidas

Gerencia a coleção de partidas carregadas dos arquivos CSV.

Responsabilidades implementadas:

- Carregar partidas do arquivo CSV;
- Armazenar partidas em memória;
- Consultar partidas por ID;
- Imprimir todas as partidas;
- Tratamento de quebras de linha ao carregar os registros do CSV.

A estrutura utiliza um vetor estático com capacidade para 100 partidas.

### Função calcularClassificacao

Implementada em `bd_time.c`, esta função:

- Percorre todas as partidas carregadas;
- Atualiza vitórias, empates e derrotas para cada time;
- Atualiza gols marcados e gols sofridos;
- Reseta as estatísticas antes do cálculo (garantindo consistência);
- Permite a impressão da tabela de classificação com dados atualizados.

### Módulo menu

Implementado em `menu.c` e `menu.h`, fornece todas as funcionalidades de interação com o usuário:

- `consultarTime()` — busca times por prefixo;
- `consultarPartidas()` — submenu para busca de partidas (mandante, visitante, ambos);
- `imprimirClassificacao()` — exibe tabela de classificação atualizada;
- `atualizarPartida()`, `removerPartida()`, `inserirPartida()` — stubs com mensagem de "não implementado";

## Arquivos CSV

O sistema utiliza arquivos CSV para simular um banco de dados.

Os arquivos de dados seguem o formato indicado no enunciado. O arquivo de times contém os IDs e nomes dos clubes, enquanto os arquivos de partidas contêm os IDs dos times envolvidos e os respectivos gols.

### Arquivo de times

Arquivo utilizado:

```txt
times.csv
```

Formato:

```csv
ID,Time
0,JAVAlis
1,ESCorpiões
2,SemCTRL
```

A primeira linha é o cabeçalho e é ignorada durante a leitura.

### Arquivos de partidas

O arquivo padrão carregado pelo sistema é **`bd_partidas.csv`**, criado para esta entrega, contendo todas as 90 partidas do campeonato.

Os arquivos `partidas_vazio.csv`, `partidas_parcial.csv` e `partidas_completo.csv` foram fornecidos pelo professor e foram mantidos conforme recebidos. Eles servem como cenários de teste alternativos:

```txt
bd_partidas.csv          (90 partidas) — arquivo padrão da entrega (criado para esta Parte I)
partidas_vazio.csv       (0 partidas)  — cenário de teste fornecido pelo professor
partidas_parcial.csv     (45 partidas) — cenário de teste fornecido pelo professor
partidas_completo.csv    (90 partidas) — cenário de teste fornecido pelo professor
```

**Formato dos arquivos:**

Todos os arquivos de partidas seguem o mesmo formato CSV:

```csv
ID,Time1ID,Time2ID,GolsTime1,GolsTime2
0,5,7,4,1
1,9,1,2,5
```

O programa ignora a primeira linha do CSV (cabeçalho), portanto os nomes exatos das colunas não interferem na leitura dos dados. A interpretação é feita pela ordem: ID (primeiro), Time1 mandante (segundo), Time2 visitante (terceiro), gols Time1 (quarto), gols Time2 (quinto).

**Como usar arquivos diferentes:**

Para testar outro cenário, altere em `src/main.c` a chamada da função `carregarPartidasCSV()`, substituindo `data/bd_partidas.csv` pelo arquivo desejado, por exemplo: `data/partidas_vazio.csv`, `data/partidas_parcial.csv` ou `data/partidas_completo.csv`.

## Como compilar e executar no Linux

No terminal, dentro da pasta do projeto, compile com:

```bash
make
```

Depois execute:

```bash
./campeonato
```

Para remover os arquivos de compilação (`.o`) e o executável gerado:

```bash
make clean
```

## Como compilar e executar no Windows pelo CMD

Para executar pelo Prompt de Comando do Windows, é necessário ter o GCC instalado e configurado no PATH, por exemplo por meio do MinGW ou MSYS2.

No CMD, dentro da pasta do projeto, compile com:

```cmd
gcc -Wall -Wextra -std=c11 -I src/time -I src/partida -I src/bd_time -I src/bd_partida -I src/menu -o campeonato.exe src/main.c src/time/time.c src/partida/partida.c src/bd_time/bd_time.c src/bd_partida/bd_partida.c src/menu/menu.c
```

Depois execute:

```cmd
campeonato.exe
```

Observação: o `Makefile` foi preparado para ambiente Linux. No Windows, recomenda-se usar o comando `gcc` acima diretamente no CMD, ou executar o `make` por um ambiente compatível, como Git Bash, MSYS2 ou WSL.

## Exemplo de uso

Ao executar o programa, será exibido o menu:

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

### Opção 6 — Tabela de classificação

- A opção `6` imprime a tabela de classificação dos times com estatísticas calculadas com base nas partidas carregadas.

- Se for utilizado o arquivo `bd_partidas.csv` (padrão), será exibida a classificação com as estatísticas acumuladas:

```txt
Imprimindo classificacao...

ID Time V E D GM GS S PG
0 JAVAlis         13 3 2 58 30 28 42
1 ESCorpiões     10 2 6 55 39 16 32
2 SemCTRL         11 2 5 43 34 9 35
3 GOrilas         7 0 11 40 50 -10 21
4 PYthons         8 2 8 47 40 7 26
5 SeQueLas        7 3 8 50 49 1 24
6 NETunos         7 2 9 48 53 -5 23
7 LOOPardos       6 3 9 38 55 -17 21
8 RUSTicos        3 1 14 40 65 -25 10
9 REACTivos       8 2 8 34 38 -4 26
```

- Se for utilizado o arquivo `partidas_vazio.csv`, os times aparecerão com todas as estatísticas zeradas:

```txt
Imprimindo classificacao...

ID Time V E D GM GS S PG
0 JAVAlis         0 0 0 0 0 0 0
1 ESCorpiões      0 0 0 0 0 0 0
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

## Decisões de implementação

As principais decisões de implementação tomadas até o momento são:

- Utilizar linguagem C;
- Organizar o código em módulos;
- Manter o programa principal em `main.c`;
- Representar times e partidas por meio de `structs`;
- Utilizar TADs para separar responsabilidades;
- Separar cada TAD em um arquivo `.h` e um arquivo `.c`;
- Utilizar arquivos CSV como fonte de dados;
- Ignorar o cabeçalho dos arquivos CSV durante a leitura;
- Utilizar vetor estático para armazenar os times, pois o campeonato possui 10 clubes;
- Utilizar os campos `time1` e `time2` na estrutura de partidas para armazenar os IDs dos times, conforme os campos `Time1ID` e `Time2ID` dos arquivos CSV;
- Calcular saldo de gols e pontos ganhos por meio de funções próprias do TAD `Time`;
- Manter as opções de inserção, atualização e remoção desabilitadas nesta primeira etapa.

## Status atual

**Projeto completo — Parte I implementada com sucesso.**

### Funcionalidades implementadas:

- Menu principal com todas as opções;
- Leitura da opção do usuário;
- Encerramento do sistema (apenas com `q` ou `Q`);
- Opções 3, 4 e 5 desabilitadas (com mensagem "não implementada nesta versão");
- TAD `Time`;
- TAD `Partida`;
- TAD `BDTimes`;
- TAD `BDPartidas`;
- Leitura do arquivo `times.csv`;
- Leitura do arquivo de partidas configurado no `main.c`, atualmente `bd_partidas.csv` (90 partidas);
- Cálculo da classificação com base nas partidas (`calcularClassificacao()`);
- Consulta de time por prefixo (case-insensitive);
- Consulta de partidas (mandante, visitante, ambos);
- Impressão da tabela de classificação com estatísticas atualizadas;
- Integração completa das funcionalidades ao menu;
- Makefile com compilação modularizada;
- Leitura e exibição dos nomes dos times, incluindo acentos, quando os arquivos e o terminal utilizam codificação compatível;
- Testes com os três cenários de partidas (vazio, parcial, completo).

### Observações sobre a implementação:

- A tabela de classificação segue a ordem dos IDs dos times conforme especificado para a Parte I;
- O arquivo de partidas padrão utilizado é `data/bd_partidas.csv` (90 partidas). Para usar outro arquivo, edite a chamada de `carregarPartidasCSV()` em `src/main.c`, substituindo `"data/bd_partidas.csv"` pelo arquivo desejado (por exemplo: `"data/partidas_vazio.csv"`);
- Cenários de teste estão disponíveis na pasta `data/`:
  - `data/bd_partidas.csv` — arquivo padrão da entrega com 90 partidas
  - `data/partidas_vazio.csv` — arquivo sem partidas (testa tabela zerada)
  - `data/partidas_parcial.csv` — arquivo com 45 partidas (testa campeonato parcial)
  - `data/partidas_completo.csv` — arquivo com 90 partidas (cenário de teste alternativo)
- A busca por prefixo no módulo menu ignora diferenças entre maiúsculas e minúsculas;
- O programa foi testado em ambiente Linux com GCC 11 e está livre de warnings, erros de segmentação e problemas de leitura de CSV;
- Os nomes dos times, incluindo acentos, são lidos e exibidos corretamente quando os arquivos e o terminal utilizam codificação compatível;
