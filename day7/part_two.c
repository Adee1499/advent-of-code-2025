#include <stdio.h>
#include <string.h>

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

  unsigned long long currentRow[lineLength];
  unsigned long long nextRow[lineLength];
  memset(currentRow, 0, sizeof(currentRow));

  for (int column = 0; column < lineLength; column++) {
    if (lineBuffers[0][column] == 'S') {
      currentRow[column] = 1;
    }
  }

  for (int row = 1; row < lines; row++) {
    memset(nextRow, 0, sizeof(nextRow));

    for (int column = 0; column < lineLength; column++) {
      if (lineBuffers[row][column] == '^') {
        nextRow[column - 1] += currentRow[column];
        nextRow[column + 1] += currentRow[column];
      } else {
        nextRow[column] += currentRow[column];
      }
    }

    memcpy(currentRow, nextRow, sizeof(currentRow));
  }

  unsigned long long noOfTimelines = 0;
  for (int column = 0; column < lineLength; column++) {
    noOfTimelines += currentRow[column];
  }

  printf("Number of timelines: %llu\n", noOfTimelines);
  fclose(fptr);
  return 0;
}
