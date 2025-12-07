#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum {
  ADD,
  MULTIPLY
} Operation;

typedef struct {
  Operation operation;
  long numbers[1000];
} Problem;

void parseProblems(FILE* fptr, Problem** problems, int noOfRows);

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
  rewind(fptr);

  const int ROWS = lines;
  Problem* problems[1000];
  parseProblems(fptr, problems, ROWS);

  unsigned long long total = 0;
  for (int i = 0; i < 1000; i++) {
    Operation op = problems[i]->operation;
    unsigned long long result = op == MULTIPLY ? 1 : 0;
    for (int j = 0; j < ROWS; j++) {
      if (problems[i]->numbers[j] == 0) continue;
      if (op == MULTIPLY) {
        result *= problems[i]->numbers[j];
      } else {
        result += problems[i]->numbers[j];
      }
    }
    total += result;
  }

  printf("Grand total: %llu", total);
  fclose(fptr);
  return 0;
}

void parseOperations(const char* s, Operation* operations) {
  int i = 0;

  while (*s != '\0') {
    if (*s == '*') {
      operations[i++] = MULTIPLY;
    } else if (*s == '+') {
      operations[i++] = ADD;
    }

    s++;
  }
}

int checkSeparatorColumn(const char lineBuffers[][4096], int noOfRows, int column) {
  int isSeparator = 1;

  for (int i = 0; i < noOfRows; i++) {
    if (lineBuffers[i][column] == ' ' || lineBuffers[i][column] == '\0' || lineBuffers[i][column] == '\n') {
      isSeparator = 1;
    } else {
      isSeparator = 0;
      break;
    }
  }

  return isSeparator;
}



void parseProblems(FILE* fptr, Problem** problems, int noOfRows) {
  char lineBuffers[noOfRows][4096];

  for (int i = 0; i < noOfRows; i++) {
    fgets(lineBuffers[i], sizeof(lineBuffers[i]), fptr);
  }
  int rowLength = strlen(lineBuffers[0]);

  int currentProblem = 0;
  char numberBuffers[noOfRows][6];
  memset(numberBuffers, 0, noOfRows * sizeof(char[6]));
  int currentDigit = 0;
  for (int column = 0; column < rowLength; column++) {
    if (checkSeparatorColumn(lineBuffers, noOfRows, column)) {
      Problem* p = malloc(sizeof(Problem) + noOfRows * sizeof(unsigned int));
      problems[currentProblem] = p;
      for (int row = 0; row < noOfRows; row++) {
        problems[currentProblem]->numbers[row] = strtol(numberBuffers[row], NULL, 10);
      }
      memset(numberBuffers, 0, noOfRows * sizeof(char[6]));
      currentDigit = 0;
      currentProblem++;
      continue;
    }

    for (int row = 0; row < noOfRows; row++) {
      numberBuffers[currentDigit][row] = lineBuffers[row][column];
    }
    currentDigit++;
  }

  // Get operations
  char opsLine[4096];
  fgets(opsLine, sizeof(opsLine), fptr);
  Operation* operations = malloc(1000 * sizeof(Operation));
  parseOperations(opsLine, operations);

  for (int i = 0; i < 1000; i++) {
    problems[i]->operation = operations[i];
  }
}
