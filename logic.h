#ifndef LOGIC_H
#define LOGIC_H

struct Tessera {
  int n1;
  int n2;
  int num;
  bool selected;
};
void init_speciali(struct Tessera *speciali,int size);
void init(struct Tessera * tessera, int size_tessere); 

bool match_first(struct Tessera a,struct Tessera b);
bool match_last(struct Tessera a,struct Tessera b);

struct Tessera* put_first(struct Tessera* tessere, int* size, struct Tessera new_tessera);
struct Tessera* put_last(struct Tessera* tessere, int* size, struct Tessera new_tessera);

bool game_finished(struct Tessera *tessere,struct Tessera *giocate,int size_tessere,int size_giocate);

char * string_tessera(struct Tessera tessera);

void print_disponibili(struct Tessera *tessere, struct Tessera *speciali,int size_tessere,int size_speciali);
void print_giocate(struct Tessera * tessera, int size);

struct Tessera * remove_tessera(struct Tessera * tessera, int * size, int index);

int get_index(struct Tessera * tessera, int size, int num);
int score_update(struct Tessera*tessere,int size);
#endif