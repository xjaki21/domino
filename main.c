#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

#include <time.h>

#include <string.h>

#include <conio.h>

#include "logic.h"

int main() {
  srand(time(NULL));
  int size_speciali = 3;
  struct Tessera * speciali = (struct Tessera * ) malloc(sizeof(struct Tessera) * size_speciali);
  init_speciali(speciali, size_speciali);
  /*
[0|0]: può essere accostata a qualunque altra tessera. Esempio: [1|2][0|0][5|6]
*/

  struct Tessera * tessere = (struct Tessera * ) malloc(sizeof(struct Tessera) * 21);

  int size_tessere = rand() % 21 + 2;
  printf("N=");
  scanf("%d", & size_tessere);

  tessere = (struct Tessera * ) realloc(tessere, sizeof(struct Tessera) * size_tessere);

  // tessere giocate/scelte dal giocatore, il numero viene aggiornato ogni qualvolta che si aggiunge una tessera
  struct Tessera * giocate = (struct Tessera * ) malloc(sizeof(struct Tessera * ) * 1);
  int size_giocate = 0;
  int score = 0;
  int input = 0;

  init(tessere, size_tessere);
  printf("\e[1;1H\e[2J"); // regex che pulisce schermo

  printf("Score=%d\n", score);
  print_giocate(giocate, size_giocate);
  print_disponibili(tessere, speciali, size_tessere, size_speciali);
  printf("Scegli una tessera:\n");

  while (!game_finished(tessere, giocate, size_tessere, size_giocate)) {

    bool selected = false;
    while (!selected) {
      scanf("%d", & input);

      if (input > 0 && input <= size_tessere) {
        // int index = get_index(tessere, size_tessere, input);
        int index = input - 1;
        bool match = false;
        // se ho giocato almeno una tessera faccio il controllo se i numeri sono adiacenti
        if (size_giocate > 0) {
          bool matchFirst = match_first(tessere[index], giocate[0]); // controllo se la tessera selezionata è adiacente con la prima tessera
          bool matchLast = match_last(tessere[index], giocate[size_giocate - 1]); // controllo se la tessera selezionata è adiacente con l'ultima tessera
          match = matchFirst || matchLast;

          if (matchFirst && matchLast) {
            printf("Posiziona a sinistra 's' o posiziona a destra 'd'\n");
            char put = 0;
            while (put != 'd' && put != 's') {
              scanf("%c", & put);
            }
            if (put == 'd') {
              giocate = put_last(giocate, & size_giocate, tessere[index]);
            } else {
              giocate = put_first(giocate, & size_giocate, tessere[index]);
            }
          } else if (matchFirst) {
            giocate = put_first(giocate, & size_giocate, tessere[index]);
          } else if (matchLast) {
            giocate = put_last(giocate, & size_giocate, tessere[index]);
          }
        } else {
          match = true;
          // put_last(giocate,&size_giocate,tessere[index]);
          giocate[0] = tessere[index];
          size_giocate++;
        }
        if (match) {
          tessere = remove_tessera(tessere, & size_tessere, index);
          selected = true;
        } else {
          printf("Scegli una tessera valida!\n");
        }
      } else if (input < 0 && abs(input) <= size_speciali) {
        int index = abs(input) - 1;
        selected = true;
        size_giocate++;
        giocate = (struct Tessera * ) realloc(giocate, sizeof(struct Tessera) * size_giocate);
        printf("Posiziona a sinistra 's' o posiziona a destra 'd'\n");
        char put = 0;
        if (size_giocate == 1) {
          giocate[size_giocate - 1] = speciali[index];
        } else {
          while (put != 'd' && put != 's') {
            scanf("%c", & put);
          }
          if (put == 'd') {
            giocate[size_giocate - 1] = speciali[index];
            // giocate=put_last(giocate,&size_giocate,tessere[index]);
          } else {}
        }
      } else {
        printf("\nScegli una tessera tra quelle disponibili (es. %s)\n", string_tessera(tessere[0]));
      }
    }
    score = score_update(giocate, size_giocate);
    printf("\e[1;1H\e[2J");
    printf("Score=%d\n", score);
    print_giocate(giocate, size_giocate);
    print_disponibili(tessere, speciali, size_tessere, size_speciali);
    printf("Scegli una tessera:\n");

    // printf("%s",input);
  }
  printf("La partita e' terminata! Non ci sono piu' tessere giocabili");

  free(tessere);
  free(giocate);
}