
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "logic.h"

void init_speciali(struct Tessera *speciali,int size){
      /*
  [0|0]: può essere accostata a qualunque altra tessera. Esempio: [1|2][0|0][5|6]
  */
  speciali[0].n1=0;
  speciali[0].n2=0;
  speciali[0].num=-1;
  /*
  [11|11]: somma 1 a tutte le cifre di tutte le tessere sul piano di gioco tranne il 6 che diventa 1.
  La tessera può essere posizionata in qualunque posizione e le sue cifre vegono sostituite con la cifra
  adiacente dopo averla incrementata di 1. Esempio: [1|6][6|3][11|11] diventa [2|1][1|4][4|4]
  */
  speciali[1].n1=11;
  speciali[1].n2=11;
  speciali[1].num=-1;

  /*
  [*|*]: copia “a specchio” la tessera adiacente. La tessera può essere posizionata in qualunque
  posizione e le sue cifre vegono sostituite con le cifre della tessera adiacente in ordine inverso. Esempio:
  [1|2][2|3][12|21] diventa [1|2][2|3][3|2]
  */
  speciali[2].n1=-1;
  speciali[2].n2=-1;
  speciali[2].num=-1;
}
void init(struct Tessera * tessera, int size_tessere) {
  int n1, n2;


  for (int i = 0; i < size_tessere; i++) {

    bool diverso = false;
    /*
    while (!diverso)
    {
        diverso=true; //supponiamo sempre che i numeri generati siano diversi
        n1=rand()%6+1;
        n2=rand()%6+1;
        for(int j=0;j<i;j++){
            if((n1==tessera[j].n1 && n2==tessera[j].n2) || (n2==tessera[j].n1 && n1==tessera[j].n2)){ //controllo se esiste tessera uguale
                diverso=false; // i numeri generati mi danno una tessera che non è diversa rispetto a quelle già generate
                break;
            }
        }
    }
    */
    n1 = rand() % 6 + 1;
    n2 = rand() % 6 + 1;
    tessera[i].n1 = n1;
    tessera[i].n2 = n2;
    tessera[i].num=i+1;
    tessera[i].selected = false;
  }
}

bool match_first(struct Tessera a,struct Tessera b){
    return a.n1==b.n1 || a.n2==b.n1;
}
bool match_last(struct Tessera a,struct Tessera b){
    return a.n1==b.n2 || a.n2==b.n2;
}
struct Tessera* put_first(struct Tessera* tessere, int* size, struct Tessera new_tessera) {
    *size+=1;
    struct Tessera* new_arr = (struct Tessera*)malloc(sizeof(struct Tessera) * (*size));
    if (!new_arr) exit(EXIT_FAILURE);
    
    for(int i=0;i<*size;i++){
        new_arr[i]=tessere[i];
    }

    for (int i = *size - 2; i >= 0; i--) {
        new_arr[i + 1] = new_arr[i];
    }

    if (new_tessera.n2 != new_arr[1].n1) {
        int n2 = new_tessera.n2;
        new_tessera.n2 = new_tessera.n1;
        new_tessera.n1 = n2;
    }
    new_arr[0] = new_tessera;
    free(tessere);
    return new_arr;
}

struct Tessera* put_last(struct Tessera* tessere, int* size, struct Tessera new_tessera) {
    struct Tessera* new_arr = (struct Tessera*)malloc(sizeof(struct Tessera) * (*size + 1));
    if (!new_arr) exit(EXIT_FAILURE);
    
    for(int i=0;i<*size;i++){
        new_arr[i]=tessere[i];
    }
    *size=*size+1;
    if (new_tessera.n1 != tessere[*size-2].n2) {
        int n2 = new_tessera.n2;
        new_tessera.n2 = new_tessera.n1;
        new_tessera.n1 = n2;
    }
    
    new_arr[*size-1] = new_tessera;
    free(tessere);

    return new_arr;
}

