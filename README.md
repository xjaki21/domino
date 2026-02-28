# 🁣 Domino — Simulatore in C

Implementazione del gioco del **Domino** scritta in **C (C99)**, sviluppata come progetto universitario. Il programma è strutturato con codice sorgente nella cartella `source/` e documentazione tecnica nella cartella `docs/`.

---

## Struttura del progetto

```
domino/
├── source/         # Codice sorgente C
├── docs/           # Documentazione tecnica
├── relazione.pdf   # Relazione del progetto
├── Makefile        # Script di compilazione
└── README.md
```

---

## Tecnologie utilizzate

- **Linguaggio:** C (standard C99)
- **Build system:** Make
- **Librerie:** libm (matematica standard)

---

## Compilazione

### Con Make (consigliato)

```bash
make
```

### Manuale con GCC

```bash
gcc -O2 -std=c99 --pedantic *.c -o iap -lm
```

> L'eseguibile generato si chiama **`iap`**.

---

## Utilizzo

Dopo la compilazione, esegui il programma con:

```bash
./iap
```

---

## Pulizia dei file compilati

Per rimuovere l'eseguibile e i file oggetto generati:

```bash
make clean
```

---

## Prerequisiti

- **GCC** (versione compatibile con C99 o superiore)
- **Make**

Su sistemi Debian/Ubuntu:

```bash
sudo apt install build-essential
```

Su macOS (con Homebrew):

```bash
brew install gcc make
```

---

## Documentazione

La relazione tecnica completa del progetto è disponibile nel file [`relazione.pdf`](./relazione.pdf), mentre la documentazione aggiuntiva si trova nella cartella [`docs/`](./docs/).

---

> Sviluppato da [xjaki21](https://github.com/xjaki21)
