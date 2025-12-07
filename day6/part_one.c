#include <stdio.h>
#include <stdlib.h>

typedef enum {
  ADD,
  MULTIPLY
} Operation;

typedef struct {
  Operation operation;
  unsigned int numbers[];
} Problem;

int parseProblems(FILE* fptr, Problem** problems, int noOfRows);

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

  const int ROWS = lines - 1;
  Problem* problems[1000];
  int noOfProblems = parseProblems(fptr, problems, ROWS);

  unsigned long long total = 0;
  for (int i = 0; i < noOfProblems; i++) {
    Operation op = problems[i]->operation;
    unsigned long long result = op == MULTIPLY ? 1 : 0;
    for (int j = 0; j < ROWS; j++) {
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

int parseNumbers(const char* s, unsigned int* numbers) {
  char *end;

  int i = 0;
  while (*s != '\0') {
    numbers[i] = strtol(s, &end, 10);

    if (s == end) {
      s++;
      continue;
    }

    i++;
    s = end;
  }

  return i;
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


int parseProblems(FILE* fptr, Problem** problems, int noOfRows) {
  int noOfProblems = 0;

  char line[4096];

  for (int i = 0; i < noOfRows; i++) {
    fgets(line, sizeof(line), fptr);
    unsigned int* numbers = malloc(1000 * sizeof(unsigned int));
    int count = parseNumbers(line, numbers);
    noOfProblems = count;
    for (int j = 0; j < count; j++) {
      if (i == 0) {
        Problem* p = malloc(sizeof(Problem) + count * sizeof(unsigned int));
        problems[j] = p;
      }

      problems[j]->numbers[i] = numbers[j];
    }
  }

  fgets(line, sizeof(line), fptr);
  Operation* operations = malloc(1000 * sizeof(Operation));
  parseOperations(line, operations);

  for (int i = 0; i < noOfProblems; i++) {
    problems[i]->operation = operations[i];
  }

  return noOfProblems;
}
