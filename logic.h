#ifndef LOGIC_H
#define LOGIC_H

#include "tessere.h"

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif


void init_speciali(Tessera *speciali,int size);
void init(Tessera * tessera, int size_tessere); 

bool game_finished( Tessera *tessere, Row *piano,int size_tessere,int size_piano);


int score_update( Row*piano,int size);
void update_screen(Tessera *tessere,Row *piano,Tessera *speciali,int size_tessere,int size_piano,int size_speciali,int score);

void game_start(Tessera * tessere, Row * piano, Tessera *speciali,int * size_tessere, int * size_piano,int *size_speciali);
Row *mod_ai(Tessera * tessere, Row * piano, Tessera *speciali,int size_tessere, int size_piano,int size_speciali);
Row *ai(Tessera * tessere, Tessera *speciali,int size_tessere,int size_speciali);
//bool add_tessera(Row *row, Tessera new_tessera);
//void add_special(Row *row,Tessera new_tessera);
#endif