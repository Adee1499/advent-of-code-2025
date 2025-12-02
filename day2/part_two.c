#include <stdio.h>
#include <string.h>

int isValidId(unsigned long long id);
void slice(const char* src, char* dest, int start, int end);

int main() {
  FILE* fptr = fopen("input.txt", "r");
  unsigned long long invalidIdsSum = 0;
  unsigned long long firstId;
  unsigned long long secondId;

  while (fscanf(fptr, "%llu-%llu,", &firstId, &secondId) == 2) {
    for (unsigned long long i = firstId; i <= secondId; i++) {
      if (!isValidId(i)) {
        invalidIdsSum += i;
      }
    }
  }

  printf("Answer is: %llu", invalidIdsSum);

  return 0;
}

int isValidId(unsigned long long id) {
  char idString[20];
  sprintf(idString, "%llu", id);

  int idLength = strlen(idString);

  for (int i = 2; i <= idLength; i++) {
    if (idLength % i != 0) continue;

    int sequenceLength = idLength / i;
    char firstSequenceString[sequenceLength + 1];
    slice(idString, firstSequenceString, 0, sequenceLength);

    int allMatch = 1;

    for (int j = 1; j < i; j++) {
      char currentSequenceString[sequenceLength + 1];
      slice(idString, currentSequenceString, j * sequenceLength, (j + 1) * sequenceLength);

      if (strcmp(firstSequenceString, currentSequenceString) != 0) {
        allMatch = 0;
        break;
      }
    }

    if (allMatch) { return 0; }
  }

  return 1;
}


void slice(const char* src, char* dest, int start, int end) {
  for (int i = 0; i < end - start; i++) {
    dest[i] = src[start + i];
  }
  dest[end - start] = '\0';
}
