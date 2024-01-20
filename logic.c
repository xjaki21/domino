#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "logic.h"

void init_speciali(Tessera * speciali, int size) {
  /*
  [0|0]: può essere accostata a qualunque altra tessera. Esempio: [1|2][0|0][5|6]
  */
  speciali[0].n1 = 0;
  speciali[0].n2 = 0;
  speciali[0].num = -1;
  speciali[0].vertical=false;
  /*
  [11|11]: somma 1 a tutte le cifre di tutte le tessere sul piano di gioco tranne il 6 che diventa 1.
  La tessera può essere posizionata in qualunque posizione e le sue cifre vegono sostituite con la cifra
  adiacente dopo averla incrementata di 1. Esempio: [1|6][6|3][11|11] diventa [2|1][1|4][4|4]
  */
  speciali[1].n1 = 11;
  speciali[1].n2 = 11;
  speciali[1].num = -1;
  speciali[1].vertical=false;
  /*
  [12|21]: copia “a specchio” la tessera adiacente. La tessera può essere posizionata in qualunque
  posizione e le sue cifre vegono sostituite con le cifre della tessera adiacente in ordine inverso. Esempio:
  [1|2][2|3][12|21] diventa [1|2][2|3][3|2]
  */
  speciali[2].n1 = 12;
  speciali[2].n2 = 21;
  speciali[2].num = -1;
  speciali[2].vertical=false;
}


void init(Tessera * tessera, int size_tessere) {
  int n1, n2;
  for (int i = 0; i < size_tessere; i++) {
    n1 = rand() % 6 + 1;
    n2 = rand() % 6 + 1;
    tessera[i].n1 = n1;
    tessera[i].n2 = n2;
    tessera[i].num = i + 1;
    tessera[i].selected = false;
    tessera[i].vertical=false;
  }
}



bool game_finished(Board *board,Tessera * tessere, int size_tessere) {
  bool one_piece=false;
  for(int i=0;i<board->size;i++){
    Tessera *a=board->rows[i].tessere;
    int a_size=board->rows[i].size;
    for(int j=0;j<a_size;j++){
      one_piece=true;
      for(int k=0;k<size_tessere;k++){
        if(a[j].selected){
          if((j==0 || !a[j-1].selected) && match_left(tessere[k],a[j])){
            return false;
          }
          if((j==a_size-1 || !a[j+1].selected) && match_right(tessere[k],a[j])){
            return false;
          }
        }
      }
    }
  }
  if(!one_piece)
    return false;
  return true;
}




void update_screen(Board *board,Tessera * tessere, Tessera * speciali, int size_tessere,int size_speciali) {
  //printf("\e[1;1H\e[2J"); // regex che pulisce schermo
  system(CLEAR_SCREEN);//syscall al sistema operativo per "pulire" lo schermo

  printf("Score=%d\n", board->score);
  print_giocate(board);
  print_disponibili(tessere, speciali, size_tessere, size_speciali);
  printf("Scegli una tessera:\n");
}


void score_update(Board *board) {
  int score = 0;
  for(int i=0;i<board->size;i++){
    Tessera *a=board->rows[i].tessere;
    int size_a=board->rows[i].size;
    for(int j=0;j<size_a;j++){
      if(a[j].selected && !a[j].vertical){
        score+=a[j].n1+a[j].n2;
      }else if(a[j].selected && a[j].vertical){
        score+=a[j].n1;
      }
    }
  }
  board->score=score;
}



