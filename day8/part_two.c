#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define JBOX_COUNT 1000

typedef struct {
  int x;
  int y;
  int z;
} Vector;

typedef struct {
  int a;
  int b;
  double distance;
} Pair;

double vector_distance(Vector *a, Vector *b);

int comparePair(const void *a, const void *b) {
  double diff = ((Pair*)a)->distance - ((Pair*)b)->distance;
  if (diff < 0) return -1;
  if (diff > 0) return 1;
  return 0;
}

int compareInt(const void *a, const void *b) {
  return (*(int*)b - *(int*)a);
}

int find(int x, int parents[]);
void make_union(int x, int y, int parents[]);

int main() {
  FILE *fptr = fopen("input.txt", "r");

  char buffer[64];

  Vector jboxes[JBOX_COUNT];

  int i = 0;
  while (fgets(buffer, sizeof(buffer), fptr)) {
    sscanf(buffer, "%d,%d,%d\n", &jboxes[i].x, &jboxes[i].y, &jboxes[i].z);
    i++;
  }

  int pairCount = JBOX_COUNT * (JBOX_COUNT - 1) / 2;
  Pair pairs[pairCount];

  int pairIndex = 0;
  for (int j = 0; j < JBOX_COUNT - 1; j++) {
    for (int k = j + 1; k < JBOX_COUNT; k++) {
      pairs[pairIndex].a = j;
      pairs[pairIndex].b = k;
      pairs[pairIndex].distance = vector_distance(&jboxes[j], &jboxes[k]);
      pairIndex++;
    }
  }

  // sort pairs by distance ascending
  qsort(pairs, pairCount, sizeof(Pair), comparePair);

  // union-find
  int parents[JBOX_COUNT];
  for (int j = 0; j < JBOX_COUNT; j++) {
    parents[j] = j;
  }

  int connections = 0;
  for (int j = 0; j < pairCount; j++) {
    int a = pairs[j].a;
    int b = pairs[j].b;

    if (find(a, parents) != find(b, parents)) {
      make_union(a, b, parents);
      connections++;
      if (connections == JBOX_COUNT - 1) {
        printf("Connected X %d to X %d\n", jboxes[a].x, jboxes[b].x);
        unsigned long result = (unsigned long)jboxes[a].x * (unsigned long)jboxes[b].x;
        printf("Result is %lu\n", result);
      }
    }
  }

  fclose(fptr);
  return 0;
}

double vector_distance(Vector *a, Vector *b) {
  return sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2) + pow(a->z - b->z, 2));
}

int find(int x, int parents[]) {
  while (parents[x] != x) {
    x = parents[x];
  }
  return x;
}

void make_union(int x, int y, int parents[]) {
  int root_x = find(x, parents);
  int root_y = find(y, parents);

  if (root_x == root_y) return;

  parents[root_x] = root_y;
}
