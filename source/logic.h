/**
 * @file logic.h
 * @brief Dichiarazioni delle funzioni per la logica del gioco.
 */

#ifndef LOGIC_H
#define LOGIC_H

#include "tessere.h"

#ifdef _WIN32
    #define CLEAR_SCREEN "cls" // Comando per pulire lo schermo (WINDOWS).
#else
    #define CLEAR_SCREEN "clear" // Comando per pulire lo schermo (LINUX).
#endif

/**
 * @brief Inizializza le tessere speciali con valori specifici, consentendo il corretto funzionamento del gioco.
 * @param speciali Array di tessere speciali da inizializzare.
 * @param size Dimensione dell'array di tessere speciali.
 */
void init_speciali(Tessera *speciali, int size);

/**
 * @brief Inizializza le tessere normali assegnando a ciascuna una coppia di numeri casuali compresi tra 1 e 6.
 * @param tessera Array di tessere normali da inizializzare.
 * @param size_tessere Dimensione dell'array di tessere normali.
 */
void init(Tessera *tessera, int size_tessere);

/**
 * @brief Verifica se la partita è terminata, controllando se è possibile accostare ulteriori tessere sulla scacchiera.
 * @param board Puntatore alla scacchiera di gioco.
 * @param tessere Array di tessere normali.
 * @param size_tessere Dimensione dell'array di tessere normali.
 * @return True se la partita è terminata, False altrimenti.
 */
bool game_finished(Board *board, Tessera *tessere, int size_tessere);

/**
 * @brief Aggiorna lo schermo di gioco stampando il punteggio, le tessere giocate e quelle disponibili.
 * @param board Puntatore alla scacchiera di gioco.
 * @param tessere Array di tessere normali.
 * @param speciali Array di tessere speciali.
 * @param size_tessere Dimensione dell'array di tessere normali.
 * @param size_speciali Dimensione dell'array di tessere speciali.
 */
void update_screen(Board *board, Tessera *tessere, Tessera *speciali, int size_tessere, int size_speciali);

/**
 * @brief Aggiorna il punteggio sommando i valori delle tessere giocate sulla scacchiera.
 * @param board Puntatore alla scacchiera di gioco.
 */
void score_update(Board *board);

/**
 * @brief Avvia una partita in modalità interattiva, consentendo all'utente di selezionare e posizionare le tessere sulla scacchiera.
 * @param board Puntatore alla scacchiera di gioco..
 * @param tessere Array di tessere normali.
 * @param speciali Array di tessere speciali.
 * @param size_tessere Dimensione dell'array di tessere normali.
 * @param size_speciali Dimensione dell'array di tessere speciali.
 */
void game_start(Board *board, Tessera *tessere, Tessera *speciali, int size_tessere, int size_speciali);

/**
 * @brief  Trova la miglior tessera inseribile(quello con il punteggio più alto), se invece non è presente alcuna tessera
 * normale, viene inserita una speciale, quando non c'è più nessun match né tra quelle speicali e né tra quelle normali la partita finisce
 * 
 * @param board Puntatore alla scacchiera di gioco..
 * @param tessere Array di tessere normali.
 * @param speciali Array di tessere speciali.
 * @param size_tessere Dimensione dell'array di tessere normali.
 * @param size_speciali Dimensione dell'array di tessere speciali.
 * @return Puntatore alla scacchiera di gioco con la migliore combinazione.
 */
Board *best_match(Board *board, Tessera *tessere, Tessera *speciali, int size_tessere, int size_speciali);

/**
 * @brief Avvia una partita in modalità intelligenza artificiale.
 * 
 * Creo una scacchiera per ogni tessera di quelle generate all'inizio, per ogni tessera creo una scacchiera  e trovo i best match, confronto tutte le scacchiere trovate per trova quella con più punteggio
 *
 *
 * @param tessere Array di tessere normali.
 * @param speciali Array di tessere speciali.
 * @param size_tessere Dimensione dell'array di tessere normali.
 * @param size_speciali Dimensione dell'array di tessere speciali.
 */
void game_start_ai(Tessera *tessere, Tessera *speciali, int size_tessere, int size_speciali);


#endif // LOGIC_H