bool game_finished(struct Tessera *tessere,struct Tessera *giocate,int size_tessere,int size_giocate){
    bool finished=true;
    struct Tessera last=giocate[size_giocate-1];
    struct Tessera first=giocate[0];
    if(size_giocate>0){
        for(int i=0;i<size_tessere;i++){
            if(match_first(tessere[i],first) || match_last(tessere[i],last)){
                finished=false;
                break;
            }
        }
    }else{
        finished=false;
    }
    return finished;
}

char * string_tessera(struct Tessera tessera) {
  char * str = (char * ) malloc(sizeof(char) * 4);
  sprintf(str, "[%d|%d]", tessera.n1, tessera.n2); // concateno la stringo con gli elementi
  return str;
}

void print_disponibili(struct Tessera *tessere, struct Tessera *speciali,int size_tessere,int size_speciali) {
  printf("Tessere disponibili:\n");
  /*
  int n = 0;
  int k = 1;
  int j = 1 + size / 2;
  if (size % 2 != 0) {
    j++;
  }
  for (int i = 0; i < size; i++) {
    if (i % 2 == 0) {
      n = k;
      k++;
    } else {
      n = j;
      j++;
    }
    printf("%d. [%d|%d]\t", n, tessera[i].n1, tessera[i].n2);
    tessera[i].num = n;
    if ((i + 1) % 2 == 0 || i + 1 >= size) {
      printf("\n");
    }
  }
  */
 int righe=10;
 int col=((size_tessere)/righe)+1; //-3 per le tessere speciale
 int count_col=0;
 int resto_last_col=(size_tessere)%righe; //-3 per le tessere speciale
 for(int i=0;i<righe;i++){
  if(resto_last_col==i){
    col--;
  }
  for(int j=0;j<col;j++){
    printf("%d. [%d|%d]\t", tessere[i+j*10].num, tessere[i+j*10].n1, tessere[i+j*10].n2);
  }

  printf("\n");

  //printf("%d. [%d|%d]\t", tessera[i].num, tessera[i].n1, tessera[i].n2);
  /*
  if((i+1)%col==0){
    printf("\n");
    count_col=0;
  }
  */
    //printf("\n");
    
 }
 if(size_speciali>0){
  printf("---TESSERE SPECIALI----\n");
  for(int i=0;i<size_speciali;i++){
  printf("-%d. [%d|%d]\n",i+1,speciali[i].n1,speciali[i].n2);
 }
 }
 printf("\n");
 
}

void print_giocate(struct Tessera * tessera, int size) {
  printf("Tessere giocate:\n");
  for (int i = 0; i < size; i++) {
    printf("[%d|%d]\t", tessera[i].n1, tessera[i].n2);
    // printf("\n");
  }
  printf("\n");
}

/*
rimuove l'elemento n dell'array di tessera
*/
struct Tessera * remove_tessera(struct Tessera * tessera, int * size, int index) {
  struct Tessera * new_arr = (struct Tessera * ) malloc(sizeof(struct Tessera) * ( * size - 1));
  if (!new_arr)
    exit(EXIT_FAILURE);

  int j = 0;
  for (int i = 0; i < * size; i++) {
    if (i != index) {
      new_arr[j] = tessera[i];
      j += 1;
    }
  }
  * size -= 1;
  for(int i=0;i<*size;i++){
    new_arr[i].num=i+1;
  }
  free(tessera);
  return new_arr;
}
/*
trova l'indice del numero della tessera corrispondente
*/
int get_index(struct Tessera * tessera, int size, int num) {
  int index = 0;
  for (int i = 0; i < size; i++) {
    if (tessera[i].num == num) {
      index = i;
      break;
    }
  }
  return index;
}



int score_update(struct Tessera*tessere,int size){
    int score=0;
    for(int i=0;i<size;i++){
        score+=tessere[i].n1+tessere[i].n2;
    }
    return score;
}