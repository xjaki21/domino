#ifndef LOGIC_H
#define LOGIC_H

typedef struct Tessera {
  int n1;
  int n2;
  int num;
  bool selected;
  bool vertical;
}Tessera;

void init_speciali(Tessera *speciali,int size);
void init(Tessera * tessera, int size_tessere); 

bool match_first( Tessera a, Tessera b);
bool match_last( Tessera a, Tessera b);

Tessera* put_first( Tessera* tessere, int* size,  Tessera new_tessera);
Tessera* put_last( Tessera* tessere, int* size,  Tessera new_tessera);

bool game_finished( Tessera *tessere, Tessera *giocate,int size_tessere,int size_giocate);

char * string_tessera( Tessera tessera);

void print_disponibili( Tessera *tessere,  Tessera *speciali,int size_tessere,int size_speciali);
void print_giocate( Tessera * tessera, int size);

Tessera * remove_tessera( Tessera * tessera, int *size, int index);

int get_index( Tessera * tessera, int size, int num);
int score_update( Tessera*tessere,int size);
void update_screen(Tessera *tessere,Tessera *giocate,Tessera *speciali,int size_tessere,int size_giocate,int size_speciali,int score);
#endif