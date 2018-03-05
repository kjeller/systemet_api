#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "funktioner.h"

/* Skriver ut strängen utan \n */
int str_scan(char *dest, int max_length) {
  char * c_temp = malloc(max_length * sizeof(char));
  fflush(stdin);
  fgets(c_temp, (max_length-1), stdin);
  strtok(c_temp, "\n");
  strcat(c_temp,"\0");
  // Kollar ifall längdsträngen är större än 1
  if(!(strlen(c_temp)-1)) {
    free(c_temp);
    return 1;
  }
  strcpy(dest, c_temp);
  free(c_temp);
  return 0;
}

static int str_is_num(char *string, unsigned char size) {
  char *s, c;
  s = string; c = 0;

  // Kolla alla tecken i strängen
  while(c++, *s++) {
    if(c >= size) {
      printf("Ange ett giltigt tal:");
      fflush(stdin);
      return 1;
    }
    // När man når \n har strängen nått sitt slut
    if(*s == '\n') {
      break;
    }
    // Om det är ett nummer fortsätt till nästa
    if(isdigit(*s)) {
      continue;
    } else {
      printf("Ange ett giltigt tal:");
      fflush(stdin);
      return 1;
    }
  }
  return 0;
}

/*
 * Låter användaren mata in värden till en struct som det har
 * allokerats plats för i minnet.
 */
int add_article(item **ptr, int size) {
  /* Kollar så att användare inte matar in mer varor än gränsen enl. upg */
  if(size < MAX_SIZE) {
    item *temp = NULL;
    /* Reallokerar minne åt en ny struct */
    if((temp = realloc(*ptr, ((size+1) * sizeof(item)))) == NULL) {
      fprintf(stderr, "Inte nog med minne BEEP BOOP");
      exit(-1);
    }
    *ptr = temp;

    char * c_temp = malloc(100 * sizeof(char)); // Temporär char fält som används för inmatning med fgets

    // Clear buff
    printf("Enter ID: ");
    do {
    fgets(c_temp, 100, stdin);
  }while(str_is_num(c_temp, 7));
    sscanf(c_temp, "%d", &(*ptr+size)->varunummer);

    printf("Enter Name: ");
    while(str_scan((*ptr+size)->namn, MAX_SIZE)) {
      printf("Vänligen mata in och försök igen.");
    }

    printf("Enter Price (kr): ");
    do {
    fgets(c_temp, 100, stdin);
    }while(str_is_num(c_temp, 7));
    sscanf(c_temp, "%f", &(*ptr+size)->pris);

    printf("Enter Volym (ml): ");
    do {
    fgets(c_temp, 100, stdin);
    }while(str_is_num(c_temp, 7));
    sscanf(c_temp, "%f", &(*ptr+size)->volym);

    printf("Enter Style: ");
    while(str_scan((*ptr+size)->stil, MAX_SIZE)) {
      printf("Vänligen mata in och försök igen.");
    }

    printf("Enter Type: ");
    while(str_scan((*ptr+size)->typ, MAX_SIZE)) {
      printf("Vänligen mata in och försök igen.");
    }

    printf("Enter Pack: ");
    while(str_scan((*ptr+size)->forpackning, MAX_SIZE)) {
      printf("Vänligen mata in och försök igen.");
    }

    printf("Enter Country: ");
    while(str_scan((*ptr+size)->land, MAX_SIZE)) {
      printf("Vänligen mata in och försök igen.");
    }

    printf("Enter Producer: ");
    while(str_scan((*ptr+size)->producent, MAX_SIZE)) {
      printf("Vänligen mata in och försök igen.");
    }

    printf("Enter alcohol%%: ");
    do {
    fgets(c_temp, 100, stdin);
    }while(str_is_num(c_temp, 7));
    sscanf(c_temp, "%f", &(*ptr+size)->alkoholhalt);;

    free(c_temp);
    size++;
    return(size);
    }
  }

/*
 * Söker efter artiklar i minnet med ID eller eller namn genom
 * att jämföra posternas namn med den sökta strängen.
 * Om användaren skriver med endast ID söker funktioner endast med ID
 * och då jämförs istället ID.
 */
void search_article(item *ptr, int size) {
  char search_str[100], index_save[size];
  int n = 0;
  printf("Enter the Name or ID: ");
  str_scan(search_str, MAX_SIZE);
  printf("\n");

  /*
   * Kollar ifall användaren söker med ID,
   * alltså endast siffror.
   */
  bool ID_search = true;
  for (int i = 0; i < strlen(search_str); i++) {
    if (isalpha(search_str[i])) {
      ID_search = false;
    }
  }

  /* Användaren söker med ID */
  if (ID_search == true) {
    for (int i = 0; i < size; i++) {
      if (compare_int(atoi(search_str), ((ptr+i)->varunummer)) == 0) {
        index_save[n] = i;
        n++;
      }
    }
  /* Användaren söker mha. en sträng */
  } else {
    for (int i = 0; i < size; i++) {
      if (compare_str(search_str, ((ptr+i)->namn)) == 0) {
        index_save[n] = i;
        n++;
      }
    }
  }

  if (n == 1) {
    printf("Article found!\n");
    details(ptr, index_save[0]);    // Skriver ut detaljer om en sökt varan
  } else if (n > 1) {
    printf("%d articles found!\n", n);
    for (int j = 0; j < n; j++) {
      details(ptr, index_save[j]);  // Skriver ut detaljer om flera varor
    }
  } else {
    printf("No articles found!\n");
  }
}

/*
 * Öppnar en fil och skriver alla sparade structs i minnet till den filen
 */
void save_to_file(item *ptr, char *filename, int size) {
  FILE *file;
  // Fråga om filnamn och lägg till filändelsen.
  if ((file = fopen(strcat(filename, ".csv"), "w")) == NULL) {
    fprintf(stderr, "Could not open the file\n");
    exit(-1);
  }

  // Skriver till filen med formattering
  for (int i = 0; i < size; i++) {
    fprintf(file,"%d,%s,%f,%f,%s,%s,%s,%s,%s,%f\n",
    (ptr+i)->varunummer,(ptr+i)->namn,(ptr+i)->pris,(ptr+i)->volym,(ptr+i)->stil,
    (ptr+i)->typ,(ptr+i)->forpackning,(ptr+i)->land,(ptr+i)->producent,(ptr+i)->alkoholhalt);
  }
  printf("\n\n ===== Products has been saved in file %s =====\n", filename);
  fclose(file);
}
