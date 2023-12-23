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

Linea *create_linea(){
  Linea *new=(Linea*)malloc(sizeof(Linea));
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

bool match_first(Tessera a, Tessera b) {
  if(b.n1==0){
    return true;
  }
  return a.n1 == b.n1 || a.n2 == b.n1;
}
bool match_last(Tessera a, Tessera b) {
  if(b.n1==0){
    return true;
  }
  return a.n1 == b.n2 || a.n2 == b.n2;
}

//matrice che restituisce le possibili scelte
int *scelte_possibili(Linea *piano,int size,Tessera tessera,int *num_scelte){
  int *scelte=(int*)malloc(sizeof(int)*100);
  int k=0;
  /*
  int scelte={{1,2},
              {0,1},
              {1,1}}
  */
  for(int i=0;i<size;i++){
    Tessera *a=piano[i].tessere;
    int a_size=piano[i].size;
    int start_index=piano[i].start_index;
    for(int j=0;j<a_size;j++){
      if(a[j].selected){
        if((j==0 || !a[j-1].selected) && match_first(tessera,a[j])){
          scelte[k]=i;
          scelte[k+1]=j-1;
          k=k+2;
        }
        if((j==a_size-1 || !a[j+1].selected) && match_last(tessera,a[j])){
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



void extend_arr_tessere(Linea *l){
  if(l->size>=l->capacity){
    l->tessere=(Tessera*)realloc(l->tessere,sizeof(Tessera)*l->size*2);
    if(!l->tessere) exit(EXIT_FAILURE);
    l->capacity*=2;
    //inizializzo i nuovi spazi con false e -1, perché sono "vuoti"
    for(int i=l->size;i<l->capacity;i++){
      l->tessere[i].n1=-1;
      l->tessere[i].n1=-1;
      l->tessere[i].selected=false;
      l->tessere[i].vertical=false;
    }
  }
}


void put_first(Linea *l, Tessera new_tessera) {
  //++*size;
  extend_arr_tessere(l);
  /*
  scambio in caso i due numeri siano adiacenti in verso opposto,
  esempio: [5|2] [5|1] diventa [2|5] [5|1], metto il numero adiacente in maniera giusta
  */
 int index=l->start_index;
 if(l->start_index==0){
  for(int i=l->size-1;i>=0;i--){
    l->tessere[i+1]=l->tessere[i];
  }
  index=1;
 }
  if (new_tessera.n2 != l->tessere[index].n1) {
    int n2 = new_tessera.n2;
    new_tessera.n2 = new_tessera.n1;
    new_tessera.n1 = n2;
  }
  l->tessere[index-1] = new_tessera;
  l->size++;
  

}



void put_last(Linea *l, Tessera new_tessera) {
  //Tessera * new_arr = (Tessera * ) malloc(sizeof(Tessera) * ( * size));
  extend_arr_tessere(l);
  int size=l->size;
  /*
  scambio in caso i due numeri siano adiacenti in verso opposto,
  esempio: [5|2] [5|1] diventa [2|5] [5|1], metto il numero adiacente in maniera giusta
  */

  if (new_tessera.n1 != l->tessere[size-1].n2 && l->tessere[size-1].n1!=0) { //se è tessera [0|0] mettila com'è
    int n2 = new_tessera.n2;
    new_tessera.n2 = new_tessera.n1;
    new_tessera.n1 = n2;
  }

  l->tessere[size] = new_tessera;
  l->size++;
}

bool game_finished(Tessera * tessere, Linea * piano, int size_tessere, int size_piano) {
  bool finished=true;
  for(int i=0;i<size_piano;i++){
    Tessera *tessere_linea=piano[i].tessere;
    int size_linea= piano[i].size;
    //printf("bello");
    for(int j=0;j<size_tessere;j++){
      if(match_first(tessere[j],tessere_linea[0]) || match_last(tessere[j],tessere_linea[size_linea-1])){
        finished=false;
      }
    }
    //printf("okokok");
  }
  return finished;
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

int max_linea(Linea *piano,int size){
  int max=piano[0].size;
  for(int i=1;i<size;i++){
    if(piano[i].size>max){
      max=piano[i].size;
    }
  }
  return max;
}
void print_giocate(Linea * piano, int size) {

  printf("Tessere giocate:\n");
  printf("\t  ");
  for(int i=0;i<max_linea(piano,size);i++){
    printf("%d\t  ",i);
  }
  printf("%d\n",max_linea(piano,size));
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

void update_screen(Tessera * tessere, Linea * piano, Tessera * speciali, int size_tessere, int size_piano, int size_speciali, int score) {
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

int score_update(Linea *piano, int size) {
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



void put_tessera(Linea *l,Tessera tessera,int pos){
  if(pos>=l->size){
    extend_arr_tessere(l);
    ++l->size;
  }
   //metto a sinistra la tessera
  if(match_first(tessera,l->tessere[pos+1])){
    if (tessera.n2 != l->tessere[pos+1].n1 && l->tessere[pos+1].n1!=0) { //se è tessera [0|0] mettila com'è
      int n2=tessera.n2;
      tessera.n2=tessera.n1;
      tessera.n1=n2;
    }
  }
  
  
   //metto a destra la tessera
  if(pos>0 && match_last(tessera,l->tessere[pos-1])){
    if(tessera.n1 !=l->tessere[pos-1].n2 && l->tessere[pos-1].n1!=0){
    int n2=tessera.n2;
    tessera.n2=tessera.n1;
    tessera.n1=n2;
    }
  }
  
  l->tessere[pos]=tessera;
}
bool scegli_tessera(Linea *piano,int *size_piano,Tessera tessera){
  Linea *l_0=&piano[0];
  if(l_0->size==0){
    l_0->tessere[0]=tessera;
    l_0->size=1;
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
  int pos=scelte[s*2+1];
  int num_linea=scelte[s*2];
  Linea *l=&piano[num_linea];
  //put_tessera()
  if(pos>=0){
    //put_first()
    put_tessera(l,tessera,pos);
  }else{
    //put_tessera
  }

  char scelta=0;
  while(scelta!='v' && scelta!='h'){
    printf("Digita v o h (v=vertical e h=horizontal)\n");
    scanf(" %c",&scelta);
  }
  if(scelta=='v'){
    if(num_linea+1>=*size_piano){
      ++*size_piano;
      piano[num_linea+1].tessere=create_arr_tessere(l->size);
      piano[num_linea+1].size=l->size;
    }
    Linea *under_line=&piano[num_linea+1];

    if(l->size>under_line->size){
      int old_size=under_line->size;
      under_line->size=l->size;
      extend_arr_tessere(under_line);
      for(int i=old_size;i<under_line->size;i++){
        under_line->tessere[i].n1=-1;
        under_line->tessere[i].n1=-1;
        under_line->tessere[i].selected=false;
        under_line->tessere[i].vertical=false;
      }
      
    }
    l->tessere[pos].vertical=true;
    under_line->tessere[pos]=l->tessere[pos];

    l->tessere[pos].n2=l->tessere[pos].n1; //per la tessera in alto voglio lasciare invariato solo n1, n2 sarà uguale ad n1 avranno lo stesso valore per comodità

    under_line->tessere[pos].n1=under_line->tessere[pos].n2; // per la tessera più in alto voglio lasciare invariato solo n2, n1 sarà uguale ad n1
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

bool add_tessera(Linea * linea, Tessera new_tessera) {
  bool selected = false; //mi serve per dire se ho scelto una tessere valida!
  
  Tessera * giocate = linea -> tessere;
  int * size_giocate = &linea -> size;
  bool match = false;
  bool matchFirst = match_first(new_tessera, giocate[0]); // controllo se la tessera selezionata è adiacente con la prima tessera
  bool matchLast = match_last(new_tessera, giocate[ *size_giocate - 1]); // controllo se la tessera selezionata è adiacente con l'ultima tessera
  match = matchFirst || matchLast;
  if(*size_giocate>0){
  if (matchFirst && matchLast) {
    printf("Posiziona a sinistra 's' o posiziona a destra 'd'\n");
    char put = 0;
    while (put != 'd' && put != 's') {
      scanf("%c", & put);
    }
    if (put == 'd') {
      //giocate = put_last(giocate, size_giocate, new_tessera);
      //linea -> tessere = giocate; //l'indirizzo di memoria di ogni linea viene cambiato quando aggiungo!, quindi devo ricordarmi di memorizzarlo nel piano
      put_last(linea,new_tessera);
    } else {
      //giocate = put_first(giocate, size_giocate, new_tessera);
      //linea -> tessere = giocate;
      put_first(linea,new_tessera);
    }
  } 
  else if (matchFirst) {
    //giocate = put_first(giocate, size_giocate, new_tessera);
    //linea -> tessere = giocate;
    put_first(linea,new_tessera);

  } 
  else if (matchLast) {
    //giocate = put_last(giocate, size_giocate, new_tessera);
    //linea -> tessere = giocate;
    put_last(linea,new_tessera);

  } 
  }
  else{
    match=true;
    giocate[0]=new_tessera;
    ++*size_giocate;
  }
  return match;

}

void add_special(Linea * linea, Tessera new_tessera) {
  Tessera *giocate=linea->tessere;
  int *size_giocate=&linea->size;
  if ( *size_giocate == 0) {
    ++*size_giocate;
    giocate[0] = new_tessera;
  } 
  else {
    printf("Posiziona a sinistra 's' o posiziona a destra 'd'\n");
    char put = 0;
    while (put != 'd' && put != 's') {
      scanf("%c", & put);
    }
    if (new_tessera.n1 == 11) {
      for (int i = 0; i < * size_giocate; i++) {
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
      if (new_tessera.n1 == 11) { //tessera somma tutti 1
        new_tessera.n1 = giocate[ * size_giocate - 1].n2;
        new_tessera.n2 = new_tessera.n1;
      }
      if (new_tessera.n1 == -1) { // tessera specchio
        new_tessera.n1 = giocate[ * size_giocate - 1].n2;
        new_tessera.n2 = giocate[ * size_giocate - 1].n1;
      }
      //giocate = put_last(giocate, size_giocate, new_tessera);
      //linea->tessere=giocate;
      put_last(linea,new_tessera);
      // giocate=put_last(giocate,&size_giocate,tessere[index]);
    } else {
      if (new_tessera.n1 == 11) { // tessera somma tutti 1
        new_tessera.n1 = giocate[0].n1;
        new_tessera.n2 = new_tessera.n1;
      }
      if (new_tessera.n1 == -1) { //tessera specchio
        new_tessera.n1 = giocate[0].n2;
        new_tessera.n2 = giocate[0].n1;
      }
      //giocate = put_first(giocate, size_giocate, new_tessera);
      //linea->tessere=giocate;
      put_first(linea,new_tessera);
    }

  }
}