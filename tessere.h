/**
 * @file tessere.h
 * @brief File header contenente le funzioni e le strutture per la gestione di una scacchiera di tessere.
 */

#ifndef TESSERE_H
#define TESSERE_H


/**
 * @struct Tessera
 * @brief Rappresenta una tessera con due numeri interi e alcune informazioni aggiuntive.
 */
typedef struct Tessera{
  int n1;        /**< Primo numero della tessera. */
  int n2;        /**< Secondo numero della tessera. */
  int num;       /**< Numero identificativo della tessera. */
  bool selected; /**< Indica se la tessera è stata selezionata. */
  bool vertical; /**< Indica se la tessera è posizionata verticalmente. */
} Tessera;

/**
 * @struct Row
 * @brief Rappresenta una riga della scacchiera di gioco con un array di tessere.
 */
typedef struct Row {
  Tessera *tessere; /**< Array di tessere nella riga. */
  int size;         /**< Numero effettivo di tessere nella riga. */
  int capacity;     /**< Capacità massima dell'array di tessere. */
} Row;

/**
 * @struct Board
 * @brief Rappresenta la scacchiera di gioco con un array di righe.
 */
typedef struct Board {
  Row *rows; /**< Array di righe della scacchiera. */
  int size;  /**< Numero effettivo di righe nella scacchiera. */
  int score; /**< Punteggio del giocatore. */
} Board;

/**
 * @brief Crea una nuova riga della scacchiera.
 * @return Puntatore alla nuova riga creata.
 */
Row *create_row();

/**
 * @brief Crea una nuova scacchiera di gioco.
 * @param max_size Massima dimensione della scacchiera.
 * @return Puntatore alla nuova scacchiera creato.
 */
Board *create_board(int max_size);

/**
 * @brief Dealloca la memoria utilizzata dalla scacchiera di gioco.
 * @param board Puntatore alla scacchiera di gioco da deallocare.
 */
void free_board(Board *board);

/**
 * @brief Copia le tessere da un array a un altro.
 * @param tessere Array di tessere da copiare.
 * @param size_tessere Dimensione dell'array di tessere.
 * @return Puntatore al nuovo array di tessere copiate.
 */
Tessera *copy_tessere(Tessera *tessere, int size_tessere);

/**
 * @brief Copia una intera scacchiera di gioco.
 * @param board Puntatore alla scacchiera da copiare.
 * @return Puntatore alla nuova scacchiera copiato.
 */
Board *copy_board(Board *board);

/**
 * @brief Estende l'array di tessere di una riga se necessario.
 * @param r Puntatore alla riga.
 */
void extend_arr_tessere(Row *r);

/**
 * @brief Crea un nuovo array di tessere con dimensione specificata.
 * @param size Dimensione dell'array di tessere.
 * @return Puntatore al nuovo array di tessere creato.
 */
Tessera *create_arr_tessere(int size);

/**
 * @brief Verifica se una tessera è speciale.
 * @param a Tessera da verificare.
 * @return True se la tessera è speciale, False altrimenti.
 */
bool is_special(Tessera a);

/**
 * @brief Verifica se due tessere possono essere accostate a sinistra.
 * @param a Prima tessera.
 * @param b Seconda tessera.
 * @return True se le tessere possono essere accostate a sinistra, False altrimenti.
 */
bool match_left(Tessera a, Tessera b);

/**
 * @brief Verifica se due tessere possono essere accostate a destra.
 * @param a Prima tessera.
 * @param b Seconda tessera.
 * @return True se le tessere possono essere accostate a destra, False altrimenti.
 */
bool match_right(Tessera a, Tessera b);

/**
 * @brief Restituisce le posizioni possibili per accostare una tessera.
 * @param board Puntatore alla scacchiera di gioco.
 * @param tessera Tessera da accostare.
 * @param num_scelte Puntatore alla variabile che conterrà il numero di scelte possibili.
 * @return Puntatore all'array di posizioni possibili.
 */
int *scelte_possibili(Board *board, Tessera tessera, int *num_scelte);

/**
 * @brief Stampa le scelte possibili per accostare una tessera.
 * @param m Array di posizioni possibili.
 * @param size Dimensione dell'array di posizioni.
 */
void print_scelte(int *m, int size);

/**
 * @brief Stampa le tessere disponibili nella scacchiera di gioco.
 * @param tessere Array di tessere nella scacchiera.
 * @param speciali Array di tessere speciali.
 * @param size_tessere Dimensione dell'array di tessere.
 * @param size_speciali Dimensione dell'array di tessere speciali.
 */
void print_disponibili(Tessera *tessere, Tessera *speciali, int size_tessere, int size_speciali);

/**
 * @brief Restituisce il massimo numero di tessere in una riga della scacchiera.
 * @param board Puntatore alla scacchiera di gioco.
 * @return Massimo numero di tessere in una riga.
 */
int max_row(Board *board);

/**
 * @brief Stampa le tessere giocate nella scacchiera di gioco.
 * @param board Puntatore alla scacchiera di gioco.
 */
void print_giocate(Board *board);

/**
 * @brief Converte una stringa in un intero.
 * @param s Stringa da convertire.
 * @return Valore intero convertito.
 */
int char_to_int(char *s);

/**
 * @brief Rimuove l'elemento n dall'array di tessera.
 * @param tessera Array di tessere.
 * @param size Puntatore alla dimensione dell'array di tessere.
 * @param index Indice dell'elemento da rimuovere.
 * @return Nuovo array di tessere senza l'elemento rimosso.
 */
Tessera *remove_tessera(Tessera *tessera, int *size, int index);

/**
 * @brief Inserisce una tessera all'inizio della riga.
 * @param board Puntatore alla scacchiera di gioco.
 * @param r Puntatore alla riga.
 * @param tessera Tessera da inserire.
 */
void put_front_tessera(Board *board, Row *r, Tessera tessera);

/**
 * @brief Inserisce una tessera in una posizione specifica della riga.
 * @param r Puntatore alla riga.
 * @param tessera Tessera da inserire.
 * @param pos Posizione in cui inserire la tessera.
 */
void put_tessera(Row *r, Tessera tessera, int pos);

/**
 * @brief Inserisce una tessera speciale in una posizione specifica della riga.
 * @param board Puntatore alla scacchiera di gioco.
 * @param row Puntatore alla riga.
 * @param pos Posizione in cui inserire la tessera.
 * @param tessera Tessera speciale da inserire.
 */
void put_tessera_speciale(Board *board, Row *row, int pos, Tessera tessera);

/**
 * @brief Posiziona una tessera nella scacchiera di gioco.
 * @param board Puntatore alla scacchiera di gioco.
 * @param tessera Tessera da posizionare.
 * @return True se la tessera è stata posizionata con successo, False altrimenti.
 */
bool posiziona_tessera(Board *board, Tessera tessera);

#endif  // TESSERE_H
