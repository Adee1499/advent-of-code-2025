#include <math.h>
#include <stdio.h>

int main() {
  FILE* fptr = fopen("input.txt", "r");

  fseek(fptr, 0L, SEEK_END);
  int rowLength = sqrt(ftell(fptr));
  rewind(fptr);

  char row[rowLength + 1];
  int rolls[rowLength][rowLength];

  int currentRow = 0;
  while (fscanf(fptr, "%s", row) == 1) {
    for (int i = 0; i < rowLength; i++) {
      if (row[i] == '.') rolls[currentRow][i] = 0;
      else rolls[currentRow][i] = 1;
    }
    currentRow++;
  }

  int accessibleRolls = 0;
  for (int i = 0; i < rowLength; i++) {
    for (int j = 0; j < rowLength; j++) {
      if (rolls[i][j] == 0) {
        continue;
      }
      int adjacents = 0;

      // Top left
      if (i > 0 && j > 0 && rolls[i - 1][j - 1] == 1) adjacents++;

      // Top
      if (i > 0 && rolls[i - 1][j] == 1) adjacents++;

      // Top right
      if (i > 0 && j < rowLength - 1 && rolls[i - 1][j + 1] == 1) adjacents++;

      // Right
      if (j < rowLength - 1 && rolls[i][j + 1] == 1) adjacents++;

      // Bottom right
      if (i < rowLength - 1 && j < rowLength - 1 && rolls[i + 1][j + 1] == 1) adjacents++;

      // Bottom
      if (i < rowLength - 1 && rolls[i + 1][j] == 1) adjacents++;

      // Bottom left
      if (i < rowLength - 1 && j > 0 && rolls[i + 1][j - 1] == 1) adjacents++;

      // Left
      if (j > 0 && rolls[i][j - 1] == 1) adjacents++;

      if (adjacents < 4) accessibleRolls++;
    }
  }

  printf("Accessible rolls: %d\n", accessibleRolls);

  return 0;
}
