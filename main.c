#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include "logic.h"


void game_start(Tessera * tessere, Linea * piano, Tessera *speciali,int * size_tessere, int * size_piano,int *size_speciali) {

  Tessera *giocate=piano[0].tessere;
  int *size_giocate=&(piano[0].size);
  int score = 0;
  char key[2];
  update_screen(tessere,piano,speciali,*size_tessere,*size_piano,*size_speciali,score);
  while (!game_finished(tessere, piano, *size_tessere, *size_piano) || *size_speciali>0) {
    bool selected = false; //mi serve per dire se ho scelto una tessere valida!
    while (!selected) {
      int input=0;
      scanf("%d",&input);

      if (input > 0 && input <= *size_tessere) {
        int index = input - 1;
        tessere[index].selected=true;
        bool match=add_tessera(&piano[0],tessere[index]); //la funzione controlla se c'è un match e aggiunge la tessere se c'è, restituisce true o false se è stata aggiunta la tessera
        if (match) {
          char scelta=0;
          while(scelta!='v' && scelta!='h'){
            printf("Digita v o h (v=vertical e h=horizontal)\n");
            scanf(" %c",&scelta);
          }
          if(scelta=='v'){
            Tessera *l_tessere=piano[0].tessere;
            int l_size=piano[0].size;
            l_tessere[l_size-1].vertical=true;

            ++*size_piano;
            piano[1].tessere=create_arr_tessere(l_size);
            piano[1].size=l_size;

            Tessera *new_l=piano[1].tessere;
            new_l[l_size-1]=l_tessere[l_size-1];
            new_l[l_size-1].n1=new_l[l_size-1].n2;
            
            l_tessere[l_size-1].n2=l_tessere[l_size-1].n1;
          }
          tessere = remove_tessera(tessere, size_tessere, index);//--*size_tessere; faccio già nella funzione
          selected = true;
        } else {
          printf("Scegli una tessera valida!\n");
        }
      } 
      else if (input < 0 && abs(input) <= *size_speciali && *size_speciali>0) { 
        int index = abs(input) - 1;
        selected = true;
        speciali[index].selected=true;
        add_special(&piano[0],speciali[index]);
        speciali=remove_tessera(speciali,size_speciali,index);
      } 
      else {
        printf("\nScegli una tessera tra quelle disponibili (es. %s)\n", string_tessera(tessere[0]));
      }
    }
    //score = score_update(piano, *size_piano);
    score=0;
    //piano[0].tessere[0].n1=2;
    //piano[0].tessere[0].n2=2;
    update_screen(tessere,piano,speciali,*size_tessere,*size_piano,*size_speciali,score);

    // printf("%s",input);
  }
  printf("La partita e' terminata! Non ci sono piu' tessere giocabili");

  free(tessere);
  //free(giocate);
  free(speciali);
  free(piano);

}

int main() {
  srand(time(NULL));
  int size_speciali = 3;
  Tessera * speciali = (Tessera * ) malloc(sizeof(Tessera) * size_speciali);
  init_speciali(speciali, size_speciali);
  /*
[0|0]: può essere accostata a qualunque altra tessera. Esempio: [1|2][0|0][5|6]
*/

  Tessera * tessere = (Tessera * ) malloc(sizeof(Tessera) * 1);  
  int size_tessere = 0;
  system(CLEAR_SCREEN);
  printf("N=");
  scanf("%d", &size_tessere);
  if(size_tessere>0){
    tessere = (Tessera * ) realloc(tessere, sizeof(Tessera) * size_tessere);
    init(tessere,size_tessere);
    
    // tessere giocate/scelte dal giocatore, il numero viene aggiornato ogni qualvolta che si aggiunge una tessera
    
    Linea *piano=(Linea*)malloc(sizeof(Linea)*size_tessere);
    piano[0]=*create_linea();
    int size_piano=1;
    game_start(tessere,piano,speciali,&size_tessere,&size_piano,&size_speciali);
  }
  


  init(tessere, size_tessere);

}