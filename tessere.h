#ifndef TESSERE_H
#define TESSERE_H


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


Row *create_row();
void extend_arr_tessere(Row *r);

Tessera *create_arr_tessere(int size);

char * string_tessera(Tessera tessera);

bool is_special(Tessera a);

bool match_left( Tessera a, Tessera b);

bool match_right( Tessera a, Tessera b);

int *scelte_possibili(Row *piano,int size,Tessera tessera,int *num_scelte);

void print_scelte(int *m,int size);

void print_disponibili( Tessera *tessere,  Tessera *speciali,int size_tessere,int size_speciali);

int max_row(Row *piano,int size);
void print_giocate( Row * piano, int size);




Tessera * remove_tessera( Tessera * tessera, int *size, int index);

void put_front_tessera(Row *piano,int size_piano,Row *r,Tessera tessera);

void put_tessera(Row *l,Tessera tessera,int pos);

void put_tessera_speciale(Row *piano,int size_piano,Row *row,int pos,Tessera tessera);

int char_to_int(char*s);

bool posiziona_tessera(Row *piano,int *size_piano,Tessera tessera);


#endif