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

typedef struct Row{ //vector di tessere
  Tessera*tessere;
  int size;
  int capacity;
  int start_index;//indice della prima tessera di una riga
}Row;

void init_speciali(Tessera *speciali,int size);
void init(Tessera * tessera, int size_tessere); 

Row *create_row();
Tessera *create_arr_tessere(int size);


int *scelte_possibili(Row *piano,int size,Tessera tessera,int *num_scelte);
void print_scelte(int *m,int size);

void put_front_tessera(Row *piano,int size_piano,Row *r,Tessera tessera);
void put_tessera(Row *l,Tessera tessera,int pos);
bool posiziona_tessera(Row *piano,int *size_piano,Tessera tessera);

bool mathc_left( Tessera a, Tessera b);
bool match_right( Tessera a, Tessera b);

//void put_first( Row *l,Tessera new_tessera);
//void put_last( Row *l ,Tessera new_tessera);

bool game_finished( Tessera *tessere, Row *piano,int size_tessere,int size_piano);

char * string_tessera( Tessera tessera);

void print_disponibili( Tessera *tessere,  Tessera *speciali,int size_tessere,int size_speciali);
void print_giocate( Row * piano, int size);

Tessera * remove_tessera( Tessera * tessera, int *size, int index);

int get_index( Tessera * tessera, int size, int num);
int score_update( Row*piano,int size);
void update_screen(Tessera *tessere,Row *piano,Tessera *speciali,int size_tessere,int size_piano,int size_speciali,int score);

void game_start(Tessera * tessere, Row * piano, Tessera *speciali,int * size_tessere, int * size_piano,int *size_speciali);
Row *mod_ai(Tessera * tessere, Row * piano, Tessera *speciali,int size_tessere, int size_piano,int size_speciali);
//bool add_tessera(Row *row, Tessera new_tessera);
//void add_special(Row *row,Tessera new_tessera);
#endif