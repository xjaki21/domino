#include <stdbool.h>

#include <stdio.h>

#include <stdlib.h>

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

Row *create_row(){
  Row *new=(Row*)malloc(sizeof(Row));
  new->capacity=10;
  new->tessere=(Tessera*)malloc(sizeof(Tessera)*new->capacity);
  new->size=0;

  return new;
}

Tessera *create_arr_tessere(int size){
  Tessera *new=(Tessera*)malloc(sizeof(Tessera)*size);
  for(int i=0;i<size;i++){
    new[i].n1=-1;
    new[i].n2=-1;
    new[i].selected=false;
    new[i].vertical=false;
  }
  return new;
}

bool is_special(Tessera a){
  if(a.n1==0 || a.n1==-1 || a.n1==11)
    return true;
  return false;
}

bool match_left(Tessera a, Tessera b) {
  if(is_special(a) || is_special(b)){
    return true;
  }
  return a.n1 == b.n1 || a.n2 == b.n1;
}
bool match_right(Tessera a, Tessera b) {
  if(is_special(a) || is_special(b)){
    return true;
  }
  return a.n1 == b.n2 || a.n2 == b.n2;
}

//matrice che restituisce le possibili scelte
int *scelte_possibili(Row *piano,int size,Tessera tessera,int *num_scelte){
  
  int *scelte=(int*)malloc(sizeof(int)*size*100);
  int k=0;
  /*
  int scelte={{1,2},
              {0,1},
              {1,1}}
  */
  for(int i=0;i<size;i++){
    Tessera *a=piano[i].tessere;
    int a_size=piano[i].size;
    for(int j=0;j<a_size;j++){
      if(a[j].selected){
        if((j==0 || !a[j-1].selected) && match_left(tessera,a[j])){
          scelte[k]=i;
          scelte[k+1]=j-1;
          k=k+2;
          
        }
        if((j==a_size-1 || !a[j+1].selected) && match_right(tessera,a[j])){
            scelte[k]=i;
            scelte[k+1]=j+1;
            k=k+2;
        }
      }
    }
  }
  *num_scelte=k/2;
  if(k>0){
    scelte=(int*)realloc(scelte,sizeof(int)* k);
    if(!scelte) exit(EXIT_FAILURE);
  }

  return scelte;
}

void print_scelte(int *m,int size){
  int k=0;
  for(int i=0;i<size;i++){
    printf("%d. {%d,%d}\n",i,m[k],m[k+1]);
    k=k+2;
  }
}

