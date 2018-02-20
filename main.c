#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "funktioner.h"

int main() {
  int count; // Ökar för varje post.
  item *products = NULL;
  count = read_file(&products, count);
  int choice;
  bool sub_list = false, sub_save = false;
  char backup_path[] = {"varor_backup"};

  /* Hanterar inmatningar.
   * Om användaren inte matar in annat än siffror så frågas användaren igen.
   */
  while(1) {
    printf("\n\n===== MENU =====\n");
    printf("1. List contents.\n");
    printf("2. Add new items.\n");
    printf("3. Search for items.\n");
    printf("4. Save to file.\n");
    printf("5. Exit.\n");
    printf("Input: ");

    /* Sub menyer */
    if(scanf("%d", &choice) != 0) {
      switch (choice) {

        /* Listar poster som laddats in. */
        case 1:
        printf("\n\n===== LIST =====\n");
        printf("1. List by name\n");
        printf("2. List by ID.\n");
        printf("3. List by price.\n");
        printf("4. Return to main menu.\n");
        printf("Input: ");
        sub_list = true;

        /* Hanterar sub-meny inmatning. */
        while(sub_list) {
          if(scanf("%d", &choice) != 0) {
            switch (choice) {
              case 1:
              printf("\n===== LIST BY NAMES =====\n");
              sort_by_name(products, count);
              list_products(products, count);
              break;
              case 2:
              printf("\n===== LIST BY NUMBERS =====\n");
              sort_by_number(products, count);
              list_products(products, count);
              break;
              case 3:
              printf("\n===== LIST BY PRICE =====\n");
              sort_by_price(products, count);
              list_products(products, count);
              break;
              case 4: sub_list = false; break;
              default: printf("Invalid value\n"); fflush(stdin); break;
            }
          } else {
            printf("Invalid value\n");
            fflush(stdin);
          }
          if(sub_list) {
            printf("\n===== LIST =====\n");
            printf("1. List by name\n");
            printf("2. List by ID.\n");
            printf("3. List by price.\n");
            printf("4. Return to main menu.\n");
            printf("Input: ");
          }
        }
        break;

        /* Lägg till nya items */
        case 2:
        fflush(stdin);
        count = add_article(&products, count);
        printf("Added product without failure.");
        break;

        /* Söker efter items */
        case 3:
        search_article(products, count);
        break;

        /* Sparar till fil */
        case 4:
        printf("\n\n===== SAVE =====\n");
        printf("1. Save to file\n");
        printf("2. Save a backup\n");
        printf("3. Return to main menu.\n");
        printf("Input: ");
        sub_save = true;

        /* Hanterar sub-meny inmatningar. */
        while(sub_save) {
          if(scanf("%d", &choice) != 0) {
            switch (choice) {
              case 1:
              printf("\n===== SAVE TO FILE =====\n");
              char filename[100];
              printf("Please enter the name for the file (will be saved as a .csv file): ");
              str_scan(filename, 100);
              save_to_file(products, filename, count);
              break;
              case 2:
              printf("\n===== SAVE BACKUP =====\n");
              save_to_file(products, backup_path, count);
              break;
              case 3:
              /* Return to main menu */
              sub_save = false;
              break;
              default: printf("Invalid value."); fflush(stdin); break;
            }
          } else {
              printf("Invalid value.\n");
              fflush(stdin);
          }
          if(sub_save) {
            printf("\n===== SAVE =====\n");
            printf("1. Save to file\n");
            printf("2. Save a backup\n");
            printf("3. Return to main menu\n");
            printf("Input: ");
          }
        }
        break;

        case 5:
        save_to_file(products, backup_path, count);
        printf("Now exiting...");
        exit(0); break;
        default: printf("Invalid value.\nEnter a new value: "); fflush(stdin); break;
      }
    } else {
      printf("Invalid value.\nPlease enter a new value:\n");
      fflush(stdin);
    }

  }
  return 0;
}
