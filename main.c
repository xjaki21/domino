#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include "logic.h"




int main() {
  srand(time(NULL));
  int size_speciali = 3;
  Tessera * speciali = (Tessera * ) malloc(sizeof(Tessera) * size_speciali);
  init_speciali(speciali, size_speciali);

  Tessera * tessere = (Tessera * ) malloc(sizeof(Tessera) * 1);  
  int size_tessere = 0;
  
  system(CLEAR_SCREEN);
  printf("N=");
  scanf("%d", &size_tessere);
  
  if(size_tessere>0){
    tessere = (Tessera * ) realloc(tessere, sizeof(Tessera) * size_tessere);
    init(tessere,size_tessere);
    // tessere giocate/scelte dal giocatore, il numero viene aggiornato ogni qualvolta che si aggiunge una tessera
    Row *piano=(Row*)malloc(sizeof(Row)*size_tessere);
    piano[0]=*create_row();
    piano[0].start_index=0;
    int size_piano=1;
    game_start(tessere,piano,speciali,&size_tessere,&size_piano,&size_speciali);
  }
  


  init(tessere, size_tessere);

}