void extend_arr_tessere(Row *r){
  if(r->size>=r->capacity){
    r->tessere=(Tessera*)realloc(r->tessere,sizeof(Tessera)*r->size*2);
    if(!r->tessere) exit(EXIT_FAILURE);
    r->capacity*=2;
    //inizializzo i nuovi spazi con false e -1, perché sono "vuoti"
    for(int i=r->size;i<r->capacity;i++){
      r->tessere[i].n1=-1;
      r->tessere[i].n1=-1;
      r->tessere[i].selected=false;
      r->tessere[i].vertical=false;
    }
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

char * string_tessera(Tessera tessera) {
  char * str = (char * ) malloc(sizeof(char) * 4);
  sprintf(str, "[%d|%d]", tessera.n1, tessera.n2); // concateno la stringo con gli elementi
  return str;
}

void print_disponibili(Tessera * tessere, Tessera * speciali, int size_tessere, int size_speciali) {
  printf("Tessere disponibili:\n");
  int righe = 10;
  int col = ((size_tessere) / righe) + 1; //-3 per le tessere speciale
  int count_col = 0;
  int resto_last_col = (size_tessere) % righe; //-3 per le tessere speciale
  for (int i = 0; i < righe; i++) {
    if (resto_last_col == i) {
      col--;
    }
    for (int j = 0; j < col; j++) {
      printf("%d. [%d|%d]\t", tessere[i + j * 10].num, tessere[i + j * 10].n1, tessere[i + j * 10].n2);
    }
    printf("\n");
  }
  if (size_speciali > 0) {
    printf("---TESSERE SPECIALI----\n");
    for (int i = 0; i < size_speciali; i++) {
      printf("-%d. [%d|%d]\n", i + 1, speciali[i].n1, speciali[i].n2);
    }
  }
  printf("\n");

}

int max_row(Row *piano,int size){
  int max=piano[0].size;
  for(int i=1;i<size;i++){
    if(piano[i].size>max){
      max=piano[i].size;
    }
  }
  return max;
}
void print_giocate(Row * piano, int size) {

  printf("Tessere giocate:\n");
  printf("\t  ");
  for(int i=0;i<max_row(piano,size);i++){
    printf("%d\t  ",i);
  }
  printf("%d\n",max_row(piano,size));
  for(int i=0;i<size;i++){
    Tessera *a=piano[i].tessere;
    int size_a=piano[i].size;
    printf("%d\t",i);
    for(int j=0;j<size_a;j++){
      if(a[j].vertical && a[j].selected){
          printf(" [%d]\t",a[j].n1);
      }else{
        if(a[j].selected){
          printf("[%d|%d]\t",a[j].n1,a[j].n2);
        }else{
          printf("     \t");
        }
      }
    }
    printf("\n");
  }
  printf("\n\n");
}

void update_screen(Tessera * tessere, Row * piano, Tessera * speciali, int size_tessere, int size_piano, int size_speciali, int score) {
  //printf("\e[1;1H\e[2J"); // regex che pulisce schermo
  system(CLEAR_SCREEN);//syscall al sistema operativo per "pulire" lo schermo

  printf("Score=%d\n", score);
  print_giocate(piano, size_piano);
  print_disponibili(tessere, speciali, size_tessere, size_speciali);
  printf("Scegli una tessera:\n");
}

/*
rimuove l'elemento n dell'array di tessera
*/
Tessera * remove_tessera(Tessera * tessera, int *size, int index) {
  Tessera * new_arr = (Tessera * ) malloc(sizeof(Tessera) * (*size - 1));
  if (!new_arr) exit(EXIT_FAILURE);
  int j = 0;
  for (int i = 0; i < *size; i++) {
    if (i != index) {
      new_arr[j] = tessera[i];
      ++j;
    }
  }
  for (int i = 0; i < *size - 1; i++) {
    new_arr[i].num = i + 1; //aggiorno numero relativo all'interfaccia utente, cioè i numeri che scelgo da tastiera
  }
  --*size;
  free(tessera); //libero la vecchia memoria allocata
  return new_arr;
}
/*
trova l'indice del numero della tessera corrispondente
*/
int get_index(Tessera * tessera, int size, int num) {
  int index = 0;
  for (int i = 0; i < size; i++) {
    if (tessera[i].num == num) {
      index = i;
      break;
    }
  }
  return index;
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

void put_front_tessera(Row *piano,int size_piano,Row *r,Tessera tessera){
  for(int i=0;i<size_piano;i++){
    Row *row=&piano[i];
    extend_arr_tessere(row);
    for(int j=row->size-1;j>=0;j--){
      row->tessere[j+1]=row->tessere[j];
    }
    row->tessere[0].n1=-1;
    row->tessere[0].n2=-1;
    row->tessere[0].selected=false;
    row->tessere[0].vertical=false;
    ++row->size;
  }
  if(tessera.n2!=r->tessere[1].n1){
    int n2=tessera.n2;
    tessera.n2=tessera.n1;
    tessera.n1=n2;
  }
  r->tessere[0]=tessera;
}


void put_tessera(Row *r,Tessera tessera,int pos){
  if(pos>=r->size){
    extend_arr_tessere(r);
    ++r->size;
  }
   //metto a sinistra la tessera
  if(r->tessere[pos+1].selected && match_left(tessera,r->tessere[pos+1])){
    if (tessera.n2 != r->tessere[pos+1].n1 && r->tessere[pos+1].n1!=0) { //se è tessera [0|0] mettila com'è
      int n2=tessera.n2;
      tessera.n2=tessera.n1;
      tessera.n1=n2;
    }
  }
  
  
   //metto a destra la tessera
  if(pos>0 && r->tessere[pos-1].selected && match_right(tessera,r->tessere[pos-1])){
    if(tessera.n1 !=r->tessere[pos-1].n2 && r->tessere[pos-1].n1!=0){
      int n2=tessera.n2;
      tessera.n2=tessera.n1;
      tessera.n1=n2;
    }
  }
  //tessera.selected=true;
  r->tessere[pos]=tessera;
}


/*
• [0|0]: può essere accostata a qualunque altra tessera. Esempio: [1|2][0|0][5|6]
• [11|11]: somma 1 a tutte le cifre di tutte le tessere sul piano di gioco tranne il 6 che diventa 1.
La tessera può essere posizionata in qualunque posizione e le sue cifre vegono sostituite con la cifra
adiacente dopo averla incrementata di 1. Esempio: [1|6][6|3][11|11] diventa [2|1][1|4][4|4]
• [-1|-1]: copia “a specchio” la tessera adiacente. La tessera può essere posizionata in qualunque
posizione e le sue cifre vegono sostituite con le cifre della tessera adiacente in ordine inverso. Esempio:
[1|2][2|3][12|21] diventa [1|2][2|3][3|2]
*/
void put_tessera_speciale(Row *piano,int size_piano,Row *row,int pos,Tessera tessera){
  if(pos>=row->size){
    extend_arr_tessere(row);
    ++row->size;
  }
  if(tessera.n1==11){
    //sommo 1 a tutte le tessere
    for(int i=0;i<size_piano;i++){
      Row *r=&piano[i];
      Tessera *tessere=r->tessere;
      for(int j=0;j<r->size;j++){
        //se 4%6=4 e 4+1=5, quindi va bene
        //se 6%6=0 e 0+1=1, quindi va bene
        tessere[j].n1=(tessere[j].n1%6)+1; 
        tessere[j].n2=(tessere[j].n2%6)+1;
      }
    }
    
    if(pos>0 && row->tessere[pos-1].selected){
      tessera.n1=row->tessere[pos-1].n2;
      tessera.n2=row->tessere[pos-1].n2;
    }else if(row->tessere[pos+1].selected){
      tessera.n1=row->tessere[pos+1].n1;
      tessera.n2=row->tessere[pos+1].n1;
    }

  }

  if(tessera.n1==-1){
    if(pos>0 && row->tessere[pos-1].selected){
      tessera.n1=row->tessere[pos-1].n2;
      tessera.n2=row->tessere[pos-1].n1;
    } else if(row->tessere[pos+1].selected){
      tessera.n1=row->tessere[pos+1].n2;
      tessera.n2=row->tessere[pos+1].n1;
    }
  }
  //se è zero inserisco normalmente
  if(pos<0){
    put_front_tessera(piano,size_piano,row,tessera);
    return;
  }
 // tessera.selected=true;
  row->tessere[pos]=tessera;

}
bool posiziona_tessera(Row *piano,int *size_piano,Tessera tessera){
  Row *r_0=&piano[0];
  if(r_0->size==0){
    r_0->tessere[0]=tessera;
    r_0->size=1;
    return true;
  }
  int num_scelte=0;
  int *scelte=scelte_possibili(piano,*size_piano,tessera,&num_scelte);
  int s=-1;
  if(num_scelte<=0){
    return false;
  }
  if(num_scelte>1){
    while(s<0 || s>=num_scelte){
      printf("Scelte possibili:\n");
      print_scelte(scelte,num_scelte);
      scanf("%d",&s);
    }
  }else{
    s=0; //se la scelta è solo 1 la inserisco in automatico
  }
  int pos=scelte[s*2+1]; //num col
  int num_row=scelte[s*2]; //num row
  Row *r=&piano[num_row];
  //put_tessera()
  if(pos>=0){
    //put_first()
    if(is_special(tessera)){
      put_tessera_speciale(piano,*size_piano,r,pos,tessera);
    }else{
      put_tessera(r,tessera,pos);
    }
  }else{ //pos=-1
    //put_tessera
    if(is_special(tessera)){
      put_tessera_speciale(piano,*size_piano,r,pos,tessera);
    }else{
      put_front_tessera(piano,*size_piano,r,tessera);
    }
    pos=0;
  }

  if(num_row+1>=*size_piano || !piano[num_row+1].tessere[pos].selected){

    char scelta=0;
    while(scelta!='v' && scelta!='h'){
      printf("Digita v o h (v=vertical e h=horizontal)\n");
      scanf(" %c",&scelta);
    }
    if(scelta=='v'){
      if(num_row+1>=*size_piano){
        ++*size_piano;
        piano[num_row+1].tessere=create_arr_tessere(r->size);
        piano[num_row+1].size=r->size;
      }
      Row *under_row=&piano[num_row+1];

      if(r->size>under_row->size){
        int old_size=under_row->size;
        under_row->size=r->size;
        extend_arr_tessere(under_row);
        for(int i=old_size;i<under_row->size;i++){
          under_row->tessere[i].n1=-1;
          under_row->tessere[i].n1=-1;
          under_row->tessere[i].selected=false;
          under_row->tessere[i].vertical=false;
        }
        
      }
      r->tessere[pos].vertical=true;
      //[3|1]
      if(pos+1<r->size && match_left(r->tessere[pos],r->tessere[pos+1])){
        if (r->tessere[pos].n2 == r->tessere[pos+1].n1 && r->tessere[pos+1].n1!=0) { //se è tessera [0|0] mettila com'è
          int n2=r->tessere[pos].n2;
          r->tessere[pos].n2=r->tessere[pos].n1;
          r->tessere[pos].n1=n2;
        }
      }

      under_row->tessere[pos]=r->tessere[pos];

      r->tessere[pos].n2=r->tessere[pos].n1; //per la tessera in alto voglio lasciare invariato solo n1, n2 sarà uguale ad n1 avranno lo stesso valore per comodità

      under_row->tessere[pos].n1=under_row->tessere[pos].n2; // per la tessera più in alto voglio lasciare invariato solo n2, n1 sarà uguale ad n1
    }
  }


  /*
  if(pos>l->start_index){
    put_last(l,tessera);
  }else if(pos<l->start_index){
    put_first(l,tessera);
  }
  */
  free(scelte);
  return true;
}

void game_start(Tessera * tessere, Row * piano, Tessera *speciali,int * size_tessere, int * size_piano,int *size_speciali) {

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


Row *mod_ai(Tessera * tessere, Row *piano, Tessera *speciali,int size_tessere, int size_piano,int size_speciali){


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
            //printf("put\n");
            put_tessera(r,t,pos);

           // break;
          }else{
            //printf("put\n");

            put_front_tessera(piano,size_piano,r,t);
            //break;
          }
        }
        /*
        for(int j=0;j<num_scelte;j++){
          int pos=scelte[j*2+1];
          int num_row=scelte[j*2];
          Row *r=&game[num_row];
          if(pos>=0){
            printf("put\n");
            put_tessera(r,t,pos);
          }else{
            t.selected=true;
            put_front_tessera(game,1,r,tessere[i]);
          }
          Tessera *new_tessere=copy_tessere(tessere,size_tessere);
          Row *game_2=mod_ai(new_tessere,game_1,speciali,size_tessere,size_piano,size_speciali);
          if(score_update(game_1,1)<score_update(game_2,1)){
            game_1=game_2;
          }
        }
        */
        put=true;
      }
     // print_giocate(piano,size_piano);

    }
    if(!put){
      i++;
    }else{
      i=0;
    }

 
    //print_giocate(piano,1);


    //printf("gamefinished:%d\n",game_finished(new_tessere,game,size_game_tessere,1));
  }

  //print_giocate(piano,1);
  //Row *temp_piano=copy_piano(piano,size_piano);
  //piano=copy_piano(temp_piano,size_piano);
  //print_giocate(piano,1);

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

    new_piano=mod_ai(copia_tessere,new_piano,speciali,copia_size_tessere,size_piano,size_speciali);
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
  
