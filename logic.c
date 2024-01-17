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
  [*|*]: copia “a specchio” la tessera adiacente. La tessera può essere posizionata in qualunque
  posizione e le sue cifre vegono sostituite con le cifre della tessera adiacente in ordine inverso. Esempio:
  [1|2][2|3][12|21] diventa [1|2][2|3][3|2]
  */
  speciali[2].n1 = -1;
  speciali[2].n2 = -1;
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

bool game_finished(Tessera * tessere, Row * piano, int size_tessere, int size_piano) {
  bool one_piece=false;
  for(int i=0;i<size_piano;i++){
    Tessera *a=piano[i].tessere;
    int a_size=piano[i].size;
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




void update_screen(Tessera * tessere, Row * piano, Tessera * speciali, int size_tessere, int size_piano, int size_speciali, int score) {
  //printf("\e[1;1H\e[2J"); // regex che pulisce schermo
  system(CLEAR_SCREEN);//syscall al sistema operativo per "pulire" lo schermo

  printf("Score=%d\n", score);
  print_giocate(piano, size_piano);
  print_disponibili(tessere, speciali, size_tessere, size_speciali);
  printf("Scegli una tessera:\n");
}


int score_update(Row *piano, int size) {
  int score = 0;
  for(int i=0;i<size;i++){
    Tessera *a=piano[i].tessere;
    int size_a=piano[i].size;
    for(int j=0;j<size_a;j++){
      if(a[j].selected && !a[j].vertical){
        score+=a[j].n1+a[j].n2;
      }else if(a[j].selected && a[j].vertical){
        score+=a[j].n1;
      }
    }
  }
  return score;
}


void game_start(Tessera * tessere, Row * piano, Tessera *speciali,int * size_tessere, int * size_piano,int *size_speciali) {

  Tessera *giocate=piano[0].tessere;
  int *size_giocate=&(piano[0].size);
  int score = 0;

  update_screen(tessere,piano,speciali,*size_tessere,*size_piano,*size_speciali,score);
  while (!game_finished(tessere, piano, *size_tessere, *size_piano) || *size_speciali>0) {
    bool selected = false; //mi serve per dire se ho scelto una tessere valida!
    while (!selected) {
      char keys[10];
      scanf("%s",&keys);
      int input=char_to_int(keys);
      if (input > 0 && input <= *size_tessere) {
        int index = input - 1;
        tessere[index].selected=true;

        //bool match=add_tessera(&piano[0],tessere[index]); //la funzione controlla se c'è un match e aggiunge la tessere se c'è, restituisce true o false se è stata aggiunta la tessera
        bool match= posiziona_tessera(piano,size_piano,tessere[index]);
        if (match) {
          tessere = remove_tessera(tessere, size_tessere, index);//--*size_tessere; faccio già nella funzione
          selected = true;
        } else {
          printf("Scegli una tessera valida!\n");
        }
      }else if (input < 0 && abs(input) <= *size_speciali && *size_speciali>0) { 
        int index = abs(input) - 1;
        selected = true;
        speciali[index].selected=true;
        bool match=posiziona_tessera(piano,size_piano,speciali[index]);
        //add_special(&piano[0],speciali[index]);
        speciali=remove_tessera(speciali,size_speciali,index);
      }else {
        printf("Scegli una tessera tra quelle disponibili (es. %s)\n", string_tessera(tessere[0]));
      }
    }
    score = score_update(piano, *size_piano);
    //piano[0].tessere[0].n1=2;
    //piano[0].tessere[0].n2=2;
    update_screen(tessere,piano,speciali,*size_tessere,*size_piano,*size_speciali,score);

    // printf("%s",input);
  }
  printf("La partita e' terminata! Non ci sono piu' tessere giocabili");

  free(tessere);
  free(speciali);
  free(piano);

}

Tessera *copy_tessere(Tessera *tessere,int size_tessere){
  Tessera *new=(Tessera*)malloc(sizeof(Tessera)*size_tessere);
  for(int i=0;i<size_tessere;i++){
    new[i].n1=tessere[i].n1;
    new[i].n2=tessere[i].n2;
    new[i].num=tessere[i].num;
    new[i].selected=tessere[i].selected;
    new[i].vertical=tessere[i].vertical;
  }
  return new;
}

Row *copy_piano(Row *piano,int size){
  Row *new=(Row*)malloc(sizeof(Row)*size);
  for(int i=0;i<size;i++){
    Row *r=&piano[i];
    Tessera *tessere=r->tessere;
    new[i].size=r->size;
    new[i].capacity=r->capacity;
    new[i].tessere=copy_tessere(tessere,r->size);
  }
  return new;
}


Row *first_match(Tessera * tessere, Row *piano, Tessera *speciali,int size_tessere, int size_piano,int size_speciali){


  int i=0;
  
  while(!game_finished(tessere,piano,size_tessere,size_piano)){
   // printf("start\n");
    bool put=false;
    Row *r_0=&piano[0];
    //Row *game=copy_piano(piano,size_piano);
    if(r_0->size==0){
      // print_disponibili(new_tessere,speciali,size_game_tessere,size_speciali);
      tessere[0].selected=true;
      printf("primo inserimento\n");
      r_0->tessere[0]=tessere[0];
      r_0->size=1;
      tessere=remove_tessera(tessere,&size_tessere,0);
      put=true;
      //i++;
    }else{
      int num_scelte=0;
      int *scelte=scelte_possibili(piano,1,tessere[i],&num_scelte);
      //print_scelte(scelte,num_scelte);
      if(num_scelte>0){

        Tessera t=tessere[i];
        t.selected=true;
        tessere=remove_tessera(tessere,&size_tessere,i);
        for(int j=0;j<1;j++){
          //piano=copy_piano(temp_piano,size_piano);

          int pos=scelte[j*2+1];
          //printf("POS:%d\n",pos);
          int num_row=0;
          Row *r=&piano[num_row];

          if(pos>=0){
            put_tessera(r,t,pos);
          }else{
            put_front_tessera(piano,size_piano,r,t);
          }
        }
        put=true;
      }
    }
    if(!put){
      i++;
    }else{
      i=0;
    }
  }
  return  piano;
}

Row *ai(Tessera * tessere, Tessera *speciali,int size_tessere,int size_speciali){
  Row *piano;
  int size_piano=1;
  for(int i=0;i<size_tessere;i++){
    Tessera *copia_tessere=copy_tessere(tessere,size_tessere);
    int copia_size_tessere=size_tessere;

    Row *new_piano=(Row*)malloc(sizeof(Row)*size_tessere);
    new_piano[0]=*create_row();
    new_piano[0].size=0;
    new_piano[0].start_index=0;

    Row *r_0=&new_piano[0];
    copia_tessere[i].selected=true;
    r_0->tessere[0]=copia_tessere[i];
    r_0->size=1;
    copia_tessere=remove_tessera(copia_tessere,&copia_size_tessere,i);

    new_piano=first_match(copia_tessere,new_piano,speciali,copia_size_tessere,size_piano,size_speciali);
    //print_giocate(new_piano,size_piano);
    print_giocate(new_piano,size_piano);
    if(i==0){
      piano=new_piano;

    }else{
      //printf("NEW_PIANO SCORE:%d\nPIANO_SCORE:%d\n",score_update(new_piano,size_piano),score_update(piano,size_piano));
      if(score_update(new_piano,size_piano)>score_update(piano,size_piano)){
        //printf("CAMBIO\n");
        free(piano);
        piano=new_piano;
      }
    }
  }
  return piano;
}
  
