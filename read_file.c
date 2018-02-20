#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "funktioner.h"

/*
 * Läser en fil rad för rad och åtskiljer enskilda element i en rad med ','.
 * De inlästa värdena skrivs till en allokerad plats i minnet för en post.
 */
int read_file(item **ptr, int count) {

  char *oneline, *tok;
  char envara[256];
  char delim[] = ",";
  int item_index = 0;  // Har koll på vilken struct som är aktuell
  FILE *fp;

  /* Allokerar plats i minnet åt 100 item poster. */
  if((*ptr = malloc(MAX_SIZE * sizeof(item))) == NULL) {
    printf("INTE NOG MED UTRYMME!");
    exit(-1);
  }

  if ((fp = fopen("varor.csv", "r")) == NULL) {
    fprintf(stderr, "Filen varor.csv gick inte att öppna\n");
    exit(-1);
  }

  while (fgets(envara, 256, fp)) {
    int inline_type = 0;                  // Håller koll på vilket element som ska skrivas
    envara[strlen(envara) - 1] = '\0';    // Ta bort radslutstecknet
    oneline = strdup(envara);
    tok = strtok(oneline, delim);

    /* Läser alla tills filslut */
    while (tok != NULL) {

      /* Lägger till värden till en struct beroende på vilket element som är aktivt*/
      switch (inline_type) {
        case 0: (*ptr+item_index)->varunummer  = atoi(tok);              break;
        case 1: strncpy((*ptr+item_index)->namn,  tok, MAX_SIZE);        break;
        case 2: (*ptr+item_index)->pris        = atof(tok);              break;
        case 3: (*ptr+item_index)->volym       = atof(tok);              break;
        case 4: strncpy((*ptr+item_index)->stil, tok, MAX_SIZE);         break;
        case 5: strncpy((*ptr+item_index)->typ, tok, MAX_SIZE);          break;
        case 6: strncpy((*ptr+item_index)->forpackning, tok, MAX_SIZE);  break;
        case 7: strncpy((*ptr+item_index)->land, tok, MAX_SIZE);         break;
        case 8: strncpy((*ptr+item_index)->producent, tok, MAX_SIZE);    break;
        case 9: (*ptr+item_index)->alkoholhalt = atof(tok);              break;
      }
      tok = strtok(NULL, delim);
      inline_type++;
    }
    item_index++;         // Räknar producter och håller koll på index
    if(item_index > 99) {
      fprintf(stderr, "You have reached maximum capacity! Rows will be truncated..");
      break;
    }
  }
  free(oneline); free(tok);
  fclose(fp);

  /* Reallokerar minnet till så många structs som faktiskt används.  */
  if ((*ptr = realloc(*ptr, item_index * sizeof(item))) == NULL) {
    fprintf(stderr, "Could not reallocate any more memory.");
  }
  return item_index;
}
