CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = campeonato

OBJ = main.o time.o partida.o bd_time.o bd_partida.o menu.o

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

main.o: main.c bd_time.h bd_partida.h menu.h
	$(CC) $(CFLAGS) -c main.c

time.o: time.c time.h
	$(CC) $(CFLAGS) -c time.c

partida.o: partida.c partida.h
	$(CC) $(CFLAGS) -c partida.c

bd_time.o: bd_time.c bd_time.h time.h bd_partida.h partida.h
	$(CC) $(CFLAGS) -c bd_time.c

bd_partida.o: bd_partida.c bd_partida.h partida.h
	$(CC) $(CFLAGS) -c bd_partida.c

menu.o: menu.c menu.h bd_time.h bd_partida.h time.h partida.h
	$(CC) $(CFLAGS) -c menu.c

clean:
	rm -f *.o $(TARGET)