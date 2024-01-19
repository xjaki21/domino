#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#include "tessere.h"

Row *create_row(){
  Row *new=(Row*)malloc(sizeof(Row));
  new->capacity=10;
  new->tessere=(Tessera*)malloc(sizeof(Tessera)*new->capacity);
  new->size=0;

  return new;
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

char * string_tessera(Tessera tessera) {
  char * str = (char * ) malloc(sizeof(char) * 4);
  sprintf(str, "[%d|%d]", tessera.n1, tessera.n2); // concateno la stringo con gli elementi
  return str;
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
    printf("%d. {%d,%d}\n",i+1,m[k],m[k+1]);
    k=k+2;
  }
}

void print_disponibili(Tessera * tessere, Tessera * speciali, int size_tessere, int size_speciali) {
  printf("Tessere disponibili:\n");
  int righe = 10;
  int col = ((size_tessere) / righe) + 1;
  int resto_last_col = (size_tessere) % righe; 
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


int char_to_int(char*s){
  int sum=0;
  int sign=1;
  int i=0;
  if(s[0]=='-'){
    sign=-1;
    i=1;
  }
  while(i<strlen(s)){
    int cifra=s[i]-48;
    if(cifra<0 || cifra>=10) // se non è una cifra valida restituisco 0;
      return 0;
    sum=sum+cifra*pow(10,strlen(s)-i-1);
    i++;
  }
  return sum*sign;
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
  int s;
  if(num_scelte<=0){
    return false;
  }
  printf("Tessera scelta: %s\n",string_tessera(tessera));

  if(num_scelte>1){
    char keys[10];
    do{
        printf("Scelte possibili:\n");
        print_scelte(scelte,num_scelte);
        scanf("%s",&keys);
        s=char_to_int(keys);
   }while(s<=0 || s>num_scelte);
   s=s-1; //per sistemare l'index, si accettano in input valori da 1 a x, per sistemare l'index devo fare -1
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
  free(scelte);
  return true;
}