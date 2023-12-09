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
    tessera[i].num = i + 1;
    tessera[i].selected = false;
    tessera[i].vertical=false;
  }
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
Tessera * put_first(Tessera * tessere, int * size, Tessera new_tessera) {
  ++*size;
  Tessera * new_arr = (Tessera * ) malloc(sizeof(Tessera) * ( * size));
  if (!new_arr) exit(EXIT_FAILURE);

  for (int i = 0; i < * size; i++) {
    new_arr[i] = tessere[i];
  }

  for (int i = * size - 2; i >= 0; i--) {
    new_arr[i + 1] = new_arr[i];
  }
  /*
  scambio in caso i due numeri siano adiacenti in verso opposto,
  esempio: [5|2] [5|1] diventa [2|5] [5|1], metto il numero adiacente in maniera giusta
  */
  if (new_tessera.n2 != new_arr[1].n1) {
    int n2 = new_tessera.n2;
    new_tessera.n2 = new_tessera.n1;
    new_tessera.n1 = n2;
  }
  new_arr[0] = new_tessera;
  free(tessere);
  return new_arr;
}

Tessera * put_last(Tessera * tessere, int * size, Tessera new_tessera) {
  ++*size;
  Tessera * new_arr = (Tessera * ) malloc(sizeof(Tessera) * ( * size));
  if (!new_arr) exit(EXIT_FAILURE);

  for (int i = 0; i < * size; i++) {
    new_arr[i] = tessere[i];
  }

  /*
  scambio in caso i due numeri siano adiacenti in verso opposto,
  esempio: [5|2] [5|1] diventa [2|5] [5|1], metto il numero adiacente in maniera giusta
  */

  if (new_tessera.n1 != tessere[*size-2].n2 && tessere[*size-2].n1!=0) { //se è tessera [0|0] mettila com'è
    int n2 = new_tessera.n2;
    new_tessera.n2 = new_tessera.n1;
    new_tessera.n1 = n2;
  }

  new_arr[ *size-1] = new_tessera;
  free(tessere);

  return new_arr;
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

void print_giocate(Linea * piano, int size) {
  printf("Tessere giocate:\n");
  for(int i=0;i<size;i++){
    Tessera *a=piano[0].tessere;
    int size_a=piano[0].size;
    //printf("%d\t",size_a);
    for(int j=0;j<size_a;j++){
      printf("[%d|%d]\t",a[j].n1,a[j].n2);
    }
  }
  printf("\n");
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
      score+=a[j].n1+a[j].n2;
    }
  }
  return score;
}

bool add_horizontal(Linea * linea, Tessera new_tessera) {
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
      giocate = put_last(giocate, size_giocate, new_tessera);
      linea -> tessere = giocate; //l'indirizzo di memoria di ogni linea viene cambiato quando aggiungo!, quindi devo ricordarmi di memorizzarlo nel piano

    } else {
      giocate = put_first(giocate, size_giocate, new_tessera);
      linea -> tessere = giocate;
    }
  } 
  else if (matchFirst) {
    giocate = put_first(giocate, size_giocate, new_tessera);
    linea -> tessere = giocate;
  } 
  else if (matchLast) {
    giocate = put_last(giocate, size_giocate, new_tessera);
    linea -> tessere = giocate;
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
      giocate = put_last(giocate, size_giocate, new_tessera);
      linea->tessere=giocate;
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
      giocate = put_first(giocate, size_giocate, new_tessera);
      linea->tessere=giocate;
    }

  }
}