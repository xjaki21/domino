CC=gcc
CFLAGS=-O2 -std=c99 --pedantic -lm

# Usa le variabili per i percorsi dei file sorgente
SOURCE_DIR := .
LIB_DIR := lib

# Cerca i file sorgente nelle cartelle specificate
SOURCES := $(wildcard $(SOURCE_DIR)/*.c) $(wildcard $(LIB_DIR)/*.c)

EXECUTABLE=domino

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	rm -rf $(EXECUTABLE)
	$(CC) $(CFLAGS) $^ -o $@ -lm

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)

