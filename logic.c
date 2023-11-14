
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

struct tessera {
  int n1;
  int n2;
  int num;
  bool selected;
};

void init(struct tessera * tessera, int size_tessere) {
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

bool match_first(struct tessera a,struct tessera b){
    return a.n1==b.n1 || a.n2==b.n1;
}
bool match_last(struct tessera a,struct tessera b){
    return a.n1==b.n2 || a.n2==b.n2;
}
struct tessera* put_first(struct tessera* tessere, int* size, struct tessera new_tessera) {
    *size+=1;
    struct tessera* new_arr = (struct tessera*)malloc(sizeof(struct tessera) * (*size));
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

struct tessera* put_last(struct tessera* tessere, int* size, struct tessera new_tessera) {
    struct tessera* new_arr = (struct tessera*)malloc(sizeof(struct tessera) * (*size + 1));
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

bool game_finished(struct tessera *tessere,struct tessera *giocate,int size_tessere,int size_giocate){
    bool finished=true;
    struct tessera last=giocate[size_giocate-1];
    struct tessera first=giocate[0];
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

char * string_tessera(struct tessera tessera) {
  char * str = (char * ) malloc(sizeof(char) * 4);
  sprintf(str, "[%d|%d]", tessera.n1, tessera.n2); // concateno la stringo con gli elementi
  return str;
}

void print_disponibili(struct tessera * tessera, int size) {
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
 int j=size/2;
 int k=0;
 int c=0;
 if(size%2!=0){
    j++;
 }
 for(int i=0;i<size;i++){
    /*
    if(i%2==0){
        c=k;
        k++;
    }else{
        c=j;
        j++;
    }
    */
    printf("%d. [%d|%d]\t", tessera[i].num, tessera[i].n1, tessera[i].n2);
    printf("\n");
    /*
    if ((i + 1) % 2 == 0) {
        printf("\n");
    }
    */
 }
 printf("\n");
}

void print_giocate(struct tessera * tessera, int size) {
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
struct tessera * remove_tessera(struct tessera * tessera, int * size, int index) {
  struct tessera * new_arr = (struct tessera * ) malloc(sizeof(struct tessera) * ( * size - 1));
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

int get_index(struct tessera * tessera, int size, int num) {
  int index = 0;
  for (int i = 0; i < size; i++) {
    if (tessera[i].num == num) {
      index = i;
      break;
    }
  }
  return index;
}



int score_update(struct tessera*tessere,int size){
    int score=0;
    for(int i=0;i<size;i++){
        score+=tessere[i].n1+tessere[i].n2;
    }
    return score;
}