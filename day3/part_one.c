#include <stdio.h>
#include <string.h>

int main() {
  FILE* fptr = fopen("input.txt", "r");

  int totalJoltage = 0;
  char bank[101];

  while (fscanf(fptr, "%s", bank) == 1) {
    int batteryCount = strlen(bank);
    int largestJoltage = 0;
    for (int i = 0; i < batteryCount - 1; i++) {
      for (int j = i + 1; j < batteryCount; j++) {
        int firstDigit = bank[i] - '0';
        int secondDigit = bank[j] - '0';
        int currentJoltage = firstDigit * 10 + secondDigit;
        if (currentJoltage > largestJoltage) {
          largestJoltage = currentJoltage;
        }
      }
    }
    totalJoltage += largestJoltage;
  }

  printf("Answer is: %d", totalJoltage);

  return 0;
}
