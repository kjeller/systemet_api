#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include "funktioner.h"

/* Här nedan finns de printfunktioner som andvänds. */
void list_products(item* ptr, int size) {
  printf("\n  n |  ID   |                  Namn                   |   Pris   |   Volym   |    %%   |\n");
  for (int i = 0; i < size; i++) {
      printf(" %02d ", (i + 1));
      printf(" %5d  ", (ptr+i)->varunummer);
      printf(" %40s  ", (ptr+i)->namn);
      printf(" %.2f kr   ", (ptr+i)->pris);
      printf(" %.1f ml   ", (ptr+i)->volym);
      printf(" %.1f\n", (ptr+i)->alkoholhalt);
  }
}

void details(item *ptr, int index) {
  printf("ID:        %5d\n", (ptr+index)->varunummer);
  printf("Name:      %s\n", (ptr+index)->namn);
  printf("Price:     %.2f kr\n", (ptr+index)->pris);
  printf("Volume:    %.1f ml\n", (ptr+index)->volym);
  printf("Style:     %s\n", (ptr+index)->stil);
  printf("Type:      %s\n", (ptr+index)->typ);
  printf("Packaging: %s\n", (ptr+index)->forpackning);
  printf("Country:   %s\n", (ptr+index)->land);
  printf("Producer:  %s\n", (ptr+index)->producent);
  printf("Alcohol:   %.1f%%\n\n", (ptr+index)->alkoholhalt);
}

/* Här nedan finns de mindre funktioner som används vid sortering.*/
int compare_int(int a, int b) {
  if (a < b) {
    return -1;
  } else if (a == b) {
    return 0;
  } else {
    return 1;
  }
}

int compare_str(char *a, char *b) {
  int length;

  if (strlen(a) < strlen(b)) {
    length = strlen(a);
  } else {
    length = strlen(b);
  }

  char tmp_a[length], tmp_b[length];

  for (int i = 0; i < length; i++) {
    tmp_a[i] = tolower(a[i]);
    tmp_b[i] = tolower(b[i]);
  }

  tmp_a[length] = '\0';
  tmp_b[length] = '\0';

  return(strcmp(tmp_a, tmp_b));
}

void swap(item *a, item *b) {
  struct item temp;
  temp = *b;
  *b = *a;
  *a = temp;
}

/*
 *   Här nere finns de sort funktioner som andvänds.
 *   Vi har valt bubblesort då programmet max ska hantera 100 olika artiklar.
 */
void sort_by_name(item *ptr, int size) {
  int sum;
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (strcmp((ptr+i)->namn, (ptr+j)->namn) < 0) {
        swap((ptr+i), (ptr+j));
      }
      sum++;
    }
  }
}

void sort_by_number(item *ptr, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (compare_int((ptr+i)->varunummer, (ptr+j)->varunummer) < 0) {
        swap((ptr+i), (ptr+j));
      }
    }
  }
}

void sort_by_price(item *ptr, int size) {
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      if (compare_int((ptr+i)->pris, (ptr+j)->pris) < 0) {
        swap((ptr+i), (ptr+j));
      }
    }
  }
}
