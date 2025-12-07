#include <stdio.h>

int main() {
  FILE* fptr = fopen("input.txt", "r");

  int lines = 0;
  while(!feof(fptr))
  {
    char ch = fgetc(fptr);
    if(ch == '\n')
    {
      lines++;
    }
  }
  int lineLength = lines - 1;
  rewind(fptr);

  char lineBuffers[lines][lineLength + 2];

  for (int i = 0; i < lines; i++) {
    fgets(lineBuffers[i], lineLength + 2, fptr);
  }

  int noOfSplits = 0;
  for (int row = 1; row < lines; row++) {
    for (int column = 0; column < lineLength; column++) {
      // Start
      if (lineBuffers[row - 1][column] == 'S' && lineBuffers[row][column] == '.') {
        lineBuffers[row][column] = '|';
      }

      // Splitters
      if (lineBuffers[row][column] == '^' && lineBuffers[row - 1][column] == '|') {
        lineBuffers[row][column - 1] = '|';
        lineBuffers[row][column + 1] = '|';
        noOfSplits++;
      }

      if (lineBuffers[row][column] == '.' && lineBuffers[row - 1][column] == '|') {
        lineBuffers[row][column] = '|';
      }
    }
  }

  printf("Number of splits: %d\n", noOfSplits);
  fclose(fptr);
  return 0;
}
