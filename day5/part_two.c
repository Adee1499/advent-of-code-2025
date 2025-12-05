#include <stdio.h>

#define RANGE_SIZE 192

struct Range {
  unsigned long long a;
  unsigned long long b;
};

void bubbleSort(struct Range ranges[]);
int checkOverlap(struct Range rangeA, struct Range rangeB);

int main() {
  FILE* fptr = fopen("input.txt", "r");

  char line[64];

  struct Range ranges[RANGE_SIZE];

  int i = 0;
  while (fgets(line, sizeof(line), fptr) && line[0] != '\n') {
    sscanf(line, "%llu-%llu", &ranges[i].a, &ranges[i].b);
    i++;
  }

  bubbleSort(ranges);

  int mergedCount = 1;
  for (int j = 1; j < i; j++) {
    if (checkOverlap(ranges[mergedCount - 1], ranges[j])) {
      if (ranges[j].b > ranges[mergedCount - 1].b) {
        ranges[mergedCount - 1]. b = ranges[j].b;
      }
    } else {
      ranges[mergedCount] = ranges[j];
      mergedCount++;
    }
  }

  unsigned long long freshIngredients = 0;

  for (int j = 0; j < mergedCount; j++) {
    freshIngredients += ranges[j].b - ranges[j].a + 1;
  }

  printf("Fresh ingredients: %llu", freshIngredients);
  fclose(fptr);
  return 0;
}

void bubbleSort(struct Range ranges[]) {
  int swapped = 0;
  while (!swapped) {
    swapped = 1;
    for (int i = 0; i < RANGE_SIZE - 1; i++) {
      if (ranges[i].a > ranges[i + 1].a) {
        struct Range temp = ranges[i];
        ranges[i] = ranges[i + 1];
        ranges[i + 1] = temp;
        swapped = 0;
      }
    }
  }
}

int checkOverlap(struct Range rangeA, struct Range rangeB) {
  return rangeB.a <= rangeA.b + 1;
}
