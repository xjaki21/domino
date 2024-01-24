CC=gcc
CFLAGS=-O2 -std=c99 --pedantic -lm

# Cerca i file sorgente nelle cartelle specificate
SOURCES := $(wildcard *.c)

EXECUTABLE=iap

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	rm -rf $(EXECUTABLE)
	$(CC) $(CFLAGS) $^ -o $@ -lm

run: $(EXECUTABLE)
	./$(EXECUTABLE)

clean:
	rm -f $(EXECUTABLE)

