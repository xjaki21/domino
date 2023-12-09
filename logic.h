#ifndef LOGIC_H
#define LOGIC_H

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif



typedef struct Tessera {
  int n1;
  int n2;
  int num;
  bool selected;
  bool vertical;
}Tessera;

typedef struct Linea{
  Tessera*tessere;
  int size;
}Linea;

void init_speciali(Tessera *speciali,int size);
void init(Tessera * tessera, int size_tessere); 

bool match_first( Tessera a, Tessera b);
bool match_last( Tessera a, Tessera b);

Tessera* put_first( Tessera* tessere, int* size,  Tessera new_tessera);
Tessera* put_last( Tessera* tessere, int* size,  Tessera new_tessera);

bool game_finished( Tessera *tessere, Linea *piano,int size_tessere,int size_piano);

char * string_tessera( Tessera tessera);

void print_disponibili( Tessera *tessere,  Tessera *speciali,int size_tessere,int size_speciali);
void print_giocate( Linea * piano, int size);

Tessera * remove_tessera( Tessera * tessera, int *size, int index);

int get_index( Tessera * tessera, int size, int num);
int score_update( Linea*piano,int size);
void update_screen(Tessera *tessere,Linea *piano,Tessera *speciali,int size_tessere,int size_piano,int size_speciali,int score);

bool add_horizontal(Linea * linea, Tessera new_tessera);
void add_special(Linea*linea,Tessera new_tessera);
#endif