#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include <time.h>

#include <string.h>

#include <conio.h>

#include "logic.h"


void game_start(Tessera * tessere, Tessera * giocate, Tessera *speciali,int * size_tessere, int * size_giocate,int *size_speciali) {

  int score = 0;
  char key[2];
  update_screen(tessere,giocate,speciali,*size_tessere,*size_giocate,*size_speciali,score);
  while (!game_finished(tessere, giocate, *size_tessere, *size_giocate)) {

    bool selected = false; //mi serve per dire se ho scelto una tessere valida!
    while (!selected) {
      int input=0;
      scanf("%d",&input);
      if (input > 0 && input <= *size_tessere) {
        // int index = get_index(tessere, size_tessere, input);
        int index = input - 1;
        bool match = false;
        // se ho giocato almeno una tessera faccio il controllo se i numeri sono adiacenti
        if (*size_giocate > 0) {

          bool matchFirst = match_first(tessere[index], giocate[0]); // controllo se la tessera selezionata è adiacente con la prima tessera
          bool matchLast = match_last(tessere[index], giocate[*size_giocate - 1]); // controllo se la tessera selezionata è adiacente con l'ultima tessera
          match = matchFirst || matchLast;

          if (matchFirst && matchLast) {
            printf("Posiziona a sinistra 's' o posiziona a destra 'd'\n");
            char put = 0;
            while (put != 'd' && put != 's') {
              scanf("%c", & put);
            }
            if (put == 'd') {
              giocate = put_last(giocate, size_giocate, tessere[index]);
            } else {
              giocate = put_first(giocate, size_giocate, tessere[index]);
            }
          } else if (matchFirst) {
            giocate = put_first(giocate, size_giocate, tessere[index]);

          } else if (matchLast) {
            giocate = put_last(giocate, size_giocate, tessere[index]);
          }
        } else {
          match = true;
          // put_last(giocate,&size_giocate,tessere[index]);
          giocate[0] = tessere[index];
          ++*size_giocate;
        }
        if (match) {
          tessere = remove_tessera(tessere, size_tessere, index);
          //--*size_tessere; faccio già nella funzione
          selected = true;
        } else {
          printf("Scegli una tessera valida!\n");
        }
      } 
      else if (input < 0 && abs(input) <= *size_speciali && *size_speciali>0) { 
        int index = abs(input) - 1;
        selected = true;
        if (*size_giocate == 0) {
          ++*size_giocate;
          giocate[0] = speciali[index];
        } else {
          printf("Posiziona a sinistra 's' o posiziona a destra 'd'\n");
          char put = 0;
          while (put != 'd' && put != 's') {
            scanf("%c", &put);
          }
          if(speciali[index].n1==11){
            for(int i=0;i<*size_giocate;i++){
              ++giocate[i].n1;
              ++giocate[i].n2;
            }
          }
          if (put == 'd') {
            /*
            [11|11]: somma 1 a tutte le cifre di tutte le tessere sul piano di gioco tranne il 6 che diventa 1.
            La tessera può essere posizionata in qualunque posizione e le sue cifre vegono sostituite con la cifra
            adiacente dopo averla incrementata di 1. Esempio: [1|6][6|3][11|11] diventa [2|1][1|4][4|4]
            */
           if(speciali[index].n1==11){//tessera somma tutti 1
            speciali[index].n1=giocate[*size_giocate-1].n2;
            speciali[index].n2=speciali[index].n1;
           }
          if(speciali[index].n1==-1){ // tessera specchio
            speciali[index].n1=giocate[*size_giocate-1].n2;
            speciali[index].n2=giocate[*size_giocate-1].n1;
          }
           giocate=put_last(giocate,size_giocate,speciali[index]);
            // giocate=put_last(giocate,&size_giocate,tessere[index]);
          } else {
            if(speciali[index].n1==11){ // tessera somma tutti 1
            speciali[index].n1=giocate[0].n1;
            speciali[index].n2=speciali[index].n1;
           }
           if(speciali[index].n1==-1){  //tessera specchio
            speciali[index].n1=giocate[0].n2;
            speciali[index].n2=giocate[0].n1;
           }
            giocate=put_first(giocate,size_giocate,speciali[index]);
          }
          speciali=remove_tessera(speciali,size_speciali,index);
        }
      } 
      else {
        printf("\nScegli una tessera tra quelle disponibili (es. %s)\n", string_tessera(tessere[0]));
      }
    }
    score = score_update(giocate, *size_giocate);
    update_screen(tessere,giocate,speciali,*size_tessere,*size_giocate,*size_speciali,score);

    // printf("%s",input);
  }
  printf("La partita e' terminata! Non ci sono piu' tessere giocabili");

  free(tessere);
  free(giocate);
  free(speciali);

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
  printf("N=");
  scanf("%d", &size_tessere);
  if(size_tessere>0){
    
    tessere = (Tessera * ) realloc(tessere, sizeof(Tessera) * size_tessere);
    init(tessere,size_tessere);

    // tessere giocate/scelte dal giocatore, il numero viene aggiornato ogni qualvolta che si aggiunge una tessera
    Tessera * giocate = (Tessera * ) malloc(sizeof(Tessera * ) * 1);
    int size_giocate = 0;
    game_start(tessere,giocate,speciali,&size_tessere,&size_giocate,&size_speciali);
  }
  


  init(tessere, size_tessere);

}