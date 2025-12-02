#include <stdio.h>
#include <string.h>

int isValidId(unsigned long long id);

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
  int isValid = 1;

  int idLength = strlen(idString);
  if (idLength % 2 != 0) {
    return isValid;
  }

  for (int i = 0; i < idLength / 2; i++) {
    if (idString[i] == idString[i + idLength / 2]) {
      isValid = 0;
    } else {
      isValid = 1;
      break;
    }
  }

  return isValid;
}
