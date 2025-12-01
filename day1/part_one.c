#include <stdio.h>

int main() {
  FILE* fptr = fopen("input.txt", "r");

  int currentDial = 50;
  int password = 0;

  char direction;
  int rotations;

  while (fscanf(fptr, "%c%d\n", &direction, &rotations) == 2) {
    if (direction == 'L') {
      for (int i = 0; i < rotations; i++) {
        currentDial--;
        if (currentDial < 0) {
          currentDial = 99;
        }
      }
    } else {
      for (int i = 0; i < rotations; i++) {
        currentDial++;
        if (currentDial > 99) {
          currentDial = 0;
        }
      }
    }
    if (currentDial == 0) {
      password++;
    }
  }

  printf("Password: %d", password);

  fclose(fptr);
  return 0;
}
