#include <stdbool.h>
#include <stdio.h>

#include <stdint.h>
#include <stdlib.h>

/**
 * Library-level functions.
 * You should use them in the main sections.
 */

uint64_t convertToUint64(double number) { return *((uint64_t *)(&number)); }

bool getBit(const uint64_t number, const uint8_t index) {
  return number & (1 << index);
}

bool hasZeroExponent(uint64_t number) {
  for (int i = 52; i <= 62; i++) {
    if (getBit(number, i)) {
      return 0;
    }
  }

  return 1;
}

bool isPositive(uint64_t number) { return getBit(number, 63); }

bool isNaN(uint64_t number) {
  for (int i = 52; i <= 62; i++) {
    if (!getBit(number, i)) {
      return 0;
    }
  }

  int all_bits_zero = 1;
  for (int i = 0; i <= 51; i++) {
    if (getBit(number, i)) {
      all_bits_zero = 0;
      break;
    }
  }

  if (all_bits_zero) {
    return 0;
  }

  return 1;
}

bool isDenormalized(uint64_t number) { return hasZeroExponent(number) ? 1 : 0; }

/**
 * Checkers here:
 */

bool checkForPlusZero(uint64_t number) { return number == 0x0; }

bool checkForMinusZero(uint64_t number) { return number == 0x8000000000000000; }

bool checkForPlusInf(uint64_t number) { return number == 0x7FF0000000000000; }

bool checkForMinusInf(uint64_t number) { return number == 0xFFF0000000000000; }

bool checkForPlusNormal(uint64_t number) {
  return !isDenormalized(number) && isPositive(number);
}

bool checkForMinusNormal(uint64_t number) {
  return !isDenormalized(number) && !isPositive(number);
}

bool checkForPlusDenormal(uint64_t number) {
  return isDenormalized(number) && isPositive(number);
}

bool checkForMinusDenormal(uint64_t number) {
  return isDenormalized(number) && !isPositive(number);
}

bool checkForSignalingNan(uint64_t number) {
  if (!isNaN(number)) {
    return 0;
  }

  return !getBit(number, 51);
}

bool checkForQuietNan(uint64_t number) {
  if (!isNaN(number)) {
    return 0;
  }

  return getBit(number, 51);
}

void classify(double number) {
  if (checkForPlusZero(convertToUint64(number))) {
    printf("Plus zero\n");
  }

  else if (checkForMinusZero(convertToUint64(number))) {
    printf("Minus zero\n");
  }

  else if (checkForPlusInf(convertToUint64(number))) {
    printf("Plus inf\n");
  }

  else if (checkForMinusInf(convertToUint64(number))) {
    printf("Minus inf\n");
  }

  else if (checkForPlusNormal(convertToUint64(number))) {
    printf("Plus normal\n");
  }

  else if (checkForMinusNormal(convertToUint64(number))) {
    printf("Minus normal\n");
  }

  else if (checkForPlusDenormal(convertToUint64(number))) {
    printf("Plus Denormal\n");
  }

  else if (checkForMinusDenormal(convertToUint64(number))) {
    printf("Minus Denormal\n");
  }

  else if (checkForSignalingNan(convertToUint64(number))) {
    printf("Signailing NaN\n");
  }

  else if (checkForQuietNan(convertToUint64(number))) {
    printf("Quiet NaN\n");
  }

  else {
    printf("Error.\n");
  }
}
