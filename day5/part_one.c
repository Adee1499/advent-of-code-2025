#include <stdio.h>

struct Range {
  unsigned long long a;
  unsigned long long b;
};

int main() {
  FILE* fptr = fopen("input.txt", "r");

  char line[64];

  struct Range ranges[192];

  int i = 0;
  while (fgets(line, sizeof(line), fptr) && line[0] != '\n') {
    sscanf(line, "%llu-%llu", &ranges[i].a, &ranges[i].b);
    i++;
  }

  unsigned long long id;
  int freshIngredients = 0;
  while (fscanf(fptr, "%llu", &id) == 1) {
    for (int i = 0; i < 192; i++) {
      if (id >= ranges[i].a && id <= ranges[i].b) {
        freshIngredients++;
        break;
      }
    }
  }

  printf("Fresh ingredients: %d", freshIngredients);
  fclose(fptr);
  return 0;
}
