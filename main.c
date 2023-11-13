#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include <time.h>

#include <string.h>

#include <conio.h>

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
    tessera[i].selected = false;
  }
}

char * string_tessera(struct tessera tessera) {
  char * str = (char * ) malloc(sizeof(char) * 4);
  sprintf(str, "[%d|%d]", tessera.n1, tessera.n2); // concateno la stringo con gli elementi
  return str;
}

void print_disponibili(struct tessera * tessera, int size) {
  printf("Tessere disponibili:\n");
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

int score_update(struct tessera*tessere,int size){
    int score=0;
    for(int i=0;i<size;i++){
        score+=tessere[i].n1+tessere[i].n2;
    }
    return score;
}



int main() {
  srand(time(NULL));

  struct tessera * tessere = (struct tessera * ) malloc(sizeof(struct tessera) * 21);

  int size_tessere = rand() % 21 + 2;
  printf("N=");
  scanf("%d", & size_tessere);

  tessere = (struct tessera * ) realloc(tessere, sizeof(struct tessera) * size_tessere);

  /*
  tessere giocate/scelte dal giocatore, il numero viene aggiornato ogni qualvolta che si aggiunge una tessera
  */
  struct tessera * giocate = (struct tessera * ) malloc(sizeof(struct tessera * ) * 1);
  int size_giocate = 0;
  int score = 0;

  // num_tessere=21;

  init(tessere, size_tessere);
  printf("\e[1;1H\e[2J"); // regex che pulisce schermo

  printf("Score=%d\n", score);
  print_giocate(giocate, size_giocate);
  print_disponibili(tessere, size_tessere);
  printf("Scegli una tessera:\n");

  int points = 0;
  // printf("Scegli una tessera tra quelle disponibili (es. %s digita 1)\n",string_tessera(tessere[0]));
  // print_giocate(giocate,size_giocate);

  int input = 0;
  while (true) {

    bool selected = false;
    while (!selected) {
      scanf("%d", & input);

      if (input > 0 && input <= size_tessere) {
        int index = get_index(tessere, size_tessere, input);
        bool match = false;
         // se ho giocato almeno una tessera faccio il controllo se i numeri sono adiacenti
        if (size_giocate > 0) {
            bool match_last=(tessere[index].n1 == giocate[size_giocate-1].n2) || (tessere[index].n2==giocate[size_giocate-1].n2); //controllo se la tessera selezionata è adiacente con l'ultima tessera
            bool match_first=(tessere[index].n1==giocate[0].n1) || (tessere[index].n2==giocate[0].n1); //controllo se la tessera selezionata è adiacente con la prima tessera
            match=match_last || match_first;
            //printf("%s",string_tessera(tessere[index]));
            //giocate=put_last(giocate,&size_giocate,tessere[index]);
            
          if (match_last && match_first) {
            printf("Posiziona a sinistra 's' o posiziona a destra 'd'\n");
            char put=0;
            while(put!='d' && put!='s'){
                scanf("%c",&put);
            }
            if(put=='d'){
                giocate=put_last(giocate,&size_giocate,tessere[index]);            
            }else{
                giocate=put_first(giocate,&size_giocate,tessere[index]);
            }
            /*
            logica per scambio di posizioni
            */
            match = true;
          } else if(match_first){
            giocate=put_first(giocate,&size_giocate,tessere[index]);
          }else if(match_last){
            giocate=put_last(giocate,&size_giocate,tessere[index]);
          }
        }else{
            match=true;
            //put_last(giocate,&size_giocate,tessere[index]);
            giocate[0]=tessere[index];
            size_giocate++;
        }
        

        if (match) {
          tessere = remove_tessera(tessere, & size_tessere, index);
          selected = true;
        } else {
          printf("Scegli una tessera valida!\n");
        }
      } else {
        printf("\nScegli una tessera tra quelle disponibili (es. %s)\n", string_tessera(tessere[0]));
      }
    }
    score=score_update(giocate,size_giocate);
    printf("\e[1;1H\e[2J");
    printf("Score=%d\n", score);
    print_giocate(giocate, size_giocate);
    print_disponibili(tessere, size_tessere);
    printf("Scegli una tessera:\n");

    // printf("%s",input);
  }

  free(tessere);
  free(giocate);
}