#include <stdio.h>
#include <string.h>

#include "defs.h"

int main()
{
  RestaurantType *restaurant = (RestaurantType *)malloc(sizeof(RestaurantType));
  initRestaurant(restaurant, "The Cafe");

  loadResData(restaurant);
  loadPatronData(restaurant);

  int choice = -1;

  while (choice != 0) {
    printMenu(&choice);

    switch (choice) {
      case 1:
        printf("Welcome to %s:\n", restaurant->name);
        printPatrons(restaurant->patrons);
        break;
      case 2:
        printf("Welcome to %s:\n", restaurant->name);
        printReservations(&restaurant->reservation);
        break;
      case 3:
        int patId;
        printf("Please Enter a Patron ID: ");
        scanf("%d", &patId);
        printResByPatron(restaurant, patId);
        break;
      case 0:
        printf("Exiting the program...\n");
        cleanupRestaurant(restaurant);
        break;
      default:
        printf("Invalid selection. Please try again.\n");
        break;
    }
  }
  return(0);
}

void printMenu(int *choice)
{
  int c = -1;
  int numOptions = 3;

  printf("\nMAIN MENU\n");
  printf("  (1) Print patrons\n");
  printf("  (2) Print reservations\n");
  printf("  (3) Print reservations by patron\n");
  printf("  (0) Exit\n\n");

  printf("Please enter your selection: ");
  scanf("%d", &c);

  if (c == 0) {
    *choice = c;
    return;
  }

  while (c < 0 || c > numOptions) {
    printf("Please enter your selection: ");
    scanf("%d", &c);
  }

  *choice = c;
}

