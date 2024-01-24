#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <time.h>
#include <string.h>

#include "logic.h"




int main() {
  srand(time(NULL));
  int size_speciali = 3;
  Tessera * speciali = (Tessera * ) malloc(sizeof(Tessera) * size_speciali);
  init_speciali(speciali, size_speciali);

  Tessera * tessere = (Tessera * ) malloc(sizeof(Tessera) * 1);  
  int size_tessere = 0;
  
  system(CLEAR_SCREEN);
  printf("Con quante tessere vuoi giocare?\n");
  scanf("%d", &size_tessere);
  
  if(size_tessere>0){

    tessere = (Tessera * ) realloc(tessere, sizeof(Tessera) * size_tessere);
    init(tessere,size_tessere);
        
    char mod=0;
    printf("Modalita':\n1.Interattiva\n2.AI\n");
    
    do{
      scanf(" %c",&mod);
      mod=mod-48;
    }while(mod!=1 && mod!=2);

    if(mod==1){
      Board *board=create_board(size_tessere);
      game_start(board,tessere,speciali,size_tessere,size_speciali);
    }
    if(mod==2){
      game_start_ai(tessere,speciali,size_tessere,size_speciali);
    }
  }
}