void game_start(Board *board,Tessera * tessere, Tessera *speciali,int size_tessere,int size_speciali) {

  Tessera *giocate=board->rows[0].tessere;
  int score = 0;

  update_screen(board,tessere,speciali,size_tessere,size_speciali);
  while (!game_finished(board,tessere, size_tessere) || size_speciali>0) {
    bool selected = false; //mi serve per dire se ho scelto una tessere valida!

    while (!selected) {
      char keys[10];
      scanf(" %s",keys);
      int input=char_to_int(keys);
     // int input=0;
      //scanf(" %d",&input);
      if (input > 0 && input <= size_tessere) {
        int index = input - 1;
        tessere[index].selected=true;

        //bool match=add_tessera(&piano[0],tessere[index]); //la funzione controlla se c'è un match e aggiunge la tessere se c'è, restituisce true o false se è stata aggiunta la tessera
        bool match= posiziona_tessera(board,tessere[index]);
        if (match) {
          tessere = remove_tessera(tessere,&size_tessere, index);//--*size_tessere; faccio già nella funzione
          selected = true;
        } else {
          printf("Scegli una tessera valida!\n");
        }
      }
      else if ( input < 0 && abs(input) <= size_speciali && size_speciali>0 && board->rows[0].size>0) { //se tessera è speciale
        int index = abs(input) - 1;
        selected = true;
        speciali[index].selected=true;
        bool match=posiziona_tessera(board,speciali[index]);
        //add_special(&piano[0],speciali[index]);
        speciali=remove_tessera(speciali,&size_speciali,index);
      }else {
        if(board->rows[0].size==0){
          printf("La prima tessera non puo' essere speciale!\n");
        }else{
          printf("Scegli una tessera tra quelle disponibili\n");
        }

      }
    }
    score_update(board);
    //piano[0].tessere[0].n1=2;
    //piano[0].tessere[0].n2=2;
    update_screen(board,tessere,speciali,size_tessere,size_speciali);

    // printf("%s",input);
  }
  printf("La partita e' terminata! Non ci sono piu' tessere giocabili\n");

  if(size_tessere>0) free(tessere);
  if(size_speciali>0)free(speciali);
  free_board(board);

}

Board *first_match(Board *board,Tessera * tessere, Tessera *speciali,int size_tessere,int size_speciali){


  
  while(!game_finished(board,tessere,size_tessere) || size_speciali>0){

    int num_scelte=0;
    Tessera best_tessera;
    best_tessera.n1=0;
    best_tessera.n2=0;

    int index=-1;
    int *scelte=NULL;
    int pos;
    for(int i=0;i<size_tessere;i++){
      scelte=scelte_possibili(board,tessere[i],&num_scelte);
      if(num_scelte>0 && tessere[i].n1+tessere[i].n2 > best_tessera.n1+best_tessera.n2 ){
        best_tessera=tessere[i];
        index=i;
        pos=scelte[1];
      }
      //free(scelte);
    }
    Row *r=&board->rows[0];
    if(num_scelte>0){
      best_tessera.selected=true;
      tessere=remove_tessera(tessere,&size_tessere,index);
      if(pos>=0){
        put_tessera(r,best_tessera,pos);
      }else{
        put_front_tessera(board,r,best_tessera);
      }
      //break;
    }
    //se non ci sono tessere normali che posso mettere, metto quelle speciali
    else if(size_speciali>0){
      best_tessera=speciali[0];
     // printf("[%d|%d]\n",best_tessera.n1,best_tessera.n2);
      best_tessera.selected=true;

      speciali=remove_tessera(speciali,&size_speciali,0);
      put_tessera_speciale(board,r,-1,best_tessera);
      //put_front_tessera(board,r,best_tessera);
    }else{
      break;
    }
  }
  score_update(board);
  return  board;
}

void game_start_ai(Tessera * tessere, Tessera *speciali,int size_tessere,int size_speciali){
  print_disponibili(tessere,speciali,size_tessere,size_speciali);
  Board *board=NULL;
  
  for(int i=0;i<size_tessere;i++){
    Tessera *copia_tessere=copy_tessere(tessere,size_tessere);
    Tessera *copia_speciali=copy_tessere(speciali,size_speciali);

    int copia_size_tessere=size_tessere;

    Board *new_board=create_board(copia_size_tessere);
    Row *r_0=&new_board->rows[0];
    
    copia_tessere[i].selected=true;
    r_0->tessere[0]=copia_tessere[i];
    r_0->size=1;
    
    copia_tessere=remove_tessera(copia_tessere,&copia_size_tessere,i);

    new_board=first_match(new_board,copia_tessere,copia_speciali,copia_size_tessere,size_speciali);
    //print_giocate(new_piano,size_piano)
    //score_update(new_board);
    printf("Score=%d\n", new_board->score);
    print_giocate(new_board);
    if(i==0){
      board=new_board;
    }else{
      //printf("NEW_PIANO SCORE:%d\nPIANO_SCORE:%d\n",score_update(new_piano,size_piano),score_update(piano,size_piano));
      if(new_board->score > board->score){
        //printf("CAMBIO\n");
        free_board(board);
        board=new_board;
      }
    }
    
  }
  printf("Best game:\n");

  printf("Score=%d\n", board->score);
  print_giocate(board);
}
  
