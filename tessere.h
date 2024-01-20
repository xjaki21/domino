/**
 * @file tessere.h
 * @brief File header contenente le funzioni e le strutture per la gestione di una scacchiera di tessere.
 */

#ifndef TESSERE_H
#define TESSERE_H


/**
 * @struct Tessera
 * @brief Struttura che rappresenta una tessera con due numeri (n1 e n2).
 */
typedef struct Tessera{
  int n1;          ///< Primo numero sulla tessera.
  int n2;          ///< Secondo numero sulla tessera.
  bool selected;   ///< Flag che indica se la tessera è selezionata.
  bool vertical;   ///< Flag che indica se la tessera è orientata verticalmente.
  int num;         ///< Flag che indica il numero per l'interfaccia utente, quelli che scelgo da tastiera.
} Tessera;

/**
 * @struct Row
 * @brief Struttura che rappresenta una riga sulla scacchiera di gioco.
 */
typedef struct Row{
  Tessera *tessere; ///< Array di tessere nella riga.
  int capacity;    ///< Capacità dell'array.
  int size;        ///< Numero di tessere attualmente nella riga.
} Row;

/**
 * @brief Crea una nuova riga.
 * @return Un puntatore alla nuova riga creata.
 */
Row *create_row();

/**
 * @brief Estende l'array di tessere in una riga.
 * @param r Puntatore alla riga.
 */
void extend_arr_tessere(Row *r);

/**
 * @brief Crea un array di tessere.
 * @param size Numero di tessere da creare.
 * @return Un puntatore all'array di tessere.
 */
Tessera *create_arr_tessere(int size);

/**
 * @brief Converte una tessera in una rappresentazione stringa.
 * @param tessera La tessera da convertire.
 * @return Una stringa allocata dinamicamente che rappresenta la tessera.
 */
char *string_tessera(Tessera tessera);

/**
 * @brief Verifica se una tessera è una tessera speciale.
 * @param a La tessera da verificare.
 * @return true se la tessera è speciale, false altrimenti.
 */
bool is_special(Tessera a);

/**
 * @brief Verifica se due tessere possono essere abbinate sul lato sinistro.
 * @param a Prima tessera.
 * @param b Seconda tessera.
 * @return true se le tessere possono essere abbinate a sinistra, false altrimenti.
 */
bool match_left(Tessera a, Tessera b);

/**
 * @brief Verifica se due tessere possono essere abbinate sul lato destro.
 * @param a Prima tessera.
 * @param b Seconda tessera.
 * @return true se le tessere possono essere abbinate a destra, false altrimenti.
 */
bool match_right(Tessera a, Tessera b);

/**
 * @brief Genera un array di scelte possibili per posizionare una tessera sulla scacchiera di gioco.
 * @param piano Array di righe che rappresenta la scacchiera di gioco.
 * @param size Dimensione dell'array di righe.
 * @param tessera La tessera da posizionare.
 * @param num_scelte Parametro di output per memorizzare il numero di scelte.
 * @return Un array allocato dinamicamente di interi che rappresenta le scelte.
 */
int *scelte_possibili(Row *piano, int size, Tessera tessera, int *num_scelte);

/**
 * @brief Stampa l'array di scelte per posizionare una tessera.
 * @param m Array di scelte.
 * @param size Dimensione dell'array.
 */
void print_scelte(int *m, int size);

/**
 * @brief Stampa le tessere disponibili e le tessere speciali.
 * @param tessere Array di tessere.
 * @param speciali Array di tessere speciali.
 * @param size_tessere Dimensione dell'array di tessere.
 * @param size_speciali Dimensione dell'array di tessere speciali.
 */
void print_disponibili(Tessera *tessere, Tessera *speciali, int size_tessere, int size_speciali);

/**
 * @brief Trova la dimensione massima tra tutte le righe nella scacchiera di gioco.
 * @param piano Array di righe che rappresenta la scacchiera di gioco.
 * @param size Dimensione dell'array di righe.
 * @return La dimensione massima tra tutte le righe.
 */
int max_row(Row *piano, int size);

/**
 * @brief Stampa lo stato attuale della scacchiera di gioco.
 * @param piano Array di righe che rappresenta la scacchiera di gioco.
 * @param size Dimensione dell'array di righe.
 */
void print_giocate(Row *piano, int size);

/**
 * @brief Rimuove una tessera da un array di tessere.
 * @param tessera Array di tessere.
 * @param size Puntatore alla dimensione dell'array.
 * @param index Indice della tessera da rimuovere.
 * @return Un nuovo array di tessere allocato dinamicamente con la tessera specificata rimossa.
 */
Tessera *remove_tessera(Tessera *tessera, int *size, int index);

/**
 * @brief Posiziona una tessera all'inizio di una riga sulla scacchiera di gioco.
 * @param piano Array di righe che rappresenta la scacchiera di gioco.
 * @param size_piano Puntatore alla dimensione dell'array di righe.
 * @param r Puntatore alla riga in cui posizionare la tessera.
 * @param tessera La tessera da posizionare.
 */
void put_front_tessera(Row *piano, int size_piano, Row *r, Tessera tessera);

/**
 * @brief Posiziona una tessera in una posizione specificata all'interno di una riga sulla scacchiera di gioco.
 * @param r Puntatore alla riga in cui posizionare la tessera.
 * @param tessera La tessera da posizionare.
 * @param pos Posizione in cui posizionare la tessera.
 */
void put_tessera(Row *r, Tessera tessera, int pos);

/**
 * @brief Posiziona una tessera speciale in una posizione specificata all'interno di una riga sulla scacchiera di gioco.
 * @param piano Array di righe che rappresenta la scacchiera di gioco.
 * @param size_piano Puntatore alla dimensione dell'array di righe.
 * @param row Puntatore alla riga in cui posizionare la tessera speciale.
 * @param pos Posizione in cui posizionare la tessera speciale.
 * @param tessera La tessera speciale da posizionare.
 */
void put_tessera_speciale(Row *piano, int size_piano, Row *row, int pos, Tessera tessera);

/**
 * @brief Converte una stringa in un intero.
 * @param s La stringa da convertire.
 * @return Il valore intero ottenuto dalla conversione.
 */
int char_to_int(char *s);

/**
 * @brief Verifica se è possibile posizionare una tessera sulla scacchiera di gioco e la posiziona.
 * @param piano Array di righe che rappresenta la scacchiera di gioco.
 * @param size_piano Puntatore alla dimensione dell'array di righe.
 * @param tessera La tessera da posizionare.
 * @return true se la tessera è stata posizionata con successo, false altrimenti.
 */
bool posiziona_tessera(Row *piano, int *size_piano, Tessera tessera);

#endif // TESSERE_H
