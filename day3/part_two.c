#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  FILE* fptr = fopen("input.txt", "r");

  unsigned long long totalJoltage = 0;
  char bank[101];

  while (fscanf(fptr, "%s", bank) == 1) {
    int batteryCount = strlen(bank);
    char pickedBatteries[13];

    int currentBattery = -1;
    for (int i = 0; i < 12; i++) {
      char largestBattery = '0';
      int largestBatteryIndex = currentBattery;
      for (int j = currentBattery + 1; j < batteryCount + i - 11; j++) {
        if (bank[j] > largestBattery) {
          largestBattery = bank[j];
          largestBatteryIndex = j;
        }
      }
      pickedBatteries[i] = largestBattery;
      currentBattery = largestBatteryIndex;
    }
    pickedBatteries[12] = '\0';

    unsigned long long largestJoltage = strtoull(pickedBatteries, NULL, 10);

    totalJoltage += largestJoltage;
  }

  printf("Answer is: %llu", totalJoltage);

  return 0;
}
