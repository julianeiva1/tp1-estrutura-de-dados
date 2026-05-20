CC = gcc
CFLAGS = -Wall -Wextra -std=c11
IFLAGS = -Isrc/time -Isrc/partida -Isrc/bd_time -Isrc/bd_partida -Isrc/menu

# Diretórios de origem
SRCDIR = src
TIMEDIR = src/time
PARTIDADIR = src/partida
BD_TIMEDIR = src/bd_time
BD_PARTIDADIR = src/bd_partida
MENUDIR = src/menu

# Arquivos objeto
OBJECTS = \
	$(SRCDIR)/main.o \
	$(TIMEDIR)/time.o \
	$(PARTIDADIR)/partida.o \
	$(BD_TIMEDIR)/bd_time.o \
	$(BD_PARTIDADIR)/bd_partida.o \
	$(MENUDIR)/menu.o

# Executável
TARGET = campeonato

# Regra padrão
all: $(TARGET)

# Compilar executável
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

# Compilar main.o
$(SRCDIR)/main.o: $(SRCDIR)/main.c $(BD_TIMEDIR)/bd_time.h $(BD_PARTIDADIR)/bd_partida.h $(MENUDIR)/menu.h
	$(CC) $(CFLAGS) $(IFLAGS) -c $(SRCDIR)/main.c -o $(SRCDIR)/main.o

# Compilar time.o
$(TIMEDIR)/time.o: $(TIMEDIR)/time.c $(TIMEDIR)/time.h
	$(CC) $(CFLAGS) $(IFLAGS) -c $(TIMEDIR)/time.c -o $(TIMEDIR)/time.o

# Compilar partida.o
$(PARTIDADIR)/partida.o: $(PARTIDADIR)/partida.c $(PARTIDADIR)/partida.h
	$(CC) $(CFLAGS) $(IFLAGS) -c $(PARTIDADIR)/partida.c -o $(PARTIDADIR)/partida.o

# Compilar bd_time.o
$(BD_TIMEDIR)/bd_time.o: $(BD_TIMEDIR)/bd_time.c $(BD_TIMEDIR)/bd_time.h $(TIMEDIR)/time.h $(BD_PARTIDADIR)/bd_partida.h $(PARTIDADIR)/partida.h
	$(CC) $(CFLAGS) $(IFLAGS) -c $(BD_TIMEDIR)/bd_time.c -o $(BD_TIMEDIR)/bd_time.o

# Compilar bd_partida.o
$(BD_PARTIDADIR)/bd_partida.o: $(BD_PARTIDADIR)/bd_partida.c $(BD_PARTIDADIR)/bd_partida.h $(PARTIDADIR)/partida.h
	$(CC) $(CFLAGS) $(IFLAGS) -c $(BD_PARTIDADIR)/bd_partida.c -o $(BD_PARTIDADIR)/bd_partida.o

# Compilar menu.o
$(MENUDIR)/menu.o: $(MENUDIR)/menu.c $(MENUDIR)/menu.h $(BD_TIMEDIR)/bd_time.h $(BD_PARTIDADIR)/bd_partida.h $(TIMEDIR)/time.h $(PARTIDADIR)/partida.h
	$(CC) $(CFLAGS) $(IFLAGS) -c $(MENUDIR)/menu.c -o $(MENUDIR)/menu.o

# Limpar arquivos de compilação
clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean