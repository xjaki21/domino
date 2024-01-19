#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <time.h>
#include <string.h>

#include "lib/logic.h"




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
    piano[0].size=0;
    int size_piano=1;

    char mod=0;
    printf("Modalita':\n1.Interattiva\n2.AI\n");
    
    do{
      scanf(" %c",&mod);
      mod=mod-48;
    }while(mod!=1 && mod!=2);

    if(mod==1)
      game_start(tessere,piano,speciali,&size_tessere,&size_piano,&size_speciali);
    if(mod==2){
      game_start_ai(tessere,speciali,size_tessere,size_speciali);
    }
  }
}