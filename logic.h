/**
 * @file logic.h
 * @brief Dichiarazioni delle funzioni per la logica del gioco.
 */

#ifndef LOGIC_H
#define LOGIC_H

#include "tessere.h"

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

/**
 * @brief Inizializza le tessere speciali.
 * @param speciali Array di tessere speciali da inizializzare.
 * @param size Dimensione dell'array di tessere speciali.
 */
void init_speciali(Tessera *speciali, int size);

/**
 * @brief Inizializza un array di tessere con valori casuali.
 * @param tessera Array di tessere da inizializzare.
 * @param size_tessere Dimensione dell'array di tessere.
 */
void init(Tessera *tessera, int size_tessere);

/**
 * @brief Verifica se il gioco è terminato.
 * @param tessere Array di tessere disponibili.
 * @param piano Array di righe che rappresenta la scacchiera di gioco.
 * @param size_tessere Dimensione dell'array di tessere disponibili.
 * @param size_piano Dimensione dell'array di righe della scacchiera di gioco.
 * @return true se il gioco è terminato, false altrimenti.
 */
bool game_finished(Tessera *tessere, Row *piano, int size_tessere, int size_piano);

/**
 * @brief Aggiorna lo schermo di gioco.
 * @param tessere Array di tessere disponibili.
 * @param piano Array di righe che rappresenta la scacchiera di gioco.
 * @param speciali Array di tessere speciali disponibili.
 * @param size_tessere Dimensione dell'array di tessere disponibili.
 * @param size_piano Dimensione dell'array di righe della scacchiera di gioco.
 * @param size_speciali Dimensione dell'array di tessere speciali disponibili.
 * @param score Punteggio corrente.
 */
void update_screen(Tessera *tessere, Row *piano, Tessera *speciali, int size_tessere, int size_piano, int size_speciali, int score);

/**
 * @brief Calcola e restituisce il punteggio corrente.
 * @param piano Array di righe che rappresenta la scacchiera di gioco.
 * @param size Dimensione dell'array di righe della scacchiera di gioco.
 * @return Il punteggio corrente.
 */
int score_update(Row *piano, int size);

/**
 * @brief Avvia il gioco umano.
 * @param tessere Array di tessere disponibili.
 * @param piano Array di righe che rappresenta la scacchiera di gioco.
 * @param speciali Array di tessere speciali disponibili.
 * @param size_tessere Dimensione dell'array di tessere disponibili.
 * @param size_piano Dimensione dell'array di righe della scacchiera di gioco.
 * @param size_speciali Dimensione dell'array di tessere speciali disponibili.
 */
void game_start(Tessera *tessere, Row *piano, Tessera *speciali, int *size_tessere, int *size_piano, int *size_speciali);

/**
 * @brief Crea una copia dell'array di tessere.
 * @param tessere Array di tessere da copiare.
 * @param size_tessere Dimensione dell'array di tessere.
 * @return Puntatore alla copia dell'array di tessere.
 */
Tessera *copy_tessere(Tessera *tessere, int size_tessere);

/**
 * @brief Crea una copia dell'array di righe della scacchiera.
 * @param piano Array di righe della scacchiera da copiare.
 * @param size Dimensione dell'array di righe della scacchiera.
 * @return Puntatore alla copia dell'array di righe della scacchiera.
 */
Row *copy_piano(Row *piano, int size);

/**
 * @brief Trova la prima combinazione valida di tessere e aggiorna la scacchiera.
 * @param tessere Array di tessere disponibili.
 * @param piano Array di righe che rappresenta la scacchiera di gioco.
 * @param speciali Array di tessere speciali disponibili.
 * @param size_tessere Dimensione dell'array di tessere disponibili.
 * @param size_piano Dimensione dell'array di righe della scacchiera di gioco.
 * @param size_speciali Dimensione dell'array di tessere speciali disponibili.
 * @return Puntatore alla scacchiera aggiornata.
 */
Row *first_match(Tessera *tessere, Row *piano, Tessera *speciali, int size_tessere, int size_piano, int size_speciali);

/**
 * @brief Avvia il gioco automatico (AI).
 * @param tessere Array di tessere disponibili.
 * @param speciali Array di tessere speciali disponibili.
 * @param size_tessere Dimensione dell'array di tessere disponibili.
 * @param size_speciali Dimensione dell'array di tessere speciali disponibili.
 */
void game_start_ai(Tessera *tessere, Tessera *speciali, int size_tessere, int size_speciali);
//bool add_tessera(Row *row, Tessera new_tessera);
//void add_special(Row *row,Tessera new_tessera);
#endif